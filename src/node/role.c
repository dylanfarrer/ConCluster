#include "../../include/node/role.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node_role* create_role(char** character_roles,
                       int* integer_roles,
                       int character_role_count,
                       int integer_role_count) {
    node_role* role_struct = malloc(sizeof(node_role));
    if (role_struct == NULL) {
        return NULL;
    }

    if (character_role_count < 0 || \
        integer_role_count < 0) {
        return NULL;
    }

    // plus one for null terminator
    role_struct->character_roles = malloc(sizeof(char*) * (character_role_count + 1));
    if (role_struct->character_roles == NULL) {
        free(role_struct);
        return NULL;
    }

    for (int i = 0; i < character_role_count; i++) {
        size_t role_length = strlen(character_roles[i]);
        role_struct->character_roles[i] = malloc(role_length + 1);
        if (role_struct->character_roles[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(role_struct->character_roles[j]);
            }
            free(role_struct->character_roles);
            free(role_struct);
            return NULL;
        }
        strcpy(role_struct->character_roles[i], character_roles[i]);
    }
    // null terminate
    role_struct->character_roles[character_role_count] = NULL; 

    role_struct->integer_roles = malloc(sizeof(int) * integer_role_count);
    if (role_struct->integer_roles == NULL) {
        for (int i = 0; i < character_role_count; i++) {
            free(role_struct->character_roles[i]);
        }
        free(role_struct->character_roles);
        free(role_struct);
        return NULL;
    }
    memcpy(role_struct->integer_roles, integer_roles, sizeof(int) * integer_role_count);

    role_struct->character_role_count = character_role_count;
    role_struct->integer_role_count = integer_role_count;

    return role_struct;
}

int delete_role(node_role* role) {
    if (role == NULL) {
        return 0;
    }

    if (role->integer_role_count < 0 || \
        role->character_role_count < 0) {
        return -1;
    }

    if (role->character_roles != NULL) {
        for (int i = 0; i < role->character_role_count; i++) {
            if (role->character_roles[i] != NULL) {
                free(role->character_roles[i]);
            }
        }
        free(role->character_roles);
    }

    if (role->integer_roles != NULL) {
        free(role->integer_roles);
    }
    free(role);
    return 0;
}