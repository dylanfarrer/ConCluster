#include "../../include/node/contacts.h"

#include <stdlib.h>
#include <memory.h>

node_contacts* create_contacts(node_address** contacts, int contact_count) {
    if (contact_count < 0) {
        return NULL;
    }

    node_contacts* contacts_struct = malloc(sizeof(node_contacts));
    if (contacts_struct == NULL) {
        return NULL;
    }

    if (contacts == NULL) {
        contacts_struct->contacts = NULL;
        contacts_struct->contact_count = 0;
        return contacts_struct;
    }

    // although pointer array length cannot directly be determined,
    // if count is less than one, it is not representative of the array.
    if (contact_count < 1) {
        free(contacts_struct);
        return NULL;
    }

    // if there is a null member in the array, return NULL.
    for (int i = 0; i < contact_count; i++) {
        if (contacts[i] == NULL) {
            free(contacts_struct);
            return NULL;
        }
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

    for (int i = 0; i < contacts->contact_count; i++) {
        if (delete_address(contacts->contacts[i]) != 0) {
            return -1;
        }
    }
    free(contacts->contacts);

    free(contacts);
    return 0;
}
