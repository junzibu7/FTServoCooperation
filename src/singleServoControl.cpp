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
	this->declare_parameter<int>("up_init", 180);
	this->declare_parameter<int>("down_init", 180);
	this->declare_parameter<std::string>("camera_config_file", "config/four_camera.yaml");

	id_up = this->get_parameter("id_up").as_int();
	id_down = this->get_parameter("id_down").as_int();
	target_frame = this->get_parameter("target_frame").as_string();
	source_frame = this->get_parameter("source_frame").as_string();
	cam = this->get_parameter("cam").as_string();
	serial_str = this->get_parameter("serial").as_string();
	up_init = this->get_parameter("up_init").as_int();
	down_init = this->get_parameter("down_init").as_int();
	camera_config_file = this->get_parameter("camera_config_file").as_string();

    loadCameraConfig(camera_config_file);

	// cout << "id_up:" << id_up << endl;
	// cout << "id_down:" << id_down << endl;
	// cout << "serial:" << serial_str << endl;

	// TF2 Initialization	
	tf_target_estimation_buffer = std::make_shared<tf2_ros::Buffer>(this->get_clock());
	tf_target_estimation_listener = std::make_shared<tf2_ros::TransformListener>(*tf_target_estimation_buffer);

	// System Initialization
	timer_ = this->create_wall_timer(std::chrono::milliseconds(33), std::bind(&SingleServoNode::T_servogroup_to_camera, this));
	pub_servogroup_to_cam = this->create_publisher<geometry_msgs::msg::TransformStamped>("/T_servogroup" + std::to_string(id_down) + std::to_string(id_up) + "_to_" + cam, 1);
	pub_target_loss = this->create_publisher<msgs::msg::Loss>("/target_loss_" + cam, 1);
	// sub_irlandmark = this->create_subscription<msgs::msg::Landmark>("/" + cam + "/single_cam_process_ros/ir_mono/marker_pixel", 10, std::bind(&SingleServoNode::target_status_callback, this, std::placeholders::_1));
	sub_trajectory = this->create_subscription<geometry_msgs::msg::TransformStamped>("/trajectory", 10, std::bind(&SingleServoNode::T_cam_to_coopestimation_callback, this, std::placeholders::_1));
	sub_ServoCommand = this->create_subscription<msgs::msg::Servocommand>("servo" + std::to_string(id_down) + std::to_string(id_up) + "_command", 10, std::bind(&SingleServoNode::servo_command_callback, this, std::placeholders::_1));
    servogroup_to_cam = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
	// cout << "System has been initialized!" << endl;
}

void SingleServoNode::init(std::shared_ptr<rclcpp::Node> nh_)
{
	nh = nh_;
	
	#ifdef SERVO_ENABLE
	const char *serial_ = serial_str.c_str();

	// Servo Initialization
	_servo.init(serial_, 2, nh, {id_down, id_up});
	#endif

	// Move the servo to the initial position
	servo_move(down_init, up_init);
	

	// std::this_thread::sleep_for(1s);

	// cout << "down_status:" << down_status << endl;
	// cout << "up_status:" << up_status << endl;
}

void SingleServoNode::servo_move(double target_down_status, double target_up_status)
{
	// Move the down servo to the target position
	// 向左转动为负，向右转动为正
	if ((target_down_status > down_status_max) )
	{
		#ifdef SERVO_ENABLE
		_servo.move(down_status_max, id_down);
		#else
		down_status = down_status_max;
		#endif

		RCLCPP_ERROR(nh->get_logger(), "The target position of the down servo is out of range!");
	}
	else if((target_down_status < down_status_min))
	{
		#ifdef SERVO_ENABLE
		_servo.move(down_status_min, id_down);
		#else
		down_status = down_status_min;
		#endif

		RCLCPP_ERROR(nh->get_logger(), "The target position of the down servo is out of range!");
	}
	else
	{
		#ifdef SERVO_ENABLE
		_servo.move(target_down_status, id_down);
		#else
		down_status = target_down_status;
		#endif
	}

	// Move the up servo to the target position
	// 向下转动为正，向上转动为负
	if ((target_up_status > up_status_max) )
	{
		#ifdef SERVO_ENABLE
		_servo.move(up_status_max, id_up);
		#else
		up_status = up_status_max;
		#endif

		RCLCPP_ERROR(nh->get_logger(), "The target position of the up servo is out of range!");
	}
	else if((target_up_status < up_status_min))
	{
		#ifdef SERVO_ENABLE
		_servo.move(up_status_min, id_up);
		#else
		up_status = up_status_min;
		#endif

		RCLCPP_ERROR(nh->get_logger(), "The target position of the up servo is out of range!");
	}
	else
	{
		#ifdef SERVO_ENABLE
		_servo.move(target_up_status, id_up);
		#else
		up_status = target_up_status;
		#endif
	}
}

