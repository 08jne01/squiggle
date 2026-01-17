# Concepts

The squiggle library was designed to provide general matrix, quaternion and vector operations to any types which satisfy a given set of requirements/concepts.

The requirements are non-intrusive requiring no modification to the desired class/struct to use.

## Traits

Each compatible struct/class must implement the respective traits so that the intended concepts for the type are satisified.

The broad requirements are:
    1. number of dimensions
    2. accessor functions for components
    3. alias for scalar type
    4. alias for constructable type of the same concept

For requirement 4 this is usually just the type that is being implemented but in the case of a view (holding a reference to another object) it is important that squiggle can construct an appropriate by value, usually when returning from a function by value.

For each vector, matrix or quaternion there is a read only concept and a writable concept of these types. Similar to above read only concepts are used for views of other object. If you have a read only object you only need to implement the read accessor functions.

### vec_traits

The user vector must specialise the `sqg::vec_traits` template with their type as shown below.

```cpp
template<typename T>
struct Vector3 // example vector
{
    T x;
    T y;
    T z;
};

// in namespace sqg
template<typename T>
struct vec_traits<Vector3<T>>
{
    using scalar_type = T; // this should match your vector's scalar type
    using type = Vector3<T>; // value returned by a value operation ie cross(a,b), this must be default constructable.
    static constexpr int n_dims = 3; // number of dimensions

    // Getters, one for each dimension.
    // X,Y,Z,W are the expected names for each dimension.
    static SQUIGGLE_INLINE constexpr scalar_type X(const type& v) { return v.x; }
    static SQUIGGLE_INLINE constexpr scalar_type Y(const type& v) { return v.y; }
    static SQUIGGLE_INLINE constexpr scalar_type Z(const type& v) { return v.z; }

    // If your vector/view of a vector is read only then you only need to define
    // the read/getter functions and it will automatically satisfy the read_vecx_type
    // where x is the dimension.
    //
    // Setters, one for each dimension, you can either provide a function
    // which returns a scalar_type reference or provide a set function.
    // Both examples are show here for completeness but only one is needed.

    // scalar reference method
    static SQUIGGLE_INLINE constexpr scalar_type& X(type& v) { return v.x; }
    static SQUIGGLE_INLINE constexpr scalar_type& Y(type& v) { return v.y; }
    static SQUIGGLE_INLINE constexpr scalar_type& Z(type& v) { return v.z; }
    // setter method
    static SQUIGGLE_INLINE constexpr void X(type& v, scalar_type s) { v.x = s; }
    static SQUIGGLE_INLINE constexpr void Y(type& v, scalar_type s) { v.y = s; }
    static SQUIGGLE_INLINE constexpr void Z(type& v, scalar_type s) { v.z = s; }
};
```

That is everything that is required. Optionally you can provide more trait information to help deduce return types when two vectors are used in a function. The traits `vec_value2` are used. For example look at the cross function.

```cpp
template<concepts::read_vec3_type V1, concepts::read_vec3_type V2>
SQUIGGLE_INLINE constexpr vec_value2<V1,V2> cross( const V1& a, const V2& b );
```

The user can specialise `deduce_vec_traits` to prefer one vector over another. Whenever a scalar or value type is chosen between two vectors the `deduce_vec_traits` is used. The order of operands in the function determines the order in the templates. By default the traits of the left type are used.

```cpp
template<typename T>
struct Vector3;

template<typename T, typename V>
struct deduce_vec_traits<V, Vector3<T>> { using traits = vec_traits<Vector3<T>>; };
```

### mat_traits

The user vector must specialise the `sqg::vec_traits` template with their type as shown below.

```cpp
template<typename T>
struct Matrix33 // example matrix
{
    T a[3][3];
};

// in namespace sqg
template<typename T>
struct mat_traits<Matrix33<T>>
{
    using scalar_type = T; // this should match your vector's scalar type
    using type = Matrix33<T>; // value returned by a value operation ie cross(a,b), this must be default constructable.
    static constexpr int n_dims = 3; // number of dimensions

    // Getter templated by row and col.
    template<int row, int col>
    static SQUIGGLE_INLINE constexpr scalar_type A(const type& v) { return v.a[row][col]; }

    // If your matrix/view of a matrix is read only then you only need to define
    // the read/getter functions and it will automatically satisfy the read_matxx_type
    // where x is the dimension.
    //
    // Setter templated by row and col, you can either provide a function
    // which returns a scalar_type reference or provide a set function.
    // Both examples are show here for completeness but only one is needed.

    // scalar reference method
    template<int row, int col>
    static SQUIGGLE_INLINE constexpr scalar_type& Z(type& v) { return v.a[row][col]; }
    // setter method
    template<int row, int col>
    static SQUIGGLE_INLINE constexpr void A(type& v, scalar_type s) { v.a[row][col] = s; }
};
```

That is everything that is required. Optionally you can provide more trait information to help deduce return types when two vectors are used in a function. The traits `mat_value2` are used.

The user can specialise `deduce_mat_traits` to prefer one matrix over another. Whenever a scalar or value type is chosen between two matrix the `deduce_mat_traits` is used. The order of operands in the function determines the order in the templates. By default the traits of the left type are used.

```cpp
template<typename T>
struct Matrix3;

template<typename T, typename V>
struct deduce_mat_traits<V, Matrix3<T>> { using traits = mat_traits<Matrix3<T>>; };
```

## Concepts

The squiggle library defines several concepts located in the sqg_concepts.h. These concepts are used for to constrain library functions to the correct types.

```cpp
template<concepts::read_mat22_type M1, concepts::read_mat22_type M2>
SQUIGGLE_INLINE constexpr mat_value2<M1,M2> operator*( const M1& a, const M2& b )
```

For example several * operator functions will exist but for this particular operation we only want to select read only mat22.

See below the core concepts.

```cpp
// Vector Dimensions
// X - 0
// Y - 1
// Z - 2
// W - 3
// Note this only refers to which setters/getters exist in each
// dimension not the actual memory layout of the vector that is up
// to the user. For example the sqg::quat is arranged w,x,y,z;
//
// Matrix dimensions are defined by row,col in the template.

// constraint defining getter
concept vec_x_read;
concept vec_y_read;
concept vec_z_read;
concept vec_w_read;
concept mat_read<row,col>;

// constraint defining setter
concept vec_x_write;
concept vec_y_write;
concept vec_z_write;
concept vec_w_write;
concept mat_write<row,col>;

// constraint defining setter through getting reference
concept vec_x_write_ref;
concept vec_y_write_ref;
concept vec_z_write_ref;
concept vec_w_write_ref;
concept mat_write_ref<row,col>;
```

```cpp
// read/write vectors of a given dimension.
concept vec2_type;
concept vec3_type;
concept vec4_type;

// read only vectors of a given dimension.
// these are primarily used for const views of vectors
// like the row of matrix.
concept read_vec2_type;
concept read_vec3_type;
concept read_vec4_type;

// read/write matrices of given dimensions.
concept mat22_type;
concept mat33_type;
concept mat44_type;

// read only matricies of given dimensions.
// these are primarily used for const views of matricies
// like the transpose of a matrix.
concept read_mat22_type;
concept read_mat33_type;
concept read_mat44_type;
```

Any user type can be easily made into a compatible type by providing the corresponding [traits](#traits).
