#pragma once
#include <SDL2/SDL.h>

// ---------------------------------- Type Definitions ---------------------------------- //

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// Define a struct to hold size and hash
typedef struct {
    char *hash_str;  // The SHA-1 hash as a hex string
    int  file_len;   // Length of the file (in bytes)
} RomInfo;
