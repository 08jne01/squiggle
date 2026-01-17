#pragma once
#include "sqg_concepts.h"
#include "sqg_mat_view.h"
#include "sqg_struct.h"
#include "sqg_vec3.h"
#include <utility>
#include <cmath>
namespace sqg
{
    template<detail::mat33_type M1, detail::read_mat33_type M2> 
    SQUIGGLE_INLINE constexpr void assign( M1& destination, const M2& source )
    {
        static_assert( std::convertible_to<mat_scalar<M1>, mat_scalar<M2>>, "Source Scalar must be convertible to Destination Scalar" );
        A00(destination,  A00(source));
        A01(destination,  A01(source));
        A02(destination,  A02(source));

        A10(destination,  A10(source));
        A11(destination,  A11(source));
        A12(destination,  A12(source));

        A20(destination,  A20(source));
        A21(destination,  A21(source));
        A22(destination,  A22(source));
    }
    
    template<detail::mat33_type T> SQUIGGLE_INLINE constexpr void set_identity( T& matrix )
    {
        constexpr typename mat_traits<T>::scalar_type zero{0}; 
        constexpr typename mat_traits<T>::scalar_type one{1}; 
        A00(matrix,  one);
        A01(matrix,  zero);
        A02(matrix,  zero);

        A10(matrix,  zero);
        A11(matrix,  one);
        A12(matrix,  zero);

        A20(matrix,  zero);
        A21(matrix,  zero);
        A22(matrix,  one);
    }

    template<detail::read_mat33_type M1, detail::read_mat33_type M2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr mat_value2<M1,M2> operator*( const M1& a, const M2& b )
    {
        mat_value2<M1,M2> m;
        A00(m,  sqg::dot(sqg::row<0>(a), sqg::col<0>(b)));
        A01(m,  sqg::dot(sqg::row<0>(a), sqg::col<1>(b)));
        A02(m,  sqg::dot(sqg::row<0>(a), sqg::col<2>(b)));

        A10(m,  sqg::dot(sqg::row<1>(a), sqg::col<0>(b)));
        A11(m,  sqg::dot(sqg::row<1>(a), sqg::col<1>(b)));
        A12(m,  sqg::dot(sqg::row<1>(a), sqg::col<2>(b)));

        A20(m,  sqg::dot(sqg::row<2>(a), sqg::col<0>(b)));
        A21(m,  sqg::dot(sqg::row<2>(a), sqg::col<1>(b)));
        A22(m,  sqg::dot(sqg::row<2>(a), sqg::col<2>(b)));
        return m;
    }

    template<detail::mat33_type M> SQUIGGLE_INLINE constexpr void transpose(M& matrix)
    {
        // xx 01 02
        // 10 xx 12
        // 20 21 xx
        mat_swap_element<0,1, 1,0>(matrix);        
        mat_swap_element<0,2, 2,0>(matrix);
        mat_swap_element<1,2, 2,1>(matrix);
    }

    //https://en.wikipedia.org/wiki/Determinant
    template<detail::read_mat33_type M> 
    SQUIGGLE_INLINE constexpr mat_traits<M>::scalar_type determinant(const M& matrix)
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
    template<detail::mat33_type T> SQUIGGLE_INLINE void set_rotx(T& matrix, typename mat_traits<T>::scalar_type angle)
    {
        using scalar = mat_traits<T>::scalar_type;

        const scalar cosa = std::cos(angle);
        const scalar sina = std::sin(angle);

        A00(matrix,  scalar{1});
        A01(matrix,  scalar{0});
        A02(matrix,  scalar{0});
        
        A10(matrix,  scalar{0});
        A11(matrix,  cosa);
        A12(matrix,  -sina);
        
        A20(matrix,  scalar{0});
        A21(matrix,  sina);
        A22(matrix,  cosa);
    }

    //https://en.wikipedia.org/wiki/Rotation_matrix
    // Ry(theta)
    template<detail::mat33_type T> SQUIGGLE_INLINE void set_roty(T& matrix, typename mat_traits<T>::scalar_type angle)
    {
        using scalar = mat_traits<T>::scalar_type;

        const scalar cosa = std::cos(angle);
        const scalar sina = std::sin(angle);

        A00(matrix,  cosa);
        A01(matrix,  scalar{0});
        A02(matrix,  sina);
        
        A10(matrix,  scalar{0});
        A11(matrix,  scalar{1});
        A12(matrix,  scalar{0});
        
        A20(matrix,  -sina);
        A21(matrix,  scalar{0});
        A22(matrix,  cosa);
    }

    //https://en.wikipedia.org/wiki/Rotation_matrix
    // Rz(theta)
    template<detail::mat33_type T> SQUIGGLE_INLINE void set_rotz(T& matrix, typename mat_traits<T>::scalar_type angle)
    {
        using scalar = mat_traits<T>::scalar_type;

        const scalar cosa = std::cos(angle);
        const scalar sina = std::sin(angle);

        A00(matrix,  cosa);
        A01(matrix,  -sina);
        A02(matrix,  scalar{0});
        
        A10(matrix,  sina);
        A11(matrix,  cosa);
        A12(matrix,  scalar{0});
        
        A20(matrix,  scalar{0});
        A21(matrix,  scalar{0});
        A22(matrix,  scalar{1});
    }

    template<typename T> SQUIGGLE_INLINE mat33<T> rotx_mat( T angle )
    {
        mat33<T> m;
        set_rotx(m, angle);
        return m;
    }

    template<typename T> SQUIGGLE_INLINE mat33<T> roty_mat( T angle )
    {
        mat33<T> m;
        set_roty(m, angle);
        return m;
    }

    template<typename T> SQUIGGLE_INLINE mat33<T> rotz_mat( T angle )
    {
        mat33<T> m;
        set_rotz(m, angle);
        return m;
    }
}