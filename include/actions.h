#ifndef ACTIONS_H
#define ACTIONS_H

#define EXPORT __attribute__((__visibility__("default")))

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
} ccon_n_node_actions;

/**
 * @brief Create a ccon_n_actions struct.
 * Performs a deep copy on the actions array.
 * If malloc fails at anypoint or action_count < 0, cleanup is attempted and NULL is returned.
 * 
 * @param actions array of function pointers (void* return and paramaters).
 * @param action_count length of function pointers array, used in operations.
 * @return ccon_n_node_actions* actions struct, NULL if any malloc operation fails.
 */
EXPORT ccon_n_node_actions* ccon_n_create_actions(Action* actions, int action_count);

/**
 * @brief performs deep copy on action struct to create new ccon_n_node_actions.
 * if actions is NULL, return NULL
 * 
 * @param actions struct to copy
 * @return ccon_n_node_actions* struct, or NULL
 */
EXPORT ccon_n_node_actions* ccon_n_copy_actions(ccon_n_node_actions* actions);

/**
 * @brief deletes a ccon_n_actions struct.
 * Nullifies the struct pointer.
 * 
 * @param actions struct to free.
 * @return int 0 on success, -1 if count members are negative (free operation not possible).
 */
EXPORT int ccon_n_delete_actions(ccon_n_node_actions** actions);

/**
 * @brief invokes an action in the ccon_n_node_actions struct
 * result must be a valid pointer, otherwise NULL is returned.
 * if action_index is out of range, result is -1.
 * result will be set to zero if the function is invoked,
 * but does not necessarily indicate successful function execution.
 * 
 * @param actions struct to utilise
 * @param action_index index of action
 * @param result must not be NULL, will be overwritten to 0 or -1.
 * @param arguments args to give to action
 * @return void* returns action return value.
 */
EXPORT void* ccon_n_invoke_action(ccon_n_node_actions* actions,
                                  int action_index,
                                  int* result,
                                  void* arguments);

#endif
