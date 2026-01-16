#pragma once
#include "sqg_struct.h"
#include <cmath>

namespace sqg
{
    template<detail::vec4_type TyLeft, detail::vec4_type TyRight>
    inline constexpr void assign( TyLeft& destination, const TyRight& source )
    {
        W(destination) = W(source);
        X(destination) = X(source);
        Y(destination) = Y(source);
        Z(destination) = Z(source);
    }

    template<detail::vec4_type T>
    inline constexpr void set_zero( T& vector )
    {
        constexpr typename vec_traits<T>::scalar_type zero{0};
        W(vector) = zero;
        X(vector) = zero;
        Y(vector) = zero;
        Z(vector) = zero;
    }

    template<detail::vec4_type T>
    [[nodiscard]] inline constexpr typename vec_traits<T>::scalar_type dot( const T&a, const T& b )
    {
        return W(a) * W(b) + X(a) * X(b) + Y(a) * Y(b) + Z(a) * Z(b);
    }

    template<detail::vec4_type T>
    [[nodiscard]] inline constexpr T operator-( const T& vector )
    {
        T v;
        W(v) = -W(vector);
        X(v) = -X(vector);
        Y(v) = -Y(vector);
        Z(v) = -Z(vector);
        return v;
    }

    template<detail::vec4_type T>
    [[nodiscard]] inline constexpr T operator+( const T& a, const T& b )
    {
        T v;
        W(v) = W(a) + W(b);
        X(v) = X(a) + X(b);
        Y(v) = Y(a) + Y(b);
        Z(v) = Z(a) + Z(b);
        return v;
    }

    template<detail::vec4_type T>
    [[nodiscard]] inline constexpr T operator-( const T& a, const T& b )
    {
        T v;
        W(v) = W(a) - W(b);
        X(v) = X(a) - X(b);
        Y(v) = Y(a) - Y(b);
        Z(v) = Z(a) - Z(b);
        return v;
    }

    template<detail::vec4_type T>
    [[nodiscard]] inline constexpr T operator*( typename vec_traits<T>::scalar_type scalar, const T& vector )
    {
        T v;
        W(v) = scalar * W(vector);
        X(v) = scalar * X(vector);
        Y(v) = scalar * Y(vector);
        Z(v) = scalar * Z(vector);
        return v;
    }

    template<detail::vec4_type T>
    [[nodiscard]] inline constexpr T operator/( const T& vector, typename vec_traits<T>::scalar_type scalar )
    {
        T v;
        W(v) = W(vector) / scalar;
        X(v) = X(vector) / scalar;
        Y(v) = Y(vector) / scalar;
        Z(v) = Z(vector) / scalar;
        return v;
    }

    template<detail::vec4_type T>
    [[nodiscard]] inline constexpr bool operator==( const T& a, const T& b )
    {
        return 
            W(a) == W(b) && 
            X(a) == X(b) &&
            Y(a) == Y(b) &&
            Z(a) == Z(b);
    }
}