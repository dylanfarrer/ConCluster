#include "../../include/node/background_tasks.h"

#include <stdlib.h>
#include <memory.h>

node_background_tasks* create_background_tasks(node_actions* actions,
                                               void* (*schedule) (void*)) {
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

node_background_tasks* copy_background_tasks(node_background_tasks* background_tasks) {
    if (background_tasks == NULL) {
        return NULL;
    }

    return create_background_tasks(copy_actions(background_tasks->actions),
                                   background_tasks->schedule);
}

int delete_background_tasks(node_background_tasks* background_tasks) {
    if (background_tasks == NULL) {
        return 0;
    }

    // call address-specific function
    if (delete_actions(background_tasks->actions) != 0) {
        // if inner member delete failed, stop
        return -1;
    }

    free(background_tasks);
    return 0;
}
