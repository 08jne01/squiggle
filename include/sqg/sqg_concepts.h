#pragma once
#include <concepts>

namespace sqg
{
    template<typename T>
    struct vec_traits;

    template<typename T>
    struct mat_traits;
}


namespace sqg::detail
{
    template<typename T>
    concept vec_type = requires(T v) {
        requires std::same_as<typename vec_traits<T>::type, T>;
        { vec_traits<T>::n_dims };
        { typename vec_traits<T>::scalar_type{} };
        { typename vec_traits<T>::scalar_type{0} };
        { typename vec_traits<T>::scalar_type{1} };
    };

    template<typename T>
    concept vec_x_access = requires(const T cv, T v) {
        { vec_traits<T>::X(cv) } -> std::same_as<typename vec_traits<T>::scalar_type>;
        { vec_traits<T>::X(v) } -> std::same_as<typename vec_traits<T>::scalar_type&>;
    };

    template<typename T>
    concept vec_y_access = requires(const T cv, T v) {
        { vec_traits<T>::Y(cv) } -> std::same_as<typename vec_traits<T>::scalar_type>;
        { vec_traits<T>::Y(v) } -> std::same_as<typename vec_traits<T>::scalar_type&>;
    };

    template<typename T>
    concept vec_z_access = requires(const T cv, T v) {
        { vec_traits<T>::Z(cv) } -> std::same_as<typename vec_traits<T>::scalar_type>;
        { vec_traits<T>::Z(v) } -> std::same_as<typename vec_traits<T>::scalar_type&>;
    };

    template<typename T>
    concept vec_w_access = requires(const T cv, T v) {
        { vec_traits<T>::W(cv) } -> std::same_as<typename vec_traits<T>::scalar_type>;
        { vec_traits<T>::W(v) } -> std::same_as<typename vec_traits<T>::scalar_type&>;
    };

    template<typename T>
    concept mat_type = requires(T v) {
        requires std::same_as<typename mat_traits<T>::type, T>;
        { mat_traits<T>::n_dims };
        { typename mat_traits<T>::scalar_type{} };
        { typename mat_traits<T>::scalar_type{0} };
        { typename mat_traits<T>::scalar_type{1} };
    };

    template<typename T, int row, int col>
    concept mat_access = requires( const T cm, T m ) {
        { mat_traits<T>::template A<row,col>(cm) } -> std::same_as<typename mat_traits<T>::scalar_type>;
        { mat_traits<T>::template A<row,col>(m) } -> std::same_as<typename mat_traits<T>::scalar_type&>;
    };

    // 2 dimensions
    template<typename T>
    concept vec2_type = requires(const T cv, T v) {
        requires vec_type<T>;
        requires vec_traits<T>::n_dims == 2;
        requires vec_x_access<T>;
        requires vec_y_access<T>;
    };

    template<typename T>
    concept mat22_type = requires( const T cm, T m ) {
        requires mat_type<T>;
        requires mat_traits<T>::n_dims == 2;
        requires mat_access<T,0,0>;
        requires mat_access<T,0,1>;
        requires mat_access<T,1,0>;
        requires mat_access<T,1,1>;
    };

    // 3 dimensions
    template<typename T>
    concept vec3_type = requires(const T cv, T v) {
        requires vec_type<T>;
        requires vec_traits<T>::n_dims == 3;
        requires vec_x_access<T>;
        requires vec_y_access<T>;
        requires vec_z_access<T>;
    };

    template<typename T>
    concept mat33_type = requires( const T cm, T m ) {
        requires mat_type<T>;
        requires mat_traits<T>::n_dims == 3;
        requires mat_access<T,0,0>;
        requires mat_access<T,0,1>;
        requires mat_access<T,0,2>;

        requires mat_access<T,1,0>;
        requires mat_access<T,1,1>;
        requires mat_access<T,1,2>;

        requires mat_access<T,2,0>;
        requires mat_access<T,2,1>;
        requires mat_access<T,2,2>; 
    };

    // 4 dimensions
    template<typename T>
    concept vec4_type = requires(const T cv, T v) {
        requires vec_type<T>;
        requires vec_traits<T>::n_dims == 4;
        requires vec_x_access<T>;
        requires vec_y_access<T>;
        requires vec_z_access<T>;
        requires vec_w_access<T>;
    };

    template<typename T>
    concept quat_type = requires() {
        requires vec4_type<T>;
        requires std::floating_point<typename vec_traits<T>::scalar_type>;
    };

    template<typename T>
    concept mat44_type = requires( const T cm, T m ) {
        requires mat_type<T>;
        requires mat_traits<T>::n_dims == 4;

        requires mat_access<T,0,0>;
        requires mat_access<T,0,1>;
        requires mat_access<T,0,2>;
        requires mat_access<T,0,3>;

        requires mat_access<T,1,0>;
        requires mat_access<T,1,1>;
        requires mat_access<T,1,2>;
        requires mat_access<T,1,3>;

        requires mat_access<T,2,0>;
        requires mat_access<T,2,1>;
        requires mat_access<T,2,2>;
        requires mat_access<T,2,3>;

        requires mat_access<T,3,0>;
        requires mat_access<T,3,1>;
        requires mat_access<T,3,2>;
        requires mat_access<T,3,3>;
    };
}