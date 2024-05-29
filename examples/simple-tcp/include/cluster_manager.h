#ifndef CLUSTER_MANAGER_H
#define CLUSTER_MANAGER_H

#include "../../utils/include/socker_handler.h"
#include "../../utils/include/thread_handler.h"

#include <concluster/cluster.h>
#include <stdatomic.h>

/**
 * @brief struct that wraps arounf ccon_cluster, providing an additional
 * message_count metric, that will log the number of messages sent between
 * nodes.
 */
typedef struct {
    ccon_cluster cluster;
    _Atomic(int) message_count;
} cluster;

/**
 * @brief create a cluster of usecase specific nodes, with a configurable size.
 * 
 * @param node_count 
 * @return cluster* 
 */
cluster* generate_cluster(int node_count);

/**
 * @brief start the nodes talking with each other for a given time frame.
 * 
 * @param ms_time 
 * @return int 
 */
int perform_chatter_event(int ms_time);

/**
 * @brief delete a cluster struct.
 * 
 * @param cluster_to_delete 
 * @return true 
 * @return false 
 */
int delete_cluster(cluster** cluster_to_delete);

#endif
