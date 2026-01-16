#pragma once
#include "sqg_concepts.h"
#include "sqg_struct.h"
#include <utility>
#include <cmath>
namespace sqg
{
    template<detail::mat22_type TyLeft, detail::mat22_type TyRight> 
    inline constexpr void assign( TyLeft& destination, const TyRight& source )
    {
        A00(destination) = A00(source);
        A01(destination) = A01(source);

        A10(destination) = A10(source);
        A11(destination) = A11(source);
    }

    template<detail::mat22_type T> 
    inline constexpr void set_identity(T& matrix)
    {
        constexpr typename mat_traits<T>::scalar_type zero{0};
        constexpr typename mat_traits<T>::scalar_type one{0};

        A00(matrix) = one;
        A01(matrix) = zero;

        A10(matrix) = zero;
        A11(matrix) = one;
    }

    template<detail::mat22_type M> 
    inline constexpr void transpose(M& matrix)
    {
        // xx 01
        // 10 xx
        std::swap( A01(matrix), A10(matrix) );
    }

    //https://en.wikipedia.org/wiki/Determinant
    template<detail::mat22_type M> 
    inline constexpr mat_traits<M>::scalar_type determinant(const M& matrix)
    {
        return A00(matrix) * A11(matrix) - A10(matrix) * A01(matrix);
    }

    // 2 dimensional rotation
    template<typename T> inline mat22<T> rot_mat2( T angle )
    {
        using scalar = T;
        const scalar cosa = std::cos(angle);
        const scalar sina = std::sin(angle);

        mat22<T> m;
        A00(m) = cosa;
        A01(m) = -sina;
        
        A10(m) = sina;
        A10(m) = cosa;
    }
}