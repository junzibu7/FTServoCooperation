#include <ftservocontrol/FEETECHservo.h>
#include <ftservocontrol/math_tools.h>
#include <math.h>
#include <chrono>

#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_eigen/tf2_eigen.h>
#include <tf2_ros/buffer.h>

#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/quaternion_stamped.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>


double x, y, z;
using namespace std;

bool flag = false;
int id_up;
int id_down;
double up_status = 0;
double down_status = 180.0;
double down_change = 0;
double up_change = 0;
string source_frame;
string target_frame;
string cam;
string serial_str;

Eigen::Matrix4Xd T01 = Eigen::Matrix4d::Identity();
Eigen::Matrix4Xd T12 = Eigen::Matrix4d::Identity();
Eigen::Matrix4Xd T23 = Eigen::Matrix4d::Identity();
Eigen::Matrix4Xd T34 = Eigen::Matrix4d::Identity();
Eigen::Matrix4Xd T_servogroup_to_cam = Eigen::Matrix4d::Identity();
Eigen::Matrix4Xd T_cam_to_coopestimation = Eigen::Matrix4d::Identity();
Eigen::Matrix4Xd T_cam_to_estimation = Eigen::Matrix4d::Identity();

rclcpp::Publisher<geometry_msgs::msg::TransformStamped>::SharedPtr pub_servogroup_to_cam;
rclcpp::Subscription<geometry_msgs::msg::TransformStamped>::SharedPtr sub_cam_to_estimation;
rclcpp::Subscription<geometry_msgs::msg::TransformStamped>::SharedPtr sub_cam_to_coopestimation;

tf2::Stamped<tf2::Transform> servogroup_to_cam;
tf2::Stamped<tf2::Transform> cam_to_estimation;
tf2::Stamped<tf2::Transform> cam_to_coopestimation;
geometry_msgs::msg::TransformStamped msg_servogroup_to_cam;

void T_servogroup_to_camera(double id_down, double id_up){
	T01 << cos(id_down), sin(id_down), 0, 0, -sin(id_down), cos(id_down), 0, 0, 0, 0, 1, 38.3/1000, 0, 0, 0, 1;
	T12 << 1, 0, 0, 0, 0, 0, 1, 21.3 / 1000, 0, -1, 0, 39.6 / 1000, 0, 0, 0, 1;
	T23 << cos(id_up), sin(id_up), 0, 0, -sin(id_up), cos(id_up), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
	T34 << 1, 0, 0, 9.36 / 1000, 0, 0, -1, -59 / 1000, 0, 1, 0, 26 / 1000, 0, 0, 0, 1;
	Eigen::Matrix4d T_correct = Eigen::Matrix4d::Identity();
	T_servogroup_to_cam = T01 * T12 * T23 * T34;
	
}

