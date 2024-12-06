#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cpu.h"

void cpu_reset(void) {

	// Initialize
	cpu_initialize();

	// Keep the rom size
	romsize = fsize(filename);

	// If a rom is bigger than chip8 memory (invalid game or program)
	if ( romsize > (4096-512) ) {
		cpu_initialize();

		// Print a message
		strcpy(gui_statusbar_msg, "Invalid rom file! Aborting!");
		printf("Invalid rom file! Aborting!\n");

	} else {
		// Load ROM into Memory
		load_rom(filename, Memory, sizeof(Memory));

		// Get Game signature for Qwirks
		game_signature = get_game_signature(filename);
		printf("Rom size:\t%d bytes\nSignature:\t%s\n", romsize, game_signature );

		// Check for Quirks
		handle_quirks(game_signature);

		// Load Fonts
		cpu_load_fonts();

		// Keyboard remaps
		input_keyboard_remaps();

		// Update StatusBar message
		strcpy(gui_statusbar_msg, "ROM loaded");
	}

	if ( cpu_rom_loaded ) {
		// Read the Opcode from PC and PC+1 bytes
		Opcode = cpu_fetch_opcode(PC);
	}

	// Clean messages
	strcpy(cpu_debug_message, "");

	// Clean counters
	cycle_cpu = 0;
}

