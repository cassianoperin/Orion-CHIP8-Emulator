#pragma once
#include "typedef.h"

// /* Nuklear Flags */
#define INT_MAX 50
#define INT_MIN 0
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_STANDARD_VARARGS
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"

// // --------------------------------- External Variables --------------------------------- //
// // GUI
// extern const struct  nk_color nk_white;
// // CPU
// extern unsigned int  CPU_CLOCK;
// extern unsigned char Memory[4096];
// // Display
// extern unsigned char display_pixels[8192];
// extern unsigned int  display_EMULATOR_RES_X;
// extern unsigned int  display_EMULATOR_RES_Y;

// // ---------------------------------- Global Variables ---------------------------------- //
// char guiDebug_mem_addr_msg[6];
// char guiDebug_mem_emuinfo_msg[50];

// // -------------------------------------- Functions ------------------------------------- //
int win_debug_opc(struct nk_context *ctx);
