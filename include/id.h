#ifndef ID_H
#define ID_H

#define EXPORT __attribute__((__visibility__("default")))

/**
 * @brief struct to represent a node/server id.
 * Provides an array of both string ids and integer ids.
 * Possible use cases:
 *  1.
 *      use arrays to store local and far identifiers for node.
 *  2.
 *      use arrays to store each 'level' the node is available in wrt system topology.
 */
EXPORT typedef struct {
    char** character_ids;
    int* integer_ids;
    int character_id_count;
    int integer_id_count;
} ccon_n_node_id;

/**
 * @brief Create a ccon_n_id struct.
 * Performs a deep copy on character and integer arrays.
 * If malloc fails at anypoint or either count < 0, cleanup is attempted and NULL is returned.
 * Accepts NULL arrays, but will not accept NULL array items in non-NULL arrays.
 * 
 * @param character_ids array of strings to add as a struct member. Assumes each string is null terminated.
 * @param integer_ids array of integers to add as a struct member.
 * @param character_id_count Length of string array, used in operations.
 * @param integer_id_count Length of integer array, used in operations.
 * @return ccon_n_node_id* id struct. NULL if any malloc operation fails.
 */
EXPORT ccon_n_node_id* ccon_n_create_id(char** character_ids,
                                 int* integer_ids,
                                 int character_id_count,
                                 int integer_id_count);

/**
 * @brief performs deep copy on ccon_n_id struct to create new node_id.
 * if id is NULL, return NULL
 * 
 * @param id struct to copy
 * @return ccon_n_node_id* struct, or NULL
 */
EXPORT ccon_n_node_id* ccon_n_copy_id(ccon_n_node_id* id);

/**
 * @brief deletes a ccon_n_id struct.
 * nullifies id struct pointer.
 * 
 * @param id struct to free.
 * @return int 0 on success, -1 if count members are negative (free operation not possible).
 */
EXPORT int ccon_n_delete_id(ccon_n_node_id** id);

#endif
