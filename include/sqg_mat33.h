#pragma once
#include "sqg_concepts.h"
#include "sqg_mat_view.h"
#include "sqg_vec3.h"
#include "sqg_mat22.h"
#include <cmath>
namespace sqg
{
    template<concepts::mat33_type M1, concepts::read_mat33_type M2> 
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

    template<concepts::mat33_type T> SQUIGGLE_INLINE constexpr void set_zero( T& matrix )
    {
        constexpr typename mat_traits<T>::scalar_type zero{0};
        A00(matrix,  zero);
        A01(matrix,  zero);
        A02(matrix,  zero);

        A10(matrix,  zero);
        A11(matrix,  zero);
        A12(matrix,  zero);

        A20(matrix,  zero);
        A21(matrix,  zero);
        A22(matrix,  zero);
    }
    
    template<concepts::mat33_type T> SQUIGGLE_INLINE constexpr void set_identity( T& matrix )
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

    template<concepts::read_mat33_type M1, concepts::read_mat33_type M2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr mat_value2<M1,M2> operator*( const M1& a, const M2& b )
    {
        static_assert( std::same_as<mat_scalar<M1>,mat_scalar<M2>>, "Scalar type must match for this operation" );

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

    template<concepts::mat33_type M> SQUIGGLE_INLINE constexpr void transpose(M& matrix)
    {
        // xx 01 02
        // 10 xx 12
        // 20 21 xx
        mat_swap_element<0,1, 1,0>(matrix);        
        mat_swap_element<0,2, 2,0>(matrix);
        mat_swap_element<1,2, 2,1>(matrix);
    }

    //https://en.wikipedia.org/wiki/Determinant
    template<concepts::read_mat33_type M> 
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

    // This is horrifically slow, mainly just for constexpr operation
    // If you want the inverse of a rotation for an orthonormal matrix transpose is equivalent.
    template<concepts::read_mat33_type M>
    [[nodiscard]] SQUIGGLE_INLINE constexpr mat_value<M> inverse(const M& matrix)
    { //https://mathworld.wolfram.com/MatrixInverse.html

        mat_value<M> m;

        using scalar = mat_scalar<M>;

        const scalar a11 = A00(matrix);
        const scalar a12 = A01(matrix);
        const scalar a13 = A02(matrix);

        const scalar a21 = A10(matrix);
        const scalar a22 = A11(matrix);
        const scalar a23 = A12(matrix);

        const scalar a31 = A20(matrix);
        const scalar a32 = A21(matrix);
        const scalar a33 = A22(matrix);


        A00(m, determinant(sqg::mat22<mat_scalar<M>>{{
            { a22, a23 },
            { a32, a33 }
        }}));

        A01(m, determinant(sqg::mat22<mat_scalar<M>>{{
            { a13, a12 },
            { a33, a32 }
        }}));

        A02(m,determinant(sqg::mat22<mat_scalar<M>>{{
            { a12, a13 },
            { a22, a23 }
        }}));

        A10(m,determinant(sqg::mat22<mat_scalar<M>>{{
            { a23, a21 },
            { a33, a31 }
        }}));

        A11(m,determinant(sqg::mat22<mat_scalar<M>>{{
            { a11, a13 },
            { a31, a33 }
        }}));

        A12(m,determinant(sqg::mat22<mat_scalar<M>>{{
            { a13, a11 },
            { a23, a21 }
        }}));

        A20(m,determinant(sqg::mat22<mat_scalar<M>>{{
            { a21, a22 },
            { a31, a32 }
        }}));

        A21(m,determinant(sqg::mat22<mat_scalar<M>>{{
            { a12, a11 },
            { a32, a31 }
        }}));

        A22(m,determinant(sqg::mat22<mat_scalar<M>>{{
            { a11, a12 },
            { a21, a22 }
        }}));

        const scalar det = determinant(matrix);
        assert(det != scalar{0});
        return m * ( scalar{1} / det );
    }

    template<concepts::read_mat33_type M> 
    SQUIGGLE_INLINE constexpr mat_value<M> operator-( const M& matrix )
    {
        mat_value<M> m;
        row<0>(m) = -row<0>(matrix);
        row<1>(m) = -row<1>(matrix);
        row<2>(m) = -row<2>(matrix);
        return m;
    }

    template<concepts::read_mat33_type M1, concepts::read_mat33_type M2> 
    SQUIGGLE_INLINE constexpr mat_value2<M1,M2> operator+( const M1& a, const M2& b )
    {
        mat_value2<M1,M2> m;
        row<0>(m) = row<0>(a) + row<0>(b);
        row<1>(m) = row<1>(a) + row<1>(b);
        row<2>(m) = row<2>(a) + row<2>(b);
        return m;
    }

    template<concepts::read_mat33_type M1, concepts::read_mat33_type M2> 
    SQUIGGLE_INLINE constexpr mat_value2<M1,M2> operator-( const M1& a, const M2& b )
    {
        mat_value2<M1,M2> m;
        row<0>(m) = row<0>(a) - row<0>(b);
        row<1>(m) = row<1>(a) - row<1>(b);
        row<2>(m) = row<2>(a) - row<2>(b);
        return m;
    }

    template<concepts::read_mat33_type M> 
    SQUIGGLE_INLINE constexpr mat_value<M> operator*( mat_scalar<M> scalar, const M& matrix )
    {
        mat_value<M> m;
        row<0>(m) = row<0>(matrix) * scalar;
        row<1>(m) = row<1>(matrix) * scalar;
        row<2>(m) = row<2>(matrix) * scalar;
        return m;
    }

    template<concepts::read_mat33_type M> 
    SQUIGGLE_INLINE constexpr mat_value<M> operator/( const M& matrix, mat_scalar<M> scalar )
    {
        mat_value<M> m;
        row<0>(m) = row<0>(matrix) / scalar;
        row<1>(m) = row<1>(matrix) / scalar;
        row<2>(m) = row<2>(matrix) / scalar;
        return m;
    }

    //https://en.wikipedia.org/wiki/Rotation_matrix
    // Rx(theta)
    template<concepts::mat33_type T> SQUIGGLE_INLINE void set_rotx(T& matrix, typename mat_traits<T>::scalar_type angle)
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
    template<concepts::mat33_type T> SQUIGGLE_INLINE void set_roty(T& matrix, typename mat_traits<T>::scalar_type angle)
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
    template<concepts::mat33_type T> SQUIGGLE_INLINE void set_rotz(T& matrix, typename mat_traits<T>::scalar_type angle)
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

    //https://en.wikipedia.org/wiki/Rotation_matrix
    // Rotation matrix from axis and angle
    // set matrix to angle/axis rotation, function DOES NOT normalize axis, normalized vector is EXPECTED
    template<concepts::mat33_type M, concepts::read_vec3_type V> SQUIGGLE_INLINE void set_rot( M& matrix, const V& axis, mat_scalar<M> angle )
    {
        static_assert( std::same_as<mat_scalar<M>,vec_scalar<V>>, "Scalar type must match for this operation" );

        using scalar = mat_scalar<M>;
        const scalar cosa = std::cos(angle);
        const scalar one_cosa = scalar{1} - cosa;
        const scalar sina = std::sin(angle);

        const auto x = X(axis);
        const auto y = Y(axis);
        const auto z = Z(axis);

        // Diagonal
        // ux^2 * ( 1 - cosa ) + cosa
        // ux^2 - ux^2 cosa + cosa
        // ux^2 + (1 - ux^2) cosa 
        const scalar xx = x*x;
        const scalar yy = y*y;
        const scalar zz = z*z;

        A00(matrix,  xx + (scalar{1} - xx) * cosa);
        A11(matrix,  yy + (scalar{1} - yy) * cosa);
        A22(matrix,  zz + (scalar{1} - zz) * cosa);

        // Off Diagonal
        const scalar xy_one_cosa = (x * y) * one_cosa;
        const scalar zsina = z * sina;
        A01(matrix,  xy_one_cosa - zsina);
        A10(matrix,  xy_one_cosa + zsina);

        const scalar xz_one_cosa = (x * z) * one_cosa;
        const scalar ysina = y * sina;
        A02(matrix,  xz_one_cosa + ysina);
        A20(matrix,  xz_one_cosa - ysina);

        const scalar yz_one_cosa = (y * z) * one_cosa;
        const scalar xsina = x * sina;
        A12(matrix,  yz_one_cosa - xsina);
        A21(matrix,  yz_one_cosa + xsina);
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

    template<concepts::read_vec3_type V> SQUIGGLE_INLINE mat33<vec_scalar<V>> rot_mat( const V& axis, vec_scalar<V> angle )
    {
        mat33<vec_scalar<V>> m;
        set_rot(m, axis, angle);
        return m;
    }

    template<concepts::read_mat33_type M1, concepts::read_mat33_type M2>
    [[nodiscard]] SQUIGGLE_INLINE constexpr bool operator==( const M1& a, const M2& b )
    {
        static_assert( std::same_as<mat_scalar<M1>,mat_scalar<M2>>, "Scalar type must match for this operation" );

        return 
            row<0>(a) == row<0>(b) &&
            row<1>(a) == row<1>(b) &&
            row<2>(a) == row<2>(b);
    }
}