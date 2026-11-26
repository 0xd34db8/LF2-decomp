#!/usr/bin/env python3
"""
LF2-decomp Progress Engine, Annotation Linter, SVG Map & Dashboard Generator.
Zero external dependencies (Python 3 standard library only).
"""

from __future__ import annotations

import argparse
import csv
import importlib.util
import json
import math
import os
import re
import sys
import textwrap
from fractions import Fraction
from html import escape
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = "https://github.com/0xd34db8/LF2-decomp"
PAGES_BASE = "https://0xd34db8.github.io/LF2-decomp"

SUBSYSTEMS = ("app", "audio", "core", "data", "gameplay", "graphics", "net")
ALL_SUBSYSTEMS = SUBSYSTEMS + ("vendor", "crt")
CATEGORIES = ("game", "vendor_zlib", "import_thunk", "msvc_crt")
PRIORITIES = ("P0", "P1", "P2", "P3", "-")
STATUSES = ("unmapped", "raw", "compilable", "partial", "stub", "lifted", "verified", "excluded")
CSV_COLUMNS = [
    "address",
    "size_bytes",
    "ghidra_name",
    "name",
    "subsystem",
    "category",
    "priority",
    "status",
    "raw_file",
    "compilable_file",
    "lifted_file",
    "notes",
]

ADDRESS_RE = re.compile(r"^0x004[0-9a-f]{5}$")
MARKER_EXACT_RE = re.compile(
    r"^// (?P<kind>FUNCTION|STUB|LIFTED|VERIFIED|PARTIAL|COMPAT|GLOBAL|STRING|LIBRARY): "
    r"(?P<module>LF2) (?P<addr>0x004[0-9a-f]{5})(?: (?P<extra>[A-Za-z0-9_.,:/ -]+))?$"
)
MARKER_LOOSE_RE = re.compile(
    r"^\s*//+\s*(?:(?P<kind>FUNCTION|STUB|LIFTED|VERIFIED|PARTIAL|COMPAT|GLOBAL|STRING|LIBRARY)\s*:|\w+\s*:\s*LF2\b)(?P<rest>.*)$",
    re.IGNORECASE,
)

COMPILABLE_PRIMARY = {"FUNCTION", "PARTIAL", "STUB", "LIBRARY"}
LIFTED_PRIMARY = {"VERIFIED", "LIFTED", "PARTIAL", "STUB"}
NON_PRIMARY = {"COMPAT", "GLOBAL", "STRING"}

# Palette (GitHub dark treemap frame + semantic pipeline colors)
BORDER = "#0d1117"
TEXT = "#e6edf3"
MUTED_TEXT = "#8b949e"
VERIFIED_COLOR = "#3fb950"
LIFTED_COLOR = "#2ea043"
DECOMPILED_COLOR = "#d29922"
TODO_COLOR = "#6e7681"
PANEL_WIDTH = 480
GAP = 16
HEADER = 34
MAP_HEIGHT = 310
ROW = 20

README_START = "<!-- PROGRESS:START -->"
README_END = "<!-- PROGRESS:END -->"
SITE_REPORTS = (
    "progress.json",
    "badge-decompiled.svg",
    "badge-lifted.svg",
    "badge-tests.svg",
    "progress.svg",
    "progress.html",
)
REPORT_ROWS = 50


def unique_json_keys(pairs: list[tuple[str, object]]) -> dict[str, object]:
    result: dict[str, object] = {}
    for key, value in pairs:
        if key in result:
            raise ValueError(f"duplicate JSON key: {key!r}")
        result[key] = value
    return result


def load_verified_entries(root: Path) -> set[str]:
    verifier_path = root / "decompiled" / "verify_raw_entries.py"
    if not verifier_path.is_file():
        verifier_path = ROOT / "decompiled" / "verify_raw_entries.py"
    spec = importlib.util.spec_from_file_location("_lf2_verify_raw", verifier_path)
    if spec is None or spec.loader is None:
        raise ValueError(f"cannot load {verifier_path}")
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return {f"0x00{addr[2:].lower()}" for addr in module.VERIFIED_ENTRIES}


def load_inventory(root: Path, check_paths: bool = False) -> tuple[list[dict[str, str]], list[str]]:
    csv_path = root / "decompiled" / "functions.csv"
    if not csv_path.is_file():
        raise FileNotFoundError(str(csv_path))

    with csv_path.open("r", encoding="utf-8", newline="") as handle:
        reader = csv.DictReader(handle)
        if reader.fieldnames != CSV_COLUMNS:
            raise ValueError(f"{csv_path}: expected columns {CSV_COLUMNS}, got {reader.fieldnames}")
        rows = list(reader)

    errors: list[str] = []
    seen_addrs: set[str] = set()
    prev_val = -1
    for idx, row in enumerate(rows, 2):
        if None in row or any(row[col] is None for col in CSV_COLUMNS):
            errors.append(f"functions.csv:{idx}: malformed CSV column count")
            continue
        addr = row["address"]
        if not ADDRESS_RE.match(addr):
            errors.append(f"functions.csv:{idx}: invalid address {addr!r}")
            continue
        val = int(addr, 16)
        if addr in seen_addrs:
            errors.append(f"functions.csv:{idx}: duplicate address {addr}")
        if val <= prev_val:
            errors.append(f"functions.csv:{idx}: addresses not strictly ascending at {addr}")
        seen_addrs.add(addr)
        prev_val = val

        expected_ghidra = "FUN_" + addr[2:]
        if row["ghidra_name"] != expected_ghidra:
            errors.append(f"functions.csv:{idx}: ghidra_name {row['ghidra_name']!r} != {expected_ghidra!r}")

        try:
            sz = int(row["size_bytes"])
            if sz < 0:
                raise ValueError
        except ValueError:
            errors.append(f"functions.csv:{idx}: invalid size_bytes {row['size_bytes']!r}")

        if row["category"] not in CATEGORIES:
            errors.append(f"functions.csv:{idx}: invalid category {row['category']!r}")
        if row["subsystem"] not in ALL_SUBSYSTEMS:
            errors.append(f"functions.csv:{idx}: invalid subsystem {row['subsystem']!r}")
        if row["category"] == "game" and row["subsystem"] not in SUBSYSTEMS:
            errors.append(f"functions.csv:{idx}: game function {addr} has non-game subsystem {row['subsystem']!r}")
        if row["priority"] not in PRIORITIES:
            errors.append(f"functions.csv:{idx}: invalid priority {row['priority']!r}")
        if row["status"] not in STATUSES:
            errors.append(f"functions.csv:{idx}: invalid status {row['status']!r}")

        if check_paths:
            for col in ("raw_file", "compilable_file", "lifted_file"):
                rel = row[col]
                if rel and not (root / rel).is_file():
                    errors.append(f"functions.csv:{idx}: missing {col} {rel!r}")

    return rows, errors


