#ifndef ACTIONS_H
#define ACTIONS_H

typedef void* (*Action) (void*);

typedef struct {
    Action* actions;
    int action_count;
} node_actions;

node_actions* create_actions(Action* actions, int action_count);
int delete_actions(node_actions* actions);

#endif