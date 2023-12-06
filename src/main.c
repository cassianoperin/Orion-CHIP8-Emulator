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
	// sound_close();
    nk_sdl_shutdown(); // Nuklear
	SDL_close();

    return 0;
}
