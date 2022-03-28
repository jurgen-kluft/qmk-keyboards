# Windows

On Windows you can use `mklink`:
 
In `"qmk_firmware\keyboards\splitkb\kyria\keymaps"`:

 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\kyria\keymaps\jaykay\`

In `"qmk_firmware\users"`:

 `mklink /D jaykay E:\Dev.Go\src\github.com\jurgen-kluft\qmk-keyboards\shared\jaykay\`

 
# Mac OS

On Mac OS you can use `ln` (-s is for symbolic link):

`ln -s /Users/@user/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/kyria/keymaps/jurgen-kluft /Users/@user/dev.qmk/keyboards/kyria/keymaps`

`ln -s /Users/@user/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/hillside/keymaps/jurgen-kluft /Users/@user/dev.qmk/keyboards/handwired/hillside/0_1/keymaps`

`ln -s /Users/@user/dev.go/src/github.com/jurgen-kluft/qmk-keyboards/shared/jaykay /Users/@user/dev.qmk/users`