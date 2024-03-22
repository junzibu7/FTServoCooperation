cmake_minimum_required(VERSION 3.0.2)
project(ftservoControl)
set(CMAKE_CXX_FLAGS "-fPIC")
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
  std_msgs
  geometry_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ftservoControl
  CATKIN_DEPENDS roscpp rospy std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(ftservoControl
  src/FEETECHservo.cpp
)

target_link_libraries( ftservoControl
    ${catkin_LIBRARIES} 
    # ${PROJECT_SOURCE_DIR}/include/ftservoControl/lib_arm/libSCServo.so #nvidia
    ${PROJECT_SOURCE_DIR}/include/ftservoControl/lib_x86/libSCServo.so #laptop
    )  

add_executable(WritePos src/WritePos.cpp)
target_link_libraries(WritePos
  ${catkin_LIBRARIES}
  ftservoControl
  # ${PROJECT_SOURCE_DIR}/include/ftservoControl/lib_arm/libSCServo.so #nvidia
  ${PROJECT_SOURCE_DIR}/include/ftservoControl/lib_x86/libSCServo.so #laptop
 )
add_dependencies(WritePos ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

# add_executable(servoControl src/servoControl.cpp)
# target_link_libraries(servoControl
#   ${catkin_LIBRARIES}
#   ${PROJECT_SOURCE_DIR}/include/ftservoControl/libSCServo.a
#  )
# add_dependencies(servoControl ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(initialize src/initialize.cpp)
target_link_libraries(initialize
  ${catkin_LIBRARIES}
  ftservoControl
  # ${PROJECT_SOURCE_DIR}/include/ftservoControl/lib_arm/libSCServo.so #nvidia
  ${PROJECT_SOURCE_DIR}/include/ftservoControl/lib_x86/libSCServo.so #laptop
 )
add_dependencies(initialize ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(singleServoControl src/singleServoControl.cpp)
target_link_libraries(singleServoControl
  ${catkin_LIBRARIES}
  ftservoControl
  # ${PROJECT_SOURCE_DIR}/include/ftservoControl/lib_arm/libSCServo.so #nvidia
  ${PROJECT_SOURCE_DIR}/include/ftservoControl/lib_x86/libSCServo.so #laptop
 )
add_dependencies(initialize ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})