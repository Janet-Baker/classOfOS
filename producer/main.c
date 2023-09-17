#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t mutex;
void delay (int len) {
    int i = rand() % len;
    int x;
    while (i > 0) {
        x = rand() % len;
        while (x > 0) {
            x--;
        }
        i--;
    }
}

void *producer (void* arg) {
    int i = *(int *)arg;
    sem_post(&mutex);
    printf("生产者%d生产了1个信号量\n", i);
}

void *consumer (void* arg) {
    int i = *(int *)arg;
    sem_wait(&mutex);
    delay(i+1);
    printf("消费者%d消费了1个信号量\n", i);
}


int main (int argc, char **argv) {
    srand(time(NULL));
    // 创建线程
    pthread_t producers[N];
    pthread_t consumers[N];
    int count[N];
    for (int i=0; i<N; i++) {
        count[i] = i;
    }
    for (int i=0; i<N; i++) {
        pthread_create(&producers[i], NULL, producer, &count[i]);
    }
    for (int i=0; i<N; i++) {
        pthread_create(&consumers[i], NULL, consumer, &count[i]);
    }
    // 信号量初始化
    sem_init(&mutex, 0, 0);

    //挂起线程
    for (int i=0; i<N; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i=0; i<N; i++) {
        pthread_join(consumers[i], NULL);
    }

    // 销毁信号量
    sem_destroy(&mutex);

    return 0;
}