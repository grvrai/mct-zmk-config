# Cirque Trackpad Setup for HillsideView

This document describes the working Cirque TM035035 trackpad configuration for the HillsideView keyboard.

## Working Configuration (as of commit 6ca0a4c)

### Hardware Setup

- **Cirque TM035035** 35mm curved overlay trackpad
- **Connection:** I2C (not SPI)
- **I2C Address:** 0x2A (ADR resistor empty)
- **R1 Resistor:** Empty (selects I2C mode; populated = SPI mode)

### I2C Pins (from PCB schematic)

| Signal | nRF52840 Pin | Pro Micro Pin |
|--------|--------------|---------------|
| SDA    | P1.0         | D6            |
| SCL    | P0.24        | D5            |
| DR     | P1.2         | -             |

**Note:** The FFC connector has pads on both PCB layers (F.Cu and B.Cu) with mirrored positions, so either top or bottom FFC works with the same I2C pins.

### Layout Options

#### Regular Layout (Cirque + Display on RIGHT side)
- Right side: Peripheral with Cirque trackpad AND nice!view display
- Left side: Central
- Files: `hillside_view_right.overlay`, `config/hillside_view_right.conf`

#### Flip Layout (Display on LEFT, Cirque on RIGHT)
- Left side: Central with nice!view display (MCU on top)
- Right side: Peripheral with Cirque trackpad only (MCU on top)
- Files: `hillside_view_left_flip.overlay`, `hillside_view_right_flip.overlay`

### Key Differences: Regular vs Flip

| Aspect | Regular | Flip |
|--------|---------|------|
| Display location | Right (peripheral) | Left (central) |
| Cirque location | Right (peripheral) | Right (peripheral) |
| MCU orientation | Bottom | Top (flipped) |
| Right overlay | Enables nice!view + Cirque | Enables Cirque only |
| Keyboard name | Default | Custom ("HSV Left", "HSV Right") |

## Critical Configuration Files

### 1. Shield Conf (`boards/shields/hillside_view/hillside_view.conf`)

```kconfig
CONFIG_I2C=y
CONFIG_PINNACLE=y
CONFIG_NFCT_PINS_AS_GPIOS=y
CONFIG_ZMK_MOUSE=y
CONFIG_INPUT=y
CONFIG_INPUT_PINNACLE=y
```

**Important:** `CONFIG_PINNACLE=y` and `CONFIG_NFCT_PINS_AS_GPIOS=y` are technically undefined/deprecated symbols, but they are required for the build to work. They generate warnings but don't abort.

### 2. DTSi (`boards/shields/hillside_view/hillside_view.dtsi`)

```dts
/* I2C pinctrl definitions */
&pinctrl {
  i2c0_default: i2c0_default {
    group1 {
      psels = <NRF_PSEL(TWIM_SDA, 1, 0)>,
          <NRF_PSEL(TWIM_SCL, 0, 24)>;
    };
  };

  i2c0_sleep: i2c0_sleep {
    group1 {
      psels = <NRF_PSEL(TWIM_SDA, 1, 0)>,
          <NRF_PSEL(TWIM_SCL, 0, 24)>;
      low-power-enable;
    };
  };
};

/* Cirque device definition - disabled by default */
&i2c0 {
    status = "disabled";
    glidepoint0: glidepoint@2a {
        compatible = "cirque,pinnacle";
        reg = <0x2a>;
        status = "disabled";
        dr-gpios = <&gpio1 2 (GPIO_ACTIVE_HIGH)>;
        sensitivity = "1x";
        sleep;
    };
};
```

**Critical:** Do NOT add `compatible`, `pinctrl-0`, `pinctrl-1`, or `pinctrl-names` directly to the `&i2c0` node. The nice_nano board already provides these. Adding them breaks the build.

### 3. Right Side Overlay (enables Cirque)

```dts
/* Enable I2C and Cirque */
&i2c0 {
    status = "okay";
    glidepoint0: glidepoint@2a {
        status = "okay";
    };
};

/ {
    /* Virtual input for keymap binding */
    glidepoint1: virtual_input {
        compatible = "zmk,virtual-input";
    };

    /* Relay Cirque input from peripheral to central */
    input_relay_config_102 {
        compatible = "zmk,split-peripheral-input-relay";
        device = <&glidepoint0>;
        relay-channel = <102>;
    };
};
```

