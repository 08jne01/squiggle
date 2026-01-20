#pragma once
#include "sqg_vec4.h"
#include "sqg_struct.h"

namespace sqg
{
    template<concepts::vec_type V>
    struct extend4_view
    {
        const V& vector;
        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        static_assert( concepts::read_vec4_type<extend4_view>, "Type V must satisfy read_vec4 constraints" );
    };

    template<concepts::read_vec3_type V>
    struct vec_traits<extend4_view<V>>
    {
        using scalar_type = vec_scalar<V>;
        using type = vec4<scalar_type>;
        using view = extend4_view<V>;
        static constexpr int n_dims = 4;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return X(v.vector); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return Y(v.vector); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return Z(v.vector); }
        static SQUIGGLE_INLINE constexpr scalar_type W(const view& v) { return scalar_type{1}; }
    };
}