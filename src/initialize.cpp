/*
 * @Author: 黄先 1215399660@qq.com
 * @Date: 2024-02-28 09:36:03
 * @LastEditors: 黄先 1215399660@qq.com
 * @LastEditTime: 2024-02-28 20:48:17
 * @FilePath: /test_ws/src/ftservocontrol/src/initialize.cpp
 * @Description: initialization of modified_id-th servo
 */
#include <ftservocontrol/FEETECHservo.h>

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("initialize");
	int modified_id ;
	const char *_serial;
	std::string serial_string;
	node->declare_parameter<int>("ftservo/id", 1);
    node->declare_parameter<std::string>("ftservo/serial", "/dev/ttyUSB0");
	modified_id = node->get_parameter("ftservo/id").as_int();
    serial_string = node->get_parameter("/initialize/ftservo/serial").as_string();
	// serial_string = node->get_parameter("/initialize/ftservo/serial").as_string();
    RCLCPP_INFO(node->get_logger(), "%d", modified_id);
	_serial = serial_string.c_str();
	ftServo _servo;
	std::vector<int> ID_list = {1, 2, 3, 4, 5, 6, 7, 8};
	_servo.init(_serial, 8, node, ID_list);
	_servo.ping(1);
	_servo.ping(2);
	_servo.ping(3);
	_servo.ping(4);
	_servo.ping(5);
	_servo.ping(6);
	_servo.ping(7);
	_servo.ping(8);
	
	_servo.rename(1, modified_id);
	_servo.reset(modified_id);
	_servo.ping(1);
	RCLCPP_INFO(node->get_logger(), "Modification completed. The modified ID is: %d", modified_id);
    rclcpp::shutdown();
	return 0;
}