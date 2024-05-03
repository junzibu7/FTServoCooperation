// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from ftservocontrol:msg/Landmark.idl
// generated code does not contain a copyright notice

#ifndef FTSERVOCONTROL__MSG__DETAIL__LANDMARK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define FTSERVOCONTROL__MSG__DETAIL__LANDMARK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "ftservocontrol/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "ftservocontrol/msg/detail/landmark__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace ftservocontrol
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ftservocontrol
cdr_serialize(
  const ftservocontrol::msg::Landmark & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ftservocontrol
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  ftservocontrol::msg::Landmark & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ftservocontrol
get_serialized_size(
  const ftservocontrol::msg::Landmark & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ftservocontrol
max_serialized_size_Landmark(
  bool & full_bounded,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace ftservocontrol

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_ftservocontrol
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, ftservocontrol, msg, Landmark)();

#ifdef __cplusplus
}
#endif

#endif  // FTSERVOCONTROL__MSG__DETAIL__LANDMARK__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
