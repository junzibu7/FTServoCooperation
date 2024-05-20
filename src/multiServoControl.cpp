#include <ftservocontrol/multiServoControl.h>


using namespace std;


MultiServoNode::MultiServoNode(const std::string &node_name) : Node(node_name)
{
	// Basic Parameters	
	timer_ = this->create_wall_timer(std::chrono::milliseconds(1000), std::bind(&MultiServoNode::calculate_control_signal, this));

	// System Initialization
	sub_target_loss_camA = this->create_subscription<msgs::msg::Loss>("/target_loss_camA", 10, std::bind(&MultiServoNode::target_loss_camA_callback, this, std::placeholders::_1));
	sub_target_loss_camB = this->create_subscription<msgs::msg::Loss>("/target_loss_camB", 10, std::bind(&MultiServoNode::target_loss_camB_callback, this, std::placeholders::_1));
	sub_target_loss_camC = this->create_subscription<msgs::msg::Loss>("/target_loss_camC", 10, std::bind(&MultiServoNode::target_loss_camC_callback, this, std::placeholders::_1));
	sub_target_loss_camD = this->create_subscription<msgs::msg::Loss>("/target_loss_camD", 10, std::bind(&MultiServoNode::target_loss_camD_callback, this, std::placeholders::_1));

	pub_servo12_command = this->create_publisher<msgs::msg::Servocommand>("/servo12_command", 1);
	pub_servo34_command = this->create_publisher<msgs::msg::Servocommand>("/servo34_command", 1);
	pub_servo56_command = this->create_publisher<msgs::msg::Servocommand>("/servo56_command", 1);
	pub_servo78_command = this->create_publisher<msgs::msg::Servocommand>("/servo78_command", 1);
}

void MultiServoNode::target_loss_camA_callback(const msgs::msg::Loss::SharedPtr msg)
{
	loss_cur(0) = msg->x;
	loss_cur(1) = msg->y;
	camA_force_flag = msg->force_flag;
}

void MultiServoNode::target_loss_camB_callback(const msgs::msg::Loss::SharedPtr msg)
{
	loss_cur(2) = msg->x;
	loss_cur(3) = msg->y;
	camB_force_flag = msg->force_flag;
}

void MultiServoNode::target_loss_camC_callback(const msgs::msg::Loss::SharedPtr msg)
{
	loss_cur(4) = msg->x;
	loss_cur(5) = msg->y;
	camC_force_flag = msg->force_flag;
}

void MultiServoNode::target_loss_camD_callback(const msgs::msg::Loss::SharedPtr msg)
{	
	loss_cur(6) = msg->x;
	loss_cur(7) = msg->y;
	camD_force_flag = msg->force_flag;
}

void MultiServoNode::calculate_control_signal()
{
	// RCLCPP_INFO(this->get_logger(), "Calculating Control Signal!");

	// Calculate k = control / loss
	K = (R + iter_B.transpose()*Q*iter_B).inverse()*iter_B.transpose()*Q*iter_A;

	servo_cur = K * loss_cur;

	iter_B_buf = iter_B;

	min_cost_solve();

	K = (R + iter_B_buf.transpose()*Q*iter_B_buf).inverse()*iter_B_buf.transpose()*Q*iter_A;
	servo_cur = K * loss_cur;

	loss_nex = iter_A * loss_cur + iter_B_buf * servo_cur;

	servo12_command.state_down = loss_nex(0);
	servo12_command.state_up = loss_nex(1);
	servo34_command.state_down = loss_nex(2);
	servo34_command.state_up = loss_nex(3);
	servo56_command.state_down = loss_nex(4);
	servo56_command.state_up = loss_nex(5);
	servo78_command.state_down = loss_nex(6);
	servo78_command.state_up = loss_nex(7);

	servo12_command.force_flag = camA_force_flag;
	servo34_command.force_flag = camB_force_flag;
	servo56_command.force_flag = camC_force_flag;
	servo78_command.force_flag = camD_force_flag;

	pub_servo12_command->publish(servo12_command);
	pub_servo34_command->publish(servo34_command);
	pub_servo56_command->publish(servo56_command);
	pub_servo78_command->publish(servo78_command);

	// RCLCPP_INFO(this->get_logger(), "Calculated Control Signal sent out!");

}

void MultiServoNode::min_cost_solve()
{
	double cost = 100000;
	Eigen::Vector2i servo_select = Eigen::Vector2i::Zero();

	for(int i = 0; i < 3; i++)
	{
		for(int j = i + 1; j < 4; j++)
		{
			if(pow(servo_cur(2*i), 2) + pow(servo_cur(2*i + 1), 2) + pow(servo_cur(2*j), 2) + pow(servo_cur(2*j + 1), 2) < cost)
			{
				cost = pow(servo_cur(2*i), 2) + pow(servo_cur(2*i + 1), 2) + pow(servo_cur(2*j), 2) + pow(servo_cur(2*j + 1), 2);
				servo_select(0) = i;
				servo_select(1) = j;
			}
		}
	}

	iter_B_buf.block<2, 2>(servo_select(0), servo_select(0)) = Eigen::Matrix2d::Zero();
	iter_B_buf.block<2, 2>(servo_select(1), servo_select(1)) = Eigen::Matrix2d::Zero();

	for(int i = 0; i < 8; i++)
	{
		if(servo_cur(i) > 50)
		{
			iter_B_buf.block<1, 1>(i, i) = Eigen::Matrix<double, 1, 1>::Identity();
		}
		else if(servo_cur(i) < 5)
		{
			iter_B_buf.block<1, 1>(i, i) = Eigen::Matrix<double, 1, 1>::Zero();
		}
	}

}

