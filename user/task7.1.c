//create 5 threads

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *worker(void *arg) {
    int *message = (int *)arg;
    printf("Thread says: Hello from Thread %d\n", *message);
    return NULL;
}

int main() {
    pthread_t thread[5];
    int id[5];

    // Create threads
    for (int i = 0; i < 5; i++) {
        id[i] = i;
        pthread_create(&thread[i], NULL, worker, &id[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("Main thread finished.\n");

    return 0;
}
