#ifndef MULTISERVOCONTROL_H
#define MULTISERVOCONTROL_H

#include <ftservocontrol/singleServoControl.h>
#include <fstream>
#include "ament_index_cpp/get_package_share_directory.hpp"

using namespace std::chrono_literals;
using namespace std;

class MultiServoNode: public rclcpp::Node
{
public:
	// Basic Parameters
	Eigen::Matrix<double,8,8> K = Eigen::Matrix<double,8,8>::Identity();
	Eigen::Matrix<double,8,8> S = Eigen::Matrix<double,8,8>::Identity();
	Eigen::Matrix<double,8,8> Q = Eigen::Matrix<double,8,8>::Identity();
	Eigen::Matrix<double,8,8> R = Eigen::Matrix<double,8,8>::Identity();
	Eigen::Matrix<double,8,8> H = Eigen::Matrix<double,8,8>::Identity();
	Eigen::Matrix<double,8,8> iter_A = Eigen::Matrix<double,8,8>::Identity();
	Eigen::Matrix<double,8,8> iter_B = Eigen::Matrix<double,8,8>::Identity();
	Eigen::Matrix<double,8,8> iter_B_buf = Eigen::Matrix<double,8,8>::Identity();
	Eigen::Vector4d COST_WITH_CONTROL = Eigen::Vector4d::Zero();
	Eigen::Vector4d COST_WITHOUT_CONTROL = Eigen::Vector4d::Zero();
	Eigen::Vector4d DELTA_COST = Eigen::Vector4d::Zero();

	// Servo Parameters
	double s_vel = 1000;
	Eigen::Matrix<double,8,1> servo_cur = Eigen::Matrix<double,8,1>::Zero();
	Eigen::Matrix<double,8,1> servo_vel = Eigen::Matrix<double,8,1>::Zero();
	msgs::msg::Servocommand servo12_command;
	msgs::msg::Servocommand servo34_command;
	msgs::msg::Servocommand servo56_command;
	msgs::msg::Servocommand servo78_command;
	int servo_control_num = 2;

	// Target Parameters
	bool camA_force_flag = false;
	bool camB_force_flag = false;
	bool camC_force_flag = false;
	bool camD_force_flag = false;
	Eigen::Matrix<double,8,1> loss_cur = Eigen::Matrix<double,8,1>::Zero();
	Eigen::Matrix<double,8,1> loss_nex = Eigen::Matrix<double,8,1>::Zero();
	

	// Servo Transforms

	// Publishers and Subscribers
	rclcpp::TimerBase::SharedPtr signal_timer_;
	rclcpp::TimerBase::SharedPtr evaluate_timer_;
	rclcpp::Subscription<msgs::msg::Loss>::SharedPtr sub_target_loss_camA;
	rclcpp::Subscription<msgs::msg::Loss>::SharedPtr sub_target_loss_camB;
	rclcpp::Subscription<msgs::msg::Loss>::SharedPtr sub_target_loss_camC;
	rclcpp::Subscription<msgs::msg::Loss>::SharedPtr sub_target_loss_camD;
	rclcpp::Publisher<msgs::msg::Servocommand>::SharedPtr pub_servo12_command;
	rclcpp::Publisher<msgs::msg::Servocommand>::SharedPtr pub_servo34_command;
	rclcpp::Publisher<msgs::msg::Servocommand>::SharedPtr pub_servo56_command;
	rclcpp::Publisher<msgs::msg::Servocommand>::SharedPtr pub_servo78_command;

	// tf
	std::shared_ptr<tf2_ros::TransformBroadcaster> servogroup_to_cam;
	tf2::Stamped<tf2::Transform> cam_to_estimation;
	tf2::Stamped<tf2::Transform> cam_to_coopestimation;
	geometry_msgs::msg::TransformStamped msg_servogroup_to_cam;

	// Data analysis
	std::string package_path = ament_index_cpp::get_package_share_directory("ftservocontrol");
	fstream cost_values;
	string cost_values_path = package_path + "/data/cost_values.txt";


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

	/*
	 * @brief Evaluate the cost values
	 */
	void cost_values_evaluate(int i);

	/*
	 * @brief Solve the minimum cost problem
	 */
	void min_cost_solve(int servo_choose_num);

	/*
	 * @brief Update the parameters
	 */
	void Q_param_update();
	void R_param_update();
	void K_param_update(Eigen::Matrix<double,8,8> A, Eigen::Matrix<double,8,8> B, bool print_flag);

};

#endif // MULTISERVOCONTROL_H
