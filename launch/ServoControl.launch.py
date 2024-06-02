from launch import LaunchDescription
import launch
from launch_ros.actions import Node
import launch_ros.actions
from ament_index_python.packages import get_package_share_directory
import os
import yaml

def generate_launch_description():
    # 创建启动器描述
    ld = LaunchDescription()

    camera_config_file = os.path.join(get_package_share_directory('ftservocontrol'), 'config', 'four_camera.yaml')

    # 为节点ServoGroup12设置参数
    servo_group_12_params = {
        'id_up': 2,
        'id_down': 1,
        'source_frame': 'camA',
        'target_frame': 'target',
        'cam': 'camA',
        'serial': '/dev/serial_servogroup12',
        'up_init': 155,
        'down_init': 180,
        'camera_config_file': camera_config_file
    }
    
    # 为节点ServoGroup34设置参数
    servo_group_34_params = {
        'id_up': 4,
        'id_down': 3,
        'source_frame': 'camB',
        'target_frame': 'target',
        'cam': 'camB',
        'serial': '/dev/serial_servogroup34',
        'up_init': 180,
        'down_init': 180,
        'camera_config_file': camera_config_file
    }

    # 为节点ServoGroup56设置参数
    servo_group_56_params = {
        'id_up': 6,
        'id_down': 5,
        'source_frame': 'camC',
        'target_frame': 'target',
        'cam': 'camC',
        'serial': '/dev/serial_servogroup56',
        'up_init': 180,
        'down_init': 180,
        'camera_config_file': camera_config_file
    }

    # 为节点ServoGroup78设置参数
    servo_group_78_params = {
        'id_up': 8,
        'id_down': 7,
        'source_frame': 'camD',
        'target_frame': 'target',
        'cam': 'camD',
        'serial': '/dev/serial_servogroup78',
        'up_init': 180,
        'down_init': 180,
        'camera_config_file': camera_config_file
    }

    # 添加第一个节点并设置参数
    servo_group_12 = launch_ros.actions.Node(
        package='ftservocontrol',
        executable='Single_Servogp_Control',
        name='ServoGroup12',
        output='screen',
        parameters=[servo_group_12_params]
    )
    ld.add_action(servo_group_12)

    # 添加第二个节点并设置参数
    servo_group_34 = launch_ros.actions.Node(
        package='ftservocontrol',
        executable='Single_Servogp_Control',
        name='ServoGroup34',
        output='screen',
        parameters=[servo_group_34_params]
    )
    ld.add_action(servo_group_34)

    # 添加第三个节点并设置参数
    servo_group_56 = launch_ros.actions.Node(
        package='ftservocontrol',
        executable='Single_Servogp_Control',
        name='ServoGroup56',
        output='screen',
        parameters=[servo_group_56_params]
    )
    ld.add_action(servo_group_56)

    # 添加第四个节点并设置参数
    servo_group_78 = launch_ros.actions.Node(
        package='ftservocontrol',
        executable='Single_Servogp_Control',
        name='ServoGroup78',
        output='screen',
        parameters=[servo_group_78_params]
    )
    ld.add_action(servo_group_78)

    # # 构建base到servogroupxx的tf树
    # base_to_servogroupxx = Node(
    #     package='ftservocontrol',
    #     executable='base2servogroup',
    #     name='base2servogroup_node',
    # )
    # ld.add_action(base_to_servogroupxx)

    # # 模拟目标轨迹
    # Target_Trajectory_Simulation = Node(
    #     package='ftservocontrol',
    #     executable='Target_Trajectory_Simulation',
    #     name='trajectory_node',
    # )
    # ld.add_action(Target_Trajectory_Simulation)

    # # 多相机协同跟踪
    # Multi_Servogp_Control = Node(
    #     package='ftservocontrol',
    #     executable='Multi_Servogp_Control',
    #     name='MultiServogpControl',
    #     output='screen',
    # )
    # ld.add_action(Multi_Servogp_Control)

    # # 启动rviz2
    # rviz = Node(
    #     package='rviz2',
    #     executable='rviz2',
    #     name='rviz2',
    #     arguments=['-d', os.path.join(get_package_share_directory('ftservocontrol'), 'rviz', 'servocontrol.rviz')],
    #     output='screen'
    # )
    # ld.add_action(rviz)

    # 返回启动器描述
    return ld
