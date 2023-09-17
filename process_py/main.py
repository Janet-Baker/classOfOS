class PCB:
    def __init__(self, process_name, arrival_time, service_time):
        self.process_name = process_name
        self.arrival_time = arrival_time
        self.service_time = service_time
        self.process_status = "ready"


def fcfs_scheduling(process_list):
    # 按照到达时间对进程进行排序
    process_list.sort(key=lambda x: x.arrival_time)

    current_time = 0

    for process in process_list:
        if current_time < process.arrival_time:
            current_time = process.arrival_time

        waiting_time = current_time - process.arrival_time
        turnaround_time = waiting_time + process.service_time

        print(f"进程名: {process.process_name}，等待时间: {waiting_time}，周转时间: {turnaround_time}")

        current_time += process.service_time
    print("-" * 20)

def sjf_scheduling(process_list):
    # 按照到达时间对进程进行排序
    process_list.sort(key=lambda x: x.arrival_time)

    current_time = 0
    total_processes = len(process_list)
    completed_processes = 0

    while completed_processes < total_processes:
        eligible_processes = [process for process in process_list if
                              process.arrival_time <= current_time and process.process_status == "ready"]

        if len(eligible_processes) > 0:
            # 按照服务时间对可运行进程进行排序
            eligible_processes.sort(key=lambda x: x.service_time)

            process = eligible_processes[0]  # 选择服务时间最短的进程
            process.process_status = "running"

            waiting_time = current_time - process.arrival_time
            turnaround_time = waiting_time + process.service_time

            print(f"进程名: {process.process_name}，等待时间: {waiting_time}，周转时间: {turnaround_time}")

            current_time += process.service_time
            process.process_status = "completed"
            completed_processes += 1
        else:
            current_time += 1


# 创建进程列表
processes = [
    PCB("进程1", 0, 3),
    PCB("进程2", 3, 5),
    PCB("进程3", 4, 4),
    PCB("进程4", 7, 7),
    PCB("进程5", 8, 2)
]

print("先来先服务调度算法示例结果：")
fcfs_scheduling(processes)

print("短作业优先调度算法示例结果：")
sjf_scheduling(processes)