# <!-- <launch>
#     <group ns="servogroup12">
#     <node pkg="ftservoControl" type="singleServoControl" name="singleServoControl" output="screen" >
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
            package='ftservoControl',
            executable='singleServoControl',
            name='singleServoControl',
            output='screen',
            parameters=[{
                'id_up': 4,
                'id_down': 3,
                'source_frame': 'EstimationfromcamB',
                'target_frame': 'camB',
                'cam': 'camB',
                'serial': '/dev/ttyUSB1'
            }]
        )
    ])
