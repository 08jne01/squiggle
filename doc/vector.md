# Vector

This file lists all the common vector functions, the syntax is close to C++ but is partly pseudocode to help readbility.

read_vec_type is any type that satisfies one of the following [concepts](concepts.md).

```cpp
template<typename Scalar> concept read_vec2_type;
template<typename Scalar> concept read_vec3_type;
template<typename Scalar> concept read_vec4_type;
```

vec_type is any type that satisfies one of the following [concepts](concepts.md).

```cpp
template<typename Scalar> concept vec2_type;
template<typename Scalar> concept vec3_type;
template<typename Scalar> concept vec4_type;
```

Note that for all functions which take two arguments it is implied the number of dimensions of each vector are the same.

There are some type aliases which indicate return types of compatible template parameters. They are listed below.

| Alias | Input | Type
|-------|-------|------
| `vec_value` | `vector` or `read_vector` | constructible vector type value for this vector/view
| `vec_scalar` | `vector` or `read_vector` | scalar type for this vector/view
| `vec_value2` | two of `vector` or `read_vector` | chosen constructible vector type value
| `vec_scalar2` | two of `vector` or `read_vector` | chosen scalar type

## assign

```cpp
void assign( vec_type& destination, const read_vec_type& source );
```

sets destination equal to source

requires `vec_scalar<a> == vec_scalar<b>`

## set_zero

```cpp
void set_zero( vec_type& vector );
```

zeros all components of vector

## cross

### 2 dimensions

```cpp
vec_scalar2 cross( const read_vec2_type& a, const read_vec2_type& b );
```

returns cross product (scalar) of 2d vectors

requires `vec_scalar<a> == vec_scalar<b>`

### 3 dimensions

```cpp
vec_value2 cross( const read_vec3_type& a, const read_vec3_type& b );
```

returns cross product (vector) of 3d vectors

requires `vec_scalar<a> == vec_scalar<b>`

## dot

```cpp
vec_scalar2 dot( const read_vec_type& a, const read_vec_type& b );
```

returns dot product of two vectors

requires `vec_scalar<a> == vec_scalar<b>`

## operator- unary

```cpp
vec_value operator-( const read_vec_type& vector );
```

returns componentwise negated vector

## operator+

```cpp
vec_value2 operator+( const read_vec_type& a, const read_vec_type& b );
```

returns componentwise sum of vectors

requires `vec_scalar<a> == vec_scalar<b>`

## operator-

```cpp
vec_value2 operator-( const read_vec_type& a, const read_vec_type& b );
```

returns componentwise subtraction of vectors

requires `vec_scalar<a> == vec_scalar<b>`

## operator*

```cpp
vec_scalar operator*( const read_vec_type& vector, vec_scalar scalar );
```

or

```cpp
vec_scalar operator*( vec_scalar scalar, const read_vec_type& vector );
```

returns componentwise multiplication of vector by scalar

> vec_scalar is deduced from vector

## operator/

```cpp
vec_scalar operator*( const read_vec_type& vector, vec_scalar scalar );
```

returns componentwise divide of vector by scalar

> vec_scalar is deduced from vector

## operator== and operator!=

```cpp
bool operator==( const read_vec_type& a, const read_vec_type& b );
```

returns componentwise comparison, `a == b` for operator== and `a != b` for operator !=

requires `vec_scalar<a> == vec_scalar<b>`