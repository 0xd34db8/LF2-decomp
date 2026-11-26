#!/usr/bin/env python3
"""
LF2-decomp Progress History Generator.
Walks first-parent commits on a Git ref, measures RAW and Lifted progress per UTC day,
and emits history.json, history.svg, and history.html.
"""

from __future__ import annotations

import argparse
import io
import json
import subprocess
import sys
import tarfile
import tempfile
from datetime import date, datetime, timezone
from html import escape
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import progress

WIDTH, LEFT, RIGHT, TITLE, PANEL, GAP, AXIS = 900, 56, 200, 34, 170, 20, 32
MAX_DOTS = 45
BACKGROUND, GRID, TEXT, MUTED = "#0d1117", "#30363d", "#e6edf3", "#8b949e"
DECOMPILED_COLOR = "#d29922"
LIFTED_COLOR = "#2ea043"

THEME = (
    '.history-theme,svg[role="img"]{color-scheme:light dark;--history-background:#fff;--history-grid:#d0d7de;'
    '--history-text:#1f2328;--history-muted:#59636e;--history-link:#0969da;--history-visited:#8250df;--history-hit:#000}'
    '@media(prefers-color-scheme:dark){.history-theme,svg[role="img"]{--history-background:#0d1117;--history-grid:#30363d;'
    '--history-text:#e6edf3;--history-muted:#8b949e;--history-link:#58a6ff;--history-visited:#bc8cff;--history-hit:#fff}}'
)
SVG_STYLE = (
    "<style>" + THEME + 'svg[role="img"]{fill:var(--history-text)}'
    + "".join(f'svg[role="img"] [fill="{color}"]{{fill:var(--history-{name})}}'
              for name, color in (("background", BACKGROUND), ("text", TEXT), ("muted", MUTED)))
    + "".join(f'svg[role="img"] [stroke="{color}"]{{stroke:var(--history-{name})}}'
              for name, color in (("grid", GRID), ("muted", MUTED)))
    + 'svg[role="img"] .hit{fill:var(--history-hit)}</style>'
)


def git(*args: str) -> bytes:
    try:
        return subprocess.run(["git", "-C", str(progress.ROOT), *args], check=True, capture_output=True).stdout
    except subprocess.CalledProcessError as err:
        reason = err.stderr.decode("utf-8", errors="replace").strip()
        raise ValueError(f"git {' '.join(args)} failed: {reason}") from err


def daily_commits(ref: str) -> list[tuple[str, str]]:
    log = git("log", "--first-parent", "--format=%H %ct", ref)
    seen: dict[str, str] = {}
    for line in log.decode("utf-8").splitlines():
        sha, timestamp = line.split()
        day = datetime.fromtimestamp(int(timestamp), timezone.utc).date().isoformat()
        seen.setdefault(day, sha)
    return sorted(seen.items())


def measure_commit(sha: str) -> dict[str, object] | None:
    candidate_paths = ["decompiled/functions.csv", "decompiled/RAW", "decompiled/Compilable", "lifted/src"]
    tree = set(git("ls-tree", "-r", "--name-only", sha, "--", *candidate_paths).decode("utf-8").splitlines())
    paths = [
        p for p in candidate_paths
        if any(name == p or name.startswith(p + "/") for name in tree)
    ]
    if "decompiled/RAW" not in paths:
        return None

    with tempfile.TemporaryDirectory() as directory:
        root = Path(directory)
        archive = tarfile.open(fileobj=io.BytesIO(git("archive", sha, "--", *paths)))
        if hasattr(tarfile, "data_filter"):
            archive.extractall(root, filter="data")
        else:
            archive.extractall(root)
        snapshot, _, _ = progress.collect_progress(root)

    totals = snapshot["totals"]
    return {
        "total": totals["total"],
        "raw": totals["raw"],
        "compilable": totals["compilable"],
        "lifted": totals["lifted"],
        "verified": totals["verified"],
        "decompiled_percent": totals["decompiled_percent"],
        "lifted_percent": totals["lifted_percent"],
    }


def utc_day(value: str) -> str:
    try:
        if date.fromisoformat(value).isoformat() == value:
            return value
    except ValueError:
        pass
    raise argparse.ArgumentTypeError("date bounds must be valid YYYY-MM-DD UTC days")


def collect(ref: str, since: str | None = None, until: str | None = None) -> list[dict[str, object]]:
    points: list[dict[str, object]] = []
    for day, sha in daily_commits(ref):
        if (since is not None and day < since) or (until is not None and day > until):
            continue
        counts = measure_commit(sha)
        if counts:
            points.append({"date": day, "commit": sha, **counts})
    return points


def labelled(day: date, span: int) -> str:
    if span <= 14:
        return f"{day:%b} {day.day}"
    if span <= 150:
        return f"{day:%b} {day.day}" if day.weekday() == 0 else ""
    return f"{day:%b %Y}" if day.day <= 7 and day.weekday() == 0 else ""


