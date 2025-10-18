#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/nxjson/nxjson.h"

#define JSON_SHA1_HASHES "database/sha1-hashes.json"

// --------------------------------- External Variables --------------------------------- //

// --------------------------------- External Functions --------------------------------- //

// ---------------------------------- Global Variables ---------------------------------- //

// -------------------------------------- Functions ------------------------------------- //
int json_search_id(const char *hash);