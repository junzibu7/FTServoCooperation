// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ftservocontrol:msg/Landmark.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ftservocontrol/msg/detail/landmark__rosidl_typesupport_introspection_c.h"
#include "ftservocontrol/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ftservocontrol/msg/detail/landmark__functions.h"
#include "ftservocontrol/msg/detail/landmark__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `x`
// Member `y`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void Landmark__rosidl_typesupport_introspection_c__Landmark_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ftservocontrol__msg__Landmark__init(message_memory);
}

void Landmark__rosidl_typesupport_introspection_c__Landmark_fini_function(void * message_memory)
{
  ftservocontrol__msg__Landmark__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember Landmark__rosidl_typesupport_introspection_c__Landmark_message_member_array[3] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ftservocontrol__msg__Landmark, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ftservocontrol__msg__Landmark, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ftservocontrol__msg__Landmark, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers Landmark__rosidl_typesupport_introspection_c__Landmark_message_members = {
  "ftservocontrol__msg",  // message namespace
  "Landmark",  // message name
  3,  // number of fields
  sizeof(ftservocontrol__msg__Landmark),
  Landmark__rosidl_typesupport_introspection_c__Landmark_message_member_array,  // message members
  Landmark__rosidl_typesupport_introspection_c__Landmark_init_function,  // function to initialize message memory (memory has to be allocated)
  Landmark__rosidl_typesupport_introspection_c__Landmark_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t Landmark__rosidl_typesupport_introspection_c__Landmark_message_type_support_handle = {
  0,
  &Landmark__rosidl_typesupport_introspection_c__Landmark_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ftservocontrol
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ftservocontrol, msg, Landmark)() {
  Landmark__rosidl_typesupport_introspection_c__Landmark_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!Landmark__rosidl_typesupport_introspection_c__Landmark_message_type_support_handle.typesupport_identifier) {
    Landmark__rosidl_typesupport_introspection_c__Landmark_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &Landmark__rosidl_typesupport_introspection_c__Landmark_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
