#pragma once
#include "typedef.h"

// #define Max_Overclock 5000

// // --------------------------------- External Variables --------------------------------- //
// Main
extern struct nk_context    *ctx;   // Nuklear
extern struct nk_font_atlas *atlas; // Nuklear font
extern bool              quit;
// extern SDL_Window *window;
// extern SDL_Renderer *renderer;
// extern SDL_Texture *texture;
// extern unsigned int cycle_counter;
// extern unsigned int message_slot4_timer;
// extern const int pal_freq;
// // Display
// extern unsigned int  display_pixel_ON_color;
// extern unsigned int  display_pixel_OFF_color;
// extern unsigned int  display_pixel_ON_color_alt;
// extern unsigned int  display_pixel_OFF_color_alt;
// extern unsigned int  display_pixels[8192]; 
// extern unsigned char display_color_theme;
// extern unsigned int  frame_counter;
// Lib
extern char *game_signature;
// CPU
extern unsigned char   Key[];
extern bool cpu_pause;
extern bool cpu_debug_mode;
// // extern unsigned int    cycle_counter_cpu;
// extern unsigned int CPU_CLOCK;
// // Font
// extern bool msg_emuinfo;
// // Sound
// extern bool sound_enabled;

// // --------------------------------- External Functions --------------------------------- //
// // CPU
// extern void cpu_reset();
// extern void cpu_interpreter();
// // Display
// extern void display_update_theme();
// extern bool display_draw(unsigned int frame, Scene *scene);

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
