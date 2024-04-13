#include "../../include/node/id.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node_id* create_id(char** character_ids,
                   int* integer_ids,
                   int character_id_count,
                   int integer_id_count) {
    node_id* id_struct = malloc(sizeof(node_id));
    if (id_struct == NULL) {
        return NULL;
    }

    // plus one for null terminator
    id_struct->character_ids = malloc(sizeof(char*) * (character_id_count + 1));
    if (id_struct->character_ids == NULL) {
        free(id_struct);
        return NULL;
    }

    for (int i = 0; i < character_id_count; i++) {
        size_t id_len = strlen(character_ids[i]);
        // sizeof(char) is always 1
        id_struct->character_ids[i] = malloc(id_len + 1);
        if (id_struct->character_ids[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(id_struct->character_ids[j]);
            }
            free(id_struct->character_ids);
            free(id_struct);
            return NULL;
        }
        strcpy(id_struct->character_ids[i], character_ids[i]);
    }
    // null terminate
    id_struct->character_ids[character_id_count] = NULL;

    id_struct->integer_ids = malloc(sizeof(int) * integer_id_count);
    if (id_struct->integer_ids == NULL) {
        for (int i = 0; i < character_id_count; i++) {
            free(id_struct->character_ids[i]);
        }
        free(id_struct->character_ids);
        free(id_struct);
        return NULL;
    }

    memcpy(id_struct->integer_ids, integer_ids, sizeof(int) * integer_id_count);

    id_struct->character_id_count = character_id_count;
    id_struct->integer_id_count = integer_id_count;
    return id_struct;
}

int delete_id(node_id* id) {
    if (id == NULL) {
        return 0;
    }

    if (id->integer_id_count < 0 || \
        id->character_id_count < 0) {
        return -1;
    }

    for (int i = 0; i < id->character_id_count; i++) {
        free(id->character_ids[i]);
    }
    free(id->character_ids);
    free(id->integer_ids);
    free(id);
    return 0;
}
