#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu_core_chip8.h"

// ---------------------------- CHIP-8 0xxx instruction set ---------------------------- //

// // 0NNN
// // Execute RCA 1802 machine language routine at address NNN
// func opc_chip8_0NNN(void) {
// 	// Not needed by any game, just for documentation
// }

// 00E0 - CLS
// Clear the display.
void opc_chip8_00E0(void) {
	// Initialization - Clean pixels array
	for ( int i = 0 ; i < (int)( sizeof(display_pixels) / sizeof(display_pixels[0])) ; i++ ) {
			display_pixels[i] = display_pixel_OFF_color;
	}

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 00E0: Clear the display");
}

// 00EE - RET
// Return from a subroutine
// The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer.
void opc_chip8_00EE(void) {
	 // Used to detect an stack Underflow
	char original_SP = SP;

	SP --;

	PC = Stack[SP];

	// If you decrease SP and its bigger than original value its because an underflow ocurred
	if ( SP > original_SP ) {
		sprintf(gui_statusbar_msg, "CHIP-8 00EE: Stack Underflow");
		cpu_rom_loaded = false;
		// Return to original menu state
		gui_menu_quirks_inactive = true;
	}

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 00EE: Return from a subroutine (PC=0x%04X)", PC);
}


// ---------------------------- CHIP-8 1xxx instruction set ---------------------------- //

// 1nnn - JP addr
// Jump to location nnn.
// The interpreter sets the program counter to nnn.
void opc_chip8_1NNN(unsigned short nnn) {
	PC = nnn;

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 1nnn: Jump to location 0x%04X", nnn);
}


// ---------------------------- CHIP-8 2xxx instruction set ---------------------------- //

// 2nnn - CALL addr
// Call subroutine at nnn.
// The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn.
void opc_chip8_2NNN(unsigned short nnn){
	Stack[SP] = PC;
	PC = nnn;
	SP++;

	// If you increase SP and its bigger than 15, than an overflow occurred
	if ( SP > 15 ) {
		sprintf(gui_statusbar_msg, "CHIP-8 2nnn: Stack Overflow");
		cpu_rom_loaded = false;
		// Return to original menu state
		gui_menu_quirks_inactive = true;
	}

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 2nnn: Call Subroutine at 0x%04X", PC);
}


// ---------------------------- CHIP-8 3xxx instruction set ---------------------------- //

// 3xnn - SE Vx, byte
// Skip next instruction if Vx = NN.
// The interpreter compares register Vx to nn, and if they are equal, increments the program counter by 2.
void opc_chip8_3XNN(unsigned char x, unsigned char nn) {

	if ( V[x] == nn ) {
		PC += 2;
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 3xnn: V[x(%d)]:(0x%02X) = nn(0x%02X), skip one instruction", x, V[x], nn);

	} else {
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 3xnn: V[x(%d)]:(0x%02X) != nn(0x%02X), do NOT skip one instruction", x, V[x], nn);

	}
}


// ---------------------------- CHIP-8 4xxx instruction set ---------------------------- //

// 4xnn - SNE Vx, byte
// Skip next instruction if Vx != nn.
// The interpreter compares register Vx to nn, and if they are not equal, increments the program counter by 2.
void opc_chip8_4XNN(unsigned char x, unsigned char nn) {

	if ( V[x] != nn ) {
		PC += 2;
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 4xnn: V[x(%d)]: 0x%02X != nn(0x%02X), skip one instruction", x, V[x], nn);

	} else {
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 4xnn: V[x(%d)]: 0x%02X = nn(0x%02X), DO NOT skip one instruction", x, V[x], nn);
	}
}


// ---------------------------- CHIP-8 5xxx instruction set ---------------------------- //

// 5xy0 - SE Vx, Vy
// Skip next instruction if Vx = Vy.
// The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2.
void opc_chip8_5XY0(unsigned char x, unsigned char y) {

	if ( V[x] == V[y] ){
		PC += 2;
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 5xy0: V[x(%d)]:%d EQUAL V[y(%d)]:%d, SKIP one instruction", x, V[x], y, V[y]);
	} else {
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 5xy0: V[x(%d)]:%d NOT EQUAL V[y(%d)]:%d, DO NOT SKIP one instruction", x, V[x], y, V[y]);
	}
}


// ---------------------------- CHIP-8 6xxx instruction set ---------------------------- //

