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

#define JSON_PROGRAMS    "database/programs.json"
#define JSON_PLATFORMS   "database/platforms.json"

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








/* ================= Public APIs ================= */
DB_PROGRAM_rom_info JSON_DB_query_program (const char *sha1);
void                JSON_DB_print_program (const DB_PROGRAM_rom_info *r);
int                 JSON_DB_query_platform(const char *platform_id, DB_PROGRAM_platform_info *out);
void                JSON_DB_print_platform(const DB_PROGRAM_platform_info *p);


int  find_rom_by_hash(const char *hash, DB_PROGRAM_rom_info *out);
const char *find_rom_strerror(int code);




#endif
