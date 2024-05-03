// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from ftservocontrol:msg/Landmark.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "ftservocontrol/msg/detail/landmark__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace ftservocontrol
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Landmark_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) ftservocontrol::msg::Landmark(_init);
}

void Landmark_fini_function(void * message_memory)
{
  auto typed_message = static_cast<ftservocontrol::msg::Landmark *>(message_memory);
  typed_message->~Landmark();
}

size_t size_function__Landmark__x(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Landmark__x(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__Landmark__x(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void resize_function__Landmark__x(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__Landmark__y(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Landmark__y(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__Landmark__y(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void resize_function__Landmark__y(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Landmark_message_member_array[3] = {
  {
    "header",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<std_msgs::msg::Header>(),  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ftservocontrol::msg::Landmark, header),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "x",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ftservocontrol::msg::Landmark, x),  // bytes offset in struct
    nullptr,  // default value
    size_function__Landmark__x,  // size() function pointer
    get_const_function__Landmark__x,  // get_const(index) function pointer
    get_function__Landmark__x,  // get(index) function pointer
    resize_function__Landmark__x  // resize(index) function pointer
  },
  {
    "y",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ftservocontrol::msg::Landmark, y),  // bytes offset in struct
    nullptr,  // default value
    size_function__Landmark__y,  // size() function pointer
    get_const_function__Landmark__y,  // get_const(index) function pointer
    get_function__Landmark__y,  // get(index) function pointer
    resize_function__Landmark__y  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Landmark_message_members = {
  "ftservocontrol::msg",  // message namespace
  "Landmark",  // message name
  3,  // number of fields
  sizeof(ftservocontrol::msg::Landmark),
  Landmark_message_member_array,  // message members
  Landmark_init_function,  // function to initialize message memory (memory has to be allocated)
  Landmark_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Landmark_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Landmark_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace ftservocontrol


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<ftservocontrol::msg::Landmark>()
{
  return &::ftservocontrol::msg::rosidl_typesupport_introspection_cpp::Landmark_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, ftservocontrol, msg, Landmark)() {
  return &::ftservocontrol::msg::rosidl_typesupport_introspection_cpp::Landmark_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
