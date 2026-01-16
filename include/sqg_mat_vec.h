#pragma once
#include "sqg_concepts.h"

namespace sqg
{
    template<detail::mat22_type M, detail::vec2_type V>
    [[nodiscard]] inline constexpr V operator*( const M& matrix, const V& vector )
    {
        V v;
        X(v) = dot( row<0>(matrix), vector );
        Y(v) = dot( row<1>(matrix), vector );
        return v;
    }

    template<detail::mat33_type M, detail::vec3_type V>
    [[nodiscard]] inline constexpr V operator*( const M& matrix, const V& vector )
    {
        V v;
        X(v) = dot( row<0>(matrix), vector );
        Y(v) = dot( row<1>(matrix), vector );
        Z(v) = dot( row<2>(matrix), vector );
        return v;
    }

    template<detail::mat44_type M, detail::vec4_type V>
    [[nodiscard]] inline constexpr V operator*( const M& matrix, const V& vector )
    {
        V v;
        X(v) = dot( row<0>(matrix), vector );
        Y(v) = dot( row<1>(matrix), vector );
        Z(v) = dot( row<2>(matrix), vector );
        W(v) = dot( row<3>(matrix), vector );
        return v;
    }
}