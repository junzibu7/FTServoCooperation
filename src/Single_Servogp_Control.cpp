#include <ftservocontrol/singleServoControl.h>

using namespace std;
using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    // Create node
    auto Sg_node = std::make_shared<SingleServoNode>("ServoGroup");
    Sg_node->init(Sg_node);
    

    while(rclcpp::ok())
    {

        rclcpp::spin_some(Sg_node);

        // std::this_thread::sleep_for(0.1s);
    }
    // rclcpp::spin(Sg12_node);
    // rclcpp::shutdown();
    return 0;
}
