#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu_core_schip.h"

// // 00EE - RET
// // Return from a subroutine
// // The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
// // Need to incremente PC (PC+=2) after receive the value from Stack
// void opc_chip8_00EE() {
// 	PC = Stack[SP] + 2;
// 	SP --;
// 	if ( cpu_debug_mode )
// 		sprintf(cpu_debug_message, "CHIP-8 00EE: Return from a subroutine (PC=0x%04X)", PC);
// }


// SCHIP - 00FF
// Enable High-Res Mode (128 x 64 resolution)
// Enable SCHIP Mode
void opc_schip_00FF(void) {
	cpu_SCHIP_mode = true;
	cpu_SCHIP_LORES_mode = false;
	// scrollQuirks_00CN_00FB_00FC = false;

	// Set the clock to SCHIP
	CPU_CLOCK = 1500;

	// Set SCHIP Resolution
	display_SCREEN_WIDTH_X = 128;
	display_SCREEN_HEIGHT_Y = 64;

	// if Resize_Quirk_00FE_00FF {
	// 	// Clear the screen when changing graphic mode
	// 	Graphics = [128 * 64]byte{}
	// }

    SDL_SetWindowSize (window, display_SCREEN_WIDTH_X * display_SCALE, display_SCREEN_HEIGHT_Y * display_SCALE);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	PC += 2;

    if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "SCHIP 00FF: Enable high res (128 x 64) mode");

}



// Dxyn - DRW Vx, Vy, nibble
// Draw n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.

// SCHIP - DXY0
// SCHIP in HI-RES will draw 16x16 sprites
// SCHIP LOW-RES MODE will draw 16x8 sprites
void opc_schip_DXY0(void) {
		
	// Draw in Chip-8 Low Resolution mode
    unsigned short gpx_position, row, column = 0;
    unsigned char x, y, n, byte, bit, bit_value, sprite = 0;

	x = (Opcode & 0x0F00) >> 8;
	y = (Opcode & 0x00F0) >> 4;
    n = (Opcode & 0x000F);

	n = 16;

	if ( cpu_debug_mode )
		// sprintf(cpu_debug_message, "CHIP-8 Dxy0: DRAW GRAPHICS - Address I: %d Position V[x(%d)]: %d V[y(%d)]: %d N: %d", I, x, V[x], y, V[y], n);
		printf("CHIP-8 Dxy0: DRAW GRAPHICS - Address I: %d Position V[x(%d)]: %d V[y(%d)]: %d N: %d\n", I, x, V[x], y, V[y], n);

	// Clear the carry before start
	V[0xF] = 0;

	// Print N Bytes from address I in V[x]V[y] position of the screen
	// Each byte is a line of 8 bits
  	for (byte = 0; byte < n; byte++)
  	{
		// Get the sprite from memory (8 bits / 1 byte)
		sprite = Memory[I + byte];

		printf("Sprite: %X\n", sprite);

		// --------- Row --------- //
		// if ( quirk_Clipping_Dxyn ) { 
		// 	// Do not split the sprite between screen top and down
		// 	// If the line (y) plus n bytes > 31, then do not print
		// 	row = ((V[y] % 32) + byte);
		// 	if ( row > 31 ) {
		// 		sprite = 0;
		// 	}
		// } else {
		// 	// Slit the sprite between screen top and down
			// if line (y) plus n bytes > 31
			row = (V[y] + byte) % display_SCREEN_HEIGHT_Y;
		// }

		// Always print 8 bits of the byte
		for (bit = 0; bit < 8; bit++)
		{
			// Bit
			bit_value = (sprite & 0x80) >> 7;	// MSB (Most Significant Bit), 1 will draw, 0 don't
			
			// // ------- Column -------- //
			// if ( quirk_Clipping_Dxyn ) {
			// 	// Do not split the sprite between screen right and left
			// 	// If the row (x) plus number of bits > 63, then do not print
			// 	column = ((V[x]% 64) + bit);
			// 	if ( column > 63 ) {
			// 		bit_value = 0;
			// 	}
			// } else {
				column = (V[x] + bit) % display_SCREEN_WIDTH_X;
			// }

			// Translate the x and Y to the Graphics Vector
			gpx_position = (row * display_SCREEN_WIDTH_X) + column; 

			if ( gpx_position > 8192 ) {
				printf("gpx_position: %d\trow: %d\tcolumn: %d\n\n\n\n", gpx_position, row, column);
				gpx_position = 8192;
				exit(2);
			}

			// If bit=1, test current graphics[index], if is already set, mark v[F]=1 (collision)
			if ( bit_value  == 1 ) {
				// Set colision case graphics[index] is already 1
				if ( display_pixels[gpx_position] == display_pixel_ON_color ) {
					V[0xF] = 1;
					display_pixels[gpx_position] = display_pixel_OFF_color; 
				} else {
          			display_pixels[gpx_position] = display_pixel_ON_color;
				}
			}

			// Shift left to get the next bit on the MSB (Most Significant Bit) positon
			sprite <<= 1;
		}
 	 }

	PC += 2;

	// Ask to draw screen
	cpu_draw_flag = true;
}
