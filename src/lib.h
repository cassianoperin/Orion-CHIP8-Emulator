#pragma once
#include "typedef.h"
#include <SDL2/SDL.h>

// // Boolean Type for Vanilla C
// typedef int bool;
// #define true 1
// #define false 0

// --------------------------------- External Variables --------------------------------- //
// Main
extern SDL_Window *window;
extern char *filename;
// Display
extern unsigned char display_FPS;
extern unsigned char Memory[4096];
// extern unsigned int  display_pixels[8192];
// extern unsigned int  display_pixel_ON_color;
// extern unsigned int  display_pixel_OFF_color;
// extern unsigned int frame;
// CPU
extern unsigned int CPU_CLOCK;
extern void cpu_reset(void);
extern bool cpu_rom_loaded;
extern unsigned short PC;
extern unsigned short Opcode;
// extern bool cpu_draw_flag;
extern bool quirk_display_wait;
// GUI
extern bool gui_menu_quirks_inactive;
extern unsigned int gui_pixels_logo[2048];
extern unsigned int gui_pixel_logo_ON_color;
// Font
extern const int font_logo[165];

// --------------------------------- External Functions --------------------------------- //

// ---------------------------------- Global Variables ---------------------------------- //
extern bool rom_format_hex;

// -------------------------------------- Functions ------------------------------------- //

// Ticker - Use with actions that should be executed each second = 1hz
bool ticker_second(long lastTime, long currentTime);

// Ticker - Use with actions that should be executed 60 times per second = 60hz
bool ticker_fps(long lastTime, long currentTime);

// Ticker - se with actions that should be executed 500 times per second = 500hz
bool ticker_cpu(long lastTime, long currentTime);

// Load rom into memory
void load_rom(char *filename, unsigned char *mem, unsigned int mem_size);

// Time measurement
long getMicrotime(void);

// Check if a string contains in another
uint8_t strContains(char* string, char* toFind);

// Print the binary representation of a byte
void print_bin(unsigned char value);

// File Open Dialog
int lib_gui_loadrom(void);

// Show Logo
void showLogo(void);

// File(ROM) size and SHA1 hash generation
RomInfo file_size_and_hash(char *filename);
