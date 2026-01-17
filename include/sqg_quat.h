#pragma once
#include "sqg_struct.h"
#include "sqg_concepts.h"
#include "sqg_vec3.h"

namespace sqg
{
    template<concepts::vec4_type T>
    SQUIGGLE_INLINE constexpr void set_identity( T& quaternion )
    {
        using scalar = vec_traits<T>::scalar_type;
        W(quaternion,  scalar{1});
        X(quaternion,  scalar{0});
        Y(quaternion,  scalar{0});
        Z(quaternion,  scalar{0});
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> identity_quat()
    {
        return quat<T>{}; // since sqg::quat is already initialised to identity quaternion
    }

    // Returns vector part of quaternion
    template<concepts::read_quat_type T>
    SQUIGGLE_INLINE constexpr vec3<vec_scalar<T>> vector_component( const T& quaternion )
    {
        vec3<vec_scalar<T>> v;
        X(v,  X(quaternion));
        Y(v,  Y(quaternion));
        Z(v,  Z(quaternion));
        return v;
    }

    template<concepts::read_quat_type T>
    SQUIGGLE_INLINE constexpr T conjugate( const T& quaternion )
    {
        T q;
        W(q,   W(quaternion));
        X(q,  -X(quaternion));
        Y(q,  -Y(quaternion));
        Z(q,  -Z(quaternion));
        return q;
    }

    template<concepts::read_quat_type T>
    SQUIGGLE_INLINE constexpr T inverse( const T& quaternion )
    {
        return conjucate(quaternion) / mag2(quaternion);
    }

    // quaternion multiplication
    template<concepts::read_quat_type Q1, concepts::read_quat_type Q2>
    SQUIGGLE_INLINE constexpr vec_value2<Q1,Q2> operator*( const Q1& q0, const Q2& q1 )
    {
        static_assert( std::same_as<vec_scalar<Q1>,vec_scalar<Q2>>, "Scalar type must match for this operation" );

        // https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/arithmetic/index.htm
        vec_value2<Q1,Q2> q;
        
        const auto e = W(q1);
        const auto f = X(q1);
        const auto g = Y(q1);
        const auto h = Z(q1);

        W(q,  W(q0) * W(q1) - X(q0) * X(q1) - Y(q0) * Y(q1) - Z(q0) * Z(q1));
        X(q,  W(q0) * X(q1) + X(q0) * W(q1) + Y(q0) * Z(q1) - Z(q0) * Y(q1));
        Y(q,  W(q0) * Y(q1) - X(q0) * Z(q1) + Y(q0) * W(q1) + Z(q0) * X(q1));
        Z(q,  W(q0) * Z(q1) + X(q0) * Y(q1) - Y(q0) * X(q1) + Z(q0) * W(q1));
        return q;
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> rotx_quat( T angle )
    {   
        quat<T> q;        
        W(q,  std::cos(angle / T{2}));
        
        const auto sina2 = std::sin(angle / T{2});
        X(q,  sina2);
        Y(q,  T{0});
        Z(q,  T{0});
        return q;
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> roty_quat( T angle )
    {   
        quat<T> q;        
        W(q,  std::cos(angle / T{2}));
        
        const auto sina2 = std::sin(angle / T{2});
        X(q,  T{0});
        Y(q,  sina2);
        Z(q,  T{0});
        return q;
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> rotz_quat( T angle )
    {   
        quat<T> q;        
        W(q,  std::cos(angle / T{2}));
        
        const auto sina2 = std::sin(angle / T{2});
        X(q,  T{0});
        Y(q,  T{0});
        Z(q,  sina2);
        return q;
    }
}