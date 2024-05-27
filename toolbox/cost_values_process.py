import ament_index_python
import matplotlib.pyplot as plt
import numpy as np

def main():
    # 获取当前包的共享目录路径
    package_share_directory = ament_index_python.get_package_share_directory('ftservocontrol')
    cost_values_file = package_share_directory + '/data/cost_values.txt'

    # 读取文件中的数据
    cost_values = []
    with open(cost_values_file, 'r') as f:
        lines = f.readlines()
        for line in lines:
            cost_values.append(float(line.strip()))

    mean_value = sum(cost_values[80*33:]) / len(cost_values[80*33:])

    for i in range(len(cost_values)):
        cost_values[i] = cost_values[i] / mean_value
        if cost_values[i] > 4.5:
            cost_values[i] = 4.5

    time = [0] * len(cost_values)
    for j in range(len(cost_values)):
        time[j] = j / 33

    # 创建图形
    plt.figure()

    # 绘制线图
    plt.subplot(2, 1, 1)
    plt.plot(time, cost_values, label='Line 1', color='red', linestyle='-', linewidth=1)
    plt.axvline(x=10, color='blue', linestyle='--', linewidth=1)
    plt.axvline(x=20, color='blue', linestyle='--', linewidth=1)
    plt.axvline(x=25, color='blue', linestyle='--', linewidth=1)
    plt.axvline(x=80, color='blue', linestyle='--', linewidth=1)
    plt.subplot(2, 1, 2)
    plt.plot(time[90*33:], cost_values[90*33:], label='Line 1', color='red', linestyle='-', linewidth=1)

    # 添加标题和标签
    plt.title('Cost Values Analysis')
    plt.xlabel('Time')
    plt.ylabel('Cost Values / Mean Value')

    # 显示图例
    plt.legend()

    # 显示图形
    plt.show()

if __name__ == '__main__':
    main()