void SingleServoNode::T_servogroup_to_camera(){
	#ifdef SERVO_ENABLE
	// Get the status of the servos
	down_status = _servo.read(id_down);
	up_status = _servo.read(id_up);	
	#endif	

	// cout << "down_status:" << down_status << endl;
	// cout << "up_status:" << up_status << endl;

	down_change = (down_status - down_status_init) * M_PI / 180;
	up_change = (up_status - up_status_init) * M_PI / 180;

	// cout << "down_change:" << down_change / M_PI * 180 << endl;
	// cout << "up_change:" << up_change / M_PI * 180 << endl;

	// Servo down to up
	T_DU << cos(down_change), sin(down_change), 0, 0, - sin(down_change), cos(down_change), 0, 0, 0, 0, 1, 40.72/1000, 0, 0, 0, 1;
	// Servo up to Bracket
	T_UB << cos(up_change), 0, sin(up_change), 0, 0, 1, 0, 0, - sin(up_change), 0, cos(up_change), 39.60/1000, 0, 0, 0, 1;
	// Bracket to Camera
	T_BC << 1, 0, 0, (-11 + 15) / 1000, 0, 1, 0, (26.25 + 17 + 4.22) / 1000, 0, 0, 1, 66.5 / 1000, 0, 0, 0, 1;

	// Transformation from the servo group to the camera
	T_servogroup_to_cam = T_DU * T_UB * T_BC;
	// cout << T_servogroup_to_cam << endl;

	// Publish the transformation from the servo group to the camera
	msg_servogroup_to_cam.header.stamp = nh->now();
	msg_servogroup_to_cam.header.frame_id = "servogroup" + std::to_string(id_down) + std::to_string(id_up);
	msg_servogroup_to_cam.child_frame_id = cam;
	msg_servogroup_to_cam.transform.translation.x = T_servogroup_to_cam(0, 3);
	msg_servogroup_to_cam.transform.translation.y = T_servogroup_to_cam(1, 3);
	msg_servogroup_to_cam.transform.translation.z = T_servogroup_to_cam(2, 3);
	Eigen::Quaterniond q = Eigen::Quaterniond(T_servogroup_to_cam.block<3,3>(0,0));
	msg_servogroup_to_cam.transform.rotation.x = q.x();
	msg_servogroup_to_cam.transform.rotation.y = q.y();
	msg_servogroup_to_cam.transform.rotation.z = q.z();
	msg_servogroup_to_cam.transform.rotation.w = q.w();

	pub_servogroup_to_cam->publish(msg_servogroup_to_cam);
	servogroup_to_cam->sendTransform(msg_servogroup_to_cam);
}

void SingleServoNode::T_cam_to_estimation_callback(const geometry_msgs::msg::TransformStamped::SharedPtr msg){
	// Get the transformation from the camera to the estimation
	estimation_t_x = msg->transform.translation.x;
	estimation_t_y = msg->transform.translation.y;
	estimation_t_z = msg->transform.translation.z;

	// Transformation from the camera to the estimation
	cam_to_estimation.setOrigin(tf2::Vector3(estimation_t_x, estimation_t_y, estimation_t_z));
}

void SingleServoNode::T_cam_to_coopestimation_callback(const geometry_msgs::msg::TransformStamped::SharedPtr msg){
	// Get the transformation from the camera to the estimation
	rclcpp::Time time = msg->header.stamp;

	target_estimation2status();

	// Calculate the target loss
	Eigen::Vector2d target_loss_cam = target_status2loss(target_status);
	target_loss_msg.header.stamp = nh->now();
	target_loss_msg.x = target_loss_cam.x();
	target_loss_msg.y = target_loss_cam.y();
	target_loss_msg.force_flag = force_flag;
	pub_target_loss->publish(target_loss_msg);
	force_flag = false;
}

