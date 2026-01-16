#pragma once
#include "sqg_concepts.h"

namespace sqg
{
    template<detail::mat44_type TyLeft, detail::read_mat44_type TyRight> 
    inline constexpr void assign( TyLeft& destination, const TyRight& source )
    {
        A00(destination) = A00(source);
        A01(destination) = A01(source);
        A02(destination) = A02(source);
        A03(destination) = A03(source);

        A10(destination) = A10(source);
        A11(destination) = A11(source);
        A12(destination) = A12(source);
        A13(destination) = A13(source);

        A20(destination) = A20(source);
        A21(destination) = A21(source);
        A22(destination) = A22(source);
        A23(destination) = A23(source);

        A30(destination) = A30(source);
        A31(destination) = A31(source);
        A32(destination) = A32(source);
        A33(destination) = A33(source);
    }

    template<detail::mat44_type T> inline constexpr void set_identity( T& matrix )
    {
        constexpr typename mat_traits<T>::scalar_type zero{0}; 
        constexpr typename mat_traits<T>::scalar_type one{1}; 
        A00(matrix) = one;
        A01(matrix) = zero;
        A02(matrix) = zero;
        A03(matrix) = zero;

        A10(matrix) = zero;
        A11(matrix) = one;
        A12(matrix) = zero;
        A13(matrix) = zero;

        A20(matrix) = zero;
        A21(matrix) = zero;
        A22(matrix) = one;
        A23(matrix) = zero;

        A30(matrix) = zero;
        A31(matrix) = zero;
        A32(matrix) = zero;
        A33(matrix) = one;
    }

    template<detail::mat44_type M44, detail::mat33_type M33, detail::vec3_type V3> 
    inline constexpr void set_transform( M44& matrix, const M33& orientation, const V3& position )
    {
        col<0>(matrix) = col<0>(orientation);
    }
}