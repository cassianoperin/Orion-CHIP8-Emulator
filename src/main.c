/* SDL2 */
#include <SDL2/SDL.h>
#include "main.h"

/* ===============================================================
 *
 *                          MAIN
 *
 * ===============================================================*/

int main(int argc, char *argv[])
{

	// ------------ Constants ------------ //
	const float msPerFrame =  1 / (float) pal_freq; // 16 ms per frame (0.016667) on NTSC, 20ms (0,02) on PAL

	// ------------ Variables ------------ //

	// Timing
	uint64_t perfFrequency        = SDL_GetPerformanceFrequency();		// Platform independent frequency
	uint64_t msPerFrameInt        = msPerFrame * perfFrequency;			// Time per frame in the deltas format
	uint64_t timeFrameStartCount  = 0;									// Start of frame counter
	uint64_t timeFrameLastCount   = SDL_GetPerformanceCounter();		// End of frame counter
	uint64_t timeFrameDuration    = 0;									// Duration of a frame
	uint64_t timeFrameDurationSum = 0;									// Sum of all frames into a second
	uint64_t timeDeltaOperations  = 0;									// Time spent into the operations (part 1)
	uint64_t timeDeltaSleep       = 0;									// Time spent sleeping (part 2)
	int      timeFrameSleep       = 0;									// Time in ms to sleep after al  l frame executions
	// FPS
	uint64_t timeSecondStart      = 0;									// Measurement of time spent on last frame
	uint64_t timeSecondLast       = 0;									// Measurement of time spent on last frame

	// CPU
	float opcodesPerFrameResidualSum = 0;								// CPU clock fine adjustment

	// Timing debug
	bool debug_timing = false;

	// Main loop control
	quit = false;

	// --------- Initialization ---------- //
    
    // Initialize
	cpu_initialize();

    // Initialize Audio System
	sound_init();

	// // CLI and argument validation
	// command_line_interface(argc, argv);

	// Load Game into Memory
	// filename = argv[1];
	// load_rom(filename,  Memory, (sizeof(Memory) / sizeof(Memory[0])) );

	// // Get Game signature for Qwirks
	// game_signature = get_game_signature(filename);
	// printf("Signature:   %s\n", game_signature );

	// // Check for Quirks
	// handle_quirks(game_signature);

	// Load Fonts
	// cpu_load_fonts();

	// // Keyboard remaps
	// input_keyboard_remaps();

	// -------------------------- SDL Init -------------------------- //
	display_init();

 	// -------------------------- GUI Init -------------------------- //
    gui_init();

	// Seconds Counter
	timeSecondStart = SDL_GetPerformanceCounter();

	// ----------------------- Infinite Loop  ----------------------- //
    while ( !quit )
    {
		// --------------------------------- START OF SECONDs COUNTER  --------------------------------- //
		if ( timeSecondLast - timeSecondStart >= 1000000000 ){ 

			// // Seconds Ticker validation
			// printf("Second: %lld\n", timeSecondLast - timeSecondStart );
			// printf ("FINAL 60FPS time: %llu\n\n", timeFrameDurationSum);

			// Window Title Message update
			char title_msg[80];
			sprintf(title_msg, "Cycles per sec.: %d\t\tFPS: %d   Freq: %dhz   ms: %llu", cycle_counter, frame_counter, pal_freq, timeFrameDurationSum);
			SDL_SetWindowTitle(window, title_msg);

			// if ( msg_emuinfo ) {
			// 	// -------- Message slot 1 -------- //
			// 	showCPS(cycle_counter); 	// Update string_msg1	
			// 	font_update_msg1(renderer);

			// 	// -------- Message slot 2 -------- //
			// 	showCPU_CPS(cycle_counter_cpu);
			// 	font_update_msg2(renderer);

			// 	// -------- Message slot 3 -------- //
			// 	showFPS(frame_counter);
			// 	font_update_msg3(renderer);
			// }

			// // Message slot 4 timer
			// // if ( !cpu_pause) {
			// 	if ( message_slot4_timer > 0 ) {
			// 		message_slot4_timer --;

			// 		// When reach zero, clear
			// 		if ( message_slot4_timer == 0 ) {
			// 			// strcpy(string_msg4, "");
			// 		}
			// 	}	
			// // }

			// --------- Reset Counters ---------- //
			// Main cycle
			cycle_counter = 0;
			// Frame
			frame = 0;
			frame_counter = 0;
			timeFrameDurationSum = 0;
			// CPU
			cycle_counter_cpu = 0;
			// Second
			timeSecondStart = SDL_GetPerformanceCounter(); // Reset seconds counter
			opcodesPerFrameResidualSum = 0;

		}

		// Timing: Start frame
		timeFrameStartCount = SDL_GetPerformanceCounter();

		// Increment Cycle per second counter
		cycle_counter++;
		// ---------------------------------- END OF SECONDs COUNTER  ---------------------------------- //



		// --------------------------- P1: START OF FRAME OPERATIONS  --------------------------- //

		// ------------- Keyboard ------------ //
		input_keyboard();

		// ----------- Delay Timer ----------- //
		if ( DelayTimer > 0 ) {
			DelayTimer--;
		}

		// ----------- Sound Timer ----------- //
		if ( SoundTimer > 0 ) {			// Just play if sound flag is enabled
			if ( sound_enabled ) {
				if ( !playing_sound ) {
					// Start playing the beep
					SDL_PauseAudioDevice(audio_device_id, 0);
					
					// Avoid starting again when already playing the sound
					playing_sound = true;
				}
			}
			SoundTimer--;
		} else {
			if ( playing_sound ) {
				// Stop sound
				SDL_PauseAudioDevice(audio_device_id, 1);

				// Avoid starting again when already playing the sound
				playing_sound = false;
			}
		}

		// Draw screen (game and text messages)
		if ( quirk_display_wait ) {

			// Draw
			display_draw(frame);

		}

		// --------------- CPU --------------- //
		float opcodesPerFrame = (float)CPU_CLOCK / pal_freq;					// Opcodes per frame (float)
		// printf("Opcodes: %f\n",opcodesPerFrame);
		float opcodesPerFrameResidual = opcodesPerFrame - (int)opcodesPerFrame;	// Opcodes per frame residual
		// printf("Residual: %f\n",opcodesPerFrameResidual);
		// printf("Sum anterior: %f\n",opcodesPerFrameResidualSum);
		opcodesPerFrameResidualSum += opcodesPerFrameResidual;					// Opcode residual from last frame
		// printf("Sum: %f\n\n",opcodesPerFrameResidualSum);
		
		for( int i = 0 ; i < ( (int)opcodesPerFrame ) ; i++) {
			if ( !cpu_pause ) {

				// Just run the interpreter if a rom was selected
				if ( cpu_rom_loaded ) {
					cpu_interpreter();
				}
				
				// If in original draw mode, check for draw flag and draw to screen, not syncing with vsync
				if ( !quirk_display_wait ) {
					if ( cpu_draw_flag ) {
						// Draw
						display_draw(frame);
						// Reset the draw flag
						cpu_draw_flag = false;
					}
				}

				// Sum the residual to add an aditional frame if necessary
				if ( opcodesPerFrameResidualSum > 1 ) {

					// Just run the interpreter if a rom was selected
					if ( cpu_rom_loaded ) {
						cpu_interpreter();
					}

					if ( !quirk_display_wait ) {
						if ( cpu_draw_flag ) {
							// Draw
							display_draw(frame);
							// Reset the draw flag
							cpu_draw_flag = false;
						}
					}

					// Update the residual opcode sum counter
					opcodesPerFrameResidualSum = opcodesPerFrameResidualSum - 1;
				}
			}
		}
		



		// ------------------- P2: START OF FRAME OPERATIONS TIME MEASUREMENT  ------------------ //
		// Timing: Update timeFrameLastCount adding the time spent on operations
		timeFrameLastCount = SDL_GetPerformanceCounter();
		timeDeltaOperations = timeFrameLastCount - timeFrameStartCount;
		// Timing: Transform operations delta into seconds view
		float timeFrameSecondsOperations = timeDeltaOperations / (float) perfFrequency;

		// Debug Timing
		if ( debug_timing ) {
			printf("Frame: %02d OPERATIONS:\tperfFrequency: %llu\ttimeFrameStartCount: %llu\ttimeDeltaOperations: %llu\ttimeFrameDuration: %llu\ttimeFrameSecondsOperations: %fs\tmsPerFrame:%fms\n",
				frame, perfFrequency, timeFrameStartCount, timeDeltaOperations, timeFrameLastCount, timeFrameSecondsOperations, msPerFrame );
		}

		
		// ------------------------------ P3: START OF FRAME SLEEP  ----------------------------- //

		// if we have time remaining on this frame, sleep
		if ( timeFrameSecondsOperations <= msPerFrame ) {

			// Get the integer part of the remaining time
			timeFrameSleep = 1000 * (msPerFrame - timeFrameSecondsOperations);
			
			// I've reduced 2 ms from the sleep due to its imprecision, to avoid sleep more than the time of the frame
			// and later sleep more with fine adjustment
			if ( timeFrameSleep > 2 ) {
				SDL_Delay(timeFrameSleep - 2);

				// Count the exact ammount of time spent for the sleep function	
				uint64_t timeFrameSleepCount = SDL_GetPerformanceCounter();
				timeDeltaSleep = timeFrameSleepCount - timeFrameLastCount;
				if ( debug_timing ) {
					printf("SLEEP:\t\ttimeFrameSleep: %dms\ttimeDeltaSleep(real time spent on sleep): %llu\tTotal frame time: %llu\n",
						timeFrameSleep-2, timeDeltaSleep, timeDeltaOperations + timeDeltaSleep);
				}
			} else {
				if ( debug_timing ) {
					printf("SLEEP:\t\tNo time added\n");
				}
			}

			// If entered here, update the last frame count
			timeFrameLastCount = SDL_GetPerformanceCounter();
		}
		
		// Sum the time spent in operation + sleep to have the total cycle time
		timeFrameDuration = timeDeltaOperations + timeDeltaSleep;


		// ------------------------------ P4: START OF FINE SLEEP  ------------------------------ //
		// Use main cycle loop to have precision on frames and seconds counter
		while (timeFrameDuration < msPerFrameInt ) {
			timeFrameStartCount = SDL_GetPerformanceCounter();
			timeDeltaOperations = timeFrameStartCount - timeFrameLastCount;
			timeFrameDuration += timeDeltaOperations;
			// If entered here, update the last frame count
			timeFrameLastCount = timeFrameStartCount;

			// It will generate a LOT of logs, take care
			// if ( debug_timing ) {
			// 	// printf("FINE: Loop to spent cycle %d time: %llu\t\tTotal frame time: %llu\n", counterFrames, timeDeltaOperations, timeFrameDuration);
			// }

			// If entered here, update the cycle counter
			cycle_counter++;
		}

		// Debug Timing
		if ( debug_timing ) {
			printf("Final frame time: %llu\n\n", timeFrameDuration);
		}

		// Update the timeFrameDuration with the timing of the last cycle
		timeFrameDurationSum += timeFrameDuration;

		// // Increment frame counter
		frame ++;

		// Increment Main Loop Cycle
		// cycle++;

		// Seconds Counter
		timeSecondLast = SDL_GetPerformanceCounter();


    }

	//Free resources and close SDL
	sound_close();
    nk_sdl_shutdown(); // Nuklear
	SDL_close();

    return 0;
}
