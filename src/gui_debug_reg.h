#pragma once

/* Nuklear Flags */
#define INT_MAX 50
#define INT_MIN 0
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_STANDARD_VARARGS
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
//Main
extern bool rom_format_hex;
extern uint64_t counter_second_ms_duration;
extern unsigned int counter_second_cycles;
extern unsigned int counter_second_frames;
extern const int video_system_freq;
// CPU
extern unsigned short	PC;
extern unsigned short	Opcode;
extern unsigned short	Stack[16];
extern unsigned short	SP;
extern unsigned char	V[16];
extern unsigned short	I;
extern unsigned char	DelayTimer;
extern unsigned char	SoundTimer;
extern unsigned char    Key[16];
extern bool             cpu_draw_flag;
extern bool             cpu_debug_mode;
extern bool             cpu_pause;
extern unsigned int     CPU_CLOCK;
// Quirks
extern bool quirk_VF_Reset_8xy1_8xy2_8xy3;
extern bool quirk_Memory_legacy_Fx55_Fx65;
extern bool quirk_display_wait;
extern bool quirk_Clipping_Dxyn;
extern bool quirk_Shifting_legacy_8xy6_8xyE;
extern bool quirk_Jump_with_offset_Bnnn;
// GUI
extern const struct  nk_color nk_gray;
// Sound
extern bool sound_enabled;

// ---------------------------------- Global Variables ---------------------------------- //
char guiDebug_reg_label_msg[10];
char guiDebug_reg_emuinfo_msg[150];

// -------------------------------------- Functions ------------------------------------- //
int win_debug_reg(struct nk_context *ctx);