void SingleServoNode::target_status_callback(const msgs::msg::Landmark::SharedPtr msg){
	// Initialize the target center
	target_status = cv::Point2f(0, 0);

	// Get the target center
	for (unsigned int i = 0; i < msg->x.size(); i++){
		target_status.x += msg->x[i] / msg->x.size();
		target_status.y += msg->y[i] / msg->y.size();
	}

	// Calculate the target loss
	Eigen::Vector2d target_loss_cam = target_status2loss(target_status);
	target_loss_msg.header.stamp = nh->now();
	target_loss_msg.x = target_loss_cam.x();
	target_loss_msg.y = target_loss_cam.y();
	target_loss_msg.force_flag = force_flag;
	pub_target_loss->publish(target_loss_msg);
	force_flag = false;
}

Eigen::Vector2d SingleServoNode::target_status2loss(cv::Point2f target_status){
	double target_loss_x = (target_status.x - 320) / 320;
	double target_loss_y = (target_status.y - 240) / 240;

	// Calculate the target loss
	Eigen::Vector2d target_loss;

	//cubic loss version
	target_loss.x() = 10 * pow(target_loss_x, 3);
	target_loss.y() = 10 * pow(target_loss_y, 3);

	if(target_loss_x > 1.2){
		target_loss.x() = 3;
		force_flag = true;
	}else if(target_loss_x < -1.2){
		target_loss.x() = -3;
		force_flag = true;
	}

	if(target_loss_y > 1.2){
		target_loss.y() = 3;
		force_flag = true;
	}else if(target_loss_y < -1.2){
		target_loss.y() = -3;
		force_flag = true;
	}

	// if(cam == "camA")
	// {
	// 	cout << cam + "_target_status:" << target_status << endl; 
	// 	cout << cam + "_target_loss:" << target_loss << endl;
	// }

	return target_loss;
}

cv::Point2d SingleServoNode::target_loss2status(double loss_x, double loss_y, bool force_flag){
	cv::Point2d target_image_pos = cv::Point2d(0.0, 0.0);

	// Target loss process
	double x_para = 0.0;
	double y_para = 0.0;

	if(loss_x < 0){
		x_para = - pow(-loss_x / 10.0, 1.0 / 3.0);
	}else{
		x_para = pow(loss_x / 10.0, 1.0 / 3.0);
	}

	if(loss_y < 0){
		y_para = - pow(-loss_y / 10.0, 1.0 / 3.0);
	}else{	
		y_para = pow(loss_y / 10.0, 1.0 / 3.0);
	}

	target_image_pos.x = 320.0 + 320.0 * x_para;
	target_image_pos.y = 240.0 + 240.0 * y_para;

	if(force_flag){
		target_image_pos.x = 320.0;
		target_image_pos.y = 240.0;
	}

	return target_image_pos;
}

void SingleServoNode::servo_command_callback(const msgs::msg::Servocommand::SharedPtr msg)
{
	// Move the servo to the target position
	cv::Point2d target_image_pos = target_loss2status(msg->state_down, msg->state_up, msg->force_flag); 
	// target_image_pos = cv::Point2d(320, 240);
	Eigen::Vector2d target_change = target_status2change(target_image_pos);
	target_down_change = target_change.x();
	target_up_change = target_change.y();

	// // test
	// if(cam == "camA")
	// {
		// cout << cam+ "_estimation_t_x:" << estimation_t_x << endl;	
		// cout << cam+ "_estimation_t_y:" << estimation_t_y << endl;
		// cout << cam+ "_estimation_t_z:" << estimation_t_z << endl;
		// cout << cam + "_target_status:" << target_status << endl;
		// cout << cam + "_calculate_loss:" << msg->state_down << " " << msg->state_up << endl;
		// cout << cam + "_target_image_pos:" << target_image_pos << endl;
		// cout << cam + "target_down_change:" << target_down_change << endl;
		// cout << cam + "target_up_change:" << target_up_change << endl;
	// }

	servo_move(down_status + target_down_change, up_status + target_up_change);
	
}

