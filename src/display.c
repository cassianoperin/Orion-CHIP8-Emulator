#include <SDL2/SDL.h>
#include "display.h"

bool display_init(void)
{
	// Initialization flag
	bool success = true;

	// Variables
	display_SCREEN_WIDTH_X  = 64;
	display_SCREEN_HEIGHT_Y = 32;
	display_SCALE			= 10;
	display_pixel_ON_color	= 0xFFFFFFFF;
	display_pixel_OFF_color	= 0xFF000000;
	display_color_theme		= 0;

	// Debug
	debug_pixels			= false;

	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		// Create window
		// window = SDL_CreateWindow( "CHIP8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, display_SCREEN_WIDTH_X * display_SCALE, display_SCREEN_HEIGHT_Y * display_SCALE, SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI );
		// window = SDL_CreateWindow( "CHIP8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, display_SCREEN_WIDTH_X * display_SCALE, display_SCREEN_HEIGHT_Y * display_SCALE, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		window = SDL_CreateWindow( "CHIP8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, display_SCREEN_WIDTH_X * display_SCALE, display_SCREEN_HEIGHT_Y * display_SCALE, SDL_WINDOW_SHOWN);
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			// --- Create renderer for window --- //
			// Display wait quirk enabled, enable vsync
			if ( quirk_display_wait ) {
				renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			} else {
				renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			}

			// Check for errors
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				// Create texture
				texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, display_SCREEN_WIDTH_X, display_SCREEN_HEIGHT_Y);
				if( renderer == NULL )
				{
					printf( "Texture could not be created! SDL Error: %s\n", SDL_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}


bool display_draw(unsigned int frame)
{
	//Initialization flag
	bool success = true;

	// Increment total frame counter
	frame ++;

	// Increment Frame Counter for FPS
	frame_counter++;

	// Update the Screen
	SDL_UpdateTexture(texture, NULL, display_pixels, display_SCREEN_WIDTH_X * sizeof(uint32_t));
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	// SDL_RenderPresent(renderer);

	// Draw GUI
	// SDL_SetRenderDrawColor(renderer, bg.r * 255, bg.g * 255, bg.b * 255, bg.a * 255);
	// SDL_RenderClear(renderer);
	nk_sdl_render(NK_ANTI_ALIASING_ON);

	// Draw
	SDL_RenderPresent(renderer);

	// Show Menu
	if ( gui_show_menu ) {
		SDL_RenderSetVSync(renderer, 1);
		menu(ctx);
		status_bar(ctx);
	} else {
		if ( quirk_display_wait ) {
			SDL_RenderSetVSync(renderer, 1);
		} else {
			SDL_RenderSetVSync(renderer, 0);
		}
	}
	
	// Draw to console
	// draw_graphics_console();

	return success;
}


void SDL_close(void)
{
	// Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

void display_update_theme(void){
	unsigned int i;

	// Update graphics vector with new colors
	for ( i = 0 ; i < 2048 ; i++ ) {
		if ( display_pixels[i] == display_pixel_ON_color ) {
			display_pixels[i] = display_pixel_ON_color_alt;
		} else {
			display_pixels[i] = display_pixel_OFF_color_alt;
		}
	}

	// Update the colors
	display_pixel_ON_color	= display_pixel_ON_color_alt;
	display_pixel_OFF_color	= display_pixel_OFF_color_alt;
}

// Print Graphics on Console
void draw_graphics_console(void) {

	int line, column, index = 0;

	while ( index < 2048 )
	{
		// Add an border
		printf("----------------------------------------------------------------------------------------------------------------------------------\n");

		// Lines
		for ( line = 0 ; line < 32 ; line ++ ) {

			// Add an border
			printf("|");

			// 00 ..  63
			// 64 .. 127
			// Columns
			for ( column = 0 ; column < 64 ; column ++ ) {
				if ( display_pixels[index+column] == display_pixel_ON_color ) {
					// printf("[] ");
					printf("X ");
				} else {
					// printf("   ");
					printf("  ");
				}
			}
			// Add an border
			printf("|");
			printf("\n");

			// Increment the index
			index += 64;
		}
	}

	// Add an border
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");

	// Space between screens
	printf("\n\n\n");

}

void display_updateWindowSize(unsigned int pixel_scale)
{
	SDL_SetWindowSize(window, display_SCREEN_WIDTH_X * pixel_scale , display_SCREEN_HEIGHT_Y * pixel_scale);
}
