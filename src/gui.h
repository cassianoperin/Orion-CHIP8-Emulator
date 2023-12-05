#pragma once
/* Nuklear Flags */
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "../lib/nuklear.h"
#include "../lib/nuklear_sdl_renderer.h"

// --------------------------------- External Variables --------------------------------- //
// SDL Video
extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern SDL_Texture  *texture;
// GUI
extern struct nk_context *ctx;
extern float font_scale; // GUI Font

// -------------------------------------- Functions ------------------------------------- //
void gui_init(void);
int menu(struct nk_context *ctx);

