#!/usr/bin/env python3
"""
Embedded UI Asset Generator
Bakes all frontend UI bitmaps (menu backgrounds, clips, dialogs, cursors, countdowns)
directly into C++ source code matching the authentic Win32 embedded PE resource architecture.
"""

import os
import sys

def main():
    repo_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    ui_dir = os.path.join(repo_root, "data", "ui")
    out_cpp = os.path.join(repo_root, "src", "graphics", "embedded_ui.cpp")

    if not os.path.isdir(ui_dir):
        print(f"Error: UI directory not found: {ui_dir}", file=sys.stderr)
        sys.exit(1)

    files = sorted(os.listdir(ui_dir))
    table_entries = []

    with open(out_cpp, "w", encoding="utf-8") as f:
        f.write('// Auto-generated Little Fighter 2 Embedded UI Resources\n')
        f.write('// Authentic PE Resource parity: UI assets compiled directly into executable binary\n\n')
        f.write('#include "embedded_ui.h"\n')
        f.write('#include <cstring>\n')
        f.write('#include <cctype>\n')
        f.write('#include <algorithm>\n\n')
        f.write('namespace lf2 {\n\n')

        for filename in files:
            if not (filename.lower().endswith(".bmp") or filename.lower().endswith(".jpg")):
                continue

            filepath = os.path.join(ui_dir, filename)
            with open(filepath, "rb") as bf:
                data = bf.read()

            var_name = "asset_" + filename.replace(".", "_").replace("-", "_")
            f.write(f'// {filename} ({len(data)} bytes)\n')
            f.write(f'static const char {var_name}[] =\n')

            # Write chunks of 80 bytes per line in escaped hex format
            chunk_size = 80
            for i in range(0, len(data), chunk_size):
                chunk = data[i:i+chunk_size]
                hex_str = "".join(f"\\x{b:02x}" for b in chunk)
                f.write(f'"{hex_str}"\n')
            f.write(';\n\n')

            table_entries.append((filename, var_name, len(data)))

        f.write('static const embedded_asset_t EMBEDDED_ASSETS[] = {\n')
        for filename, var_name, size in table_entries:
            f.write(f'    {{ "{filename}", reinterpret_cast<const uint8_t*>({var_name}), {size} }},\n')
        f.write('};\n\n')

        f.write('static const size_t NUM_EMBEDDED_ASSETS = sizeof(EMBEDDED_ASSETS) / sizeof(EMBEDDED_ASSETS[0]);\n\n')

        f.write('const embedded_asset_t* find_embedded_ui_asset(const std::string& name) {\n')
        f.write('    if (name.empty()) return nullptr;\n\n')
        f.write('    // Normalize path: extract filename\n')
        f.write('    std::string base = name;\n')
        f.write('    for (char& c : base) {\n')
        f.write('        if (c == \'\\\\\') c = \'/\';\n')
        f.write('    }\n')
        f.write('    size_t slash = base.rfind(\'/\');\n')
        f.write('    if (slash != std::string::npos) {\n')
        f.write('        base = base.substr(slash + 1);\n')
        f.write('    }\n\n')
        f.write('    // Convert lookup name to lower-case\n')
        f.write('    std::string lower_base = base;\n')
        f.write('    for (char& c : lower_base) {\n')
        f.write('        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));\n')
        f.write('    }\n\n')
        f.write('    for (size_t i = 0; i < NUM_EMBEDDED_ASSETS; ++i) {\n')
        f.write('        const auto& a = EMBEDDED_ASSETS[i];\n')
        f.write('        std::string lower_name = a.name;\n')
        f.write('        for (char& c : lower_name) {\n')
        f.write('            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));\n')
        f.write('        }\n')
        f.write('        if (lower_base == lower_name) {\n')
        f.write('            return &a;\n')
        f.write('        }\n')
        f.write('        if (lower_base + ".bmp" == lower_name) {\n')
        f.write('            return &a;\n')
        f.write('        }\n')
        f.write('    }\n')
        f.write('    return nullptr;\n')
        f.write('}\n\n')
        f.write('} // namespace lf2\n')

    print(f"[LF2 EMBED] Successfully baked {len(table_entries)} UI assets into {out_cpp}")

if __name__ == "__main__":
    main()

