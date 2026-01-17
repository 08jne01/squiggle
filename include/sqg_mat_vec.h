#pragma once
#include "sqg_concepts.h"
#include "sqg_mat_view.h"
#include "sqg_vec2.h"
#include "sqg_vec3.h"
#include "sqg_vec4.h"
#include "sqg_vec_view.h"

namespace sqg
{
    template<concepts::read_mat22_type M, concepts::read_vec2_type V>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<V> operator*( const M& matrix, const V& vector )
    {
        V v;
        X(v,   dot( row<0>(matrix), vector ));
        Y(v,   dot( row<1>(matrix), vector ));
        return v;
    }

    template<concepts::read_mat33_type M, concepts::read_vec3_type V>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<V> operator*( const M& matrix, const V& vector )
    {
        V v;
        X(v,   dot( row<0>(matrix), vector ));
        Y(v,   dot( row<1>(matrix), vector ));
        Z(v,   dot( row<2>(matrix), vector ));
        return v;
    }

    template<concepts::read_mat44_type M, concepts::read_vec4_type V>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<V> operator*( const M& matrix, const V& vector )
    {
        V v;
        X(v,  dot( row<0>(matrix), vector ));
        Y(v,  dot( row<1>(matrix), vector ));
        Z(v,  dot( row<2>(matrix), vector ));
        W(v,  dot( row<3>(matrix), vector ));
        return v;
    }

    template<concepts::read_mat44_type M, concepts::read_vec3_type V>
    [[nodiscard]] SQUIGGLE_INLINE constexpr vec_value<V> operator*( const M& matrix, const V& vector )
    {
        const auto view = extend4_view{vector};
        V v;
        X(v,  dot( row<0>(matrix), view ));
        Y(v,  dot( row<1>(matrix), view ));
        Z(v,  dot( row<2>(matrix), view )); // can skip W component since we would just discard anyway
        return v;
    }
}