// 6xnn - LD Vx, byte
// Set Vx = nn.
// The interpreter puts the value nn into register Vx.
void opc_chip8_6XNN(unsigned char x, unsigned char nn) {
	V[x] = nn;

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 6xnn: Set V[x(%d)] = 0x%02X", x, nn);
}


// ---------------------------- CHIP-8 7xxx instruction set ---------------------------- //

// 7xnn - ADD Vx, byte
// Set Vx = Vx + nn.
// Adds the value nn to the value of register Vx, then stores the result in Vx.
void opc_chip8_7XNN(unsigned char x, unsigned char nn) {
	V[x] += nn;

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 7xnn: Add the value nn(%d) to V[x(%d)]", nn, x);
}

// ---------------------------- CHIP-8 8xxx instruction set ---------------------------- //

// 8xy0 - LD Vx, Vy
// Set Vx = Vy.
// Stores the value of register Vy in register Vx.
void opc_chip8_8XY0(unsigned char x, unsigned char y) {
	V[x] = V[y];
	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 8xy0: Set V[x(%d)] to the value of V[y(%d)] = 0x%02X", x, y, V[y]);

}

// 8xy1 - Set Vx = Vx OR Vy.
// Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corresponding bits from two values,
// and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0.
void opc_chip8_8XY1(unsigned char x, unsigned char y) {
	V[x] |= V[y];

	if ( quirk_VF_Reset_8xy1_8xy2_8xy3 ) {
		V[0xF] = 0;
	}

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 8xy1: Set V[x(%d)]:%d OR V[y(%d)]:%d", x, V[x], y, V[y]);

}

// 8xy2 - AND Vx, Vy
// Set Vx = Vx AND Vy.
// Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corresponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0.
void opc_chip8_8XY2(unsigned char x, unsigned char y) {
	V[x] &= V[y];

	if ( quirk_VF_Reset_8xy1_8xy2_8xy3 ) {
		V[0xF] = 0;
	}

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 8xy2: Set V[x(%d)] to the result of V[x(%d)]:(0x%02x) AND V[y(%d)]:(0x%02X) = 0x%02X", x, x, V[x], y, V[y], V[x] &= V[y]);

}

// 8xy3 - XOR Vx, Vy
// Set Vx = Vx XOR Vy.
// Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corresponding bits from two values,
// and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0.
void opc_chip8_8XY3(unsigned char x, unsigned char y) {
	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 8xy3: Set V[x(%d)]:%d XOR V[y(%d)]:%d", x, V[x], y, V[y]);
	
	V[x] ^= V[y];

	if ( quirk_VF_Reset_8xy1_8xy2_8xy3 ) {
		V[0xF] = 0;
	}
}

// 8xy4 - ADD Vx, Vy
// Set Vx = Vx + Vy, set VF = carry.
// The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0.
// Only the lowest 8 bits of the result are kept, and stored in Vx.
// *** Flag needs to be set AFTER the ADD
void opc_chip8_8XY4(unsigned char x, unsigned char y) {

	// Test the new value and set the flag
	unsigned char sum = V[x] + V[y];	// Need in case of overflows (keep number between 0-255)
	unsigned char Vx_original = V[x];	// Necessary once the flag will be set AFTER the ADD

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 8xy4: Set V[x(%d)] = V[x(%d)]: 0x%02X + V[y(%d)]: 0x%02X", x, x, V[x], y, V[y]);

	// Old implementation, sum values, READ THE DOCS IN CASE OF PROBLEMS
	V[x] += V[y];

	if ( sum < Vx_original) {
		V[0xF] = 1;
	} else {
		V[0xF] = 0;
	}
}

// 8xy5 - SUB Vx, Vy
// Set Vx = Vx - Vy, set VF = NOT borrow.
// If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx.
// *** Flag needs to be set AFTER the ADD
void opc_chip8_8XY5(unsigned char x, unsigned char y) {

	unsigned char Vx_original = V[x];	// Necessary once the flag will be set AFTER the ADD

    if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 8xy5: Set V[x(%d)] = V[x(%d)]: 0x%02X - V[y(%d)]: 0x%02X", x, x, V[x], y, V[y]);

	V[x] -= V[y];

	// Now update the flag
	if ( Vx_original >= V[y] ) {
		V[0xF] = 1;
	} else {
		V[0xF] = 0;
	}
}

