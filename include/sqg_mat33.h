#pragma once
#include "sqg_concepts.h"
#include "sqg_struct.h"
#include <utility>
#include <cmath>
namespace sqg
{
    template<detail::mat33_type TyLeft, detail::mat33_type TyRight> 
    inline constexpr void assign( TyLeft& destination, TyRight& source )
    {
        A00(destination) = A00(source);
        A01(destination) = A01(source);
        A02(destination) = A02(source);

        A10(destination) = A10(source);
        A11(destination) = A11(source);
        A12(destination) = A12(source);

        A20(destination) = A20(source);
        A21(destination) = A21(source);
        A22(destination) = A22(source);
    }
    
    template<detail::mat33_type T> inline constexpr void set_identity( T& matrix )
    {
        constexpr typename mat_traits<T>::scalar_type zero{0}; 
        constexpr typename mat_traits<T>::scalar_type one{1}; 
        A00(matrix) = one;
        A01(matrix) = zero;
        A02(matrix) = zero;

        A10(matrix) = zero;
        A11(matrix) = one;
        A12(matrix) = zero;

        A20(matrix) = zero;
        A21(matrix) = zero;
        A22(matrix) = one;
    }

    template<int row_index, detail::mat33_type M> vec3<typename mat_traits<M>::scalar_type> row(const M& matrix)
    {
        vec3<typename mat_traits<M>::scalar_type> v;
        X(v) = A<row_index,0>(matrix);
        Y(v) = A<row_index,1>(matrix);
        Z(v) = A<row_index,2>(matrix);
        return v;
    }

    template<int col_index, detail::mat33_type M> vec3<typename mat_traits<M>::scalar_type> col(const M& matrix)
    {
        vec3<typename mat_traits<M>::scalar_type> v;
        X(v) = A<0,col_index>(matrix);
        Y(v) = A<1,col_index>(matrix);
        Z(v) = A<2,col_index>(matrix);
        return v;
    }

    template<detail::mat33_type M> inline constexpr void transpose(M& matrix)
    {
        // xx 01 02
        // 10 xx 12
        // 20 21 xx
        std::swap( A01(matrix), A10(matrix) );
        std::swap( A02(matrix), A20(matrix) );
        std::swap( A12(matrix), A21(matrix) );
    }

    template<detail::mat33_type M> inline constexpr M transposed(const M& matrix)
    {
        M m = matrix;
        transpose(m);
        return m;
    }

    //https://en.wikipedia.org/wiki/Determinant
    template<detail::mat33_type M> 
    inline constexpr mat_traits<M>::scalar_type determinant(const M& matrix)
    {
        const auto a = A00(matrix);
        const auto b = A01(matrix);
        const auto c = A02(matrix);

        const auto d = A10(matrix);
        const auto e = A11(matrix);
        const auto f = A12(matrix);

        const auto g = A20(matrix);
        const auto h = A21(matrix);
        const auto i = A22(matrix);

        return 
            a * e * i + 
            b * f * g + 
            c * d * h -
            c * e * g -
            b * d * i -
            a * f * h;
    }

    //https://en.wikipedia.org/wiki/Rotation_matrix
    // Rx(theta)
    template<detail::mat33_type T> inline void set_rotx(T& matrix, typename mat_traits<T>::scalar_type angle)
    {
        using scalar = mat_traits<T>::scalar_type;

        const scalar cosa = std::cos(angle);
        const scalar sina = std::sin(angle);

        A00(matrix) = scalar{1};
        A01(matrix) = scalar{0};
        A02(matrix) = scalar{0};
        
        A10(matrix) = scalar{0};
        A10(matrix) = cosa;
        A10(matrix) = -sina;
        
        A20(matrix) = scalar{0};
        A21(matrix) = sina;
        A22(matrix) = cosa;
    }

    //https://en.wikipedia.org/wiki/Rotation_matrix
    // Ry(theta)
    template<detail::mat33_type T> inline void set_roty(T& matrix, typename mat_traits<T>::scalar_type angle)
    {
        using scalar = mat_traits<T>::scalar_type;

        const scalar cosa = std::cos(angle);
        const scalar sina = std::sin(angle);

        A00(matrix) = cosa;
        A01(matrix) = scalar{0};
        A02(matrix) = sina;
        
        A10(matrix) = scalar{0};
        A10(matrix) = scalar{1};
        A10(matrix) = scalar{0};
        
        A20(matrix) = -sina;
        A21(matrix) = scalar{0};
        A22(matrix) = cosa;
    }

    //https://en.wikipedia.org/wiki/Rotation_matrix
    // Rz(theta)
    template<detail::mat33_type T> inline void set_rotz(T& matrix, typename mat_traits<T>::scalar_type angle)
    {
        using scalar = mat_traits<T>::scalar_type;

        const scalar cosa = std::cos(angle);
        const scalar sina = std::sin(angle);

        A00(matrix) = cosa;
        A01(matrix) = -sina;
        A02(matrix) = scalar{0};
        
        A10(matrix) = sina;
        A10(matrix) = cosa;
        A10(matrix) = scalar{0};
        
        A20(matrix) = scalar{0};
        A21(matrix) = scalar{0};
        A22(matrix) = scalar{1};
    }

    template<typename T> inline mat33<T> rotx_mat( T angle )
    {
        mat33<T> m;
        set_rotx(m, angle);
        return m;
    }

    template<typename T> inline mat33<T> roty_mat( T angle )
    {
        mat33<T> m;
        set_roty(m, angle);
        return m;
    }

    template<typename T> inline mat33<T> rotz_mat( T angle )
    {
        mat33<T> m;
        set_rotz(m, angle);
        return m;
    }
}