#include "../../include/node/background_tasks.h"

#include <stdlib.h>
#include <memory.h>

ccon_n_node_background_tasks* ccon_n_create_background_tasks(ccon_n_node_actions* actions,
                                               void* (*schedule) (void*)) {
    ccon_n_node_background_tasks* background_tasks = malloc(sizeof(ccon_n_node_background_tasks));
    if (background_tasks == NULL) {
        return NULL;
    }

    // shallow copy
    background_tasks->actions = actions;

    // 0 -> not invoked, 1 -> invoked
    background_tasks->invocation_status = 0;
    background_tasks->schedule = schedule;
    return background_tasks;
}

ccon_n_node_background_tasks* ccon_n_copy_background_tasks(ccon_n_node_background_tasks* background_tasks) {
    if (background_tasks == NULL) {
        return NULL;
    }

    return ccon_n_create_background_tasks(ccon_n_copy_actions(background_tasks->actions),
                                   background_tasks->schedule);
}

int ccon_n_delete_background_tasks(ccon_n_node_background_tasks* background_tasks) {
    if (background_tasks == NULL) {
        return 0;
    }

    // call address-specific function
    if (ccon_n_delete_actions(background_tasks->actions) != 0) {
        // if inner member delete failed, stop
        return -1;
    }

    free(background_tasks);
    return 0;
}
