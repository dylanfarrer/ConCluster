#!/bin/bash

# simple shell script to run test suite in a docker container
# requires docker to be installed, and to be runnable by the user.
# assumes concluster is the image name - WILL REMOVE IT IF PRESENT.
# usage: ./docker_test_suite.sh
# options:
#   -d, --debug     Enable debug mode (opens container shell)
#   -h, --help      Display this help message

display_help() {
    echo "Usage: $0 [OPTIONS]"
    echo "Options:"
    echo "  -d, --debug     Enable debug mode"
    echo "  -h, --help      Display this help message"
    exit 0
}

# parse commands
while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        -d|--debug)
            DEBUG=true
            printf "\n\nDebug mode...\n"
            shift
            ;;
        -h|--help)
            display_help
            ;;
        *)
            # Unknown option
            echo "Unknown option: $key"
            display_help
            ;;
    esac
done



printf "\n\nStarting Docker concluster test suite...\n"

if ! docker info &>/dev/null; then
    printf "\n\nDocker is not available. Exiting...\n"
    exit 1
fi

# cleanup old processes/images
printf "\n\nRemoving old concluster processes and image...\n"
containers_to_stop_and_remove=$(docker ps -a -q --filter "ancestor=concluster")

if [ -n "$containers_to_stop_and_remove" ]; then
    docker stop $containers_to_stop_and_remove
    docker rm $containers_to_stop_and_remove
fi

if ! docker images -q concluster &>/dev/null; then
    docker rmi concluster
fi

# build new image
printf "\n\nBuilding new image...\n"
docker build -t concluster .

if [ "$DEBUG" = true ]; then
    printf "\n\nEntering container...\n"
    docker run --rm -it concluster /bin/sh
else
    # run test suite
    printf "\n\nRunning test suite...\n"
    docker run --rm concluster
fi

# cleanup
printf "\n\nRemoving image...\n"
docker rmi concluster

printf "\n\nDone.\n"
