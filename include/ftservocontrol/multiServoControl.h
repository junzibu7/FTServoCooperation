#ifndef MULTISERVOCONTROL_H
#define MULTISERVOCONTROL_H

#include <ftservocontrol/singleServoControl.h>

using namespace std::chrono_literals;
using namespace std;

class MultiServoNode: public rclcpp::Node
{
public:
	//Basic Parameters
	Eigen::Matrix<double,4,4> K = Eigen::Matrix<double,4,4>::Identity();
	Eigen::Matrix<double,4,4> S = Eigen::Matrix<double,4,4>::Identity();
	Eigen::Matrix<double,4,4> Q = Eigen::Matrix<double,4,4>::Identity();
	Eigen::Matrix<double,4,4> R = Eigen::Matrix<double,4,4>::Identity();
	Eigen::Matrix<double,4,4> H = Eigen::Matrix<double,4,4>::Identity();
	Eigen::Matrix<double,4,4> iter_A = Eigen::Matrix<double,4,4>::Identity();
	Eigen::Matrix<double,4,4> iter_B = Eigen::Matrix<double,4,4>::Identity();

	//Servo Parameters
	Eigen::Vector2d servo12_control;
	Eigen::Vector2d servo34_control;
	Eigen::Vector2d servo56_control;
	Eigen::Vector2d servo78_control;
	Eigen::Vector2d servo12_velcity;
	Eigen::Vector2d servo34_velcity;
	Eigen::Vector2d servo56_velcity;
	Eigen::Vector2d servo78_velcity;
	double s_vel = 1000;
	Eigen::Matrix<double,4,1> servo_cur = Eigen::Matrix<double,4,1>::Zero();
	Eigen::Matrix<double,4,1> servo_vel = Eigen::Matrix<double,4,1>::Zero();

	//Target Parameters
	Eigen::Vector2d target_loss_camA;
	Eigen::Vector2d target_loss_camB;
	Eigen::Vector2d target_loss_camC;
	Eigen::Vector2d target_loss_camD;
	Eigen::Matrix<double,4,1> loss_cur = Eigen::Matrix<double,4,1>::Zero();
	Eigen::Matrix<double,4,1> loss_nex = Eigen::Matrix<double,4,1>::Zero();
	

	//Servo Transforms


	//Publishers and Subscribers
	rclcpp::Subscription<msgs::msg::Loss>::SharedPtr sub_target_loss_camA;
	rclcpp::Subscription<msgs::msg::Loss>::SharedPtr sub_target_loss_camB;
	rclcpp::Subscription<msgs::msg::Loss>::SharedPtr sub_target_loss_camC;
	rclcpp::Subscription<msgs::msg::Loss>::SharedPtr sub_target_loss_camD;

	//tf
	std::shared_ptr<tf2_ros::TransformBroadcaster> servogroup_to_cam;
	tf2::Stamped<tf2::Transform> cam_to_estimation;
	tf2::Stamped<tf2::Transform> cam_to_coopestimation;
	geometry_msgs::msg::TransformStamped msg_servogroup_to_cam;

//================================== function declarations ==================================//
	MultiServoNode(const std::string &node_name);

	/*
	 * @brief Callback function for target loss of camA
	 * @param msg: target loss message
	 */
	void target_loss_camA_callback(const msgs::msg::Loss::SharedPtr msg);
	void target_loss_camB_callback(const msgs::msg::Loss::SharedPtr msg);
	void target_loss_camC_callback(const msgs::msg::Loss::SharedPtr msg);
	void target_loss_camD_callback(const msgs::msg::Loss::SharedPtr msg);

	/*
	 * @brief Calculate the control signal for the servos
	 */
	void calculate_control_signal();
	
};

#endif // MULTISERVOCONTROL_H