// 8xy6 - SHR Vx {, Vy}
// Set Vx = Vx SHR 1.
// If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2 (SHR).
void opc_chip8_8XY6(unsigned char x, unsigned char y) {

	unsigned int carry; // Set V[F] to the Least Significant Bit

	if ( quirk_Shifting_legacy_8xy6_8xyE ) {
		// modern CHIP-48 and SUPER-CHIP hardware
		carry = V[x] & 0x01;
		V[x] = V[x] >> 1;

	} else {
		// original COSMAC VIP hardware
		V[x] = V[y];
		carry = V[x] & 0x01;
		V[x] = V[x] >> 1;
	}

	// Now update the flag
	V[0xF] = carry; 

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 8xy6: Set V[x(%d)] SHIFT RIGHT 1 = 0x%02X", x, V[x]);		

}

// 8xy7 - SUBN Vx, Vy
// Set Vx = Vy - Vx, set VF = NOT borrow.
// If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx.
// *** Update the flag AFTER the SUBN with the V[x] RESULT and not original
void opc_chip8_8XY7(unsigned char x, unsigned char y) {

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 8xy7: Set V[x(%d)]:%d = V[y(%d)]:%d - V[x(%d)]:%d\t\t = %d", x, V[x], y, V[y], x, V[x], V[y] - V[x]);

	V[x] = V[y] - V[x];

	// Now update the flag
	if ( V[x] > V[y] ) {
		V[0xF] = 0;
	} else {
		V[0xF] = 1;
	}
}

// 8xyE - SHL Vx {, Vy}
// Set Vx = Vx SHL 1.
// If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2.
void opc_chip8_8XYE(unsigned char x, unsigned char y) {

	unsigned int carry = V[x] >> 7; // Set V[F] to the Most Important Bit

	if ( quirk_Shifting_legacy_8xy6_8xyE ) {
		// modern CHIP-48 and SUPER-CHIP hardware
		V[x] = V[x] << 1;

	} else {
		// original COSMAC VIP hardware
		V[x] = V[y];
		V[x] = V[x] << 1;
	}

	// // Now update the flag
	V[0xF] = carry; 
	
	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 8xyE: Set V[x(%d)] SHIFT LEFT 1 =  0x%02X ", x, V[x]);

}

// ---------------------------- CHIP-8 9xxx instruction set ---------------------------- //

// 9xy0 - SNE Vx, Vy
// Skip next instruction if Vx != Vy.
// The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2.
void opc_chip8_9XY0(unsigned char x, unsigned char y) {

	if ( V[x] != V[y] ) {
		PC += 2;

		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 9xy0: V[x(%d)]:%02X != V[y(%d)]: 0x%02X, SKIP one instruction", x, V[x], y, V[y]);
	} else {
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 9xy0: V[x(%d)]:%02X = V[y(%d)]: 0x%02X, DO NOT SKIP one instruction", x, V[x], y, V[y]);
	}
}


// ---------------------------- CHIP-8 Axxx instruction set ---------------------------- //

// Annn - LD I, addr
// Set I = nnn.
// The value of register I is set to nnn.
void opc_chip8_ANNN(unsigned short nnn) {
	I = nnn;

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Annn: Set I = 0x%04X", I);
}


// ---------------------------- CHIP-8 Bxxx instruction set ---------------------------- //

// Bnnn - JP V0, addr
// Jump to location nnn + V0.
// The program counter is set to nnn plus the value of V0.
void opc_chip8_BNNN(unsigned short nnn, unsigned char x) {

	// Normal Chip8 Bnnn Behavior
	if ( !quirk_Jump_with_offset_Bnnn ) {
		PC = nnn + (unsigned short)V[0];
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 Bnnn: Jump to location nnn(%d) + V[0(%d)]", nnn, V[0]);

	// Bnnn_jump_with_offset quirk, sum V[x] instead of V[0]
	} else {
		PC = nnn + (unsigned short)V[x];
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 Bnnn: Jump to location nnn(%d) + V[x(%d)]", nnn, V[x]);
	}
}


// ---------------------------- CHIP-8 Cxxx instruction set ---------------------------- //

