#include <ftservocontrol/multiServoControl.h>


using namespace std;


MultiServoNode::MultiServoNode(const std::string &node_name) : Node(node_name)
{
	// Basic Parameters	
	this->declare_parameter<int>("servo_control_num", 2);
	servo_control_num = this->get_parameter("servo_control_num").as_int();
	
	// Frequency Parameters
	signal_timer_ = this->create_wall_timer(std::chrono::milliseconds(50), std::bind(&MultiServoNode::calculate_control_signal, this));
	// evaluate_timer_ = this->create_wall_timer(std::chrono::milliseconds(33), std::bind(&MultiServoNode::cost_values_evaluate, this));
	
	// System Initialization
	sub_target_loss_camA = this->create_subscription<msgs::msg::Loss>("/target_loss_camA", 10, std::bind(&MultiServoNode::target_loss_camA_callback, this, std::placeholders::_1));
	sub_target_loss_camB = this->create_subscription<msgs::msg::Loss>("/target_loss_camB", 10, std::bind(&MultiServoNode::target_loss_camB_callback, this, std::placeholders::_1));
	sub_target_loss_camC = this->create_subscription<msgs::msg::Loss>("/target_loss_camC", 10, std::bind(&MultiServoNode::target_loss_camC_callback, this, std::placeholders::_1));
	sub_target_loss_camD = this->create_subscription<msgs::msg::Loss>("/target_loss_camD", 10, std::bind(&MultiServoNode::target_loss_camD_callback, this, std::placeholders::_1));

	pub_servo12_command = this->create_publisher<msgs::msg::Servocommand>("/servo12_command", 1);
	pub_servo34_command = this->create_publisher<msgs::msg::Servocommand>("/servo34_command", 1);
	pub_servo56_command = this->create_publisher<msgs::msg::Servocommand>("/servo56_command", 1);
	pub_servo78_command = this->create_publisher<msgs::msg::Servocommand>("/servo78_command", 1);

	// Clear the cost_values file
	cost_values.open(cost_values_path, std::ios::out | std::ios::trunc);

	RCLCPP_INFO(this->get_logger(), "MultiServoNode has been initialized.");
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
	RCLCPP_INFO(this->get_logger(),"Calculate Start !");
	Q_param_update();
	R_param_update();
	
	// Calculate k = control / loss (+)
	K_param_update(iter_A, iter_B, false);

	servo_cur = K * loss_cur;

	loss_nex = iter_A * loss_cur - iter_B * servo_cur;

	RCLCPP_INFO(this->get_logger(), "loss_cur: %f %f %f %f %f %f %f %f", loss_cur(0), loss_cur(1), loss_cur(2), loss_cur(3), loss_cur(4), loss_cur(5), loss_cur(6), loss_cur(7));
	// RCLCPP_INFO(this->get_logger(), "servo_cur: %f %f %f %f %f %f %f %f", servo_cur(0), servo_cur(1), servo_cur(2), servo_cur(3), servo_cur(4), servo_cur(5), servo_cur(6), servo_cur(7));

	iter_B_buf = Eigen::Matrix<double,8,8>::Zero();

	min_cost_solve(servo_control_num);

	K_param_update(iter_A, iter_B_buf, true);

	servo_cur = K * loss_cur;

	loss_nex = iter_A * loss_cur - iter_B_buf * servo_cur;
	RCLCPP_INFO(this->get_logger(), "loss_nex: %f %f %f %f %f %f %f %f", loss_nex(0), loss_nex(1), loss_nex(2), loss_nex(3), loss_nex(4), loss_nex(5), loss_nex(6), loss_nex(7));
	// RCLCPP_INFO(this->get_logger(), "delta_loss: %f %f %f %f %f %f %f %f", loss_nex(0) - loss_cur(0), loss_nex(1) - loss_cur(1), loss_nex(2) - loss_cur(2), loss_nex(3) - loss_cur(3), loss_nex(4) - loss_cur(4), loss_nex(5) - loss_cur(5), loss_nex(6) - loss_cur(6), loss_nex(7) - loss_cur(7));

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
}