def scale(peak: int) -> tuple[int, int]:
    magnitude = 1
    while peak > 20 * magnitude:
        magnitude *= 10
    step = next(s * magnitude for s in (1, 2, 5) if peak <= s * magnitude * 4) if magnitude > 1 else 5
    return step, max(step, -(-peak // step) * step)


def spread(ys: list[float], gap: int = 16) -> list[float]:
    out = list(ys)
    order = sorted(range(len(ys)), key=ys.__getitem__)
    for above, below in zip(order, order[1:]):
        out[below] = max(out[below], out[above] + gap)
    return out


def chart(points: list[dict[str, object]]) -> str:
    days = [date.fromisoformat(str(p["date"])).toordinal() for p in points]
    first, span = days[0], max(days[-1] - days[0], 1)
    px = lambda d: LEFT + ((d - first) / span * (WIDTH - LEFT - RIGHT) if len(points) > 1 else (WIDTH - LEFT - RIGHT) / 2)
    xs = [px(d) for d in days]
    edges = [LEFT] + [(a + b) / 2 for a, b in zip(xs, xs[1:])] + [WIDTH - RIGHT]
    labels = [(px(d), labelled(date.fromordinal(d), span)) for d in range(first, days[-1] + 1)]

    top = TITLE
    base = top + PANEL
    height = TITLE + PANEL + AXIS
    max_total = max(int(p["total"]) for p in points)
    step, peak = scale(max_total)
    py = lambda v: base - v / peak * PANEL

    out = [
        f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {WIDTH} {height}" role="img" '
        'aria-label="Decompiled RAW and lifted game functions over time" '
        f'font-family="sans-serif" font-size="12" fill="{TEXT}">',
        "<style>.hit{fill:#fff;fill-opacity:0}.hit:hover{fill-opacity:0.06}</style>",
        f'<rect width="{WIDTH}" height="{height}" rx="6" fill="{BACKGROUND}"/>',
        f'<text x="{LEFT}" y="{top - 12}" font-size="13" font-weight="bold">LF2-decomp Coverage Over Time (of {max_total} game functions)</text>',
    ]
    for tick in range(0, peak + 1, step):
        out.append(
            f'<line x1="{LEFT}" x2="{WIDTH - RIGHT}" y1="{py(tick):.1f}" y2="{py(tick):.1f}" stroke="{GRID}"/>'
            f'<text x="{LEFT - 6}" y="{py(tick) + 4:.1f}" text-anchor="end" fill="{MUTED}">{tick:,}</text>'
        )
    for x, label in labels:
        if label:
            out.append(f'<line x1="{x:.1f}" x2="{x:.1f}" y1="{top}" y2="{base}" stroke="{GRID}" stroke-width="0.5"/>')

    line_pts = lambda coords: " ".join(f"{x:.1f},{y:.1f}" for x, y in coords)
    total_coords = [(x, py(int(p["total"]))) for x, p in zip(xs, points)]
    raw_coords = [(x, py(int(p["raw"]))) for x, p in zip(xs, points)]
    lift_coords = [(x, py(int(p["lifted"]))) for x, p in zip(xs, points)]

    out.append(f'<polyline points="{line_pts(total_coords)}" fill="none" stroke="{MUTED}" stroke-width="1.5" stroke-dasharray="6 4"/>')
    if len(points) > 1:
        out.append(f'<polygon points="{xs[0]:.1f},{base} {line_pts(raw_coords)} {xs[-1]:.1f},{base}" fill="{DECOMPILED_COLOR}" opacity="0.10"/>')
        out.append(f'<polygon points="{xs[0]:.1f},{base} {line_pts(lift_coords)} {xs[-1]:.1f},{base}" fill="{LIFTED_COLOR}" opacity="0.18"/>')
        out.append(f'<polyline points="{line_pts(raw_coords)}" fill="none" stroke="{DECOMPILED_COLOR}" stroke-width="2"/>')
        out.append(f'<polyline points="{line_pts(lift_coords)}" fill="none" stroke="{LIFTED_COLOR}" stroke-width="2"/>')

    if len(points) <= MAX_DOTS:
        out += [f'<circle cx="{x:.1f}" cy="{y:.1f}" r="3.5" fill="{DECOMPILED_COLOR}"/>' for x, y in raw_coords]
        out += [f'<circle cx="{x:.1f}" cy="{y:.1f}" r="3.5" fill="{LIFTED_COLOR}"/>' for x, y in lift_coords]

    last = points[-1]
    ty, ry, ly = spread([total_coords[-1][1], raw_coords[-1][1], lift_coords[-1][1]])
    out.append(f'<text x="{WIDTH - RIGHT + 8}" y="{ty + 4:.1f}" fill="{MUTED}">Target {last["total"]:,}</text>')
    out.append(
        f'<text x="{WIDTH - RIGHT + 8}" y="{ry + 4:.1f}" fill="{TEXT}" font-weight="bold">'
        f'<tspan fill="{DECOMPILED_COLOR}">-</tspan> Decompiled {last["raw"]:,} ({last["decompiled_percent"]}%)</text>'
    )
    out.append(
        f'<text x="{WIDTH - RIGHT + 8}" y="{ly + 4:.1f}" fill="{TEXT}" font-weight="bold">'
        f'<tspan fill="{LIFTED_COLOR}">-</tspan> Lifted {last["lifted"]:,} ({last["lifted_percent"]}%)</text>'
    )

    for (left_e, right_e), p in zip(zip(edges, edges[1:]), points):
        out.append(
            f'<rect class="hit" x="{left_e:.1f}" y="{top}" width="{right_e - left_e:.1f}" height="{PANEL}">'
            f'<title>{p["date"]}\nDecompiled RAW: {p["raw"]}/{p["total"]} ({p["decompiled_percent"]}%)\n'
            f'Lifted: {p["lifted"]}/{p["total"]} ({p["lifted_percent"]}%)</title></rect>'
        )

    axis_y = height - AXIS + 18
    out += [f'<text class="x" x="{x:.1f}" y="{axis_y}" text-anchor="middle" font-size="11" fill="{MUTED}">{escape(label)}</text>' for x, label in labels if label]
    out.append(SVG_STYLE)
    out.append("</svg>")
    return "\n".join(out)


def page(points: list[dict[str, object]], ref: str = "HEAD") -> str:
    raw_deltas = ["n/a"] + [f'{int(p["raw"]) - int(q["raw"]):+,}' for q, p in zip(points, points[1:])]
    lift_deltas = ["n/a"] + [f'{int(p["lifted"]) - int(q["lifted"]):+,}' for q, p in zip(points, points[1:])]
    rows = "\n".join(
        f'<tr><td>{p["date"]}</td><td><code>{str(p["commit"])[:7]}</code></td>'
        f'<td>{p["raw"]}/{p["total"]}</td><td>{p["decompiled_percent"]}%</td><td>{rd}</td>'
        f'<td>{p["lifted"]}/{p["total"]}</td><td>{p["lifted_percent"]}%</td><td>{ld}</td></tr>'
        for p, rd, ld in reversed(list(zip(points, raw_deltas, lift_deltas)))
    )
    return "\n".join([
        "<!DOCTYPE html>",
        '<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1">',
        '<meta name="color-scheme" content="light dark"><title>LF2-decomp Progress History</title>',
        "<style>:root{color-scheme:light dark}" + THEME +
        "body{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',sans-serif;max-width:1000px;margin:auto;padding:24px;"
        "background:var(--history-background);color:var(--history-text);line-height:1.5}svg{max-width:100%;height:auto}"
        "a{color:var(--history-link)}a:visited{color:var(--history-visited)}"
        "table{border-collapse:collapse;width:100%;margin-top:16px}th,td{border:1px solid var(--history-grid);padding:6px 10px}"
        "td+td,th+th{text-align:right}td:nth-child(2),th:nth-child(2){text-align:left}</style>",
        '</head><body class="history-theme">',
        "<h1>LF2-decomp Progress History</h1>",
        chart(points),
        f'<p>One measurement per UTC day on <code>{escape(ref)}</code> (latest commit per day). '
        'Pre-inventory commits measure <code>decompiled/RAW/</code> against the 181 game-code entries. '
        '<a href="history.json">history.json</a> | <a href="progress.html">Back to current progress</a></p>',
        "<table><thead><tr><th>Date</th><th>Commit</th><th>RAW</th><th>RAW %</th><th>RAW Delta</th>"
        "<th>Lifted</th><th>Lifted %</th><th>Lifted Delta</th></tr></thead><tbody>",
        rows,
        "</tbody></table></body></html>\n",
    ])


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description="Generate LF2-decomp coverage history artifacts")
    parser.add_argument("output", type=Path)
    parser.add_argument("--ref", default="HEAD", help="Git ref whose first-parent history is measured")
    parser.add_argument("--since", type=utc_day, help="first UTC day to measure (YYYY-MM-DD)")
    parser.add_argument("--until", type=utc_day, help="last UTC day to measure (YYYY-MM-DD)")
    args = parser.parse_args(argv)

    if args.since and args.until and args.since > args.until:
        parser.error("--since must not be later than --until")
    try:
        points = collect(args.ref, args.since, args.until)
    except (OSError, ValueError) as err:
        parser.error(str(err))
    if not points:
        parser.error("no commit with a measurable tree")

    args.output.mkdir(parents=True, exist_ok=True)
    (args.output / "history.json").write_text(json.dumps(points, indent=2) + "\n", encoding="utf-8", newline="\n")
    (args.output / "history.svg").write_text(chart(points) + "\n", encoding="utf-8", newline="\n")
    (args.output / "history.html").write_text(page(points, args.ref), encoding="utf-8", newline="\n")
    print(f"{len(points)} days, {points[0]['date']} .. {points[-1]['date']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
