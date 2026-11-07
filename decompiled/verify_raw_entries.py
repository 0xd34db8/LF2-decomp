#!/usr/bin/env python3
"""
LF2 RAW Archive Integrity Verifier
Verifies that:
1. Every .c source file in decompiled/RAW/ contains a valid hex entrypoint in its filename.
2. Every filename entrypoint strictly matches a genuine function entry discovered by Ghidra in lf2.exe.
3. No two files represent the same procedure entry.
4. Each file is non-empty and contains authentic decompiler output or metadata.
"""

import os
import re
import sys

# Complete inventory of verified function entry points in lf2.exe (.text section)
VERIFIED_ENTRIES = set(['0x401000', '0x401090', '0x401110', '0x4011d0', '0x401250', '0x401290', '0x401300', '0x4013d0', '0x4014e0', '0x401970', '0x4019b0', '0x401a30', '0x401a80', '0x401ae0', '0x401b00', '0x401bf0', '0x401c90', '0x401d30', '0x401da0', '0x401e90', '0x401f30', '0x402000', '0x402020', '0x402100', '0x402130', '0x4025b0', '0x4025d0', '0x402810', '0x4028a0', '0x402a60', '0x402ad0', '0x402b60', '0x402d70', '0x402ec0', '0x4031d0', '0x403270', '0x4034e0', '0x4034f0', '0x403a40', '0x4061a0', '0x4061d0', '0x4064d0', '0x406a20', '0x406ba0', '0x408cb0', '0x4094b0', '0x40bbf0', '0x40bd90', '0x40be70', '0x40bf30', '0x40bfb0', '0x40c030', '0x40c0e0', '0x40c160', '0x40c910', '0x40d0a0', '0x40d940', '0x40d960', '0x40de30', '0x40e170', '0x40e2d0', '0x40e450', '0x40e490', '0x40ef70', '0x4122f0', '0x412800', '0x4128f0', '0x4129e0', '0x412ac0', '0x412ba0', '0x412c90', '0x412d80', '0x412e60', '0x412f40', '0x413080', '0x4143d0', '0x414450', '0x4146b0', '0x4148a0', '0x414a30', '0x414b70', '0x415140', '0x415160', '0x4151d0', '0x416c70', '0x416ca0', '0x416cd0', '0x416dd0', '0x416df0', '0x416e10', '0x416e30', '0x416e60', '0x416eb0', '0x416f10', '0x416f60', '0x416fb0', '0x417090', '0x417170', '0x4171c0', '0x417200', '0x417400', '0x417f80', '0x4187b0', '0x418c30', '0x419380', '0x4196f0', '0x4197a0', '0x4198f0', '0x419a60', '0x419e40', '0x419e60', '0x41a050', '0x41a250', '0x41a5a0', '0x41ae60', '0x41b130', '0x41b390', '0x41b5d0', '0x41bc90', '0x422ac0', '0x422b00', '0x422f60', '0x423230', '0x423480', '0x4236d0', '0x4237e0', '0x423840', '0x423910', '0x423940', '0x423a70', '0x423b00', '0x4242e0', '0x4246b0', '0x429730', '0x42e100', '0x431b70', '0x431c70', '0x431d10', '0x432ab0', '0x434ab0', '0x436fc0', '0x437220', '0x437400', '0x437860', '0x4389a0', '0x438ad0', '0x438b40', '0x43a860', '0x43b3d0', '0x43bdd0', '0x43bec0', '0x43bf10', '0x43c0c0', '0x43c450', '0x43c4a0', '0x43c690', '0x43c710', '0x43c780', '0x43cc60', '0x43cf40', '0x43d230', '0x43d280', '0x43d2a0', '0x43d2c0', '0x43db40', '0x43dc50', '0x43dd60', '0x43df00', '0x43dfa0', '0x43e620', '0x43e860', '0x43e890', '0x43e8e0', '0x43e940', '0x43e9a0', '0x43ed10', '0x43ee50', '0x43ef50', '0x43ef70', '0x43f010', '0x43f310', '0x43f37e', '0x43f384', '0x43f38a', '0x43f390', '0x43f396', '0x43f39c', '0x43f3a2', '0x43f3a8', '0x43f3ae', '0x43f3b4', '0x43f3ba', '0x43f3c0', '0x43f3c6', '0x43f3cc', '0x43f3d2', '0x43f3d8', '0x43f3de', '0x43f3e4', '0x43f3ea', '0x43f3f0', '0x43f3f6', '0x43f400', '0x43f4b0', '0x43f4d0', '0x43f570', '0x43f5a0', '0x43f610', '0x43f8a0', '0x43f9c0', '0x4403a0', '0x440420', '0x440640', '0x440670', '0x4406c0', '0x440710', '0x440810', '0x440830', '0x440d60', '0x441de0', '0x441e60', '0x441ed0', '0x441f60', '0x4422a0', '0x442340', '0x442730', '0x442920', '0x4429a0', '0x442a40', '0x4435a0', '0x443cf0', '0x443d30', '0x444450', '0x444470', '0x444960', '0x444a10', '0x444ba0', '0x444bd0', '0x444d00', '0x4450a0', '0x4450a6', '0x4450ac'])

