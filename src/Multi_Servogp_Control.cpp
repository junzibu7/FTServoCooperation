#include <ftservocontrol/singleServoControl.h>

using namespace std;
using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    // Create four nodes
    auto Sg12_node = std::make_shared<SingleServoNode>("ServoGroup12");
    Sg12_node->init(Sg12_node);
    auto Sg34_node = std::make_shared<SingleServoNode>("ServoGroup34");
    Sg34_node->init(Sg34_node);
    // auto Sg56_node = std::make_shared<SingleServoNode>();
    // auto Sg78_node = std::make_shared<SingleServoNode>();
    

    while(rclcpp::ok())
    {
        Sg12_node->T_servogroup_to_camera();
        Sg34_node->T_servogroup_to_camera();
        // Sg56_node->T_servogroup_to_camera();
        // Sg78_node->T_servogroup_to_camera();

        rclcpp::spin_some(Sg12_node);
        rclcpp::spin_some(Sg34_node);
        // rclcpp::spin_some(Sg56_node);
        // rclcpp::spin_some(Sg78_node);

        // std::this_thread::sleep_for(0.1s);
    }
    // rclcpp::spin(Sg12_node);
    // rclcpp::shutdown();
    return 0;
}
