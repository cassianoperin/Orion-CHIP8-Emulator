#include <SDL2/SDL.h>
#include "sound.h"

void audio_callback(void *userdata, uint8_t *stream, int len)
{
    uint64_t *samples_played = (uint64_t*)userdata;
    float* fstream = (float*)(stream);
    static const float volume = 0.04;
    static const float frequency = 2800.0;

    for(int sid = 0; sid < (len / 8); ++sid)
    {
        double time = (*samples_played + sid) / 44100.0;
        fstream[2 * sid + 0] = volume * sin(frequency * 2.0 * M_PI * time); /* L */
        fstream[2 * sid + 1] = volume * sin(frequency * 2.0 * M_PI * time); /* R */
    }

    *samples_played += (len / 8);
}

void sound_init(void)
{
    // Initialize Varibles;
    sound_enabled = true;
	playing_sound = false;

	// Initialize SDL_Audio
	if( SDL_Init( SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL Audio could not initialize! SDL Error: %s\n", SDL_GetError() );
		exit(2);
	}

    samples_played = 0;

	SDL_AudioSpec audio_spec_want, audio_spec;
    SDL_memset(&audio_spec_want, 0, sizeof(audio_spec_want));

    audio_spec_want.freq     = 44100;
    audio_spec_want.format   = AUDIO_F32;
    audio_spec_want.channels = 2;
    audio_spec_want.samples  = 512;
    audio_spec_want.callback = audio_callback;
    audio_spec_want.userdata = (void*)&samples_played;

    audio_device_id = SDL_OpenAudioDevice(
        NULL, 0,
        &audio_spec_want, &audio_spec,
        SDL_AUDIO_ALLOW_FORMAT_CHANGE
    );

    if(!audio_device_id)
    {
        fprintf(stderr, "Error creating SDL audio device. SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(2);
    }

}

void sound_close(void)
{
	// Destroy Audio
	SDL_CloseAudioDevice(audio_device_id);
}
