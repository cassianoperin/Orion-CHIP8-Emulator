#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "lib_json.h"

// -------------------------------- 1 -  START of Send the hash and receive program info --------------------------------- //

/* =========================================================
 * Utilities
 * ========================================================= */
static void safe_strcpy(char *dst, size_t dst_sz, const char *src){
    if(!dst || dst_sz == 0) return;
    if(src){
        strncpy(dst, src, dst_sz - 1);
        dst[dst_sz - 1] = '\0';
    } else {
        dst[0] = '\0';
    }
}

static void node_to_cstring(const nx_json *n, char *buf, size_t bufsz){
    if(!buf || bufsz == 0){
        return;
    }

    if(!n){
        buf[0] = '\0';
        return;
    }

    switch(n->type){
        case NX_JSON_BOOL:
            snprintf(buf, bufsz, "%s", n->num.u_value ? "true" : "false");
            break;
        case NX_JSON_INTEGER:
            snprintf(buf, bufsz, "%lld", (long long)n->num.u_value);
            break;
        case NX_JSON_STRING:
            safe_strcpy(buf, bufsz, n->text_value);
            break;
        default:
            snprintf(buf, bufsz, "(unsupported)");
            break;
    }
}

static char *read_file(const char *path){
    FILE *f = fopen(path, "rb");
    if(!f){
        fprintf(stderr, "[JSON_DB_query_program] ERROR: Failed to open '%s': %s\n",
                path, strerror(errno));
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);

    if(sz <= 0){
        fclose(f);
        return NULL;
    }

    char *buf = malloc(sz + 1);
    if(!buf){
        fclose(f);
        return NULL;
    }

    fread(buf, 1, sz, f);
    buf[sz] = '\0';
    fclose(f);
    return buf;
}

static void strip_utf8_bom(char *s){
    if(!s) return;
    if((unsigned char)s[0] == 0xEF &&
       (unsigned char)s[1] == 0xBB &&
       (unsigned char)s[2] == 0xBF){
        memmove(s, s + 3, strlen(s + 3) + 1);
    }
}

/* =========================================================
 * Fill result on Struct
 * ========================================================= */
