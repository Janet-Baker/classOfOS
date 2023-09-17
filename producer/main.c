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
    printf("������%d������1���ź���\n", i);
}

void *consumer (void* arg) {
    int i = *(int *)arg;
    sem_wait(&mutex);
    delay(i+1);
    printf("������%d������1���ź���\n", i);
}


int main (int argc, char **argv) {
    srand(time(NULL));
    // �����߳�
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
    // �ź�����ʼ��
    sem_init(&mutex, 0, 0);

    //�����߳�
    for (int i=0; i<N; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i=0; i<N; i++) {
        pthread_join(consumers[i], NULL);
    }

    // �����ź���
    sem_destroy(&mutex);

    return 0;
}