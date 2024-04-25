#ifndef ADDRESS_H
#define ADDRESS_H

#define EXPORT __attribute__((__visibility__("default")))

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
EXPORT typedef struct {
    char** character_addresses;
    int* integer_addresses;
    int character_address_count;
    int integer_address_count;
} ccon_n_node_address;

/**
 * @brief Create a ccon_n_address struct.
 * Performs a deep copy on character and integer arrays.
 * If malloc fails at anypoint or either count < 0, cleanup is attempted and NULL is returned.
 * Accepts NULL arrays, but will not accept NULL array items in non-NULL arrays.
 * 
 * @param character_addresses array of strings to add as a struct member. Assumes each string is null terminated.
 * @param integer_addresses array of integers to add as a struct member.
 * @param character_address_count Length of string array, used in operations.
 * @param integer_address_count Length of integer array, used in operations.
 * @return ccon_n_node_address* address struct. NULL if any malloc operation fails.
 */
EXPORT ccon_n_node_address* ccon_n_create_address(char** character_addresses,
                                           int* integer_addresses,
                                           int character_address_count,
                                           int integer_address_count);

/**
 * @brief performs deep copy on ccon_n_address struct to create new node_address.
 * if address is NULL, return NULL
 * 
 * @param address struct to copy
 * @return ccon_n_node_address* struct, or NULL
 */
EXPORT ccon_n_node_address* ccon_n_copy_address(ccon_n_node_address* address);

/**
 * @brief deletes a ccon_n_address struct.
 * nullifies struct pointer.
 * 
 * @param address struct to free.
 * @return int 0 on success, -1 if count members are negative (free operation not possible).
 */
EXPORT int ccon_n_delete_address(ccon_n_node_address** address);

#endif
