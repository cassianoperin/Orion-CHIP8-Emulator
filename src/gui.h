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
extern bool rom_format_hex;
// SDL Video
extern SDL_Window   *window;
extern SDL_Renderer *renderer;
// extern SDL_Texture  *texture;
extern SDL_Window   *window_debug;
extern SDL_Renderer *renderer_debug;
// GUI
extern struct nk_context *ctx;
extern float font_scale; // GUI Font
extern bool cpu_rom_loaded;
// CPU
extern bool cpu_debug_mode;
extern unsigned int CPU_CLOCK;
// Sound
extern bool sound_enabled;
// Display
extern unsigned char display_SCREEN_WIDTH_X;
extern unsigned char display_SCREEN_HEIGHT_Y;
extern unsigned int display_SCALE;
extern unsigned int  display_pixel_ON_color_alt;   // New color of enabled pixels
extern unsigned int  display_pixel_OFF_color_alt;  // New color of disabled pixels
extern unsigned int display_pixel_ON_color_tmp;    // Keep the new theme if choosen in Pause Menu
extern unsigned int display_pixel_OFF_color_tmp;   // Keep the new theme if choosen in Pause Menu
extern bool display_fullscreen;
// Quirks
extern bool quirk_VF_Reset_8xy1_8xy2_8xy3;
extern bool quirk_Memory_legacy_Fx55_Fx65;
extern bool quirk_display_wait;
extern bool quirk_Clipping_Dxyn;
extern bool quirk_Shifting_legacy_8xy6_8xyE;
extern bool quirk_Jump_with_offset_Bnnn;

// --------------------------------- External Functions --------------------------------- //
// NFD Extended
extern int lib_gui_loadrom(void);
// Display
extern void display_update_theme(void);
extern void display_updateWindowSize(unsigned int pixel_scale);
bool display_debug_init(void);
// CPU
extern void cpu_reset(void);
// Font
extern void showLogo(void);

// ---------------------------------- Global Variables ---------------------------------- //
bool gui_show_menu; // Show Menu Flag
bool gui_menu_quirks_inactive; // Enable/Disable Quirks Menu
char gui_statusbar_msg[100];

// -------------------------------------- Functions ------------------------------------- //
void gui_init(void);
int menu(struct nk_context *ctx);
int status_bar(struct nk_context *ctx);

