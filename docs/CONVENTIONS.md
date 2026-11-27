# Engineering & Annotation Conventions

This document defines the canonical source-annotation grammar, inventory synchronization rules, and verification discipline for `LF2-decomp`.

---

## 1. Source Annotation Grammar

Every decompiled or lifted routine must carry a single-line machine-readable comment immediately above its primary definition (or immediately above a `case` label when multiple x86 entry points map into a single switch dispatcher):

```c
// <MARKER>: LF2 <0x004xxxxx> [EXTRA]
```

Canonical regular expression enforced by [`tools/progress.py`](../tools/progress.py):

```text
^// (?P<kind>FUNCTION|STUB|LIFTED|VERIFIED|PARTIAL|COMPAT|GLOBAL|STRING|LIBRARY): (?P<module>LF2) (?P<addr>0x004[0-9a-f]{5})(?: (?P<extra>[A-Za-z0-9_.,:/ -]+))?$
```

Formatting rules:
- Use lowercase 8-digit hexadecimal addresses (`0x00403270`, never `0x403270` or `0x0040327A`).
- Keep exact single spaces (`// MARKER: LF2 0x004xxxxx`).
- In `decompiled/Compilable/`, top-level annotations start at column 0.

---

## 2. Marker Semantics

| Marker | Allowed Track | Meaning |
| :--- | :--- | :--- |
| `FUNCTION` | `decompiled/Compilable/` | Complete compilable C translation of the original x86 routine at `0x004xxxxx`. |
| `LIBRARY` | `decompiled/Compilable/` | Third-party library wrapper (e.g., statically linked `zlib 1.1.4` wrappers `0x0043f4b0`, `0x0043f4d0`). |
| `STUB` | `decompiled/Compilable/` or `lifted/src/` | Placeholder, no-op, or intentionally stubbed platform/ad routine. |
| `PARTIAL` | `decompiled/Compilable/` or `lifted/src/` | Partial or consolidated implementation awaiting full 1:1 parity reconciliation. |
| `LIFTED` | `lifted/src/` | Ported to modern C++20 / SDL2, awaiting dedicated differential parity tests. |
| `VERIFIED` | `lifted/src/` | Lifted to C++20 / SDL2 and directly exercised by automated parity tests in `lifted/tests/`. |
| `COMPAT` | `decompiled/Compilable/` or `lifted/src/` | Interior block alias or legacy compatibility wrapper not counted as a separate entry point. |
| `GLOBAL` | `decompiled/Compilable/` or `lifted/src/` | Static global data address annotation (does not alter function totals). |
| `STRING` | `decompiled/Compilable/` or `lifted/src/` | Static string literal address annotation (does not alter function totals). |

### Uniqueness & Multi-Function Mapping
- Annotate each `0x004xxxxx` entry point **once** per track (`decompiled/Compilable/` vs `lifted/src/`). Where a `Compilable` file contains both a descriptive `lf2_*` implementation and a forwarding `FUN_004xxxxx` wrapper, place `// FUNCTION: LF2 0x004xxxxx` once above the primary implementation.
- Do not promote a routine to `VERIFIED` unless an automated test in [`lifted/tests/`](../lifted/tests/) exercises its behavior against the extracted binary logic.

---

## 3. Single Source of Truth (`decompiled/functions.csv`)

[`decompiled/functions.csv`](../decompiled/functions.csv) is the canonical inventory for all 244 verified `.text` entry points in `lf2.exe`:
- **Static metadata** (`address`, `size_bytes`, `ghidra_name`, `name`, `subsystem`, `category`, `priority`, `notes`) is authored in `decompiled/functions.csv`.
- **Live pipeline state** (`status`) and file paths (`raw_file`, `compilable_file`, `lifted_file`) are derived deterministically from disk (`decompiled/RAW/` + `// <MARKER>: LF2 0x004xxxxx` comments).
- `decompiled/RAW/` is immutable forensic evidence: never edit `.c` files inside `decompiled/RAW/`.
- After adding or modifying annotations or RAW exports, synchronize the CSV, badges, coverage map, and `README.md` table:

```bash
python tools/progress.py --update-readme
```

---

## 4. Verification Discipline

All four checks must pass with zero new compiler warnings before any decompilation or lifting change is complete:

```bash
python decompiled/verify_raw_entries.py
python tools/progress.py --check --check-readme
mingw32-make -C decompiled/Compilable test
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy mingw32-make -C lifted test
```
