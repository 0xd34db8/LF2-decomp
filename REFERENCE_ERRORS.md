# Discrepancies and Inaccuracies in Prior Reference Decompilations

This document catalogues technical inaccuracies, miscalculated struct offsets, and architectural assumptions identified in prior open-source LF2 reverse engineering attempts (specifically [`xsoameix/openlf2`](https://github.com/xsoameix/openlf2) and [`xsoameix/lf2`](https://github.com/xsoameix/lf2)) when evaluated against the ground-truth disassembly and decompiler output of `lf2.exe` extracted via Ghidra.

---

## 1. `file_t::attacking_itrs` Starting Offset Mismatch

### In `openlf2/include/file.h`:
```c
typedef struct file {
    uint32_t _padding1[41];
    uint32_t _unknown1;            // 0xA4
    uint32_t _padding2;
    uint32_t _unknown2;            // 0xAC
    uint32_t _padding3[5];
    itr_t    attaking_itrs[4];     // Assumed at 0xC4
    ...
} file_t;
```

### Binary Ground Truth (`lf2.exe` @ `0x40ef70`):
In `func_0040ef70` (the `.dat` file loader), the parsing loop for `<weapon_strength_list>` reads:
```c
puVar18 = (undefined4 *)(in_ECX + 0xb0);
for (iVar15 = 200; iVar15 != 0; iVar15 = iVar15 + -1) {
    *puVar18 = 0;
    puVar18 = puVar18 + 1;
}
...
if (bVar19) { // dvx:
    iVar15 = (int)local_4e0 * 0x50 + 0xc4 + in_ECX;
}
```
- **The Bug:** `openlf2` observed the address `local_4e0 * 0x50 + 0xC4` in the decompiler and mistakenly concluded that `attacking_itrs[0]` starts at `0xC4`.
- **The Reality:** Offset `0x14` within an `itr_t` struct is `dvx` (`kind: 0x00`, `x: 0x04`, `y: 0x08`, `w: 0x0C`, `h: 0x10`, `dvx: 0x14`).
- `0x0B0 + 0x14 = 0x0C4`.
- The `attacking_itrs[4]` array actually begins at offset **`0x0B0`**, spanning `4 * 0x50 = 0x140` bytes (from `0x0B0` to `0x1F0`).

---

## 2. `file_t` Total Allocation Size and Frame Array Bounds

### In `openlf2/include/file.h`:
```c
    uint32_t _padding5[42];
    frame_t  frames[400];          // 0x7A4
```
`openlf2` placed `frames[400]` as the final member of `file_t` and calculated the total struct size as `0x25364` or undefined.

### Binary Ground Truth (`lf2.exe` @ `0x43e9a0` & `0x40ef70`):
1. In `func_0043e9a0` (the game mode manager), `file_t` instances are dynamically allocated via:
   ```c
   local_140 = operator_new(0x25360);
   ```
   The exact memory size requested from the heap is **`0x25360`** (152,416 bytes), **not** `0x25364`.
2. Calculating the end of the frame array:
   - Frame start offset: `0x7A4` (1,956).
   - Frame size: `0x178` (376 bytes).
   - `400 * 0x178 = 0x24B80` (150,400 bytes).
   - Frame end offset: `0x7A4 + 0x24B80 = 0x25324`.
3. At offset `0x25324`, `func_0040ef70` initializes:
   ```c
   *(undefined4 *)(in_ECX + 0x25324) = 0x656e6f6e; // "none"
   *(undefined1 *)(in_ECX + 0x25328) = 0;
   ...
   if (bVar19) { // "name:"
       fscanf(local_4e8, "%s", in_ECX + 0x25324);
   }
   ```
4. The remaining `60` bytes (`0x25360 - 0x25324 = 0x3C`) constitute the `name` string buffer. `openlf2` completely missed this field at the tail of `file_t`.

---

## 3. DirectDraw Surface Managers & String Buffer Offsets

### In `openlf2/include/file.h`:
`openlf2` did not identify the DirectDraw surface manager pointers, representing offsets between `0x6F8` and `0x7A4` as arbitrary dword padding arrays (`_padding5[42]`).

### Binary Ground Truth (`lf2.exe` @ `0x40ef70`):
By tracing `func_0040ef70`, the exact members are:
- `0x6F4`: `uint32_t id`
- `0x6F8`: `uint32_t type`
- `0x6FC`: `void* head_bmp_mgr` (DirectDraw surface wrapper for head icon)
- `0x700`: `char head[40]` (head image filename, ends at `0x728`)
- `0x728`: `void* small_bmp_mgr` (DirectDraw surface wrapper for small icon)
- `0x72C`: `char small[36]` (small image filename, ends at `0x750`)
- `0x750`: `void* bmp_mgrs[10]` (up to 10 sprite sheet surfaces, spans `0x750`–`0x778`)
- `0x778`: `void* mirror_bmp_mgrs[10]` (up to 10 horizontally flipped surfaces, spans `0x778`–`0x7A0`)
- `0x7A0`: `uint32_t _pad` (4 bytes padding)
- `0x7A4`: `frame_t frames[400]`

---

## 4. Architectural Trap: Vtables vs. Monolithic Entity Instances

### Prior Assumptions in Multiple Clones:
Several community rebuilds (e.g., `OriVered/Little-Fighter-2---Rebuild`, `OpenLF2/OpenLF2`) introduced complex OOP class hierarchies (`class Character : public Entity`, `class Weapon : public Item`, `class Projectile : public Entity`) with virtual dispatch tables (`vptr`).

### Binary Ground Truth:
In `lf2.exe`, there are **no virtual function tables** for entity dispatch.
Every entity on the battlefield—whether John, a stick, a fireball, or a criminal hostage—is an instance of the exact same 880-byte `object_t` struct (`0x370` bytes).
Behavioral branching is handled purely by querying `object->file->type` (`TYPE_CHARACTER`, `TYPE_WEAPON`, `TYPE_PROJECTILE`, etc.) inside flat procedural functions (`does_attack_success`, `attack_process`, `teleport`).

---

## 5. 64-Bit Pointer Truncation Pitfall

### The Problem in Naive Lifts:
Because LF2 is a 32-bit executable where pointers are 4 bytes, previous modernizing attempts that forced struct fields to be 4-byte integers (`uint32_t raw_ptr`) suffer immediate segmentation faults when compiled as native 64-bit executables. On 64-bit operating systems, stack and heap allocations routinely exceed `0xFFFFFFFF` (4 GB), causing upper address bits to be silently truncated when cast through a 32-bit integer.

### Our Solution:
Our lift uses native C++ pointers (`T*`), maintaining full 64-bit compatibility:
- In `object_t`, `file_t* file` is placed at offset `0x368`. On 64-bit, an 8-byte pointer spans `0x368`–`0x370`, absorbing the original 4-byte padding and preserving the exact `sizeof(object_t) == 0x370` size!
- In `frame_t`, `itrs` and `bdys` pointers expand to 8 bytes on 64-bit, absorbing 8 bytes of adjacent unused dwords in `_unknown5`, preserving `sizeof(frame_t) == 0x178` and keeping `name` at `0x15C` and `sound` at `0x170`.
- All fixed struct offsets and gameplay math remain 100% byte-accurate on both 32-bit and 64-bit compilation targets.

