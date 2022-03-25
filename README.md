# Kyria

My keymap uses the following features:
- Callum style Oneshot Modifiers (a rewrite)
  - plus a modification to allow double-tap to lock a modifier
- Smart numbers 
- Smart caps words
- Custom normal/shift keycodes (cushi)
- Custom OS keycodes to deal with Mac OS / Windows / Ubuntu (cukey)

# Setup

- Clone the QMK repository and install/setup
- Symlink, see `symlink-howto.md`

Then compile Kyria or Hillside:

- `qmk compile -kb splitkb/kyria/rev1 -km jaykay`
- `qmk compile -kb handwired/hillside/0_1 -km jaykay`

# Keymap

(Generated with `https://github.com/jurgen-kluft/go-qmk-keymap`)

![](keymap.svg)
