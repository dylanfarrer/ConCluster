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
} node_role;

/**
 * @brief Create a role struct.
 * Performs a deep copy on character and integer arrays.
 * If malloc fails at anypoint or either count < 0 or either array is NULL, cleanup is attempted and NULL is returned.
 * 
 * @param character_roles array of strings to add as a struct member. Assumes each string is null terminated.
 * @param integer_roles array of integers to add as a struct member.
 * @param character_role_count Length of string array, used in operations.
 * @param integer_role_count Length of integer array, used in operations.
 * @return node_role* role struct. NULL if any malloc operation fails.
 */
node_role* create_role(char** character_roles,
                       int* integer_roles,
                       int character_role_count,
                       int integer_role_count);

/**
 * @brief deletes a role struct.
 * 
 * @param role struct to free.
 * @return int 0 on success, -1 if count members are negative (free operation not possible).
 */
int delete_role(node_role* role);

#endif
