#pragma once
#include "typedef.h"

#define BUFFER_DURATION 1 // Length of the buffer in seconds
#define FREQUENCY 48000 // Samples per second
#define BUFFER_LEN (BUFFER_DURATION * FREQUENCY) // Samples in the buffer

// ---------------------------------- Global Variables ---------------------------------- //
SDL_AudioDeviceID audio_device_id;
uint64_t samples_played;
bool sound_enabled;
bool playing_sound;

// -------------------------------------- Functions ------------------------------------- //
void sound_init(void);
void sound_close(void);
void audio_callback(void *userdata, uint8_t *stream, int len);
