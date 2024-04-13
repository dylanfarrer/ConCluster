#include "../../include/node/background_tasks.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

node_background_tasks* create_background_tasks(node_actions* actions,
                                               void* (*schedule) (void*)) {
    if (actions == NULL) {
        return NULL;
    }

    node_background_tasks* background_tasks = malloc(sizeof(node_background_tasks));
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

int delete_background_tasks(node_background_tasks* background_tasks) {
    if (background_tasks == NULL) {
        return 0;
    }

    if (background_tasks->actions != NULL) {
        // call action-specific function
        if (delete_actions(background_tasks->actions) != 0) {
            // if inner member delete failed, stop
            return -1;
        }
    }

    free(background_tasks);
    return 0;
}
