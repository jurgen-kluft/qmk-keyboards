# Kyria

My keymap uses the following features:
- Custom layers & layer switching (Only 1 QMK layer, `user_layers.c`)
- Internally uses custom 8-bit keycodes
- Callum style Oneshot Modifiers (a rewrite, `oneshot.c`, `user_oneshot.c`)
  - double-tap to lock a modifier
- Smart Numbers (`feature.c`)
  - will end when pressing *space*
- Smart Caps (`feature.c`)
  - pressing `Smart Caps` will go through `Normal/Repeat -> Camel Case -> Snake Case -> Off`
- Smart Caps (`feature.c`), Normal mode
  - start typing letters
  - will end when pressing *space*
- Smart Caps (`feature.c`), Repeat mode
  - first enter some symbols that should be the delimiters
  - then start typing letters
  - space will emit the delimiters (maximum 4)
  - will end when pressing **NAV**
- Smart Caps (`feature.c`), Camel Case
  - start with typing letters
  - space will emit a space and set the next letter to be shifted
  - you can use `,` to activate shift manually
  - tap `.` to deactivate
- Smart Caps (`feature.c`), Snake Case
  - start with typing letters
  - space will emit an underscore
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
- **VIM** basic features (`vim.c`)

# Leader

The leader key is the same key that activates the NAVIGATION layer (hold), however we treat it as a leader when it is tapped.
When it is a single tap the user has `250 ms` to tap the first letter in the chain, the letter(s) following are not time bound.
Tapping the leader twice means that a second set of chains will be used, entering the chain is not time bound. Then
there is also a third set of chains, not time bound, that can be activated by tapping leader three times.

Examples:

## Single tap leader chains

- `leader f`, this will activate *easy motion* (vscode)
- `leader z`, this will center the cursor in the middle of the screen (vscode)
- `leader d d`, this will execute a *delete line* command
- `leader o o`, this will execute a *insert line below* command
- `leader g g`, this will put the cursor at the top of the document
- `leader c i w`, this will execute a *change inside word* command
- etc.. see `user_leader.c` for the full list


## Double tap leader chains

- `leader leader n`, this will print ` != `
- `leader leader a`, this will print ` && `
- `leader leader o`, this will print ` || `
- etc.. see `user_leader.c` for the full list

# Status

- HillSide: **OK**
- Kyria: **OK**
- Moonlander: **OK**

# Setup

- Clone the QMK repository and install/setup
- Symlink, see `symlink-howto.md`

Then compile Kyria, Hillside or Moonlander:

- `make splitkb/kyria/rev1:jaykay`
- `make handwired/hillside/0_1:jaykay`
- `make moonlander:jaykay`

# Keymap

(Generated with `https://github.com/jurgen-kluft/go-qmk-keymap`)

![](keymap.svg)
