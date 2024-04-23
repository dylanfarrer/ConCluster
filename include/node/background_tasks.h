#ifndef BACKGROUND_TASKS
#define BACKGROUND_TASKS

#include "actions.h"

/**
 * @brief struct to represent a set of background tasks and a schedule mechanism.
 * Takes an action struct as a member to represent the set of background tasks.
 * Possible use cases:
 *  1.
 *      node_actions -> set of work items
 *      schedule -> invoke a producer consumer queue
 *  2.
 *      node_actions -> endpoint functions
 *      schedule -> invoke a server for the endpoints
 *  3.
 *      node_actions -> maintenance functions in Distributed Hash Table protocol
 *      schedule -> invoke a periodic caller on the functions
 */
typedef struct {
    ccon_n_node_actions* actions;
    int invocation_status;
    void* (*schedule) (void*);
} node_background_tasks;

/**
 * @brief Create a background tasks struct.
 * Performs a shallow copy on the actions struct.
 * if malloc fails, returns NULL.
 * 
 * @param actions actions struct to represent background tasks.
 * @param schedule void* (void*) function pointer to represent a schedule mechanism.
 * @return node_background_tasks* struct or NULL.
 */
node_background_tasks* create_background_tasks(ccon_n_node_actions* actions,
                                               void* (*schedule) (void*));

/**
 * @brief performs deep copy on background_tasks struct to create new node_background_tasks.
 * if background_tasks is NULL, return NULL
 * 
 * @param background_tasks struct to copy
 * @return node_background_tasks* struct, or NULL
 */
node_background_tasks* copy_background_tasks(node_background_tasks* background_tasks);

/**
 * @brief deletes a node_background_tasks struct.
 * Calls actions function to delete actions member - if this fails, delete operation cancelled.
 * 
 * @param background_tasks struct to free.
 * @return int 0 on success, -1 on failure.
 */
int delete_background_tasks(node_background_tasks* background_tasks);

#endif
