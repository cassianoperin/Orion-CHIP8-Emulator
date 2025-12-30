#include "input.h"

// Handle Inputs
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
				

				// ---------- Remap Keys ----------- //
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

				// ----------- Interface ----------- //

				// Pause
				case SDLK_p:
					if ( cpu_rom_loaded )
						cpu_pause = !cpu_pause;

					break;

				// Sound
				case SDLK_o:
					sound_enabled = !sound_enabled;

					if (sound_enabled ) {
						printf("Sound: ENABLED\n");
					} else {
						printf("Sound: DISABLED\n");
					}

					break;

				// Step Forward
				case SDLK_i:

					if (cpu_pause ) {
							cpu_interpreter();
						printf("CPU: STEP FORWARD\n");
					}

					break;
				
				// Fullscreen
				case SDLK_RIGHTBRACKET:
					
					display_fullscreen = !display_fullscreen;

					if ( display_fullscreen ) {
						display_EMULATOR_RES_SCALE = 20; // To ensure that will fill entire screen
						display_updateWindowSize(display_EMULATOR_RES_SCALE);
						SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
						
					} else {
						display_EMULATOR_RES_SCALE = 10; // To ensure that will fill entire screen
						display_updateWindowSize(display_EMULATOR_RES_SCALE);
						SDL_SetWindowFullscreen(window, 0);
						SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
					}

					break;	

				// Reduce Clock
				case SDLK_5:
					if ( CPU_CLOCK >= video_system_freq + 10) {
						CPU_CLOCK -= 10;

						printf("Clock %d\n", CPU_CLOCK);
					} else {
						printf("Clock %d - Minimum Allowed\n", CPU_CLOCK);
					}

					break;
				
				// Increase Clock
				case SDLK_6:
					if ( CPU_CLOCK < Max_Overclock) {
						CPU_CLOCK += 10;

						printf("Clock %d\n", CPU_CLOCK);

					} else {
						printf("Clock %d - Maximum Allowed\n", CPU_CLOCK);

					}

					break;
					
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

				// 	// Show Message
				// 	printf("Theme %d\n", display_color_theme);

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

				// Debug
				case SDLK_9:
					cpu_debug_mode = !cpu_debug_mode;

					if ( cpu_debug_mode ) {
						// Resize main Window
						display_EMULATOR_RES_SCALE_tmp = display_EMULATOR_RES_SCALE;
						display_WINDOW_WIDTH_X_tmp = display_WINDOW_WIDTH_X;
						display_WINDOW_HEIGHT_Y_tmp = display_WINDOW_HEIGHT_Y;
						display_EMULATOR_RES_SCALE = 9;
						nk_window_set_bounds(ctx, "Emulator", nk_rect(0, 36, (display_EMULATOR_RES_X * display_EMULATOR_RES_SCALE) + 4, (display_EMULATOR_RES_Y * display_EMULATOR_RES_SCALE) + 34 ) );

						// Set debug resolution (720p)
						display_WINDOW_WIDTH_X		= 1280;
						display_WINDOW_HEIGHT_Y 	=  720;
						SDL_SetWindowSize (window, display_WINDOW_WIDTH_X, display_WINDOW_HEIGHT_Y);
						SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

						// Set Emulation Windows focus
						nk_window_set_focus(ctx, "Emulator");
					
					} else {

						// Set the default emulator message status in status bar
						if ( cpu_rom_loaded )
							strcpy(gui_statusbar_msg, "ROM loaded");
						else
							strcpy(gui_statusbar_msg, "No ROM loaded");

						nk_window_set_focus(ctx, "Emulator");
						
						// Resize main Window
						display_WINDOW_WIDTH_X     = display_WINDOW_WIDTH_X_tmp;
						display_WINDOW_HEIGHT_Y    = display_WINDOW_HEIGHT_Y_tmp;
						display_EMULATOR_RES_SCALE = display_EMULATOR_RES_SCALE_tmp;

						// Return main window size
						SDL_SetWindowSize (window, display_WINDOW_WIDTH_X, display_WINDOW_HEIGHT_Y);
						SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
						// Draw Emulator Window
						nk_window_set_bounds(ctx, "Emulator", nk_rect(0, 36, display_EMULATOR_RES_X * 1, display_EMULATOR_RES_Y * display_EMULATOR_RES_SCALE ));
					}


					break;

				// Reset
				case SDLK_0:

					if ( cpu_rom_loaded ) {
						cpu_reset();
					}

					break;

				case SDLK_ESCAPE:
					if ( cpu_rom_loaded ) {
						cpu_pause = !cpu_pause;

						if (cpu_pause ) {
							// Update the status bar message
							char str[100];
							sprintf(str, "PAUSED!");
							strcpy(gui_statusbar_msg, str);
						} else {
							// Update the status bar message
							char str[100];
							sprintf(str, "ROM loaded");
							strcpy(gui_statusbar_msg, str);
						}
					}
					
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
					// if ( input_remap_flag )
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
			// When last window is closed, the SDL_QUIT is triggered
			quit = true;
		}

		// Nuklear Input Handle
		nk_sdl_handle_event(&event);
	}

	// Nuklear Input Handling End
	nk_input_end(ctx);
}


// Emulator key remaps
void input_keyboard_remaps(char *rom_sha1) {
	input_remap_flag = false;

	// ---------------------- CHIP8 ---------------------- //

	// Game "Blinky [Hans Christian Egeberg, 1991].ch8"
	if ( !strcmp(rom_sha1, "d40abc54374e4343639f993e897e00904ddf85d9") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x3;
		input_remap_btn_DOWN	= 0x6;
		input_remap_btn_LEFT	= 0x7;
		input_remap_btn_RIGHT	= 0x8;
		printf("Keys remaped to Arrows.\n");
	}

	// Game "Blinky [Hans Christian Egeberg] (alt).ch8"
	if ( !strcmp(rom_sha1, "f4169141735d8d60e51409ca7e73f4adedcefef2") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x2;
		input_remap_btn_DOWN	= 0x8;
		input_remap_btn_LEFT	= 0x4;
		input_remap_btn_RIGHT	= 0x6;
		printf("Keys remaped to Arrows.\n");
	}

	// CHIP-8 Game "Syzygy [Roy Trevino, 1990].ch8"
	if ( !strcmp(rom_sha1, "1bdb4ddaa7049266fa3226851f28855a365cfd12") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x3;
		input_remap_btn_DOWN	= 0x6;
		input_remap_btn_LEFT	= 0x7;
		input_remap_btn_RIGHT	= 0x8;
		printf("Keys remaped to Arrows, C, F and V\n");
	}
	
	// CHIP-8 Game "Tank.ch8"
	if ( !strcmp(rom_sha1, "18b9d15f4c159e1f0ed58c2d8ec1d89325d3a3b6") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x8;
		input_remap_btn_DOWN	= 0x2;
		input_remap_btn_LEFT	= 0x4;
		input_remap_btn_RIGHT	= 0x6;
		input_remap_btn_SPACE 	= 0x5;
		printf("Keys remaped to Arrows and SPACE.\n");
	}

	// CHIP-8 Game "Pong (1 player).ch8"
	if ( !strcmp(rom_sha1, "607c4f7f4e4dce9f99d96b3182bfe7e88bb090ee") ) {
		input_remap_flag = true;
		input_remap_btn_UP		= 0x1;
		input_remap_btn_DOWN	= 0x4;
		printf("Keys remaped to UP and DOWN.\n");
	}
}
