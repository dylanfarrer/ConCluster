#ifndef ROLE_H
#define ROLE_H

/**
 * @brief struct to represent a node role.
 * Provides an array of both string roles and integer roles.
 * Possible use cases:
 *  1.
 *      character_roles -> array of named roles
 *      integer_roles -> array of bitmap permissions related to roles
 *  2.
 *      (admin use case?)
 *      character_roles -> array of all possible roles
 *      integer_roles -> array of bitmap permissions related to possible roles
 */
typedef struct {
    char** character_roles;
    int* integer_roles;
    int character_role_count;
    int integer_role_count;
} ccon_n_node_role;

/**
 * @brief Create a ccon_n_role struct.
 * Performs a deep copy on character and integer arrays.
 * If malloc fails at anypoint or either count < 0, cleanup is attempted and NULL is returned.
 * Accepts NULL arrays, but will not accept NULL array items in non-NULL arrays.
 * 
 * @param character_roles array of strings to add as a struct member. Assumes each string is null terminated.
 * @param integer_roles array of integers to add as a struct member.
 * @param character_role_count Length of string array, used in operations.
 * @param integer_role_count Length of integer array, used in operations.
 * @return ccon_n_node_role* ccon_n_role struct. NULL if any malloc operation fails.
 */
ccon_n_node_role* ccon_n_create_role(char** character_roles,
                                    int* integer_roles,
                                    int character_role_count,
                                    int integer_role_count);

/**
 * @brief performs deep copy on ccon_n_role struct to create new node_role.
 * if role is NULL, return NULL
 * 
 * @param role struct to copy
 * @return ccon_n_node_role* struct, or NULL
 */
ccon_n_node_role* ccon_n_copy_role(ccon_n_node_role* role);

/**
 * @brief deletes a ccon_n_role struct.
 * 
 * @param role struct to free.
 * @return int 0 on success, -1 if count members are negative (free operation not possible).
 */
int ccon_n_delete_role(ccon_n_node_role* role);

#endif
