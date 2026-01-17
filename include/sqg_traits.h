#pragma once
#include "sqg_concepts.h"
namespace sqg
{
    // Defined Row,Col
    template<int row, int col, detail::mat_type T> 
    SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A(const T& v) 
    { 
        static_assert( row < mat_traits<T>::n_dims && col < mat_traits<T>::n_dims, "row and col must be less than the number of dimensions" );
        return mat_traits<T>::template A<row,col>(v); 
    }
    
    template<int row, int col, detail::mat_type T>
    requires detail::mat_write<T, row, col>
    SQUIGGLE_INLINE constexpr void A(T& v, typename mat_traits<T>::scalar_type s)
    {
        static_assert( row < mat_traits<T>::n_dims && col < mat_traits<T>::n_dims, "row and col must be less than the number of dimensions" );
        mat_traits<T>::template A<row,col>(v,s); 
    }

    template<int row, int col, detail::mat_type T>
    requires detail::mat_write_ref<T,row,col>
    SQUIGGLE_INLINE constexpr void A(T& v, typename mat_traits<T>::scalar_type s)
    {
        static_assert( row < mat_traits<T>::n_dims && col < mat_traits<T>::n_dims, "row and col must be less than the number of dimensions" );
        mat_traits<T>::template A<row,col>(v) = s; 
    }

    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A00(const T& v) { return mat_traits<T>::template A<0,0>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A01(const T& v) { return mat_traits<T>::template A<0,1>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A02(const T& v) { return mat_traits<T>::template A<0,2>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A03(const T& v) { return mat_traits<T>::template A<0,3>(v); } 

    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A10(const T& v) { return mat_traits<T>::template A<1,0>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A11(const T& v) { return mat_traits<T>::template A<1,1>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A12(const T& v) { return mat_traits<T>::template A<1,2>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A13(const T& v) { return mat_traits<T>::template A<1,3>(v); } 

    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A20(const T& v) { return mat_traits<T>::template A<2,0>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A21(const T& v) { return mat_traits<T>::template A<2,1>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A22(const T& v) { return mat_traits<T>::template A<2,2>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A23(const T& v) { return mat_traits<T>::template A<2,3>(v); } 

    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A30(const T& v) { return mat_traits<T>::template A<3,0>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A31(const T& v) { return mat_traits<T>::template A<3,1>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A32(const T& v) { return mat_traits<T>::template A<3,2>(v); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr typename mat_traits<T>::scalar_type A33(const T& v) { return mat_traits<T>::template A<3,3>(v); } 

    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A00(T& v, typename mat_traits<T>::scalar_type s) { A<0,0>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A01(T& v, typename mat_traits<T>::scalar_type s) { A<0,1>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A02(T& v, typename mat_traits<T>::scalar_type s) { A<0,2>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A03(T& v, typename mat_traits<T>::scalar_type s) { A<0,3>(v,s); } 

    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A10(T& v, typename mat_traits<T>::scalar_type s) { A<1,0>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A11(T& v, typename mat_traits<T>::scalar_type s) { A<1,1>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A12(T& v, typename mat_traits<T>::scalar_type s) { A<1,2>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A13(T& v, typename mat_traits<T>::scalar_type s) { A<1,3>(v,s); } 

    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A20(T& v, typename mat_traits<T>::scalar_type s) { A<2,0>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A21(T& v, typename mat_traits<T>::scalar_type s) { A<2,1>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A22(T& v, typename mat_traits<T>::scalar_type s) { A<2,2>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A23(T& v, typename mat_traits<T>::scalar_type s) { A<2,3>(v,s); } 

    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A30(T& v, typename mat_traits<T>::scalar_type s) { A<3,0>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A31(T& v, typename mat_traits<T>::scalar_type s) { A<3,1>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A32(T& v, typename mat_traits<T>::scalar_type s) { A<3,2>(v,s); } 
    template<detail::mat_type T> SQUIGGLE_INLINE constexpr void A33(T& v, typename mat_traits<T>::scalar_type s) { A<3,3>(v,s); } 

    template<detail::vec_type T> SQUIGGLE_INLINE constexpr typename vec_traits<T>::scalar_type W(const T& v) { return vec_traits<T>::W(v); } 
    template<detail::vec_type T> SQUIGGLE_INLINE constexpr typename vec_traits<T>::scalar_type X(const T& v) { return vec_traits<T>::X(v); } 
    template<detail::vec_type T> SQUIGGLE_INLINE constexpr typename vec_traits<T>::scalar_type Y(const T& v) { return vec_traits<T>::Y(v); } 
    template<detail::vec_type T> SQUIGGLE_INLINE constexpr typename vec_traits<T>::scalar_type Z(const T& v) { return vec_traits<T>::Z(v); } 

    template<detail::vec_type T> requires detail::vec_w_write<T> SQUIGGLE_INLINE constexpr void W(T& v, typename vec_traits<T>::scalar_type s) { return vec_traits<T>::W(v,s); } 
    template<detail::vec_type T> requires detail::vec_x_write<T> SQUIGGLE_INLINE constexpr void X(T& v, typename vec_traits<T>::scalar_type s) { return vec_traits<T>::X(v,s); } 
    template<detail::vec_type T> requires detail::vec_y_write<T> SQUIGGLE_INLINE constexpr void Y(T& v, typename vec_traits<T>::scalar_type s) { return vec_traits<T>::Y(v,s); } 
    template<detail::vec_type T> requires detail::vec_z_write<T> SQUIGGLE_INLINE constexpr void Z(T& v, typename vec_traits<T>::scalar_type s) { return vec_traits<T>::Z(v,s); } 

    template<detail::vec_type T> requires detail::vec_w_write_ref<T> SQUIGGLE_INLINE constexpr void W(T& v, typename vec_traits<T>::scalar_type s) { vec_traits<T>::W(v) = s; } 
    template<detail::vec_type T> requires detail::vec_x_write_ref<T> SQUIGGLE_INLINE constexpr void X(T& v, typename vec_traits<T>::scalar_type s) { vec_traits<T>::X(v) = s; } 
    template<detail::vec_type T> requires detail::vec_y_write_ref<T> SQUIGGLE_INLINE constexpr void Y(T& v, typename vec_traits<T>::scalar_type s) { vec_traits<T>::Y(v) = s; } 
    template<detail::vec_type T> requires detail::vec_z_write_ref<T> SQUIGGLE_INLINE constexpr void Z(T& v, typename vec_traits<T>::scalar_type s) { vec_traits<T>::Z(v) = s; } 

    template<typename T1, typename T2> 
    SQUIGGLE_INLINE constexpr T1 convert_to( const T2& other )
    {
        T1 v;
        assign(v, other);
        return v;
    }

    template<int row1, int col1, int row2, int col2, typename M>
    SQUIGGLE_INLINE constexpr void mat_swap_element( M& m )
    {
        static_assert( row1 != row2 || col1 != col2, "Swapping onto same element, potential bug!" );
        mat_scalar<M> temp = A<row1,col1>(m);
        A<row1,col1>(m,A<row2,col2>(m));
        A<row2,col2>(m,temp);
    }
}