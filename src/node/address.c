#include "../../include/node/address.h"

#include <stdlib.h>
#include <string.h>

ccon_n_node_address* ccon_n_create_address(char** character_addresses,
                                        int* integer_addresses,
                                        int character_address_count,
                                        int integer_address_count) {
    
    if (integer_address_count < 0 || \
        character_address_count < 0) {
        return NULL;
    }
    
    ccon_n_node_address* address_struct = malloc(sizeof(ccon_n_node_address));
    if (address_struct == NULL) {
        return NULL;
    }

    if (character_addresses == NULL) {
        address_struct->character_addresses = NULL;
        address_struct->character_address_count = 0;
    } else {
        // although pointer array length cannot directly be determined,
        // if count is less than one, it is not representative of the array.
        if (character_address_count < 1) {
            free(address_struct);
            return NULL;
        }

        address_struct->character_addresses = malloc(sizeof(char*) * character_address_count);
        if (address_struct->character_addresses == NULL) {
            free(address_struct);
            return NULL;
        }

        for (int i = 0; i < character_address_count; i++) {
            size_t role_length = strlen(character_addresses[i]);
            address_struct->character_addresses[i] = malloc(role_length + 1);
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

        address_struct->character_address_count = character_address_count;
    }

    if (integer_addresses == NULL) {
        address_struct->integer_addresses = NULL;
        address_struct->integer_address_count = 0;
    } else {
        // although pointer array length cannot directly be determined,
        // if count is less than one, it is not representative of the array.
        if (integer_address_count < 1) {
            for (int i = 0; i < address_struct->character_address_count; i++) {
                if (address_struct->character_addresses[i] != NULL) {
                    free(address_struct->character_addresses[i]);
                }
            }
            free(address_struct);
            return NULL;
        }

        address_struct->integer_addresses = malloc(sizeof(int) * integer_address_count);
        if (address_struct->integer_addresses == NULL) {
            for (int i = 0; i < address_struct->character_address_count; i++) {
                free(address_struct->character_addresses[i]);
            }
            free(address_struct->character_addresses);
            free(address_struct);
            return NULL;
        }
        memcpy(address_struct->integer_addresses, integer_addresses, sizeof(int) * integer_address_count);

        address_struct->integer_address_count = integer_address_count;
    }

    return address_struct;
}

ccon_n_node_address* ccon_n_copy_address(ccon_n_node_address* address) {
    if (address == NULL) {
        return NULL;
    }

    return ccon_n_create_address(address->character_addresses,
                          address->integer_addresses,
                          address->character_address_count,
                          address->integer_address_count);
}

int ccon_n_delete_address(ccon_n_node_address* address) {
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
