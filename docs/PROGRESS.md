# Progress Counting & Reporting Rules

[`tools/progress.py`](../tools/progress.py) and [`tools/progress_history.py`](../tools/progress_history.py) compute binary reverse-engineering and source-lift coverage directly from [`decompiled/functions.csv`](../decompiled/functions.csv), [`decompiled/RAW/`](../decompiled/RAW/), and `// <MARKER>: LF2 0x004xxxxx` annotations in [`decompiled/Compilable/`](../decompiled/Compilable/) and [`lifted/src/`](../lifted/src/).

---

## 1. Game-Code Denominator & Exclusions

The verified `.text` entry inventory contains **242** addresses:
- **181 `game` functions** (`0x00401000`–`0x0043f310`, across 7 subsystems: `app`, `audio`, `core`, `data`, `gameplay`, `graphics`, `net`). Only `category=game` rows count toward completion percentages.
- **37 `vendor_zlib` functions** (`0x0043f400`–`0x00444d00`): statically linked `zlib 1.1.4` routines replaced by system `-lz` (`status=excluded`).
- **24 `import_thunk` entries** (`0x0043f37e`–`0x0043f3f6` and `0x004450a0`–`0x004450ac`): MSVC Win32 import jump thunks (`status=excluded`).

---

## 2. Status Derivation Hierarchy

For each `category=game` entry, [`tools/progress.py`](../tools/progress.py) derives its live `status` in descending precedence:

1. `verified`: `// VERIFIED: LF2 0x004xxxxx` in `lifted/src/`
2. `lifted`: `// LIFTED: LF2 0x004xxxxx` in `lifted/src/`
3. `partial`: `// PARTIAL: LF2 0x004xxxxx` in `lifted/src/` or `decompiled/Compilable/`
4. `compilable`: `// FUNCTION: LF2 0x004xxxxx` in `decompiled/Compilable/`
5. `raw`: matching Ghidra export in `decompiled/RAW/<subsystem>/func_004xxxxx_<name>.c`
6. `stub`: `// STUB: LF2 0x004xxxxx` in `lifted/src/` or `decompiled/Compilable/`
7. `unmapped`: in inventory without a RAW export or source annotation yet

### Headline Metrics
- **Decompiled (RAW):** count of `game` functions with a verified `decompiled/RAW/` export divided by `181`.
- **Compilable:** count of `game` functions with a `// FUNCTION: LF2 0x004xxxxx` translation in `decompiled/Compilable/`.
- **Lifted:** count of `game` functions with status `lifted` or `verified` divided by `181`.
- **Verified:** count of `game` functions with status `verified` divided by `181`.
- When `size_bytes` values are populated (> 0) in `decompiled/functions.csv`, `progress.json` also computes byte-weighted totals (`total_bytes`, `lifted_bytes`, `decompiled_bytes`).

---

## 3. Coverage Map (`progress.svg`) & History (`history.html`)

- **Treemap (`assets/progress/progress.svg`):** Squarified layout grouped by the 7 subsystems. Each cell represents one `game` function with an XML `<title>` tooltip (`0x004xxxxx — name (status)`):
  - `#3fb950` (Bright Green): `verified`
  - `#2ea043` (Green): `lifted`
  - `#d29922` (Amber): `compilable`, `raw`, or `partial`
  - `#6e7681` (Slate Gray): `unmapped` or `stub`
- **History (`tools/progress_history.py`):** Walks `--first-parent` commits, taking the latest commit per UTC day. Pre-overhaul commits lacking `decompiled/functions.csv` fall back to counting `decompiled/RAW/**/*.c` (excluding `0x0043f4b0` and `0x0043f4d0`) against the `181` game-code denominator.

---

## 4. Common Commands

```bash
# Validate inventory schema, RAW integrity, annotations, CSV sync, README, and SVGs
python tools/progress.py --check --check-readme

# Synchronize functions.csv, regenerate assets/progress/*.svg, and update README.md
python tools/progress.py --update-readme

# Find the top 10 highest-priority remaining targets (optionally filtered)
python tools/progress.py --next 10
python tools/progress.py --next 15 --subsystem net --stage lifted

# Run progress tooling unit tests
python -m unittest discover -s tools/tests -v

# Build full HTML/SVG/JSON site locally into a temporary directory
python tools/progress.py _site && python tools/progress_history.py _site
```