def main():
    repo_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    raw_dir = os.path.join(repo_root, 'decompiled', 'RAW')

    if not os.path.isdir(raw_dir):
        print(f"Error: RAW directory not found at {raw_dir}", file=sys.stderr)
        return 1

    raw_files = []
    for root, _, files in os.walk(raw_dir):
        for f in files:
            if f.endswith('.c'):
                raw_files.append((os.path.join(root, f), f))

    print(f"[*] Scanning {len(raw_files)} files in decompiled/RAW/...")

    errors = []
    seen_addresses = {}

    for full_path, filename in sorted(raw_files):
        # Extract hex address: func_00XXXXXX_...
        match = re.search(r'00([0-9a-fA-F]{6})', filename)
        if not match:
            errors.append(f"{filename}: Missing hex virtual address in filename")
            continue

        addr_str = '0x' + match.group(1).lower()
        if addr_str not in VERIFIED_ENTRIES:
            errors.append(f"{filename}: Address {addr_str} is NOT a verified Ghidra function entry!")

        if addr_str in seen_addresses:
            errors.append(f"{filename}: Duplicate entry point {addr_str} (already in {seen_addresses[addr_str]})")
        else:
            seen_addresses[addr_str] = filename

        # Check file non-empty and validate content integrity
        size = os.path.getsize(full_path)
        if size == 0:
            errors.append(f"{filename}: File is empty (0 bytes)")
            continue

        with open(full_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()

        # Strip C comments before checking for #include, extern, or FUN_00XXXXXX definition
        code_no_comments = re.sub(r'/\*.*?\*/', '', content, flags=re.DOTALL)
        code_no_comments = re.sub(r'//.*', '', code_no_comments)

        if re.search(r'^\s*#\s*include\b', code_no_comments, re.MULTILINE):
            errors.append(f"{filename}: Contains hand-edited #include directive (not pure Ghidra RAW output)")

        if re.search(r'\bextern\b', code_no_comments):
            errors.append(f"{filename}: Contains hand-edited extern declaration (not pure Ghidra RAW output)")

        expected_func = f"FUN_00{match.group(1).lower()}"
        if not re.search(rf'\b{expected_func}\s*\(', code_no_comments, re.IGNORECASE):
            errors.append(f"{filename}: Missing genuine Ghidra procedure definition '{expected_func}(...)'")

    if errors:
        print(f"[FAIL] Archive integrity verification FAILED with {len(errors)} error(s):", file=sys.stderr)
        for err in errors:
            print(f"  - {err}", file=sys.stderr)
        return 1

    print(f"[PASS] Archive integrity verified! All {len(raw_files)} files map 1:1 to genuine function entry points.")
    return 0

if __name__ == '__main__':
    sys.exit(main())
