#ifndef MULTISERVOCONTROL_H
#define MULTISERVOCONTROL_H

#include <ftservocontrol/singleServoControl.h>

using namespace std::chrono_literals;
using namespace std;

class MultiServoNode: public rclcpp::Node
{
public:
	//Basic Parameters
	

	//Servo Parameters
	

	//Target Parameters
	Eigen::Vector2d target_loss_camA;
	Eigen::Vector2d target_loss_camB;
	Eigen::Vector2d target_loss_camC;
	Eigen::Vector2d target_loss_camD;
	

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

	
};

#endif // MULTISERVOCONTROL_H
