#include "lib_json.h"

// Receive an SHA1 hash and return database ID
int json_search_id(const char *hash) {
    FILE *file = fopen(JSON_SHA1_HASHES, "rb");
    if (!file) {
		fprintf(stderr, "Error opening JSON database file: %s. Exiting.\n", JSON_SHA1_HASHES);
        perror("Error details: ");
        exit(2);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *json_data = malloc(size + 1);
    if (!json_data) {
        perror("JSON_LIB: Error allocating memory. Exiting.\n");
        fclose(file);
		exit(2);
    }

    fread(json_data, 1, size, file);
    fclose(file);
    json_data[size] = '\0';

    const nx_json *root = nx_json_parse(json_data, NULL);
    free(json_data);

    if (!root) {
        fprintf(stderr, "JSON_LIB: Error parsing JSON: %s. Exiting\n", JSON_SHA1_HASHES);
        exit(2);
    }

    if (root->type != NX_JSON_OBJECT) {
        fprintf(stderr, "JSON_LIB: JSON is not an object\n");
        nx_json_free(root);
        exit(2);
    }

    const nx_json *entry = root->children.first;
    int result = -1;

    for (; entry != NULL; entry = entry->next) {
        if (entry->key && strcmp(entry->key, hash) == 0) {
            result = (int)entry->num.s_value;
            break;
        }
    }

    nx_json_free(root);
    return result;
}
