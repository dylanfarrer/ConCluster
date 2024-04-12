#ifndef ROLE_H
#define ROLE_H

typedef struct {
    char** character_roles;
    int* integer_roles;
    int character_role_count;
    int integer_role_count;
} node_role;

node_role* create_role(char** character_roles, int* integer_roles, int character_role_count, int integer_role_count);
int delete_role(node_role* role);

#endif