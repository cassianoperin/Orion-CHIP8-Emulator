#pragma once
#include "typedef.h"

#include "nuklear.h"
#include "nuklear_sdl_renderer.h"

// --------------------------------- External Variables --------------------------------- //
// Main
extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern SDL_Texture  *texture;
// Nuklear
extern struct nk_context *ctx;
// Quirk
extern bool quirk_display_wait;

// --------------------------------- External Functions --------------------------------- //
// Display
extern int menu(struct nk_context *ctx);
extern int status_bar(struct nk_context *ctx);

// ---------------------------------- Global Variables ---------------------------------- //
// Window size
unsigned int display_WINDOW_WIDTH_X;
unsigned int display_WINDOW_HEIGHT_Y;

// Display (Screen size)
unsigned char display_EMULATOR_RES_X;
unsigned char display_EMULATOR_RES_Y;
unsigned int  display_EMULATOR_RES_SCALE;
bool display_fullscreen;
// Colors
unsigned int  display_pixel_ON_color;
unsigned int  display_pixel_OFF_color;
unsigned char display_color_theme;          // Theme number
unsigned int  display_pixel_ON_color_alt;   // New color of enabled pixels
unsigned int  display_pixel_OFF_color_alt;  // New color of disabled pixels
unsigned int  display_pixel_ON_color_tmp;   // keep the theme color on pause
unsigned int  display_pixel_OFF_color_tmp;  // keep the theme color on pause

// Display Array
// unsigned int  display_pixels[2048];
unsigned int  display_pixels[8192];
// Frames per second
unsigned char display_FPS;
// Debug Pixels
bool debug_pixels;                          // Print pixels to console
// Frame Counters
unsigned int frame = 0;                      // Frame counter
unsigned int frame_counter = 0;              // Frame per second

// -------------------------------------- Functions ------------------------------------- //
bool display_init(void);
bool display_draw(void);
void SDL_close(void);
void display_update_theme(void);
void draw_graphics_console(void);
void display_updateWindowSize(unsigned int pixel_scale);