static void
fill_result(DB_PROGRAM_rom_info *r,
            const nx_json *program,
            const nx_json *rom,
            const char *chosen,
            int index)
{
    memset(r, 0, sizeof(*r));
    snprintf(r->program_index, sizeof(r->program_index), "%d", index);

    const nx_json *n = NULL;

    /* ---------- PROGRAM ---------- */
    if((n = nx_json_get(program,"title")) && n->text_value)
        safe_strcpy(r->title,sizeof(r->title),n->text_value);

    if((n = nx_json_get(program,"description")) && n->text_value)
        safe_strcpy(r->description_program,sizeof(r->description_program),n->text_value);

    if((n = nx_json_get(program,"release")) && n->text_value)
        safe_strcpy(r->release,sizeof(r->release),n->text_value);

    if((n = nx_json_get(program,"license")) && n->text_value)
        safe_strcpy(r->license,sizeof(r->license),n->text_value);

    if((n = nx_json_get(program,"copyright")) && n->text_value)
        safe_strcpy(r->copyright,sizeof(r->copyright),n->text_value);

    if((n = nx_json_get(program,"authors")) && n->type == NX_JSON_ARRAY){
        const nx_json *a = n->children.first;
        while(a && r->author_count < MAX_AUTHORS){
            if(a->text_value)
                safe_strcpy(r->authors[r->author_count++],
                            sizeof(r->authors[0]), a->text_value);
            a = a->next;
        }
    }

    if((n = nx_json_get(program,"urls")) && n->type == NX_JSON_ARRAY){
        const nx_json *u = n->children.first;
        while(u && r->url_count < MAX_URLS){
            if(u->text_value)
                safe_strcpy(r->urls[r->url_count++],
                            sizeof(r->urls[0]), u->text_value);
            u = u->next;
        }
    }

    if((n = nx_json_get(program,"images")) && n->type == NX_JSON_ARRAY){
        const nx_json *img = n->children.first;
        while(img && r->image_count < MAX_IMAGES){
            if(img->text_value)
                safe_strcpy(r->images[r->image_count++],
                            sizeof(r->images[0]), img->text_value);
            img = img->next;
        }
    }

    if((n = nx_json_get(program,"origin")) && n->type == NX_JSON_OBJECT){
        const nx_json *t = nx_json_get(n,"type");
        const nx_json *ref = nx_json_get(n,"reference");
        if(t && t->text_value)
            safe_strcpy(r->origin_type,sizeof(r->origin_type),t->text_value);
        if(ref && ref->text_value)
            safe_strcpy(r->origin_reference,sizeof(r->origin_reference),ref->text_value);
    }

    /* ---------- ROM ---------- */
    if((n = nx_json_get(rom,"file")) && n->text_value)
        safe_strcpy(r->rom_file,sizeof(r->rom_file),n->text_value);

    if((n = nx_json_get(rom,"description")) && n->text_value)
        safe_strcpy(r->description_rom,sizeof(r->description_rom),n->text_value);

    if((n = nx_json_get(rom,"embeddedTitle")) && n->text_value)
        safe_strcpy(r->embedded_title,sizeof(r->embedded_title),n->text_value);

    if((n = nx_json_get(rom,"tickrate"))){
        if(n->type == NX_JSON_INTEGER)
            r->tickrate = (int)n->num.u_value;
        else if(n->type == NX_JSON_STRING && n->text_value)
            r->tickrate = atoi(n->text_value);
    }

    if((n = nx_json_get(rom,"platforms")) && n->type == NX_JSON_ARRAY){
        const nx_json *p = n->children.first;
        while(p && r->platform_count < MAX_PLATFORMS){
            if(p->text_value)
                safe_strcpy(r->platforms[r->platform_count++],
                            sizeof(r->platforms[0]), p->text_value);
            p = p->next;
        }
    }

    /* ---------- COLORS ---------- */
    if((n = nx_json_get(rom,"colors")) && n->type == NX_JSON_OBJECT){
        const nx_json *b = nx_json_get(n,"buzzer");
        const nx_json *s = nx_json_get(n,"silence");
        const nx_json *px = nx_json_get(n,"pixels");

        if(b && b->text_value)
            safe_strcpy(r->color_buzzer,sizeof(r->color_buzzer),b->text_value);
        if(s && s->text_value)
            safe_strcpy(r->color_silence,sizeof(r->color_silence),s->text_value);

        if(px && px->type == NX_JSON_ARRAY){
            const nx_json *c = px->children.first;
            while(c && r->pixel_color_count < MAX_PIXEL_COLORS){
                if(c->text_value)
                    safe_strcpy(r->color_pixels[r->pixel_color_count++],
                                sizeof(r->color_pixels[0]), c->text_value);
                c = c->next;
            }
        }
    }

    /* ---------- KEYS ---------- */
    if((n = nx_json_get(rom,"keys")) && n->type == NX_JSON_OBJECT){
        const nx_json *k = n->children.first;
        while(k && r->key_count < MAX_KEYS){
            if(k->key){
                char valbuf[MAX_STR];
                node_to_cstring(k, valbuf, sizeof(valbuf));
                safe_strcpy(r->keys[r->key_count][0],
                            sizeof(r->keys[0][0]), k->key);
                safe_strcpy(r->keys[r->key_count][1],
                            sizeof(r->keys[0][1]), valbuf);
                r->key_count++;
            }
            k = k->next;
        }
    }

    /* ---------- QUIRKY PLATFORMS ---------- */
    if(chosen)
        safe_strcpy(r->chosen_platform,sizeof(r->chosen_platform),chosen);

    const nx_json *qp = nx_json_get(rom,"quirkyPlatforms");
    if(qp && qp->type == NX_JSON_OBJECT && qp->children.first){
        const nx_json *platform = qp->children.first;
        if(platform->key)
            safe_strcpy(r->quirky_platform,sizeof(r->quirky_platform),platform->key);

        const nx_json *prop = platform->children.first;
        while(prop && r->quirk_count < MAX_QUIRKS){
            if(prop->key){
                char valbuf[MAX_STR];
                node_to_cstring(prop,valbuf,sizeof(valbuf));
                safe_strcpy(r->quirk_keys[r->quirk_count],
                            sizeof(r->quirk_keys[0]), prop->key);
                safe_strcpy(r->quirk_values[r->quirk_count],
                            sizeof(r->quirk_values[0]), valbuf);
                r->quirk_count++;
            }
            prop = prop->next;
        }
    }
}

