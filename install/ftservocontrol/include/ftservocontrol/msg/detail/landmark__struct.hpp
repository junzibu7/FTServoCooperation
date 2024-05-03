// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ftservocontrol:msg/Landmark.idl
// generated code does not contain a copyright notice

#ifndef FTSERVOCONTROL__MSG__DETAIL__LANDMARK__STRUCT_HPP_
#define FTSERVOCONTROL__MSG__DETAIL__LANDMARK__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__ftservocontrol__msg__Landmark __attribute__((deprecated))
#else
# define DEPRECATED__ftservocontrol__msg__Landmark __declspec(deprecated)
#endif

namespace ftservocontrol
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Landmark_
{
  using Type = Landmark_<ContainerAllocator>;

  explicit Landmark_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit Landmark_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _x_type =
    std::vector<float, typename ContainerAllocator::template rebind<float>::other>;
  _x_type x;
  using _y_type =
    std::vector<float, typename ContainerAllocator::template rebind<float>::other>;
  _y_type y;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__x(
    const std::vector<float, typename ContainerAllocator::template rebind<float>::other> & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const std::vector<float, typename ContainerAllocator::template rebind<float>::other> & _arg)
  {
    this->y = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ftservocontrol::msg::Landmark_<ContainerAllocator> *;
  using ConstRawPtr =
    const ftservocontrol::msg::Landmark_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ftservocontrol::msg::Landmark_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ftservocontrol::msg::Landmark_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ftservocontrol::msg::Landmark_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ftservocontrol::msg::Landmark_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ftservocontrol::msg::Landmark_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ftservocontrol::msg::Landmark_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ftservocontrol::msg::Landmark_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ftservocontrol::msg::Landmark_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ftservocontrol__msg__Landmark
    std::shared_ptr<ftservocontrol::msg::Landmark_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ftservocontrol__msg__Landmark
    std::shared_ptr<ftservocontrol::msg::Landmark_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Landmark_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    return true;
  }
  bool operator!=(const Landmark_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Landmark_

// alias to use template instance with default allocator
using Landmark =
  ftservocontrol::msg::Landmark_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ftservocontrol

#endif  // FTSERVOCONTROL__MSG__DETAIL__LANDMARK__STRUCT_HPP_