void cpu_initialize(void) {

	// Clock
	CPU_CLOCK  = CHIP8_DEFAULT_CLOCK;

	// Components
	memset(Memory, 0x00,  (sizeof(Memory) / sizeof(Memory[0])) );	// Clean Memory
	PC = 0x200;								// Start at 0x200 (default CHIP-8)
	// Opcode = 0x00;
	memset(Stack, 0x00, sizeof(Stack));		// Clean Stack
	SP = 0x00;
	memset(V, 0x00, sizeof(V));				// Clean V Register
	I = 0x00;

	Opcode = 0;
	
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
	display_EMULATOR_RES_X = 64;		// Number of Columns in Graphics
	display_EMULATOR_RES_Y = 32;		// Number of Lines in Graphics
	
	// Keyboard
	memset(Key, 0x00, sizeof(Key));

	// Initialize random generator
	srand(time(NULL));

	// Draw flag
	cpu_draw_flag = 0;

	// GUI
	gui_menu_quirks_inactive = false; // Enable Quirks menu

	// Rom size
	romsize = 0;

	// Reset ROM loaded status
	cpu_rom_loaded = false;

	// Debug
	// cpu_debug_mode	       = false;
	// cpu_debug_print_console = false;
	// cpu_pause		       = false;
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

	// Debug
	if ( cpu_debug_print_console )
		cpu_debug_print();

	// Map Opcode Family
	switch ( Opcode & 0xF000 )
  	{
		// ---------------------------- CHIP-8 0xxx instruction set ---------------------------- //
		// 0NNN: Execute RCA 1802 machine language routine at address NNN
		// 00E0: Clear the screen
		// 00EE: Return from subroutine

		case 0x0000: //0NNN
		
			switch ( Opcode & 0x0F00 ) {

				case 0x0000: //00NN
					
					switch ( Opcode & 0x00FF ) { //00NN

						// 00E0 (CHIP-8)
						case 0x00E0:
							opc_chip8_00E0();
							break;

						// 00EE (CHIP-8)
						case 0x00EE:
							opc_chip8_00EE();
							break;

						default:
							// printf("\t\tOpcode 0x%04X NOT IMPLEMENTED!!!!\n", Opcode);
							// exit(0);
							cpu_invalid_opcode(Opcode);
					}

				case 0x0200: //02NN
					switch ( Opcode & 0x0FFF ) {

						// 02D8 (CHIP-8 NON DOCUMENTED)
						case 0x02D8:
							opc_chip8_ND_02D8();
							break;

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
			opc_chip8_DXYN();
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

				default:
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
	// if ( cpu_debug_mode ) {
	// 	printf("\t\t%s\n\n" , cpu_debug_message);
	// }

	// Read the Opcode from PC and PC+1 bytes
	Opcode = cpu_fetch_opcode(PC);

}

void cpu_invalid_opcode(unsigned short opc) {
		char str[100];
		sprintf(str, "Invalid ROM (Opcode 0x%04X not existent or not implemented.)", opc);
		strcpy(gui_statusbar_msg, str);
		cpu_rom_loaded = false;
		// Return to original menu state
		quirk_display_wait = true;
		gui_menu_quirks_inactive = true;

}

// Read the Opcode from PC and PC+1 bytes
int cpu_fetch_opcode(int PC_addr) {
	
	int opc;
	opc = (unsigned short)Memory[PC_addr]<<8 | (unsigned short)Memory[PC_addr+1];

	// Increment PC
	PC += 2;

	return opc;
}

// Read the Opcode from PC and PC+1 bytes for debug screen
int cpu_fetch_opcode_debug(int PC_addr) {
	
	int opc;
	opc = (unsigned short)Memory[PC_addr]<<8 | (unsigned short)Memory[PC_addr+1];

	return opc;
}

// Decode next opcode to debug message
void cpu_decode_opcode(int opc) {

    switch(opc & 0xF000)
    {

		// ---------------------------- CHIP-8 0xxx instruction set ---------------------------- //
        case 0x0000:
        {
			switch(opc & 0x00F0)
            {
				case 0x0000: // --0-
                {
					// Just to handle the not loaded memories, its not an opcode
					break;
				}

                case 0x00E0: // --E-
                {
					switch(opc & 0x000F)
					{
						// 0_E0
						case 0x0000:
						{
							sprintf(guiDebug_opc_description_msg, "CLS");
							break;
						}

						// 0_EE
						case 0x000E:
						{
							sprintf(guiDebug_opc_description_msg, "RET  #%04X", Stack[SP]+2);
							break;
						}
						default :
						{
							sprintf(guiDebug_opc_description_msg, "-");
							// printf("Opcode 0: Nibble 4 not mapped: %04X\n\n", opc);
							// exit(2);
						}
					}

                    break;
                }

                default : {
					sprintf(guiDebug_opc_description_msg, "-");
					// printf("Opcode 0: Nibble 3 not mapped: %04X\n\n", opc);
					// exit(2);
				}
			}

			break;
        }

		// ---------------------------- CHIP-8 1xxx instruction set ---------------------------- //
		case 0x1000: { // 1nnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "JUMP #%04X", opc & 0x0FFF);
			break;
		}

		// ---------------------------- CHIP-8 2xxx instruction set ---------------------------- //
		case 0x2000: { // 2nnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "CALL #%04X", opc & 0x0FFF);
			break;
		} 

		// ---------------------------- CHIP-8 3xxx instruction set ---------------------------- //
		case 0x3000: { // 3nnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "SKIP.EQ V[%X] #%02X", (opc & 0x0F00 ) >> 8, opc & 0x00FF);
			break;
		} 

		// ---------------------------- CHIP-8 4xxx instruction set ---------------------------- //
		case 0x4000: { // 4nnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "SKIP.NE V[%X] #%02X", (opc & 0x0F00 ) >> 8, opc & 0x00FF);
			break;
		}

		// ---------------------------- CHIP-8 5xxx instruction set ---------------------------- //
		case 0x5000: { // 5nnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "SKIP.EQ V[%X] V[%X]", (opc & 0x0F00 ) >> 8, (opc & 0x00F0) >> 4);
			break;
		} 

		// ---------------------------- CHIP-8 6xxx instruction set ---------------------------- //
		case 0x6000: { // 6nnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "LOAD V[%X] with #%02X", (opc & 0x0F00 ) >> 8, opc & 0x00FF);
			break;
		}

		// ---------------------------- CHIP-8 7xxx instruction set ---------------------------- //
		case 0x7000: { // 7nnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "ADD #%02X to V[%X] ", opc & 0x00FF, (opc & 0x0F00 ) >> 8);
			break;
		}

		// ---------------------------- CHIP-8 8xxx instruction set ---------------------------- //
		case 0x8000: { // 8nnn (CHIP-8)


			switch(opc & 0x000F)
            {
				case 0x0000: // 8--0
                {
					sprintf(guiDebug_opc_description_msg, "LOAD V[%X] with V[%X]", (opc & 0x0F00 ) >> 8, (opc & 0x00F0) >> 4);
					break;
				}

                case 0x0001: // 8--1
                {
					sprintf(guiDebug_opc_description_msg, "OR V[%X] with V[%X] ", (opc & 0x0F00) >> 8, (opc & 0x00F0) >> 4 );
                    break;
                }

                case 0x0002: // 8--2
                {
					sprintf(guiDebug_opc_description_msg, "AND V[%X] with V[%X] ", (opc & 0x0F00) >> 8, (opc & 0x00F0) >> 4 );
                    break;
                }

                case 0x0003: // 8--3
                {
					sprintf(guiDebug_opc_description_msg, "XOR V[%X] with V[%X] ", (opc & 0x0F00) >> 8, (opc & 0x00F0) >> 4 );
                    break;
                }

                case 0x0004: // 8--4
                {
					sprintf(guiDebug_opc_description_msg, "ADD V[%X] to V[%X] ", (opc & 0x00F0) >> 4, (opc & 0x0F00 ) >> 8 );
                    break;
                }

                case 0x0005: // 8--5
                {
					sprintf(guiDebug_opc_description_msg, "SUB V[%X], V[%X]", (opc & 0x0F00 ) >> 8, (opc & 0x00F0 ) >> 4);
                    break;
                }

                case 0x0006: // 8--6
                {
					if ( quirk_Shifting_legacy_8xy6_8xyE ) {
						sprintf(guiDebug_opc_description_msg, "SHR V[%X]", (opc & 0x0F00 ) >> 8 );
					} else {
						sprintf(guiDebug_opc_description_msg, "SHR V[%X], LD in V[%X]", (opc & 0x00F0 ) >> 4, (opc & 0x0F00 ) >> 8 );
					}
                    break;
                }

                case 0x0007: // 8--7
                {
					sprintf(guiDebug_opc_description_msg, "SUB_B V[%X], V[%X]", (opc & 0x0F00 ) >> 8, (opc & 0x00F0 ) >> 4);
                    break;
                }

                case 0x000E: // 8--E
                {
					if ( quirk_Shifting_legacy_8xy6_8xyE ) {
						sprintf(guiDebug_opc_description_msg, "SHL V[%X]", (opc & 0x0F00 ) >> 8 );
					} else {
						sprintf(guiDebug_opc_description_msg, "SHL V[%X], LD in V[%X]", (opc & 0x00F0 ) >> 4, (opc & 0x0F00 ) >> 8 );
					}
                    break;
                }

                default : {
					sprintf(guiDebug_opc_description_msg, "-");
					// printf("Opcode 8: Nibble 4 not mapped: %04X\n\n", opc);
					// exit(2);
				}
			}

			break;
		}

		// ---------------------------- CHIP-8 9xxx instruction set ---------------------------- //
		case 0x9000: { // 9nnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "SKIP.NE V[%X] V[%X]", (opc & 0x0F00 ) >> 8, opc & 0x00F0 >> 4);
			break;
		}

		// ---------------------------- CHIP-8 Axxx instruction set ---------------------------- //
		case 0xA000: { // Annn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "LOAD I with #%04X", opc & 0x0FFF);
			break;
		}

		// ---------------------------- CHIP-8 Bxxx instruction set ---------------------------- //
		case 0xB000: { // Bnnn (CHIP-8)
			if ( !quirk_Jump_with_offset_Bnnn ) {
				sprintf(guiDebug_opc_description_msg, "LOAD PC, #%04X+V[0]", opc & 0x0FFF);
			} else {
				sprintf(guiDebug_opc_description_msg, "LOAD PC, #%04X+V[%X]", opc & 0x0FFF, (opc & 0x0F00) >> 8);
			}

			break;
		}

		// ---------------------------- CHIP-8 Cxxx instruction set ---------------------------- //
		case 0xC000: { // Cnnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "RAND V[%X], up to #%02X", (opc & 0x0F00 ) >> 8, opc & 0x00FF);
			break;
		}

		// ---------------------------- CHIP-8 Dxxx instruction set ---------------------------- //
		case 0xD000: { // Dnnn (CHIP-8)
			sprintf(guiDebug_opc_description_msg, "DRAW X:%02d Y:%02d N:%02d", V[(opc & 0x0F00 ) >> 8], V[(opc & 0x00F0 ) >> 4], opc & 0x000F);
			break;
		}

		// ---------------------------- CHIP-8 Exxx instruction set ---------------------------- //
		case 0xE000: { // Ennn (CHIP-8)

			switch(opc & 0x00FF)
            {
				case 0x009E: // E-9E
                {
					sprintf(guiDebug_opc_description_msg, "SKIP.KEY #%X", V[(opc & 0x0F00 ) >> 8] );
					break;
				}

                case 0x00A1: // E-A1
                {
					sprintf(guiDebug_opc_description_msg, "SKIP.NOKEY #%X", V[(opc & 0x0F00 ) >> 8] );
                    break;
                }

                default : {
					sprintf(guiDebug_opc_description_msg, "-");
					// printf("Opcode E: Nibble 4 not mapped: %04X\n\n", opc);
					// exit(2);
				}
			}

			break;
		}



		// ---------------------------- CHIP-8 Fxxx instruction set ---------------------------- //
		case 0xF000: { // Fnnn (CHIP-8)

			switch(opc & 0x00FF)
            {
				case 0x0007: // Fx07
				{
					sprintf(guiDebug_opc_description_msg, "LOAD V[%X], DT", ( opc & 0x0F00 ) >> 8 );
					break;
				}

                case 0x000A: // F-0A
                {
					sprintf(guiDebug_opc_description_msg, "LOAD V[%X], KEY_PRESS", ( opc & 0x0F00 ) >> 8 );
                    break;
                }

                case 0x0015: // F-15
                {
					sprintf(guiDebug_opc_description_msg, "LOAD DT, V[%X]", ( opc & 0x0F00 ) >> 8 );
                    break;
                }

                case 0x0018: // F-18
                {
					sprintf(guiDebug_opc_description_msg, "LOAD ST, V[%X]", ( opc & 0x0F00 ) >> 8 );
                    break;
                }

				case 0x001E: // F-1E
                {
					sprintf(guiDebug_opc_description_msg, "ADD I, V[%X]", (opc & 0x0F00 ) >> 8 );
                    break;
                }

				case 0x0029: // F-29
                {
					sprintf(guiDebug_opc_description_msg, "SPRITECHAR V[%X]", (opc & 0x0F00 ) >> 8 );
                    break;
                }

                case 0x0033: // F-33
                {
					sprintf(guiDebug_opc_description_msg, "BCD V[%X], I,I+1,I+2", (opc & 0x0F00 ) >> 8 );
                    break;
                }

                case 0x0055: // F-55
                {
					sprintf(guiDebug_opc_description_msg, "LOAD M[%04X], V[0-%X]", I, (opc & 0x0F00 ) >> 8 );
                    break;
                }

                case 0x0065: // F-65
                {
					sprintf(guiDebug_opc_description_msg, "LOAD V[0-%X], M[%04X]", (opc & 0x0F00 ) >> 8, I );
                    break;
                }

                default : {
					sprintf(guiDebug_opc_description_msg, "-");
					// printf("Opcode F: Nibble 4 not mapped: %04X\n\n", opc);
					// exit(2);
				}
			}

			break;
		}

        default :
		{
			sprintf(guiDebug_opc_description_msg, "-");
			printf("Main opcode not mapped: %04X\n", opc);
			exit(2);
		}

    }
}
