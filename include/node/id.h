#ifndef ID_H
#define ID_H

typedef struct {
    char** character_ids;
    int* integer_ids;
    int character_id_count;
    int integer_id_count;
} node_id;

node_id* create_id(char** character_ids, int* integer_ids, int character_id_count, int integer_id_count);
int delete_id(node_id* id);

#endif