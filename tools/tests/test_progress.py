import csv
import io
import json
import shutil
import sys
import tempfile
import unittest
import xml.etree.ElementTree as ET
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import progress
import progress_history


def make_mini_repo(tmp: Path) -> Path:
    """Create a minimal self-contained repository fixture for unit tests."""
    (tmp / "decompiled" / "RAW" / "gameplay").mkdir(parents=True)
    (tmp / "decompiled" / "Compilable" / "gameplay").mkdir(parents=True)
    (tmp / "lifted" / "src" / "gameplay").mkdir(parents=True)
    (tmp / "assets" / "progress").mkdir(parents=True)

    (tmp / "decompiled" / "verify_raw_entries.py").write_text(
        "VERIFIED_ENTRIES = {'0x403270', '0x4061a0', '0x4061d0', '0x43f4b0'}\n",
        encoding="utf-8",
    )
    (tmp / "decompiled" / "RAW" / "gameplay" / "func_00403270_teleport.c").write_text(
        "void FUN_00403270(void) {}\n", encoding="utf-8"
    )
    (tmp / "decompiled" / "Compilable" / "gameplay" / "teleport.c").write_text(
        "// FUNCTION: LF2 0x00403270\nvoid lf2_teleport(void) {}\n", encoding="utf-8"
    )
    (tmp / "lifted" / "src" / "gameplay" / "teleport.cpp").write_text(
        "// VERIFIED: LF2 0x00403270\nvoid teleport() {}\n", encoding="utf-8"
    )
    (tmp / "decompiled" / "Compilable" / "gameplay" / "object_init.c").write_text(
        "// FUNCTION: LF2 0x004061a0\nint FUN_004061a0(void) { return 0; }\n", encoding="utf-8"
    )
    (tmp / "lifted" / "src" / "gameplay" / "entity.cpp").write_text(
        "// STUB: LF2 0x004061d0\nvoid object_init_stub() {}\n", encoding="utf-8"
    )

    rows = [
        ["0x00403270", "120", "FUN_00403270", "teleport", "gameplay", "game", "P0", "verified",
         "decompiled/RAW/gameplay/func_00403270_teleport.c",
         "decompiled/Compilable/gameplay/teleport.c",
         "lifted/src/gameplay/teleport.cpp", "Teleport"],
        ["0x004061a0", "40", "FUN_004061a0", "is_between", "gameplay", "game", "P0", "compilable",
         "", "decompiled/Compilable/gameplay/object_init.c", "", "Betweenness"],
        ["0x004061d0", "80", "FUN_004061d0", "object_init", "gameplay", "game", "P1", "stub",
         "", "", "lifted/src/gameplay/entity.cpp", "Entity init"],
        ["0x0043f4b0", "0", "FUN_0043f4b0", "zlib_compress", "vendor", "vendor_zlib", "-", "excluded",
         "", "", "", "zlib"],
    ]
    with (tmp / "decompiled" / "functions.csv").open("w", encoding="utf-8", newline="\n") as f:
        w = csv.writer(f, lineterminator="\n")
        w.writerow(progress.CSV_COLUMNS)
        w.writerows(rows)

    (tmp / "README.md").write_text(
        "# Title\n\n<!-- PROGRESS:START -->\nold\n<!-- PROGRESS:END -->\n\nFooter\n",
        encoding="utf-8",
    )
    return tmp