void MultiServoNode::cost_values_evaluate(int i)
{
	// Analysis of the cost
	Eigen::Vector2d single_loss_cur = Eigen::Vector2d::Zero();
	single_loss_cur(0) = loss_cur(2*i);
	single_loss_cur(1) = loss_cur(2*i + 1);
	Eigen::Vector2d single_servo_cur = Eigen::Vector2d::Zero();
	single_servo_cur(0) = servo_cur(2*i);
	single_servo_cur(1) = servo_cur(2*i + 1);
	Eigen::Vector2d single_loss_nex = Eigen::Vector2d::Zero();
	single_loss_nex(0) = loss_nex(2*i);
	single_loss_nex(1) = loss_nex(2*i + 1);
	
	COST_WITH_CONTROL(i) = 0.5*(single_servo_cur.transpose()*(R.block<2, 2>(2*i, 2*i))*single_servo_cur).value() + 0.5*(single_loss_nex.transpose()*(Q.block<2, 2>(2*i, 2*i))*single_loss_nex).value();
	COST_WITHOUT_CONTROL(i) = 0.5*(single_loss_cur.transpose()*(Q.block<2, 2>(2*i, 2*i))*single_loss_cur).value();
	DELTA_COST(i) = COST_WITHOUT_CONTROL(i) - COST_WITH_CONTROL(i);

	// cost_values.open(cost_values_path, std::ios::out | std::ios::app);
	// if (!cost_values.is_open()) {
	// 	RCLCPP_ERROR(this->get_logger(), "Failed to open cost_values.txt");
	// }else{
	// 	cost_values << COST << endl;
	// 	cost_values.close();
	// }
}

void MultiServoNode::min_cost_solve(int servo_choose_num)
{
	// Caculate the minimum cost
	for(int i = 0; i < 4; i++)
	{
		cost_values_evaluate(i);
	}
	RCLCPP_INFO(this->get_logger(), "DELTA_COST: %f %f %f %f", DELTA_COST(0), DELTA_COST(1), DELTA_COST(2), DELTA_COST(3));
	
	// Initialize the servo_select and min_cost_values
	servo_select(0) = -1;
	servo_select(1) = -1;
	servo_select(2) = -1;
	servo_select(3) = -1;
	min_cost_values(0) = -10000.0;
	min_cost_values(1) = -10000.0;
	min_cost_values(2) = -10000.0;
	min_cost_values(3) = -10000.0;

	// Find two maximum delta costs from DELTA_COST
	for(int i = 0; i < servo_choose_num; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(DELTA_COST(j) > min_cost_values(i))
			{
				min_cost_values(i) = DELTA_COST(j);
				servo_select(i) = j;
			}
		}
		DELTA_COST(servo_select(i)) = -10000;
	}

	for(int i = 0; i < servo_choose_num; i++)
	{
		iter_B_buf.block<2, 2>(2 * servo_select(i), 2 * servo_select(i)) = Eigen::Matrix2d::Identity();
	}

	// Parameters print
	RCLCPP_INFO(this->get_logger(), "servo_select: %d %d %d %d", servo_select(0), servo_select(1), servo_select(2), servo_select(3));
}

void MultiServoNode::Q_param_update()
{
	Q(0, 0) = 15;
	Q(1, 1) = 10;
	Q(2, 2) = 15;
	Q(3, 3) = 10;
	Q(4, 4) = 15;
	Q(5, 5) = 10;
	Q(6, 6) = 15;
	Q(7, 7) = 10;
}

void MultiServoNode::R_param_update()
{
	R(0, 0) = 40;
	R(1, 1) = 30;
	R(2, 2) = 40;
	R(3, 3) = 30;
	R(4, 4) = 40;
	R(5, 5) = 30;
	R(6, 6) = 40;
	R(7, 7) = 30;

	// for(int i = 0; i < 4; i++)
	// {
	// 	if(servo_select(i) != -1)
	// 	{
	// 		R(2 * servo_select(i), 2 * servo_select(i)) *= 30;
	// 		R(2 * servo_select(i) + 1, 2 * servo_select(i) + 1) *= 30;
	// 	}
	// }
}

void MultiServoNode::K_param_update(Eigen::Matrix<double,8,8> A, Eigen::Matrix<double,8,8> B, bool print_flag)
{
	Eigen::Matrix<double,8,8> buffer;
	
	buffer = R + B.transpose()*Q*B;
	
	for(int i = 0; i < 8; i++)
	{
		if(buffer(i, i) < 0.0001)
		{
			buffer(i, i) = 0.0001;
		}
	}
	K = buffer.inverse()*B.transpose()*Q*A;

	if(print_flag)
	{
		// cout << "A: " << endl << A << endl;
		// cout << "B: " << endl << B << endl;
		// cout << "buffer: " << endl << buffer << endl;
		// cout << "K: " << endl << K << endl;
	}
	
}