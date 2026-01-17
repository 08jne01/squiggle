#pragma once
#include "sqg_struct.h"
#include <cmath>
namespace sqg
{
    //https://en.wikipedia.org/wiki/Rotation_matrix
    // Rotation matrix from axis and angle
    template<detail::vec3_type T> SQUIGGLE_INLINE mat33<typename vec_traits<T>::scalar_type> rot_mat( const T& vector, typename vec_traits<T>::scalar_type angle )
    {
        using scalar = vec_traits<T>::scalar_type;
        const scalar cosa = std::cos(angle);
        const scalar one_cosa = scalar{1} - cosa;
        const scalar sina = std::sin(angle);
        mat33<scalar> m;
        // Diagonal
        A00(m) = X(vector) * X(vector) * one_cosa + cosa;
        A11(m) = Y(vector) * Y(vector) * one_cosa + cosa;
        A22(m) = Z(vector) * Z(vector) * one_cosa + cosa;

        // Off Diagonal
        const scalar xy_one_cosa = X(vector) * Y(vector) * one_cosa;
        const scalar zsina = Z(vector) * sina;
        A01(m) = xy_one_cosa - zsina;
        A10(m) = xy_one_cosa + zsina;

        const scalar xz_one_cosa = X(vector) * Z(vector) * one_cosa;
        const scalar ysina = Y(vector) * sina;
        A02(m) = xz_one_cosa + ysina;
        A20(m) = xz_one_cosa - ysina;

        const scalar yz_one_cosa = Y(vector) * Z(vector) * one_cosa;
        const scalar xsina = X(vector) * sina;
        A12(m) = yz_one_cosa - xsina;
        A21(m) = yz_one_cosa + xsina;

        return m;
    }
}