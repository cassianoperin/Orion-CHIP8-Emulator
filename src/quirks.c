#include <stdio.h>
#include <string.h>
#include "quirks.h"

// Quirks needed by specific games
void handle_quirks(char *game_signature) {

	// ---------------------- CHIP8 ---------------------- //

	// Quirk: DISABLE Fx55 and Fx65 legacy mode (load_store_quirk)
	if ( !strcmp(game_signature, "00E06300640165EE35EE+40424")		// Test Program: BC_test.ch8
	|| !strcmp(game_signature, "60FFF015600069006E00+43064")		// Test Program: c8_test.c8
	|| !strcmp(game_signature, "6601221EF40A44027301+5104")			// Program:		 Delay Timer Test [Matthew Mikolay, 2010].ch8
	|| !strcmp(game_signature, "120543385060008500C0+102791")		// Demo:		 Stars [Sergey Naydenov, 2010].ch8
	|| !strcmp(game_signature, "12145245564956414C53+106009") 		// Game:		 Astro Dodge [Revival Studios, 2008].ch8
	|| !strcmp(game_signature, "121A322E303020432E20+203129") 		// Game:		 Blinky [Hans Christian Egeberg, 1991].ch8
	|| !strcmp(game_signature, "00E0121A4368722E2045+174546") 		// Game:		 Blinky [Hans Christian Egeberg] (alt).ch8
	|| !strcmp(game_signature, "121A434F4E4E45435434+19434") 		// Game:		 Connect 4 [David Winter].ch8
	|| !strcmp(game_signature, "121D48494444454E2120+87881") 		// Game:		 Hidden [David Winter, 1996].ch8
	|| !strcmp(game_signature, "12128D8D20A931393930+88372") 		// Game:		 Syzygy [Roy Trevino, 1990].ch8
	|| !strcmp(game_signature, "12185449435441432062+39518") )		// Game:		 Tic-Tac-Toe [David Winter].ch8
	{
		quirk_Memory_legacy_Fx55_Fx65 = false;
	}

	// Quirk: ENABLE 8XY6 and 8XYE legacy mode (shift_quirk)
	if ( !strcmp(game_signature, "120200E0A201F065A230+31866")		// Program: BMP Viewer - Hello (C8 example) [Hap, 2005].ch8
	|| !strcmp(game_signature, "12054338506014A370F0+36295")		// Program: Division Test [Sergey Naydenov, 2010].ch8
	|| !strcmp(game_signature, "124E0819010108010F01+9100") 		// Program: Keypad Test [Hap, 2006].ch8
	|| !strcmp(game_signature, "121A322E303020432E20+203129") 		// Game:		 Blinky [Hans Christian Egeberg, 1991].ch8
	|| !strcmp(game_signature, "00E0121A4368722E2045+174546") 		// Game:		 Blinky [Hans Christian Egeberg] (alt).ch8
	|| !strcmp(game_signature, "1225535041434520494E+124842") 		// Game:		 Space Invaders [David Winter].ch8
	|| !strcmp(game_signature, "1225535041434520494E+123139") 		// Game:		 Space Invaders [David Winter] (alt).ch8
	|| !strcmp(game_signature, "A2CD69386A1ED9A2A2D0+31820") 		// Game:		 Submarine [Carmelo Cortez, 1978].ch8
	|| !strcmp(game_signature, "00E06A0022626380228A+16829") 		// Game:		 Sum Fun [Joyce Weisbecker].ch8
	|| !strcmp(game_signature, "12185449435441432062+39518") )		// Game:		 Tic-Tac-Toe [David Winter].ch8
	{
		quirk_Shifting_legacy_8xy6_8xyE	= true;
	}

	// Quirk: DISABLE DXYN Clipping feature
	if ( !strcmp(game_signature, "2280CC014C011216CA3E+12252") ) {	// Program: Framed MK1 [GV Samways, 1980].ch8
		quirk_Clipping_Dxyn	= false;
	}

	// Quirk:		Do not load SCHIP fonts to avoid garbage after FFFFFF clock
	if ( !strcmp(game_signature, "F10AF20AF30AF40AF50A+27721") ) {	// Program: Clock Program [Bill Fisher, 1981].ch8
		quirk_ClockProgram_fonts = true;
		printf("Clock Program Quirk Enabled.\n");
	}
	

	// ---------------------- SCHIP ---------------------- //

	// // Enable undocumented FX1E feature needed by Spacefight 2091!
	// // Game "Spacefight 2091 [Carsten Soerensen, 1992].ch8"
	// if ( !strcmp(game_signature, "12245370616365466967+250532") ) {
	// 	quirk_Spacefight2091_Fx1E = true;
	// 	printf("FX1E undocumented feature enabled.\n");
	// }

	// // Enable undocumented FX1E feature needed by sctest_12
	// // SCHIP Test Program "sctest_12 (SC Test.ch8)"
	// if ( !strcmp(game_signature, "12122054726F6E697820+49853") ) {
	// 	quirk_Spacefight2091_Fx1E = true;
	// 	printf("FX1E undocumented feature enabled.\n");
	// }

	// // Enable Low Res 16x16 Pixel Draw in Robot.ch8 DEMO
	// // SCHIP Demo: "Robot"
	// if ( !strcmp(game_signature, "00FEA23A60006100620F+7720") ) {
	// 	quirk_LoRes_Wide_Sprite_Dxy0 = true;
	// 	printf("DXY0 SCHIP Low Res 16x16 Pixel fix enabled.\n");
	// }

	// // This game uses 64x32 screen size
	// // CHIP-8 ETI-660 Hybrid: "Pong"
	// if ( !strcmp(game_signature, "6A026B0C6C3F6D0CA6EA+25121") ) {
	// 	quirk_ETI660_64x32_screen = true;
	// 	printf("ETI-660 Quirk 64 x 32 resolution Enabled.\n");
	// 	display_EMULATOR_RES_X = 64;
	// 	display_EMULATOR_RES_Y = 32;
	// }

	// Bnnn behavior in some CHIP-48 and SUPER-CHIP that sum the value of V[x] instead of V[0]
	// https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#bnnn-jump-with-offset
	// Not used yet
	// if ( !strcmp(game_signature, "xxx") ) {
	// 	Bnnn_jump_with_offset	= false;
	// }

	// Set the quirks necessary for chip8-test-suite.ch8"



	// Print Quirk status on screen
	printf("\nCHIP 8 Quirks:\nVF Reset:\t%s\nMemory:\t\t%s\nDisplay Wait:\t%s\nClipping:\t%s\nShifting:\t%s\nJumping:\t%s\n\n", 
		quirk_VF_Reset_8xy1_8xy2_8xy3?"Enabled":"Disabled",
		quirk_Memory_legacy_Fx55_Fx65?"Enabled":"Disabled",
		quirk_display_wait?"Enabled":"Disabled",
		quirk_Clipping_Dxyn?"Enabled":"Disabled",
		quirk_Shifting_legacy_8xy6_8xyE?"Enabled":"Disabled",
		quirk_Jump_with_offset_Bnnn?"Enabled":"Disabled");

}
