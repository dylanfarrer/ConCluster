#ifndef ADDRESS_H
#define ADDRESS_H

/**
 * @brief struct to represent a node/server address.
 * Provides an array of both string addresses and integer addresses.
 * Possible use cases:
 *  1.
 *      character_addresses -> array of IP/hostname addresses
 *      integer_addresses -> array of ports
 *  2.
 *      character_addresses -> array of watched files
 *  3.
 *      character_addresses -> array of subscribed message bus channels
 *  4.
 *      integer_addresses -> array of process IDs
 */
typedef struct {
    char** character_addresses;
    int* integer_addresses;
    int character_address_count;
    int integer_address_count;
} node_address;

/**
 * @brief Create an address struct.
 * Performs a deep copy on character and integer arrays.
 * If malloc fails at anypoint or either count < 0, cleanup is attempted and NULL is returned.
 * Accepts NULL arrays, but will not accept NULL array items in non-NULL arrays.
 * 
 * @param character_addresses array of strings to add as a struct member. Assumes each string is null terminated.
 * @param integer_addresses array of integers to add as a struct member.
 * @param character_address_count Length of string array, used in operations.
 * @param integer_address_count Length of integer array, used in operations.
 * @return node_address* address struct. NULL if any malloc operation fails.
 */
node_address* create_address(char** character_addresses,
                             int* integer_addresses,
                             int character_address_count,
                             int integer_address_count);

/**
 * @brief deletes an address struct.
 * 
 * @param address struct to free.
 * @return int 0 on success, -1 if count members are negative (free operation not possible).
 */
int delete_address(node_address* address);

#endif
