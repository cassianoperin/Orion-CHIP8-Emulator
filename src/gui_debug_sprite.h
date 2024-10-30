#pragma once
#include "nuklear.h"

// ---------------------------------- Global Variables ---------------------------------- //
// // background colors
// unsigned char bg_R = 0;
// unsigned char bg_G = 0;
// unsigned char bg_B = 0;
// // pixel colors
// unsigned char px_R = 255;
// unsigned char px_G = 255; 
// unsigned char px_B = 255; 

// --------------------------------- External Variables --------------------------------- //
/* Display */ 
extern unsigned int   display_EMULATOR_RES_X;
extern unsigned int   display_EMULATOR_RES_Y;
extern unsigned int   display_EMULATOR_RES_SCALE;
extern unsigned char  display_pixels[8192];
extern unsigned char  display_pixel_ON_color;
/* CPU */
extern unsigned short Opcode;
extern unsigned char  Memory[4096];
extern short I;

// -------------------------------------- Functions ------------------------------------- //
void win_debug_sprite(struct nk_context *ctx);
