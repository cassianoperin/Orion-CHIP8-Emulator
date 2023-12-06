#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// CPU
extern bool cpu_pause; 
extern unsigned char Memory[4096];
extern bool cpu_debug_mode;
// Sound
extern bool sound_enabled;
// Quirk
extern bool quirk_display_wait;
// Main
extern char *filename;
extern bool rom_format_hex;

// --------------------------------- External Functions --------------------------------- //
// Lib
extern void load_rom(char *filename, unsigned char *mem, unsigned int mem_size);
extern uint8_t strContains(char* string, char* toFind);

// -------------------------------------- Functions ------------------------------------- //
// CLI
void command_line_interface(int argc, char* argv[]);
void print_usage(char* args[]);
