#pragma once

/* Nuklear Flags */
#define INT_MAX 50
#define INT_MIN 0
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
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
// GUI
extern const struct  nk_color nk_white;
// CPU
extern unsigned int  CPU_CLOCK;
extern unsigned char Memory[4096];
// Display
extern unsigned char display_pixels[8192];
extern unsigned int  display_EMULATOR_RES_X;
extern unsigned int  display_EMULATOR_RES_Y;

// ---------------------------------- Global Variables ---------------------------------- //
char guiDebug_mem_addr[6];
char guiDebug_emuinfo_msg[50];

// -------------------------------------- Functions ------------------------------------- //
int win_debug(struct nk_context *ctx);
