class Block:
    def __init__(self, page, time):
        self.page = page  # 页号
        self.time = time  # 时间戳

    def update_time(self, new_time):
        self.time = new_time  # 更新时间戳

    def compare_time(self, other):
        return self.time < other.time  # 比较时间戳，如果小于则返回True，否则返回False


def LRU(pages, n):
    blocks = []  # 物理块列表
    faults = 0  # 缺页次数
    process = []  # 页面分配过程
    time = 0  # 当前时间

    for page in pages:  # 遍历页面走向
        time += 1  # 时间增加1
        found = False  # 标记是否找到相同的页号
        for block in blocks:  # 遍历物理块列表
            if block.page == page:  # 如果找到相同的页号
                found = True  # 标记为True
                block.update_time(time)  # 更新该物理块的时间戳
                break  # 跳出循环
        if not found:  # 如果没有找到相同的页号
            faults += 1  # 缺页次数增加1
            if len(blocks) < n:  # 如果物理块列表还有空位
                blocks.append(Block(page, time))  # 直接添加新的物理块
            else:  # 如果物理块列表已满
                min_block = blocks[0]  # 找到最近最少使用的物理块，初始为第一个
                for block in blocks[1:]:  # 遍历剩余的物理块
                    if block.compare_time(min_block):  # 如果比当前的最近最少使用的物理块更旧
                        min_block = block  # 更新最近最少使用的物理块
                min_block.page = page  # 用新的页号替换最近最少使用的物理块的页号
                min_block.update_time(time)  # 更新该物理块的时间戳
        process.append([block.page for block in blocks])  # 将当前的物理块列表添加到页面分配过程中
    return faults, process  # 返回缺页次数和页面分配过程


# 按间距中的绿色按钮以运行脚本。
if __name__ == '__main__':
    pages = [1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5]  # 页面走向列表
    n = 3  # 物理块数量

    faults, process = LRU(pages, n)  # 调用函数

    print("缺页次数:", faults)  # 打印缺页次数
    print("缺页率:", faults / len(pages))  # 打印缺页率

    print("详细页面分配过程:")
    for i in range(len(process)):  # 遍历页面分配过程
        print("访问页面", pages[i], "时:", process[i])  # 打印每一步的物理块列表
