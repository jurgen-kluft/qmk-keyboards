# Pre-requisites

Make sure you have installed the necessary software to be able to compile the firmware.

## Windows

On Windows install QMK Toolbox.

For Elore, you will need to clone the following repository:

 
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
