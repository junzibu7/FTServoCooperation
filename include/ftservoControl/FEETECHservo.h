/*
 * @Author: hx2020hx 1215399660@qq.com
 * @Date: 2024-02-28 09:42:51
 * @LastEditors: 黄先 1215399660@qq.com
 * @LastEditTime: 2024-03-05 13:15:35
 * @FilePath: /test_ws/src/ftservoControl/include/ftservoControl/FEETECHservo.h
 * @Description: API for FEETECHServo contol
 */

#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include "ftservoControl/SCServo.h"

class ftServo
{
public:
    ftServo() {}
    ~ftServo() { sm_st.end(); }
    /**
     * @description: initialize the servo
     * @param {char*} serial:serial string such as "/dev/ttyUSB0"
     * @param {int} num_servos
     * @param {NodeHandle} &nh
     * @return {*}
     */
    void init(const char *serial, int num_servos, rclcpp::Node::SharedPtr &nh);
    /**
     * @description: initialize the servo
     * @param {char*} serial:serial string such as "/dev/ttyUSB0"
     * @param {int} num_servos
     * @param {NodeHandle} &nh
     * @param {vector<int>} ID_list
     * @return {*}
     */
    void init(const char *serial, int num_servos, rclcpp::Node::SharedPtr &nh, std::vector<int> ID_list);
    /**
     * @description: move servo to angle
     * @param {double} angle
     * @param {int} id
     * @param {double} speed
     * @return {*}
     */
    void move(double angle, int id, double speed = 2400);
    /**
     * @description: read id-th servo angle
     * @param {int} id
     * @return {double} id-th servo angle
     */
    double read(int id);
    /**
     * @description: reset id-th servo's angle to 180 deg
     * @param {int} id
     * @return {*}
     */
    void reset(int id);
    /**
     * @description: rename id-th servo id to modified_id
     * @param {int} id
     * @param {int} modified_id
     * @return {*}
     */
    void rename(int id, int modified_id);
    /**
     * @description: ping id-th servo in order to check if 'id' pairs with the servo
     * @param {int} id
     * @return {*}
     */
    bool ping(int id);

private:
    SMS_STS sm_st;
    std::vector<double> target_angle;
    std::vector<double> current_angle;
    std::vector<int> current_speed;
    std::vector<int> id_list;
    rclcpp::TimerBase::SharedPtr update_timer;
    rclcpp::Node::SharedPtr nh_;
    int num;

    int angleTrans(double angle) { return static_cast<int>(angle * 2048 / 180); }
    double stepTrans(int step) { return static_cast<double>(step) * 0.08789; }
    bool find_id(int id, int &index);

    /**
     * @description: continuous update of servo state
     * @param {rclcpp::TimerEvent} &
     * @return {*}
     */
    // void update_servo_state(const rclcpp::TimerEvent &);
    void update_servo_state();
};