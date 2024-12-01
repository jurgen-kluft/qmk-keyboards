# SplitKeyboards

So now that I have two 34 key split keyboards on the way I have to start figuring out how to reduce my thumb cluster to only allow for 2 thumb keys per side while still being able to easily access `Smart Caps` and `Smart Numbers`.

## Keyboards

- [Kyria](https://splitkb.com/collections/keyboard-kits/products/kyria-pcb-kit)
- [Hillside](https://github.com/mmccoyd/hillside)
- [Moonlander](https://www.zsa.io/moonlander/)
- On the way => [Sweep](https://splitkb.com/collections/keyboard-kits/products/aurora-sweep-pcb-kit)
- On the way => [Dilemma](https://bastardkb.com/dilemma/)

## Keymap

With the following features:
- Callum style Oneshot Modifiers (*rewrite*, `oneshot.c`, `user_oneshot.c`)
  - double-tap to lock a modifier
  - tap **NAV** to cancel all modifiers
- Smart Numbers (`feature.c`)
  - holding **NAV** and tapping **SYM**
  - will end when pressing *space*
- Smart Caps (`feature.c`)
  - holding **SYM** and tapping **NAV** will turn ON Smart Caps
  - tapping **NAV** will turn OFF Smart Caps
  - tapping `.` will cycle:
    - `Normal/Repeat -> Camel Case -> Snake Case -> Off`
  - will end when pressing *space* or **NAV**
- Smart Caps (`feature.c`), Normal mode
  - start typing letters
- Smart Caps (`feature.c`), Repeat mode
  - first enter some symbols that should be the delimiters
  - then start typing letters
  - `;` will emit the delimiters (maximum 4)
- Smart Caps (`feature.c`), Camel Case
  - start with typing letters
  - `;` will emit a space and set the next letter to be shifted
  - you can use `,` to activate shift manually
- Smart Caps (`feature.c`), Snake Case
  - start with typing letters
  - `;` will emit an underscore
  - you can use `,` to activate shift manually
- **SYM** key can be tapped for a oneshot key from the **SYM** layer (`feature.c`)
  - **SYM** key can also be held
- **RAISE** layer can be activated by holding **NAV** and **SYM** like tri-layer. (`feature.c`)
- **RAISE** layer can also be activated/locked by first tapping **SYM** then tapping **NAV** (`feature.c`)
- Custom `leader` implementation using **NAV** as leader key (`leader.c`, `user_leader.c`)
  - `leader`, mode = 1
  - `leader` `leader`, mode = 2
  - `leader` `leader` `leader`, mode = 3
  - `leader` **`SYM`**, mode = 4
- Custom normal/shift/ctrl/alt keycodes (`cushi.c`)
- Custom OS keycodes to deal with `Mac OS` / `Windows` / `Ubuntu` (`cukey.c`)

## Leader

The leader key is the same key that activates the NAVIGATION layer (hold), however we treat it as a leader when it is tapped.
When it is a single tap the user has `250 ms` to tap the first letter in the chain, the letter(s) following are not time bound.
Tapping the leader twice means that a second set of chains will be used, entering the chain is not time bound. Then
there is also a third set of chains, not time bound, that can be activated by tapping leader three times.

Examples:

### Single tap leader chains

- `leader f`, this will activate *easy motion* (vscode)
- `leader z`, this will center the cursor in the middle of the screen (vscode)
- `leader d d`, this will execute a *delete line* command
- `leader o o`, this will execute a *insert line below* command
- `leader g g`, this will put the cursor at the top of the document
- `leader c i w`, this will execute a *change inside word* command
- etc.. see `user_leader.c` for the full list

### Double tap leader chains

- `leader leader n`, this will print ` != `
- `leader leader a`, this will print ` && `
- `leader leader o`, this will print ` || `
- etc.. see `user_leader.c` for the full list

## Status

- HillSide: **OK**
- Kyria: **OK**
- Moonlander: **OK**

## Setup

- Clone the QMK repository and install/setup
- Symlink, see `symlink-howto.md`

Then compile Kyria, Hillside or Moonlander:

- `make splitkb/kyria/rev1:jaykay`
- `make handwired/hillside/0_1:jaykay`
- `make moonlander:jaykay`

## Visual Keymap

(Generated with `https://github.com/jurgen-kluft/go-qmk-keymap`)

![](keymap.svg)
