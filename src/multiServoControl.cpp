#include <ftservocontrol/multiServoControl.h>


using namespace std;


MultiServoNode::MultiServoNode(const std::string &node_name) : Node(node_name)
{
	// Basic Parameters	

	// System Initialization
	sub_target_loss_camA = this->create_subscription<msgs::msg::Loss>("/target_loss_camA", 10, std::bind(&MultiServoNode::target_loss_camA_callback, this, std::placeholders::_1));
	sub_target_loss_camB = this->create_subscription<msgs::msg::Loss>("/target_loss_camB", 10, std::bind(&MultiServoNode::target_loss_camB_callback, this, std::placeholders::_1));
	sub_target_loss_camC = this->create_subscription<msgs::msg::Loss>("/target_loss_camC", 10, std::bind(&MultiServoNode::target_loss_camC_callback, this, std::placeholders::_1));
	sub_target_loss_camD = this->create_subscription<msgs::msg::Loss>("/target_loss_camD", 10, std::bind(&MultiServoNode::target_loss_camD_callback, this, std::placeholders::_1));

}

void MultiServoNode::target_loss_camA_callback(const msgs::msg::Loss::SharedPtr msg)
{
	target_loss_camA.x() = msg->x;
	target_loss_camA.y() = msg->y;

}

void MultiServoNode::target_loss_camB_callback(const msgs::msg::Loss::SharedPtr msg)
{
	target_loss_camB.x() = msg->x;
	target_loss_camB.y() = msg->y;
}

void MultiServoNode::target_loss_camC_callback(const msgs::msg::Loss::SharedPtr msg)
{
	target_loss_camC.x() = msg->x;
	target_loss_camC.y() = msg->y;
}

void MultiServoNode::target_loss_camD_callback(const msgs::msg::Loss::SharedPtr msg)
{
	target_loss_camD.x() = msg->x;
	target_loss_camD.y() = msg->y;
}

void MultiServoNode::calculate_control_signal()
{
	// Calculate k = control / loss
	K = (R + iter_B.transpose()*Q*iter_B + S.transpose()*H*S).inverse()*iter_B.transpose()*Q*iter_A;

	loss_cur(0) = target_loss_camA.x();
	loss_cur(1) = target_loss_camA.y();
	loss_cur(2) = target_loss_camB.x();
	loss_cur(3) = target_loss_camB.y();

	servo_cur = K * loss_cur;

	Eigen::Matrix<double,4,4> iter_B_buf = iter_B;

	if(pow(servo_cur(0), 2) + pow(servo_cur(1), 2) > pow(servo_cur(2), 2) + pow(servo_cur(3), 2))
	{
		iter_B_buf.block<2, 2>(2, 2) = Eigen::Matrix2d::Zero();
	}
	else
	{
		iter_B_buf.block<2, 2>(0, 0) = Eigen::Matrix2d::Zero();
	}

	for(int i = 0; i < 4; i++)
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

	K = -(R + iter_B_buf.transpose()*Q*iter_B_buf + S.transpose()*H*S).inverse()*iter_B_buf.transpose()*Q*iter_A;

	loss_nex = iter_A * loss_cur + iter_B_buf * servo_cur;
}