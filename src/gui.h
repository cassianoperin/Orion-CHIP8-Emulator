#pragma once
#include "typedef.h"

/* Nuklear Flags */
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

/* Nuklear Colors*/
const struct nk_color nk_red = {255,0,0,255};
const struct nk_color nk_green = {0,255,0,255};
const struct nk_color nk_blue = {0,0,255,255};
const struct nk_color nk_light_blue = {0,255,255,255};
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
extern SDL_Texture  *texture;
// GUI
extern struct nk_context *ctx;
extern float font_scale; // GUI Font
extern bool cpu_rom_loaded;
// GUI EMU (background and pixel colors)
extern unsigned char bg_R;
extern unsigned char bg_G;
extern unsigned char bg_B;
extern unsigned char px_R;
extern unsigned char px_G;
extern unsigned char px_B;
// CPU
extern bool         cpu_debug_mode;
extern unsigned int CPU_CLOCK;
extern int          core;
extern int          core_current;
extern bool 	    cpu_pause;
extern bool         core_autodetection_enabled;

// Sound
extern bool sound_enabled;
// Display
extern unsigned int display_WINDOW_WIDTH_X;
extern unsigned int display_WINDOW_HEIGHT_Y;
extern unsigned int display_EMULATOR_RES_X;
extern unsigned int display_EMULATOR_RES_Y;
extern unsigned int display_EMULATOR_RES_SCALE;
extern unsigned int display_WINDOW_WIDTH_X_tmp;
extern unsigned int display_WINDOW_HEIGHT_Y_tmp;
extern unsigned int display_EMULATOR_RES_SCALE_tmp;
extern bool display_fullscreen;
// Quirks
extern bool quirk_VF_Reset_8xy1_8xy2_8xy3;
extern bool quirk_Memory_IncByX_Fx55_Fx65;
extern bool quirk_Memory_LeaveI_Fx55_Fx65;
extern bool quirk_display_wait;
extern bool quirk_Wrap_Dxyn;
extern bool quirk_Shifting_legacy_8xy6_8xyE;
extern bool quirk_Jump_with_offset_Bnnn;

// --------------------------------- External Functions --------------------------------- //
// NFD Extended
extern int lib_gui_loadrom(void);
// Display
extern void display_updateWindowSize(unsigned int pixel_scale);
extern unsigned int display_menu_heigth;
// CPU
extern void cpu_reset(void);
extern void cpu_initialize(void);
// Font
extern void showLogo(void);
// Quirks
extern void handle_quirks(DB_PROGRAM_rom_info r, DB_PROGRAM_platform_info p, char *rom_sha1) ;

// ---------------------------------- Global Variables ---------------------------------- //
bool gui_menu_quirks_inactive; // Enable/Disable Quirks Menu
bool gui_menu_core_inactive; // Enable/Disable Core Selection Menu

char gui_statusbar_msg[120];
unsigned int gui_pixels_logo[2048];
unsigned int gui_pixel_logo_ON_color;
unsigned int gui_pixel_logo_OFF_color;

// -------------------------------------- Functions ------------------------------------- //
void gui_init(void);
int menu(struct nk_context *ctx);
int status_bar(struct nk_context *ctx);


extern void cpu_reset(void);