#pragma once
#include "sqg_concepts.h"
#include "sqg_mat_view.h"
#include "sqg_vec4.h"

namespace sqg
{
    template<concepts::mat44_type M1, concepts::read_mat44_type M2> 
    SQUIGGLE_INLINE constexpr void assign( M1& destination, const M2& source )
    {
        static_assert( std::convertible_to<mat_scalar<M1>, mat_scalar<M2>>, "Source Scalar must be convertible to Destination Scalar" );
        A00(destination,  A00(source));
        A01(destination,  A01(source));
        A02(destination,  A02(source));
        A03(destination,  A03(source));

        A10(destination,  A10(source));
        A11(destination,  A11(source));
        A12(destination,  A12(source));
        A13(destination,  A13(source));

        A20(destination,  A20(source));
        A21(destination,  A21(source));
        A22(destination,  A22(source));
        A23(destination,  A23(source));

        A30(destination,  A30(source));
        A31(destination,  A31(source));
        A32(destination,  A32(source));
        A33(destination,  A33(source));
    }

    template<concepts::mat44_type T> SQUIGGLE_INLINE constexpr void set_identity( T& matrix )
    {
        constexpr typename mat_traits<T>::scalar_type zero{0}; 
        constexpr typename mat_traits<T>::scalar_type one{1}; 
        A00(matrix,  one);
        A01(matrix,  zero);
        A02(matrix,  zero);
        A03(matrix,  zero);

        A10(matrix,  zero);
        A11(matrix,  one);
        A12(matrix,  zero);
        A13(matrix,  zero);

        A20(matrix,  zero);
        A21(matrix,  zero);
        A22(matrix,  one);
        A23(matrix,  zero);

        A30(matrix,  zero);
        A31(matrix,  zero);
        A32(matrix,  zero);
        A33(matrix,  one);
    }

    template<concepts::read_mat44_type M1, concepts::read_mat44_type M2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr mat_value2<M1,M2> operator*( const M1& a, const M2& b )
    {
        mat_value2<M1,M2> m;
        A00(m,  sqg::dot(sqg::row<0>(a), sqg::col<0>(b)));
        A01(m,  sqg::dot(sqg::row<0>(a), sqg::col<1>(b)));
        A02(m,  sqg::dot(sqg::row<0>(a), sqg::col<2>(b)));
        A03(m,  sqg::dot(sqg::row<0>(a), sqg::col<3>(b)));

        A10(m,  sqg::dot(sqg::row<1>(a), sqg::col<0>(b)));
        A11(m,  sqg::dot(sqg::row<1>(a), sqg::col<1>(b)));
        A12(m,  sqg::dot(sqg::row<1>(a), sqg::col<2>(b)));
        A13(m,  sqg::dot(sqg::row<1>(a), sqg::col<3>(b)));

        A20(m,  sqg::dot(sqg::row<2>(a), sqg::col<0>(b)));
        A21(m,  sqg::dot(sqg::row<2>(a), sqg::col<1>(b)));
        A22(m,  sqg::dot(sqg::row<2>(a), sqg::col<2>(b)));
        A23(m,  sqg::dot(sqg::row<2>(a), sqg::col<3>(b)));

        A30(m,  sqg::dot(sqg::row<3>(a), sqg::col<0>(b)));
        A31(m,  sqg::dot(sqg::row<3>(a), sqg::col<1>(b)));
        A32(m,  sqg::dot(sqg::row<3>(a), sqg::col<2>(b)));
        A33(m,  sqg::dot(sqg::row<3>(a), sqg::col<3>(b)));
        return m;
    }

    template<concepts::mat44_type M> SQUIGGLE_INLINE constexpr void transpose(M& matrix)
    {
        // xx 01 02 03
        // 10 xx 12 13
        // 20 21 xx 23
        // 30 31 32 xx

        mat_swap_element<0,1, 1,0>(matrix);
        mat_swap_element<0,2, 2,0>(matrix);
        mat_swap_element<0,3, 3,0>(matrix);
        
        mat_swap_element<1,2, 2,1>(matrix);
        mat_swap_element<1,3, 3,1>(matrix);
        mat_swap_element<2,3, 3,2>(matrix);
    }
}