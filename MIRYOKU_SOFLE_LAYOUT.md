# Miryoku Layout for Sofle Keyboard

This is a Miryoku-inspired keymap for the Sofle keyboard, implementing the ergonomic and efficient Miryoku layout principles with a **flipped** configuration.

## What is Miryoku?

Miryoku is an ergonomic, minimal, orthogonal, and universal keyboard layout that emphasizes:
- **Home row mods**: All modifiers (GUI/Alt/Ctrl/Shift) on the home row
- **Layers over reach**: Use thumb layer keys instead of reaching for distant keys
- **Symmetry**: Balanced layout between hands
- **Minimal finger travel**: Everything within easy reach

## Layout Overview

### Base Layer (QWERTY)

```
┌────┬────┬────┬────┬────┬────┐                    ┌────┬────┬────┬────┬────┬────┐
│    │    │    │    │    │    │                    │    │    │    │    │    │    │
├────┼────┼────┼────┼────┼────┤                    ├────┼────┼────┼────┼────┼────┤
│    │ Q  │ W  │ E  │ R  │ T  │                    │ Y  │ U  │ I  │ O  │ P  │    │
├────┼────┼────┼────┼────┼────┤                    ├────┼────┼────┼────┼────┼────┤
│    │GUI │ALT │CTRL│SHFT│ G  │                    │ H  │SHFT│CTRL│ALT │GUI │    │
│    │ A  │ S  │ D  │ F  │    │                    │    │ J  │ K  │ L  │ '  │    │
├────┼────┼────┼────┼────┼────┼────┐          ┌────┼────┼────┼────┼────┼────┼────┤
│    │ Z  │ X  │ C  │ V  │ B  │MUTE│          │    │ N  │ M  │ ,  │ .  │ /  │    │
└────┴────┴────┼────┼────┼────┼────┤          ├────┼────┼────┼────┼────┴────┴────┘
               │    │    │MOUS│NAV │          │SYM │NUM │FUN │    │
               │    │    │TAB │SPC │          │RET │BSP │DEL │    │
               └────┴────┼────┼────┤          ├────┼────┼────┴────┘
                         │MEDI│    │          │    │    │
                         │ESC │    │          │    │    │
                         └────┴────┘          └────┴────┘

Home Row Mods (hold keys on home row):
- Left: A=GUI, S=ALT, D=CTRL, F=SHIFT
- Right: J=SHIFT, K=CTRL, L=ALT, '=GUI
```

### Key Features

1. **Home Row Mods**: All modifiers are on the home row
   - Left hand: GUI(⌘/Win) - ALT - CTRL - SHIFT
   - Right hand: SHIFT - CTRL - ALT - GUI(⌘/Win)
   - Hold for modifier, tap for letter

2. **Thumb Cluster Layer Access** (Flipped Configuration):
   - **Left thumb**:
     - Inner: MOUSE layer (hold) / TAB (tap)
     - Middle: NAV layer (hold) / SPACE (tap)
     - Outer: MEDIA layer (hold) / ESC (tap)
   - **Right thumb**:
     - Inner: SYM layer (hold) / RETURN (tap)
     - Middle: NUM layer (hold) / BACKSPACE (tap)
     - Outer: FUN layer (hold) / DELETE (tap)

3. **Balanced Timing**:
   - Tapping term: 200ms
   - Quick tap: 175ms
   - Prior idle: 150ms

## Layer Details

### 0. BASE - Base QWERTY Layer
- Standard QWERTY alpha keys
- Home row mods on ASDF (left) and JKL; (right)
- Thumb keys access all other layers

### 1. NAV - Navigation Layer
**Left hand**: Navigation keys
```
HOME  PG_DN  PG_UP  END    INS
LEFT  DOWN   UP     RIGHT  CAPS
UNDO  CUT    COPY   PASTE  REDO
```
**Right hand**: Modifiers + access
```
      BASE
      SHFT   CTRL   ALT    GUI
NAV   NUM    RALT
```

### 2. MOUSE - Mouse Keys Layer
**Left hand**: Mouse movement (simulated)
```
(Mouse movement keys)
```
**Right hand**: Modifiers + access
```
      BASE
      SHFT   CTRL   ALT    GUI
MOUSE SYM    RALT
```

### 3. MEDIA - Media Controls & System
**Left hand**: Media and RGB controls
```
RGB   RGB    RGB    RGB    RGB
EFF   HUI    SAI    BRI    TOG

PREV  VOL-   VOL+   NEXT   EPTOG

BT0   BT1    BT2    BT3    OUT
```
**Right hand**: Modifiers + access
```
      BASE
      SHFT   CTRL   ALT    GUI
MEDIA FUN    RALT
```

