#include <stdio.h>
#include <string.h>
#include "quirks.h"

// Quirks needed by specific games
void handle_quirks(DB_PROGRAM_rom_info r, DB_PROGRAM_platform_info p, char *rom_sha1) {

	// Got information from program.json and platforms.json
	if (r.chosen_platform[0] != '\0' && p.name[0] != '\0' && core_autodetection_enabled ) {

		printf("JSON Databases loaded successfully, updating platform quirks\n");

		// Update Logic Quirk
		if (p.quirks.logic.present) {
			// printf("'logic' quirk exist with value: %s\n", p.quirks.logic.value ? "true" : "false");
			quirk_VF_Reset_8xy1_8xy2_8xy3 = p.quirks.logic.value;
		}

		// Update memoryIncrementByX Quirk
		if (p.quirks.memoryIncrementByX.present) {
			// printf("'memoryIncrementByX' quirk exist with value: %s\n", p.quirks.memoryIncrementByX.value ? "true" : "false");
			quirk_Memory_IncByX_Fx55_Fx65 = p.quirks.memoryIncrementByX.value;
		}

		// Update memoryLeaveIUnchanged Quirk
		if (p.quirks.memoryLeaveIUnchanged.present) {
			// printf("'memoryLeaveIUnchanged' quirk exist with value: %s\n", p.quirks.memoryLeaveIUnchanged.value ? "true" : "false");
			quirk_Memory_LeaveI_Fx55_Fx65 = p.quirks.memoryLeaveIUnchanged.value;
		}

		// Update vblank Quirk
		if (p.quirks.vblank.present) {
			// printf("'vblank' quirk exist with value: %s\n", p.quirks.vblank.value ? "true" : "false");
			quirk_display_wait = p.quirks.vblank.value;
		}

		// Update wrap Quirk
		if (p.quirks.wrap.present) {
			// printf("'wrap' quirk exist with value: %s\n", p.quirks.wrap.value ? "true" : "false");
			quirk_Wrap_Dxyn = p.quirks.wrap.value;
		}

		// Update wrap shift
		if (p.quirks.shift.present) {
			// printf("'shift' quirk exist with value: %s\n", p.quirks.shift.value ? "true" : "false");
			quirk_Shifting_legacy_8xy6_8xyE = p.quirks.shift.value;
		}

		// Update wrap jump
		if (p.quirks.jump.present) {
			// printf("'jump' quirk exist with value: %s\n", p.quirks.jump.value ? "true" : "false");
			quirk_Jump_with_offset_Bnnn = p.quirks.jump.value;
		}

		// After updating 7 possible quirks, check if there is some quirk specific in rom definition in program.json
		for(int i = 0; i < r.quirk_count; i++) {

			const char *key   = r.quirk_keys[i];
			const char *value = r.quirk_values[i];

			int state = (strcmp(value, "true") == 0) ? 1 : 0;

			if(strcmp(key, "shift") == 0) {
				quirk_Shifting_legacy_8xy6_8xyE = state;
			}
			else if(strcmp(key, "memoryIncrementByX") == 0) {
				quirk_Memory_IncByX_Fx55_Fx65 = state;
			}
			else if(strcmp(key, "memoryLeaveIUnchanged") == 0) {
				quirk_Memory_LeaveI_Fx55_Fx65 = state;
			}
			else if(strcmp(key, "wrap") == 0) {
				quirk_Wrap_Dxyn = state;
			}
			else if(strcmp(key, "jump") == 0) {
				quirk_Jump_with_offset_Bnnn = state;
			}
			else if(strcmp(key, "vblank") == 0) {
				quirk_display_wait = state;
			}
			else if(strcmp(key, "logic") == 0) {
				quirk_VF_Reset_8xy1_8xy2_8xy3 = state;
			}
			else {
				/* Unknown quirk */
				printf("[quirk] Unknown quirk ignored: %s = %s\n", key, value);
				continue;
			}

			printf("Quirk defined to this rom in programs.json: %s = %s\n", key, state ? "true" : "false");
		}


	} else {
		printf("Problem loading databases or game not found, using default platform quirks\n");

		// Hardcoded Quirks per Platform in case of a game that does not exist on database
		switch( core )
		{
			// Original CHIP8
			case 0:
				quirk_VF_Reset_8xy1_8xy2_8xy3	= true;		// Logic (VF Reset) - OK
				quirk_Memory_IncByX_Fx55_Fx65	= false;	// I incremented by X or X+1
				quirk_Memory_LeaveI_Fx55_Fx65	= false;	// Leave I untouched
				quirk_Wrap_Dxyn					= false;	// Wrap (Clipping)
				quirk_Jump_with_offset_Bnnn		= false;	// Jumping
				quirk_display_wait				= false;	// Display wait
				quirk_Shifting_legacy_8xy6_8xyE	= false;	// Shifting

				break;

			// Modern CHIP-8
			case 1: {
				quirk_VF_Reset_8xy1_8xy2_8xy3	= false;	// Logic (VF Reset) - OK
				quirk_Memory_IncByX_Fx55_Fx65	= false;	// I incremented by X or X+1
				quirk_Memory_LeaveI_Fx55_Fx65	= false;	// Leave I untouched
				quirk_Wrap_Dxyn					= false;	// Wrap (Clipping)
				quirk_Jump_with_offset_Bnnn		= false;	// Jumping
				quirk_display_wait				= false;	// Display wait
				quirk_Shifting_legacy_8xy6_8xyE	= false;	// Shifting

				break;
			}

			// Superchip 1.1
			case 2: {
				quirk_VF_Reset_8xy1_8xy2_8xy3	= false;	// Logic (VF Reset) - OK
				quirk_Memory_IncByX_Fx55_Fx65	= false;	// I incremented by X or X+1
				quirk_Memory_LeaveI_Fx55_Fx65	= true;		// Leave I untouched
				quirk_Wrap_Dxyn					= false;	// Wrap (Clipping)
				quirk_Jump_with_offset_Bnnn		= true;		// Jumping
				quirk_display_wait				= false;	// Display wait
				quirk_Shifting_legacy_8xy6_8xyE	= true;		// Shifting

				break;
			}

		}

	}

	// Print Core on screen
	static const char *core_names[] = { "Original CHIP-8 (Cosmac VIP)", "Modern CHIP-8", "SuperCHIP 1.1" };
	printf("\nCHIP-8 CORE: %s\n", (core >= 0 && core < 3) ? core_names[core] : "UNKNOWN_CORE");

	// Print Default Quirk status on screen
	printf("Quirks:\n   Logic:\t\t%s\n   Memory Inc by X:\t%s\n   Memory Leave I:\t%s\n   Display Wait:\t%s\n   Wrap:\t\t%s\n   Shifting:\t\t%s\n   Jumping:\t\t%s\n\n", 
		quirk_VF_Reset_8xy1_8xy2_8xy3?"Enabled":"Disabled",
		quirk_Memory_IncByX_Fx55_Fx65?"Enabled":"Disabled",
		quirk_Memory_LeaveI_Fx55_Fx65?"Enabled":"Disabled",
		quirk_display_wait?"Enabled":"Disabled",
		quirk_Wrap_Dxyn?"Enabled":"Disabled",
		quirk_Shifting_legacy_8xy6_8xyE?"Enabled":"Disabled",
		quirk_Jump_with_offset_Bnnn?"Enabled":"Disabled");
	
































	// ---------------------- CHIP8 ---------------------- //

	// DISABLE Quirk "Memory"
	// Fx55 and Fx65 legacy mode (load_store_quirk)
	// The save and load opcodes (Fx55 and Fx65) increment the index register
	// if ( !strcmp(rom_sha1, "9df1689015a0d1d95144f141903296f9f1c35fc5")		// Test Program: BC_test.ch8
	// ||   !strcmp(rom_sha1, "8e592d3620481e00ea36d29765b95287c7349a70")		// Test Program: c8_test.c8
	// ||   !strcmp(rom_sha1, "082c71b67e36e033c2e615ad89ba4ed5d55a56d0")		// Program:		 Delay Timer Test [Matthew Mikolay, 2010].ch8
	// ||   !strcmp(rom_sha1, "0085dd8fce4f7ac2e39ba73cf67cc043f9ba4812")		// Demo:		 Stars [Sergey Naydenov, 2010].ch8
	// ||   !strcmp(rom_sha1, "ac621d9fcada302ba6965768229ef130630bc525") 		// Game:		 Astro Dodge [Revival Studios, 2008].ch8
	// ||   !strcmp(rom_sha1, "d40abc54374e4343639f993e897e00904ddf85d9") 		// Game:		 Blinky [Hans Christian Egeberg, 1991].ch8
	// ||   !strcmp(rom_sha1, "f4169141735d8d60e51409ca7e73f4adedcefef2") 		// Game:		 Blinky [Hans Christian Egeberg] (alt).ch8
	// ||   !strcmp(rom_sha1, "2d10c07b532f4fa7c07a07324ba26ca39fe484fd") 		// Game:		 Connect 4 [David Winter].ch8
	// ||   !strcmp(rom_sha1, "050f07a54371da79f924dd0227b89d07b4f2aed0") 		// Game:		 Hidden [David Winter, 1996].ch8
	// ||   !strcmp(rom_sha1, "1bdb4ddaa7049266fa3226851f28855a365cfd12")		// Game:		 Syzygy [Roy Trevino, 1990].ch8
	// ||   !strcmp(rom_sha1, "5e70f91ca08e9b9e9de61670492e3db2d7f7d57a")		// Game:		 Rocket Launch [Jonas Lindstedt].ch8
	// ||   !strcmp(rom_sha1, "429d455a4bc53167942bf6fd934d72b0f648dce3") )	// Game:		 Tic-Tac-Toe [David Winter].ch8
	// {
	// 	quirk_Memory_IncByX_Fx55_Fx65 = true;
	// }


	// // ENABLE Quirk "Shifting"
	// // 8XY6 and 8XYE legacy mode (shift_quirk)
	// // The shift opcodes (8xy6 and 8xyE) only operate on vX instead of storing the shifted version of vY in vX
	// if ( !strcmp(rom_sha1, "72c2cbfea48000e25891dd4968ae9f1adef1e7e3")		// Program:		 BMP Viewer - Hello (C8 example) [Hap, 2005].ch8
	// ||   !strcmp(rom_sha1, "0ebc4b92c6059d6193565644fb00108161d03d23") 		// Program: 	 Keypad Test [Hap, 2006].ch8
	// ||   !strcmp(rom_sha1, "d40abc54374e4343639f993e897e00904ddf85d9") 		// Game:		 Blinky [Hans Christian Egeberg, 1991].ch8
	// ||   !strcmp(rom_sha1, "f4169141735d8d60e51409ca7e73f4adedcefef2") 		// Game:		 Blinky [Hans Christian Egeberg] (alt).ch8
	// ||   !strcmp(rom_sha1, "5c28a5f85289c9d859f95fd5eadbdcb1c30bb08b") 		// Game:		 Space Invaders [David Winter].ch8
	// ||   !strcmp(rom_sha1, "f100197f0f2f05b4f3c8c31ab9c2c3930d3e9571") 		// Game:		 Space Invaders [David Winter] (alt).ch8
	// ||   !strcmp(rom_sha1, "89aadf7c28bcd1c11e71ad9bd6eeaf0e7be474f3") 		// Game:		 Submarine [Carmelo Cortez, 1978].ch8
	// ||   !strcmp(rom_sha1, "83a2f9c8153be955c28e788bd803aa1d25131330")		// Game:		 Sum Fun [Joyce Weisbecker].ch8
	// ||   !strcmp(rom_sha1, "9df1689015a0d1d95144f141903296f9f1c35fc5")		// Game:		 BC_test.ch8
	// ||   !strcmp(rom_sha1, "da710f631f8e35534d0b9170bcf892a60f49c43d")		// Game:		 Vertical Brix [Paul Robson, 1996].ch8
	// ||   !strcmp(rom_sha1, "429d455a4bc53167942bf6fd934d72b0f648dce3") )	// Game:		 Tic-Tac-Toe [David Winter].ch8
	// {
	// 	quirk_Shifting_legacy_8xy6_8xyE	= true;
	// }

	// DISABLE Quirk "Clipping"
	// // DXYN Sprites drawn at the bottom edge of the screen get clipped instead of wrapping around to the top of the screen
	// if ( !strcmp(rom_sha1, "ac7c8db7865beb22c9ec9001c9c0319e02f5d5c2") ) {	// Program: Framed MK1 [GV Samways, 1980].ch8
	// 	quirk_Wrap_Dxyn	= false;

	// 	// TESTAR BOWLING
	// }

	// // ENABLE Quirk "Display Wait"
	// // Drawing sprites to the display waits for the vertical blank, limiting to max 60 FPS
	// if ( !strcmp(rom_sha1, "A2CD69386A1ED9A2A2D0+31820") ) {	// Game: Submarine [Carmelo Cortez, 1978].ch8
	// 	quirk_display_wait	= true;
	// }

	// ---------------------- SCHIP ---------------------- //

	// CONFIRM, PROBABLY FIXED BY I BUFFER OVERFLOOW IMPLEMENTATION ON Fx1E
	// // Enable undocumented FX1E feature needed by sctest_12
	// // SCHIP Test Program "sctest_12 (SC Test.ch8)"
	// if ( !strcmp(rom_sha1, "12122054726F6E697820+49853") ) {
	// 	workaround_Fx1E_Spacefight = true;
	// 	printf("FX1E undocumented feature enabled.\n");
	// }

	// // Enable Low Res 16x16 Pixel Draw in Robot.ch8 DEMO
	// // SCHIP Demo: "Robot"
	// if ( !strcmp(rom_sha1, "00FEA23A60006100620F+7720") ) {
	// 	quirk_LoRes_Wide_Sprite_Dxy0 = true;
	// 	printf("DXY0 SCHIP Low Res 16x16 Pixel fix enabled.\n");
	// }

	// // This game uses 64x32 screen size
	// // CHIP-8 ETI-660 Hybrid: "Pong"
	// if ( !strcmp(rom_sha1, "6A026B0C6C3F6D0CA6EA+25121") ) {
	// 	quirk_ETI660_64x32_screen = true;
	// 	printf("ETI-660 Quirk 64 x 32 resolution Enabled.\n");
	// 	display_EMULATOR_RES_X = 64;
	// 	display_EMULATOR_RES_Y = 32;
	// }

	// Bnnn behavior in some CHIP-48 and SUPER-CHIP that sum the value of V[x] instead of V[0]
	// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#bnnn-jump-with-offset
	// Not used yet
	// if ( !strcmp(rom_sha1, "xxx") ) {
	// 	Bnnn_jump_with_offset	= false;
	// }

	// Set the quirks necessary for chip8-test-suite.ch8"



	// // Print Quirk status on screen
	// printf("\nCHIP 8 Quirks:\nVF Reset:\t%s\nMemory:\t\t%s\nDisplay Wait:\t%s\nWrap:\t%s\nShifting:\t%s\nJumping:\t%s\n\n", 
	// 	quirk_VF_Reset_8xy1_8xy2_8xy3?"Enabled":"Disabled",
	// 	quirk_Memory_IncByX_Fx55_Fx65?"Enabled":"Disabled",
	// 	quirk_display_wait?"Enabled":"Disabled",
	// 	quirk_Wrap_Dxyn?"Enabled":"Disabled",
	// 	quirk_Shifting_legacy_8xy6_8xyE?"Enabled":"Disabled",
	// 	quirk_Jump_with_offset_Bnnn?"Enabled":"Disabled");








}



