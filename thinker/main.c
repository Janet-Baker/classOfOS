#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t chopsticks[N];//����N���ź�������N�ֲ�ͬ���͵���Դ��ÿһ����1��,����������⣬��Ϊÿ����ѧ����Ҫ����Դ��ͬ
sem_t m;//���������m(N-1)����ѧ��ͬʱ���������


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

void *philosopher (void* arg) {
    int i = *(int *)arg;
    int left = i;//����ӵı�ź���ѧ�ҵı����ͬ
    int right = (i + 1) % N;//�ҿ��ӵı��Ϊ��ѧ�ұ��+1
    /*while (1)*/ {
        printf("��ѧ��%d����˼������\n", i);
        delay(60000);

        printf("��ѧ��%d����\n", i);
        sem_wait(&m);//���ǰ4����ѧ��ͬʱ��������ӣ����������ͬʱ��������ӣ���֤������һλ��ѧ���ܳԵ��������������״̬����
        sem_wait(&chopsticks[left]);//��ʱ�����ѧ������ӵ��ź���-1֮��>=0ʱ����ʾ�ܼ���ִ�С�
        printf("��ѧ��%d������%d�ſ���,����ֻ��һ֧����,���ܽ���\n", i, left);
        sem_wait(&chopsticks[right]);
        printf("��ѧ��%d������%d�ſ���, ��������֧����,��ʼ����\n", i, right);
        delay(60000);
        sem_post(&chopsticks[left]);
        printf("��ѧ��%d������%d�ſ���\n", i, left);
        sem_post(&m);//����ѧ���ͷ��������ʱ���ź���m+1
        sem_post(&chopsticks[right]);
        printf("��ѧ��%d������%d�ſ���\n", i, right);

    }
}

int main (int argc, char **argv) {
    srand(time(NULL));
    pthread_t philo[N];

    //�ź�����ʼ��
    for (int i=0; i<N; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }
    sem_init(&m, 0, 4);
    int philosophers[N];//������ѧ�ҵı��
    for (int i=0; i<N; i++) {
        philosophers[i] = i;
    }

    //�����߳�
    for (int i=0; i<N; i++) {
        pthread_create(&philo[i], NULL, philosopher, &philosophers[i]);
    }

    //�����߳�
    for (int i=0; i<N; i++) {
        pthread_join(philo[i], NULL);
    }

    //�����ź���
    for (int i=0; i<N; i++) {
        sem_destroy(&chopsticks[i]);
    }
    sem_destroy(&m);

    return 0;
}