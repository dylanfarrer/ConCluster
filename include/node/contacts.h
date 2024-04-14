#ifndef CONTACTS_H
#define CONTACTS_H

#include "address.h"

/**
 * @brief struct to represent a set of 'contacts'.
 * Takes an array of node_address structs.
 * Possible use cases:
 *  1.
 *      see address.h
 */
typedef struct {
    node_address** contacts;
    int contact_count;
} node_contacts;

/**
 * @brief Create a node_address struct.
 * Creates a new address array, but shallow copies each node_address structs.
 * if malloc fails or contacts is NULL or contact_count < 0, returns NULL.
 * 
 * @param contacts set of node_address structs to represent contacts. Cannot be NULL.
 * @param contact_count number of contacts, used in operations.
 * @return node_contacts* struct or NULL.
 */
node_contacts* create_contacts(node_address** contacts, int contact_count);

/**
 * @brief deletes a node_contacts struct.
 * Calls node_address function to delete node_address member - if this fails, delete operation cancelled.
 * 
 * @param node_contacts struct to free.
 * @return int 0 on success, -1 on failure.
 */
int delete_contacts(node_contacts* contacts);

#endif
