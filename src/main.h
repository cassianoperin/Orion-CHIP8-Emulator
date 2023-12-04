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
#include "../lib/nuklear.h"
#include "../lib/nuklear_sdl_renderer.h"


// // --------------------------------- External Variables --------------------------------- //
// // Lib
// extern char *game_signature;
// extern char *string_msg1,*string_msg2, *string_msg3, *string_msg4;
// // extern char teste;
// // CPU
// extern unsigned char	        Memory[4096];
// extern bool                     cpu_draw_flag;
// extern unsigned char	        DelayTimer;
// extern unsigned char	        SoundTimer;
// extern bool                     cpu_pause;
// extern unsigned int             cycle_counter_cpu;
// // Display
// extern Scene                    scene;
// extern unsigned int             frame;
// extern unsigned int             frame_counter;
// // Audio
// extern SDL_AudioDeviceID        audio_device_id;
// extern bool                     playing_sound;
// extern bool                     sound_enabled;
// // Font
// extern bool                     msg_emuinfo;
// // Quirks
// extern bool                     quirk_display_wait;

// // --------------------------------- External Functions --------------------------------- //
// // Font
// extern bool font_init(SDL_Renderer *renderer);
// extern void font_update_msg1(SDL_Renderer *renderer);
// extern void font_update_msg2(SDL_Renderer *renderer);
// extern void font_update_msg3(SDL_Renderer *renderer);
// extern void font_update_msg4(SDL_Renderer *renderer);
// // Cli
// extern void command_line_interface(int argc, char* args[]);
// // Lib
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
// // CPU
// extern void cpu_initialize();
// extern void cpu_load_fonts();
// extern void cpu_interpreter();
// extern unsigned int CPU_CLOCK;
// // Quirks
// extern void handle_quirks(char *game_signature);
// // Input
// extern void input_keyboard();
// extern void input_keyboard_remaps();
// // Display
// extern bool display_init();
// extern bool display_draw(unsigned int frame, Scene *scene);
// extern void SDL_close();
// // Audio
// extern void sound_init();
// extern void sound_close();

// // ---------------------------------- Global Constants ---------------------------------- //
// // NTSC: 60hz, PAL: 50HZ
// const int   pal_freq   = 60; 					

// ---------------------------------- Global Variables ---------------------------------- //
// SDL Video
SDL_Window *window;
SDL_Renderer *renderer;
// SDL_Texture *texture;

// // Game path and ROM name
// char *filename;
// // Flag to indicate rom in hexadecimal format
// bool rom_format_hex;

// // Control the Main loop exit
// bool quit;

// // Cycle Counters
// // unsigned int cycle               = 0;     // Main loop cycles
// unsigned int cycle_counter       = 0;     // Main loop cyles/second counter

// // Main loop control
// unsigned int sleep_modulus      = 100;     // Cycle modulus do reduce infinity loop useless usage of cpu
// unsigned int last_cycle_counter = 9999999; // Maximum value of the last count of cycled/second to be used by main loop limit control
//                                            // Need to start with a high value due to sleep function to avoid unnecessary cpu usage
// unsigned int sleep_counter      = 0;       // How many Milliseconds slept for second

// // Message Counters
// unsigned int message_slot4_timer = 0;

