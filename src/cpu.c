#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cpu.h"

void cpu_reset(void) {

	// Initialize
	cpu_initialize();

	// Load ROM into Memory
	load_rom(filename,  Memory, sizeof(Memory));

	// Get Game signature for Qwirks
	game_signature = get_game_signature(filename);
	printf("Signature:   %s\n", game_signature );

	// Check for Quirks
	handle_quirks(game_signature);

	// Load Fonts
	cpu_load_fonts();

	// Keyboard remaps
	input_keyboard_remaps();

	// Clean counters
	cycle_cpu = 0;
}

void cpu_initialize(void) {

	// Clock
	CPU_CLOCK  = CHIP8_DEFAULT_CLOCK;

	// Components
	memset(Memory, 0x00,  (sizeof(Memory) / sizeof(Memory[0])) );	// Clean Memory
	PC = 0x200;								// Start at 0x200 (default CHIP-8)
	Opcode = 0x00;
	memset(Stack, 0x00, sizeof(Stack));		// Clean Stack
	SP = 0x00;
	memset(V, 0x00, sizeof(V));				// Clean V Register
	I = 0x00;
	
	// Initialization - Clean pixels array
	for ( int i = 0 ; i < (int)( sizeof(display_pixels) / sizeof(display_pixels[0])) ; i++ ) {
			display_pixels[i] = display_pixel_OFF_color;
	}

	// New quirk pattern
	quirk_VF_Reset_8xy1_8xy2_8xy3	= true;		// VF Reset
	quirk_Memory_legacy_Fx55_Fx65	= true;		// Memory
	quirk_display_wait				= true;		// Display wait
	quirk_Clipping_Dxyn				= true;		// Clipping
	quirk_Shifting_legacy_8xy6_8xyE	= false;	// Shifting
	quirk_Jump_with_offset_Bnnn		= false;	// Jumping

	// // ETI
	// quirk_ETI660_64x32_screen        	= false;
	// // SCHIP
	// quirk_Spacefight2091_Fx1E            = false;
	// quirk_Resize_SCHIP_00FE_00FF         = true;
	// quirk_LoRes_Wide_Sprite_Dxy0         = false;
	// quirk_Scroll_SCHIP_00CN_00FB_00FC    = false;
	// quirk_ClockProgram_fonts             = false;
	// Keyboard_slow_press                  = false;

	// SCHIP Specific Variables
	cpu_SCHIP_mode 		 = false;
	cpu_SCHIP_LORES_mode = false;

	// Screen Size
	display_SCREEN_WIDTH_X  = 64;		// Number of Columns in Graphics
	display_SCREEN_HEIGHT_Y = 32;		// Number of Lines in Graphics
	
	// Keyboard
	memset(Key, 0x00, sizeof(Key));

	// Initialize random generator
	srand(time(NULL));

	// GUI
	gui_menu_quirks_inactive = false; // Enable Quirks menu

	// Debug
	// cpu_debug_mode	= false;
	cpu_pause		= false;
}

void cpu_load_fonts(void) {

	unsigned char i;

	// Load CHIP-8 8x5 fontset (Memory address 0-79)
	for ( i = 0; i < sizeof(Chip8Fontset); i++  ){
		Memory[i] = Chip8Fontset[i];
	}

	if ( !quirk_ClockProgram_fonts ) {
		// Load SCHIP 8x10 fontset (Memory address 80-240)
		for ( i = 0; i < sizeof(SCHIPFontset); i++ ) {
			Memory[i+80] = SCHIPFontset[i];
		}
	}
}

// Debug
void cpu_debug_print(void){ // Missing Delay Timers and Keys
	printf("Cycle: %d\tOpcode: %04X(%04X)\tPC: %04d(0x%04X)\tSP: %02X\tStack: [ %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ]\
	  V: [ %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X ]  I: 0x%04X  DT: 0x%02X  ST: 0x%02X\n", cycle_cpu, Opcode, Opcode & 0xF000, PC, PC,  SP, Stack[0],
	 Stack[1], Stack[2], Stack[3], Stack[4], Stack[5], Stack[6], Stack[7], Stack[8], Stack[9], Stack[10], Stack[11], Stack[12], Stack[13], Stack[14], Stack[15],
	  V[0], V[1], V[2], V[3], V[4], V[5], V[6], V[7], V[8], V[9], V[10], V[11], V[12], V[13], V[14], V[15], I, DelayTimer, SoundTimer);
}

