#include <ftservocontrol/singleServoControl.h>


using namespace std;

SingleServoNode::SingleServoNode(const std::string &node_name) : Node(node_name)
{
	// Basic Parameters
	this->declare_parameter<int>("id_down", 1);
	this->declare_parameter<int>("id_up", 2);
	this->declare_parameter<std::string>("target_frame", "EstimationfromcamA");
	this->declare_parameter<std::string>("source_frame", "camA");
	this->declare_parameter<std::string>("cam", "camA"); 
	this->declare_parameter<std::string>("serial", "/dev/ttyUSB0");

	id_up = this->get_parameter("id_up").as_int();
	id_down = this->get_parameter("id_down").as_int();
	target_frame = this->get_parameter("target_frame").as_string();
	source_frame = this->get_parameter("source_frame").as_string();
	cam = this->get_parameter("cam").as_string();
	serial_str = this->get_parameter("serial").as_string();

	cout << "id_up:" << id_up << endl;
	cout << "id_down:" << id_down << endl;
	cout << "serial:" << serial_str << endl;	

	// System Initialization
	pub_servogroup_to_cam = this->create_publisher<geometry_msgs::msg::TransformStamped>("/T_servogroup" + std::to_string(id_down) + std::to_string(id_up) + "_to_" + cam, 1);
	// sub_irlandmark = this->create_subscription<ftservocontrol::msg::landmark>("/" + cam + "/single_cam_process_ros/ir_mono/marker_pixel", 1, std::bind(&SingleServoNode::target_center_callback, this, _1));

	cout << "System has been initialized!" << endl;
}

void SingleServoNode::init(std::shared_ptr<rclcpp::Node> nh_)
{
	nh = nh_;
	
	const char *serial_ = serial_str.c_str();
	
	// Servo Initialization
	_servo.init(serial_, 2, nh, {id_down, id_up});

	// Move the servo to the initial position
	// servo_move(down_status_init, up_status_init);

	// std::this_thread::sleep_for(1s);

	// down_status = _servo.read(id_down);
	// up_status = _servo.read(id_up);

	// cout << "down_status:" << down_status << endl;
	// cout << "up_status:" << up_status << endl;
}

void SingleServoNode::servo_move(double target_down_status, double target_up_status)
{
	// Move the down servo to the target position
	if ((target_down_status > down_status_max) )
	{
		_servo.move(down_status_max, id_down);
		RCLCPP_ERROR(nh->get_logger(), "The target position of the down servo is out of range!");
	}
	else if((target_down_status < down_status_min))
	{
		_servo.move(down_status_min, id_down);
		RCLCPP_ERROR(nh->get_logger(), "The target position of the down servo is out of range!");
	}
	else
	{
		_servo.move(target_down_status, id_down);
	}

	// Move the up servo to the target position
	if ((target_up_status > up_status_max) )
	{
		_servo.move(up_status_max, id_up);
		RCLCPP_ERROR(nh->get_logger(), "The target position of the up servo is out of range!");
	}
	else if((target_up_status < up_status_min))
	{
		_servo.move(up_status_min, id_up);
		RCLCPP_ERROR(nh->get_logger(), "The target position of the up servo is out of range!");
	}
	else
	{
		_servo.move(target_up_status, id_up);
	}
}

void SingleServoNode::T_servogroup_to_camera(){
	down_status = _servo.read(id_down);
	up_status = _servo.read(id_up);

	// cout << "down_status:" << down_status << endl;
	// cout << "up_status:" << up_status << endl;

	down_change = (down_status - down_status_init) * M_PI / 180;
	up_change = (up_status - up_status_init) * M_PI / 180;

	// cout << "down_change:" << down_change / M_PI * 180 << endl;
	// cout << "up_change:" << up_change / M_PI * 180 << endl;

	// Servo down to up
	T_DU << cos(down_change), sin(down_change), 0, 0, - sin(down_change), cos(down_change), 0, 0, 0, 0, 1, 40.72/1000, 0, 0, 0, 1;
	// Servo up to Bracket
	T_UB << cos(up_change), 0, -sin(up_change), 0, 0, 1, 0, 0, sin(up_change), 0, cos(up_change), 39.60/1000, 0, 0, 0, 1;
	// Bracket to Camera
	T_BC << 1, 0, 0, (-11 + 15) / 1000, 0, 1, 0, (26.25 + 17 + 4.22) / 1000, 0, 0, 1, 66.5 / 1000, 0, 0, 0, 1;

	// Transformation from the servo group to the camera
	T_servogroup_to_cam = T_DU * T_UB * T_BC;

	// cout << T_servogroup_to_cam << endl;
	
}

void SingleServoNode::T_cam_to_estimation_callback(const geometry_msgs::msg::TransformStamped &msg){
	// Get the transformation from the camera to the estimation
	target_t_x = msg.transform.translation.x;
	target_t_y = msg.transform.translation.y;
	target_t_z = msg.transform.translation.z;
	target_q_x = msg.transform.rotation.x;
	target_q_y = msg.transform.rotation.y;
	target_q_z = msg.transform.rotation.z;
	target_q_w = msg.transform.rotation.w;

	// Transformation from the camera to the estimation
	cam_to_estimation.setOrigin(tf2::Vector3(target_t_x, target_t_y, target_t_z));
	cam_to_estimation.setRotation(tf2::Quaternion(target_q_x, target_q_y, target_q_z, target_q_w));
}

void SingleServoNode::T_cam_to_coopestimation_callback(const geometry_msgs::msg::TransformStamped &msg){
	// Get the transformation from the camera to the estimation
	target_t_x = msg.transform.translation.x;
	target_t_y = msg.transform.translation.y;
	target_t_z = msg.transform.translation.z;
	target_q_x = msg.transform.rotation.x;
	target_q_y = msg.transform.rotation.y;
	target_q_z = msg.transform.rotation.z;
	target_q_w = msg.transform.rotation.w;

	// Transformation from the camera to the estimation
	cam_to_coopestimation.setOrigin(tf2::Vector3(target_t_x, target_t_y, target_t_z));
	cam_to_coopestimation.setRotation(tf2::Quaternion(target_q_x, target_q_y, target_q_z, target_q_w));
}

void SingleServoNode::target_center_callback(const msgs::msg::Landmark &msg){
	// Initialize the target center
	target_center = cv::Point2f(0, 0);

	// Get the target center
	for (unsigned int i = 0; i < msg.x.size(); i++){
		target_center.x += msg.x[i] / msg.x.size();
		target_center.y += msg.y[i] / msg.y.size();
	}
}