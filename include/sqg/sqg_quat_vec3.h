#pragma once
#include "sqg_concepts.h"
#include "sqg_struct.h"
#include <cmath>
namespace sqg
{
    template<detail::quat_type Q, detail::vec3_type V>
    inline constexpr V operator*( const Q& quaternion, const V& vector )
    {
        //https://math.stackexchange.com/questions/4037487/quaternion-sandwich-simplification-gives-me-a-term-too-many
        // (c^2 - b^2)v + 2(v . b)b + 2c(b x v)
        using scalar = vec_traits<Q>::scalar_type;
        const auto c = W(quaternion);
        const auto b = V(quaternion); 
        
        return 
            (c * c - mag2(b)) * vector + 
            scalar{2} * dot(vector, b) * b + 
            scalar{2} * c * cross(b, vector);
    }

    template<detail::quat_type Q, detail::vec3_type V>
    inline constexpr void set_quat( Q& quaternion, const V& vector, typename vec_traits<Q>::scalar_type angle )
    {
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

    template<detail::vec3_type V>
    inline constexpr quat<typename vec_traits<V>::scalar_type> rot_quat( const V& vector, typename vec_traits<V>::scalar_type angle )
    {
        using scalar = typename vec_traits<V>::scalar_type;
        quat<scalar> q;
        set_quat(q, vector, angle);
        return q;
    }
}