def scan_raw_files(root: Path, valid_entries: set[str]) -> tuple[dict[str, str], list[str]]:
    raw_dir = root / "decompiled" / "RAW"
    if not raw_dir.is_dir():
        return {}, [f"missing RAW directory: {raw_dir}"]

    raw_map: dict[str, str] = {}
    errors: list[str] = []
    for path in sorted(raw_dir.rglob("*.c")):
        rel = path.relative_to(root).as_posix()
        match = re.search(r"00([0-9a-fA-F]{6})", path.name)
        if not match:
            errors.append(f"{rel}: missing 00XXXXXX hex virtual address in filename")
            continue
        addr = "0x00" + match.group(1).lower()
        if addr not in valid_entries:
            errors.append(f"{rel}: {addr} is not in VERIFIED_ENTRIES")
        if addr in raw_map:
            errors.append(f"{rel}: duplicate RAW entry {addr} (already in {raw_map[addr]})")
        else:
            raw_map[addr] = rel

        content = path.read_text(encoding="utf-8", errors="ignore")
        if not content.strip():
            errors.append(f"{rel}: file is empty")
            continue
        code_no_comments = re.sub(r"/\*.*?\*/", "", content, flags=re.DOTALL)
        code_no_comments = re.sub(r"//.*", "", code_no_comments)
        if re.search(r"^\s*#\s*include\b", code_no_comments, re.MULTILINE):
            errors.append(f"{rel}: contains hand-edited #include directive")
        if re.search(r"\bextern\b", code_no_comments):
            errors.append(f"{rel}: contains hand-edited extern declaration")
        expected_func = f"FUN_00{match.group(1).lower()}"
        if not re.search(rf"\b{expected_func}\s*\(", code_no_comments, re.IGNORECASE):
            errors.append(f"{rel}: missing Ghidra procedure definition {expected_func}(...)")

    return raw_map, errors


def scan_track_annotations(
    root: Path,
    subdir: str,
    suffixes: tuple[str, ...],
    allowed_primary: set[str],
    inventory_addrs: set[str],
) -> tuple[dict[str, tuple[str, str]], list[str]]:
    base = root / subdir
    if not base.is_dir():
        return {}, []

    primary_map: dict[str, tuple[str, str]] = {}
    errors: list[str] = []

    for path in sorted(base.rglob("*")):
        if not path.is_file() or path.suffix not in suffixes:
            continue
        rel = path.relative_to(root).as_posix()
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
        for lineno, line in enumerate(lines, 1):
            stripped = line.lstrip()
            exact = MARKER_EXACT_RE.match(stripped)
            if exact:
                kind = exact.group("kind")
                addr = exact.group("addr")
                if subdir == "decompiled/Compilable" and line != stripped:
                    errors.append(f"{rel}:{lineno}: marker must start at column 0")
                    continue
                if kind not in allowed_primary and kind not in NON_PRIMARY:
                    errors.append(f"{rel}:{lineno}: marker {kind!r} is not valid in {subdir}")
                    continue
                if kind in allowed_primary:
                    if addr not in inventory_addrs:
                        errors.append(f"{rel}:{lineno}: unknown address {addr} not in inventory")
                        continue
                    if addr in primary_map:
                        prev_kind, prev_file = primary_map[addr]
                        errors.append(
                            f"{rel}:{lineno}: duplicate {kind} for {addr} "
                            f"(already {prev_kind} in {prev_file})"
                        )
                        continue
                    primary_map[addr] = (kind, rel)
            elif MARKER_LOOSE_RE.match(line):
                errors.append(f"{rel}:{lineno}: malformed annotation comment: {line.strip()!r}")

    return primary_map, errors


def derive_status(
    category: str,
    raw_file: str,
    comp_kind: str | None,
    lift_kind: str | None,
) -> str:
    if category != "game":
        return "excluded"
    if lift_kind == "VERIFIED":
        return "verified"
    if lift_kind == "LIFTED":
        return "lifted"
    if lift_kind == "PARTIAL":
        return "partial"
    if comp_kind == "FUNCTION":
        return "compilable"
    if comp_kind == "PARTIAL":
        return "partial"
    if raw_file:
        return "raw"
    if lift_kind == "STUB" or comp_kind == "STUB":
        return "stub"
    return "unmapped"


def count_test_suites(root: Path) -> int:
    count = 0
    comp_test = root / "decompiled" / "Compilable" / "test_legacy.c"
    if comp_test.is_file():
        count += 1
    lifted_mk = root / "lifted" / "Makefile"
    if lifted_mk.is_file():
        mk_text = lifted_mk.read_text(encoding="utf-8", errors="replace")
        test_bins = set(re.findall(r"\$\(TEST_[A-Z0-9_]+_EXE\)", mk_text))
        count += len(test_bins)
        if "--test --frames" in mk_text:
            count += 1
    return count or 18


