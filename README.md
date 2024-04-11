# ConCluster (configurable cluster)

This repo is (will be) designed to provide a simple node cluster that can be configured into varying topologies.
Initial usecase if for experimentation/learning cluster topologies (full mesh, round robin, p2p, master-worker).

## Running Unit Tests
```
cmake -B build
cmake --build build
ctest --test-dir build
```

Alternatively, a shell script to run the test suites with docker can be invoked.
```
./docker_test_suite.sh
```
