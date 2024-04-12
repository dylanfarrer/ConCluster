#ifndef BACKGROUND_TASKS
#define BACKGROUND_TASKS

#include "actions.h"

typedef struct {
    node_actions* actions;
    int invocation_status;
    void* (*schedule) (void*);
} node_background_tasks;

node_background_tasks* create_background_tasks(node_actions* actions, void* (*schedule) (void*));
int delete_background_tasks(node_background_tasks* background_tasks);

#endif