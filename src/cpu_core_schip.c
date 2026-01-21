#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu_core_schip.h"

// --------------------------- SCHIP 1.0 --------------------------- //

// SCHIP 1.0 - 00FD
// Exit Emulator
void opc_schip_00FD(void) {

	if (cpu_debug_mode) {
		snprintf(cpu_debug_message, sizeof(cpu_debug_message), "SCHIP 00FD: Exit emulator");
		puts(cpu_debug_message);
	}
	
	// Reset
	cpu_initialize();
    // cpu_reset();

	// Update StatusBar message
	strcpy(gui_statusbar_msg, "No ROM loaded");
}


// SCHIP 1.0 - 00FE
// Enable Low-Res Mode (64 x 32 resolution)
void opc_schip_00FE(void) {
	// Enable SCHIP Mode
	cpu_SCHIP_mode = true;
	cpu_SCHIP_LORES_mode = true;
	
	// Set the clock to CHIP-8 Speed
	CPU_CLOCK = CHIP8_DEFAULT_CLOCK;

	// Set SCHIP Resolution
	display_EMULATOR_RES_X = 64;
	display_EMULATOR_RES_Y = 32;
	if ( !cpu_debug_mode ) {
		display_EMULATOR_RES_SCALE = 10;
	} else {
		display_EMULATOR_RES_SCALE = 8;
	}

	// Clear the screen when changing graphic mode
	unsigned int gfx_len = display_EMULATOR_RES_X * display_EMULATOR_RES_Y;
	for (unsigned int i = 0; i < gfx_len; i++) {
		display_pixels[i] = display_pixel_OFF_color;
	}

	cpu_draw_flag = true;

	if (cpu_debug_mode) {
		sprintf(cpu_debug_message, "SCHIP 00FE: Enable low res (64 x 32) mode");
		puts(cpu_debug_message);
	}
}


// SCHIP 1.0 - 00FF
// Enable High-Res Mode (128 x 64 resolution)
// Enable SCHIP Mode
void opc_schip_00FF(void) {
	cpu_SCHIP_mode = true;
	cpu_SCHIP_LORES_mode = false;

	// Set the clock to SCHIP
	CPU_CLOCK = SCHIP_DEFAULT_CLOCK;

	// Set SCHIP Resolution
	display_EMULATOR_RES_X = 128;
	display_EMULATOR_RES_Y = 64;
	if ( !cpu_debug_mode ) {
		display_EMULATOR_RES_SCALE = 5;
	} else {
		display_EMULATOR_RES_SCALE = 4;
	}

	// Clear the screen when changing graphic mode
	unsigned int gfx_len = display_EMULATOR_RES_X * display_EMULATOR_RES_Y;
	for (unsigned int i = 0; i < gfx_len; i++) {
		display_pixels[i] = display_pixel_OFF_color;
	}

	cpu_draw_flag = true;

	if (cpu_debug_mode) {
		sprintf(cpu_debug_message, "SCHIP 00FF: Enable high res (128 x 64) mode");
		puts(cpu_debug_message);
	}
}


