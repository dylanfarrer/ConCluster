#include "../../include/node/address.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

node_address* create_address(char** character_addresses,
                             int* integer_addresses,
                             int character_address_count,
                             int integer_address_count) {
    node_address* address_struct = malloc(sizeof(node_address));
    if (address_struct == NULL) {
        return NULL;
    }

    if (integer_address_count < 0 || \
        character_address_count < 0) {
        return NULL;
    }

    // plus one for null terminator
    address_struct->character_addresses = malloc(sizeof(char*) * (character_address_count + 1));
    if (address_struct->character_addresses == NULL) {
        free(address_struct);
        return NULL;
    }

    for (int i = 0; i < character_address_count; i++) {
        size_t address_len = strlen(character_addresses[i]);
        // sizeof(char) is always 1
        address_struct->character_addresses[i] = malloc(address_len + 1);
        if (address_struct->character_addresses[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(address_struct->character_addresses[j]);
            }
            free(address_struct->character_addresses);
            free(address_struct);
            return NULL;
        }
        strcpy(address_struct->character_addresses[i], character_addresses[i]);
    }
    // null terminate
    address_struct->character_addresses[character_address_count] = NULL;

    address_struct->integer_addresses = malloc(sizeof(int) * integer_address_count);
    if (address_struct->integer_addresses == NULL) {
        for (int i = 0; i < character_address_count; i++) {
            free(address_struct->character_addresses[i]);
        }
        free(address_struct->character_addresses);
        free(address_struct);
        return NULL;
    }
    memcpy(address_struct->integer_addresses, integer_addresses, sizeof(int) * integer_address_count);

    address_struct->character_address_count = character_address_count;
    address_struct->integer_address_count = integer_address_count;

    return address_struct;
}

int delete_address(node_address* address) {
    if (address == NULL) {
        return 0;
    }

    if (address->integer_address_count < 0 || \
        address->character_address_count < 0) {
        return -1;
    }

    if (address->character_addresses != NULL) {
        for (int i = 0; i < address->character_address_count; i++) {
            if (address->character_addresses[i] != NULL) {
                free(address->character_addresses[i]);
            }
        }
        free(address->character_addresses);
    }

    if (address->integer_addresses != NULL) {
        free(address->integer_addresses);
    }
    free(address);
    return 0;
}