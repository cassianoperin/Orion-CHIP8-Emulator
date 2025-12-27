#ifndef LIB_JSON_ID
#define LIB_JSON_ID

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
// #include <stdbool.h>
#include "typedef.h"
#include "../lib/nxjson/nxjson.h"



/* ================= LIMITS ================= */
#define MAX_STR             256
#define MAX_AUTHORS         16
#define MAX_IMAGES          16
#define MAX_URLS            16
#define MAX_PLATFORMS       16
#define MAX_PIXEL_COLORS    16
#define MAX_KEYS            16
#define MAX_QUIRKS          16
#define MAX_RESOLUTIONS      8

// #define JSON_SHA1_HASHES "database/sha1-hashes.json"
#define JSON_PROGRAMS    "database/programs.json"
#define JSON_PLATFORMS   "database/platforms.json"

/* ================= RESULT STRUCT ================= */
typedef struct {

    /* ---------- PROGRAM ---------- */
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

    /* ---------- QUIRKS ---------- */
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

} RomResult;

/* ================= ERROR CODES ================= */
enum {
    FIND_ROM_OK = 0,
    FIND_ROM_INVALID_ARGUMENT,
    FIND_ROM_IO_ERROR,
    FIND_ROM_JSON_ERROR,
    FIND_ROM_HASH_NOT_FOUND,
    FIND_ROM_PROGRAM_NOT_FOUND,
    FIND_ROM_ROM_NOT_FOUND
};


/* =========================================================
 * Quirk value with presence flag
 * ========================================================= */
typedef struct {
    bool present;   /* indicates if the quirk exists in JSON */
    bool value;     /* true / false */
} PlatformQuirk;

/* =========================================================
 * All known quirks
 * ========================================================= */
typedef struct {
    PlatformQuirk shift;
    PlatformQuirk memoryIncrementByX;
    PlatformQuirk memoryLeaveIUnchanged;
    PlatformQuirk wrap;
    PlatformQuirk jump;
    PlatformQuirk vblank;
    PlatformQuirk logic;
    // PlatformQuirk clip;
    // PlatformQuirk scroll;
    // PlatformQuirk hiresCollision;
    // PlatformQuirk spriteWidth8;
    // PlatformQuirk waitVBlank;
    // PlatformQuirk planeMask;
    // PlatformQuirk audioPattern;
    // PlatformQuirk loadStore;
} PlatformQuirks;

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

    PlatformQuirks quirks;
} PlatformInfo;

/* ================= Public APIs ================= */
// 1 
// int  json_search_id(const char *hash);
// 2
int  find_rom_by_hash(const char *hash, RomResult *out);
void print_rom_result(const RomResult *r);
const char *find_rom_strerror(int code);
// 3
int load_platform_by_id(const char *platform_id, PlatformInfo *out);
void print_platform_info(const PlatformInfo *p);


#endif