### 4. NUM - Number Pad Layer
**Right hand**: Number pad
```
[     7      8      9      ]
=     4      5      6      ;
\     1      2      3      `
-     0      .
```
**Left hand**: Modifiers + access
```

GUI   ALT    CTRL   SHFT
      RALT   NUM    NAV
```

### 5. SYM - Symbols Layer
**Right hand**: Symbol keys
```
{     &      *      (      }
+     $      %      ^      :
|     !      @      #      ~
_     (      )
```
**Left hand**: Modifiers + access
```

GUI   ALT    CTRL   SHFT
      RALT   SYM    MOUSE
```

### 6. FUN - Function Keys Layer
**Right hand**: Function keys
```
PSCR  F7     F8     F9     F12
SLCK  F4     F5     F6     F11
PAUS  F1     F2     F3     F10
TAB   SPACE  APP
```
**Left hand**: Modifiers + access
```

GUI   ALT    CTRL   SHFT
      RALT   FUN    MEDIA
```

### 7. BUTTON - Button Layer
Clipboard operations mirrored on both hands:
```
UNDO  CUT    COPY   PASTE  REDO
GUI   ALT    CTRL   SHFT
```

## Flipped vs Standard Miryoku

This implementation uses the **flipped** Miryoku configuration:

**Standard Miryoku (right-hand navigation)**:
- Left thumb: Media, Nav, Mouse
- Right thumb: Sym, Num, Fun

**Flipped Miryoku (LEFT-hand navigation)** - THIS LAYOUT:
- Left thumb: Mouse, Nav, Media
- Right thumb: Sym, Num, Fun

The flipped version is preferred by users who want navigation (arrows, home, end, etc.) on the LEFT hand instead of the right.

## Why Miryoku?

1. **Ergonomic**: Minimizes finger movement and reach
2. **Fast**: Home row mods eliminate need to move hands
3. **Universal**: Same layout works across different keyboards
4. **Balanced**: Equal work distribution between hands
5. **Layers**: Access all keys without stretching
6. **Customizable**: Easy to adapt to personal preferences

## Usage Tips

### Learning Home Row Mods
1. Start slowly - the timing takes practice
2. Focus on one hand at a time
3. Common combinations:
   - Ctrl+C: Hold D, tap C
   - Ctrl+V: Hold D, tap V
   - Alt+Tab: Hold S, tap Tab
4. Use typing games to build muscle memory

### Layer Access Patterns
- **Text editing**: Use NAV layer (arrows, home, end)
- **Number entry**: Use NUM layer (number pad)
- **Coding**: Use SYM layer (brackets, operators)
- **Shortcuts**: Use FUN layer (F-keys)
- **System**: Use MEDIA layer (volume, brightness, BT)

### Common Workflows

**Text navigation**:
- Hold Space (NAV layer) + arrow keys
- Hold Space + Home/End for line navigation
- Hold Space + PgUp/PgDn for page navigation

**Number entry**:
- Hold Backspace (NUM layer) + number keys
- Works like a traditional numpad

**Symbols**:
- Hold Return (SYM layer) + symbol keys
- Quick access to programming symbols

## Configuration Files

- **Keymap**: `config/sofle_miryoku.keymap`
- **Config**: Use existing `config/sofle.conf` (no changes needed)

## Building Firmware

Use the same build commands as the standard Sofle firmware:

```bash
# For nice!nano v2
make only_nice_sofle_left_view_urob
make only_nice_sofle_right_view_urob

# For puchi_ble_v1
make only_puchi_sofle_left_view_urob
make only_puchi_sofle_right_view_urob
```

Just replace the keymap filename in the build configuration.

## Customization

To customize this layout:

1. **Change base alpha layout**: Modify the base_layer bindings
   - Currently QWERTY, can change to Colemak, Dvorak, etc.
2. **Adjust timing**: Modify the MIRYOKU_* defines at the top
3. **Swap layers**: Rearrange thumb layer assignments
4. **Add combos**: Add combo definitions for frequently used key combinations

## Resources

- [Miryoku Official](https://github.com/manna-harbour/miryoku)
- [Miryoku ZMK](https://github.com/manna-harbour/miryoku_zmk)
- [ZMK Documentation](https://zmk.dev/)

## Credits

- Layout design by [Manna Harbour](https://github.com/manna-harbour)
- Adapted for Sofle keyboard with flipped configuration
- Based on Miryoku ZMK implementation
