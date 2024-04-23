#ifndef CONTACTS_H
#define CONTACTS_H

#include "address.h"

/**
 * @brief struct to represent a set of 'contacts'.
 * Takes an array of ccon_n_node_address structs.
 * Possible use cases:
 *  1.
 *      see address.h
 */
typedef struct {
    ccon_n_node_address** contacts;
    int contact_count;
} ccon_n_node_contacts;

/**
 * @brief Create a ccon_n_node_address struct.
 * Creates a new address array, but shallow copies each ccon_n_node_address structs.
 * if malloc fails or contact_count < 0, returns NULL.
 * Accepts NULL array, but will not accept NULL array items in non-NULL array.
 * 
 * @param contacts set of ccon_n_node_address structs to represent contacts.
 * @param contact_count number of contacts, used in operations.
 * @return ccon_n_node_contacts* struct or NULL.
 */
ccon_n_node_contacts* ccon_n_create_contacts(ccon_n_node_address** contacts, int contact_count);

/**
 * @brief performs deep copy on contacts struct to create new ccon_n_node_contacts.
 * if contacts is NULL, return NULL
 * 
 * @param contacts struct to copy
 * @return ccon_n_node_contacts* struct, or NULL
 */
ccon_n_node_contacts* ccon_n_copy_contacts(ccon_n_node_contacts* contacts);

/**
 * @brief deletes a ccon_n_node_contacts struct.
 * Calls ccon_n_node_address function to delete ccon_n_node_address member - if this fails, delete operation cancelled.
 * 
 * @param node_contacts struct to free.
 * @return int 0 on success, -1 on failure.
 */
int ccon_n_delete_contacts(ccon_n_node_contacts* contacts);

#endif
