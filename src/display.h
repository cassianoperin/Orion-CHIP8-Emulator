#pragma once
#include "typedef.h"

// // Boolean Type for Vanilla C
// typedef int bool;
// #define true 1
// #define false 0

// --------------------------------- External Variables --------------------------------- //
// Main - SDL Video
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *texture;
// Quirk
// extern bool quirk_display_wait;

// // ---------------------------------- Global Variables ---------------------------------- //
// // Display (Screen size)
// unsigned char display_SCREEN_WIDTH_X;
// unsigned char display_SCREEN_HEIGHT_Y;
// unsigned char display_SCALE;
// // Colors
// unsigned int  display_pixel_ON_color;
// unsigned int  display_pixel_OFF_color;
// unsigned char display_color_theme;          // Theme number
// unsigned int  display_pixel_ON_color_alt;   // New color of enabled pixels
// unsigned int  display_pixel_OFF_color_alt;  // New color of disabled pixels
// // Display Array
// // unsigned int  display_pixels[2048];
// unsigned int  display_pixels[8192];
// // Frames per second
// unsigned char display_FPS;
// // Debug Pixels
// bool debug_pixels;                          // Print pixels to console
// // Print Messages
// Scene scene;
// // Frame Counters
// unsigned int frame = 0;                      // Frame counter
// unsigned int frame_counter = 0;              // Frame per second

// -------------------------------------- Functions ------------------------------------- //
bool display_init();
bool display_draw(unsigned int frame, Scene *scene);
void display_update_theme();
void draw_graphics_console();