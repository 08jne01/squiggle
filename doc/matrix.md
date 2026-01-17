# Matrix

This file lists all the common matrix functions, the syntax is close to C++ but is partly pseudocode to help readbility.

read_mat_type is any type that satisfies one of the following [concepts](concepts.md).

```cpp
template<typename Scalar> concept read_mat22_type;
template<typename Scalar> concept read_mat33_type;
template<typename Scalar> concept read_mat44_type;
```

mat_type is any type that satisfies one of the following [concepts](concepts.md).

```cpp
template<typename Scalar> concept mat22_type;
template<typename Scalar> concept mat33_type;
template<typename Scalar> concept mat44_type;
```

Note that for all functions which take two arguments it is implied the number of dimensions of each matrix are the same.

There are some type aliases which indicate return types of compatible template parameters. They are listed below.

| Alias | Input | Type
|-------|-------|------
| `mat_value` | `matrix` or `read_matrix` | constructible matrix type value for this matrix/view
| `mat_scalar` | `matrix` or `read_matrix` | scalar type for this matrix/view
| `mat_value2` | two of `matrix` or `read_matrix` | chosen constructible matrix type value
| `mat_scalar2` | two of `matrix` or `read_matrix` | chosen scalar type

## assign

```cpp
void assign( mat_type& destination, const read_mat_type& source );
```

sets destination equal to source

requires `mat_scalar<a> == mat_scalar<b>`

## set_zero

```cpp
void set_zero( mat_type& matrix );
```

zeros all components of matrix

## set_identity

```cpp
void set_identity( mat_type& matrix );
```

sets matrix to identity matrix of it's dimensions

## identity_mat

```cpp
template<typename Scalar, int dims> 
mat_type<Scalar,dims> identity_mat();
```

returns the corresponding squiggle matrix type with scalar type `Scalar` and number of dimensions specified. For example with `dims == 3`, mat33 is returned.

## transpose

```cpp
void transpose( mat_type& matrix );
```

in-place transpose of matrix

## transposed

```cpp
transpose_view<mat_type> transposed( const mat_type& matrix );
```

returns `transpose_view` (contains const matrix reference) of the matrix since this is a shallow copy it cannot be a value on its own but it satisfies `read_mat_type` so can be used in any function with that requirement. This also means it can be implicitly copied to one of the squiggle matrices. It can be explicitly copied to a user defined matrix using the [convert_to](#convert_to) function.

## determinant

```cpp
mat_scalar determinant( const read_mat_type& matrix );
```

returns determinant of matrix

> This is only defined for 2 and 3 dimensional matrices.

## row

```cpp
template<int row>
row_view<mat_type> row( mat_type& matrix );
```

return `row_view` (contains matrix reference) which satisifies `vec_type`

```cpp
template<int row>
read_row_view<mat_type> row( const mat_type& matrix );
```

return `read_row_view` (contains matrix reference) which satisfies `read_vec_type`

These views cannot be values on their own but they satisfy `vec_type` and `read_vec_type` respectively so can be used in any function with that requirement. This also means they can be implicitly copied to one of the squiggle vectors. They can be explicitly copied to a user defined vector using the [convert_to](./vector.md#convert_to) function.

## col

```cpp
template<int col>
row_view<mat_type> col( mat_type& matrix );
```

return `row_view` (contains matrix reference) which satisifies `vec_type`

```cpp
template<int col>
read_row_view<mat_type> col( const mat_type& matrix );
```

return `read_row_view` (contains matrix reference) which satisfies `read_vec_type`

Otherwise the same as [row](#row).

## set_rot2

```cpp
void set_rot2( mat22_type& matrix, mat_scalar scalar );
```

sets `matrix` as 2d rotation by angle `scalar`

> mat_scalar is deduced from matrix

## rot2_mat

```cpp
mat22<scalar_type> rot2_mat( scalar_type scalar );
```

returns 2d rotation by angle `scalar`

## operator- unary

```cpp
mat_value operator-( const read_mat_type& matrix );
```

returns componentwise negated matrix

## set_rotx

```cpp
void set_rotx( mat33_type& matrix, mat_scalar scalar );
```

sets `matrix` as rotation by angle `scalar` about x axis (0 column)

## set_roty

```cpp
void set_roty( mat33_type& matrix, mat_scalar scalar );
```

sets `matrix` as rotation by angle `scalar` about y axis (1 column)

## set_rotz

```cpp
void set_rotz( mat33_type& matrix, mat_scalar scalar );
```

sets `matrix` as rotation by angle `scalar` about z axis (2 column)

## set_rot

```cpp
void set_rot( mat33_type& matrix, const read_vec3_type& axis, mat_scalar scalar );
```

sets `matrix` as rotation by angle `scalar` about `axis`

> axis is **not** normalised by function

## rotx_mat

```cpp
mat33<scalar_type> rotx_mat( scalar_type scalar );
```

returns `matrix` as rotation by angle `scalar` about x axis (0 column)

## roty_mat

```cpp
mat33<scalar_type> roty_mat( scalar_type scalar );
```

returns `matrix` as rotation by angle `scalar` about y axis (1 column)

## rotz_mat

```cpp
mat33<scalar_type> set_rotz( scalar_type scalar );
```

returns `matrix` as rotation by angle `scalar` about z axis (2 column)

## rot_mat

```cpp
mat33<vec_scalar> rot_mat( const read_vec3_type& axis, vec_scalar scalar );
```

returns `matrix` as rotation by angle `scalar` about `axis`

> axis is **not** normalised by function, vec_scalar is deduced from axis

## operator+

```cpp
mat_value2 operator+( const read_mat_type& a, const read_mat_type& b );
```

returns componentwise sum of matrices

requires `mat_scalar<a> == mat_scalar<b>`

## operator-

```cpp
mat_value2 operator-( const read_mat_type& a, const read_mat_type& b );
```

returns componentwise subtraction of matrices

requires `mat_scalar<a> == mat_scalar<b>`

## operator*

```cpp
mat_value2 operator*( const read_mat_type& a, const read_mat_type& b );
```

returns the matrix multiplication ab

requires `mat_scalar<a> == mat_scalar<b>`

## operator/

```cpp
mat_scalar operator*( const read_mat_type& matrix, mat_scalar scalar );
```

returns componentwise divide of matrix by scalar

> mat_scalar is deduced from matrix

## operator== and operator!=

```cpp
bool operator==( const read_mat_type& a, const read_mat_type& b );
```

returns componentwise comparison, `a == b` for operator== and `a != b` for operator !=

requires `mat_scalar<a> == mat_scalar<b>`
