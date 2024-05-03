// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ftservocontrol:msg/Landmark.idl
// generated code does not contain a copyright notice

#ifndef FTSERVOCONTROL__MSG__DETAIL__LANDMARK__STRUCT_H_
#define FTSERVOCONTROL__MSG__DETAIL__LANDMARK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'x'
// Member 'y'
#include "rosidl_runtime_c/primitives_sequence.h"

// Struct defined in msg/Landmark in the package ftservocontrol.
typedef struct ftservocontrol__msg__Landmark
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__float__Sequence x;
  rosidl_runtime_c__float__Sequence y;
} ftservocontrol__msg__Landmark;

// Struct for a sequence of ftservocontrol__msg__Landmark.
typedef struct ftservocontrol__msg__Landmark__Sequence
{
  ftservocontrol__msg__Landmark * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ftservocontrol__msg__Landmark__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // FTSERVOCONTROL__MSG__DETAIL__LANDMARK__STRUCT_H_
