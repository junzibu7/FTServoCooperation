cmake_minimum_required(VERSION 3.25.2)
project(ftservocontrol)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


if($ENV{ROS_VERSION} EQUAL 1)
#================================= ROS1 ==================================
  message("Version : ROS1")
  find_package(catkin REQUIRED COMPONENTS
    cv_bridge
    roscpp
    rospy
    tf
    std_msgs
    geometry_msgs
  )
  find_package(OpenCV 4.2.0 REQUIRED)
  find_package(Eigen3 REQUIRED)

  include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
  )
  add_definitions(${EIGEN_DEFINITIONS})

  catkin_package(ServoControl
    INCLUDE_DIRS include 
    LIBRARIES ftservocontrol
    CATKIN_DEPENDS roscpp rospy std_msgs tf cv_bridge
  )

  add_library(ftservocontrol src/FEETECHservo.cpp)
  add_library(math_tools_lib src/math_tools.cpp)

  target_link_libraries(ftservocontrol
    ${catkin_LIBRARIES} 
    ${PROJECT_SOURCE_DIR}/include/SCServo/lib_x86/libSCServo.so #x86
  )  
  add_executable(WritePos src/WritePos.cpp)
  target_link_libraries(WritePos
    ${catkin_LIBRARIES}
    ftservocontrol
    ${PROJECT_SOURCE_DIR}/include/SCServo/lib_x86/libSCServo.so #x86
  )
  add_dependencies(WritePos ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

  # add_executable(servoControl src/servoControl.cpp)
  # target_link_libraries(servoControl
  #   ${catkin_LIBRARIES}
  #   ${PROJECT_SOURCE_DIR}/include/ftservocontrol/libSCServo.a
  #  )
  # add_dependencies(servoControl ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

  add_executable(initialize src/initialize.cpp)
  target_link_libraries(initialize
    ${catkin_LIBRARIES}
    ftservocontrol
    ${PROJECT_SOURCE_DIR}/include/SCServo/lib_x86/libSCServo.so #x86
  )
  add_dependencies(initialize ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

  add_executable(singleServoControl src/singleServoControl.cpp)
  target_link_libraries(singleServoControl
    ${catkin_LIBRARIES}
    ftservocontrol
    math_tools_lib
    ${PROJECT_SOURCE_DIR}/include/SCServo/lib_x86/libSCServo.so #x86
  )
  add_dependencies(initialize ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

else()
#==================================== ROS2 ==================================
  message("Version : ROS2")

  find_package(ament_cmake REQUIRED)
  find_package(rclcpp REQUIRED)
  find_package(rclpy REQUIRED)
  find_package(std_msgs REQUIRED)
  find_package(geometry_msgs REQUIRED)
  find_package(tf2 REQUIRED)
  find_package(tf2_ros REQUIRED)
  find_package(cv_bridge REQUIRED)
  find_package(OpenCV 4.2.0 REQUIRED)
  find_package(Eigen3 REQUIRED)
  find_package(rosidl_default_generators REQUIRED)
  find_package(msgs REQUIRED)

  include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${tf2_INCLUDE_DIRS}
  )
  add_definitions(${EIGEN_DEFINITIONS})

  add_library(ftservo_Control SHARED src/FEETECHservo.cpp)
  ament_target_dependencies(ftservo_Control
    rclcpp
    std_msgs
    tf2
    cv_bridge
    geometry_msgs
    tf2_ros
  )

  add_library(math_tools_lib SHARED src/math_tools.cpp)
  ament_target_dependencies(math_tools_lib
    rclcpp
    std_msgs
    tf2
    cv_bridge
    geometry_msgs
    tf2_ros
  )

  add_library(singleServoControl SHARED src/singleServoControl.cpp)
  ament_target_dependencies(singleServoControl
    rclcpp
    std_msgs
    tf2
    cv_bridge
    geometry_msgs
    tf2_ros
    msgs
  )
  target_link_libraries(singleServoControl
    ftservo_Control
    math_tools_lib
    ${PROJECT_SOURCE_DIR}/include/SCServo/lib_x86/libSCServo.so #x86
  )

  add_library(multiServoControl SHARED src/multiServoControl.cpp)
  ament_target_dependencies(multiServoControl
    rclcpp
    std_msgs
    tf2
    cv_bridge
    geometry_msgs
    tf2_ros
    msgs
  )
  target_link_libraries(multiServoControl
    singleServoControl
    ftservo_Control
    math_tools_lib
    ${PROJECT_SOURCE_DIR}/include/SCServo/lib_x86/libSCServo.so #x86
  )

  add_executable(WritePos src/WritePos.cpp)
  ament_target_dependencies(WritePos rclcpp std_msgs tf2 cv_bridge)
  target_link_libraries(WritePos
    ftservo_Control
    ${PROJECT_SOURCE_DIR}/include/SCServo/lib_x86/libSCServo.so #x86
  )

  add_executable(initialize src/initialize.cpp)
  ament_target_dependencies(initialize rclcpp std_msgs tf2 cv_bridge)
  target_link_libraries(initialize
    ftservo_Control
    ${PROJECT_SOURCE_DIR}/include/SCServo/lib_x86/libSCServo.so #x86
  )

  add_executable(Single_Servogp_Control src/Single_Servogp_Control.cpp)
  ament_target_dependencies(Single_Servogp_Control rclcpp std_msgs tf2 cv_bridge)
  target_link_libraries(Single_Servogp_Control
    singleServoControl
  )

  add_executable(Multi_Servogp_Control src/Multi_Servogp_Control.cpp)
  ament_target_dependencies(Multi_Servogp_Control rclcpp std_msgs tf2 cv_bridge)
  target_link_libraries(Multi_Servogp_Control
    multiServoControl
  )


  install(
    DIRECTORY include/SCServo/lib_x86/
    DESTINATION lib
  )

  install(TARGETS 
    singleServoControl
    multiServoControl
    ftservo_Control
    math_tools_lib
    WritePos
    initialize
    Single_Servogp_Control
    Multi_Servogp_Control
    RUNTIME DESTINATION lib/${PROJECT_NAME}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
  )

  install(DIRECTORY 
    launch
    DESTINATION share/${PROJECT_NAME}
  )

  if(BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    ament_lint_auto_find_test_dependencies()
  endif()

  ament_package()

endif()









