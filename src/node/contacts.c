#include "../../include/node/contacts.h"

#include <stdlib.h>
#include <memory.h>

node_contacts* create_contacts(node_address** contacts, int contact_count) {
    if (contacts == NULL || contact_count < 1) {
        return NULL;
    }

    for (int i = 0; i < contact_count; i++) {
        if (contacts[i] == NULL) {
            return NULL;
        }
    }

    node_contacts* contacts_struct = malloc(sizeof(node_contacts));
    if (contacts_struct == NULL) {
        return NULL;
    }

    contacts_struct->contacts = malloc(sizeof(node_address*) * contact_count);
    if (contacts_struct->contacts == NULL) {
        free(contacts_struct);
        return NULL;
    }
    
    for (int i = 0; i < contact_count; i++) {
        contacts_struct->contacts[i] = contacts[i];
    }

    contacts_struct->contact_count = contact_count;
    return contacts_struct;
}

int delete_contacts(node_contacts* contacts) {
    if (contacts == NULL) {
        return 0;
    }

    if (contacts->contact_count < 0) {
        return -1;
    }

    if (contacts->contacts != NULL) {
        for (int i = 0; i < contacts->contact_count; i++) {
            if (delete_address(contacts->contacts[i]) != 0) {
                return -1;
            }
        }
        free(contacts->contacts);
    }
    free(contacts);
    return 0;
}