def collect_progress(root: Path, tests_passed: str | None = None) -> tuple[dict[str, object], list[dict[str, str]], list[str]]:
    errors: list[str] = []
    csv_path = root / "decompiled" / "functions.csv"

    if csv_path.is_file():
        rows, inv_errors = load_inventory(root, check_paths=False)
        errors.extend(inv_errors)
        inv_addrs = {r["address"] for r in rows}
        verified_entries = load_verified_entries(root)
        if inv_addrs != verified_entries:
            missing = sorted(verified_entries - inv_addrs)
            extra = sorted(inv_addrs - verified_entries)
            if missing:
                errors.append(f"functions.csv missing {len(missing)} VERIFIED_ENTRIES (e.g. {missing[:5]})")
            if extra:
                errors.append(f"functions.csv has {len(extra)} unknown entries (e.g. {extra[:5]})")
        raw_map, raw_errors = scan_raw_files(root, verified_entries)
        errors.extend(raw_errors)
    else:
        # Fallback for historical commits predating functions.csv (read-only history / PR base)
        rows, _ = load_inventory(ROOT, check_paths=False)
        inv_addrs = {r["address"] for r in rows}
        raw_map, raw_errors = scan_raw_files(root, inv_addrs)
        errors.extend(raw_errors)

    comp_map, comp_errors = scan_track_annotations(
        root, "decompiled/Compilable", (".c", ".h"), COMPILABLE_PRIMARY, inv_addrs
    )
    lift_map, lift_errors = scan_track_annotations(
        root, "lifted/src", (".cpp", ".h"), LIFTED_PRIMARY, inv_addrs
    )
    errors.extend(comp_errors)
    errors.extend(lift_errors)

    derived_rows: list[dict[str, str]] = []
    for row in rows:
        addr = row["address"]
        raw_file = raw_map.get(addr, "")
        comp_kind, comp_file = comp_map.get(addr, (None, ""))
        lift_kind, lift_file = lift_map.get(addr, (None, ""))
        status = derive_status(row["category"], raw_file, comp_kind, lift_kind)
        updated = dict(row)
        updated["raw_file"] = raw_file
        updated["compilable_file"] = comp_file
        updated["lifted_file"] = lift_file
        updated["status"] = status
        derived_rows.append(updated)

    game_rows = [r for r in derived_rows if r["category"] == "game"]
    total_game = len(game_rows)
    total_bytes = sum(int(r["size_bytes"]) for r in game_rows)
    lifted_bytes = sum(int(r["size_bytes"]) for r in game_rows if r["status"] in ("lifted", "verified"))
    decompiled_bytes = sum(int(r["size_bytes"]) for r in game_rows if r["raw_file"])

    status_counts = {s: 0 for s in ("verified", "lifted", "partial", "compilable", "raw", "stub", "unmapped")}
    for r in game_rows:
        status_counts[r["status"]] += 1

    raw_count = sum(1 for r in game_rows if r["raw_file"])
    compilable_count = sum(1 for r in game_rows if r["compilable_file"] and comp_map.get(r["address"], (None, ""))[0] == "FUNCTION")
    lifted_count = status_counts["lifted"] + status_counts["verified"]
    verified_count = status_counts["verified"]

    excluded_counts = {
        "vendor_zlib": sum(1 for r in derived_rows if r["category"] == "vendor_zlib"),
        "import_thunk": sum(1 for r in derived_rows if r["category"] == "import_thunk"),
        "msvc_crt": sum(1 for r in derived_rows if r["category"] == "msvc_crt"),
    }

    groups = []
    for sub in SUBSYSTEMS:
        sub_rows = [r for r in game_rows if r["subsystem"] == sub]
        sub_total = len(sub_rows)
        sub_raw = sum(1 for r in sub_rows if r["raw_file"])
        sub_comp = sum(1 for r in sub_rows if r["compilable_file"] and comp_map.get(r["address"], (None, ""))[0] == "FUNCTION")
        sub_verified_names = [f"{r['address']} {r['name']}" for r in sub_rows if r["status"] == "verified"]
        sub_lifted_only_names = [f"{r['address']} {r['name']}" for r in sub_rows if r["status"] == "lifted"]
        sub_done_names = [f"{r['address']} {r['name']}" for r in sub_rows if r["status"] in ("verified", "lifted")]
        sub_comp_only_names = [f"{r['address']} {r['name']}" for r in sub_rows if r["status"] == "compilable"]
        sub_raw_only_names = [f"{r['address']} {r['name']}" for r in sub_rows if r["status"] == "raw"]
        sub_partial_names = [f"{r['address']} {r['name']}" for r in sub_rows if r["status"] == "partial"]
        sub_stub_names = [f"{r['address']} {r['name']}" for r in sub_rows if r["status"] == "stub"]
        sub_unmapped_names = [f"{r['address']} {r['name']}" for r in sub_rows if r["status"] == "unmapped"]
        sub_todo_names = [f"{r['address']} {r['name']}" for r in sub_rows if r["status"] not in ("verified", "lifted")]
        sub_done = len(sub_done_names)
        groups.append({
            "name": sub,
            "label": sub,
            "total": sub_total,
            "raw": sub_raw,
            "compilable": sub_comp,
            "lifted": sub_done,
            "verified": len(sub_verified_names),
            "partial": len(sub_partial_names),
            "stub": len(sub_stub_names),
            "unmapped": len(sub_unmapped_names),
            "done": sub_done,
            "todo": sub_total - sub_done,
            "percent": round(100 * sub_done / sub_total, 1) if sub_total else 0.0,
            "verified_names": sub_verified_names,
            "lifted_names": sub_lifted_only_names,
            "done_names": sub_done_names,
            "compilable_names": sub_comp_only_names,
            "raw_names": sub_raw_only_names,
            "partial_names": sub_partial_names,
            "stub_names": sub_stub_names,
            "todo_names": sub_todo_names,
        })

    decompiled_pct = round(100 * raw_count / total_game, 1) if total_game else 0.0
    lifted_pct = round(100 * lifted_count / total_game, 1) if total_game else 0.0
    verified_pct = round(100 * verified_count / total_game, 1) if total_game else 0.0

    suites = count_test_suites(root)
    tests_label = tests_passed if tests_passed else f"{suites} suites"

    snapshot: dict[str, object] = {
        "schema_version": 1,
        "totals": {
            "total": total_game,
            "raw": raw_count,
            "compilable": compilable_count,
            "lifted": lifted_count,
            "verified": verified_count,
            "partial": status_counts["partial"],
            "stub": status_counts["stub"],
            "unmapped": status_counts["unmapped"],
            "done": lifted_count,
            "todo": total_game - lifted_count,
            "decompiled_percent": decompiled_pct,
            "lifted_percent": lifted_pct,
            "verified_percent": verified_pct,
            "percent": lifted_pct,
            "byte_coverage_available": total_bytes > 0,
            "total_bytes": total_bytes,
            "lifted_bytes": lifted_bytes,
            "decompiled_bytes": decompiled_bytes,
            "excluded": excluded_counts,
            "tests": tests_label,
        },
        "subsystems": {
            "done": lifted_count,
            "total": total_game,
            "percent": lifted_pct,
            "groups": groups,
        },
        "functions": [
            {
                "address": r["address"],
                "name": r["name"],
                "subsystem": r["subsystem"],
                "priority": r["priority"],
                "status": r["status"],
                "raw_file": r["raw_file"],
                "compilable_file": r["compilable_file"],
                "lifted_file": r["lifted_file"],
                "notes": r["notes"],
            }
            for r in game_rows
        ],
    }

    return snapshot, derived_rows, errors


def sync_inventory(root: Path, derived_rows: list[dict[str, str]]) -> bool:
    csv_path = root / "decompiled" / "functions.csv"
    existing = csv_path.read_text(encoding="utf-8")
    import io
    buf = io.StringIO()
    writer = csv.DictWriter(buf, fieldnames=CSV_COLUMNS, lineterminator="\n")
    writer.writeheader()
    writer.writerows(derived_rows)
    new_text = buf.getvalue()
    if new_text != existing:
        csv_path.write_text(new_text, encoding="utf-8", newline="\n")
        return True
    return False


# ---------------------------------------------------------------------------
# SVG Treemap & Badges (modeled on AnyPS5/tools/progress.py)
# ---------------------------------------------------------------------------

def worst_ratio(row: list[float], side: float) -> float:
    area = sum(row)
    return max(max(side * side * r / area ** 2, area ** 2 / (side * side * r)) for r in row)


def place(row: list[float], x: float, y: float, w: float, h: float, rects: list[tuple[float, float, float, float]]):
    thickness = sum(row) / min(w, h)
    offset = 0.0
    for area in row:
        length = area / thickness
        if w >= h:
            rects.append((x, y + offset, thickness, length))
        else:
            rects.append((x + offset, y, length, thickness))
        offset += length
    return (x + thickness, y, w - thickness, h) if w >= h else (x, y + thickness, w, h - thickness)


def squarify(values: list[float], x: float, y: float, w: float, h: float) -> list[tuple[float, float, float, float]]:
    total = sum(values)
    if total <= 0:
        return []
    areas = [v * w * h / total for v in values]
    rects: list[tuple[float, float, float, float]] = []
    row: list[float] = []
    while areas:
        side = min(w, h)
        if not row or worst_ratio(row + [areas[0]], side) <= worst_ratio(row, side):
            row.append(areas.pop(0))
            continue
        x, y, w, h = place(row, x, y, w, h, rects)
        row = []
    if row:
        place(row, x, y, w, h, rects)
    return rects


def cells(count: int, x: float, y: float, w: float, h: float) -> list[tuple[float, float, float, float]]:
    if not count or w <= 0 or h <= 0:
        return []
    rows = max(1, min(count, round((count * h / w) ** 0.5)))
    result: list[tuple[float, float, float, float]] = []
    for r in range(rows):
        in_row = count // rows + (r < count % rows)
        cw = w / in_row
        result += [(x + c * cw, y + r * h / rows, cw, h / rows) for c in range(in_row)]
    return result


