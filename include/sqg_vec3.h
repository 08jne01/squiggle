#pragma once
#include "sqg_concepts.h"
#include <cmath>
namespace sqg
{
    template<detail::vec3_type V1, detail::read_vec3_type V2>
    SQUIGGLE_INLINE constexpr void assign( V1& destination, const V2& source )
    {
        X(destination) = X(source);
        Y(destination) = Y(source);
        Z(destination) = Z(source);
    }

    template<detail::vec3_type T>
    SQUIGGLE_INLINE constexpr void set_zero( T& vector )
    {
        constexpr vec_scalar<T> zero{0};
        X(vector) = zero;
        Y(vector) = zero;
        Z(vector) = zero;
    }

    template<detail::read_vec3_type V1, detail::read_vec3_type V2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value2<V1,V2> cross( const V1& a, const V2& b )
    {
        static_assert( std::same_as<vec_scalar<V1>,vec_scalar<V2>>, "Scalar type must match for this operation" );

        vec_value2<V1,V2> v;
        X(v) = Y(a) * Z(b) - Z(a) * Y(b);
        Y(v) = Z(a) * X(b) - X(a) * Z(b);
        Z(v) = X(a) * Y(b) - Y(a) * X(b);
        return v;
    }

    template<detail::read_vec3_type V1, detail::read_vec3_type V2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_scalar2<V1,V2> dot( const V1&a, const V2& b )
    {
        static_assert( std::same_as<vec_scalar<V1>,vec_scalar<V2>>, "Scalar type must match for this operation" );
        return X(a) * X(b) + Y(a) * Y(b) + Z(a) * Z(b);
    }

    template<detail::read_vec3_type T>
    [[nodiscard]] SQUIGGLE_INLINE constexpr T operator-( const T& vector )
    {
        vec_value<T> v;
        X(v) = -X(vector);
        Y(v) = -Y(vector);
        Z(v) = -Z(vector);
        return v;
    }

    template<detail::read_vec3_type V1, detail::read_vec3_type V2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value2<V1,V2> operator+( const V1& a, const V2& b )
    {
        static_assert( std::same_as<vec_scalar<V1>,vec_scalar<V2>>, "Scalar type must match for this operation" );

        vec_value2<V1,V2> v;
        X(v) = X(a) + X(b);
        Y(v) = Y(a) + Y(b);
        Z(v) = Z(a) + Z(b);
        return v;
    }

    template<detail::read_vec3_type V1, detail::read_vec3_type V2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value2<V1,V2> operator-( const V1& a, const V2& b )
    {
        static_assert( std::same_as<vec_scalar<V1>,vec_scalar<V2>>, "Scalar type must match for this operation" );

        vec_value2<V1,V2> v;
        X(v) = X(a) - X(b);
        Y(v) = Y(a) - Y(b);
        Z(v) = Z(a) - Z(b);
        return v;
    }

    template<detail::read_vec3_type T>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<T> operator*( vec_scalar<T> scalar, const T& vector )
    {
        vec_value<T> v;
        X(v) = scalar * X(vector);
        Y(v) = scalar * Y(vector);
        Z(v) = scalar * Z(vector);
        return v;
    }

    template<detail::read_vec3_type T>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<T> operator/( const T& vector, vec_scalar<T> scalar )
    {
        vec_value<T> v;
        X(v) = X(vector) / scalar;
        Y(v) = Y(vector) / scalar;
        Z(v) = Z(vector) / scalar;
        return v;
    }

    template<detail::read_vec3_type V1, detail::read_vec3_type V2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr bool operator==( const V1& a, const V2& b )
    {
        static_assert( std::same_as<vec_scalar<V1>,vec_scalar<V2>>, "Scalar type must match for this operation" );

        return 
            X(a) == X(b) &&
            Y(a) == Y(b) &&
            Z(a) == Z(b);
    }
}

