#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //

// Screen Size
extern unsigned int display_EMULATOR_RES_X;
extern unsigned int display_EMULATOR_RES_Y;
extern unsigned char display_pixels[8192];
extern unsigned char display_pixel_ON_color;
extern unsigned char display_pixel_OFF_color;
// Font
extern const char Chip8Fontset[80];
extern const char SCHIPFontset[160];
// Legacy Opcodes and Quirks
extern bool quirk_Memory_legacy_Fx55_Fx65;
extern bool quirk_Shifting_legacy_8xy6_8xyE;
extern bool quirk_Spacefight2091_Fx1E;
extern bool quirk_Clipping_Dxyn;
extern bool quirk_Resize_SCHIP_00FE_00FF;
extern bool quirk_Scroll_SCHIP_00CN_00FB_00FC;
extern bool quirk_ETI660_64x32_screen;
extern bool quirk_Jump_with_offset_Bnnn;
extern bool quirk_LoRes_Wide_Sprite_Dxy0;
extern bool quirk_VF_Reset_8xy1_8xy2_8xy3;
extern bool quirk_ClockProgram_fonts;
extern bool quirk_display_wait;
// Main
extern char *game_signature;
extern char *filename;
extern int romsize;
// GUI
extern bool gui_menu_quirks_inactive;
extern char gui_statusbar_msg[120];
// GUI DEBUG OPC
extern char guiDebug_opc_description_msg[50];

// --------------------------------- External Functions --------------------------------- //
// Lib
extern void handle_quirks(char *game_signature);
extern void load_rom(char *filename, unsigned char *mem, unsigned int mem_size);
extern char *get_game_signature(char *filename);
extern int fsize(char *filename);
// Input
extern void input_keyboard_remaps(void);
// CHIP-8
// void opc_chip8_0NNN(); // Not needed by any game, just for documentation
extern void opc_chip8_00E0(void);
extern void opc_chip8_00EE(void);
extern void opc_chip8_1NNN(void);
extern void opc_chip8_2NNN(void);
extern void opc_chip8_3XNN(void);
extern void opc_chip8_4XNN(void);
extern void opc_chip8_5XY0(void);
extern void opc_chip8_6XNN(void);
extern void opc_chip8_7XNN(void);
extern void opc_chip8_8XY0(unsigned char x, unsigned char y);
extern void opc_chip8_8XY1(unsigned char x, unsigned char y);
extern void opc_chip8_8XY2(unsigned char x, unsigned char y);
extern void opc_chip8_8XY3(unsigned char x, unsigned char y);
extern void opc_chip8_8XY4(unsigned char x, unsigned char y);
extern void opc_chip8_8XY5(unsigned char x, unsigned char y);
extern void opc_chip8_8XY6(unsigned char x, unsigned char y);
extern void opc_chip8_8XY7(unsigned char x, unsigned char y);
extern void opc_chip8_8XYE(unsigned char x, unsigned char y);
extern void opc_chip8_9XY0(void);
extern void opc_chip8_ANNN(void);
extern void opc_chip8_BNNN(void);
extern void opc_chip8_CXNN(void);
extern void opc_chip8_DXYN(void);
extern void opc_chip8_EX9E(unsigned char x);
extern void opc_chip8_EXA1(unsigned char x);
extern void opc_chip8_FX0A(unsigned char x);
extern void opc_chip8_FX07(unsigned char x);
extern void opc_chip8_FX15(unsigned char x);
extern void opc_chip8_FX18(unsigned char x);
extern void opc_chip8_FX1E(unsigned char x);
extern void opc_chip8_FX29(unsigned char x);
extern void opc_chip8_FX33(unsigned char x);
extern void opc_chip8_FX55(unsigned char x);
extern void opc_chip8_FX65(unsigned char x);
// CHIP-8 Undocumented
extern void opc_chip8_ND_02D8(void);
// SCHIP
extern void opc_schip_00FF(void);
extern void opc_schip_DXY0(void);

// ---------------------------------- Global Constants ---------------------------------- //
const int CHIP8_DEFAULT_CLOCK = 500;

// ---------------------------------- Global Variables ---------------------------------- //
unsigned char	Memory[4096];		        // Memory
unsigned short	PC;          	            // Program Counter
unsigned short	Opcode;                 	// CPU Operation Code
unsigned short	Stack[16];              	// Stack
unsigned short	SP;                     	// Stack Pointer
unsigned char	V[16];                    	// V Register
unsigned short	I;                   	    // I Register
unsigned char	DelayTimer;			        // Delay Timer
unsigned char	SoundTimer;			        // Sound Timer
unsigned char   Key[16];                    // Control the Keys Pressed
// Draw
bool            cpu_draw_flag;			    // Send the draw to screen signal
// Debug
bool            cpu_debug_mode;  	        // Enable debug messages
char            cpu_debug_message[120];     // Debug messages
bool            cpu_debug_print_console;    // Print debut messages to console
// SCHIP Specific Variables
bool            cpu_SCHIP_mode;             // SCHIP mode (ENABLED or DISABLED)
bool            cpu_SCHIP_LORES_mode;       // SCHIP in Low Resolution mode (00FE)
// bool            cpu_SCHIP_timer_hack;       // Enable or disable SCHIP DelayTimer Hack
// unsigned char   cpu_HP48_RPL_user_flags[8]; // HP-48 RPL user flags
// Interface
bool            cpu_pause;                  // Pause emulation
// CPU Counters
unsigned int    cycle_cpu = 0;		        // Executed cpu cycles
unsigned int    cycle_counter_cpu = 0;      // CPU instructions per second
// CPU Clock
unsigned int    CPU_CLOCK  = 0;             // CPU clock speed
// Input
unsigned char   key_FX0A = 0;                // Keep track of the first key pressed, to wait it to be released as necessary on FX0A
bool            key_FX0A_pressed = false;    // keep track of the state of first key pressed to check when is released to update V[x]
// GUI
bool            cpu_rom_loaded;                  // Tell the main loop when to start running the cpu_interpreter()

// -------------------------------------- Functions ------------------------------------- //
void cpu_initialize(void);
void cpu_load_fonts(void);
void cpu_debug_print(void);
void cpu_interpreter(void);
void cpu_reset(void);
void cpu_invalid_opcode(unsigned short opc);
int cpu_get_opcode(int PC_addr);
void cpu_decode_opcode(int opc);