/* =========================================================
 * Platform selection
 * ========================================================= */
static void finalize_chosen_platform(DB_PROGRAM_rom_info *r){
    if(r->chosen_platform[0])
        return;

    if(r->quirky_platform[0]){
        safe_strcpy(r->chosen_platform,
                    sizeof(r->chosen_platform),
                    r->quirky_platform);
        return;
    }

    if(r->platform_count > 0){
        safe_strcpy(r->chosen_platform,
                    sizeof(r->chosen_platform),
                    r->platforms[0]);
    }
}

/* =========================================================
 * Public API
 * ========================================================= */
int find_rom_by_hash(const char *hash, DB_PROGRAM_rom_info *out){
    if(!hash || !out)
        return FIND_ROM_INVALID_ARGUMENT;

    char *p_txt = read_file(JSON_PROGRAMS);
    if(!p_txt)
        return FIND_ROM_IO_ERROR;

    strip_utf8_bom(p_txt);

    const nx_json *programs = nx_json_parse_utf8(p_txt);
    if(!programs)
        return FIND_ROM_JSON_ERROR;

    int index = 0;
    const nx_json *p = programs->children.first;
    while(p){
        const nx_json *roms = nx_json_get(p,"roms");
        if(roms && roms->type == NX_JSON_OBJECT){
            const nx_json *r = nx_json_get(roms, hash);
            if(r){
                fill_result(out, p, r, NULL, index);
                finalize_chosen_platform(out);
                return FIND_ROM_OK;
            }
        }
        p = p->next;
        index++;
    }

    return FIND_ROM_HASH_NOT_FOUND;
}

/* =========================================================
 * Error strings
 * ========================================================= */
const char *find_rom_strerror(int code){
    switch(code){
        case FIND_ROM_OK: return "No error";
        case FIND_ROM_INVALID_ARGUMENT: return "Invalid argument";
        case FIND_ROM_IO_ERROR: return "I/O error";
        case FIND_ROM_JSON_ERROR: return "JSON parse error";
        case FIND_ROM_HASH_NOT_FOUND: return "Hash not found";
        case FIND_ROM_PROGRAM_NOT_FOUND: return "Program not found";
        case FIND_ROM_ROM_NOT_FOUND: return "ROM not found";
        default: return "Unknown error";
    }
}

/* =========================================================
 * Print ALL fields (always)
 * ========================================================= */
