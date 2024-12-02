# ORION CHIP-8 Emulator

CHIP-8 emulator written in C with Nuklear gui library.

## Improvements

1) Test games again (quirks and tests)
    * Breakout Camelo Cortez: quirk problem ingame
2) Insert the name of game loaded in the status bar OR window
3) Reduce the number of global variables
4) Rewrite DXYN function

## Problems
1) INPUT: When the first key is pressed, freeze the emulation by a second (with input_keyboard_remaps() enabled). Table and update value? Pointer?

## New GUI version

1) quirk_display_wait and menu problems:
 	vsync not good yet (main)
		// Pause when over main menu to be able to priorize menu rendering and activate vsync
		if (nk_window_is_active(ctx, "MainMenu")) {
			cpu_pause = true;
		} else {
			cpu_pause = false;
		}

2) Update SDL to 3

3) Fullscreen
	a) Menu resolution enabled in fullscreen?
	b) Canvas.painter (gui_emu.c) doesn't draw correctly with float numbers

4) Test draw float squares values on high dpi

5) Replace manual processing in DXYN by a XOR.

