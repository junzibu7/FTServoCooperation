# <!-- <launch>
#     <group ns="servogroup12">
#     <node pkg="ftservocontrol" type="singleServoControl" name="singleServoControl" output="screen" >
#         <param name="id_up" type="int" value="2" />
#         <param name="id_down" type="int" value="1" />
#         <param name="source_frame" type="string" value="EstimationfromcamA" />
#         <param name="target_frame" type="string" value="camA" />
#         <param name="cam" type="string" value="camA" />
#         <param name="serial" type="string" value="/dev/ttyUSB0" />
#     </node>
#     </group>
# </launch> -->

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ftservocontrol',
            executable='Multi_Servogp_Control',
            name='ServoGroup12',
            output='screen',
            parameters=[{
                'id_up': 2,
                'id_down': 1,
                'source_frame': 'EstimationfromcamA',
                'target_frame': 'camA',
                'cam': 'camA',
                'serial': '/dev/ttyUSB0'
            }]
        )
    ])
