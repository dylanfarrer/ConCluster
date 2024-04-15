#ifndef ACTIONS_H
#define ACTIONS_H

/**
 * @brief typedef for easy creation of Action arrays/items.
 * 
 */
typedef void* (*Action) (void*);

/**
 * @brief struct to represent a set of callable actions.
 * Provides an array of void* (void*) function pointers.
 * Possible use cases:
 *  1.
 *      API endpoints.
 *  2.
 *      background maintenance functions.
 *  3.
 *      possible items to populate a workqueue.
 */
typedef struct {
    Action* actions;
    int action_count;
} node_actions;

/**
 * @brief Create an actions struct.
 * Performs a deep copy on the actions array.
 * If malloc fails at anypoint or action_count < 0, cleanup is attempted and NULL is returned.
 * 
 * @param actions array of function pointers (void* return and paramaters).
 * @param action_count length of function pointers array, used in operations.
 * @return node_actions* actions struct, NULL if any malloc operation fails.
 */
node_actions* create_actions(Action* actions, int action_count);

/**
 * @brief deletes an actions struct.
 * 
 * @param actions struct to free.
 * @return int 0 on success, -1 if count members are negative (free operation not possible).
 */
int delete_actions(node_actions* actions);

#endif