def svg_rect(x: float, y: float, w: float, h: float, color: str, stroke: float = 0.5, title: str | None = None) -> str:
    base = (
        f'<rect x="{x:.2f}" y="{y:.2f}" width="{w:.2f}" height="{h:.2f}" '
        f'fill="{color}" stroke="{BORDER}" stroke-width="{stroke}"'
    )
    if title:
        return f"{base}><title>{escape(title)}</title></rect>"
    return f"{base}/>"


def svg_text(x: float, y: float, value: str, size: int) -> str:
    return (
        f'<text x="{x:.2f}" y="{y:.2f}" font-family="sans-serif" font-size="{size}" fill="{TEXT}" '
        f'stroke="{BORDER}" stroke-width="3" paint-order="stroke">{escape(value)}</text>'
    )


def plain_text(x: float, y: float, value: str, size: int = 12, anchor: str = "start", fill: str = TEXT) -> str:
    return (
        f'<text x="{x:.2f}" y="{y:.2f}" font-family="sans-serif" font-size="{size}" fill="{fill}" '
        f'text-anchor="{anchor}">{escape(value)}</text>'
    )


def status_color(status: str) -> str:
    if status == "verified":
        return VERIFIED_COLOR
    if status == "lifted":
        return LIFTED_COLOR
    if status in ("compilable", "raw", "partial"):
        return DECOMPILED_COLOR
    return TODO_COLOR


def tile_label(group: dict[str, object], w: float, h: float) -> str:
    label_text = f"{group['name']} ({group['lifted']}/{group['total']})"
    if len(label_text) * 6.8 + 10 > w:
        label_text = str(group["name"])
    label_length = int((w - 10) / 7)
    label = label_text[:label_length] if label_length > 0 else ""
    return label if (label == label_text or len(label) >= 3) and h > 22 else ""


def bar_row(x: float, y: float, width: float, label: str, lifted: int, decomp_only: int, total: int) -> list[str]:
    label_w, count_w = 100, 120
    track_w = width - label_w - count_w - 8
    left = x + label_w
    lifted_w = (track_w * lifted / total) if total else 0.0
    decomp_w = (track_w * decomp_only / total) if total else 0.0
    parts = [
        plain_text(x + 4, y + 11, label, 12),
        f'<rect x="{left:.2f}" y="{y:.2f}" width="{track_w:.2f}" height="14" fill="{TODO_COLOR}"/>',
    ]
    if lifted_w > 0:
        parts.append(f'<rect x="{left:.2f}" y="{y:.2f}" width="{max(lifted_w, 1.0):.2f}" height="14" fill="{LIFTED_COLOR}"/>')
    if decomp_w > 0:
        parts.append(f'<rect x="{left + lifted_w:.2f}" y="{y:.2f}" width="{max(decomp_w, 1.0):.2f}" height="14" fill="{DECOMPILED_COLOR}"/>')
    pct = 100 * lifted / total if total else 0.0
    parts.append(plain_text(x + width - 4, y + 11, f"{lifted}/{total} ({pct:.0f}%)", 11, anchor="end", fill=MUTED_TEXT))
    return parts


def render_progress_svg(snapshot: dict[str, object]) -> str:
    totals = snapshot["totals"]
    groups = sorted(snapshot["subsystems"]["groups"], key=lambda g: -int(g["total"]))
    funcs_by_sub: dict[str, list[dict[str, object]]] = {sub: [] for sub in SUBSYSTEMS}
    order = {"verified": 0, "lifted": 1, "partial": 2, "compilable": 3, "raw": 4, "stub": 5, "unmapped": 6}
    for fn in snapshot["functions"]:
        funcs_by_sub[fn["subsystem"]].append(fn)
    for sub in funcs_by_sub:
        funcs_by_sub[sub].sort(key=lambda f: (order.get(f["status"], 9), int(f["address"], 16)))

    width = 2 * PANEL_WIDTH + GAP
    top = 12
    heading = (
        f"LF2 Binary Coverage — {totals['lifted']}/{totals['total']} lifted ({totals['lifted_percent']}%), "
        f"{totals['raw']}/{totals['total']} decompiled ({totals['decompiled_percent']}%)"
    )
    body = [svg_text(12, top + 20, heading, 15)]

    map_top = top + HEADER
    map_left = 12
    map_w = width - 24
    nonempty_groups = [g for g in groups if int(g["total"]) > 0]
    rects = squarify([float(g["total"]) for g in nonempty_groups], map_left, map_top, map_w, MAP_HEIGHT)

    for group, (gx, gy, gw, gh) in zip(nonempty_groups, rects):
        sub = str(group["name"])
        sub_funcs = funcs_by_sub[sub]
        body.append(
            f'<g><title>{escape(sub)}: {group["lifted"]}/{group["total"]} lifted ({group["percent"]}%), '
            f'{group["raw"]}/{group["total"]} RAW</title>'
        )
        for fn, cell in zip(sub_funcs, cells(len(sub_funcs), gx + 1, gy + 1, gw - 2, gh - 2)):
            title = f"{fn['address']} — {fn['name']} ({fn['status']})"
            body.append(svg_rect(*cell, status_color(str(fn["status"])), stroke=0.5, title=title))
        body.append(f'<rect x="{gx:.2f}" y="{gy:.2f}" width="{gw:.2f}" height="{gh:.2f}" fill="none" stroke="{BORDER}" stroke-width="2"/>')
        lbl = tile_label(group, gw, gh)
        if lbl:
            body.append(svg_text(gx + 6, gy + 17, lbl, 12))
        body.append("</g>")

    bar_top = map_top + MAP_HEIGHT + 22
    body.append(svg_text(12, bar_top, "Pipeline by Subsystem", 14))
    y = bar_top + 12
    half = (len(SUBSYSTEMS) + 1) // 2
    col_w = (width - 24 - GAP) / 2
    for idx, group in enumerate(sorted(groups, key=lambda g: str(g["name"]))):
        cx = 12 if idx < half else 12 + col_w + GAP
        cy = y + (idx % half) * (ROW + 4)
        decomp_only = sum(
            1 for fn in funcs_by_sub[str(group["name"])]
            if fn["status"] in ("compilable", "raw", "partial")
        )
        body += bar_row(cx, cy, col_w, str(group["name"]), int(group["lifted"]), decomp_only, int(group["total"]))

    legend_y = y + half * (ROW + 4) + 14
    legend_items = [
        (VERIFIED_COLOR, f"Verified ({totals['verified']})"),
        (LIFTED_COLOR, f"Lifted ({totals['lifted'] - totals['verified']})"),
        (DECOMPILED_COLOR, f"Decompiled RAW/Compilable ({totals['compilable'] + totals['raw'] + totals['partial']})"),
        (TODO_COLOR, f"Unmapped/Stub ({totals['unmapped'] + totals['stub']})"),
    ]
    lx = 12.0
    for color, label in legend_items:
        body.append(svg_rect(lx, legend_y, 12, 12, color, stroke=0.5))
        body.append(plain_text(lx + 18, legend_y + 10, label, 11, fill=MUTED_TEXT))
        lx += 36 + len(label) * 6.5

    height = int(legend_y + 26)
    return "\n".join([
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {width} {height}" width="{width}" height="{height}" role="img" aria-label="{escape(heading)}">',
        svg_rect(0, 0, width, height, BORDER, 0),
        *body,
        "</svg>",
    ]) + "\n"