### 4. Per-Side Conf (e.g., `config/hillside_view_right_flip.conf`)

```kconfig
# Mouse/Trackpad - basic settings only
CONFIG_ZMK_MOUSE=y
CONFIG_INPUT=y
CONFIG_GPIO=y
CONFIG_I2C=y
CONFIG_PINCTRL=y
```

**Note:** `CONFIG_INPUT_PINNACLE` is NOT needed in the per-side conf - it's provided by the shield conf.

## ZMK Fork and Dependencies

This setup requires badjeff's ZMK fork with pointer support and several modules.

### Required in `config/west.yml`

```yaml
manifest:
  remotes:
    - name: zmkfirmware
      url-base: https://github.com/zmkfirmware
    - name: badjeff
      url-base: https://github.com/badjeff

  projects:
    # REQUIRED: ZMK fork with pointer/mouse support
    - name: zmk
      remote: badjeff
      revision: feat/pointers-move-scroll
      import: app/west.yml

    # REQUIRED: Cirque Pinnacle trackpad driver
    - name: cirque-input-module
      remote: badjeff
      revision: main

    # REQUIRED: Relays trackpad input from peripheral to central over BLE
    - name: zmk-split-peripheral-input-relay
      remote: badjeff
      revision: main

    # REQUIRED: Input behavior listener for mouse movement/scroll
    - name: zmk-input-behavior-listener
      remote: badjeff
      revision: main

    # OPTIONAL: Mouse key toggle behavior
    - name: zmk-behavior-mouse-key-toggle
      remote: badjeff
      revision: main

  self:
    path: config
```

### Module Descriptions

| Module | Purpose | Required |
|--------|---------|----------|
| `zmk` (badjeff fork) | ZMK with `feat/pointers-move-scroll` branch for mouse/trackpad support | Yes |
| `cirque-input-module` | Cirque Pinnacle I2C/SPI driver | Yes |
| `zmk-split-peripheral-input-relay` | Sends trackpad events from peripheral to central via BLE | Yes |
| `zmk-input-behavior-listener` | Processes input events and maps to mouse movement/scroll | Yes |
| `zmk-behavior-mouse-key-toggle` | Toggle mouse keys on/off | Optional |

### Why Not Standard ZMK?

Standard ZMK (`zmkfirmware/zmk`) does not have:
- Mouse/pointer HID support
- Input relay for split keyboards
- Cirque driver integration

You **must** use badjeff's `feat/pointers-move-scroll` branch for trackpad functionality.

### Keeping Dependencies Updated

These modules are actively developed and receive frequent updates. Check for updates regularly:

```bash
# Check for updates to badjeff's ZMK fork
gh api repos/badjeff/zmk/commits/feat/pointers-move-scroll --jq '.commit.message, .commit.author.date'

# Check cirque-input-module updates
gh api repos/badjeff/cirque-input-module/commits/main --jq '.commit.message, .commit.author.date'
```

**Update sources:**
- badjeff's ZMK fork: https://github.com/badjeff/zmk/tree/feat/pointers-move-scroll
- cirque-input-module: https://github.com/badjeff/cirque-input-module
- zmk-split-peripheral-input-relay: https://github.com/badjeff/zmk-split-peripheral-input-relay

**Note:** After updating west.yml, you may need to rebuild firmware. Breaking changes occasionally happen - if trackpad stops working after an update, check the commit history for changes to Kconfig symbols or devicetree bindings.

## Troubleshooting

### DR Pin Stuck at 3.3V
- Cirque not initializing - check I2C address (ADR resistor)
- Check R1 resistor is empty (for I2C mode)
- Verify pull-up resistors on SDA/SCL show ~4.7kΩ

### Build Fails with "undefined symbol PINNACLE"
- This is expected - keep `CONFIG_PINNACLE=y` anyway
- The symbol generates a warning but is still needed

### Build Fails with "Aborting due to Kconfig warnings"
- Recent ZMK/Zephyr versions are stricter
- Make sure you're using the exact config from working commit 6ca0a4c

### Trackpad Works on One PCB But Not Another
- Check resistor population matches (R1 empty, ADR as needed)
- Verify FFC cable is seated correctly
- Test with multimeter: SDA/SCL pull-ups should show 4.7kΩ
