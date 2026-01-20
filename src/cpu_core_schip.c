#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu_core_schip.h"

// --------------------------- SCHIP 1.0 --------------------------- //

// SCHIP 1.0 - 00FD
// Exit Emulator
void opc_schip_00FD(void) {

	if (cpu_debug_mode)
        sprintf(cpu_debug_message, "SCHIP 00FD: Exit emulator");
	
	// Reset
	cpu_initialize();

	// Update StatusBar message
	strcpy(gui_statusbar_msg, "No ROM loaded");
}


// SCHIP 1.0 - 00FE
// Enable Low-Res Mode (64 x 32 resolution)
void opc_schip_00FE(void) {
	// Disable SCHIP Mode
	cpu_SCHIP_mode = true;
	cpu_SCHIP_LORES_mode = true;
	
	// Set the clock to CHIP-8 Speed
	CPU_CLOCK = CHIP8_DEFAULT_CLOCK;

	// Set SCHIP Resolution
	display_EMULATOR_RES_X = 64;
	display_EMULATOR_RES_Y = 32;
	if ( !cpu_debug_mode ) {
		display_EMULATOR_RES_SCALE = 10;
	} else {
		display_EMULATOR_RES_SCALE = 8;
	}

	// Clear the screen when changing graphic mode
	for ( int i = 0 ; i < (int)( sizeof(display_pixels) / sizeof(display_pixels[0])) ; i++ ) {
		display_pixels[i] = display_pixel_OFF_color;
	}

	if ( cpu_debug_mode )
		printf(cpu_debug_message, "SCHIP 00FE: Enable low res (64 x 32) mode");
}


// SCHIP 1.0 - 00FF
// Enable High-Res Mode (128 x 64 resolution)
// Enable SCHIP Mode
void opc_schip_00FF(void) {
	cpu_SCHIP_mode = true;
	cpu_SCHIP_LORES_mode = false;

	// Set the clock to SCHIP
	CPU_CLOCK = SCHIP_DEFAULT_CLOCK;

	// Set SCHIP Resolution
	display_EMULATOR_RES_X = 128;
	display_EMULATOR_RES_Y = 64;
	if ( !cpu_debug_mode ) {
		display_EMULATOR_RES_SCALE = 5;
	} else {
		display_EMULATOR_RES_SCALE = 4;
	}

	// Clear the screen when changing graphic mode
	for ( int i = 0 ; i < (int)( sizeof(display_pixels) / sizeof(display_pixels[0])) ; i++ ) {
		display_pixels[i] = display_pixel_OFF_color;
	}

    if ( cpu_debug_mode )
		printf(cpu_debug_message, "SCHIP 00FF: Enable high res (128 x 64) mode");
}


