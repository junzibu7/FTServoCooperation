from launch import LaunchDescription
import launch
from launch_ros.actions import Node
import launch_ros.actions
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # 创建启动器描述
    ld = LaunchDescription()

    # 为第一个节点ServoGroup12设置参数
    servo_group_12_params = {
        'id_up': 2,
        'id_down': 1,
        'source_frame': 'EstimationfromcamA',
        'target_frame': 'camA',
        'cam': 'camA',
        'serial': '/dev/ttyUSB0'
    }
    
    # 为第二个节点ServoGroup34设置参数
    servo_group_34_params = {
        'id_up': 4,
        'id_down': 3,
        'source_frame': 'EstimationfromcamB',
        'target_frame': 'camB',
        'cam': 'camB',
        'serial': '/dev/ttyUSB0'
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

    # 返回启动器描述
    return ld
