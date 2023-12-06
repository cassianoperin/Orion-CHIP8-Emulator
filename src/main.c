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



	// -------------------------- SDL Init -------------------------- //
	display_init();

 	// -------------------------- GUI Init -------------------------- //
    gui_init();

	// ----------------------- Infinite Loop  ----------------------- //
    while ( !quit )
    {

        // ------------- Keyboard ------------- //
        input_keyboard();

        // ---------------- Menu -------------- //
        menu(ctx);



        // --------------- Draw --------------- //
        display_draw(frame);


    }

	//Free resources and close SDL
	sound_close();
    nk_sdl_shutdown(); // Nuklear
	SDL_close();

    return 0;
}
