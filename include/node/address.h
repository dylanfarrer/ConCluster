#ifndef ADDRESS_H
#define ADDRESS_H

typedef struct {
    char** character_addresses;
    int* integer_addresses;
    int character_address_count;
    int integer_address_count;
} node_address;

node_address* create_address(char** character_addresses,
                             int* integer_addresses,
                             int character_address_count,
                             int integer_address_count);

int delete_address(node_address* address);

#endif