// SCHIP - DXY0 - draw 16x16 sprites
// Draw 16x16 sprite starting at memory location I at (Vx, Vy), set VF = collision.
// In LOW-RES (64x32), if workaround_DXY0_loresWideSprite == false,
// only the first 8 pixels are drawn (8x16 behavior).
void opc_schip_DXY0(unsigned char x, unsigned char y, unsigned char n) {

    unsigned int gpx_position, row, column = 0;
    unsigned char Vx, Vy, byte, bit, bit_value, sprite = 0, sprite2 = 0;

    Vx = V[x];
    Vy = V[y];
    n  = 16;

    V[0xF] = 0;

    for (byte = 0; byte < n; byte++) {

        // Always fetch as 16x16 source (2 bytes per row)
        sprite  = Memory[I + (byte * 2)];
        sprite2 = Memory[I + (byte * 2) + 1];

        // --------- Row --------- //
        if (quirk_Wrap_Dxyn) {
            row = (Vy + byte) % display_EMULATOR_RES_Y;
        } else {
            row = (Vy % display_EMULATOR_RES_Y) + byte;
            if (row >= (unsigned)display_EMULATOR_RES_Y)
                continue;
        }

        // --------- First 8 pixels (left byte) --------- //
        for (bit = 0; bit < 8; bit++) {

            bit_value = (sprite & 0x80) >> 7;

            if (quirk_Wrap_Dxyn) {
                column = (Vx + bit) % display_EMULATOR_RES_X;
            } else {
                column = (Vx % display_EMULATOR_RES_X) + bit;
                if (column >= (unsigned)display_EMULATOR_RES_X)
                    bit_value = 0;
            }

            if (bit_value) {
                gpx_position = row * display_EMULATOR_RES_X + column;
                if (gpx_position < (unsigned)(display_EMULATOR_RES_X * display_EMULATOR_RES_Y)) {
                    if (display_pixels[gpx_position] == display_pixel_ON_color)
                        V[0xF] = 1;
                    display_pixels[gpx_position] ^= display_pixel_ON_color;
                }
            }

            sprite <<= 1;
        }

        // --------- Second 8 pixels (right byte) --------- //
        if (!cpu_SCHIP_LORES_mode || workaround_DXY0_loresWideSprite) {

            for (bit = 0; bit < 8; bit++) {

                bit_value = (sprite2 & 0x80) >> 7;

                unsigned int col2;
                if (quirk_Wrap_Dxyn) {
                    col2 = (Vx + 8 + bit) % display_EMULATOR_RES_X;
                } else {
                    col2 = (Vx % display_EMULATOR_RES_X) + 8 + bit;
                    if (col2 >= (unsigned)display_EMULATOR_RES_X)
                        bit_value = 0;
                }

                if (bit_value) {
                    gpx_position = row * display_EMULATOR_RES_X + col2;
                    if (gpx_position < (unsigned)(display_EMULATOR_RES_X * display_EMULATOR_RES_Y)) {
                        if (display_pixels[gpx_position] == display_pixel_ON_color)
                            V[0xF] = 1;
                        display_pixels[gpx_position] ^= display_pixel_ON_color;
                    }
                }

                sprite2 <<= 1;
            }
        }
    }

    cpu_draw_flag = true;
}




// SCHIP 1.0 - FX75
// Store V0 through VX to HP-48 RPL user flags (X <= 7).
void opc_schip_FX75(unsigned char x) {
	// Limit to 7
	if (x > 7) x = 7;

	for (int i = 0; i <= x; i++) {
		RPL[i] = V[i];
	}

	if (cpu_debug_mode) {
		snprintf(cpu_debug_message, sizeof(cpu_debug_message), "SCHIP Fx75: Store registers V[0] through V[x(%u)] in RPL user flags from 0 to %u", (unsigned)x, (unsigned)x);
		puts(cpu_debug_message);
	}

}

// SCHIP 1.0 - FX85
// Read V0 through VX to HP-48 RPL user flags (X <= 7).
void opc_schip_FX85(unsigned char x) {
	// Limit to 7
	if (x > 7) x = 7;

	for (int i = 0; i <= x; i++) {
		V[i] = RPL[i];
	}

	if (cpu_debug_mode) {
		snprintf(cpu_debug_message, sizeof(cpu_debug_message), "SCHIP Fx85: Read registers V[0] through V[x(%u)] and store in RPL user flags", (unsigned)x);
		puts(cpu_debug_message);
	}
}


// --------------------------- SCHIP 1.1 --------------------------- //

