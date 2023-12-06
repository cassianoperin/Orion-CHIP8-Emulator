#pragma once
#include "typedef.h"

// // --------------------------------- External Variables --------------------------------- //
// // Display
// extern unsigned char display_SCREEN_WIDTH_X;
// extern unsigned char display_SCREEN_HEIGHT_Y;
// // CPU
// extern unsigned int  CPU_CLOCK;

// ---------------------------------- Global Variables ---------------------------------- //
// Legacy Opcodes and Quirks
// Chip8
bool quirk_VF_Reset_8xy1_8xy2_8xy3;		// The AND, OR and XOR opcodes (8XY1, 8XY2 and 8XY3) reset the flags register to zero
bool quirk_Memory_legacy_Fx55_Fx65; 	// Enable original Chip-8 Fx55 and Fx65 opcodes (increases I)
										// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#fx55-and-fx65-store-and-load-memory
bool quirk_display_wait;				// Drawing sprites to the display waits for the vertical blank interrupt, limiting their speed to max 60 draws per second
bool quirk_Clipping_Dxyn;				// DXYN sprite wrap in Bowling game
										// Sprites drawn at the bottom edge of the screen get clipped instead of wrapping around to the top of the screen.
										// When clipping is off, the test checks if sprites get rendered at the right coordinates on the other side of the screen.
										// This also tests that sprites drawn at coordinates of x > 63 and/or y > 31 are rendered at x % 64 and y % 32. If any of these checks fail, the test will show ERR
bool quirk_Shifting_legacy_8xy6_8xyE;	// Enable original Chip-8 8xy6 and 8xyE opcodes
										// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#8xy6-and-8xye-shift

// // SCHIP
bool quirk_Spacefight2091_Fx1E;			// FX1E undocumented feature needed by Spacefight 2091! 
bool quirk_Resize_SCHIP_00FE_00FF;		// Resize_Quirk_00FE_00FF - Clears the screen - Must be set to True always
bool quirk_Scroll_SCHIP_00CN_00FB_00FC;	// Shift only 2 lines
bool quirk_Jump_with_offset_Bnnn;		// Bnnn behavior in some CHIP-48 and SUPER-CHIP that sum the value of V[x] instead of V[0]
bool quirk_LoRes_Wide_Sprite_Dxy0;		// DXY0_loresWideSpriteQuirks - Draws a 16x16 sprite even in low-resolution (64x32) mode, row-major
bool quirk_ClockProgram_fonts;			// To avoid glitches on FFFFF display, the memory used by SCHIP fonts can't be loaded
// // ETI
// bool quirk_ETI660_64x32_screen;			// Enable screen adjustment to 64x32 instead of default 64x48 ETI-660 HW
// 										// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#bnnn-jump-with-offset
// // bool	Keyboard_slow_press;			// Used by some programs that needs a slower key press rate


// -------------------------------------- Functions ------------------------------------- //
void handle_quirks(char *game_signature);


