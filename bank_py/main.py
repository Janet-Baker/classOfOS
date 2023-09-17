# 定义四个数据结构
Available = [17, 5, 20]
Max = [[5, 5, 9], [5, 3, 6], [4, 0, 11], [4, 2, 5], [4, 2, 4]]
Allocation = [[2, 1, 2], [4, 0, 2], [4, 0, 5], [2, 0, 4], [3, 1, 4]]
Need = [[3, 4, 7], [1, 3, 4], [0, 0, 6], [2, 2, 1], [1, 1, 0]]

# 定义进程数和资源类型数
process_num = len(Max)
resource_num = len(Available)


# 定义银行家算法
def banker_algorithm(request):
    # 获取请求资源的进程编号
    process_id = request[0]
    # 判断请求是否超过最大需求
    if any(request[j + 1] > Need[process_id][j] for j in range(resource_num)):
        print("不可以分配。进程请求的资源超过了声明的最大需求")
        return False
    # 判断请求是否超过可用资源
    if any(request[j + 1] > Available[j] for j in range(resource_num)):
        print("该请求必须等待，当前没有足够的资源")
        return False
    # 尝试分配资源，并执行安全性算法
    for j in range(resource_num):
        Available[j] -= request[j + 1]
        Allocation[process_id][j] += request[j + 1]
        Need[process_id][j] -= request[j + 1]
    safe, sequence = is_safe()
    # 如果安全性算法判断系统处于安全状态，返回True
    if safe:
        print("可以分配。")
        print("一个可能的安全序列是：", end="")
        for i in sequence:
            print(f"P{i+1}", end=" ")
        print()
        return True


# 定义安全性算法
def is_safe():
    # 初始化工作向量和完成序列
    Work = Available.copy()
    Finish = [False] * process_num
    # 初始化一个空列表，用于存储安全序列
    safe_sequence = []

    # 循环寻找满足条件的进程
    while True:
        found = False  # 标记是否找到满足条件的进程
        for i in range(process_num):
            # 判断进程是否已完成，以及是否满足需求小于等于工作向量的条件
            if not Finish[i] and all(Need[i][j] <= Work[j] for j in range(resource_num)):
                # 假设将进程运行完毕，并释放其占用的资源，更新数据结构
                for j in range(resource_num):
                    Work[j] += Allocation[i][j]
                Finish[i] = True
                found = True  # 标记找到满足条件的进程
                # 将进程加入安全序列
                safe_sequence.append(i)
                break  # 跳出循环，继续寻找下一个进程
        # 如果无法找到满足条件的进程，或者所有进程都完成，结束循环
        if not found or all(Finish):
            break

    # 如果所有进程都完成，返回True和安全序列；否则，返回False和空列表
    if all(Finish):
        return True, safe_sequence
    else:
        return False, []


# 测试代码
if __name__ == "__main__":
    # 打印初始状态表格
    print("T0时刻系统状态表")
    print("\t最大资源需求量\t已分配资源数量")
    print("\tA\tB\tC\tA\tB\tC")
    for i in range(process_num):
        print(f"P{i+1}\t", end="")
        for j in range(resource_num):
            print(f"{Max[i][j]}\t", end="")
        for j in range(resource_num):
            print(f"{Allocation[i][j]}\t", end="")
        print()

    # 判断T0时刻是否为安全状态，并给出安全序列（如果存在）
    safe, sequence = is_safe()
    if safe:
        print("T0时刻为安全状态。")
        print("一个可能的安全序列是：", end="")
        for i in sequence:
            print(f"P{i+1}", end=" ")
        print()
    else:
        print("T0时刻为不安全状态。")

    # 在T0时刻若进程P2请求资源（0，3，4），判断是否能实施资源分配
    request = [2-1, 0, 3, 4]  # 进程P2请求资源（0，3，4）
    banker_algorithm(request)
