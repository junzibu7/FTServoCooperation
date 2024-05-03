// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ftservocontrol:msg/Landmark.idl
// generated code does not contain a copyright notice

#ifndef FTSERVOCONTROL__MSG__DETAIL__LANDMARK__BUILDER_HPP_
#define FTSERVOCONTROL__MSG__DETAIL__LANDMARK__BUILDER_HPP_

#include "ftservocontrol/msg/detail/landmark__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace ftservocontrol
{

namespace msg
{

namespace builder
{

class Init_Landmark_y
{
public:
  explicit Init_Landmark_y(::ftservocontrol::msg::Landmark & msg)
  : msg_(msg)
  {}
  ::ftservocontrol::msg::Landmark y(::ftservocontrol::msg::Landmark::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ftservocontrol::msg::Landmark msg_;
};

class Init_Landmark_x
{
public:
  explicit Init_Landmark_x(::ftservocontrol::msg::Landmark & msg)
  : msg_(msg)
  {}
  Init_Landmark_y x(::ftservocontrol::msg::Landmark::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Landmark_y(msg_);
  }

private:
  ::ftservocontrol::msg::Landmark msg_;
};

class Init_Landmark_header
{
public:
  Init_Landmark_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Landmark_x header(::ftservocontrol::msg::Landmark::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Landmark_x(msg_);
  }

private:
  ::ftservocontrol::msg::Landmark msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ftservocontrol::msg::Landmark>()
{
  return ftservocontrol::msg::builder::Init_Landmark_header();
}

}  // namespace ftservocontrol

#endif  // FTSERVOCONTROL__MSG__DETAIL__LANDMARK__BUILDER_HPP_