class ProgressEngineTests(unittest.TestCase):
    def test_live_repo_check_passes(self):
        self.assertEqual(progress.main(["--check"]), 0)

    def test_sync_and_check_detect_csv_drift(self):
        with tempfile.TemporaryDirectory() as d:
            repo = make_mini_repo(Path(d))
            self.assertEqual(progress.main(["--root", str(repo), "--check"]), 0)

            # Introduce drift in CSV status
            csv_path = repo / "decompiled" / "functions.csv"
            csv_path.write_text(csv_path.read_text(encoding="utf-8").replace(",verified,", ",raw,"), encoding="utf-8")
            stderr = io.StringIO()
            with patch("sys.stderr", stderr):
                self.assertEqual(progress.main(["--root", str(repo), "--check"]), 1)
            self.assertIn("functions.csv drift", stderr.getvalue())

            # --sync repairs drift
            self.assertEqual(progress.main(["--root", str(repo), "--sync"]), 0)
            self.assertEqual(progress.main(["--root", str(repo), "--check"]), 0)

    def test_marker_linter_rejects_malformed_unknown_and_duplicate_markers(self):
        bad_cases = [
            "// function: LF2 0x004061d0\n",
            "// FUNCTION: LF2 0x4061d0\n",
            "// FUNCTION: LF2 0x004061D0\n",
            "// TEMPLATE: LF2 0x004061d0\n",
            "// FUNCTION: LF2 0x00409999\n",
            "// LIFTED: LF2 0x004061d0\n",
        ]
        for snippet in bad_cases:
            with self.subTest(snippet=snippet), tempfile.TemporaryDirectory() as d:
                repo = make_mini_repo(Path(d))
                target = repo / "decompiled" / "Compilable" / "gameplay" / "bad.c"
                target.write_text(snippet + "void f(void) {}\n", encoding="utf-8")
                stderr = io.StringIO()
                with patch("sys.stderr", stderr):
                    rc = progress.main(["--root", str(repo), "--check"])
                self.assertEqual(rc, 1)

        # Duplicate primary marker in same track fails
        with tempfile.TemporaryDirectory() as d:
            repo = make_mini_repo(Path(d))
            dup = repo / "decompiled" / "Compilable" / "gameplay" / "dup.c"
            dup.write_text("// FUNCTION: LF2 0x00403270\nvoid dup(void) {}\n", encoding="utf-8")
            stderr = io.StringIO()
            with patch("sys.stderr", stderr):
                self.assertEqual(progress.main(["--root", str(repo), "--check"]), 1)

        # COMPAT for non-inventory interior address is accepted
        with tempfile.TemporaryDirectory() as d:
            repo = make_mini_repo(Path(d))
            compat = repo / "decompiled" / "Compilable" / "gameplay" / "compat.c"
            compat.write_text("// COMPAT: LF2 0x004068b0\nvoid compat(void) {}\n", encoding="utf-8")
            self.assertEqual(progress.main(["--root", str(repo), "--check"]), 0)

    def test_byte_weighted_reporting_and_svg_xml_validity(self):
        with tempfile.TemporaryDirectory() as d:
            repo = make_mini_repo(Path(d))
            out = Path(d) / "site"
            self.assertEqual(progress.main(["--root", str(repo), str(out)]), 0)
            data = json.loads((out / "progress.json").read_text(encoding="utf-8"))
            self.assertTrue(data["totals"]["byte_coverage_available"])
            self.assertEqual(data["totals"]["total_bytes"], 240)
            self.assertEqual(data["totals"]["lifted_bytes"], 120)

            for svg_name in ("progress.svg", "badge-decompiled.svg", "badge-lifted.svg", "badge-tests.svg"):
                svg_text = (out / svg_name).read_text(encoding="utf-8")
                ET.fromstring(svg_text)

    def test_next_filtering_and_ordering(self):
        with tempfile.TemporaryDirectory() as d:
            repo = make_mini_repo(Path(d))
            stdout = io.StringIO()
            with patch("sys.stdout", stdout):
                self.assertEqual(progress.main(["--root", str(repo), "--next", "5"]), 0)
            out = stdout.getvalue()
            self.assertIn("0x004061a0", out)
            self.assertIn("0x004061d0", out)
            self.assertNotIn("0x00403270", out)
            self.assertLess(out.index("0x004061a0"), out.index("0x004061d0"))

    def test_compare_validation_and_markdown(self):
        with tempfile.TemporaryDirectory() as d:
            base = Path(d) / "base.json"
            head = Path(d) / "head.json"
            base_snap = {
                "subsystems": {
                    "done": 0, "total": 2, "percent": 0.0,
                    "groups": [{"name": "gameplay", "done": 0, "todo": 2, "total": 2, "raw": 1, "compilable": 1, "verified": 0, "percent": 0.0,
                                "done_names": [], "todo_names": ["0x00403270 teleport", "0x004061a0 is_between"], "verified_names": []}],
                }
            }
            head_snap = {
                "subsystems": {
                    "done": 1, "total": 2, "percent": 50.0,
                    "groups": [{"name": "gameplay", "done": 1, "todo": 1, "total": 2, "raw": 1, "compilable": 1, "verified": 1, "percent": 50.0,
                                "done_names": ["0x00403270 teleport"], "todo_names": ["0x004061a0 is_between"], "verified_names": ["0x00403270 teleport"]}],
                }
            }
            base.write_text(json.dumps(base_snap), encoding="utf-8")
            head.write_text(json.dumps(head_snap), encoding="utf-8")
            stdout = io.StringIO()
            with patch("sys.stdout", stdout):
                self.assertEqual(progress.main(["--compare", str(base), str(head)]), 0)
            md = stdout.getvalue()
            self.assertIn("LF2 Binary Lift Coverage", md)
            self.assertIn("0x00403270 teleport", md)
            self.assertIn("Changed Subsystems", md)

            # Invalid snapshot raises exit code 2
            base.write_text(json.dumps({"subsystems": {"done": 5, "total": 2, "percent": 0, "groups": []}}), encoding="utf-8")
            stderr = io.StringIO()
            with patch("sys.stderr", stderr), self.assertRaises(SystemExit) as ctx:
                progress.main(["--compare", str(base), str(head)])
            self.assertEqual(ctx.exception.code, 2)

    def test_update_readme_is_idempotent_and_checked(self):
        with tempfile.TemporaryDirectory() as d:
            repo = make_mini_repo(Path(d))
            self.assertEqual(progress.main(["--root", str(repo), "--update-readme"]), 0)
            first = (repo / "README.md").read_text(encoding="utf-8")
            self.assertIn("# Title", first)
            self.assertIn("Footer", first)
            self.assertIn("assets/progress/progress.svg", first)
            self.assertEqual(progress.main(["--root", str(repo), "--check", "--check-readme"]), 0)

            # Second run makes zero changes
            self.assertEqual(progress.main(["--root", str(repo), "--update-readme"]), 0)
            self.assertEqual((repo / "README.md").read_text(encoding="utf-8"), first)

    def test_history_chart_valid_xml_for_single_and_multi_points(self):
        pts = [
            {"date": "2026-11-25", "commit": "a" * 40, "total": 181, "raw": 100, "compilable": 50, "lifted": 40, "verified": 30, "decompiled_percent": 55.2, "lifted_percent": 22.1},
            {"date": "2026-11-26", "commit": "b" * 40, "total": 181, "raw": 139, "compilable": 123, "lifted": 112, "verified": 92, "decompiled_percent": 76.8, "lifted_percent": 61.9},
        ]
        ET.fromstring(progress_history.chart(pts[:1]))
        ET.fromstring(progress_history.chart(pts))


if __name__ == "__main__":
    unittest.main()
