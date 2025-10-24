# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

This is a ZMK firmware configuration repository for split mechanical keyboards (Corne, Sofle, Lily58, and SplitKB Aurora Sofle). It supports wireless operation with nice!nano v2, puchi_ble_v1, and Seeeduino XIAO BLE controllers. The repository includes advanced features like dongle support, ZMK Studio integration, and multiple display options.

## Build Commands

### Building Firmware with Docker

The repository uses Docker-based builds via Make. Docker must be installed.

**Initialize codebase (first time setup):**
```bash
make codebase_urob          # Clone and initialize urob's ZMK fork
make codebase_default       # Clone and initialize default ZMK
```

**Build firmware for specific keyboards:**
```bash
make corne_urob             # Build all Corne variants with urob's ZMK
make only_nice_corne_left_view_urob          # Build specific variant
make only_puchi_corne_right_view_urob        # Build specific variant
make only_corne_xiao_corne_dongle_xiao_dongle_display_urob  # Build dongle
make settings_reset_urob    # Build settings reset firmware
```

**Flash firmware (macOS):**
```bash
make nice_corne_flash_left   # Flash to nice!nano left half
make nice_corne_flash_right  # Flash to nice!nano right half
make puchi_corne_flash_left  # Flash to puchi_ble left half
make puchi_corne_flash_right # Flash to puchi_ble right half
```

**Cleanup:**
```bash
make clean_firmware  # Remove built .uf2 files
make clean_zmk      # Remove ZMK source
make clean          # Clean Docker containers and volumes
make clean_all      # Complete cleanup
```

### GitHub Actions Builds

The `build.yaml` file controls GitHub Actions builds. Enable/disable specific keyboard builds by commenting/uncommenting entries. Artifacts are downloaded from the Actions tab after successful builds.

## Architecture

### Repository Structure

```
├── boards/shields/          # Keyboard shield definitions
│   ├── corne/              # Corne keyboard files
│   ├── sofle/              # Sofle keyboard files
│   ├── lily58/             # Lily58 keyboard files
│   └── splitkb_aurora_sofle/  # Aurora Sofle files
├── config/                  # User configuration files
│   ├── *.keymap            # Keymap definitions (user edits these)
│   ├── *.conf              # Configuration overrides (user edits these)
│   └── west.yml            # Module dependencies
├── snippets/               # Reusable configuration snippets
│   ├── common-config/      # Common settings
│   ├── dongle-config/      # Dongle-specific settings
│   └── rgb-config/         # RGB configuration
├── firmware/               # Compiled .uf2 files (output)
└── zmk/                    # ZMK source (cloned by Makefile)
```

### Shield Architecture

Each keyboard has multiple shield variants:
- `{keyboard}_left` / `{keyboard}_right` - Standard split halves
- `{keyboard}_left_peripheral` - Left half as peripheral (for dongle setups)
- `{keyboard}_dongle_pro_micro` - Dongle with Pro Micro pinout (nice!nano, puchi_ble)
- `{keyboard}_dongle_xiao` - Dongle with XIAO pinout (Seeeduino XIAO BLE)

Shield files in `boards/shields/{keyboard}/`:
- `Kconfig.shield` / `Kconfig.defconfig` - Shield definitions
- `{keyboard}.dtsi` - Common devicetree for the keyboard
- `{keyboard}.keymap` - Default keymap (copied from `config/` during build)
- `{keyboard}.conf` - Default configuration
- `{keyboard}_dongle_*.overlay` - Dongle display configurations
- `{keyboard}.zmk.yml` - ZMK hardware metadata

### Configuration Workflow

1. **User edits** keymaps and configs in `config/` directory:
   - `config/corne.keymap` - Corne keyboard layout
   - `config/corne.conf` - Corne configuration options
   - Similar for other keyboards

2. **Build system** copies files from `config/` to shields during compilation

3. **ZMK modules** are loaded via `config/west.yml`:
   - `zmk-dongle-display` - Display widgets for dongles with OLED
   - `zmk-nice-oled` - Vertical OLED widgets for split keyboards
   - `zmk-dongle-display-view` - nice!view display support for dongles
   - `zmk-oled-adapter` - Adapter for different OLED screen sizes
   - `zmk-helpers` - Convenience macros (urob)
   - `zmk-auto-layer` - Auto-layer behaviors (urob)

