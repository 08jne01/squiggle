#pragma once
#include "sqg_concepts.h"

namespace sqg
{
    template<detail::read_mat22_type M, detail::read_vec2_type V>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<V> operator*( const M& matrix, const V& vector )
    {
        V v;
        X(v) = dot( row<0>(matrix), vector );
        Y(v) = dot( row<1>(matrix), vector );
        return v;
    }

    template<detail::read_mat33_type M, detail::read_vec3_type V>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<V> operator*( const M& matrix, const V& vector )
    {
        V v;
        X(v) = dot( row<0>(matrix), vector );
        Y(v) = dot( row<1>(matrix), vector );
        Z(v) = dot( row<2>(matrix), vector );
        return v;
    }

    template<detail::read_mat44_type M, detail::read_vec4_type V>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<V> operator*( const M& matrix, const V& vector )
    {
        V v;
        X(v) = dot( row<0>(matrix), vector );
        Y(v) = dot( row<1>(matrix), vector );
        Z(v) = dot( row<2>(matrix), vector );
        W(v) = dot( row<3>(matrix), vector );
        return v;
    }
}