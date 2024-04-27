# <!-- <launch>
#     <arg name="modified_id" default="1"/> 
#     <arg name="port" default="/dev/ttyUSB0"/>

#     <node pkg="ftservoControl" type="initialize" name="initialize" output="screen" >
#         <param name="ftservo/id" value="$(arg modified_id)"/>
#         <param name="ftservo/serial" value="$(arg port)"/>
#     </node>
# </launch> -->

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='ftservoControl',
            executable='initialize',
            name='initialize',
            output='screen',
            parameters=[{
                'ftservo': {
                    'id': 1,
                    'serial': '/dev/ttyUSB0'
                }
            }]
        )
    ])
