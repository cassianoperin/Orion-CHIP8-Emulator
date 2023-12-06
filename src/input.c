#include <SDL2/SDL.h>
#include <string.h>
#include "input.h"

#include "../lib/nuklear.h"
#include "../lib/nuklear_sdl_renderer.h"

void input_keyboard(void) {

	//Event handler
	SDL_Event event;
	
	// Nuklear Input Handling Start
	nk_input_begin(ctx);

	// Handle events on queue
	while( SDL_PollEvent( &event ) != 0 )
	{
		if (event.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch( event.key.keysym.sym )
			{
				case SDLK_1:
					Key[0x1] = 1;
					break;

				case SDLK_2:
					Key[0x2] = 1;
					break;

				case SDLK_3:
					Key[0x3] = 1;
					break;

				case SDLK_4:
					Key[0xC] = 1;
					break;

				case SDLK_q:
					Key[0x4] = 1;
					break;

				case SDLK_w:
					Key[0x5] = 1;
					break;

				case SDLK_e:
					Key[0x6] = 1;
					break;

				case SDLK_r:
					Key[0xD] = 1;
					break;

				case SDLK_a:
					Key[0x7] = 1;
					break;

				case SDLK_s:
					Key[0x8] = 1;
					break;

				case SDLK_d:
					Key[0x9] = 1;
					break;

				case SDLK_f:
					Key[0xE] = 1;
					break;

				case SDLK_z:
					Key[0xA] = 1;
					break;

				case SDLK_x:
					Key[0x0] = 1;
					break;

				case SDLK_c:
					Key[0xB] = 1;
					break;

				case SDLK_v:
					Key[0xF] = 1;
					break;
				
				// Remap Keys

				case SDLK_UP:
				if ( input_remap_flag )
					Key[input_remap_btn_UP] = 1;

				break;
				
				case SDLK_DOWN:
					if ( input_remap_flag )
						Key[input_remap_btn_DOWN] = 1;

					break;		

				case SDLK_LEFT:
					if ( input_remap_flag )
						Key[input_remap_btn_LEFT] = 1;
					
					break;

				case SDLK_RIGHT:
					if ( input_remap_flag )
						Key[input_remap_btn_RIGHT] = 1;
					
					break;

				case SDLK_SPACE:
					if ( input_remap_flag )
						Key[input_remap_btn_SPACE] = 1;
					
					break;

				// Interface

				// // Pause
				// case SDLK_p:
				// 	cpu_pause = !cpu_pause;

				// 	if (cpu_pause ) {
				// 		// -------- Message slot 4 -------- //
				// 		strcpy(string_msg4, "Pause: ENABLED");
				// 		font_update_msg4(renderer);

				// 		// Draw
				// 		display_draw(frame_counter, &scene);

				// 		message_slot4_timer = 3;
				// 	} else {
				// 		// -------- Message slot 4 -------- //
				// 		strcpy(string_msg4, "Pause: DISABLED");
				// 		font_update_msg4(renderer);

				// 		// Draw
				// 		display_draw(frame_counter, &scene);

				// 		message_slot4_timer = 3;
				// 	}

				// 	break;

				// // Sound
				// case SDLK_o:
				// 	sound_enabled = !sound_enabled;

				// 	if (sound_enabled ) {
				// 		// -------- Message slot 4 -------- //
				// 		strcpy(string_msg4, "Sound: ENABLED");
				// 		font_update_msg4(renderer);

				// 		// Draw
				// 		display_draw(frame_counter, &scene);

				// 		message_slot4_timer = 3;
				// 	} else {
				// 		// -------- Message slot 4 -------- //
				// 		strcpy(string_msg4, "Sound: DISABLED");
				// 		font_update_msg4(renderer);

				// 		// Draw
				// 		display_draw(frame_counter, &scene);

				// 		message_slot4_timer = 3;
				// 	}

				// 	break;

				// // Step Forward
				// case SDLK_i:

				// 	if (cpu_pause ) {
						
				// 		cpu_interpreter();
						
				// 		// -------- Message slot 4 -------- //
				// 		strcpy(string_msg4, "CPU: STEP FORWARD");
				// 		font_update_msg4(renderer);

				// 		// Draw
				// 		display_draw(frame_counter, &scene);

				// 		message_slot4_timer = 3;
				// 	}

				// 	break;
					
				// // Reduce Clock
				// case SDLK_5:
				// 	if ( CPU_CLOCK >= pal_freq + 10) {
				// 		CPU_CLOCK -= 10;

				// 		// Show Message
				// 		sprintf(string_msg4, "Clock %d", CPU_CLOCK);
				// 		font_update_msg4(renderer);

				// 	} else {
				// 		// Show Message
				// 		sprintf(string_msg4, "Clock %d", CPU_CLOCK);
				// 		strcat(string_msg4, " - Minimum Allowed");
				// 		font_update_msg4(renderer);
				// 	}

				// 	// Draw
				// 	display_draw(frame_counter, &scene);
				// 	message_slot4_timer = 3;

				// 	break;
				
				// // Increase Clock
				// case SDLK_6:
				// 	if ( CPU_CLOCK < Max_Overclock) {
				// 		CPU_CLOCK += 10;

				// 		// Show Message
				// 		sprintf(string_msg4, "Clock %d", CPU_CLOCK);
				// 		font_update_msg4(renderer);

				// 	} else {
				// 		// Show Message
				// 		sprintf(string_msg4, "Clock %d", CPU_CLOCK);
				// 		strcat(string_msg4, " - Maximum Allowed");
				// 		font_update_msg4(renderer);
				// 	}

				// 	// Draw
				// 	display_draw(frame_counter, &scene);
				// 	message_slot4_timer = 3;

				// 	break;
					
				// // Change Theme
				// case SDLK_7: {

				// 	// Jump to next color theme
				// 	if ( display_color_theme < 5 ) {
				// 		display_color_theme ++;
				// 	} else {
				// 		display_color_theme = 0;
				// 	}
					
				// 	//Select surfaces based on key press
				// 	switch( display_color_theme )
				// 	{
				// 		// Black and White
				// 		case 0:
				// 			display_pixel_ON_color_alt	= 0xFFFFFFFF;
				// 			display_pixel_OFF_color_alt	= 0xFF000000;

				// 			display_update_theme();
				// 			break;

				// 		// White and Black
				// 		case 1: {
				// 			// New colors
				// 			display_pixel_ON_color_alt	= 0xFF000000;
				// 			display_pixel_OFF_color_alt	= 0xFFFFFFFF;

				// 			display_update_theme();
				// 			break;
				// 		}

				// 		// Grey Wolfand and Crystal Blue
				// 		case 2: {
				// 			// New colors
				// 			display_pixel_ON_color_alt	= 0xFF5CB3FF;
				// 			display_pixel_OFF_color_alt	= 0xFF504A4B;

				// 			display_update_theme();
				// 			break;
				// 		}

				// 		// Cloudy Gray and Emerald Green
				// 		case 3: {
				// 			// New colors
				// 			display_pixel_ON_color_alt	= 0xFF50C878;
				// 			display_pixel_OFF_color_alt	= 0xFF6D6968;

				// 			display_update_theme();
				// 			break;
				// 		}

				// 		// Night Black and Pastel Yellow
				// 		case 4: {
				// 			// New colors
				// 			display_pixel_ON_color_alt	= 0xFFFAF884;
				// 			display_pixel_OFF_color_alt	= 0xFF0C090A;

				// 			display_update_theme();
				// 			break;
				// 		}


				// 		// Grey and LightCoral Pink
				// 		case 5: {
				// 			// New colors
				// 			display_pixel_ON_color_alt	= 0xFFF08080;
				// 			display_pixel_OFF_color_alt	= 0xFF1C1C1C;

				// 			display_update_theme();
				// 			break;
				// 		}

				// 	}

				// 	// -------- Message slot 4 -------- //

				// 	// Show Message
				// 	sprintf(string_msg4, "Theme %d", display_color_theme);
				// 	font_update_msg4(renderer);

				// 	// Draw
				// 	display_draw(frame_counter, &scene);
				// 	message_slot4_timer = 3;

				// 	break;
				// }

				// // Show Emulator Information on screen
				// case SDLK_8:
				// 	msg_emuinfo = !msg_emuinfo;

				// 	// First update must be immediate
				// 	if ( msg_emuinfo ) {
				// 		// -------- Message slot 1 -------- //
				// 		strcpy(string_msg1, "Emulator Cycles per second: -");
				// 		font_update_msg1(renderer);
				// 		// -------- Message slot 2 -------- //
				// 		strcpy(string_msg2, "CPU Clock: -");
				// 		font_update_msg2(renderer);
				// 		// -------- Message slot 3 -------- //
				// 		strcpy(string_msg3, "FPS: -");
				// 		font_update_msg3(renderer);

				// 		// Draw
				// 		display_draw(frame_counter, &scene);
				// 	} else {
				// 		// Clean messages
				// 		strcpy(string_msg1, "");
				// 		strcpy(string_msg2, "");
				// 		strcpy(string_msg3, "");
				// 	}
				// 	break;

				// // Debug
				// case SDLK_9:
				// 	cpu_debug_mode = !cpu_debug_mode;

				// 	if (cpu_debug_mode ) {
				// 		// -------- Message slot 4 -------- //
				// 		strcpy(string_msg4, "Debug mode: ENABLED");
				// 		font_update_msg4(renderer);

				// 	} else {
				// 		// -------- Message slot 4 -------- //
				// 		strcpy(string_msg4, "Debug mode: DISABLED");
				// 		font_update_msg4(renderer);
				// 	}

				// 	// Draw
				// 	display_draw(frame_counter, &scene);
				// 	message_slot4_timer = 3;

				// 	break;

				// // Reset
				// case SDLK_0:
				// 	cpu_reset();

				// 	// -------- Message slot 4 -------- //
				// 	strcpy(string_msg4, "RESET");
				// 	font_update_msg4(renderer);

				// 	// Draw
				// 	display_draw(frame_counter, &scene);
				// 	message_slot4_timer = 3;

				// 	break;

				case SDLK_ESCAPE:
					quit = true;
					break;
			}

		} else if (event.type == SDL_KEYUP) {
			
			//Select surfaces based on key press
			switch( event.key.keysym.sym )
			{
				case SDLK_1:
					Key[0x1] = 0;
					break;

				case SDLK_2:
					Key[0x2] = 0;
					break;

				case SDLK_3:
					Key[0x3] = 0;
					break;

				case SDLK_4:
					Key[0xC] = 0;
					break;

				case SDLK_q:
					Key[0x4] = 0;
					break;

				case SDLK_w:
					Key[0x5] = 0;
					break;

				case SDLK_e:
					Key[0x6] = 0;
					break;

				case SDLK_r:
					Key[0xD] = 0;
					break;

				case SDLK_a:
					Key[0x7] = 0;
					break;

				case SDLK_s:
					Key[0x8] = 0;
					break;

				case SDLK_d:
					Key[0x9] = 0;
					break;

				case SDLK_f:
					Key[0xE] = 0;
					break;

				case SDLK_z:
					Key[0xA] = 0;
					break;

				case SDLK_x:
					Key[0x0] = 0;
					break;

				case SDLK_c:
					Key[0xB] = 0;
					break;

				case SDLK_v:
					Key[0xF] = 0;
					break;

				// Remap Keys
				case SDLK_UP:
					if ( input_remap_flag )
						Key[input_remap_btn_UP] = 0;
					
					break;
				
				case SDLK_DOWN:
					if ( input_remap_flag )
						Key[input_remap_btn_DOWN] = 0;
					
					break;		

				case SDLK_LEFT:
					if ( input_remap_flag )
						Key[input_remap_btn_LEFT] = 0;
					
					break;

				case SDLK_RIGHT:
					if ( input_remap_flag )
						Key[input_remap_btn_RIGHT] = 0;
					
					break;

				case SDLK_SPACE:
					if ( input_remap_flag )
						Key[input_remap_btn_SPACE] = 0;
					
					break;
			}

		} else if (event.type == SDL_QUIT)
		{
			quit = true;
		}

		// Nuklear Input Handle
		nk_sdl_handle_event(&event);
	}

	// Nuklear Input Handling End
	nk_input_end(ctx);
}