void JSON_DB_print_program(const DB_PROGRAM_rom_info *r){
    if(!r) return;

    printf("=================================================\n");
    printf("DATABASE PROGRAM DATA\n");
    printf("=================================================\n");
    printf("Index       : %s\n", r->program_index);
    printf("Title       : %s\n", r->title);
    printf("Release     : %s\n", r->release);
    printf("License     : %s\n", r->license);  // NAO EXISTE
    printf("Copyright   : %s\n", r->copyright);
    printf("Description : %s\n", r->description_program);
    printf("\nAuthors (%d):\n", r->author_count);
    for(int i=0;i<r->author_count;i++) printf("  - %s\n", r->authors[i]);
    printf("\nImages (%d):\n", r->image_count);
    for(int i=0;i<r->image_count;i++) printf("  - %s\n", r->images[i]);
    printf("\nOrigin:\n   Type: %s\n   Reference: %s\n", r->origin_type, r->origin_reference);

    printf("\n=================================================\n");
    printf("ROM\n");
    printf("=================================================\n");
    printf("File            : %s\n", r->rom_file);
    printf("Embedded Title  : %s\n", r->embedded_title);
    printf("Description     : %s\n", r->description_rom);
    printf("Tickrate        : %d\n", r->tickrate);
    printf("\nPlatforms (%d):\n", r->platform_count);
    for(int i=0;i<r->platform_count;i++) printf("  - %s\n", r->platforms[i]);
        printf("Quirky Platform : %s\n", r->quirky_platform);
    printf("  Quirks (%d):\n", r->quirk_count);
    for(int i=0;i<r->quirk_count;i++)
        printf("     - %s = %s\n", r->quirk_keys[i], r->quirk_values[i]);
    printf("\nColors:\n");
    printf("  Buzzer  : %s\n", r->color_buzzer);
    printf("  Silence : %s\n", r->color_silence);
    for(int i=0;i<r->pixel_color_count;i++)
        printf("  Pixel %d : %s\n", i, r->color_pixels[i]);
    printf("\nKeys (%d):\n", r->key_count);
    for(int i=0;i<r->key_count;i++)
        printf("  %s -> %s\n", r->keys[i][0], r->keys[i][1]);

    printf("\nChosen Platform : %s\n\n", r->chosen_platform);

    printf("=================================================\n\n");
}

DB_PROGRAM_rom_info JSON_DB_query_program(const char *sha1){
    DB_PROGRAM_rom_info rom_info_tmp;
    memset(&rom_info_tmp, 0, sizeof(DB_PROGRAM_rom_info));

    if(!sha1 || !sha1[0]){
        fprintf(stderr, "[JSON_DB_query_program] Invalid hash\n");
        return rom_info_tmp;
    }

    int ret = find_rom_by_hash(sha1, &rom_info_tmp);
    if(ret != FIND_ROM_OK){
        fprintf(stderr,
                "[JSON_DB_query_program] ERROR: %s\n",
                find_rom_strerror(ret));
        memset(&rom_info_tmp, 0, sizeof(DB_PROGRAM_rom_info));
    }

    return rom_info_tmp;
}

// --------------------------------- 1 -  END of Send the hash and receive program info ---------------------------------- //


// -------------------------------- 2 -  START of Send Platform and receive Platform info -------------------------------- //

/* =========================================================
 * Load platform information by ID from the JSON file
 * ========================================================= */
