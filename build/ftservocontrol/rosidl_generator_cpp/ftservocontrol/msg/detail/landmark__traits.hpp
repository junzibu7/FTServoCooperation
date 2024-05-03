// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ftservocontrol:msg/Landmark.idl
// generated code does not contain a copyright notice

#ifndef FTSERVOCONTROL__MSG__DETAIL__LANDMARK__TRAITS_HPP_
#define FTSERVOCONTROL__MSG__DETAIL__LANDMARK__TRAITS_HPP_

#include "ftservocontrol/msg/detail/landmark__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ftservocontrol::msg::Landmark>()
{
  return "ftservocontrol::msg::Landmark";
}

template<>
inline const char * name<ftservocontrol::msg::Landmark>()
{
  return "ftservocontrol/msg/Landmark";
}

template<>
struct has_fixed_size<ftservocontrol::msg::Landmark>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ftservocontrol::msg::Landmark>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ftservocontrol::msg::Landmark>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // FTSERVOCONTROL__MSG__DETAIL__LANDMARK__TRAITS_HPP_
