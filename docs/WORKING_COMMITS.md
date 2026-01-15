# Working Commits and Firmware

## Cirque Trackpad - Working Config

**Commit:** `6ca0a4c53a20dcde2ebf9d4dbbb7baa81d4ff499`
- Both left and right hillside builds succeeded
- Cirque trackpad working on peripheral (right) side

**Flip Firmware Build:** Run ID `21039000759` (commit `070648c`)
- `nice_hillside_view_left_flip.uf2` - central with nice!view
- `nice_hillside_view_right_flip.uf2` - peripheral with Cirque

**Backup Location:** `firmware/backup_working/`

## Key Config at Working Commit

### Shield conf (`boards/shields/hillside_view/hillside_view.conf`)
```kconfig
CONFIG_I2C=y
CONFIG_PINNACLE=y
CONFIG_NFCT_PINS_AS_GPIOS=y
CONFIG_ZMK_MOUSE=y
CONFIG_INPUT=y
CONFIG_INPUT_PINNACLE=y
```

### DTSi - no pinctrl on i2c0, sensitivity=1x
```dts
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

## To Restore Working State

```bash
git checkout 070648c -- boards/shields/hillside_view/hillside_view.dtsi
git checkout 070648c -- boards/shields/hillside_view/hillside_view.conf
git checkout 070648c -- config/hillside_view_right.conf
```
