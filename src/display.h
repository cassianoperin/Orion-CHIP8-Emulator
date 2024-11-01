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
extern unsigned int gui_pixels_logo[2048];
extern unsigned int gui_menu_heigth;
// CPU
extern bool cpu_debug_mode;
extern bool cpu_rom_loaded;

// --------------------------------- External Functions --------------------------------- //
// GUI
extern int menu(struct nk_context *ctx);
extern int status_bar(struct nk_context *ctx);
extern int win_debug_mem(struct nk_context *ctx);
// GUI Emu
extern void win_emulator(struct nk_context *ctx);
// GUI Sprite
extern void win_debug_sprite(struct nk_context *ctx);
// GUI Reg
extern int win_debug_reg(struct nk_context *ctx);
// GUI Opc
extern int win_debug_opc(struct nk_context *ctx);

// ---------------------------------- Global Variables ---------------------------------- //
// Window size
unsigned int display_WINDOW_WIDTH_X;
unsigned int display_WINDOW_HEIGHT_Y;

// Display (Screen size)
unsigned int display_EMULATOR_RES_X;
unsigned int display_EMULATOR_RES_Y;
unsigned int display_EMULATOR_RES_SCALE;
unsigned int display_menu_heigth;

bool display_fullscreen;
// Colors
unsigned char display_pixel_ON_color;
unsigned char display_pixel_OFF_color;
unsigned char display_color_theme;          // Theme number

// Display Array
// unsigned int  display_pixels[2048];
unsigned char  display_pixels[8192];

// Frames per second
unsigned char display_FPS;

// Debug Pixels
bool debug_pixels;                          // Print pixels to console

// Frame Counters
unsigned int frame = 0;                      // Frame counter
unsigned int frame_counter = 0;              // Frame per second

// Debug mode
unsigned int display_WINDOW_WIDTH_X_tmp; // Keep original pixel scale after leaving debug mode
unsigned int display_WINDOW_HEIGHT_Y_tmp;
unsigned int display_EMULATOR_RES_SCALE_tmp; 


// -------------------------------------- Functions ------------------------------------- //
bool display_init(void);
bool display_draw(void);
void SDL_close(void);
// void display_update_theme(void);
void draw_graphics_console(void);
void display_updateWindowSize(unsigned int pixel_scale);
