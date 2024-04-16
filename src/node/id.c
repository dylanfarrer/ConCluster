#include "../../include/node/id.h"

#include <stdlib.h>
#include <string.h>

node_id* create_id(char** character_ids,
                   int* integer_ids,
                   int character_id_count,
                   int integer_id_count) {
    if (character_id_count < 0 || \
        integer_id_count < 0) {
        return NULL;
    }

    node_id* id_struct = malloc(sizeof(node_id));
    if (id_struct == NULL) {
        return NULL;
    }

    if (character_ids == NULL) {
        id_struct->character_ids = NULL;
        id_struct->character_id_count = 0;
    } else {
        // although pointer array length cannot directly be determined,
        // if count is less than one, it is not representative of the array.
        if (character_id_count < 1) {
            free(id_struct);
            return NULL;
        }

        id_struct->character_ids = malloc(sizeof(char*) * character_id_count);
        if (id_struct->character_ids == NULL) {
            free(id_struct);
            return NULL;
        }

        for (int i = 0; i < character_id_count; i++) {
            size_t role_length = strlen(character_ids[i]);
            id_struct->character_ids[i] = malloc(role_length + 1);
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

        id_struct->character_id_count = character_id_count;
    }

    if (integer_ids == NULL) {
        id_struct->integer_ids = NULL;
        id_struct->integer_id_count = 0;
    } else {
        // although pointer array length cannot directly be determined,
        // if count is less than one, it is not representative of the array.
        if (integer_id_count < 1) {
            for (int i = 0; i < id_struct->character_id_count; i++) {
                if (id_struct->character_ids[i] != NULL) {
                    free(id_struct->character_ids[i]);
                }
            }
            free(id_struct);
            return NULL;
        }

        id_struct->integer_ids = malloc(sizeof(int) * integer_id_count);
        if (id_struct->integer_ids == NULL) {
            for (int i = 0; i < id_struct->character_id_count; i++) {
                free(id_struct->character_ids[i]);
            }
            free(id_struct->character_ids);
            free(id_struct);
            return NULL;
        }
        memcpy(id_struct->integer_ids, integer_ids, sizeof(int) * integer_id_count);

        id_struct->integer_id_count = integer_id_count;
    }

    return id_struct;
}

node_id* copy_id(node_id* id) {
    if (id == NULL) {
        return NULL;
    }

    return create_id(id->character_ids,
                     id->integer_ids,
                     id->character_id_count,
                     id->integer_id_count);
}

int delete_id(node_id* id) {
    if (id == NULL) {
        return 0;
    }

    if (id->integer_id_count < 0 || \
        id->character_id_count < 0) {
        return -1;
    }

    if (id->character_ids != NULL) {
        for (int i = 0; i < id->character_id_count; i++) {
            if (id->character_ids[i] != NULL) {
                free(id->character_ids[i]);
            }
        }
        free(id->character_ids);
    }

    if (id->integer_ids != NULL) {
        free(id->integer_ids);
    }
    free(id);
    return 0;
}
