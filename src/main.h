#pragma once
#include "typedef.h"

/* nuklear - 1.32.0 - public domain */
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdint.h>
// #include <stdarg.h>
// #include <string.h>
// #include <math.h>
// #include <assert.h>
// #include <limits.h>
// #include <time.h>
/* Nuklear Flags */
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_RENDERER_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"


// --------------------------------- External Variables --------------------------------- //
// Lib
extern char *game_signature;
// // extern char teste;
// CPU
extern unsigned char	        Memory[4096];
extern bool                     cpu_draw_flag;
extern unsigned char	        DelayTimer;
extern unsigned char	        SoundTimer;
extern bool                     cpu_pause;
extern unsigned int             cycle_counter_cpu;
// Display
extern unsigned int             frame;
extern unsigned int             frame_counter;
// Audio
extern SDL_AudioDeviceID        audio_device_id;
extern bool                     playing_sound;
extern bool                     sound_enabled;
// // Font
// extern bool                     msg_emuinfo;
// Quirks
extern bool                     quirk_display_wait;

// --------------------------------- External Functions --------------------------------- //
// Cli
extern void command_line_interface(int argc, char* argv[]);
// Lib
// extern bool ticker_second(long lastTime, long currentTime);
// extern bool ticker_cpu(long lastTime, long currentTime);
// extern bool ticker_fps(long lastTime, long currentTime);
// extern void showCPS(long long unsigned int number);
// extern void showFPS(int number);
// extern void showCPU_CPS(int number);
// extern void load_rom(char *filename, unsigned char *mem, unsigned int mem_size);
// extern char *get_game_signature(char *filename);
// extern long getMicrotime();
// extern void string_memory_alloc();
// extern void string_memory_free();
// CPU
extern void cpu_initialize(void);
// extern void cpu_load_fonts(void);
extern void cpu_interpreter(void);
extern unsigned int CPU_CLOCK;
extern bool cpu_rom_loaded;
// Quirks
// extern void handle_quirks(char *game_signature);
// Input
extern void input_keyboard(void);
// extern void input_keyboard_remaps(void);
// Display
extern bool display_init(void);
extern bool display_draw(unsigned int frame);
extern void SDL_close(void);
// Audio
extern void sound_init(void);
extern void sound_close(void);
// GUI
extern void gui_init(void);
extern int menu(struct nk_context *ctx);
extern bool gui_show_menu;

// ---------------------------------- Global Constants ---------------------------------- //
// NTSC: 60hz, PAL: 50HZ
const int   pal_freq   = 60; 					

// ---------------------------------- Global Variables ---------------------------------- //
// SDL Video
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

// --- Nuklear --- //
/* GUI */
struct nk_context *ctx;
struct nk_colorf bg;
// GUI Font
struct nk_font_atlas *atlas;
float font_scale = 1;

// Game path and ROM name
char *filename;

// Flag to indicate rom in hexadecimal format
bool rom_format_hex;

// Control the Main loop exit
bool quit;

// Cycle Counters
// // unsigned int cycle               = 0;     // Main loop cycles
unsigned int cycle_counter       = 0;     // Main loop cyles/second counter

// // Main loop control
// unsigned int sleep_modulus      = 100;     // Cycle modulus do reduce infinity loop useless usage of cpu
// unsigned int last_cycle_counter = 9999999; // Maximum value of the last count of cycled/second to be used by main loop limit control
//                                            // Need to start with a high value due to sleep function to avoid unnecessary cpu usage
// unsigned int sleep_counter      = 0;       // How many Milliseconds slept for second

// // Message Counters
// unsigned int message_slot4_timer = 0;

