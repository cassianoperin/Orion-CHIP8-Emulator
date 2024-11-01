# CHIP-8 GUI with Nuklear

Port of chip8 emulator to use nuklear GUI.

## Improvements

1) Test games again (quirks and tests)
    * Breakout Camelo Cortez: quirk problem ingame
2) Insert the name of game loaded in the status bar OR window
3) Reduce the number of global variables
4) Rewrite DXYN function
5) 

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

3) Fullscreen lots of problems

4) Resize register texts
