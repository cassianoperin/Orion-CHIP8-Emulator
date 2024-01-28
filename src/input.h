#pragma once
#include "typedef.h"

#define Max_Overclock 3000

// // --------------------------------- External Variables --------------------------------- //
// Main
extern struct nk_context    *ctx;   // Nuklear
extern struct nk_font_atlas *atlas; // Nuklear font
extern bool quit;
extern SDL_Window *window;
// extern SDL_Renderer *renderer;
// extern SDL_Texture *texture;
// extern unsigned int cycle_counter;
extern const int pal_freq;
// // Display
extern unsigned int  display_pixel_ON_color;
extern unsigned int  display_pixel_OFF_color;
extern unsigned int  display_pixel_ON_color_alt;
extern unsigned int  display_pixel_OFF_color_alt;
extern bool display_fullscreen;
extern unsigned int display_SCALE;
// extern unsigned int  display_pixels[8192]; 
extern unsigned char display_color_theme;
// extern unsigned int  frame_counter;
// Lib
extern char *game_signature;
// CPU
extern unsigned char   Key[];
extern bool cpu_pause;
extern bool cpu_debug_mode;
// extern unsigned int    cycle_counter_cpu;
extern unsigned int CPU_CLOCK;
// // Font
// extern bool msg_emuinfo;
// Sound
extern bool sound_enabled;
// GUI
extern bool gui_show_menu;

// --------------------------------- External Functions --------------------------------- //
// CPU
extern void cpu_reset(void);
extern void cpu_interpreter(void);
// Display
extern void display_update_theme(void);
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
void input_keyboard_remaps(void);
