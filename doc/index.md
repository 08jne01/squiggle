# Squiggle

## Introduction

Squiggle is a C++20 vector, matrix and quaternion library. It is heavily inspired by the awesome [boost library qvm](https://github.com/boostorg/qvm).

Like boost qvm this library allows compatibility with user types via non-intrusive trait specification. This is very useful if you are working with several other libraries each with their own vector type for more see the [concepts](./concepts.md) page.

The primary motivation for this additional library was to create a modern vector, matrix and quaternion library which makes use of concepts for faster build times and reduced code complexity.

This library is aimed at game-developement and physics simulation. As such only 2,3,4 dimension vectors and square matricies are implemented, along with quaternions.

## Features

- Free functions which operate on concepts only
- Easily extend user defined types to work as compatible, vector, matrix or quaternion
- Uses C++20 concepts to reduce compile times and code complexity
- Constexpr where possible (constexpr trig functions coming in C++26)

## Example

```cpp
// Simple Operations
sqg::vec3f v0;
sqg::vec3f v1;
sqg::vec3f v2;

sqg::vec3f v4 = v0 + v1 - v2;
v4 *= 10.0f;
v4 /= 10.0f;

v0 = v4 / 10.0f;
```

```cpp
// Matrix Operations
mat33f m = sqg::identity_mat<float,3>();
const sqg::vec3f x = { 1.0f, 0.0f, 0.0f };
const sqg::vec3f y = { 1.0f, 0.0f, 1.0f };

sqg::col<0>(m) = x; // set column 1 of m to vector x
sqg::col<1>(m) = y; // set column 1 of m to vector y

// pass a transpose view of matrix m to the function
// not copies happen here
const float det_m = sqg::determinant( sqg::transposed(m) )

```

```cpp
// Quaternions
void rotate_camera(sqg::vec3f& direction, const sqg::vec3f& up, const sqg::vec2f mouse)
{
    const sqg::vec3f pitch_axis = sqg::cross(up, direction);
    const sqg::quatf pitch_rotation = sqg::rot_quat(pitch_axis, mouse.y);
    
    direction = pitch_rotation * direction;

    const sqg::quatf yaw_rotation = sqg::rot_quat(up, mouse.x);
    direction = yaw_rotation * direction;
}
```

```cpp
sqg::mat33f orientation;
sqg::vec3f position;

sqg::mat44f transform = sqg::identity_mat<float,4>();

// get views of upper 3x3 and vec3 view of column 3 (zero indexed)
sqg::orientation(transform) = orientation;
sqg::position(transform) = position;

sqg::vec3f local_point;
// transform local point to world space
// local_point is converted to vec4 view with 1 as last component for transformation
sqg::vec3f world_point = transform * local_point;

```

## Other More Established Libraries

- [boost qvm](https://github.com/boostorg/qvm)
- [GLM](https://github.com/icaven/glm)
- [Eigen](https://github.com/PX4/eigen/tree/3.4) for heavier linear algebra requirements
