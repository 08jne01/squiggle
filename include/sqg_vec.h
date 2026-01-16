#pragma once
#include "sqg_struct.h"

#include "sqg_vec2.h"
#include "sqg_vec3.h"
#include "sqg_vec4.h"

namespace sqg
{
    template<typename T, int dims>
    [[nodiscard]] inline constexpr detail::vec_type_dims<T,dims>::vec_type zero_vec()
    {
        typename detail::vec_type_dims<T, dims>::vec_type v;
        set_zero(v);
        return v;
    }

     template<typename T, detail::vec2_type V>
    [[nodiscard]] inline constexpr vec2<T> scalar_cast( const V& vector )
    {
        vec2<T> v;
        X(v) = static_cast<T>(X(vector));
        Y(v) = static_cast<T>(Y(vector));
        return v;
    }

    template<typename T, detail::vec3_type V>
    [[nodiscard]] inline constexpr vec3<T> scalar_cast( const V& vector )
    {
        vec3<T> v;
        X(v) = static_cast<T>(X(vector));
        Y(v) = static_cast<T>(Y(vector));
        Z(v) = static_cast<T>(Z(vector));
        return v;
    }

    template<typename T, detail::vec4_type V>
    [[nodiscard]] inline constexpr vec4<T> scalar_cast( const V& vector )
    {
        vec4<T> v;
        X(v) = static_cast<T>(X(vector));
        Y(v) = static_cast<T>(Y(vector));
        Z(v) = static_cast<T>(Z(vector));
        W(v) = static_cast<T>(W(vector));
        return v;
    }

    template<detail::vec_type T>
    [[nodiscard]] inline constexpr vec_traits<T>::scalar_type mag2( const T& vector )
    {
        return dot(vector, vector);
    }

    template<detail::vec_type T>
    [[nodiscard]] inline constexpr vec_traits<T>::scalar_type mag( const T& vector )
    {
        return std::sqrt(mag2(vector));
    }

    template<detail::vec_type T>
    inline constexpr void normalize( T& vector )
    {
        const auto length = mag(vector);
        assert(length != decltype(length){0});
        vector /= length;
    }

    template<detail::vec_type T>
    inline constexpr T normalized( const T& vector )
    {
        T v = vector;
        normalize(v);
        return v;
    }

    template<detail::vec_type T>
    [[nodiscard]] inline constexpr T operator*( const T& vector, typename vec_traits<T>::scalar_type scalar )
    {
        return scalar * vector;
    }

    template<detail::vec_type T>
    inline constexpr T& operator*=( T& vector, typename vec_traits<T>::scalar_type scalar )
    {
        vector = scalar * vector;
        return vector;
    }

    template<detail::vec_type T>
    inline constexpr T& operator/=( T& vector, typename vec_traits<T>::scalar_type scalar )
    {
        vector = vector / scalar;
        return vector;
    }

    template<detail::vec_type T>
    [[nodiscard]] inline constexpr bool operator!=( const T& a, const T& b )
    {
        return ! ( a == b );
    }
}