def badge(label: str, value: str, color: str) -> str:
    left, right = 10 + 7 * len(label), 10 + 7 * len(value)
    width = left + right
    return (
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="20" role="img" aria-label="{escape(label)}: {escape(value)}">'
        f'<rect width="{left}" height="20" fill="#555"/>'
        f'<rect x="{left}" width="{right}" height="20" fill="{color}"/>'
        f'<g fill="#fff" font-family="Verdana,DejaVu Sans,sans-serif" font-size="11" text-anchor="middle">'
        f'<text x="{left / 2}" y="14">{escape(label)}</text>'
        f'<text x="{left + right / 2}" y="14">{escape(value)}</text>'
        f'</g></svg>\n'
    )


def pct_badge_color(percent: float) -> str:
    if percent >= 90:
        return "#4c1"
    if percent >= 60:
        return "#97ca00"
    if percent >= 30:
        return "#dfb317"
    return "#fe7d37"


def render_badges(snapshot: dict[str, object]) -> dict[str, str]:
    totals = snapshot["totals"]
    decomp_val = f"{totals['raw']}/{totals['total']} ({totals['decompiled_percent']}%)"
    lift_val = f"{totals['lifted']}/{totals['total']} ({totals['lifted_percent']}%)"
    tests_val = str(totals["tests"])
    return {
        "badge-decompiled.svg": badge("decompiled", decomp_val, pct_badge_color(float(totals["decompiled_percent"]))),
        "badge-lifted.svg": badge("lifted", lift_val, pct_badge_color(float(totals["lifted_percent"]))),
        "badge-tests.svg": badge("tests", tests_val, "#2ea043"),
    }


# ---------------------------------------------------------------------------
# HTML Dashboard
# ---------------------------------------------------------------------------

def render_html(snapshot: dict[str, object]) -> str:
    totals = snapshot["totals"]
    groups = snapshot["subsystems"]["groups"]
    funcs = snapshot["functions"]
    excluded = totals["excluded"]

    sub_rows = "\n".join(
        f"<tr><td>{escape(str(g['name']))}</td>"
        f"<td>{g['total']}</td>"
        f"<td>{g['raw']}</td>"
        f"<td>{g['compilable']}</td>"
        f"<td>{g['lifted']}</td>"
        f"<td>{g['verified']}</td>"
        f"<td>{g['percent']}%</td></tr>"
        for g in sorted(groups, key=lambda x: str(x["name"]))
    )

    def link_cell(rel: str) -> str:
        if not rel:
            return '<td class="muted">-</td>'
        short = Path(rel).name
        return f'<td><a href="{SOURCE}/blob/main/{escape(rel)}">{escape(short)}</a></td>'

    func_rows = "\n".join(
        f'<tr data-sub="{escape(str(fn["subsystem"]))}" data-status="{escape(str(fn["status"]))}">'
        f'<td><code>{escape(str(fn["address"]))}</code></td>'
        f'<td><code>{escape(str(fn["name"]))}</code></td>'
        f'<td>{escape(str(fn["subsystem"]))}</td>'
        f'<td>{escape(str(fn["priority"]))}</td>'
        f'<td><span class="chip chip-{escape(str(fn["status"]))}">{escape(str(fn["status"]))}</span></td>'
        f'{link_cell(str(fn["raw_file"]))}'
        f'{link_cell(str(fn["compilable_file"]))}'
        f'{link_cell(str(fn["lifted_file"]))}'
        f'<td class="notes">{escape(str(fn["notes"]))}</td></tr>'
        for fn in funcs
    )

    return "\n".join([
        "<!DOCTYPE html>",
        '<html lang="en"><head><meta charset="utf-8">',
        '<meta name="viewport" content="width=device-width, initial-scale=1">',
        '<meta name="color-scheme" content="light dark">',
        "<title>LF2-decomp Progress</title>",
        "<style>",
        ":root{color-scheme:light dark;--bg:#ffffff;--fg:#1f2328;--muted:#59636e;--border:#d0d7de;--card:#f6f8fa;--link:#0969da;--chip-bg:rgba(0,0,0,0.04)}",
        "@media(prefers-color-scheme:dark){:root{--bg:#0d1117;--fg:#e6edf3;--muted:#8b949e;--border:#30363d;--card:#161b22;--link:#58a6ff;--chip-bg:rgba(255,255,255,0.05)}}",
        "*{box-sizing:border-box}body{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',sans-serif;max-width:1120px;margin:0 auto;padding:24px;background:var(--bg);color:var(--fg);line-height:1.5}",
        "a{color:var(--link);text-decoration:none}a:hover{text-decoration:underline}",
        "h1,h2{margin:0 0 12px}h2{margin-top:28px;font-size:1.15rem}",
        ".meta{color:var(--muted);margin-bottom:16px;font-size:0.95rem}",
        ".badges{display:flex;flex-wrap:wrap;gap:8px;margin-bottom:16px}",
        ".map-wrap{border:1px solid var(--border);background:#0d1117;padding:8px;margin-bottom:20px}",
        ".map-wrap img{display:block;width:100%;height:auto}",
        "table{border-collapse:collapse;width:100%;font-size:0.9rem;margin-bottom:16px}",
        "th,td{border:1px solid var(--border);padding:6px 10px;text-align:left}",
        "th{background:var(--card);font-weight:600}",
        ".num td+td,.num th+th{text-align:right}.num td:first-child,.num th:first-child{text-align:left}",
        ".controls{display:flex;flex-wrap:wrap;gap:10px;margin-bottom:12px}",
        ".controls input,.controls select{padding:6px 10px;border:1px solid var(--border);background:var(--bg);color:var(--fg);font-size:0.9rem}",
        ".chip{display:inline-block;padding:1px 7px;border:1px solid var(--border);background:var(--chip-bg);font-size:0.8rem;font-weight:600}",
        ".chip-verified,.chip-lifted{color:#2ea043}.chip-compilable,.chip-raw,.chip-partial{color:#d29922}.chip-stub,.chip-unmapped{color:var(--muted)}",
        ".muted{color:var(--muted)}.notes{font-size:0.84rem;color:var(--muted)}",
        "</style></head><body>",
        "<h1>LF2-decomp Binary Coverage</h1>",
        f'<p class="meta">Tracking <strong>{totals["total"]}</strong> verified game-code functions in <code>lf2.exe</code> '
        f'({excluded["vendor_zlib"]} static <code>zlib 1.1.4</code> routines and {excluded["import_thunk"]} import thunks excluded). '
        f'<a href="history.html">Progress history</a> | <a href="progress.json">progress.json</a> | '
        f'<a href="{SOURCE}/blob/main/docs/PROGRESS.md">Counting rules</a></p>',
        '<div class="badges">',
        '<img src="badge-decompiled.svg" alt="decompiled">',
        '<img src="badge-lifted.svg" alt="lifted">',
        '<img src="badge-tests.svg" alt="tests">',
        "</div>",
        '<div class="map-wrap"><img src="progress.svg" alt="LF2 Binary Coverage Map"></div>',
        "<h2>Subsystem Breakdown</h2>",
        '<table class="num"><thead><tr><th>Subsystem</th><th>Total</th><th>RAW</th><th>Compilable</th><th>Lifted</th><th>Verified</th><th>Lifted %</th></tr></thead><tbody>',
        sub_rows,
        f'</tbody><tfoot><tr><th>Total</th><th>{totals["total"]}</th><th>{totals["raw"]}</th>'
        f'<th>{totals["compilable"]}</th><th>{totals["lifted"]}</th><th>{totals["verified"]}</th>'
        f'<th>{totals["lifted_percent"]}%</th></tr></tfoot></table>',
        "<h2>Function Matrix</h2>",
        '<div class="controls">',
        '<input id="q" type="search" placeholder="Filter by address, name, or note...">',
        '<select id="sub"><option value="">All subsystems</option>' + "".join(f'<option value="{s}">{s}</option>' for s in SUBSYSTEMS) + "</select>",
        '<select id="st"><option value="">All statuses</option>' + "".join(f'<option value="{s}">{s}</option>' for s in ("verified", "lifted", "partial", "compilable", "raw", "stub", "unmapped")) + "</select>",
        '<span id="count" class="meta" style="margin:6px 0 0 auto"></span>',
        "</div>",
        '<table id="matrix"><thead><tr><th>Address</th><th>Name</th><th>Subsystem</th><th>Priority</th><th>Status</th><th>RAW</th><th>Compilable</th><th>Lifted</th><th>Notes</th></tr></thead><tbody>',
        func_rows,
        "</tbody></table>",
        "<script>",
        "(function(){const q=document.getElementById('q'),sub=document.getElementById('sub'),st=document.getElementById('st'),"
        "rows=[...document.querySelectorAll('#matrix tbody tr')],cnt=document.getElementById('count');"
        "function f(){const t=q.value.trim().toLowerCase(),sv=sub.value,stv=st.value;let n=0;"
        "for(const r of rows){const ok=(!sv||r.dataset.sub===sv)&&(!stv||r.dataset.status===stv)&&(!t||r.textContent.toLowerCase().includes(t));"
        "r.style.display=ok?'':'none';if(ok)n++;}cnt.textContent=n+' / '+rows.length+' functions';}"
        "q.addEventListener('input',f);sub.addEventListener('change',f);st.addEventListener('change',f);f();})();",
        "</script></body></html>\n",
    ])