int JSON_DB_query_platform(const char *platform_id, DB_PROGRAM_platform_info *out) {
    if (!platform_id || !out) return -1;

    FILE *f = fopen(JSON_PLATFORMS, "rb");
    if (!f) {
        fprintf(stderr, "Error opening JSON file: %s\n", JSON_PLATFORMS);
        return -1;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *json_data = malloc(fsize + 1);
    if (!json_data) {
        fclose(f);
        return -1;
    }

    fread(json_data, 1, fsize, f);
    fclose(f);
    json_data[fsize] = '\0';

    const nx_json *root = nx_json_parse_utf8(json_data);
    free(json_data);
    if (!root || root->type != NX_JSON_ARRAY) {
        fprintf(stderr, "Invalid JSON format!\n");
        return -1;
    }

    for (int i = 0; i < root->children.length; i++) {
        const nx_json *platform = nx_json_item(root, i);
        const nx_json *id = nx_json_get(platform, "id");
        if (!id || id->type != NX_JSON_STRING) continue;
        if (strcmp(platform_id, id->text_value) != 0) continue;

        /* Fill the output struct */
        memset(out, 0, sizeof(DB_PROGRAM_platform_info));
        strncpy(out->id, id->text_value, MAX_STR - 1);

        const nx_json *name = nx_json_get(platform, "name");
        if (name && name->type == NX_JSON_STRING)
            strncpy(out->name, name->text_value, MAX_STR - 1);

        const nx_json *desc = nx_json_get(platform, "description");
        if (desc && desc->type == NX_JSON_STRING)
            strncpy(out->description, desc->text_value, MAX_STR - 1);

        const nx_json *release = nx_json_get(platform, "release");
        if (release && release->type == NX_JSON_STRING)
            strncpy(out->release, release->text_value, MAX_STR - 1);

        const nx_json *tick = nx_json_get(platform, "defaultTickrate");
        if (tick && (tick->type == NX_JSON_INTEGER || tick->type == NX_JSON_DOUBLE))
            out->default_tickrate = (int)tick->num.u_value;

        /* Load resolutions */
        const nx_json *resolutions = nx_json_get(platform, "displayResolutions");
        if (resolutions && resolutions->type == NX_JSON_ARRAY) {
            out->display_resolution_count = resolutions->children.length;
            for (int j = 0; j < resolutions->children.length && j < MAX_RESOLUTIONS; j++) {
                const nx_json *r = nx_json_item(resolutions, j);
                if (r && r->type == NX_JSON_STRING)
                    strncpy(out->display_resolutions[j], r->text_value, MAX_STR - 1);
            }
        }

        /* Load quirks */
        const nx_json *quirks = nx_json_get(platform, "quirks");
        if (quirks && quirks->type == NX_JSON_OBJECT) {
            #define LOAD_QUIRK(name) \
                { const nx_json *q = nx_json_get(quirks, #name); \
                  if (q && q->type == NX_JSON_BOOL) { out->quirks.name.present = true; out->quirks.name.value = q->num.u_value ? true : false; } \
                  else { out->quirks.name.present = false; out->quirks.name.value = false; } }

            LOAD_QUIRK(shift)
            LOAD_QUIRK(memoryIncrementByX)
            LOAD_QUIRK(memoryLeaveIUnchanged)
            LOAD_QUIRK(wrap)
            LOAD_QUIRK(jump)
            LOAD_QUIRK(vblank)
            LOAD_QUIRK(logic)
        }

        nx_json_free(root);
        return 0; /* Found and loaded */
    }

    nx_json_free(root);
    fprintf(stderr, "Platform '%s' not found!\n", platform_id);
    return -1;
}

/* =========================================================
 * Print platform information
 * ========================================================= */
void JSON_DB_print_platform(const DB_PROGRAM_platform_info *p) {
    if (!p) return;
    
    printf("=================================================\n");
    printf("DATABASE PLATFORM DATA\n");
    printf("=================================================\n");
    printf("ID: %s\n", p->id);
    printf("Name: %s\n", p->name);
    printf("Description: %s\n", p->description);
    printf("Release: %s\n", p->release);
    printf("Tickrate: %d\n", p->default_tickrate);

    printf("Resolutions (%d):\n", p->display_resolution_count);
    for (int i = 0; i < p->display_resolution_count; i++)
        printf("  %s\n", p->display_resolutions[i]);

    printf("Quirks:\n");
    #define PRINT_QUIRK(name) \
        if (p->quirks.name.present) \
            printf("  %s: %s\n", #name, p->quirks.name.value ? "true" : "false"); // \
        // else \
        //     printf("  %s:\n", #name);

    PRINT_QUIRK(shift)
    PRINT_QUIRK(memoryIncrementByX)
    PRINT_QUIRK(memoryLeaveIUnchanged)
    PRINT_QUIRK(wrap)
    PRINT_QUIRK(jump)
    PRINT_QUIRK(vblank)
    PRINT_QUIRK(logic)

    printf("\n");
}

// --------------------------------- 2 -  END of Send Platform and receive Platform info --------------------------------- //





