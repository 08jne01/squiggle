#pragma once
#include "sqg_concepts.h"
#include "sqg_mat_view.h"
#include "sqg_struct.h"
#include "sqg_vec2.h"

#include <utility>
#include <cmath>
namespace sqg
{
    template<detail::mat22_type M1, detail::read_mat22_type M2> 
    SQUIGGLE_INLINE constexpr void assign( M1& destination, const M2& source )
    {
        static_assert( std::convertible_to<mat_scalar<M1>, mat_scalar<M2>>, "Source Scalar must be convertible to Destination Scalar" );
        A00(destination,  A00(source));
        A01(destination,  A01(source));

        A10(destination,  A10(source));
        A11(destination,  A11(source));
    }

    template<detail::mat22_type T> 
    SQUIGGLE_INLINE constexpr void set_identity(T& matrix)
    {
        constexpr typename mat_traits<T>::scalar_type zero{0};
        constexpr typename mat_traits<T>::scalar_type one{1};

        A00(matrix,  one);
        A01(matrix,  zero);

        A10(matrix,  zero);
        A11(matrix,  one);
    }

    template<detail::read_mat22_type M1, detail::read_mat22_type M2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr mat_value2<M1,M2> operator*( const M1& a, const M2& b )
    {
        mat_value2<M1,M2> m;
        A00(m,  sqg::dot(sqg::row<0>(a), sqg::col<0>(b)));
        A01(m,  sqg::dot(sqg::row<0>(a), sqg::col<1>(b)));
        A10(m,  sqg::dot(sqg::row<1>(a), sqg::col<0>(b)));
        A11(m,  sqg::dot(sqg::row<1>(a), sqg::col<1>(b)));
        return m;
    }

    template<detail::mat22_type M> 
    SQUIGGLE_INLINE constexpr void transpose(M& matrix)
    {
        // xx 01
        // 10 xx
        mat_swap_element<0,1,  1,0>(matrix);
    }

    //https://en.wikipedia.org/wiki/Determinant
    template<detail::mat22_type M> 
    SQUIGGLE_INLINE constexpr mat_traits<M>::scalar_type determinant(const M& matrix)
    {
        return A00(matrix) * A11(matrix) - A10(matrix) * A01(matrix);
    }

    // 2 dimensional rotation
    template<typename T> SQUIGGLE_INLINE mat22<T> rot_mat2( T angle )
    {
        using scalar = T;
        const scalar cosa = std::cos(angle);
        const scalar sina = std::sin(angle);

        mat22<T> m;
        A00(m,  cosa);
        A01(m,  -sina);
        
        A10(m,  sina);
        A10(m,  cosa);
    }
}