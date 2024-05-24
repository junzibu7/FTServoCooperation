#include "rclcpp/rclcpp.hpp"

#include <tf2/LinearMath/Transform.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <tf2_eigen/tf2_eigen.h>
#include <tf2_ros/buffer.h>

#include <Eigen/Eigen>
#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/quaternion_stamped.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>

#include <cstdlib>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <queue>
#include <vector>
#include <chrono>
#include <sstream>

using namespace std::chrono_literals;
using namespace std;

class TargetTrajectorySimulation : public rclcpp::Node
{
public:
    TargetTrajectorySimulation() : Node("TargetTrajectorySimulation")
    {
        timer_ = this->create_wall_timer(std::chrono::milliseconds(33), std::bind(&TargetTrajectorySimulation::publish_trajectory, this));
        trajectory_publisher = this->create_publisher<geometry_msgs::msg::TransformStamped>("trajectory", 1);
        trajectory = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    }

    void publish_trajectory()
    {
        // 生成轨迹
        // circle_trajectory(0, 0, 0);
        // eight_trajectory(0, 0, 0);
        preset_trajectory();

        // 发布 base 到 target 的变换
        msg_base_to_target.header.stamp = this->now();
        msg_base_to_target.header.frame_id = "base";
        msg_base_to_target.child_frame_id = "target";
        q.setRPY(0, 0, 0);
        msg_base_to_target.transform.translation.x = target_position.x();
        msg_base_to_target.transform.translation.y = target_position.y();
        msg_base_to_target.transform.translation.z = target_position.z();
        msg_base_to_target.transform.rotation = tf2::toMsg(q);

        trajectory_publisher->publish(msg_base_to_target);
        trajectory->sendTransform(msg_base_to_target);
    }

    // 生成圆形轨迹
    void circle_trajectory(double x_init, double y_init, double z_init)
    {
        double radius = 0.6;
        static double count = 0.0;
        double d_count = M_PI / 3600;
        target_position.x() = radius * cos(count) + x_init;
        target_position.y() = radius * sin(count) + y_init;
        target_position.z() = 0.4 + z_init;
        count += d_count * 10;
        if(count > 2*M_PI)
        {
            count = 0.0;
        }
    }

    // 生成8字形轨迹
    void eight_trajectory(double x_init, double y_init, double z_init)
    {
        double radius = 0.5;
        static double count = 0.0;
        double d_count = M_PI / 3600;
        target_position.x() = radius * cos(count) + 1 + x_init;
        target_position.y() = radius * sin(count) * cos(count) + y_init;
        target_position.z() = 0.5 + 0.2 * sin(count) + z_init;
        count += d_count * 10;
        if(count > 2 * M_PI)
        {
            count = 0.0;
        }
    }

    // 生成工作预设轨迹
    void preset_trajectory()
    {
        static double COUNT = 0.0;
        // 直线抬高
        if(COUNT < 10000.0 / 33.0)
        {
            target_position.x() = 0;
            target_position.y() = 0;
            target_position.z() += 0.5 / (10000.0 / 33.0);
            COUNT++;
        }
        // 悬停
        else if((COUNT < 15000.0 / 33.0) && (COUNT >= 10000.0 / 33.0))
        {
            target_position.x() += 0;
            target_position.y() += 0;
            target_position.z() += 0;
            COUNT++;
        }
        // 直线到达目标位置
        else if((COUNT < 50000.0 / 33.0) && (COUNT >= 15000.0 / 33.0))
        {
            target_position.x() += 5.0 / (30000.0 / 33.0);
            target_position.y() += 0;
            target_position.z() += 3.5 / (30000.0 / 33.0);
            COUNT++;
        }
        // 生成圆形轨迹
        else if(COUNT >= 50000 / 33)
        {
            circle_trajectory(5, 0, 4);
        }
    }

    // Parameters
    rclcpp::Publisher<geometry_msgs::msg::TransformStamped>::SharedPtr trajectory_publisher;
    std::shared_ptr<tf2_ros::TransformBroadcaster> trajectory;
    geometry_msgs::msg::TransformStamped msg_base_to_target;
    rclcpp::TimerBase::SharedPtr timer_;

    // tf parameters
    tf2::Quaternion q;
    Eigen::Vector3d target_position = Eigen::Vector3d(0.0, 0.0, 0.0);
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto trajectory_node = std::make_shared<TargetTrajectorySimulation>();

    rclcpp::spin(trajectory_node);
    rclcpp::shutdown();
    return 0;
}