### Dongle Setup

**Dongle architecture:**
- A third controller acts as USB-to-Bluetooth bridge
- Both keyboard halves connect to the dongle as peripherals
- Dongle connects to computer via USB
- Supports OLED displays (128x32, 128x64, 128x128) or nice!view ePaper

**Configuration locations:**
- Pro Micro dongles: `boards/shields/{keyboard}/{keyboard}_dongle_pro_micro.overlay`
- XIAO dongles: `boards/shields/{keyboard}/{keyboard}_dongle_xiao.overlay`
- Display widgets: Controlled by `zmk-dongle-display` or `zmk-dongle-display-view` modules

**To use a dongle:**
1. Flash `{keyboard}_left_peripheral` to left half
2. Flash `{keyboard}_right` to right half
3. Flash `{board}_{keyboard}_dongle_*` to dongle controller
4. Connect dongle to computer; both halves pair automatically

### ZMK Studio Integration

ZMK Studio is pre-configured for runtime keymap editing.

**Configuration requirements (already set in this repo):**
- `CONFIG_ZMK_STUDIO=y` in build.yaml cmake-args
- `CONFIG_ZMK_STUDIO_LOCKING=n` to skip unlock macro requirement
- `snippet: studio-rpc-usb-uart` in build.yaml for USB/UART communication
- Reserved layers in keymaps (extra_1, extra_2, extra_3 with `status = "reserved"`)

**Usage:**
1. Connect master/dongle to computer via USB
2. Visit https://zmk.studio/ or use desktop app
3. Edit keymap in real-time

### Display Support

**ePaper (nice!view):**
- Ultra-low power SSD1306 replacement
- Enabled by adding `nice_view_adapter nice_epaper` shields
- Configuration via `zmk-dongle-display-view` module for dongles
- Cannot be used with RGB (same pin conflict)

**OLED Screens:**
- Supported sizes: 128x32 (SSD1306), 128x64 (SSD1306), 128x128 (SH1106/SH1107)
- Configuration in `.overlay` files for dongles
- Module: `zmk-dongle-display` or `zmk-oled-adapter`
- Examples in overlay files show different screen configurations

**Screen configuration:**
- Edit `{keyboard}_dongle_*.overlay` files
- Multiple screen examples provided as comments
- Change compatible string and dimensions for different screens

## Important Configuration Notes

### Module System

Modules are external ZMK extensions loaded via `config/west.yml`. When adding or modifying modules:
1. Edit `config/west.yml` remotes and projects sections
2. Run `west update` (Docker: via Makefile targets)
3. Reference module shields in `build.yaml`

### Build Configuration

`build.yaml` controls which firmware variants are built:
- `board:` - Controller type (nice_nano_v2, puchi_ble_v1, seeeduino_xiao_ble)
- `shield:` - Keyboard shield(s), space-separated for multiple
- `cmake-args:` - Build flags (keyboard name, features)
- `snippet:` - Configuration snippets (studio, logging, rgb)
- `artifact-name:` - Output firmware filename

### Keymap Structure

Keymaps use ZMK's devicetree syntax:
- Layers defined in `keymap { }` node
- Bindings use `&behavior` syntax (e.g., `&kp`, `&mo`, `&bt`)
- Studio compatibility requires reserved layers at the end
- Behaviors: `&kp` (key press), `&mo` (momentary layer), `&lt` (layer-tap), `&bt` (bluetooth), `&bootloader`, `&sys_reset`

### Reset and Recovery

**Settings reset:**
- Flash `settings_reset` firmware to both halves
- Clears bonding and configuration
- Re-flash keyboard firmware afterward

**Troubleshooting pairing:**
- Reset both halves simultaneously (press reset button 10x on each)
- Flash peripheral firmware to left, standard firmware to right
- Use settings_reset if problems persist

## Development Tips

- Test builds locally with Docker before pushing to GitHub
- Enable only needed builds in `build.yaml` to save CI time
- Check `firmware/` directory for compiled outputs
- Dongle bootloader access: create combo with `&bootloader` in keymap
- RGB cannot coexist with nice!view on standard pin (pin conflict)
- The repository defaults to urob's ZMK fork with additional features
- Keymap changes don't require reflashing if using ZMK Studio
