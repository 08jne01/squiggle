# Types

## Vector

```cpp
template<typename Scalar> vec2;
template<typename Scalar> vec3;
template<typename Scalar> vec4;
```

Each are accessible with x,y,z,w (up to the number of dimensions). These vectors are special because they contain the conversion operator, this allows them to **implicitly** be converted to any type to which they can be [assigned](vector.md#assign).

Default initialisation is zero.

## Matrix

```cpp
template<typename Scalar> mat22;
template<typename Scalar> mat33;
template<typename Scalar> mat44;
```

The member a is a simple n x n array of Scalar type. These matricies are special because they contain the conversion operator, this allows them to **implicitly** be converted to any type to which they can be [assigned](matrix.md#assign).

Default initialisation is zero.

## Quaternion

```cpp
template<std::floating_point Scalar> quat;
```

Components are accessible with w,x,y,z (up to the number of dimensions). This quaternion is special because it contains the conversion operator, this allows it to **implicitly** be converted to any type to which it can be [assigned](vector.md#assign).

The `quat` just implements the `vec_traits` for a 4 dimension vector. Any 4 dimension vector can be used as a quaternion however this structure is specifically arranged so that the real component (w) is at the start similar to layouts of other quaternions.

Furthermore the default initialisation is the identity quaternion.