// SCHIP - DXY0 - draw 16x16 sprites
// Draw n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void opc_schip_DXY0(unsigned char x, unsigned char y, unsigned char n) {
	
	// Draw in Chip-8 Low Resolution mode
    unsigned short gpx_position, row, column = 0;
    unsigned char Vx, Vy, byte, bit, bit_value, sprite = 0, sprite2 = 0;

	// Is NOT allowed to use the vx/vy directly in the draw loop itself, you must make a copy of the coordinates
	// because either of them could be the vf register
	Vx = V[x];
	Vy = V[y];

	n = 16;

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Dxyn: DRAW GRAPHICS - Address I: %d Position V[x(%d)]: %d V[y(%d)]: %d N: %d", I, x, V[x], y, V[y], n);
	
	// Clear the carry before start
	V[0xF] = 0;

	// Print N Bytes from address I in V[x]V[y] position of the screen
	// Each byte is a line of 8 bits

	// // Print header of pixels to console
	// if ( debug_pixels )
	// 	printf("Sprite (x3): Position Line: %d\tColumn:%d\tBytes: %d\n", V[y]%display_EMULATOR_RES_Y, V[x]%display_EMULATOR_RES_X, n);
	
  	for (byte = 0; byte < n; byte++)
  	{
		
		// if in LOW-RES (16x8), update to traditional sprite storage mode in memory
		// if ( cpu_SCHIP_LORES_mode) {
		// 	sprite = Memory[I+byte];
		// } else {
			// if in HI-RES (16x16) get the bytes in pairs
			sprite = Memory[I+(byte*2)];
			sprite2 = Memory[I+(byte*2)+1];
		// }

		// // Print byte to console
		// if ( debug_pixels )
		// 	print_bin(sprite);

		// --------- Row --------- //
		if ( quirk_Wrap_Dxyn ) { 
			// Slit the sprite between screen top and down
			// if line (y) plus n bytes > 31 or > 63
			row = (Vy + byte) % display_EMULATOR_RES_Y;
		} else {
			// Do not split the sprite between screen top and down
			// If the line (y) plus n bytes > 31 or > 63, then do not print
			row = ((Vy % display_EMULATOR_RES_Y) + byte);
			if ( row > display_EMULATOR_RES_Y - 1 ) {
				sprite = 0;
			}
		}

		// Always print 8 bits of the byte
		for (bit = 0; bit < 8; bit++)
		{
			// Bit
			bit_value = (sprite & 0x80) >> 7;	// MSB (Most Significant Bit), 1 will draw, 0 don't
			
			// ------- Column -------- //
			if ( quirk_Wrap_Dxyn ) {
				column = (Vx + bit) % display_EMULATOR_RES_X;
			} else {
				// Do not split the sprite between screen right and left
				// If the row (x) plus number of bits > 63, then do not print
				column = ((Vx % display_EMULATOR_RES_X) + bit);
				if ( column > display_EMULATOR_RES_X - 1 ) {
					bit_value = 0;
				}
			}

			// Translate the x and Y to the Graphics Vector
			gpx_position = (row * display_EMULATOR_RES_X) + column; 

			if (bit_value == 1) {
				// Set colision case graphics[index] is already 1
				if (display_pixels[gpx_position] == display_pixel_ON_color) {
					V[0xF] = 1;
				}
				// XOR to toggle between the two colors (ON/OFF)
				display_pixels[gpx_position] ^= display_pixel_ON_color;
			}

			// Shift left to get the next bit on the MSB (Most Significant Bit) positon
			sprite <<= 1;
		}


		// if ( !cpu_SCHIP_LORES_mode ) {
			// Print 8 bits from SECOND SPRITE
			for ( bit = 0; bit < 8; bit++ ) {

				// Get the value of the byte
				bit_value = (sprite2 & 0x80) >> 7;
				// bit_value = sprite2 >> (7 - bit) & 1;

				// Set the index to write the 8 bits of each pixel
				// gfx_index := uint16(gpx_position) + uint16(8+bit) + (byte * uint16(Global.SizeX))
				gpx_position = (row * display_EMULATOR_RES_X) + (column+bit+1); 


				// If tryes to draw bits outside the vector size, ignore
				if ( gpx_position >= display_EMULATOR_RES_X * display_EMULATOR_RES_Y) {
					printf("Position: %d\tBigger than 2048 or 8192 x: %d y:%d \n",gpx_position, display_EMULATOR_RES_X, display_EMULATOR_RES_Y );
					// exit(2);
				}

				if (bit_value == 1) {
					// Set colision case graphics[index] is already 1
					if (display_pixels[gpx_position] == display_pixel_ON_color) {
						V[0xF] = 1;
					}
					// XOR to toggle between the two colors (ON/OFF)
					display_pixels[gpx_position] ^= display_pixel_ON_color;
				}

				// Shift left to get the next bit on the MSB (Most Significant Bit) positon
				sprite2 <<= 1;

			}
		// }

 	}

	// // Print a new line after the pixel
	// if ( debug_pixels )
	// 	printf("\n");

	// Ask to draw screen
	cpu_draw_flag = true;	
}

// SCHIP 1.0 - FX75
// Store V0 through VX to HP-48 RPL user flags (X <= 7).
void opc_schip_FX75(unsigned char x) {
	for (int i = 0; i <= x; i++) {
		RPL[i] = V[i];
	}

	if (cpu_debug_mode)
	sprintf(cpu_debug_message, "SCHIP Fx75: Store registers V[0] through V[x(%d)] in RPL user flags from 0 to %d", x, x);

}

