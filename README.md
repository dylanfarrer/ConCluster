# ConCluster - Configurable Cluster

ConCluster is a C library (under-development) for simplifying the creation of multi-agent systems.
It will provide Cluster and Node structures that attempt to make little to no assumptions about the
system they will be integrated into. Additionally, example systems that utilise the Cluster and Node
structures will be available within the codebase.

## Installation

To be filled out when ready.

Current library usage is to clone the repo, point to the node.h and
node.c files.

## Usage

To be filled out when ready.

Current usage -> import node header and use available functions.

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
