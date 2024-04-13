#ifndef ID_H
#define ID_H

/**
 * @brief struct to represent a node/server id.
 * Provides an array of both string ids and integer ids.
 * Possible use cases:
 *  1.
 *      use arrays to store local and far identifiers for node.
 *  2.
 *      use arrays to store each 'level' the node is available in wrt system topology.
 */
typedef struct {
    char** character_ids;
    int* integer_ids;
    int character_id_count;
    int integer_id_count;
} node_id;

/**
 * @brief Create an id struct.
 * Performs a deep copy on character and integer arrays.
 * If malloc fails at anypoint or either count < 0, cleanup is attempted and NULL is returned.
 * 
 * @param character_ids array of strings to add as a struct member. Assumes each string is null terminated.
 * @param integer_ids array of integers to add as a struct member.
 * @param character_id_count Length of string array, used in operations.
 * @param integer_id_count Length of integer array, used in operations.
 * @return node_id* id struct. NULL if any malloc operation fails.
 */
node_id* create_id(char** character_ids,
                   int* integer_ids,
                   int character_id_count,
                   int integer_id_count);

/**
 * @brief deletes an id struct.
 * 
 * @param id struct to free.
 * @return int 0 on success, -1 if count members are negative (free operation not possible).
 */
int delete_id(node_id* id);

#endif