// CPU Interpreter
void cpu_interpreter(void) {

	// Increment CPU Cycles
	cycle_cpu ++;

	// Increment opcodes per second counter
	cycle_counter_cpu ++;

	// Read the Opcode from PC and PC+1 bytes
	Opcode = (unsigned short)Memory[PC]<<8 | (unsigned short)Memory[PC+1];

	// Debug
	if ( cpu_debug_mode )
		cpu_debug_print();

	// Map Opcode Family
	switch ( Opcode & 0xF000 )
  	{
		// ---------------------------- CHIP-8 0xxx instruction set ---------------------------- //
		case 0x0000: //0NNN
			switch ( Opcode & 0x0F00 ) {

				case 0x0000: //00NN
					switch ( Opcode & 0x00FF ) { //00NN

						// // 0000 (ETI-660)
						// case 0x0000:
						// 	opc_chip8_ETI660_0000();
						// 	break;

						// 00E0 (CHIP-8)
						case 0x00E0:
							opc_chip8_00E0();
							break;

						// 00EE (CHIP-8)
						case 0x00EE:
							opc_chip8_00EE();
							break;

						// // 00F0 (CHIP-8x HiRes)
						// case 0x00F0:
						// 	opc_chip8HiRes_00F0();
						// 	break;

						// // 00F8 (ETI-660)
						// case 0x00F8:
						// 	opc_chip8_ETI660_00F8();
						// 	break;

						// 00FB (SCHIP)
						case 0x00FB:
								// opc_schip_00FB();
								// printf("Opcode 00FB not implemented yet\n");
								// exit(2);
								cpu_invalid_opcode(Opcode);
							break;

						// 00FC (SCHIP)
						// 00FC (ETI-660) - Turn display off
						case 0x00FC:
							// // ETI-660 Opcode
							// if ( Global.Hybrid_ETI_660_HW ) {
							// 	opc_chip8_ETI660_00FC();
							// 	break;

							// // SCHIP Opcode
							// } else {
								// opc_schip_00FC();
								// printf("Opcode 00FC not implemented yet\n");
								// exit(2);
								cpu_invalid_opcode(Opcode);
								break;
							// }

						// 00FD (SCHIP)
						case 0x00FD:
							// opc_schip_00FD();
							// printf("0x00FD not implemented yet\n");
							// exit(2);
							cpu_invalid_opcode(Opcode);
							break;

						// 00FE (SCHIP)
						case 0x00FE:
							// opc_schip_00FE();
							// printf("0x00FE not implemented yet\n");
							// exit(2);
							cpu_invalid_opcode(Opcode);
							break;

						// 00FF (SCHIP)
						// 00FF - In ETI-660, 00FF is a NO OP (do nothing)
						case 0x00FF:
							opc_schip_00FF();
							break;

							// // 00FF - ETI-660
							// if ( Global.Hybrid_ETI_660_HW ) {
							// 	opc_chip8_ETI660_00FF();
							// 	break;

							// // 00FF - SCHIP
							// } else {
							// 	opc_schip_00FF();
							// 	break;
							// }

						default:
							// printf("\t\tOpcode 0x%04X NOT IMPLEMENTED!!!!\n", Opcode);
							// exit(0);
							cpu_invalid_opcode(Opcode);
					}

					switch ( Opcode & 0x00F0 ){ //00N0
						// 00CN (SCHIP)
						case 0x00C0:
							// n := Opcode & 0x000F;
							// opc_schip_00CN(n);
							// printf("00CN not implemented yet\n");
							// exit(2);
							cpu_invalid_opcode(Opcode);

							break;
					}

				case 0x0200: //02NN
					switch ( Opcode & 0x0FFF ) {

				// 		// 0230 (CHIP-8 HIRES)
				// 		case 0x0230:
				// 			opc_chip8HiRes_0230();
				// 			break;

						// 02D8 (CHIP-8 NON DOCUMENTED)
						case 0x02D8:
							opc_chip8_ND_02D8();
							break;

				// 		// 02E4 (CHIP-8 NON DOCUMENTED)
				// 		case 0x02E4:
				// 			opc_chip8_ND_02E4();
				// 			break;

					}
				break;

				default:
					// printf("\t\tOpcode 0x%04X NOT IMPLEMENTED!!!!\n", Opcode);
					// exit(0);
					cpu_invalid_opcode(Opcode);
			}
			break;
		
		// ---------------------------- CHIP-8 1xxx instruction set ---------------------------- //
		case 0x1000: // 1nnn (CHIP-8)
			opc_chip8_1NNN();
			break;

		// // ---------------------------- CHIP-8 2xxx instruction set ---------------------------- //
		case 0x2000: // 2nnn (CHIP-8)
			// printf ("2000\n");
			opc_chip8_2NNN();
			break;

		// ---------------------------- CHIP-8 3xxx instruction set ---------------------------- //
		case 0x3000: // 3xnn (CHIP-8)
			opc_chip8_3XNN();
			break;

		// ---------------------------- CHIP-8 4xxx instruction set ---------------------------- //
		case 0x4000: // 4xnn (CHIP-8)
			opc_chip8_4XNN();
			break;

		// ---------------------------- CHIP-8 5xxx instruction set ---------------------------- //
		case 0x5000: // 5xy0 (CHIP-8)
			opc_chip8_5XY0();
			break;

		// ---------------------------- CHIP-8 6xxx instruction set ---------------------------- //
		case 0x6000: // 6xnn (CHIP-8)
			opc_chip8_6XNN();
			break;

		// ---------------------------- CHIP-8 7xxx instruction set ---------------------------- //
		case 0x7000: // 7xnn (CHIP-8)
			opc_chip8_7XNN();
			break;

		// ---------------------------- CHIP-8 8xxx instruction set ---------------------------- //
		case 0x8000: // 0x8000 instruction set
		{
			unsigned char x, y;
			x = (Opcode & 0x0F00) >> 8;
			y = (Opcode & 0x00F0) >> 4;

			switch ( Opcode & 0x000F ) {

				// 8xy0 (CHIP-8)
				case 0x0000:
					opc_chip8_8XY0(x, y);
					break;

				// 8xy1 (CHIP-8)
				case 0x0001:
					opc_chip8_8XY1(x, y);
					break;

				// 8xy2 (CHIP-8)
				case 0x0002:
					opc_chip8_8XY2(x, y);
					break;

				// 8xy3 (CHIP-8)
				case 0x0003:
					opc_chip8_8XY3(x, y);
					break;

				// 8xy4 (CHIP-8)
				case 0x0004:
					opc_chip8_8XY4(x, y);
					break;

				// 8xy5 (CHIP-8)
				case 0x0005:
					opc_chip8_8XY5(x, y);
					break;

				// 8xy6 (CHIP-8)
				case 0x0006:
					opc_chip8_8XY6(x, y);
					break;

				// 8xy7 (CHIP-8)
				case 0x0007:
					opc_chip8_8XY7(x, y);
					break;

				// 8xyE (CHIP-8)
				case 0x000E:
					opc_chip8_8XYE(x, y);
					break;

				default:
					// printf("\t\tOpcode 0x%04X NOT IMPLEMENTED!!!!\n", Opcode);
					// exit(0);
					cpu_invalid_opcode(Opcode);
			}
			break;
		}

		// ---------------------------- CHIP-8 9xxx instruction set ---------------------------- //
		case 0x9000: // 9xy0 (CHIP-8)
			opc_chip8_9XY0();
			break;

		// ---------------------------- CHIP-8 Axxx instruction set ---------------------------- //
		case 0xA000: // Annn (CHIP-8)
			opc_chip8_ANNN();
			break;

		// ---------------------------- CHIP-8 Bxxx instruction set ---------------------------- //
		case 0xB000: // Bnnn (CHIP-8)
			opc_chip8_BNNN();
			break;

		// ---------------------------- CHIP-8 Cxxx instruction set ---------------------------- //
		case 0xC000: // Cxnn (CHIP-8)
			opc_chip8_CXNN();
			break;

		// ---------------------------- CHIP-8 Dxxx instruction set ---------------------------- //
		case 0xD000: // Dxyn (CHIP-8)
			switch ( Opcode & 0x000F ) {

				// DXY0 (SCHIP)
				case 0x0000:

					// if ( !cpu_SCHIP_mode ) {
					// 	// Quirk to SCHIP Robot DEMO)


					// 	// // Even in SCHIP Mode this game needs to draw 16x16 Pixels
					// 	// if ( quirk_LoRes_Wide_Sprite_Dxy0 ) {
					// 	// 	cpu_SCHIP_LORES_mode = false;
					// 	// } else {
					// 	// 	// If NOT in SCHIP mode will draw 16x8 sprites
					// 	// 	cpu_SCHIP_LORES_mode = true;


					// 	// }
					// }
					// If in SCHIP mode will draw 16x16 sprites
					opc_schip_DXY0();
							// printf("dxy0 not implemented yet\n");
							// exit(2);
					break;

				// DXYN (CHIP-8, Draw n-byte sprites)
				default:
					opc_chip8_DXYN();
					break;
			}
			break;

		// ---------------------------- CHIP-8 Exxx instruction set ---------------------------- //
		case 0xE000: { // Exxx instruction set
			unsigned char x;
			x = (Opcode & 0x0F00) >> 8;

			switch ( Opcode & 0x00FF ) {

				// Ex9E (CHIP-8)
				case 0x009E:
					opc_chip8_EX9E(x);
					break;

				// ExA1 (CHIP-8)
				case 0x00A1:
					opc_chip8_EXA1(x);
					break;

				default:
					cpu_invalid_opcode(Opcode);
			}	

			break;
		}

		// ---------------------------- CHIP-8 Fxxx instruction set ---------------------------- //
		case 0xF000: // Fxxx instruction set
		{	
			unsigned char x;
			x = (Opcode & 0x0F00) >> 8;

			switch (  Opcode & 0x00FF )
			{

				// Fx07 (CHIP-8)
				case 0x0007:
					opc_chip8_FX07(x);
					break;

				// Fx0A (CHIP-8)
				case 0x000A:
					opc_chip8_FX0A(x);
					break;

				// Fx15 (CHIP-8)
				case 0x0015:
					opc_chip8_FX15(x);
					break;

				// Fx18 (CHIP-8)
				case 0x0018:
					opc_chip8_FX18(x);
					break;

				// Fx1E (CHIP-8)
				case 0x001E:
					opc_chip8_FX1E(x);
					break;

				// Fx29 (CHIP-8)
				case 0x0029:
					opc_chip8_FX29(x);
					break;

				// Fx30 (SCHIP)
				case 0x0030:
					// opc_schip_FX30(x);
					// printf("Opcode Fx30 not implemented yet!\n ");
					// exit(2);
					cpu_invalid_opcode(Opcode);
					break;

				// Fx33 (CHIP-8)
				case 0x0033:
					opc_chip8_FX33(x);
					break;

				// Fx55 (CHIP-8)
				case 0x0055:
					opc_chip8_FX55(x);
					break;

				// Fx65 (CHIP-8)
				case 0x0065:
					opc_chip8_FX65(x);
					break;

				// FX75 (SCHIP)
				case 0x0075:
					// opc_schip_FX75(x);
					// printf("Opcode FX75 not implemented yet!\n ");
					// exit(2);
					cpu_invalid_opcode(Opcode);
					break;

				// FX85 (SCHIP)
				case 0x0085:
					// opc_schip_FX85(x);
					// printf("Opcode FX85 not implemented yet!\n ");
					// exit(2);
					cpu_invalid_opcode(Opcode);
					break;

				// // Fx00 (ETI-660)
				// case 0x0000:
				// 	opc_chip8_ETI660_FX00(x);
				// 	break;

				default:
					// printf("\t\tOpcode 0x%04X NOT IMPLEMENTED!!!!\n", Opcode);
					//     // strcpy(gui_statusbar_msg, "NOT IMPLEMENTED.");
					// exit(2);
					cpu_invalid_opcode(Opcode);	
			}
			break;
		}

		default :
			// printf ("Not implemented!\n");
			// exit(2);
			cpu_invalid_opcode(Opcode);
  	}

	// Print all opcode debug messages
	if ( cpu_debug_mode ) {
		printf("\t\t%s\n\n" , cpu_debug_message);
	}

}

void cpu_invalid_opcode(unsigned short opc) {
		char str[100];
		sprintf(str, "Invalid ROM (Opcode 0x%04X not existent or not implemented.)", opc);
		strcpy(gui_statusbar_msg, str);
		cpu_rom_loaded = false;
		// Return to original menu state
		quirk_display_wait = true;
		gui_show_menu = true;
		gui_menu_quirks_inactive = true;

}
