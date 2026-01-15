#pragma once
#include "sqg_concepts.h"
#include <cmath>
namespace sqg
{
    template<detail::vec2_type TyLeft, detail::vec2_type TyRight>
    inline constexpr void assign( TyLeft& destination, const TyRight& source )
    {
        X(destination) = X(source);
        Y(destination) = Y(source);
    }

    template<detail::vec2_type T>
    inline constexpr void set_zero( T& vector )
    {
        constexpr typename vec_traits<T>::scalar_type zero{0};
        X(vector) = zero;
        Y(vector) = zero;
    }

    //https://math.stackexchange.com/questions/3158634/whats-the-cross-product-in-2-dimensions
    template<detail::vec2_type T>
    [[nodiscard]] inline constexpr vec_traits<T>::scalar_type cross( const T& a, const T& b )
    {
        return X(a) * Y(b) - X(b) * Y(a);
    }

    template<detail::vec2_type T>
    [[nodiscard]] inline constexpr vec_traits<T>::scalar_type dot( const T& a, const T& b )
    {
        return X(a) * X(b) + Y(a) * Y(b);
    }

    template<detail::vec2_type T>
    [[nodiscard]] inline constexpr T operator-( const T& vector )
    {
        T v;
        X(v) = -X(vector);
        Y(v) = -Y(vector);
    }

    template<detail::vec2_type T>
    [[nodiscard]] inline constexpr T operator+( const T& a, const T& b )
    {
        T v;
        X(v) = X(a) + X(b);
        Y(v) = Y(a) + Y(b);
        return v;
    }

    template<detail::vec2_type T>
    [[nodiscard]] inline constexpr T operator-( const T& a, const T& b )
    {
        T v;
        X(v) = X(a) - X(b);
        Y(v) = Y(a) - Y(b);
        return v;
    }

    template<detail::vec2_type T>
    [[nodiscard]] inline constexpr T operator*( typename vec_traits<T>::scalar_type scalar, const T& vector )
    {
        T v;
        X(v) = scalar * X(vector);
        Y(v) = scalar * Y(vector);
        return v;
    }

    template<detail::vec2_type T>
    [[nodiscard]] inline constexpr T operator/( const T& vector, typename vec_traits<T>::scalar_type scalar )
    {
        T v;
        X(v) = X(vector) / scalar;
        Y(v) = Y(vector) / scalar;
        return v;
    }

    template<detail::vec2_type T>
    [[nodiscard]] inline constexpr T& operator==( const T& a, const T& b )
    {
        return 
            X(a) == X(b) &&
            Y(a) == Y(b);
    }
}