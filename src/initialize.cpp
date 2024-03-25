/*
 * @Author: 黄先 1215399660@qq.com
 * @Date: 2024-02-28 09:36:03
 * @LastEditors: 黄先 1215399660@qq.com
 * @LastEditTime: 2024-02-28 20:48:17
 * @FilePath: /test_ws/src/ftservoControl/src/initialize.cpp
 * @Description: initialization of modified_id-th servo
 */
#include <ftservoControl/FEETECHservo.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "initialize");
	ros::NodeHandle nh;
	int modified_id ;
	const char *_serial;
	std::string serial_string;
	nh.param("/initialize/ftservo/id", modified_id, 1);
	nh.param("/initialize/ftservo/serial", serial_string, std::string("/dev/ttyUSB0"));
	std::cout<<modified_id<<std::endl;
	_serial = serial_string.c_str();
	ftServo _servo;
	std::vector<int> ID_list = {7, 8};
	_servo.init(_serial, 2, nh, ID_list);
	_servo.rename(8, modified_id);
	_servo.reset(modified_id);
	_servo.ping(8);
	ROS_INFO("Modification completed. The modified ID is: %d", modified_id);
	return 0;
}