#pragma once
#include "typedef.h"

/* Nuklear Flags */
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
// #define NK_INCLUDE_DEFAULT_ALLOCATOR
// #define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
// #define NK_INCLUDE_FONT_BAKING
// #define NK_INCLUDE_DEFAULT_FONT
// #define NK_IMPLEMENTATION
// #define NK_SDL_RENDERER_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"
#include "display_emu.h"
// #include "overview.c"


// --------------------------------- External Variables --------------------------------- //
// Main
extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern SDL_Texture  *texture;
// Nuklear
extern struct nk_context *ctx;
// Quirk
extern bool quirk_display_wait;
// GUI
unsigned int gui_pixels_logo[2048];

// --------------------------------- External Functions --------------------------------- //
// Display
extern int menu(struct nk_context *ctx);
extern int status_bar(struct nk_context *ctx);
extern int overview(struct nk_context *ctx);

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
// void display_update_theme(void);
void draw_graphics_console(void);
void display_updateWindowSize(unsigned int pixel_scale);
