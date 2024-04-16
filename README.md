# ConCluster - Configurable Cluster

ConCluster is a C library (under-development) for simplifying the creation of multi-agent systems.
It will provide Cluster and Node structures that attempt to make little to no assumptions about the
system they will be integrated into. Additionally, example systems that utilise the Cluster and Node
structures will be available within the codebase.

## Installation

Currently, clone repo, build/link code manually (if looking to use outside of available CMake build).

## Usage

Point to the cluster header
```c
#include "path/to/cluster.h"

// default cluster
cluster* default_cluster = create_cluster_from_default_node(1);
int result = delete_cluster(default_cluster);

// default cloned cluster
cluster* clone_cluster = create_cluster_from_default_node(5);
delete_cluster(clone_cluster);

// custom cloned cluster
node* my_own_node = create_default_node();
cluster* my_own_clone_cluster = create_cluster_from_node(my_own_node, 5);
int node_delete_result = delete_node(my_own_node);
delete_cluster(my_own_clone_cluster);

// handrolled cluster (see node.h for further information on node creation).
node** node_array_I_made_previously;
int node_array_length;
cluster* hand_rolled_cluster = create_cluster(node_array_I_made_previously, node_array_length);
delete_cluster(hand_rolled_cluster);

// pruning a cluster
cluster* clone_cluster_to_prune = create_cluster_from_default_node(5);
int prune_result = delete_cluster_node(clone_cluster_to_prune, 3); // give index
delete_cluster(clone_cluster_to_prune);

// editing a cluster node
address* dummy_address = create_address(NULL, NULL, 0, 0);
cluster* cluster_to_edit = create_cluster_from_default_node(5);
int edit_result = edit_cluster_node(cluster_to_edit,
                                    3,
                                    NULL,
                                    NULL,
                                    dummy_address,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL,
                                    NULL,
                                    0);
                                    // 0-> deep-copy, else, shallow
                                    // see node.h for more information on edit procedure
int address_delete_result = delete_address(dummy_address);
delete_cluster(cluster_to_edit);
```

## Testing

The library and examples are tested together in a GTest suite. This can be run either with CMake,
or Docker.

```bash
# CMake testing
cmake -B build
cmake --build build
ctest --test-dir build

# Docker testing
./docker_test_suite.sh

# Docker testing information
./docker_test_suite.sh -h
./docker_test_suite.sh --help
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
