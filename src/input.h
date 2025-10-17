#pragma once
#include <SDL2/SDL.h>
#include <string.h>
#include "typedef.h"
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"

#define Max_Overclock 3000

// // --------------------------------- External Variables --------------------------------- //
// Main
extern struct nk_context    *ctx;   // Nuklear
extern struct nk_font_atlas *atlas; // Nuklear font
extern bool quit;
// Windows
extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern SDL_Texture  *texture;
extern const int video_system_freq;
// Display
extern unsigned int display_pixel_ON_color;
extern unsigned int display_pixel_OFF_color;
extern bool display_fullscreen;
extern unsigned int display_EMULATOR_RES_X;
extern unsigned int display_EMULATOR_RES_Y;
extern unsigned int display_EMULATOR_RES_SCALE;
extern unsigned char display_color_theme;
extern unsigned int display_WINDOW_WIDTH_X;
extern unsigned int display_WINDOW_HEIGHT_Y;
extern unsigned int display_WINDOW_WIDTH_X_tmp;
extern unsigned int display_WINDOW_HEIGHT_Y_tmp;
extern unsigned int display_EMULATOR_RES_SCALE_tmp; 

// CPU
extern unsigned char   Key[];
extern bool cpu_pause;
extern bool cpu_debug_mode;
extern bool cpu_rom_loaded;
extern unsigned int CPU_CLOCK;
// Sound
extern bool sound_enabled;
// GUI
extern char gui_statusbar_msg[120];

// --------------------------------- External Functions --------------------------------- //
// CPU
extern void cpu_reset(void);
extern void cpu_interpreter(void);
// Display
extern void display_updateWindowSize(unsigned int pixel_scale);

// ---------------------------------- Global Variables ---------------------------------- //
bool            input_remap_flag;
unsigned char   input_remap_btn_UP;
unsigned char   input_remap_btn_DOWN;
unsigned char   input_remap_btn_LEFT;
unsigned char   input_remap_btn_RIGHT;
unsigned char   input_remap_btn_SPACE;

// -------------------------------------- Functions ------------------------------------- //
void input_keyboard(void);
void input_keyboard_remaps(char *rom_sha1);
