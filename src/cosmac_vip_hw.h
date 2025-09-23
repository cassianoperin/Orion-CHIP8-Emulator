#pragma once
#include "typedef.h"

// --------------------------------- External Variables --------------------------------- //
// CPU
extern unsigned char	V[16];
extern unsigned short	I;
// Debug
extern bool            cpu_debug_mode;  	       // Enable debug messages
extern char            cpu_debug_message[120];     // Debug messages

// -------------------------------------- Functions ------------------------------------- //
void opc_chip8_ND_02D8(void);


