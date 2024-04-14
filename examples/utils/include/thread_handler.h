#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H

#include <pthread.h>

/**
 * @brief Utility function for creating a thread.
 * 
 * @param attr 
 * @param start_routine 
 * @param arg 
 * @return pthread_t* created thread or NULL
 */
pthread_t* run_thread(const pthread_attr_t* attr,
                      void *(*start_routine)(void *),
                      void* arg);

/**
 * @brief Utility function for joining a thread. Frees the thread pointer.
 * 
 * @param thread 
 * @param retval 
 * @return int 0 on success, -1 otherwise.
 */
int join_thread(pthread_t* thread, void** retval);

#endif