void T_cam_to_estimation_callback(const geometry_msgs::msg::TransformStamped &msg){
	cam_to_estimation.setOrigin(tf2::Vector3(msg.transform.translation.x, msg.transform.translation.y, msg.transform.translation.z));
	cam_to_estimation.setRotation(tf2::Quaternion(msg.transform.rotation.x, msg.transform.rotation.y, msg.transform.rotation.z, msg.transform.rotation.w));
	flag = true;
}


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("singleServoControl");
    
	tf2_ros::TransformBroadcaster br(node);
	tf2_ros::Buffer tfBuffer(node->get_clock());
	tf2_ros::TransformListener tfListener(tfBuffer);
	// geometry_msgs::TransformStamped transformStamped;

	node->declare_parameter<int>("id_up", 2);
	node->declare_parameter<int>("id_down", 1);
	node->declare_parameter<std::string>("target_frame", "EstimationfromcamA");
	node->declare_parameter<std::string>("source_frame", "camA");
	node->declare_parameter<std::string>("cam", "camA");
	node->declare_parameter<std::string>("serial", "/dev/ttyUSB0");

	int id_up = node->get_parameter("id_up").as_int();
	int id_down = node->get_parameter("id_down").as_int();
	std::string target_frame = node->get_parameter("target_frame").as_string();
	std::string source_frame = node->get_parameter("source_frame").as_string();
	std::string cam = node->get_parameter("cam").as_string();
	std::string serial_str = node->get_parameter("serial").as_string();
    const char *serial_ = serial_str.c_str();

	cout << "id_up:" << id_up << endl;
	cout << "id_down:" << id_down << endl;
	cout << "serial:" << serial_ << endl;

    ftServo _servo;

    rclcpp::Rate rate(30);

    _servo.init(serial_, 2, node, {id_down, id_up});
    _servo.move(down_status, id_down);
    std::cout << "down_status:" << down_status << std::endl;
    _servo.move(up_status, id_up);
    std::cout << "up_status:" << up_status << std::endl;

    std::cout << "system has been initialized!" << std::endl;
    pub_servogroup_to_cam = node->create_publisher<geometry_msgs::msg::TransformStamped>("/T_servogroup" + std::to_string(id_down) + std::to_string(id_up) + "_to_" + cam, 1);
	auto start = std::chrono::high_resolution_clock::now();
  	
	std::cout << _servo.read(id_up) << std::endl;
	std::cout << _servo.read(id_down) << std::endl;
	
	auto end = std::chrono::high_resolution_clock::now();
	// 计算差值
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // 输出运行时间
    std::cout << "Code execution time: " << duration.count() << " milliseconds" << std::endl;

	while (rclcpp::ok())
    {
        // // Calculate the transformation from the motor group to the camera
        // T_servogroup_to_camera((down_status - 180) / 180 * pi, (up_status - 180) / 180 * pi);

        // std::cout << "T_servogroup_to_cam" << std::endl << T_servogroup_to_cam << std::endl;
        // servogroup_to_cam.setOrigin(EigenVector3dToTFVector3(T_servogroup_to_cam.block<3,1>(0,3)));
        // servogroup_to_cam.setRotation(EigenQuaterniondToTFQuaternion(Eigen::Quaterniond(T_servogroup_to_cam.block<3,3>(0,0))));
        // servogroup_to_cam.stamp_ = node->now();
        // servogroup_to_cam.frame_id_ = "servogroup" + std::to_string(id_down) + std::to_string(id_up);
        // servogroup_to_cam.child_frame_id_ = cam;
        // tf2::toMsg(servogroup_to_cam, msg_servogroup_to_cam);
        // pub_servogroup_to_cam->publish(msg_servogroup_to_cam);
        // br.sendTransform(msg_servogroup_to_cam);

		// if(flag == false)
		// 	try{
		// 		// 等待变换
		// 		lr.waitForTransform(target_frame, "CoopEstimation", ros::Time(0), ros::Duration(1.0));
		// 		// 查询坐标系关系
		// 		lr.lookupTransform(target_frame, "CoopEstimation", ros::Time(0), cam_to_estimation);

		// 		flag = true;

		// 	}
		// 	catch(tf::TransformException &ex)
		// 	{
		// 		RCLCPP_ERROR(this->get_logger(), "%s", ex.what());
		// 	}


		// if(flag){
			// x = cam_to_estimation.getOrigin().x();
			// y = cam_to_estimation.getOrigin().y();
			// z = cam_to_estimation.getOrigin().z();
			// std::cout <<"(TF_cam_to_estimation)  x:"<< x <<"y:"<< y <<"z:"<< z << std::endl;
			
			//下方舵机旋转
			// if(y <= 0)
			// {
			// 	down_change = abs( atan(y / x) / pi * 180) ;//左负右正
			// }else if(y > 0)
			// {
			// 	down_change = -abs( atan(y / x) / pi * 180) ;//左负右正
			// }
			// down_status = down_change + down_status;
			// // down_status = (abs(down_change) > 2) * down_change + down_status;
			// down_status = min(max(down_status, 50.0), 310.0);
			// _servo.move(down_status,id_down);
			// std::cout<<"down moving angle:"<<down_change<<std::endl;
			// std::cout<<"down angle:"<<down_status<<std::endl;

			// //上方舵机旋转
			// double up_change = atan(z / sqrt(x * x + y * y)) / pi * 180 / 2;//上正下负
			// up_status = up_change + up_status;
			// // up_status = (abs(up_change) > 3) * up_change + up_status;
			// up_status = min(max(up_status, 135.0), 225.0);
			// _servo.move(up_status,id_up);	
			// std::cout<<"up moving angle:"<<up_change<<std::endl;
			// std::cout<<"up angle:"<<up_status<<std::endl;
			// flag = false;
		// }
		// ros::Duration(1).sleep();
		rclcpp::spin_some(node);
		rate.sleep();

		
	}
	
	return 0;
}