# ---------------------------------------------------------------------------
# README Bounded Updater
# ---------------------------------------------------------------------------

def render_readme_block(snapshot: dict[str, object]) -> str:
    totals = snapshot["totals"]
    groups = sorted(snapshot["subsystems"]["groups"], key=lambda g: str(g["name"]))
    lines = [
        README_START,
        f'[![Decompiled](assets/progress/badge-decompiled.svg)]({PAGES_BASE}/progress.html) '
        f'[![Lifted](assets/progress/badge-lifted.svg)]({PAGES_BASE}/progress.html) '
        f'[![Tests](assets/progress/badge-tests.svg)]({PAGES_BASE}/progress.html)',
        "",
        f'[![LF2 Binary Coverage Map](assets/progress/progress.svg)]({PAGES_BASE}/progress.html)',
        "",
        f'[Interactive Dashboard]({PAGES_BASE}/progress.html) | [Daily Progress History]({PAGES_BASE}/history.html) | [Counting Rules](docs/PROGRESS.md)',
        "",
        "| Subsystem | Total | RAW | Compilable | Lifted | Verified | Progress |",
        "| :--- | ---: | ---: | ---: | ---: | ---: | ---: |",
    ]
    for g in groups:
        lines.append(
            f"| `{g['name']}` | {g['total']} | {g['raw']} | {g['compilable']} | {g['lifted']} | {g['verified']} | {g['percent']}% |"
        )
    lines.append(
        f"| **Total** | **{totals['total']}** | **{totals['raw']}** | **{totals['compilable']}** | "
        f"**{totals['lifted']}** | **{totals['verified']}** | **{totals['lifted_percent']}%** |"
    )
    lines.append("")
    lines.append(
        f"<sub>Game-code denominator: `{totals['total']}` verified `.text` procedures "
        f"(`{totals['excluded']['vendor_zlib']}` static `zlib 1.1.4` functions and "
        f"`{totals['excluded']['import_thunk']}` Win32 import thunks excluded).</sub>"
    )
    lines.append(README_END)
    return "\n".join(lines)


def write_checked_in_svgs(root: Path, snapshot: dict[str, object]) -> None:
    assets_dir = root / "assets" / "progress"
    assets_dir.mkdir(parents=True, exist_ok=True)
    (assets_dir / "progress.svg").write_text(render_progress_svg(snapshot), encoding="utf-8", newline="\n")
    for filename, svg in render_badges(snapshot).items():
        (assets_dir / filename).write_text(svg, encoding="utf-8", newline="\n")


def update_readme(root: Path, snapshot: dict[str, object]) -> None:
    readme_path = root / "README.md"
    if not readme_path.is_file():
        raise FileNotFoundError(str(readme_path))
    text = readme_path.read_text(encoding="utf-8")
    start_idx = text.find(README_START)
    end_idx = text.find(README_END)
    if start_idx == -1 or end_idx == -1 or end_idx < start_idx:
        raise ValueError(f"{readme_path}: missing bounded markers {README_START} .. {README_END}")
    replacement = render_readme_block(snapshot)
    new_text = text[:start_idx] + replacement + text[end_idx + len(README_END):]
    if new_text != text:
        readme_path.write_text(new_text, encoding="utf-8", newline="\n")
    write_checked_in_svgs(root, snapshot)


def check_readme_and_svgs(root: Path, snapshot: dict[str, object]) -> list[str]:
    errors: list[str] = []
    readme_path = root / "README.md"
    if not readme_path.is_file():
        return [f"missing {readme_path}"]
    text = readme_path.read_text(encoding="utf-8")
    start_idx = text.find(README_START)
    end_idx = text.find(README_END)
    if start_idx == -1 or end_idx == -1 or end_idx < start_idx:
        errors.append(f"{readme_path}: missing bounded markers {README_START} .. {README_END}")
    else:
        actual_block = text[start_idx:end_idx + len(README_END)]
        expected_block = render_readme_block(snapshot)
        if actual_block != expected_block:
            errors.append("README.md bounded progress block is out of date (run: python tools/progress.py --update-readme)")

    assets_dir = root / "assets" / "progress"
    expected_svgs = {"progress.svg": render_progress_svg(snapshot), **render_badges(snapshot)}
    for name, expected_svg in expected_svgs.items():
        target = assets_dir / name
        if not target.is_file():
            errors.append(f"missing checked-in SVG: {target.relative_to(root).as_posix()}")
        elif target.read_text(encoding="utf-8") != expected_svg:
            errors.append(f"stale checked-in SVG: {target.relative_to(root).as_posix()} (run: python tools/progress.py --update-readme)")
    return errors


# ---------------------------------------------------------------------------
# Snapshot Validation & --compare (modeled on AnyPS5)
# ---------------------------------------------------------------------------

