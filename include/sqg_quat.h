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

    template<concepts::vec3_type V, concepts::read_quat_type Q>
    SQUIGGLE_INLINE constexpr void vector_component( V& vector, const Q& quaternion )
    {
        X(vector,  X(quaternion));
        Y(vector,  Y(quaternion));
        Z(vector,  Z(quaternion));
    }

    // Returns vector part of quaternion
    template<concepts::read_quat_type T>
    SQUIGGLE_INLINE constexpr vec3<vec_scalar<T>> vector_component( const T& quaternion )
    {
        vec3<vec_scalar<T>> v;
        extract_vector(v, quaternion);
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

        W(q,  W(q0) * W(q1) - X(q0) * X(q1) - Y(q0) * Y(q1) - Z(q0) * Z(q1));
        X(q,  W(q0) * X(q1) + X(q0) * W(q1) + Y(q0) * Z(q1) - Z(q0) * Y(q1));
        Y(q,  W(q0) * Y(q1) + Y(q0) * W(q1) + Z(q0) * X(q1) - X(q0) * Z(q1));
        Z(q,  W(q0) * Z(q1) + Z(q0) * W(q1) + X(q0) * Y(q1) - Y(q0) * X(q1));
        return q;
    }

    template<concepts::quat_type Q, concepts::read_vec3_type V>
    SQUIGGLE_INLINE constexpr vec_value<V> operator*( const Q& quaternion, const V& vector )
    {
        static_assert( std::same_as<vec_scalar<Q>,vec_scalar<V>>, "Scalar type must match for this operation" );

        //https://math.stackexchange.com/questions/4037487/quaternion-sandwich-simplification-gives-me-a-term-too-many
        // (c^2 - b^2)v + 2(v . b)b + 2c(b x v)
        using scalar = vec_scalar<Q>;
        const auto c = W(quaternion);
        const auto b = vector_component(quaternion); 
        
        return 
            (c * c - mag2(b)) * vector + 
            scalar{2} * dot(vector, b) * b + 
            scalar{2} * c * cross(b, vector);
    }

    template<concepts::quat_type Q>
    SQUIGGLE_INLINE constexpr void set_rotx(Q& quaternion, vec_scalar<Q> angle )
    {
        using scalar = vec_scalar<Q>;

        W(quaternion,  std::cos(angle / scalar{2}));
        
        const auto sina2 = std::sin(angle / scalar{2});
        X(quaternion,  sina2);
        Y(quaternion,  scalar{0});
        Z(quaternion,  scalar{0});
    }

    template<concepts::quat_type Q>
    SQUIGGLE_INLINE constexpr void set_roty(Q& quaternion, vec_scalar<Q> angle )
    {
        using scalar = vec_scalar<Q>;
        W(quaternion,  std::cos(angle / scalar{2}));
        
        const auto sina2 = std::sin(angle / scalar{2});
        X(quaternion,  scalar{0});
        Y(quaternion,  sina2);
        Z(quaternion,  scalar{0});
    }

    template<concepts::quat_type Q>
    SQUIGGLE_INLINE constexpr void set_rotz(Q& quaternion, vec_scalar<Q> angle )
    {
        using scalar = vec_scalar<Q>;
        W(quaternion,  std::cos(angle / scalar{2}));
        
        const auto sina2 = std::sin(angle / scalar{2});
        X(quaternion,  scalar{0});
        Y(quaternion,  scalar{0});
        Z(quaternion,  sina2);
    }

    template<concepts::quat_type Q, concepts::read_vec3_type V>
    SQUIGGLE_INLINE constexpr void set_rot( Q& quaternion, const V& vector, typename vec_traits<Q>::scalar_type angle )
    {
        static_assert( std::same_as<vec_scalar<Q>,vec_scalar<V>>, "Scalar type must match for this operation" );

        // https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/notations/scalarAndVector/index.htm
        using scalar = typename vec_traits<Q>::scalar_type;
        W(quaternion) = std::cos(angle / scalar{2});
    
        assert( std::abs(mag(vector) - scalar{1}) < scalar{1.0e-6} );

        // axis should be normalised
        const auto sina2 = std::sin(angle / scalar{2});
        X(quaternion) = X(vector) * sina2;
        Y(quaternion) = Y(vector) * sina2;
        Z(quaternion) = Z(vector) * sina2;
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> rotx_quat( T angle )
    {   
        quat<T> q;        
        set_rotx(q);
        return q;
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> roty_quat( T angle )
    {   
        quat<T> q;       
        set_roty(q);
        return q;
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> rotz_quat( T angle )
    {   
        quat<T> q;  
        set_rotz(q); 
        return q;
    }

    template<concepts::read_vec3_type V>
    SQUIGGLE_INLINE constexpr quat<vec_scalar<V>> rot_quat( const V& vector, vec_scalar<V> angle )
    {
        quat<vec_scalar<V>> q;
        set_quat(q, vector, angle);
        return q;
    }
}