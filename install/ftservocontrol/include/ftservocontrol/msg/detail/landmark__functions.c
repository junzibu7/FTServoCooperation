// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ftservocontrol:msg/Landmark.idl
// generated code does not contain a copyright notice
#include "ftservocontrol/msg/detail/landmark__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `x`
// Member `y`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
ftservocontrol__msg__Landmark__init(ftservocontrol__msg__Landmark * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    ftservocontrol__msg__Landmark__fini(msg);
    return false;
  }
  // x
  if (!rosidl_runtime_c__float__Sequence__init(&msg->x, 0)) {
    ftservocontrol__msg__Landmark__fini(msg);
    return false;
  }
  // y
  if (!rosidl_runtime_c__float__Sequence__init(&msg->y, 0)) {
    ftservocontrol__msg__Landmark__fini(msg);
    return false;
  }
  return true;
}

void
ftservocontrol__msg__Landmark__fini(ftservocontrol__msg__Landmark * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // x
  rosidl_runtime_c__float__Sequence__fini(&msg->x);
  // y
  rosidl_runtime_c__float__Sequence__fini(&msg->y);
}

bool
ftservocontrol__msg__Landmark__are_equal(const ftservocontrol__msg__Landmark * lhs, const ftservocontrol__msg__Landmark * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // x
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->x), &(rhs->x)))
  {
    return false;
  }
  // y
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->y), &(rhs->y)))
  {
    return false;
  }
  return true;
}

bool
ftservocontrol__msg__Landmark__copy(
  const ftservocontrol__msg__Landmark * input,
  ftservocontrol__msg__Landmark * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // x
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->x), &(output->x)))
  {
    return false;
  }
  // y
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->y), &(output->y)))
  {
    return false;
  }
  return true;
}

ftservocontrol__msg__Landmark *
ftservocontrol__msg__Landmark__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ftservocontrol__msg__Landmark * msg = (ftservocontrol__msg__Landmark *)allocator.allocate(sizeof(ftservocontrol__msg__Landmark), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ftservocontrol__msg__Landmark));
  bool success = ftservocontrol__msg__Landmark__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ftservocontrol__msg__Landmark__destroy(ftservocontrol__msg__Landmark * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ftservocontrol__msg__Landmark__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ftservocontrol__msg__Landmark__Sequence__init(ftservocontrol__msg__Landmark__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ftservocontrol__msg__Landmark * data = NULL;

  if (size) {
    data = (ftservocontrol__msg__Landmark *)allocator.zero_allocate(size, sizeof(ftservocontrol__msg__Landmark), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ftservocontrol__msg__Landmark__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ftservocontrol__msg__Landmark__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
ftservocontrol__msg__Landmark__Sequence__fini(ftservocontrol__msg__Landmark__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ftservocontrol__msg__Landmark__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

ftservocontrol__msg__Landmark__Sequence *
ftservocontrol__msg__Landmark__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ftservocontrol__msg__Landmark__Sequence * array = (ftservocontrol__msg__Landmark__Sequence *)allocator.allocate(sizeof(ftservocontrol__msg__Landmark__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ftservocontrol__msg__Landmark__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ftservocontrol__msg__Landmark__Sequence__destroy(ftservocontrol__msg__Landmark__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ftservocontrol__msg__Landmark__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ftservocontrol__msg__Landmark__Sequence__are_equal(const ftservocontrol__msg__Landmark__Sequence * lhs, const ftservocontrol__msg__Landmark__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ftservocontrol__msg__Landmark__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ftservocontrol__msg__Landmark__Sequence__copy(
  const ftservocontrol__msg__Landmark__Sequence * input,
  ftservocontrol__msg__Landmark__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ftservocontrol__msg__Landmark);
    ftservocontrol__msg__Landmark * data =
      (ftservocontrol__msg__Landmark *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ftservocontrol__msg__Landmark__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          ftservocontrol__msg__Landmark__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ftservocontrol__msg__Landmark__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
