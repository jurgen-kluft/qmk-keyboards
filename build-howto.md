# Pre-requisites

Make sure you have installed the necessary software to be able to compile the firmware.

## Windows

On Windows install QMK Toolbox.

### QMK

Then clone the QMK firmware repository:

- `https://github.com/qmk/qmk_firmware`

Then update all submodules using `git submodule update --init --recursive`.

### Elora, Vial (QMK)

For Elora, you will need to clone the following repository:

- `https://github.com/splitkb/vial-qmk`

You should clone this repository and then switch to branch `elora`.
Then update all submodules using `git submodule update --init --recursive`.
 
## Mac OS

On Mac OS:

- `brew install qmk/qmk/qmk`
- `qmk setup`, y to all prompts


## Compile a keymap

`qmk compile -kb <keyboard> -km <keymap>`

# Sweep

## Windows

On Windows using QMKSys:

```cpp
make splitkb/aurora/sweep:jaykay:flash CONVERT_TO=promicro_rp2040
```

## Mac OS

```cpp
make splitkb/aurora/sweep:jaykay:flash CONVERT_TO=promicro_rp2040
```