void SingleServoNode::loadCameraConfig(const std::string& config_path)
{
    std::ifstream fin(config_path);
    YAML::Node camera_config = YAML::Load(fin);
            
    auto IR1_camera = camera_config[cam]["ir_camera"]["IR_1"];
    // int image_width = IR1_camera["image_width"].as<int>();
    // int image_height = IR1_camera["image_height"].as<int>();
	fx = IR1_camera["fx"].as<double>();
	fy = IR1_camera["fy"].as<double>();
	cx = IR1_camera["cx"].as<double>();
	cy = IR1_camera["cy"].as<double>();

	camera_matrix = (cv::Mat_<double>(3, 3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);
	// cout << "camera_matrix" << camera_matrix << endl;

	// 获取畸变参数 D
    auto D = IR1_camera["D"].as<std::vector<double>>();
	distortion_coefficients = cv::Mat(D).clone();
	// cout << "distortion_coefficients" << distortion_coefficients << endl;
}

void SingleServoNode::target_estimation2status()
{
	find_transform(source_frame, target_frame);

	// 初始化目标点和图像点
	target_point.clear();
	image_point.clear();

	// 初始化目标点的矩阵
	cv::Point3f real_point;
	real_point.x = - estimation_t_y;
	real_point.y = - estimation_t_z;
	real_point.z = + estimation_t_x;
	if(real_point.z < 0.1) real_point.z = 0.1;
    target_point.push_back(real_point);

	// cout << "target_point:" << target_point << endl;

	// 初始化相关参数矩阵
	cv::Mat tVec(3, 1, cv::DataType<double>::type); // Translation vector
    tVec.at<double>(0) = 0.0;
    tVec.at<double>(1) = 0.0;
    tVec.at<double>(2) = 0.0;

	cv::Mat rotationMat = cv::Mat::eye(3, 3, CV_64F); // Rotation Matrix
    cv::Mat rVec; // Rotation vector
	cv::Rodrigues(rotationMat, rVec);// 转换为旋转向量

	// 投影点到图像平面
	cv::projectPoints(target_point, rVec, tVec, camera_matrix, distortion_coefficients, image_point);
	
	// image_point包含了投影到图像坐标系后的点的坐标
    target_status.x = image_point[0].x;
	target_status.y = image_point[0].y;

	DepthofField_x = real_point.x / (target_status.x - cx + 1.0);
	DepthofField_y = real_point.y / (target_status.y - cy + 1.0);

	

	// if(cam == "camA")
	// {
	// 	cout << cam + "_target_status:" << target_status << endl; 
	// }
}

Eigen::Vector2d SingleServoNode::target_status2change(cv::Point2d target_image_pos)
{
	// 由图像坐标系下的二维点（x, y）计算相机坐标系下的点 (X, Y, Z)
    Eigen::Vector3d target_camera_point(0.0, 0.0, 1.0);
	double delta_pos_x = target_image_pos.x - cx;
	double delta_pos_y = target_image_pos.y - cy;
	if(delta_pos_x < 10) delta_pos_x = 0.0;
	if(delta_pos_y < 5) delta_pos_y = 0.0;
	target_camera_point[0] = delta_pos_x * DepthofField_x;
	target_camera_point[1] = delta_pos_y * DepthofField_y;
	target_camera_point[2] = estimation_t_x;
	if(target_camera_point[2] < 0.1) target_camera_point[2] = 0.1;
	// if(cam == "camA")
	// {
		// cout << cam + "_target_camera_point:" << target_camera_point << endl;
	// }

	//水平夹角theta，垂直夹角phi
	double theta = 0;
	double phi = 0;
	theta = - atan( target_camera_point[0] / target_camera_point[2]) + atan(- estimation_t_y / estimation_t_x);
	phi = - (atan(- target_camera_point[1] / sqrt(pow(target_camera_point[0],2) + pow(target_camera_point[2],2))) - atan(estimation_t_z / sqrt(pow(estimation_t_x,2) + pow(estimation_t_y,2))));
	theta = theta * 180.0 / M_PI;
	phi = - phi * 180.0 / M_PI;

	// if(cam == "camA")
	// {
		// RCLCPP_INFO(nh->get_logger(), "theta: %f, phi: %f", theta, phi);
	// }
	
	// 由theta和phi计算舵机转动角度
	Eigen::Vector2d servo_move_target(theta, phi);
	return servo_move_target;

}

void SingleServoNode::find_transform(const std::string& from_frame, const std::string& to_frame)
  {
    try {
		// 尝试查找从from_frame到to_frame的变换
		geometry_msgs::msg::TransformStamped transform;
		transform = tf_target_estimation_buffer->lookupTransform(from_frame, to_frame, rclcpp::Time(0.3));

		estimation_t_x = transform.transform.translation.x;
		estimation_t_y = transform.transform.translation.y;
		estimation_t_z = transform.transform.translation.z;
		estimation_distance = sqrt(pow(estimation_t_x, 2) + pow(estimation_t_y, 2) + pow(estimation_t_z, 2));
    } catch (const tf2::TransformException& ex) {
      	// RCLCPP_ERROR(nh->get_logger(), "%s", ex.what());
    }

  }