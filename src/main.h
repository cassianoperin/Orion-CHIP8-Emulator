#pragma once
#include "typedef.h"

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
// Quirks
extern bool                     quirk_display_wait;

// --------------------------------- External Functions --------------------------------- //
// CPU
extern void cpu_initialize(void);
extern void cpu_interpreter(void);
extern unsigned int CPU_CLOCK;
extern bool cpu_rom_loaded;
// Input
extern void input_keyboard(void);
// Display
extern bool display_init(void);
extern bool display_draw(void);
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
// SDL Video (Emulator Window)
SDL_Window   *window;
SDL_Renderer *renderer;
SDL_Texture  *texture;

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
