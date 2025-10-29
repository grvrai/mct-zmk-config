# Unified Miryoku-Based Layout for Corne and Sofle

Both Corne and Sofle keyboards now share the same unified layer structure, combining Miryoku's ergonomic layer organization with urob's home row mods and num layer design.

## Key Features

✅ **Identical layer structure** across both keyboards
✅ **Urob's home row mods** with proven timing (280ms/175ms/150ms)
✅ **Urob's num layer** with left-hand modifiers, right-hand numbers
✅ **Right-hand navigation** using IJKL pattern
✅ **Miryoku layer organization** (BASE, NAV, MOUSE, MEDIA, NUM, SYM, FUN, SYS)
✅ **Conditional SYS layer** (NAV + MOUSE simultaneously)

## Layer Structure

### 0. BASE - QWERTY with Home Row Mods
```
Q  W  E  R  T    Y  U  I  O  P
A  S  D  F  G    H  J  K  L  '
GUI ALT CTRL SHFT    SHFT CTRL ALT GUI
Z  X  C  V  B    N  M  ,  .  /

Thumbs (Corne):
MEDI NAV MOUS    SYM NUM FUN
ESC  SPC TAB     RET BSP DEL

Thumbs (Sofle):
CTRL MEDI NAV MOUS    SYM NUM FUN RALT
     ESC  SPC TAB     RET BSP DEL
```

**Home row mods:**
- Left: A=GUI, S=ALT, D=CTRL, F=SHIFT
- Right: J=SHIFT, K=CTRL, L=ALT, ;=GUI

### 1. NAV - Navigation (Right Hand IJKL)
**Left hand:** Modifiers + layer access
```
BOOT      BASE
GUI ALT CTRL SHFT
     RALT NUM NAV
```

**Right hand:** Navigation keys
```
INS  HOME PG_DN PG_UP END
CAPS LEFT DOWN  UP    RIGHT
REDO PASTE COPY CUT   UNDO
```

### 2. MOUSE - Mouse Keys
**Left hand:** Modifiers + layer access
```
BOOT      BASE
GUI ALT CTRL SHFT
     RALT SYM MOUS
```

**Right hand:** Modifiers + clipboard
```
     SHFT CTRL ALT GUI
REDO PASTE COPY CUT UNDO
```

### 3. MEDIA - Media & System
**Left hand:** Modifiers + layer access
```
BOOT      BASE
GUI ALT CTRL SHFT
     RALT FUN MEDI
```

**Right hand:** Media & RGB controls
```
RGB  RGB  RGB  RGB  RGB
TOG  HUI  SAI  BRI  EFF
OUT  BT0  BT1  BT2  BT3
MUTE VOL- VOL+
```

### 4. NUM - Number Pad (Urob's Layout)
**Left hand:** Operators + modifiers
```
=  +  -  *  /
=  +  GUI ALT CTRL SHFT
      {  }
```

**Right hand:** Number pad
```
/  7  8  9  -
   4  5  6  +
0  1  2  3  .
   0
```

### 5. SYM - Symbols
**Left hand:** Modifiers + layer access
```
BOOT      BASE
GUI ALT CTRL SHFT
     RALT SYM MOUS
```

**Right hand:** Symbols
```
{  &  *  (  }
+  $  %  ^  :
|  !  @  #  ~
_  (  )
```

### 6. FUN - Function Keys
**Left hand:** Modifiers + layer access
```
BOOT      BASE
GUI ALT CTRL SHFT
     RALT FUN MEDI
```

**Right hand:** Function keys
```
PSCR F7  F8  F9  F12
SLCK F4  F5  F6  F11
PAUS F1  F2  F3  F10
TAB  SPC APP
```

### 7. SYS - System (Conditional)
**Activated when:** NAV + MOUSE pressed together

**Left hand:** Bluetooth + bootloader
```
BTCLR BT0 BT1 BT2 BT3 (BT4 on Sofle)
BOOT
```

**Right hand:** Bootloader
```
BOOT (right side)
```

## Thumb Cluster Layout

### Corne (3+3 thumbs)
```
Left:  MEDI/ESC   NAV/SPC   MOUS/TAB
Right: SYM/RET    NUM/BSP   FUN/DEL
```

