# Plan: Displaying Peripheral Battery on HillsideView

## Goal
Display the right side (peripheral) battery level on the left side (central) nice!view display.

## Current Status

### What's Already Configured
- `CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_FETCHING=y` - Central fetches peripheral battery via BLE
- `CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_PROXY=y` - Central can proxy peripheral battery to host
- nice!view display working on left (central) side
- Cirque trackpad working on right (peripheral) side

### The Problem
The default nice!view widget only shows the **central** battery. The peripheral battery data is fetched but not displayed.

---

## Options

### Option 1: zmk-nice-oled Module (Recommended)

**What it does:** Provides custom nice!view widgets that can display peripheral battery.

**Previous attempt:** Failed due to `input_transform.h` error (unrelated to the module itself - was a trackpad config issue that's now fixed).

**Required changes:**

1. Add to `config/west.yml`:
```yaml
remotes:
  - name: mctechnology17
    url-base: https://github.com/mctechnology17

projects:
  - name: zmk-nice-oled
    remote: mctechnology17
    revision: main
```

2. Update `build.yaml` shields:
```yaml
# Change from:
shield: hillside_view_left_flip nice_view
# To:
shield: hillside_view_left_flip nice_view_adapter nice_epaper
```

3. Add to `config/hillside_view_left_flip.conf` (or shield conf):
```kconfig
# Enable zmk-nice-oled custom widgets
CONFIG_ZMK_DISPLAY_STATUS_SCREEN_CUSTOM=y
CONFIG_NICE_EPAPER_ON=y

# Show both central and peripheral battery
CONFIG_NICE_OLED_WIDGET_CENTRAL_SHOW_BATTERY_PERIPHERAL_AND_CENTRAL=y
```

**Pros:**
- Shows both batteries on nice!view
- Well-maintained module
- Works with ePaper displays

**Cons:**
- May conflict with custom SPI pinout in hillside_view.dtsi
- Need to test if `nice_epaper` shield overrides our custom `nice_view_spi` definition

**Potential SPI Conflict:**
The `nice_epaper` shield from zmk-nice-oled defines its own SPI configuration. Our `hillside_view.dtsi` has custom SPI1 pins:
```dts
nice_view_spi: &spi1 {
  pinctrl-0 = <&spi1_default>;  // Custom pins: SCK=P0.20, MOSI=P0.17
  ...
};
```

If zmk-nice-oled's `nice_epaper` tries to redefine SPI, there could be a conflict. Solution would be to check if we need to disable the shield's SPI overlay.

---

### Option 2: Dongle Setup

**What it does:** Use a third controller (dongle) as the central device. Both keyboard halves become peripherals, and the dongle displays both batteries.

**Required changes:**

1. Add dongle shield files for HillsideView
2. Change left side from central to peripheral
3. Flash dongle firmware to a spare nice!nano/XIAO

**Pros:**
- Clean architecture - dongle handles all display/USB
- Both halves are wireless to dongle
- Can use zmk-dongle-display-view for nice!view on dongle

**Cons:**
- Requires third controller
- More complexity in build setup
- Need to create new shield files

---

### Option 3: Host Application

**What it does:** Use a desktop app that reads battery data over HID and displays it in system tray.

**Available apps:**
- [zmk-battery-center](https://github.com/kot149/zmk-battery-center) - macOS/Windows
- [zmkBATx](https://github.com/mh4x0f/zmkBATx) - Linux CLI

**Pros:**
- No firmware changes needed
- Works with current setup
- Shows exact percentage

**Cons:**
- Requires app running on host
- Not visible on keyboard itself
- Depends on OS HID battery support

---

### Option 4: Custom nice!view Widget

**What it does:** Modify the default nice!view code to display peripheral battery.

**Required:**
- Fork/modify ZMK's nice!view widget code
- Add peripheral battery rendering

**Pros:**
- Full control over display
- No external module dependencies

**Cons:**
- Significant development effort
- Need to maintain fork
- Complex to implement

---

## Recommended Approach

### Try Option 1 (zmk-nice-oled) first

The previous failure was due to `input_transform.h` missing, not SPI conflict. That issue is now fixed. Let's try again:

1. Add zmk-nice-oled to west.yml
2. Change shield to `nice_view_adapter nice_epaper`
3. Add config options for peripheral battery display
4. Build and test

### If SPI conflict occurs:

Check if we need to disable the `nice_epaper` shield's SPI overlay. The zmk-nice-oled module might have a `nice_custom` shield option that allows using our custom SPI definition.

### Fallback to Option 2 (Dongle):

If zmk-nice-oled doesn't work, set up a dongle:
1. Create `hillside_view_dongle_*.overlay` files
2. Change both keyboard halves to peripheral mode
3. Dongle becomes central with display

---

## Testing Plan

1. **Phase 1:** Try zmk-nice-oled
   - Add module to west.yml
   - Update build.yaml shield
   - Add config options
   - Build and flash
   - Check if peripheral battery displays

2. **Phase 2 (if needed):** Debug SPI conflict
   - Check build logs for SPI errors
   - Try `nice_custom` shield instead of `nice_epaper`
   - Manually merge our SPI config with module's

3. **Phase 3 (fallback):** Dongle setup
   - Create dongle overlays
   - Test dongle with both halves

---

## References

- zmk-nice-oled: https://github.com/mctechnology17/zmk-nice-oled
- zmk-dongle-display-view: https://github.com/mctechnology17/zmk-dongle-display-view
- ZMK battery config: https://zmk.dev/docs/config/battery
- Previous attempt commit: 0ba7429 (reverted in d4b7fcd)
