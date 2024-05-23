import ament_index_python
import matplotlib.pyplot as plt

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

    # 创建图形
    plt.figure()

    # 绘制线图
    plt.plot(cost_values, label='Line 1')

    # 添加标题和标签
    plt.title('Simple Plot')
    plt.xlabel('X Axis')
    plt.ylabel('Y Axis')

    # 显示图例
    plt.legend()

    # 显示图形
    plt.show()

if __name__ == '__main__':
    main()