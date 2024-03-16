#include <ftservoControl/FEETECHservo.h>
#include <math.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PointStamped.h>

double x, y, z;


bool flag;
int id_up;
int id_down;
int up_initial;

void Callback(const geometry_msgs::PoseStamped msg_T_body_to_drone)
{
    
	
	x = msg_T_body_to_drone.pose.position.x;
	y = msg_T_body_to_drone.pose.position.y;
	z = msg_T_body_to_drone.pose.position.z;
	std::cout <<"x:"<<x<<"y:"<<y<<"z:"<<z<<std::endl;
	flag = true;

	
	
	
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "control");
	ros::NodeHandle nh;
	nh.param<int>("control/id_up", id_up, 2);
    nh.param<int>("control/id_down", id_down, 1);
    nh.param<int>("control/up_initial", up_initial, 180);
	ftServo _servo;
	char* serial_ = "/dev/ttyUSB0";
	
	
	_servo.init(serial_, 2, nh,{id_down, id_up});
	std::cout<<"servo has been initialed!"<<std::endl;
	while (1)
	{
		ros::Subscriber sub = nh.subscribe<geometry_msgs::PoseStamped>("/kun0/multi_camera_cooperation_ros/mulcam_pnp/T_camera_to_drone", 1, Callback);
		if(flag == true){
			double angle1 = - atan(y/x) * 180 / 5 + 180;
			_servo.move(angle1,1);
			std::cout<<"1 moving angle:"<<angle1<<std::endl;

			double angle2 = atan(z/sqrt(x*x+y*y)) * 180 / 10 + 180;
			_servo.move(angle2,2);	
			std::cout<<"2 moving angle:"<<angle2<<std::endl;
			flag = false;
		}
		ros::Duration(1.0).sleep();
		ros::spinOnce();
	}


	ros::Duration(1.0).sleep();


	
	return 0;
}