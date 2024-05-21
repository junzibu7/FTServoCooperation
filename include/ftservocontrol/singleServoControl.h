#ifndef SINGLESERVOCONTROL_H
#define SINGLESERVOCONTROL_H

#include <ftservocontrol/FEETECHservo.h>
#include <ftservocontrol/math_tools.h>
#include <math.h>
#include <yaml-cpp/yaml.h>

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

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>
#include <cv_bridge/cv_bridge.h>

#include <cstdlib>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <queue>
#include <vector>
#include <chrono>
#include <sstream>

#include <msgs/msg/landmark.hpp>
#include <msgs/msg/loss.hpp>
#include <msgs/msg/servocommand.hpp>


using namespace std::chrono_literals;
using namespace std;

// #define SERVO_ENABLE true

class SingleServoNode: public rclcpp::Node
{
public:
	//Basic Parameters
	string source_frame, target_frame, cam;
	string serial_str;
	std::shared_ptr<rclcpp::Node> nh;
	std::string camera_config_file;

	//Servo Parameters
	ftServo _servo;
	int id_up, id_down;
	const double up_status_init = 180.0;
	const double down_status_init = 180.0;
	const double up_status_max = 250.0;
	const double up_status_min = 100.0;
	const double down_status_max = 350.0;
	const double down_status_min = 10.0;
	double up_status = up_status_init;
	double down_status = down_status_init;
	double target_up_status = up_status_init;
	double target_down_status = down_status_init;
	double down_change = 0;
	double up_change = 0;
	double target_down_change = 0;
	double target_up_change = 0;
	int up_init = 180;
	int down_init =180;
	bool force_flag = false;

	//Target Parameters
	double estimation_t_x = 1;
	double estimation_t_y = 1;
	double estimation_t_z = 1;
	double estimation_distance = 0;
	double target_t_x = 0;
	double target_t_y = 0;
	double target_t_z = 0;
    cv::Point2f target_status = cv::Point2f(0, 0);
	Eigen::Vector2d target_loss;
	msgs::msg::Loss target_loss_msg;
	vector<cv::Point3f> target_point;
	vector<cv::Point2f> image_point;

	//Camera Parameters
	double fx, fy, cx, cy;
	cv::Mat camera_matrix;
	cv::Mat distortion_coefficients;
	double DepthofField_x = 1.0;
	double DepthofField_y = 1.0;

	//Servo Transforms
	Eigen::Matrix4Xd T_DU = Eigen::Matrix4d::Identity();
	Eigen::Matrix4Xd T_UB = Eigen::Matrix4d::Identity();
	Eigen::Matrix4Xd T_BC = Eigen::Matrix4d::Identity();
	Eigen::Matrix4Xd T_servogroup_to_cam = Eigen::Matrix4d::Identity();
	Eigen::Matrix4Xd T_cam_to_coopestimation = Eigen::Matrix4d::Identity();
	Eigen::Matrix4Xd T_cam_to_estimation = Eigen::Matrix4d::Identity();

	//Publishers and Subscribers
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<geometry_msgs::msg::TransformStamped>::SharedPtr pub_servogroup_to_cam;
	rclcpp::Publisher<msgs::msg::Loss>::SharedPtr pub_target_loss;
	rclcpp::Subscription<geometry_msgs::msg::TransformStamped>::SharedPtr sub_cam_to_estimation;
	rclcpp::Subscription<geometry_msgs::msg::TransformStamped>::SharedPtr sub_cam_to_coopestimation;
	rclcpp::Subscription<geometry_msgs::msg::TransformStamped>::SharedPtr sub_trajectory;
	rclcpp::Subscription<msgs::msg::Landmark>::SharedPtr sub_irlandmark;
	rclcpp::Subscription<msgs::msg::Servocommand>::SharedPtr sub_ServoCommand;

	//tf
	std::shared_ptr<tf2_ros::TransformBroadcaster> servogroup_to_cam;
	tf2::Stamped<tf2::Transform> cam_to_estimation;
	tf2::Stamped<tf2::Transform> cam_to_coopestimation;
	geometry_msgs::msg::TransformStamped msg_servogroup_to_cam;
	std::shared_ptr<tf2_ros::Buffer> tf_target_estimation_buffer;
	std::shared_ptr<tf2_ros::TransformListener> tf_target_estimation_listener;
	int count_; // 计数器，用于控制查询的频率

//================================== function declarations ==================================//
	SingleServoNode(const std::string &node_name);

	/*
	* @brief: This function initializes the servo
	* @param: nh: the node handle
	*/
	void init(std::shared_ptr<rclcpp::Node> nh_);

	/*
	* @brief: This function moves the servo to the target position
	* @param: target_down_status: the target position of the down servo
	* @param: target_up_status: the target position of the up servo
	*/
	void servo_move(double target_down_status, double target_up_status);

	/*
	* @brief: This function calculates the transformation matrix from the servo group to the camera
	*/
	void T_servogroup_to_camera();

	/*
	* @brief: This function is the callback function for the camera to estimation subscriber
	* @param: msg: the message received from the camera to estimation subscriber
	*/
	void T_cam_to_estimation_callback(const geometry_msgs::msg::TransformStamped::SharedPtr msg);

	/*
	* @brief: This function is the callback function for the camera to coop estimation subscriber
	* @param: msg: the message received from the camera to coop estimation subscriber
	*/
	void T_cam_to_coopestimation_callback(const geometry_msgs::msg::TransformStamped::SharedPtr msg);


	/*
	* @brief: This function is the callback function for the irlandmark subscriber
	* @param: msg: the message received from the target centre subscriber
	*/
	void target_status_callback(const msgs::msg::Landmark::SharedPtr msg);

	/*
	* @brief: This function calculates the target loss
	* @param: target_status: the target center
	* @return: the target loss
	*/
	Eigen::Vector2d target_status2loss(cv::Point2f target_status);
	cv::Point2d target_loss2status(double loss_x, double loss_y, bool force_flag);

	void target_estimation2status();

	/*
	* 
	*/
	Eigen::Vector2d target_status2change(cv::Point2d target_image_pos);

	/*
	* @brief: This function is the callback function for the servo command subscriber
	* @param: msg: the message received from the servo command subscriber
	*/
	void servo_command_callback(const msgs::msg::Servocommand::SharedPtr msg);

	/*
	* @brief: This function loads the camera configuration
	* @param: config_path: the path of the camera configuration file
	*/
	void loadCameraConfig(const std::string& config_path);

	void find_transform(const std::string& from_frame, const std::string& to_frame);
};

#endif // SINGLESERVOCONTROL_H