// Cxnn - RND Vx, byte
// Set Vx = random byte AND nn.
// The interpreter generates a random number from 0 to 255, which is then ANDed with the value nn. The results are stored in Vx. See instruction 8xy2 for more information on AND.
void opc_chip8_CXNN(unsigned char x, unsigned char nn) {
	// V[x] = (rand() % 255) & nn;
	V[x] = rand() & nn;

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Cxnn: V[x(%d)] = %d (random byte AND nn(%d)) = %d", x, V[x], nn, V[x]);
}


// ---------------------------- CHIP-8 Dxxx instruction set ---------------------------- // NOVA MINHA

// Dxyn - DRW Vx, Vy, nibble
// Draw n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
void opc_chip8_DXYN(unsigned char x, unsigned char y, unsigned char n) {
		
	// Draw in Chip-8 Low Resolution mode
    unsigned short gpx_position, row, column = 0;
    unsigned char Vx, Vy, byte, bit, bit_value, sprite = 0;

	// Is NOT allowed to use the vx/vy directly in the draw loop itself, you must make a copy of the coordinates
	// because either of them could be the vf register
	Vx = V[x];
	Vy = V[y];

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Dxyn: DRAW GRAPHICS - Address I: %d Position V[x(%d)]: %d V[y(%d)]: %d N: %d", I, x, V[x], y, V[y], n);
	
	// Clear the carry before start
	V[0xF] = 0;

	// Print N Bytes from address I in V[x]V[y] position of the screen
	// Each byte is a line of 8 bits

	// Print header of pixels to console
	if ( debug_pixels )
		printf("Sprite (x3): Position Line: %d\tColumn:%d\tBytes: %d\n", V[y]%64, V[x]%64, n);
	
  	for (byte = 0; byte < n; byte++)
  	{
		// Get the sprite from memory (8 bits / 1 byte)
		sprite = Memory[I + byte];

		// Print byte to console
		if ( debug_pixels )
			print_bin(sprite);

		// --------- Row --------- //
		if ( quirk_Clipping_Dxyn ) { 
			// Do not split the sprite between screen top and down
			// If the line (y) plus n bytes > 31, then do not print
			row = ((Vy % 32) + byte);
			if ( row > 31 ) {
				sprite = 0;
			}
		} else {
			// Slit the sprite between screen top and down
			// if line (y) plus n bytes > 31
			row = (Vy + byte) % 32;
		}

		// Always print 8 bits of the byte
		for (bit = 0; bit < 8; bit++)
		{
			// Bit
			bit_value = (sprite & 0x80) >> 7;	// MSB (Most Significant Bit), 1 will draw, 0 don't
			
			// ------- Column -------- //
			if ( quirk_Clipping_Dxyn ) {
				// Do not split the sprite between screen right and left
				// If the row (x) plus number of bits > 63, then do not print
				column = ((Vx% 64) + bit);
				if ( column > 63 ) {
					bit_value = 0;
				}
			} else {
				column = (Vx + bit) % 64;
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
 	 }


	// Print a new line after the pixel
	if ( debug_pixels )
		printf("\n");

	// Ask to draw screen
	cpu_draw_flag = true;


	// ------- Alternative version for testing purposes ------- //

	// uint8_t Vx = (Opcode & 0x0F00) >> 8;
	// uint8_t Vy = (Opcode & 0x00F0) >> 4;
	// uint8_t height = Opcode & 0x000F;

	// // Wrap if going beyond screen boundaries
	// uint8_t xPos = V[Vx] % 64;
	// uint8_t yPos = V[Vy] % 32;

	// V[0xF] = 0;

	// for (unsigned int row = 0; row < height; ++row)
	// {
	// 	uint8_t spriteByte = Memory[(int)I + row];

	// 	for (unsigned int col = 0; col < 8; ++col)
	// 	{
	// 		uint8_t spritePixel = spriteByte & (0x80 >> col);
	// 		int screenPixel = (yPos + row) * 64 + (xPos + col);

	// 		// Sprite pixel is on
	// 		if (spritePixel)
	// 		{
	// 			// Screen pixel also on - collision
	// 			if (display_pixels[screenPixel] == display_pixel_ON_color)
	// 			{
	// 				V[0xF] = 1;
	// 			}

	// 			// Effectively XOR with the sprite pixel
	// 			display_pixels[screenPixel] ^= 0xFF;
	// 		}
	// 	}
	// }
}

// ---------------------------- CHIP-8 Exxx instruction set ---------------------------- //

// Ex9E - SKP Vx
// Skip next instruction if key with the value of Vx is pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2.
void opc_chip8_EX9E(unsigned char x) {

	// Mask Key number to ensure the maximum of 16 keys
	V[x] = V[x] & 0xF;

	if ( Key[V[x]] == 1 ) {
		PC += 2;
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 Ex9E: Key[%d] pressed, skip one instruction", V[x]);

	} else {
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 Ex9E: Key[%d] NOT pressed, continue", V[x]);
	}
}

// ExA1 - SKNP Vx
// Skip next instruction if key with the value of Vx is not pressed.
// Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2.
void opc_chip8_EXA1(unsigned char x) {


	V[x] = V[x] & 0xF;

	if ( Key[V[x]] == 0 ) {
		PC += 2;
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 ExA1: Key[%d] NOT pressed, skip one instruction", V[x]);

	} else {
		// Key[V[x]] = 0;
		if ( cpu_debug_mode )
			sprintf(cpu_debug_message, "CHIP-8 ExA1: Key[%d] pressed, continue\n", V[x]);

	}
}



// ---------------------------- CHIP-8 Fxxx instruction set ---------------------------- //

// Fx07 - LD Vx, DT
// Set Vx = delay timer value.
// The value of DT is placed into Vx.
void opc_chip8_FX07(unsigned char x) {
	V[x] = DelayTimer;
	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Fx07: Set V[x(%d)] with value of DelayTimer(%02X)", x, DelayTimer);

}

// Fx0A - LD Vx, K
// Wait for a key press, store the value of the key in Vx.
// All execution stops until a key is pressed, then the value of that key is stored in Vx.
// V[x] must be updated just AFTER the RELEASE of the key
void opc_chip8_FX0A(unsigned char x) {

	unsigned int i;

	PC -= 2;

	// Map the key is pressed
	if ( !key_FX0A_pressed ) {

		// Decrease the PC added after fetch if key not pressed to keep emulation stopped


		for ( i = 0 ; i < sizeof(Key) ; i++ ) {
			if (Key[i] == 1) {
				// Update the temporary values
				key_FX0A = (unsigned char)i;
				key_FX0A_pressed = true;

				if ( cpu_debug_mode )
					sprintf(cpu_debug_message, "CHIP-8 Fx0A: Wait for a key press = (Key[%d] PRESSED)", i);
				
				// Stop after find the first key pressed
				break;
			}
		}

		// if 'key_FX0A_pressed' remain negative, print message
		if ( !key_FX0A_pressed ) {
			if ( cpu_debug_mode )
					sprintf(cpu_debug_message, "CHIP-8 Fx0A: Wait for a key press = (NOT PRESSED)");
		}

	// When a key is pressed
	} else  {

		// Check if the key is already released
		if (Key[key_FX0A] == 0) {

			// Update the V[x]
			V[x] = key_FX0A;
			PC += 2;

			if ( cpu_debug_mode )
				sprintf(cpu_debug_message, "CHIP-8 Fx0A: Wait for a key press = (Key[%d] PRESSED AND RELEASED)", key_FX0A);

			// Reset the temporary variables
			key_FX0A_pressed = false;

		} else {
			if ( cpu_debug_mode )
				sprintf(cpu_debug_message, "CHIP-8 Fx0A: Wait for a key press = (Key[%d] PRESSED AND NOT RELEASED)", key_FX0A);
		}
	}
}

// Fx15 - LD DT, Vx
// Set delay timer = Vx.
// DT is set equal to the value of Vx.
void opc_chip8_FX15(unsigned char x) {
	DelayTimer = V[x];
	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Fx15: Set delay timer = V[x(%d)]: 0x%02X", x, V[x]);

		// PC-=2;

}

// Fx18 - LD ST, Vx
// Set sound timer = Vx.
// ST is set equal to the value of Vx.
void opc_chip8_FX18(unsigned char x) {
	SoundTimer = V[x];
	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Fx18: Set sound timer = V[x(%d)]:%d",x, V[x]);

}

// Fx1E - ADD I, Vx
// Set I = I + Vx.
// The values of I and Vx are added, and the results are stored in I.
// ***
// Check FX1E (I = I + VX) buffer overflow. If buffer overflow, register
// VF must be set to 1, otherwise 0. As a result, register VF not set to 1.
// This undocumented feature of the Chip-8 and used by Spacefight 2091!
void opc_chip8_FX1E(unsigned char x) {
	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Fx1E: Add the value of V[x(%d)]: 0x%02X to I: (0x%04X)",x, V[x], I);


	// Workaround for a buggy rom version of Spacefight 2091
	if ( workaround_Fx1E_Spacefight ) {
		if ( I + (unsigned short)V[x] > 0xFFF ) { //4095 - Buffer overflow
			V[0xF] = 1;
			I = ( I + (unsigned short)V[x] ) - 4095;
		} else {
			V[0xF] = 0;
			I += (unsigned short)V[x];
		}
	// Normal opcode pattern
	} else {
		// Check for I buffer overflow (>4095)
		if ( I + (unsigned short)V[x] > 0xFFF ) {
			I = ( I + (unsigned short)V[x] ) - 4095;
		} else {
			I += (unsigned short)V[x];
		}
	}
}

// Fx29 - LD F, Vx
// Set I = location of sprite for digit Vx.
// The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.
void opc_chip8_FX29(unsigned char x) {

	V[x] = V[x] & 0xF;

	// Load CHIP-8 font. Start from Memory[0]   
	I = (unsigned short)V[x] * 5;
	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Fx29: Set I(%X) = location of sprite for digit V[x(%d)]:%d (*5)", I, x, V[x]);

}

// Fx33 - LD B, Vx
// BCD - Binary Code hexadecimal
// Store BCD representation of Vx in memory locations I, I+1, and I+2.
// set_BCD(Vx);
// Ex. V[x] = ff (maximum value) = 255
// memory[i+0] = 2
// memory[i+1] = 5
// memory[i+2] = 5
// % = modulus operator:
// 3 % 1 would equal zero (since 3 divides evenly by 1)
// 3 % 2 would equal 1 (since dividing 3 by 2 results in a remainder of 1).
void opc_chip8_FX33(unsigned char x) {
	Memory[I]   = V[x]  / 100;
	Memory[I+1] = (V[x] / 10)  % 10;
	Memory[I+2] = (V[x] % 100) % 10;
	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Fx33: Store BCD of V[x(%d)]:%d in memory locations I(%X):%d, I+1(%X):%d, and I+2(%X):%d", x, V[x], I, Memory[I], I+1, Memory[I+1], I+2, Memory[I+2]);

}

// Fx55 - LD [I], Vx
// Store registers V0 through Vx in memory starting at location I.
// The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I.
//
// Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.[d]
// In the original CHIP-8 implementation, and also in CHIP-48, I is left incremented after this instruction had been executed. In SCHIP, I is left unmodified.
void opc_chip8_FX55(unsigned char x) {
    unsigned char i;
	for ( i = 0; i <= x; i++ ) {
		Memory[I+i] = V[i];
	}

	// If needed, run the original Chip-8 opcode (not used in recent games)
	if ( quirk_Memory_legacy_Fx55_Fx65 ) {
		I = I + x + 1;
	}

	if ( cpu_debug_mode )
		sprintf(cpu_debug_message, "CHIP-8 Fx55: Put registers V[0] through V[x(0x%02X)] in memory starting at location I(0x%04X)",x, I);

        // for ( i = 0 ; i <= x ; i ++ ) {
		// 	printf("\t\t Memory[%04X] = 0x%02X\n", I+i, Memory[I+i]);
		// }
}


// Fx65 - LD Vx, [I]
// Read registers V0 through Vx from memory starting at location I.
// The interpreter reads values from memory starting at location I into registers V0 through Vx.
//// I is set to I + X + 1 after operation²
//// ² Erik Bryntse’s S-CHIP documentation incorrectly implies this instruction does not modify
//// the I register. Certain S-CHIP-compatible emulators may implement this instruction in this manner.
void opc_chip8_FX65(unsigned char x) {

	unsigned char i;

	for ( i = 0; i <= x; i++ ) {
		V[i] = Memory[I+i];
	}

	// If needed, run the original Chip-8 opcode (not used in recent games)
	if ( quirk_Memory_legacy_Fx55_Fx65 ) {
		I = I + x + 1;
	}

	if ( cpu_debug_mode ) 
		sprintf(cpu_debug_message, "CHIP-8 Fx65: Set registers V[0] through V[x(%d)] from memory starting at location I(0x%04X)",x, I);

		// for ( i = 0 ; i <= x ; i ++ ) {
		// 	printf("\t\t V[%02X] = 0x%02X\n", i, V[i]);
		// }

}
