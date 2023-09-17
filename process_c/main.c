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

        printf("进程名: %s\n", process.process_name);
        printf("等待时间: %d\n", waiting_time);
        printf("周转时间: %d\n", turnaround_time);
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

            printf("进程名: %s\n", process->process_name);
            printf("等待时间: %d\n", waiting_time);
            printf("周转时间: %d\n", turnaround_time);
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
    // 创建进程列表
    int num_processes = 5;
    struct PCB processes[] = {
            {"进程1", 0, 3, "ready"},
            {"进程2", 3, 5, "ready"},
            {"进程3", 4, 4, "ready"},
            {"进程4", 7, 7, "ready"},
            {"进程5", 8, 2, "ready"}
    };

    printf("先来先服务调度算法示例结果：\n");
    fcfs_scheduling(processes, num_processes);

    printf("短作业优先调度算法示例结果：\n");
    sjf_scheduling(processes, num_processes);

    return 0;
}