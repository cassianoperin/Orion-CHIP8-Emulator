#pragma once
#include "typedef.h"

/* Nuklear Flags */
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"

// --------------------------------- External Variables --------------------------------- //
// SDL Video
extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern SDL_Texture  *texture;
// GUI
extern struct nk_context *ctx;
extern float font_scale; // GUI Font

// ---------------------------------- Global Variables ---------------------------------- //
bool show_menu; // Show Menu Flag

// -------------------------------------- Functions ------------------------------------- //
void gui_init(void);
int menu(struct nk_context *ctx);
