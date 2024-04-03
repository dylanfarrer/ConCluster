# ConCluster (configurable cluster)

This repo is (will be) designed to provide a simple node cluster that can be configured into varying topologies.
Initial usecase if for experimentation/learning cluster topologies (full mesh, round robin, p2p, master-worker).
Extensions are numerous, an example is benchmarking various topologies for different means.

## Running Unit Tests
```
cmake -B build
cmake --build build
ctest --test-dir build
```
