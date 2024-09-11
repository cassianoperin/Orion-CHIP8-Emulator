# CHIP-8 GUI with Nuklear

Port of chip8 emulator to use nuklear GUI.

## Improvements

1) Test games again (quirks and tests)
    * Breakout Camelo Cortez: quirk problem ingame
2) Create a way to show Emulator Information
3) Insert the name of game loaded in the status bar OR window
4) Reduce the number of global variables
5) Debug Window
6) Rewrite DXYN function

## Problems

* INPUT: When the first key is pressed, freeze the emulation by a second (with input_keyboard_remaps() enabled). Table and update value? Pointer?

# Reestruturação de janelas:

1) quirk_display_wait quebrado, draw todo errado
2) Draw para a main window remover
3) show_logo