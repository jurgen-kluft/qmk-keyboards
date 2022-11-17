# Windows

On Windows you can use `mklink`:
 
In `"qmk_firmware\keyboards\splitkb\kyria\keymaps"`:
 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\kyria\keymaps\jaykay\`

In `"qmk_firmware\keyboards\splitkb\aurora\sweep\keymaps"`:
 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\sweep\keymaps\jaykay\`

In `"qmk_firmware\keyboards\moonlander\keymaps"`:
 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\moonlander\keymaps\jaykay\`

In `"qmk_firmware\users"`:
 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\shared\jaykay\`

 
# Mac OS

On Mac OS you can use `ln` (-s is for symbolic link):

`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/kyria/keymaps/jaykay $HOME/dev.qmk/keyboards/splitkb/kyria/keymaps`
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/sweep/keymaps/jaykay $HOME/dev.qmk/keyboards/splitkb/aurora/sweep/keymaps`
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/hillside/keymaps/jaykay $HOME/dev.qmk/keyboards/handwired/hillside/0_1/keymaps`
`ln -s $HOME/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/shared/jaykay $HOME/dev.qmk/users`