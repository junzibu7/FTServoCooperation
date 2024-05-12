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
        'source_frame': 'EstimationfromcamA',
        'target_frame': 'camA',
        'cam': 'camA',
        'serial': '/dev/ttyUSB0',
        'up_init': 180,
        'down_init': 180,
    }
    
    # 为节点ServoGroup34设置参数
    servo_group_34_params = {
        'id_up': 4,
        'id_down': 3,
        'source_frame': 'EstimationfromcamB',
        'target_frame': 'camB',
        'cam': 'camB',
        'serial': '/dev/ttyUSB1',
        'up_init': 180,
        'down_init': 180,
    }

    # 为节点ServoGroup56设置参数
    servo_group_56_params = {
        'id_up': 6,
        'id_down': 5,
        'source_frame': 'EstimationfromcamC',
        'target_frame': 'camC',
        'cam': 'camC',
        'serial': '/dev/ttyUSB2',
        'up_init': 180,
        'down_init': 180,
    }

    # 为节点ServoGroup78设置参数
    servo_group_78_params = {
        'id_up': 8,
        'id_down': 7,
        'source_frame': 'EstimationfromcamD',
        'target_frame': 'camD',
        'cam': 'camD',
        'serial': '/dev/ttyUSB3',
        'up_init': 180,
        'down_init': 180,
    }

    # 添加第一个节点并设置参数
    servo_group_12 = launch_ros.actions.Node(
        package='ftservocontrol',
        executable='Single_Servogp_Control',
        name='ServoGroup12',
        output='screen',
        parameters=[servo_group_12_params, camera_config_file]
    )
    ld.add_action(servo_group_12)

    # 添加第二个节点并设置参数
    servo_group_34 = launch_ros.actions.Node(
        package='ftservocontrol',
        executable='Single_Servogp_Control',
        name='ServoGroup34',
        output='screen',
        parameters=[servo_group_34_params, camera_config_file]
    )
    ld.add_action(servo_group_34)

    # 添加第三个节点并设置参数
    servo_group_56 = launch_ros.actions.Node(
        package='ftservocontrol',
        executable='Single_Servogp_Control',
        name='ServoGroup56',
        output='screen',
        parameters=[servo_group_56_params, camera_config_file]
    )
    ld.add_action(servo_group_56)

    # 添加第四个节点并设置参数
    servo_group_78 = launch_ros.actions.Node(
        package='ftservocontrol',
        executable='Single_Servogp_Control',
        name='ServoGroup78',
        output='screen',
        parameters=[servo_group_78_params, camera_config_file]
    )
    ld.add_action(servo_group_78)

    # 返回启动器描述
    return ld
