#pragma once
#include "sqg_struct.h"
#include "sqg_concepts.h"
#include "sqg_vec.h"

namespace sqg
{
    template<concepts::read_quat_type T>
    SQUIGGLE_INLINE constexpr vec3<vec_scalar<T>> V( const T& quaternion )
    {
        vec3<vec_scalar<T>> v;
        X(v,  X(quaternion));
        Y(v,  Y(quaternion));
        Z(v,  Z(quaternion));
        return v;
    }

    template<concepts::read_quat_type T>
    SQUIGGLE_INLINE constexpr vec_scalar<T> S( const T& quaternion )
    {
        return W(quaternion);
    }


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

    // template<concepts::vec3_type V, concepts::read_quat_type Q>
    // SQUIGGLE_INLINE constexpr void vector_component( V& vector, const Q& quaternion )
    // {
    //     X(vector,  X(quaternion));
    //     Y(vector,  Y(quaternion));
    //     Z(vector,  Z(quaternion));
    // }

    // // Returns vector part of quaternion
    // template<concepts::read_quat_type T>
    // SQUIGGLE_INLINE constexpr vec3<vec_scalar<T>> vector_component( const T& quaternion )
    // {
    //     vec3<vec_scalar<T>> v;
    //     vector_component(v, quaternion);
    //     return v;
    // }

    template<concepts::read_quat_type T>
    SQUIGGLE_INLINE constexpr vec_value<T> conjugate( const T& quaternion )
    {
        vec_value<T> q;
        W(q,   W(quaternion));
        X(q,  -X(quaternion));
        Y(q,  -Y(quaternion));
        Z(q,  -Z(quaternion));
        return q;
    }

    // full inverse, if you quaternion is normalised you can use conjugate for the same result but cheaper
    template<concepts::read_quat_type T>
    SQUIGGLE_INLINE constexpr vec_value<T> inverse( const T& quaternion )
    {
        return conjugate(quaternion) / mag2(quaternion);
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
        // but also
        // https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/transforms/index.htm
        // so the matrix used in the above link doesn't perform the simplification qvm does
        // if you assume ww + xx + yy + zz = 1 then you get a slightly cheaper result
        // which is also shown here https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
        // this makes sense too because the matrix formed in the former is not orthonormal if the quaternion is not normalised

        using scalar = vec_scalar<Q>;

        const scalar w = W(quaternion);
        const scalar x = X(quaternion);
        const scalar y = Y(quaternion);
        const scalar z = Z(quaternion);
        
        const scalar ww = w * w;
        const scalar xx = x * x;
        const scalar yy = y * y;
        const scalar zz = z * z;

        const scalar xy = x * y;
        const scalar zw = z * w;
        const scalar xz = x * z;
        const scalar yw = y * w;
        const scalar yz = y * z;
        const scalar xw = x * w;

        

    
        
        const scalar vx = X(vector);
        const scalar vy = Y(vector);
        const scalar vz = Z(vector);
        
        vec_value<V> v;
        X(v,    vx + scalar{2} * ((-yy - zz) * vx + ( xy - zw) * vy + ( xz + yw) * vz));
        Y(v,    vy + scalar{2} * (( xy + zw) * vx + (-xx - zz) * vy + ( yz - xw) * vz));
        Z(v,    vz + scalar{2} * (( xz - yw) * vx + ( yz + xw) * vy + (-xx - yy) * vz));
        return v;
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

    // set quaternion to angle/axis rotation, function normalises input axis, so vectors with length != 1 are accepted
    template<concepts::quat_type Q, concepts::read_vec3_type V>
    SQUIGGLE_INLINE constexpr void set_rot( Q& quaternion,  const V& vector, vec_scalar<Q> angle )
    {
        static_assert( std::same_as<vec_scalar<Q>,vec_scalar<V>>, "Scalar type must match for this operation" );

        // https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/notations/scalarAndVector/index.htm
        using scalar = vec_scalar<Q>;
        angle /= scalar{2};

        sqg::vec3<scalar> v;
        assign(v, vector);

        W(quaternion,   std::cos(angle));

        // axis must be normalised
        sqg::normalize(v);
        
        const auto sina2 = std::sin(angle);
        X(quaternion,   v.x * sina2);
        Y(quaternion,   v.y * sina2);
        Z(quaternion,   v.z * sina2);
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> rotx_quat( T angle )
    {   
        quat<T> q;        
        set_rotx(q,angle);
        return q;
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> roty_quat( T angle )
    {   
        quat<T> q;       
        set_roty(q,angle);
        return q;
    }

    template<std::floating_point T>
    SQUIGGLE_INLINE constexpr quat<T> rotz_quat( T angle )
    {   
        quat<T> q;  
        set_rotz(q,angle); 
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