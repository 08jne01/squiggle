# Coordinates

It is useful to convert between different coordinate conventions. This could be the physics engine works in one coordinate system but your internal code works in another. Squiggle provides a way to do this for a set of common coordinate systems.

## Systems

Each system is described in terms of three directions representing the x,y and z axes respectively. While they are described in terms of [tangent plane coordinates](https://en.wikipedia.org/wiki/Local_tangent_plane_coordinates) this is just for convenience and they can refer to world or body coordinates.

Below is common conversion from the directions in tangent:

| Tangent Plane Direction | Local Direction Equivalent
|-------------------------|----------------------------
| North                   | Forward
| South                   | Backward
| East                    | Right
| West                    | Left
| Down                    | Down
| Up                      | Up

Ultimately it is up to you to decide the meanings of your coordinate systems, this is just here to serve as a general guide.

### North,Up,East (NUE)

+x -> forward (north)
+y -> up
+z -> right (east)

+x rotation -> roll right
+y rotation -> pitch up
+z rotation -> yaw left

### North West Up (NWU)

+x -> forward (north)
+y -> left (west)
+z -> up

+x rotation -> roll right
+y rotation -> pitch down
+z rotation -> yaw left

### North East Down (NED)

+x -> forward (north)
+y -> right (east)
+z -> down

+x rotation -> roll right
+y rotation -> pitch up
+z rotation -> yaw right

## Example and Motivation

Consider a vector `v_ned = { 1, 0, 1 }` defined in NED coordinates. In NED coordinates this vector is pointing forwards and down. The equivalent vector in NUE coordinates is `v_nue = { 1, -1, 0 }`. Note the y and z coordinates are swapped and the z is negative. They both represent the same point in space just how they are defined is different. To get the same result in code is very simple

```cpp
v_nue = NEDtoNUE(v_ned);
```

The same applies to rotations however it becomes a lot more tricky. Consider a +rotation around the down axis (+z) in NED since the axis is down using the right hand rule (since NED are a right handed coordinate system) we find that a positive rotation moves east from the north (+x) vector. If we wanted to convert this matrix/quaternion into another coordinate system NUE it would be quite tricky since in that system our rotation would be negative since in a NUE system +rotation around the up axis (+y) gives us a rotation heading west from north - the opposite of our rotation.

This gets much more complicated with general rotations. There is a simple way to convert between these definitions of systems.

```cpp
NUE_TO_NED = {{ // NUE to NED Matrix
    {1,  0,  0}, // stays same
    {0,  0,  1}, // z (east) becomes y (east) 
    {0, -1,  0}, // y (up) becomes z (down), flips
}};
```

The matrix above defines how the basis vectors (axes) change when converting from one system to another. We can multiply this by a general vector to see what it does.

```cpp
| 1   0   0 || x |   | x |
| 0   0   1 || y | = | z |
| 0  -1   0 || z |   |-y |
```

we can see it flips the y and z and inverts the y as we would expect (since y was up and now it is becoming down).

For converting rotations it's a little more involved because the rotation must be applied to a vector in the old coordinate system and then converted back to the new coordinate system. For a more detail explaination of the maths see the [sqg_coordinates.h](https://github.com/08jne01/squiggle/blob/main/include/sqg_coordinates.h)

## Functions

For each pair of coordinate systems there is a function converting from one to the other. As such we will only describe one set for clarity. Prior reading of the [vector](./vector.md), [matrix](matrix.md) and [quaternion](quaternion.md) sections are adviced to understand some of the pseudo-code.

All coordinate functions are in the sqg::coordinates namespace.

```cpp
mat_value<read_mat33_type> NUEtoNED( const read_mat33_type& matrix );
```

converts a matrix transform defined in NUE coordinates into an equivalent transform defined in NED coordinates

```cpp
vec_value<read_quat_type> NUEtoNED( const read_quat_type& quaternion );
```

converts a quaternion transform defined in NUE coordinates into an equivalent transform defined in NED coordinates

```cpp
vec_value<read_vec3_type> NUEtoNED( const read_vec3_type& vector );
```

converts a vector defined in NUE coordinates into an equivalent vector defined in NED coordinates