### Sofle (5+5 thumbs, but using inner 4+4)
```
Left:  CTRL   MEDI/ESC   NAV/SPC   MOUS/TAB   (none)
Right: (none) SYM/RET    NUM/BSP   FUN/DEL    RALT
```

## Layer Access Patterns

| Layer | Left Thumb | Right Thumb | Description |
|-------|-----------|-------------|-------------|
| **NAV** | Hold SPC | - | Navigation keys (IJKL arrows) |
| **MOUSE** | Hold TAB | - | Mouse movement/buttons |
| **MEDIA** | Hold ESC | - | Media controls, RGB, BT |
| **NUM** | - | Hold BSP | Number pad (urob style) |
| **SYM** | - | Hold RET | Symbols |
| **FUN** | - | Hold DEL | Function keys |
| **SYS** | NAV + MOUSE | - | System (conditional) |

## Design Philosophy

### Miryoku Principles Used
1. **Layer-based access**: Everything within reach via layers
2. **Balanced hands**: Actions distributed between hands
3. **Home row mods**: All modifiers on home row
4. **Consistent structure**: Same layout across keyboards

### Urob's Contributions
1. **Proven HRM timing**: 280ms tapping, 175ms quick-tap, 150ms prior-idle
2. **Num layer design**: Left modifiers, right numbers
3. **Positional hold-tap**: Prevents false activations
4. **Num word behavior**: Smart number entry

### Navigation Philosophy
- **Right-hand navigation**: IJKL pattern (like Vim)
- **Left-hand modifiers**: GUI/ALT/CTRL/SHIFT available
- **Clipboard on bottom row**: Consistent across NAV/MOUSE layers

## Common Workflows

### Text Navigation
- Hold **SPACE** (NAV layer)
- Use **J/K/L/I** for Left/Down/Up/Right
- Use **HOME/END/PG_DN/PG_UP** for jumps
- Use **PASTE/COPY/CUT** for clipboard

### Number Entry
- Hold **BACKSPACE** (NUM layer)
- Right hand becomes number pad
- Left hand has operators (+, -, *, /)
- Left hand keeps modifiers for shortcuts

### Symbols
- Hold **RETURN** (SYM layer)
- Right hand has programming symbols
- Brackets, operators, special chars

### Media Control
- Hold **ESC** (MEDIA layer)
- RGB controls on right hand
- Bluetooth selection (BT0-BT3)
- Media keys (VOL, MUTE, etc.)

### Function Keys
- Hold **DELETE** (FUN layer)
- F1-F12 on right hand
- Arranged in rows of F1-F3, F4-F6, F7-F9
- F10, F11, F12 on far right

## Differences from Stock Miryoku

1. **Navigation hand**: Right hand (IJKL) instead of left
2. **Num layer**: Urob's design instead of Miryoku's
3. **HRM timing**: Urob's proven settings (280/175/150)
4. **Thumb arrangement**: Adapted for ergonomic thumb access
5. **Extra row**: Sofle has number row on top

## Building Firmware

Same build commands work for both keyboards:

```bash
# Corne
make only_nice_corne_left_view_urob
make only_nice_corne_right_view_urob

# Sofle
make only_nice_sofle_left_view_urob
make only_nice_sofle_right_view_urob
```

## Tips for Learning

1. **Start with BASE layer**: Get comfortable with home row mods
2. **Add NAV layer**: Practice SPACE + IJKL for navigation
3. **Add NUM layer**: Practice BACKSPACE + numbers
4. **Add other layers** gradually as needed
5. **Print layer diagrams** for reference during learning

## Configuration Files

- **Corne keymap**: `config/corne.keymap`
- **Sofle keymap**: `config/sofle.keymap`
- **Config files**: `config/corne.conf`, `config/sofle.conf`

## Credits

- **Miryoku layout**: [Manna Harbour](https://github.com/manna-harbour/miryoku)
- **Urob's HRM config**: [urob](https://github.com/urob/zmk-config)
- **ZMK firmware**: [ZMK Project](https://zmk.dev/)

## Additional Notes

- Both keyboards use identical layer numbers and names
- Conditional SYS layer accessible by holding NAV + MOUSE
- Bootloader access on both sides (BOOT key in top corners)
- Bluetooth clear and selection in MEDIA and SYS layers
- Smart-num behavior: tap for num-word, hold for layer
