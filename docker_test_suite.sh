#!/bin/bash

# simple shell script to run test suite in a docker container
# requires docker to be installed, and to be runnable by the user.
# assumes concluster is the image name - WILL REMOVE IT IF PRESENT.
# usage: ./docker_test_suite.sh

printf "\n\nStarting Docker concluster test suite...\n"

if ! docker info &>/dev/null; then
    pritnf "\n\nDocker is not available. Exiting...\n"
    exit 1
fi

# cleanup old processes/images
printf "\n\nRemoving old concluster processes and image...\n"
containers_to_stop_and_remove=$(docker ps -a -q --filter "ancestor=concluster")

if [ -n "$containers_to_stop_and_remove" ]; then
    docker stop $containers_to_stop_and_remove
    docker rm $containers_to_stop_and_remove
fi

if docker images -q concluster &>/dev/null; then
    docker rmi concluster
fi

# build new image
printf "\n\nBuilding new image...\n"
docker build -t concluster .

# run test suite
printf "\n\nRunning test suite...\n"
docker run --rm concluster

printf "\n\nRemoving image...\n"
docker rmi concluster

printf "\n\nDone.\n"
