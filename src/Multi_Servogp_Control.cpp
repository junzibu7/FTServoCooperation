#include <ftservocontrol/multiServoControl.h>

using namespace std;
using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    // Create node
    auto MulSC_node = std::make_shared<MultiServoNode>("MultiServoControl");
    

    while(rclcpp::ok())
    {
        
        rclcpp::spin_some(MulSC_node);
    }
    rclcpp::shutdown();
    return 0;
}
