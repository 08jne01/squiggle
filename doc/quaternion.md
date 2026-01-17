# Quaternion

This file lists all the common quaternion functions, the syntax is close to C++ but is partly pseudocode to help readbility.

quaternions are types which satisfy any of the following [concepts](concepts.md).

```cpp
template<typename Scalar> concept read_quat_type;
template<typename Scalar> concept quat_type;
```

Quaternions and 4 dimensional vectors are the same the only additional constraint quaternions have is that their scalar must be floating point. These means that in addition to the functions below any quat can use the functions compatible with 4 dimensional [vectors](./vector.md).

Squiggle already defines a 4 dimensional vector but it also defines a quat, the reason is to have the order of the elements match convention, w,x,y,z and to default initialise the quaternion to the identity quaternion. Where instead vec4 is zero initialised.

There are some type aliases which indicate return types of compatible template parameters. Since quaternion is the same concept as a vec4 the aliases are the same as seen below.

| Alias | Input | Type
|-------|-------|------
| `vec_value` | `vector` or `read_vector` | constructible vector type value for this vector/view
| `vec_scalar` | `vector` or `read_vector` | scalar type for this vector/view
| `vec_value2` | two of `vector` or `read_vector` | chosen constructible vector type value
| `vec_scalar2` | two of `vector` or `read_vector` | chosen scalar type


## set_identity

```cpp
void set_identity( quat_type& quaternion );
```

sets `quaternion` to identity quaternion

## identity_quat

```cpp
template<typename Scalar> 
quat<Scalar> identity_quat();
```

returns the corresponding squiggle quat type with scalar type `Scalar`

## vector_component

```cpp
void vector_component( vec3_type& vector, const read_quat_type& quaternion );
```

sets `vector` to vector component (x,y,z) of `quaternion`

```cpp
vec3<vec_scalar> vector_component( const read_quat_type& quaternion );
```

returns `vec3` from vector component (x,y,z) of `quaternion`

## conjugate

```cpp
vec_value conjugate( const read_quat_type& quaternion );
```

returns conjugate (Q*) of `quaternion`

## inverse

```cpp
vec_value inverse( const read_quat_type& quaternion );
```

returns inverse (Q*/|Q|^2) of `quaternion`

> if quaternion is pure rotation then inverse(q) == conjucate(q), consider using conjugate in these cases for performance.

## operator*

```cpp
vec_value2 operator*( const read_quat_type& q0, const read_quat_type& q1 )
```

returns result of `q0q1` (quaternion multiplication)

```cpp
vec_value operator*( const read_quat_type& quaternion, const read_vec_type& vector )
```

returns result of `qvq*` (rotate vector by quaternion, sandwich product)

## set_rotx

```cpp
void set_rotx( quat_type& quaternion, vec_scalar scalar );
```

sets `quaternion` as rotation by angle `scalar` about x axis

## set_roty

```cpp
void set_roty( quat_type& quaternion, vec_scalar scalar );
```

sets `quaternion` as rotation by angle `scalar` about y axis

## set_rotz

```cpp
void set_rotz( quat_type& quaternion, vec_scalar scalar );
```

sets `quaternion` as rotation by angle `scalar` about z axis

## set_rot

```cpp
void set_rot( quat_type& quaternion, const read_vec3_type& axis, vec_scalar scalar );
```

sets `quaternion` as rotation by angle `scalar` about `axis`

> axis is **not** normalised by function

## rotx_mat

```cpp
quat<scalar_type> rotx_mat( scalar_type scalar );
```

returns `quaternion` as rotation by angle `scalar` about x axis

## roty_mat

```cpp
quat<scalar_type> roty_mat( scalar_type scalar );
```

returns `quaternion` as rotation by angle `scalar` about y axis

## rotz_mat

```cpp
quat<scalar_type> set_rotz( scalar_type scalar );
```

returns `quaternion` as rotation by angle `scalar` about z axis

## rot_mat

```cpp
quat<vec_scalar> rot_mat( const read_vec3_type& axis, vec_scalar scalar );
```

returns `quaternion` as rotation by angle `scalar` about `axis`

> axis is **not** normalised by function, vec_scalar is deduced from axis
