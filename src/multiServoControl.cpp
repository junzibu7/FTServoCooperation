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

