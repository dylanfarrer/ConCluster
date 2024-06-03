#ifndef CLUSTER_MANAGER_H
#define CLUSTER_MANAGER_H

#include "socket_handler.h"
#include "thread_handler.h"

#include <concluster/cluster.h>
#include <stdatomic.h>

/**
 * @brief struct that wraps around ccon_cluster, providing an additional
 * message_count metric, that will log the number of messages sent between
 * nodes.
 */
typedef struct {
    ccon_cluster* cluster;
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
int perform_chatter_event(cluster* cluster_to_invoke, int ms_time);

/**
 * @brief delete a cluster struct.
 * 
 * @param cluster_to_delete 
 * @return int 0 if success, -1 else  
 */
int delete_cluster(cluster** cluster_to_delete);

#endif
