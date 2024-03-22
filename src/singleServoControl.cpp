#include <ftservoControl/FEETECHservo.h>
#include <math.h>

#include <tf/transform_broadcaster.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PointStamped.h>


double x, y, z;
using namespace std;



bool flag;
int id_up;
int id_down;
int up_status = 180;
int down_status = 180;
const int pi = 3.1415926;

void T_body_to_drone_Callback(const geometry_msgs::PoseStamped msg_T_body_to_drone)
{
    
	
	x = msg_T_body_to_drone.pose.position.x;
	y = msg_T_body_to_drone.pose.position.y;
	z = msg_T_body_to_drone.pose.position.z;
	std::cout <<"(T_body_to_drone)  x:"<< x <<"y:"<< y <<"z:"<< z << std::endl;
	flag = true;

	
	
	
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "control");
	ros::NodeHandle nh;
	nh.param<int>("control/id_up", id_up, 2);
    nh.param<int>("control/id_down", id_down, 1);
	ftServo _servo;
	char* serial_ = "/dev/ttyUSB0";
	tf::TransformBroadcaster br;
	
	
	_servo.init(serial_, 2, nh,{id_down, id_up});
	_servo.move(down_status,id_down);
	_servo.move(up_status,id_up);
	tf::Transform T_servogroup_to_drone;
	std::cout<<"system has been initialed!"<<std::endl;
	ros::Subscriber sub = nh.subscribe<geometry_msgs::PoseStamped>("/kun0/multi_camera_cooperation_ros/mulcam_pnp/T_camera_to_drone", 1, T_body_to_drone_Callback);

	while (1)
	{
		if(flag == true){
			down_status = - atan(y/x) / pi * 180 + down_status;
			down_status = min(max(down_status, 50), 310);
			_servo.move(down_status,id_down);
			std::cout<<"down moving angle:"<<down_status<<std::endl;

			up_status = atan(z/sqrt(x*x+y*y)) / pi * 180 / 2 + up_status;
			up_status = min(max(up_status, 100), 260);
			_servo.move(up_status,id_up);	
			std::cout<<"up moving angle:"<<up_status<<std::endl;

			T_servogroup_to_drone.setOrigin(tf::Vector3(0, 0, 0.0));
			tf::Quaternion q;
    		q.setRPY(0, 0, 0);
			T_servogroup_to_drone.setRotation(q);
			br.sendTransform(tf::StampedTransform(T_servogroup_to_drone, ros::Time::now(), "servogroup"+to_string(id_down)+to_string(id_up), "camera"));

			flag = false;
		}
		ros::Duration(1.0).sleep();
		ros::spinOnce();
	}


	ros::Duration(1.0).sleep();


	
	return 0;
}