// SCHIP 1.1 - 00CN
// Scroll display N lines down
void opc_schip_00CN(unsigned char n) {
    unsigned int width   = display_EMULATOR_RES_X;
    unsigned int height  = display_EMULATOR_RES_Y;
    unsigned int gfx_len = width * height;

    if (n == 0) {
        cpu_draw_flag = true;
        return;
    }

    unsigned int shift = (unsigned int)n * width;

    // If shift is >= whole screen, clear everything
    if (shift >= gfx_len) {
        for (unsigned int i = 0; i < gfx_len; i++) {
            display_pixels[i] = display_pixel_OFF_color;
        }
        cpu_draw_flag = true;
        return;
    }

    // Move pixels down by 'shift' (copy from bottom to top)
    for (unsigned int i = gfx_len; i-- > shift; ) {
        display_pixels[i] = display_pixels[i - shift];
    }

    // Clear the top 'shift' pixels
    for (unsigned int i = 0; i < shift; i++) {
        display_pixels[i] = display_pixel_OFF_color;
    }

    cpu_draw_flag = true;

    if (cpu_debug_mode) {
        snprintf(cpu_debug_message, sizeof(cpu_debug_message), "SCHIP 00CN: Scroll display %u lines down", (unsigned)n);
        puts(cpu_debug_message);
    }
}



// SCHIP 1.1 - 00FB
// Scroll display 4 pixels right (hi-res). In lo-res, scroll 2 pixels right.
void opc_schip_00FB(void) {
	unsigned int width  = display_EMULATOR_RES_X;
	unsigned int height = display_EMULATOR_RES_Y;
	unsigned int shift  = (width == 64) ? 2 : 4;

	// Shift Right N pixels on Graphics Array
    for (unsigned int y = 0; y < height; y++) {
        unsigned int base = y * width;

		// Shift pixels to the right (from the end to the beginning)
        for (int x = width - 1; x >= (int)shift; x--) {
            display_pixels[base + x] = display_pixels[base + x - shift];
        }

        // Clear the first 'shift' pixels of the line
        for (unsigned int x = 0; x < shift; x++) {
            display_pixels[base + x] = display_pixel_OFF_color;
        }
    }

    cpu_draw_flag = true;

	if (cpu_debug_mode) {
		snprintf(cpu_debug_message, sizeof(cpu_debug_message), "SCHIP 00FB: Scroll display right");
		puts(cpu_debug_message);
	}
}


// SCHIP 1.1 - 00FC
// Scroll 4 pixels left (hires), 2 pixels (lores)
void opc_schip_00FC(void) {
	unsigned int width  = cpu_SCHIP_LORES_mode ? 64 : 128;
	unsigned int height = cpu_SCHIP_LORES_mode ? 32 : 64;

	// Shift 4 pixels left (hires) or 2 pixels left (lores)
    unsigned int shift = cpu_SCHIP_LORES_mode ? 2 : 4;

	// Shift Left N pixels on Graphics Array
    for (unsigned int y = 0; y < height; y++) {
        unsigned int base = y * width;

        // Move line pixels to the left
        for (unsigned int x = 0; x < width - shift; x++) {
            display_pixels[base + x] = display_pixels[base + x + shift];
        }

        // Clean the last (shift value) pixels of the line
        for (unsigned int x = width - shift; x < width; x++) {
            display_pixels[base + x] = display_pixel_OFF_color;
        }
    }

    cpu_draw_flag = true;

	if (cpu_debug_mode) {
		snprintf(cpu_debug_message, sizeof(cpu_debug_message), "SCHIP 00FC: Scroll display left");
		puts(cpu_debug_message);
	}
}


// SCHIP 1.1 - Fx30 - LD F, Vx
// Set I = location of sprite for digit Vx.
// The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx.
void opc_schip_FX30(unsigned char x) {

	// Load SCHIP font. Start from Memory[80]
	I = 80 + V[x]*10;

	if (cpu_debug_mode) {
		snprintf(cpu_debug_message, sizeof(cpu_debug_message), "SCHIP Fx30: Set I(%X) = location of sprite for digit V[x(%u)]:%u (*10)", (unsigned)I, (unsigned)x, (unsigned)V[x]);
		puts(cpu_debug_message);
	}
}



