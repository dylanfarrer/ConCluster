#ifndef CONTACTS_H
#define CONTACTS_H

#include "address.h"

typedef struct {
    node_address** contacts;
    int contact_count;
} node_contacts;

node_contacts* create_contacts(node_address** contacts, int contact_count);
int delete_contacts(node_contacts* contacts);

#endif