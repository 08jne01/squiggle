#pragma once
#include "sqg_struct.h"
#include "sqg_concepts.h"
#include "sqg_vec3.h"

namespace sqg
{
    template<detail::vec4_type T>
    inline constexpr void set_identity( T& quaternion )
    {
        using scalar = vec_traits<T>::scalar_type;
        W(quaternion) = scalar{1};
        X(quaternion) = scalar{0};
        Y(quaternion) = scalar{0};
        Z(quaternion) = scalar{0};
    }

    template<std::floating_point T>
    inline constexpr quat<T> identity_quat()
    {
        return quat<T>{}; // since sqg::quat is already initialised to identity quaternion
    }

    // Returns vector part of quaternion
    template<detail::quat_type T>
    inline constexpr vec3<typename vec_traits<T>::scalar_type> V( const T& quaternion )
    {
        vec3<typename vec_traits<T>::scalar_type> v;
        X(v) = X(quaternion);
        Y(v) = Y(quaternion);
        Z(v) = Z(quaternion);
        return v;
    }

    template<detail::quat_type T>
    inline constexpr T conjugate( const T& quaternion )
    {
        T q;
        W(q) =  W(quaternion);
        X(q) = -X(quaternion);
        Y(q) = -Y(quaternion);
        Z(q) = -Z(quaternion);
        return q;
    }

    template<detail::quat_type T>
    inline constexpr T inverse( const T& quaternion )
    {
        return conjucate(quaternion) / mag2(quaternion);
    }

    // quaternion multiplication
    template<detail::quat_type T>
    inline constexpr T operator*( const T& q0, const T& q1 )
    {
        // https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm
        T q;
        
        const auto e = W(q1);
        const auto f = X(q1);
        const auto g = Y(q1);
        const auto h = Z(q1);

        W(q) = W(q0) * W(q1) - X(q0) * X(q1) - Y(q0) * Y(q1) - Z(q0) * Z(q1);
        X(q) = W(q0) * X(q1) + X(q0) * W(q1) + Y(q0) * Z(q1) - Z(q0) * Y(q1);
        Y(q) = W(q0) * Y(q1) - X(q0) * Z(q1) + Y(q0) * W(q1) + Z(q0) * X(q1);
        Z(q) = W(q0) * Z(q1) + X(q0) * Y(q1) - Y(q0) * X(q1) + Z(q0) * W(q1);
        return q;
    }

    template<std::floating_point T>
    inline constexpr quat<T> rotx_quat( T angle )
    {   
        quat<T> q;        
        W(q) = std::cos(angle / T{2});
        
        const auto sina2 = std::sin(angle / T{2});
        X(q) = sina2;
        Y(q) = T{0};
        Z(q) = T{0};
        return q;
    }

    template<std::floating_point T>
    inline constexpr quat<T> roty_quat( T angle )
    {   
        quat<T> q;        
        W(q) = std::cos(angle / T{2});
        
        const auto sina2 = std::sin(angle / T{2});
        X(q) = T{0};
        Y(q) = sina2;
        Z(q) = T{0};
        return q;
    }

    template<std::floating_point T>
    inline constexpr quat<T> rotz_quat( T angle )
    {   
        quat<T> q;        
        W(q) = std::cos(angle / T{2});
        
        const auto sina2 = std::sin(angle / T{2});
        X(q) = T{0};
        Y(q) = T{0};
        Z(q) = sina2;
        return q;
    }
}