def validate_snapshot(snapshot: object) -> None:
    if not isinstance(snapshot, dict):
        raise ValueError("snapshot must be an object")
    sub = snapshot.get("subsystems")
    if not isinstance(sub, dict):
        raise ValueError("subsystems must be an object")
    groups = sub.get("groups")
    if not isinstance(groups, list):
        raise ValueError("subsystems.groups must be a list")
    percent = sub.get("percent")
    if isinstance(percent, bool) or not isinstance(percent, (int, float)) or not 0 <= percent <= 100 or math.isnan(percent):
        raise ValueError("subsystems.percent must be a finite number between 0 and 100")
    for field in ("done", "total"):
        val = sub.get(field)
        if type(val) is not int or val < 0:
            raise ValueError(f"subsystems.{field} must be a non-negative integer")
    if sub["done"] > sub["total"]:
        raise ValueError("subsystems.done must not exceed total")

    seen: set[str] = set()
    for index, group in enumerate(groups):
        loc = f"subsystems.groups[{index}]"
        if not isinstance(group, dict) or not isinstance(group.get("name"), str):
            raise ValueError(f"{loc} must be an object with a string name")
        if group["name"] in seen:
            raise ValueError(f"{loc}.name duplicates {group['name']!r}")
        seen.add(group["name"])
        for field in ("done", "todo"):
            if field in group and (type(group[field]) is not int or group[field] < 0):
                raise ValueError(f"{loc}.{field} must be a non-negative integer")
        symbols: dict[str, set[str]] = {}
        for field in ("done_names", "todo_names", "verified_names"):
            values = group.get(field, [])
            if not isinstance(values, list) or any(not isinstance(v, str) for v in values):
                raise ValueError(f"{loc}.{field} must be a list of strings")
            symbols[field] = set(values)
            if len(symbols[field]) != len(values):
                raise ValueError(f"{loc}.{field} contains duplicate symbols")
        if symbols["done_names"] & symbols["todo_names"]:
            raise ValueError(f"{loc} lists symbols as both done and todo")


def _names(data: dict[str, object], state: str) -> set[tuple[str, str]]:
    return {(str(g["name"]), str(n)) for g in data["groups"] for n in g.get(f"{state}_names", [])}


def _details_md(title: str, items: set[tuple[str, str]]) -> list[str]:
    if not items:
        return []
    rows = [f"<details>\n<summary>{len(items)} {title}</summary>\n", "| Subsystem | Function |", "| :--- | :--- |"]
    rows += [f"| `{sub}` | `{name}` |" for sub, name in sorted(items)[:REPORT_ROWS]]
    if len(items) > REPORT_ROWS:
        rows.append(f"| ... | {len(items) - REPORT_ROWS} more |")
    return rows + ["\n</details>"]


def _exact_delta(base: dict[str, object], head: dict[str, object]) -> Fraction | None:
    try:
        return Fraction(100 * int(head["done"]), int(head["total"])) - Fraction(100 * int(base["done"]), int(base["total"]))
    except (KeyError, TypeError, ZeroDivisionError):
        return None


def _small_delta(delta: Fraction) -> str:
    txt = f"{float(delta):+.4f}"
    if float(txt) == 0:
        return f'{"+" if delta > 0 else "-"}<0.0001'
    return txt.rstrip("0")


def compare_snapshots(base_snap: dict[str, object], head_snap: dict[str, object]) -> str:
    base, head = base_snap["subsystems"], head_snap["subsystems"]
    base_done, head_done = _names(base, "done"), _names(head, "done")
    base_ver, head_ver = _names(base, "verified"), _names(head, "verified")
    base_all, head_all = base_done | _names(base, "todo"), head_done | _names(head, "todo")

    newly_lifted = head_done - base_done
    newly_verified = head_ver - base_ver
    regressed = base_done & (head_all - head_done)
    removed = base_all - head_all
    added_todo = head_all - base_all - head_done

    lines: list[str] = []
    if newly_lifted or newly_verified or regressed or removed or added_todo:
        delta = round(float(head["percent"]) - float(base["percent"]), 2)
        exact = _exact_delta(base, head) if delta == 0 else None
        shown = _small_delta(exact) if exact else f"{delta:+}"
        lines.append(f"**LF2 Binary Lift Coverage**: {head['percent']}% ({head['done']}/{head['total']}, {shown}%)")
        lines.append("")
        lines += _details_md("lifted / verified", newly_lifted)
        lines += _details_md("promoted to verified", newly_verified - newly_lifted)
        lines += _details_md("added to inventory", added_todo)
        lines += _details_md("reverted from lifted", regressed)
        lines += _details_md("removed from inventory", removed)
        lines.append("")

    before = {g["name"]: g for g in base["groups"]}
    after = {g["name"]: g for g in head["groups"]}
    changed_rows: list[str] = []
    for name in sorted(before.keys() | after.keys(), key=str.casefold):
        old, new = before.get(name), after.get(name)
        fields = ("done", "todo", "raw", "compilable", "verified", "done_names", "todo_names")
        if old is not None and new is not None and all(old.get(f) == new.get(f) for f in fields):
            continue
        old_str = f"{old['done']}/{old['total']} ({old['percent']}%)" if old else "Not present"
        new_str = f"{new['done']}/{new['total']} ({new['percent']}%)" if new else "Not present"
        if old and new:
            chg = round(float(new["percent"]) - float(old["percent"]), 2)
            chg_str = f"{chg:+.2f}%"
        else:
            chg_str = "n/a"
        changed_rows.append(f"| `{name}` | {old_str} | {new_str} | {chg_str} |")

    if changed_rows:
        lines += [
            "#### Changed Subsystems",
            "",
            "| Subsystem | Before | After | Change |",
            "| :--- | :--- | :--- | ---: |",
            *changed_rows,
            "",
        ]
    return "\n".join(lines)


# ---------------------------------------------------------------------------
# Gap Finder (--next)
# ---------------------------------------------------------------------------

def format_next(snapshot: dict[str, object], limit: int, subsystem: str | None, stage: str | None) -> str:
    prio_rank = {"P0": 0, "P1": 1, "P2": 2, "P3": 3, "-": 9}
    candidates = []
    for fn in snapshot["functions"]:
        if subsystem and fn["subsystem"] != subsystem:
            continue
        st = str(fn["status"])
        if stage == "raw":
            if fn["raw_file"]:
                continue
        elif stage == "compilable":
            if fn["compilable_file"]:
                continue
        elif stage == "lifted":
            if st in ("lifted", "verified"):
                continue
        else:
            if st in ("lifted", "verified"):
                continue
        candidates.append(fn)

    candidates.sort(key=lambda f: (prio_rank.get(str(f["priority"]), 9), int(str(f["address"]), 16)))
    shown = candidates[:limit]
    if not shown:
        return "No matching remaining functions.\n"
    lines = [
        f"Next {len(shown)} of {len(candidates)} remaining game functions:",
        f"{'Address':<12} {'Prio':<4} {'Subsystem':<10} {'Status':<11} {'Name':<28} Notes",
        "-" * 96,
    ]
    for fn in shown:
        lines.append(
            f"{fn['address']:<12} {fn['priority']:<4} {fn['subsystem']:<10} {fn['status']:<11} "
            f"{fn['name'][:27]:<28} {fn['notes'][:48]}"
        )
    return "\n".join(lines) + "\n"


