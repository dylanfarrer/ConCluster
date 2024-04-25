#include "include/contacts.h"

#include <stdlib.h>
#include <memory.h>

ccon_n_node_contacts* ccon_n_create_contacts(ccon_n_node_address** contacts, int contact_count) {
    if (contact_count < 0) {
        return NULL;
    }

    ccon_n_node_contacts* contacts_struct = malloc(sizeof(ccon_n_node_contacts));
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

    contacts_struct->contacts = malloc(sizeof(ccon_n_node_address*) * contact_count);
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

ccon_n_node_contacts* ccon_n_copy_contacts(ccon_n_node_contacts* contacts) {
    if (contacts == NULL) {
        return NULL;
    }

    if (contacts->contacts == NULL) {
        return ccon_n_create_contacts(NULL, 0);
    }

    // incorrect count
    if (contacts->contact_count < 1) {
        return NULL;
    }

    ccon_n_node_address** new_contacts_array = malloc(sizeof(ccon_n_node_address*) * contacts->contact_count);
    if (new_contacts_array == NULL) {
        return NULL;
    }

    for (int i = 0; i < contacts->contact_count; i++) {
        new_contacts_array[i] = ccon_n_copy_address(contacts->contacts[i]);
    }

    ccon_n_node_contacts* new_contacts = ccon_n_create_contacts(new_contacts_array, contacts->contact_count);

    free(new_contacts_array);

    return new_contacts;
}

int ccon_n_delete_contacts(ccon_n_node_contacts** contacts) {
    if (contacts == NULL || (*contacts) == NULL) {
        return 0;
    }

    if ((*contacts)->contact_count < 0) {
        return -1;
    }

    for (int i = 0; i < (*contacts)->contact_count; i++) {
        if (ccon_n_delete_address(&((*contacts)->contacts[i])) != 0) {
            return -1;
        }
    }
    free((*contacts)->contacts);

    free((*contacts));
    *contacts = NULL;
    return 0;
}
