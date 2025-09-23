#include <stdio.h>
#include <string.h>
#include "cosmac_vip_hw.h"

// ---------------------------- COSMAC VIP MACHINE CODE ---------------------------- //

// 02D8 COSMAC VIP Machine Code Routine used by CLOCK Program
// No action, just go to next CHIP8 opcode
void opc_chip8_ND_02D8(void) {
	// //LDA 02, I // Load from memory at address I into V[00] to V[02]

	// Will be always 2
	// unsigned char x;
	// x = (Opcode & 0x0F00) >> 8;

	// V[0] = (unsigned char)I;
	// V[1] = (unsigned char)I + 1;
	// V[2] = (unsigned char)I + 2;

	if ( cpu_debug_mode )
	// 	sprintf(cpu_debug_message, "CHIP-8 02DB (NON DOCUMENTED): Load from memory at address I(%d) into V[0]= %d, V[1]= %d and V[2]= %d.", I, I , I+1, I+2);
		sprintf(cpu_debug_message, "CHIP-8 02DB (COSMAC VIP Hardware machine code routine call): No action, go to next instruction");

}

// // 02E4
// // NON DOCUMENTED OPCODED, USED BY CHIP-8 Tic-jkjkljac-Toe ([AUD_2464_09_B41_ID23_01] sound program
// // LDF I, V[02] // Load into I the address of the 8x5 font with index as value of V[02].
// func opc_chip8_ND_02E4() {
// 	I = uint16(Memory[V[2]])
// 	PC+=2
// }

// ---------------- CHIP-8 undocumented instructions found on internet for future needs ---------------- //
// // 02A6: 22D4
// CALL 02D4 // Call sub-routine at address 02D4 (724) in memory.
//
// // 02D4: A2F2
// LD I, 02F2 // Load 02F2 (754 in decimal) into I.
//
// // 02D6: FE33
// BCD V[0E] // Load into memory at address I the BCD value of V[0E].
//
// // Value of V[0E]: 00 (0)
// // Hundreds: 0
// // Tens    : 0
// // Units   : 0
//
// // I: 02F2 (754)
// // mem[02F2]: 00 (0)
// // mem[02F3]: 00 (0)
// // mem[02F4]: 00 (0)
//
// // 02D8: F265
// LDA 02, I // Load from memory at address I into V[00] to V[02].
//
// // V[00]: 00 (0)
// // V[01]: 00 (0)
// // V[02]: 00 (0)
//
// // 02DA: F129
// LDF I, V[01] // Load into I the address of the 8x5 font with index as value of V[01].
//
// // 02DC: 6414
// LD V[04], 0014 // Load 0014 (20) into V[04].
//
// // 02DE: 6500
// LD V[05], 0000 // Load 0000 (0) into V[05].
//
// // 02E0: D455
// DRW V[04], V[05], 05 // Draw a 8x5 sprite at x=14 (20) and y=00 (0).
//
// // 02E2: 7415
// ADD V[04], 0015 // Add 0015 (21) into V[04].
//
// // 02E4: F229
// LDF I, V[02] // Load into I the address of the 8x5 font with index as value of V[02].
//
// // 02E6: D455
// DRW V[04], V[05], 05 // Draw a 8x5 sprite at x=29 (41) and y=00 (0).
//
// // 02E8: 00EE
// RET // Return from sub-routine.
//
// // 02A8: 8E34
// ADD V[0E], V[03] // Add V[03] into V[0E].
//
// // 02AA: 22D4
// CALL 02D4 // Call sub-routine at address 02D4 (724) in memory.
//
// // 02D4: A2F2
// LD I, 02F2 // Load 02F2 (754 in decimal) into I.
//
// // 02D6: FE33
// BCD V[0E] // Load into memory at address I the BCD value of V[0E].
//
// // Value of V[0E]: 0A (10)
// // Hundreds: 0
// // Tens    : 1
// // Units   : 0
//
// // I: 02F2 (754)
// // mem[02F2]: 00 (0)
// // mem[02F3]: 01 (1)
// // mem[02F4]: 00 (0)
//
// // 02D8: F265
// LDA 02, I // Load from memory at address I into V[00] to V[02].
//
// // V[00]: 00 (0)
// // V[01]: 01 (1)
// // V[02]: 00 (0)
//
// // 02DA: F129
// LDF I, V[01] // Load into I the address of the 8x5 font with index as value of V[01].
//
// // 02DC: 6414
// LD V[04], 0014 // Load 0014 (20) into V[04].
//
// // 02DE: 6500
// LD V[05], 0000 // Load 0000 (0) into V[05].
//
// // 02E0: D455
// DRW V[04], V[05], 05 // Draw a 8x5 sprite at x=14 (20) and y=00 (0).
//
// // 02E2: 7415
// ADD V[04], 0015 // Add 0015 (21) into V[04].
//
// // 02E4: F229
// LDF I, V[02] // Load into I the address of the 8x5 font with index as value of V[02].
//
// // 02E6: D455
// DRW V[04], V[05], 05 // Draw a 8x5 sprite at x=29 (41) and y=00 (0).
//
// // 02E8: 00EE
// RET // Return from sub-routine.
