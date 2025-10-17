#pragma once
#include "typedef.h"

// /* Nuklear Flags */
#define INT_MAX 50
#define INT_MIN 0
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_STANDARD_VARARGS
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"

// --------------------------------- External Variables --------------------------------- //
// CPU
extern unsigned short PC_last;
extern unsigned char  Memory[4096];
extern char cpu_debug_message[120];
extern bool cpu_debug_mode;
extern bool cpu_rom_loaded; 
// Display
extern char gui_statusbar_msg[120];

// ---------------------------------- Global Variables ---------------------------------- //
char guiDebug_opc_addr_msg[6];
char guiDebug_opc_data_msg[6];
char guiDebug_opc_description_msg[50];

// -------------------------------------- Functions ------------------------------------- //
int win_debug_opc(struct nk_context *ctx);


// --------------------------------- External Functions --------------------------------- //
// CPU
extern int cpu_fetch_opcode(int PC_addr, bool PC_increment);
extern void cpu_decode_opcode(int opc);
