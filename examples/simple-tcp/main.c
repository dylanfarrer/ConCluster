#include "cluster_manager.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_nodes>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int node_count = atoi(argv[1]);
    if (node_count <= 0) {
        fprintf(stderr, "Invalid number of nodes: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("Generating cluster...\n");

    cluster* cl = generate_cluster(node_count);
    if (cl == NULL) {
        fprintf(stderr, "Failed to create cluster\n");
        return EXIT_FAILURE;
    }

    printf("Starting chatter event...\n");

    /*
    int chatter_time_ms = 10000;
    int result = perform_chatter_event(cl, chatter_time_ms);
    if (result < 0) {
        fprintf(stderr, "Chatter event failed\n");
        delete_cluster(&cl);
        return EXIT_FAILURE;
    }

    printf("Finished chatter event...\n");

    printf("Final message count: %d\n", result);
    */
    if (delete_cluster(&cl) == -1) {
        fprintf(stderr, "Failed to delete cluster\n");
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
