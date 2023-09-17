#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PCB {
    char process_name[20];
    int arrival_time;
    int service_time;
    char process_status[10];
};

void fcfs_scheduling(struct PCB *process_list, int num_processes) {
    int current_time = 0;

    for (int i = 0; i < num_processes; i++) {
        struct PCB process = process_list[i];

        if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }

        int waiting_time = current_time - process.arrival_time;
        int turnaround_time = waiting_time + process.service_time;

        printf("������: %s\n", process.process_name);
        printf("�ȴ�ʱ��: %d\n", waiting_time);
        printf("��תʱ��: %d\n", turnaround_time);
        printf("-----------------\n");

        current_time += process.service_time;
    }
}

void sjf_scheduling(struct PCB *process_list, int num_processes) {
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < num_processes) {
        int eligible_index = -1;
        int shortest_service_time = 99999;

        for (int i = 0; i < num_processes; i++) {
            struct PCB process = process_list[i];

            if (process.arrival_time <= current_time && strcmp(process.process_status, "ready") == 0) {
                if (process.service_time < shortest_service_time) {
                    shortest_service_time = process.service_time;
                    eligible_index = i;
                }
            }
        }

        if (eligible_index != -1) {
            struct PCB *process = &process_list[eligible_index];

            int waiting_time = current_time - process->arrival_time;
            int turnaround_time = waiting_time + process->service_time;

            printf("������: %s\n", process->process_name);
            printf("�ȴ�ʱ��: %d\n", waiting_time);
            printf("��תʱ��: %d\n", turnaround_time);
            printf("-----------------\n");

            current_time += process->service_time;
            strcpy(process->process_status, "completed");
            completed_processes++;
        } else {
            current_time++;
        }
    }
}

int main() {
    // ���������б�
    int num_processes = 5;
    struct PCB processes[] = {
            {"����1", 0, 3, "ready"},
            {"����2", 3, 5, "ready"},
            {"����3", 4, 4, "ready"},
            {"����4", 7, 7, "ready"},
            {"����5", 8, 2, "ready"}
    };

    printf("�����ȷ�������㷨ʾ�������\n");
    fcfs_scheduling(processes, num_processes);

    printf("����ҵ���ȵ����㷨ʾ�������\n");
    sjf_scheduling(processes, num_processes);

    return 0;
}