#pragma once
#include "sqg_concepts.h"
namespace sqg
{
    // Defined Row,Col
    template<int row, int col, detail::mat_type T> 
    inline constexpr typename mat_traits<T>::scalar_type A(const T& v) 
    { 
        static_assert( row < mat_traits<T>::n_dims && col < mat_traits<T>::n_dims, "row and col must be less than the number of dimensions" );
        return mat_traits<T>::template A<row,col>(v); 
    }
    
    template<int row, int col, detail::mat_type T>
    inline constexpr typename mat_traits<T>::scalar_type& A(T& v)
    {
        static_assert( row < mat_traits<T>::n_dims && col < mat_traits<T>::n_dims, "row and col must be less than the number of dimensions" );
        return mat_traits<T>::template A<row,col>(v); 
    }

    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A00(const T& v) { return mat_traits<T>::template A<0,0>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A01(const T& v) { return mat_traits<T>::template A<0,1>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A02(const T& v) { return mat_traits<T>::template A<0,2>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A03(const T& v) { return mat_traits<T>::template A<0,3>(v); } 

    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A10(const T& v) { return mat_traits<T>::template A<1,0>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A11(const T& v) { return mat_traits<T>::template A<1,1>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A12(const T& v) { return mat_traits<T>::template A<1,2>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A13(const T& v) { return mat_traits<T>::template A<1,3>(v); } 

    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A20(const T& v) { return mat_traits<T>::template A<2,0>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A21(const T& v) { return mat_traits<T>::template A<2,1>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A22(const T& v) { return mat_traits<T>::template A<2,2>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A23(const T& v) { return mat_traits<T>::template A<2,3>(v); } 

    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A30(const T& v) { return mat_traits<T>::template A<3,0>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A31(const T& v) { return mat_traits<T>::template A<3,1>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A32(const T& v) { return mat_traits<T>::template A<3,2>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type A33(const T& v) { return mat_traits<T>::template A<3,3>(v); } 

    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A00(T& v) { return mat_traits<T>::template A<0,0>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A01(T& v) { return mat_traits<T>::template A<0,1>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A02(T& v) { return mat_traits<T>::template A<0,2>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A03(T& v) { return mat_traits<T>::template A<0,3>(v); } 

    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A10(T& v) { return mat_traits<T>::template A<1,0>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A11(T& v) { return mat_traits<T>::template A<1,1>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A12(T& v) { return mat_traits<T>::template A<1,2>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A13(T& v) { return mat_traits<T>::template A<1,3>(v); } 

    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A20(T& v) { return mat_traits<T>::template A<2,0>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A21(T& v) { return mat_traits<T>::template A<2,1>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A22(T& v) { return mat_traits<T>::template A<2,2>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A23(T& v) { return mat_traits<T>::template A<2,3>(v); } 

    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A30(T& v) { return mat_traits<T>::template A<3,0>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A31(T& v) { return mat_traits<T>::template A<3,1>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A32(T& v) { return mat_traits<T>::template A<3,2>(v); } 
    template<detail::mat_type T> inline constexpr typename mat_traits<T>::scalar_type& A33(T& v) { return mat_traits<T>::template A<3,3>(v); } 

    template<detail::vec_type T> inline constexpr typename vec_traits<T>::scalar_type W(const T& v) { return vec_traits<T>::W(v); } 
    template<detail::vec_type T> inline constexpr typename vec_traits<T>::scalar_type X(const T& v) { return vec_traits<T>::X(v); } 
    template<detail::vec_type T> inline constexpr typename vec_traits<T>::scalar_type Y(const T& v) { return vec_traits<T>::Y(v); } 
    template<detail::vec_type T> inline constexpr typename vec_traits<T>::scalar_type Z(const T& v) { return vec_traits<T>::Z(v); } 

    template<detail::vec_type T> inline constexpr typename vec_traits<T>::scalar_type& W(T& v) { return vec_traits<T>::W(v); } 
    template<detail::vec_type T> inline constexpr typename vec_traits<T>::scalar_type& X(T& v) { return vec_traits<T>::X(v); } 
    template<detail::vec_type T> inline constexpr typename vec_traits<T>::scalar_type& Y(T& v) { return vec_traits<T>::Y(v); } 
    template<detail::vec_type T> inline constexpr typename vec_traits<T>::scalar_type& Z(T& v) { return vec_traits<T>::Z(v); } 
}