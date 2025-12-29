#pragma once
#include <SDL2/SDL.h>

// LIMITS used in structs and lib_json
#define MAX_STR             256
#define MAX_AUTHORS         16
#define MAX_IMAGES          16
#define MAX_URLS            16
#define MAX_PLATFORMS       16
#define MAX_PIXEL_COLORS    16
#define MAX_KEYS            16
#define MAX_QUIRKS          16
#define MAX_RESOLUTIONS      8


// ---------------------------------- Type Definitions ---------------------------------- //

// Boolean Type for Vanilla C
typedef int bool;
#define true 1
#define false 0

// -------------------------------------- Structs --------------------------------------- //

// Define a struct to hold size and hash
typedef struct {
    char *hash_str;  // The SHA-1 hash as a hex string
    int  file_len;   // Length of the file (in bytes)
} ROM_header;

// Define a struct to hold the ROM information got from programs.json database
typedef struct {
    char program_index[MAX_STR];
    char title[MAX_STR];
    char description_program[MAX_STR];
    char release[MAX_STR];
    char license[MAX_STR];
    char copyright[MAX_STR];
    char authors[MAX_AUTHORS][MAX_STR];
    int  author_count;
    char images[MAX_IMAGES][MAX_STR];
    int  image_count;
    char urls[MAX_URLS][MAX_STR];
    int  url_count;
    char origin_type[MAX_STR];
    char origin_reference[MAX_STR];
    /* ---------- ROM ---------- */
    char rom_file[MAX_STR];
    char description_rom[MAX_STR];
    int  tickrate;
    char embedded_title[MAX_STR];
    char platforms[MAX_PLATFORMS][MAX_STR];
    int  platform_count;
    char chosen_platform[MAX_STR];
    char quirky_platform[MAX_STR];
    /* ---------- Quirks ---------- */
    char quirk_keys[MAX_QUIRKS][MAX_STR];
    char quirk_values[MAX_QUIRKS][MAX_STR];
    int  quirk_count;
    /* ---------- COLORS ---------- */
    char color_buzzer[MAX_STR];
    char color_silence[MAX_STR];
    char color_pixels[MAX_PIXEL_COLORS][MAX_STR];
    int  pixel_color_count;
    /* ---------- KEYS ---------- */
    char keys[MAX_KEYS][2][MAX_STR];
    int  key_count;

} DB_PROGRAM_rom_info; 


/* =========================================================
 * Quirk value with presence flag
 * ========================================================= */
typedef struct {
    bool present;   /* indicates if the quirk exists in JSON */
    bool value;     /* true / false */
} DB_PROGRAM_platform_quirks_presence;
  

/* =========================================================
 * All known quirks
 * ========================================================= */
typedef struct {
    DB_PROGRAM_platform_quirks_presence shift;
    DB_PROGRAM_platform_quirks_presence memoryIncrementByX;
    DB_PROGRAM_platform_quirks_presence memoryLeaveIUnchanged;
    DB_PROGRAM_platform_quirks_presence wrap;
    DB_PROGRAM_platform_quirks_presence jump;
    DB_PROGRAM_platform_quirks_presence vblank;
    DB_PROGRAM_platform_quirks_presence logic;
} DB_PROGRAM_platform_quirks;


/* =========================================================
 * PlatformInfo (single authoritative struct)
 * ========================================================= */
typedef struct {
    char id[MAX_STR];
    char name[MAX_STR];
    char description[MAX_STR];
    char release[MAX_STR];

    char display_resolutions[MAX_RESOLUTIONS][MAX_STR];
    int  display_resolution_count;

    int default_tickrate;

    DB_PROGRAM_platform_quirks quirks;
} DB_PROGRAM_platform_info;

// ---------------------------------- Global Variables ---------------------------------- //

// Rom and Platform DB
ROM_header 					rom_header;	    // Struct with ROM "Header" with size and sha1 hash
DB_PROGRAM_rom_info			rom_info;	    // Struct with ROM information read from programs.json database
DB_PROGRAM_platform_info	platform_info;  // Struct with details of PLATFORM from selected rom, read from platforms.json database

