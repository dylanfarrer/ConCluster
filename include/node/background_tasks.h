#ifndef BACKGROUND_TASKS
#define BACKGROUND_TASKS

#include "actions.h"

/**
 * @brief struct to represent a set of background tasks and a schedule mechanism.
 * Takes a ccon_n_actions struct as a member to represent the set of background tasks.
 * Possible use cases:
 *  1.
 *      ccon_n_node_actions -> set of work items
 *      schedule -> invoke a producer consumer queue
 *  2.
 *      ccon_n_node_actions -> endpoint functions
 *      schedule -> invoke a server for the endpoints
 *  3.
 *      ccon_n_node_actions -> maintenance functions in Distributed Hash Table protocol
 *      schedule -> invoke a periodic caller on the functions
 */
typedef struct {
    ccon_n_node_actions* actions;
    int invocation_status;
    void* (*schedule) (void*);
} ccon_n_node_background_tasks;

/**
 * @brief Create a ccon_n_background_tasks struct.
 * Performs a shallow copy on the ccon_n_actions struct.
 * if malloc fails, returns NULL.
 * 
 * @param actions ccon_n_actions struct to represent background tasks.
 * @param schedule void* (void*) function pointer to represent a schedule mechanism.
 * @return ccon_n_node_background_tasks* struct or NULL.
 */
ccon_n_node_background_tasks* ccon_n_create_background_tasks(ccon_n_node_actions* actions,
                                                             void* (*schedule) (void*));

/**
 * @brief performs deep copy on ccon_n_background_tasks struct to create new node_background_tasks.
 * if background_tasks is NULL, return NULL
 * 
 * @param background_tasks struct to copy
 * @return ccon_n_node_background_tasks* struct, or NULL
 */
ccon_n_node_background_tasks* ccon_n_copy_background_tasks(ccon_n_node_background_tasks* background_tasks);

/**
 * @brief deletes a ccon_n_node_background_tasks struct.
 * Calls ccon_n_actions function to delete ccon_n_actions member - if this fails, delete operation cancelled.
 * 
 * @param background_tasks struct to free.
 * @return int 0 on success, -1 on failure.
 */
int ccon_n_delete_background_tasks(ccon_n_node_background_tasks* background_tasks);

#endif
