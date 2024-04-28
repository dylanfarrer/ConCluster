# ConCluster - Configurable Cluster

ConCluster is a C library (under-development) for simplifying the creation of multi-agent systems.
It provides the Cluster and Node structures, which attempt to make little-to-no assumptions about
the client requirements, such as cluster topology or node interaction medium.

## Installation
ConCluster is offered as a shared library. It relies on a few standard library headers.
```bash
cmake -B build
cmake --build build
# may need sudo
sudo cmake --install build
```

Example CMakeLists.txt file (with a main.c):
```bash
cmake_minimum_required(VERSION 3.0)
project(MyProject)

find_library(CONCLUSTER_LIB concluster PATHS /usr/local/lib)

include_directories(/usr/local/include/)

add_executable(my_program main.c)

target_link_libraries(my_program ${CONCLUSTER_LIB})
```

## Usage
```c
#include <concluster/cluster.h>

// Cluster and Node use the prefix 'ccon_', and
// provide create, delete and edit functions.
// Node also has copy. Cluster also has append.
//
// Inner node members use the prefix 'ccon_n_', and
// provide create, delete and copy functions.
//
// See individual headers for further information.


// default cluster
ccon_cluster* default_cluster = ccon_create_cluster_from_default_node(1);
int result = ccon_delete_cluster(&default_cluster);

// default cloned cluster
ccon_cluster* clone_cluster = ccon_create_cluster_from_default_node(5);
ccon_delete_cluster(&clone_cluster);

// custom cloned cluster
ccon_node* my_own_node = ccon_create_default_node();
ccon_cluster* my_own_clone_cluster = ccon_create_cluster_from_node(my_own_node, 5);
int node_delete_result = ccon_delete_node(&my_own_node);
ccon_delete_cluster(&my_own_clone_cluster);

// handrolled cluster (see node.h for further information on node creation).
ccon_node** node_array_I_made_previously;
int node_array_length;
ccon_cluster* hand_rolled_cluster = ccon_create_cluster(node_array_I_made_previously, node_array_length);
ccon_delete_cluster(&hand_rolled_cluster);

// pruning a cluster
ccon_cluster* clone_cluster_to_prune = ccon_create_cluster_from_default_node(5);
int prune_result = ccon_delete_cluster_node(clone_cluster_to_prune, 3); // give index
ccon_delete_cluster(&clone_cluster_to_prune);

// editing a cluster node
// ccon_n_address is a ccon_node member, so uses the 'ccon_n_' prefix.
ccon_n_address* dummy_address = ccon_n_create_address(NULL, NULL, 0, 0);
ccon_cluster* cluster_to_edit = ccon_create_cluster_from_default_node(5);
int edit_result = ccon_edit_cluster_node(cluster_to_edit,
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
int address_delete_result = ccon_n_delete_address(&dummy_address);
ccon_delete_cluster(&cluster_to_edit);

// inserting node into a cluster
ccon_node* hand_rolled_node = ccon_create_node(/* see node.h for full args */);
ccon_cluster* changing_cluster = ccon_create_cluster_from_default_node(5);
int insert_result = ccon_insert_cluster_node(&changing_cluster, hand_rolled_node, 3 /* index */);
// changing_cluster->node_count == 6
ccon_delete_cluster(clone_cluster);

// invocations
ccon_node* premade_cluster;
int invocation_result = 0; // did the invocation work?
void* premade_arguments;

void* action_result = ccon_n_invoke_action(premade_cluster->nodes[0]->actions,
                                           /*action_index*/ 0,
                                           &invocation_result,
                                           premade_arguments);

void* serve_result = ccon_n_invoke_server(premade_cluster->nodes[0]->servers->servers[0],
                                          &invocation_result,
                                          premade_arguments);

void* schedule_result = ccon_n_invoke_scheduler(premade_cluster->nodes[0]->background_tasks,
                                                &invocation_result,
                                                premade_arguments);

free(action_result);
free(serve_result);
free(schedule_result);
```

## Testing

The library and examples are tested together in a GTest suite. This can be run either with CMake,
or Docker. CMake assumes the library has been installed.

```bash
# CMake testing
cd tests
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
