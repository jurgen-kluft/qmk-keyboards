# Windows

On Windows you can use `mklink`:
 
In `"qmk_firmware\keyboards\splitkb\kyria\keymaps"`:
 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\kyria\keymaps\jaykay\`

In `"qmk_firmware\keyboards\splitkb\aurora\sweep\keymaps"`:
 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\sweep\keymaps\jaykay\`

In `"qmk_firmware\keyboards\splitkb\elora\keymaps"`:
 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\elora\keymaps\jaykay\`

In `"qmk_firmware\keyboards\moonlander\keymaps"`:
 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\moonlander\keymaps\jaykay\`

In `"qmk_firmware\users"`:
 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\shared\jaykay\`

 
# Mac OS

On Mac OS you can use `ln` (-s is for symbolic link):

Dilemma
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/dilemma/keymaps/jaykay $HOME/qmk_firmware/keyboards/bastardkb/dilemma/keymaps`

Hillside
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/hillside/keymaps/jaykay $HOME/qmk_firmware/keyboards/handwired/hillside/0_1/keymaps`

Kyria
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/kyria/keymaps/jaykay $HOME/qmk_firmware/keyboards/splitkb/kyria/keymaps`

Sweep
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/sweep/keymaps/jaykay $HOME/qmk_firmware/keyboards/splitkb/aurora/sweep/keymaps`

Elora (vial-qmk, from `https://github.com/splitkb/vial-qmk`, branch `elora`)
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/elora/keymaps/jaykay $HOME/vial-qmk/keyboards/splitkb/elora/keymaps`

Shared (QMK)
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/shared/jaykay $HOME/qmk_firmware/users`

Shared (Vial-QMK)
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/shared/jaykay $HOME/vial-qmk/users`