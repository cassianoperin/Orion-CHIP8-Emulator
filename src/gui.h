#pragma once
#include "typedef.h"

/* Nuklear Flags */
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"

/* Nuklear Colors*/
const struct nk_color nk_red = {255,0,0,255};
const struct nk_color nk_green = {0,255,0,255};
const struct nk_color nk_blue = {0,0,255,255};
const struct nk_color nk_white = {255,255,255,255};
const struct nk_color nk_black = {0,0,0,255};
const struct nk_color nk_gray = {120,120,120,255};
const struct nk_color nk_yellow = {255,255,0,255};

// --------------------------------- External Variables --------------------------------- //
// Main
extern bool quit;
// SDL Video
extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern SDL_Texture  *texture;
// GUI
extern struct nk_context *ctx;
extern float font_scale; // GUI Font
// Display
extern unsigned char display_SCREEN_WIDTH_X;
extern unsigned char display_SCREEN_HEIGHT_Y;
extern unsigned char display_SCALE;

// --------------------------------- External Functions --------------------------------- //
// NFD Extended
extern int gui_loadrom(void);

// ---------------------------------- Global Variables ---------------------------------- //
bool show_menu; // Show Menu Flag

// -------------------------------------- Functions ------------------------------------- //
void gui_init(void);
int menu(struct nk_context *ctx);
