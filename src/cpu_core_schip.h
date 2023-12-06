// ---------------------------- 06 Super-CHIP 1.0 opcodes ---------------------------- //
// 00FD: Exit interpreter
// 00FE: Disable high-resolution mode
// 00FF: Enable high-resolution mode
// DXY0: Draw 16 x 16 sprite (only if high-resolution mode is enabled)
// FX75: Store V0..VX in RPL user flags (X <= 7)
// FX85: Read V0..VX from RPL user flags (X <= 7)
// ---------------------------- 04 Super-CHIP 1.1 opcodes ---------------------------- //
// 00CN: Scroll display N pixels down; in low resolution mode, N/2 pixels
// 00FB: Scroll right by 4 pixels; in low resolution mode, 2 pixels
// 00FC: Scroll left by 4 pixels; in low resolution mode, 2 pixels
// FX30: Point I to 10-byte font sprite for digit VX (only digits 0-9)

#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// Main - SDL Video
extern SDL_Window *window;
// CPU
extern unsigned int     CPU_CLOCK;
extern bool             cpu_SCHIP_mode;
extern bool             cpu_SCHIP_LORES_mode;
extern unsigned short	PC;
// extern unsigned short	Stack[];
// extern unsigned short	SP;
extern bool             cpu_debug_mode;
extern char             cpu_debug_message[120];
extern unsigned short	Opcode;
extern unsigned char	V[16];
extern unsigned short	I;
extern unsigned char	Memory[4096];
// extern unsigned char    Key[16];
// extern unsigned char	DelayTimer;
// extern unsigned char	SoundTimer;
extern bool             cpu_draw_flag;
// extern unsigned char    key_FX0A;
// extern bool             key_FX0A_pressed;
extern bool            cpu_pause;

// Display
extern unsigned char display_SCREEN_WIDTH_X;
extern unsigned char display_SCREEN_HEIGHT_Y;
extern unsigned char display_SCALE;
extern unsigned int  display_pixel_ON_color;
extern unsigned int  display_pixel_OFF_color;
extern unsigned int  display_pixels[8192];
// -------------------------------------- Functions ------------------------------------- //
// CHIP-8
void opc_schip_00FF(void);
void opc_schip_DXY0(void);
