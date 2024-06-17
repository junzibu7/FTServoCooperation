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

using namespace std::chrono_literals;
using namespace std;

class Base2ServoGPBroadcaster : public rclcpp::Node
{
public:
    Base2ServoGPBroadcaster() : Node("base2servogp_broadcaster")
    {
        timer_ = this->create_wall_timer(std::chrono::milliseconds(33), std::bind(&Base2ServoGPBroadcaster::publish_transforms, this));
        base_to_servogroup12_publisher = this->create_publisher<geometry_msgs::msg::TransformStamped>("T_base_to_servogroup12", 1);
        base_to_servogroup34_publisher = this->create_publisher<geometry_msgs::msg::TransformStamped>("T_base_to_servogroup34", 1);
        base_to_servogroup56_publisher = this->create_publisher<geometry_msgs::msg::TransformStamped>("T_base_to_servogroup56", 1);
        base_to_servogroup78_publisher = this->create_publisher<geometry_msgs::msg::TransformStamped>("T_base_to_servogroup78", 1);
        base_to_servogroup12 = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
        base_to_servogroup34 = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
        base_to_servogroup56 = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
        base_to_servogroup78 = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    }

    void publish_transforms()
    {
        // 发布 base 到 servogroup12 的变换
        stamped_base_to_servogroup12.header.stamp = this->now();
        stamped_base_to_servogroup12.header.frame_id = "base";
        stamped_base_to_servogroup12.child_frame_id = "servogroup12";
        q.setRPY(0, 5*M_PI/180, (27.54+4.227)*M_PI/180.0);
        stamped_base_to_servogroup12.transform.translation.x = -0.951+1.07;
        stamped_base_to_servogroup12.transform.translation.y = -0.693+0.772;
        stamped_base_to_servogroup12.transform.translation.z = -0.2;
        stamped_base_to_servogroup12.transform.rotation = tf2::toMsg(q);

        // 发布 base 到 servogroup34 的变换
        stamped_base_to_servogroup34.header.stamp = this->now();
        stamped_base_to_servogroup34.header.frame_id = "base";
        stamped_base_to_servogroup34.child_frame_id = "servogroup34";
        q.setRPY(0, 0, (-40.1+4.227)*M_PI/180.0);
        stamped_base_to_servogroup34.transform.translation.x = -0.801+1.07;
        stamped_base_to_servogroup34.transform.translation.y = 0.876+0.772;
        stamped_base_to_servogroup34.transform.translation.z = -0.2;
        stamped_base_to_servogroup34.transform.rotation = tf2::toMsg(q);

        // 发布 base 到 servogroup56 的变换
        stamped_base_to_servogroup56.header.stamp = this->now();
        stamped_base_to_servogroup56.header.frame_id = "base";
        stamped_base_to_servogroup56.child_frame_id = "servogroup56";
        q.setRPY(0, -5*M_PI/180, (213.3+4.227)*M_PI/180.0);
        stamped_base_to_servogroup56.transform.translation.x = 0.886+1.07;
        stamped_base_to_servogroup56.transform.translation.y = 0.778+0.772;
        stamped_base_to_servogroup56.transform.translation.z = -0.2;
        stamped_base_to_servogroup56.transform.rotation = tf2::toMsg(q);

        // 发布 base 到 servogroup78 的变换
        stamped_base_to_servogroup78.header.stamp = this->now();
        stamped_base_to_servogroup78.header.frame_id = "base";
        stamped_base_to_servogroup78.child_frame_id = "servogroup78";
        q.setRPY(0, 0, (141+4.227)*M_PI/180.0);
        stamped_base_to_servogroup78.transform.translation.x = 0.805+1.07;
        stamped_base_to_servogroup78.transform.translation.y = -0.867+0.772;
        stamped_base_to_servogroup78.transform.translation.z = -0.2;
        stamped_base_to_servogroup78.transform.rotation = tf2::toMsg(q);

        base_to_servogroup12_publisher->publish(stamped_base_to_servogroup12);
        base_to_servogroup34_publisher->publish(stamped_base_to_servogroup34);
        base_to_servogroup56_publisher->publish(stamped_base_to_servogroup56);
        base_to_servogroup78_publisher->publish(stamped_base_to_servogroup78);
        
        // 使用 tf2_ros::TransformBroadcaster 发布变换
        base_to_servogroup12->sendTransform(stamped_base_to_servogroup12);
        base_to_servogroup34->sendTransform(stamped_base_to_servogroup34);
        base_to_servogroup56->sendTransform(stamped_base_to_servogroup56);
        base_to_servogroup78->sendTransform(stamped_base_to_servogroup78);
    }

    // tf2 
    rclcpp::Publisher<geometry_msgs::msg::TransformStamped>::SharedPtr base_to_servogroup12_publisher;
    rclcpp::Publisher<geometry_msgs::msg::TransformStamped>::SharedPtr base_to_servogroup34_publisher;
    rclcpp::Publisher<geometry_msgs::msg::TransformStamped>::SharedPtr base_to_servogroup56_publisher;
    rclcpp::Publisher<geometry_msgs::msg::TransformStamped>::SharedPtr base_to_servogroup78_publisher;
    std::shared_ptr<tf2_ros::TransformBroadcaster> base_to_servogroup12;
    std::shared_ptr<tf2_ros::TransformBroadcaster> base_to_servogroup34;
    std::shared_ptr<tf2_ros::TransformBroadcaster> base_to_servogroup56;
    std::shared_ptr<tf2_ros::TransformBroadcaster> base_to_servogroup78;
    rclcpp::TimerBase::SharedPtr timer_;

    tf2::Quaternion q;
    tf2::Vector3 t;

    geometry_msgs::msg::TransformStamped stamped_base_to_servogroup12;
    geometry_msgs::msg::TransformStamped stamped_base_to_servogroup34; 
    geometry_msgs::msg::TransformStamped stamped_base_to_servogroup56;
    geometry_msgs::msg::TransformStamped stamped_base_to_servogroup78;

};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto base2servogroup_node = std::make_shared<Base2ServoGPBroadcaster>();
  rclcpp::spin(base2servogroup_node);
  rclcpp::shutdown();
  return 0;
}