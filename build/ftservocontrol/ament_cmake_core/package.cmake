set(_AMENT_PACKAGE_NAME "ftservocontrol")
set(ftservocontrol_VERSION "0.0.0")
set(ftservocontrol_MAINTAINER "adminstr <adminstr@todo.todo>")
set(ftservocontrol_BUILD_DEPENDS "std_msgs" "geometry_msgs" "cv_bridge" "roscpp" "rospy" "tf" "rclcpp" "rclpy" "tf2" "msgs")
set(ftservocontrol_BUILDTOOL_DEPENDS "catkin" "ament_cmake")
set(ftservocontrol_BUILD_EXPORT_DEPENDS "std_msgs" "geometry_msgs" "cv_bridge" "roscpp" "rospy" "tf" "rclcpp" "rclpy" "tf2" "msgs")
set(ftservocontrol_BUILDTOOL_EXPORT_DEPENDS )
set(ftservocontrol_EXEC_DEPENDS "std_msgs" "geometry_msgs" "cv_bridge" "roscpp" "rospy" "tf" "rclcpp" "rclpy" "tf2" "msgs")
set(ftservocontrol_TEST_DEPENDS "ament_lint_auto" "ament_lint_common")
set(ftservocontrol_GROUP_DEPENDS )
set(ftservocontrol_MEMBER_OF_GROUPS )
set(ftservocontrol_DEPRECATED "")
set(ftservocontrol_EXPORT_TAGS)
list(APPEND ftservocontrol_EXPORT_TAGS "<build_type condition=\"$ROS_VERSION == 1\">catkin</build_type>")
list(APPEND ftservocontrol_EXPORT_TAGS "<build_type condition=\"$ROS_VERSION == 2\">ament_cmake</build_type>")
