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


## REFORMA

1) quirk_display_wait: no menu tem que setar o vsync!!! como é feito no inicio
 vsync nao ta bom ainda (main)
		// Pause when over main menu to be able to priorize menu rendering and activate vsync
		if (nk_window_is_active(ctx, "MainMenu")) {
			cpu_pause = true;
		} else {
			cpu_pause = false;
		}

2) Struct of opcodes and history

3) GUI Opcodes

4) Ver local correto dos includes .h ou .c

5) Update SDL to 3

6) Implement themes

7) Windows doesn't close

8) Add PAUSE to emulation menu

9) Opcode is wrong in the registers info (remove?)