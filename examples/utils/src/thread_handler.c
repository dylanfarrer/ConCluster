#include "thread_handler.h"

#include <stdlib.h>
#include <stdio.h>

pthread_t* run_thread(const pthread_attr_t* attr,
                      void *(*start_routine)(void *),
                      void* arg) {
    
    pthread_t* thread = malloc(sizeof(pthread_t));
    if (thread == NULL) {
        printf("Failed to allocate memory for thread.\n");
        return NULL;
    }

    if (pthread_create(thread, attr, start_routine, arg) != 0) {
        printf("Failed to create thread.\n");
        free(thread);
        return NULL;
    }

    return thread;
}

int join_thread(pthread_t* thread, void** retval) {
    if (thread == NULL) {
        return 0;
    }
    if (pthread_join(*thread, retval) != 0) {
        printf("Failed to join thread.\n");
        free(thread);
        return -1;
    }

    free(thread);
    return 0;
}
