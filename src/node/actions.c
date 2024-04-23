#include "../../include/node/actions.h"

#include <stdlib.h>
#include <memory.h>

ccon_n_node_actions* ccon_n_create_actions(Action* actions, int action_count) {
    if (action_count < 0) {
        return NULL;
    }

    ccon_n_node_actions* actions_struct = malloc(sizeof(ccon_n_node_actions));
    if (actions_struct == NULL) {
        return NULL;
    }

    if (actions == NULL) {
        actions_struct->actions = NULL;
        actions_struct->action_count = 0;
        return actions_struct;
    }

    // although pointer array length cannot directly be determined,
    // if count is less than one, it is not representative of the array.
    if (action_count < 1) {
        free(actions_struct);
        return NULL;
    }

    actions_struct->actions = malloc(sizeof(Action) * action_count);
    if (actions_struct->actions == NULL) {
        free(actions_struct);
        return NULL;
    }
    memcpy(actions_struct->actions, actions, sizeof(Action) * action_count);

    actions_struct->action_count = action_count;

    return actions_struct;
}

ccon_n_node_actions* ccon_n_copy_actions(ccon_n_node_actions* actions) {
    if (actions == NULL) {
        return NULL;
    }

    return ccon_n_create_actions(actions->actions, actions->action_count);
}

int ccon_n_delete_actions(ccon_n_node_actions* actions) {
    if (actions == NULL) {
        return 0;
    }

    if (actions->action_count < 0) {
        return -1;
    }

    if (actions->actions != NULL) {
        free(actions->actions);
    }

    free(actions);
    return 0;
}
