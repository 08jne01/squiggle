#pragma once
#include "sqg_struct.h"
#include <cmath>

namespace sqg
{
    template<detail::vec4_type V1, detail::read_vec4_type V2>
    SQUIGGLE_INLINE constexpr void assign( V1& destination, const V2& source )
    {
        static_assert( std::convertible_to<vec_scalar<V2>, vec_scalar<V1>>, "Source Scalar must be convertible to Destination Scalar" );
        W(destination,  W(source));
        X(destination,  X(source));
        Y(destination,  Y(source));
        Z(destination,  Z(source));
    }

    template<detail::vec4_type T>
    SQUIGGLE_INLINE constexpr void set_zero( T& vector )
    {
        constexpr vec_scalar<T> zero{0};
        W(vector,  zero);
        X(vector,  zero);
        Y(vector,  zero);
        Z(vector,  zero);
    }

    template<detail::read_vec4_type V1, detail::read_vec4_type V2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_scalar2<V1,V2> dot( const V1& a, const V2& b )
    {
        static_assert( std::same_as<vec_scalar<V1>,vec_scalar<V2>>, "Scalar type must match for this operation" );
        return W(a) * W(b) + X(a) * X(b) + Y(a) * Y(b) + Z(a) * Z(b);
    }

    template<detail::read_vec4_type T>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<T> operator-( const T& vector )
    {
        vec_value<T> v;
        W(v,  -W(vector));
        X(v,  -X(vector));
        Y(v,  -Y(vector));
        Z(v,  -Z(vector));
        return v;
    }

    template<detail::read_vec4_type V1, detail::read_vec4_type V2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value2<V1,V2> operator+( const V1& a, const V2& b )
    {
        static_assert( std::same_as<vec_scalar<V1>,vec_scalar<V2>>, "Scalar type must match for this operation" );

        vec_value2<V1,V2> v;
        W(v,  W(a) + W(b));
        X(v,  X(a) + X(b));
        Y(v,  Y(a) + Y(b));
        Z(v,  Z(a) + Z(b));
        return v;
    }

    template<detail::read_vec4_type V1, detail::read_vec4_type V2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value2<V1,V2> operator-( const V1& a, const V2& b )
    {
        static_assert( std::same_as<vec_scalar<V1>,vec_scalar<V2>>, "Scalar type must match for this operation" );

        vec_value2<V1,V2> v;
        W(v,  W(a) - W(b));
        X(v,  X(a) - X(b));
        Y(v,  Y(a) - Y(b));
        Z(v,  Z(a) - Z(b));
        return v;
    }

    template<detail::read_vec4_type T>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<T> operator*( vec_scalar<T> scalar, const T& vector )
    {
        vec_value<T> v;
        W(v,  scalar * W(vector));
        X(v,  scalar * X(vector));
        Y(v,  scalar * Y(vector));
        Z(v,  scalar * Z(vector));
        return v;
    }

    template<detail::read_vec4_type T>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<T> operator/( const T& vector, vec_scalar<T> scalar )
    {
        vec_value<T> v;
        W(v,  W(vector) / scalar);
        X(v,  X(vector) / scalar);
        Y(v,  Y(vector) / scalar);
        Z(v,  Z(vector) / scalar);
        return v;
    }

    template<detail::read_vec4_type V1, detail::read_vec4_type V2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr bool operator==( const V1& a, const V2& b )
    {
        static_assert( std::same_as<vec_scalar<V1>,vec_scalar<V2>>, "Scalar type must match for this operation" );

        return 
            W(a) == W(b) && 
            X(a) == X(b) &&
            Y(a) == Y(b) &&
            Z(a) == Z(b);
    }
}