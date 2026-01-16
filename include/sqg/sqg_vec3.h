#pragma once
#include "sqg_concepts.h"
#include <cmath>
namespace sqg
{
    template<detail::vec3_type TyLeft, detail::vec3_type TyRight>
    inline constexpr void assign( TyLeft& destination, const TyRight& source )
    {
        X(destination) = X(source);
        Y(destination) = Y(source);
        Z(destination) = Z(source);
    }

    template<detail::vec3_type T>
    inline constexpr void set_zero( T& vector )
    {
        constexpr typename vec_traits<T>::scalar_type zero{0};
        X(vector) = zero;
        Y(vector) = zero;
        Z(vector) = zero;
    }

    template<detail::vec3_type T>
    [[nodiscard]] inline constexpr T cross( const T& a, const T& b )
    {
        T v;
        X(v) = Y(a) * Z(b) - Z(a) * Y(b);
        Y(v) = Z(a) * X(b) - X(a) * Z(b);
        Z(v) = X(a) * Y(b) - Y(a) * X(b);
        return v;
    }

    template<detail::vec3_type T>
    [[nodiscard]] inline constexpr typename vec_traits<T>::scalar_type dot( const T&a, const T& b )
    {
        return X(a) * X(b) + Y(a) * Y(b) + Z(a) * Z(b);
    }

    template<detail::vec3_type T>
    [[nodiscard]] inline constexpr T operator-( const T& vector )
    {
        T v;
        X(v) = -X(vector);
        Y(v) = -Y(vector);
        Z(v) = -Z(vector);
        return v;
    }

    template<detail::vec3_type T>
    [[nodiscard]] inline constexpr T operator+( const T& a, const T& b )
    {
        T v;
        X(v) = X(a) + X(b);
        Y(v) = Y(a) + Y(b);
        Z(v) = Z(a) + Z(b);
        return v;
    }

    template<detail::vec3_type T>
    [[nodiscard]] inline constexpr T operator-( const T& a, const T& b )
    {
        T v;
        X(v) = X(a) - X(b);
        Y(v) = Y(a) - Y(b);
        Z(v) = Z(a) - Z(b);
        return v;
    }

    template<detail::vec3_type T>
    [[nodiscard]] inline constexpr T operator*( typename vec_traits<T>::scalar_type scalar, const T& vector )
    {
        T v;
        X(v) = scalar * X(vector);
        Y(v) = scalar * Y(vector);
        Z(v) = scalar * Z(vector);
        return v;
    }

    template<detail::vec3_type T>
    [[nodiscard]] inline constexpr T operator/( const T& vector, typename vec_traits<T>::scalar_type scalar )
    {
        T v;
        X(v) = X(vector) / scalar;
        Y(v) = Y(vector) / scalar;
        Z(v) = Z(vector) / scalar;
        return v;
    }

    template<detail::vec3_type T>
    [[nodiscard]] inline constexpr bool operator==( const T& a, const T& b )
    {
        return 
            X(a) == X(b) &&
            Y(a) == Y(b) &&
            Z(a) == Z(b);
    }
}

