#pragma once
#include "nuklear.h"

// --------------------------------- External Variables --------------------------------- //
/* Display */ 
extern unsigned char display_EMULATOR_RES_X;
extern unsigned char display_EMULATOR_RES_Y;
extern unsigned int  display_EMULATOR_RES_SCALE;
extern unsigned int  display_pixels[8192];
extern unsigned int  display_pixel_ON_color;

// -------------------------------------- Functions ------------------------------------- //
void win_emulator(struct nk_context *ctx);