// SCHIP 1.0 - FX85
// Read V0 through VX to HP-48 RPL user flags (X <= 7).
void opc_schip_FX85(unsigned char x) {
	for (int i = 0; i <= x; i++) {
		V[i] = RPL[i];
	}

 if (cpu_debug_mode)
        sprintf(cpu_debug_message, "SCHIP FX85: Read registers V[0] through V[x(%d)] and store in RPL user flags", x);
}


// --------------------------- SCHIP 1.1 --------------------------- //

// SCHIP 1.1 - 00CN
// Scroll display N lines down
void opc_schip_00CN(unsigned char n) {

	unsigned int i, shift = n * 128;

	cpu_SCHIP_mode = true;

	// // If in SCHIP Low Res mode, scroll N/2 lines only
	// if scrollQuirks_00CN_00FB_00FC {
	// 	shift = (int(x) * 128) / 2
	// }

	// Shift Right N lines on Graphics Array
	for ( i = (display_EMULATOR_RES_X * display_EMULATOR_RES_Y) - 1 ; i >= shift ; i-- )
	{
		display_pixels[i] = display_pixels[i-shift];
	}

	// Clean the shifted display bytes
	for ( i = 0 ; i < shift ; i++ ) {
		display_pixels[i] = display_pixel_OFF_color;
	}

	if ( cpu_debug_mode )
		printf(cpu_debug_message, "SCHIP 00CN: Scroll display %d lines down", n);
}


// SCHIP 1.1 - 00FB
// Scroll display 4 pixels right (hi-res). In lo-res, scroll 2 pixels right.
void opc_schip_00FB(void) {
    unsigned int width  = cpu_SCHIP_mode ? 128 : 64;
    unsigned int height = cpu_SCHIP_mode ? 64  : 32;

    unsigned int shift = cpu_SCHIP_LORES_mode ? 2 : 4;

	// Shift Right N pixels on Graphics Array
    for (unsigned int y = 0; y < height; y++) {
        unsigned int base = y * width;

		// Shift pixels to the right (from the end to the beginning)
        for (int x = width - 1; x >= (int)shift; x--) {
            display_pixels[base + x] = display_pixels[base + x - shift];
        }

        // Clear the first 'shift' pixels of the line
        for (unsigned int x = 0; x < shift; x++) {
            display_pixels[base + x] = display_pixel_OFF_color;
        }
    }

    cpu_draw_flag = true;

    if (cpu_debug_mode) {
        sprintf(cpu_debug_message, "SCHIP 00FB: Scroll display right");
    }
}


// SCHIP 1.1 - 00FC
// Scroll 4 pixels left (hires), 2 pixels (lores)
void opc_schip_00FC(void) {
    unsigned int width  = cpu_SCHIP_mode ? 128 : 64;
    unsigned int height = cpu_SCHIP_mode ? 64  : 32;

	// Shift 4 pixels left (hires) or 2 pixels left (lores)
    unsigned int shift = cpu_SCHIP_LORES_mode ? 2 : 4;

	// Shift Left N pixels on Graphics Array
    for (unsigned int y = 0; y < height; y++) {
        unsigned int base = y * width;

        // Move line pixels to the left
        for (unsigned int x = 0; x < width - shift; x++) {
            display_pixels[base + x] = display_pixels[base + x + shift];
        }

        // Clean the last (shift value) pixels of the line
        for (unsigned int x = width - shift; x < width; x++) {
            display_pixels[base + x] = display_pixel_OFF_color;
        }
    }

    cpu_draw_flag = true;

    if (cpu_debug_mode)
        sprintf(cpu_debug_message, "SCHIP 00FC: Scroll display left");
}


// SCHIP 1.1 - Fx30 - LD F, Vx
// Set I = location of sprite for digit Vx.
// The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.
void opc_schip_FX30(unsigned char x) {

	// Load SCHIP font. Start from Memory[80]
	I = 80 + V[x]*10;

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "SCHIP Fx30: Set I(%X) = location of sprite for digit V[x(%d)]:%d (*10)", I, x, V[x] );
}