void input_keyboard_remaps(void) {
	input_remap_flag = false;


	// ---------------------- CHIP8 ---------------------- //

	// Game "Blinky [Hans Christian Egeberg, 1991].ch8"
	if ( !strcmp(game_signature, "121A322E303020432E20+203129") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x3;
		input_remap_btn_DOWN	= 0x6;
		input_remap_btn_LEFT	= 0x7;
		input_remap_btn_RIGHT	= 0x8;
		printf("Keys remaped to Arrows.\n");
	}

	// Game "Blinky [Hans Christian Egeberg] (alt).ch8"
	if ( !strcmp(game_signature, "00E0121A4368722E2045+174546") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x2;
		input_remap_btn_DOWN	= 0x8;
		input_remap_btn_LEFT	= 0x4;
		input_remap_btn_RIGHT	= 0x6;
		printf("Keys remaped to Arrows.\n");
	}

	// CHIP-8 Game "Syzygy [Roy Trevino, 1990].ch8"
	if ( !strcmp(game_signature, "12128D8D20A931393930+88372") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x3;
		input_remap_btn_DOWN	= 0x6;
		input_remap_btn_LEFT	= 0x7;
		input_remap_btn_RIGHT	= 0x8;
		printf("Keys remaped to Arrows, C, F and V\n");
	}
	
	// CHIP-8 Game "Tank.ch8"
	if ( !strcmp(game_signature, "123076FB602080654F00+47957") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x8;
		input_remap_btn_DOWN	= 0x2;
		input_remap_btn_LEFT	= 0x4;
		input_remap_btn_RIGHT	= 0x6;
		input_remap_btn_SPACE 	= 0x5;
		printf("Keys remaped to Arrows and SPACE.\n");
	}

	// CHIP-8 Game "Pong (1 player).ch8"
	if ( !strcmp(game_signature, "6A026B0C6C3F6D0CA2EA+25041") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x1;
		input_remap_btn_DOWN	= 0x4;
		printf("Keys remaped to UP and DOWN.\n");
	}
}