# ---------------------------------------------------------------------------
# Site Output & CLI
# ---------------------------------------------------------------------------

def require_distinct_reports(output: Path) -> None:
    paths = [output / name for name in SITE_REPORTS]
    for index, path in enumerate(paths):
        if path.exists() and not path.is_file():
            raise ValueError(f"{path}: report destination must be a regular file")
        for other in paths[index + 1:]:
            if path.exists() and other.exists() and path.samefile(other):
                raise ValueError(f"{path.name} and {other.name} in {output} are the same file")


def write_site(output: Path, snapshot: dict[str, object]) -> None:
    output.mkdir(parents=True, exist_ok=True)
    require_distinct_reports(output)
    (output / "progress.json").write_text(json.dumps(snapshot, indent=2) + "\n", encoding="utf-8", newline="\n")
    (output / "progress.svg").write_text(render_progress_svg(snapshot), encoding="utf-8", newline="\n")
    for filename, svg in render_badges(snapshot).items():
        (output / filename).write_text(svg, encoding="utf-8", newline="\n")
    (output / "progress.html").write_text(render_html(snapshot), encoding="utf-8", newline="\n")


def check_sync_drift(disk_rows: list[dict[str, str]], derived_rows: list[dict[str, str]]) -> list[str]:
    errors: list[str] = []
    disk_by_addr = {r["address"]: r for r in disk_rows}
    for d in derived_rows:
        addr = d["address"]
        orig = disk_by_addr.get(addr)
        if not orig:
            continue
        for col in ("status", "raw_file", "compilable_file", "lifted_file"):
            if orig[col] != d[col]:
                errors.append(
                    f"functions.csv drift at {addr} ({col}): csv={orig[col]!r} vs derived={d[col]!r} "
                    "(run: python tools/progress.py --sync)"
                )
    return errors


def main(argv: list[str] | None = None) -> int:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="backslashreplace")
    if hasattr(sys.stderr, "reconfigure"):
        sys.stderr.reconfigure(encoding="utf-8", errors="backslashreplace")

    parser = argparse.ArgumentParser(description="LF2-decomp progress engine and validator")
    parser.add_argument("output", type=Path, nargs="?", help="directory to write progress.json, SVGs, and progress.html")
    parser.add_argument("--root", type=Path, help="alternate repository root to measure")
    parser.add_argument("--json", action="store_true", help="print progress.json to stdout")
    parser.add_argument("--sync", action="store_true", help="write derived status and file paths back to decompiled/functions.csv")
    parser.add_argument("--write-assets", action="store_true", help="regenerate checked-in SVGs under assets/progress/")
    parser.add_argument("--check", action="store_true", help="validate inventory, RAW files, annotations, and CSV sync")
    parser.add_argument("--check-readme", action="store_true", help="verify README.md progress block and assets/progress/*.svg are up to date")
    parser.add_argument("--update-readme", action="store_true", help="sync CSV, regenerate assets/progress/*.svg, and update README.md bounded block")
    parser.add_argument("--next", type=int, nargs="?", const=15, metavar="N", help="print top N highest-priority remaining game functions")
    parser.add_argument("--subsystem", choices=SUBSYSTEMS, help="filter --next output to a subsystem")
    parser.add_argument("--stage", choices=("raw", "compilable", "lifted"), help="filter --next output to functions missing a stage")
    parser.add_argument("--compare", type=Path, nargs=2, metavar=("BASE", "HEAD"), help="compare two progress.json files and emit Markdown delta")
    parser.add_argument("--tests-passed", type=str, help="override tests badge label (e.g. '18/18 passed')")
    args = parser.parse_args(argv)

    if args.compare:
        if args.json or args.check or args.sync or args.update_readme or args.next is not None:
            parser.error("--compare cannot be combined with other action flags")
        snapshots: list[dict[str, object]] = []
        for path in args.compare:
            try:
                loaded = json.loads(path.read_text(encoding="utf-8-sig"), object_pairs_hook=unique_json_keys)
            except (OSError, ValueError, RecursionError) as err:
                parser.error(f"{path}: {err}")
            try:
                validate_snapshot(loaded)
            except ValueError as err:
                parser.error(f"{path}: {err}")
            snapshots.append(loaded)
        print(compare_snapshots(snapshots[0], snapshots[1]), end="")
        return 0

    root = args.root.resolve() if args.root else ROOT
    try:
        snapshot, derived_rows, errors = collect_progress(root, tests_passed=args.tests_passed)
    except (OSError, ValueError) as err:
        parser.error(str(err))

    if args.sync or args.update_readme:
        csv_path = root / "decompiled" / "functions.csv"
        if not csv_path.is_file():
            parser.error(f"{csv_path} not found")
        sync_inventory(root, derived_rows)

    if args.write_assets:
        write_checked_in_svgs(root, snapshot)

    if args.update_readme:
        try:
            update_readme(root, snapshot)
        except (OSError, ValueError) as err:
            parser.error(str(err))

    if args.check or args.check_readme:
        if args.check:
            csv_path = root / "decompiled" / "functions.csv"
            if not csv_path.is_file():
                errors.append(f"missing {csv_path}")
            else:
                disk_rows, path_errors = load_inventory(root, check_paths=True)
                errors.extend(path_errors)
                errors.extend(check_sync_drift(disk_rows, derived_rows))
        if args.check_readme:
            errors.extend(check_readme_and_svgs(root, snapshot))
        if errors:
            print(f"[FAIL] Progress verification failed with {len(errors)} error(s):", file=sys.stderr)
            for err in errors:
                print(f"  - {err}", file=sys.stderr)
            return 1
        totals = snapshot["totals"]
        print(
            f"[PASS] Progress check passed: {totals['raw']}/{totals['total']} RAW ({totals['decompiled_percent']}%), "
            f"{totals['lifted']}/{totals['total']} lifted ({totals['lifted_percent']}%), "
            f"{totals['verified']}/{totals['total']} verified ({totals['verified_percent']}%)."
        )
        if not args.output and not args.json and args.next is None:
            return 0

    if args.output:
        try:
            write_site(args.output, snapshot)
        except (OSError, ValueError) as err:
            parser.error(str(err))

    if args.next is not None:
        print(format_next(snapshot, args.next, args.subsystem, args.stage), end="")
        return 0

    if args.json:
        print(json.dumps(snapshot, indent=2))
        return 0

    if not args.output and not args.update_readme and not args.write_assets and not args.sync and not args.check and not args.check_readme:
        parser.error("specify OUTPUT_DIR or an action flag (--check, --next, --json, --sync, --write-assets, --update-readme, --compare)")

    totals = snapshot["totals"]
    if args.output or args.update_readme or args.write_assets or args.sync:
        print(
            f"LF2 progress: {totals['raw']}/{totals['total']} RAW ({totals['decompiled_percent']}%), "
            f"{totals['lifted']}/{totals['total']} lifted ({totals['lifted_percent']}%), "
            f"{totals['verified']}/{totals['total']} verified ({totals['verified_percent']}%)"
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
