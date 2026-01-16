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

    template<typename T, int n_dims>
    concept vec_type_n = requires(T v) {
        requires n_dims == vec_traits<T>::n_dims;
        requires vec_type<T>;
    };

    template<typename T>
    concept vec_x_read = requires(T cv) {
        { vec_traits<std::remove_const_t<T>>::X(cv) } -> std::same_as<typename vec_traits<std::remove_const_t<T>>::scalar_type>;
    };

    template<typename T>
    concept vec_x_write = requires(T v) {
        { vec_traits<T>::X(v) } -> std::same_as<typename vec_traits<T>::scalar_type&>;
    };

    template<typename T>
    concept vec_y_read = requires(T cv) {
        { vec_traits<std::remove_const_t<T>>::Y(cv) } -> std::same_as<typename vec_traits<std::remove_const_t<T>>::scalar_type>;
    };

    template<typename T>
    concept vec_y_write = requires(T v) {
        { vec_traits<T>::Y(v) } -> std::same_as<typename vec_traits<T>::scalar_type&>;
    };

    template<typename T>
    concept vec_z_read = requires(T cv) {
        { vec_traits<std::remove_const_t<T>>::Z(cv) } -> std::same_as<typename vec_traits<std::remove_const_t<T>>::scalar_type>;
    };

    template<typename T>
    concept vec_z_write = requires(T v) {
        { vec_traits<T>::Z(v) } -> std::same_as<typename vec_traits<T>::scalar_type&>;
    };

    template<typename T>
    concept vec_w_read = requires(T cv) {
        { vec_traits<std::remove_const_t<T>>::W(cv) } -> std::same_as<typename vec_traits<std::remove_const_t<T>>::scalar_type>;
    };

    template<typename T>
    concept vec_w_write = requires(T v) {
        { vec_traits<T>::W(v) } -> std::same_as<typename vec_traits<T>::scalar_type&>;
    };

    template<typename T>
    concept vec2_read = requires() {
        requires vec_type<T>;
        requires vec_x_read<const T>;
        requires vec_y_read<const T>;
    };

    template<typename T>
    concept vec2_write = requires() {
        requires vec_type<T>;
        requires vec_x_write<T>;
        requires vec_y_write<T>;
    };

    template<typename T>
    concept vec3_read = requires() {
        requires vec_type<T>;
        requires vec_x_read<const T>;
        requires vec_y_read<const T>;
        requires vec_z_read<const T>;
    };

    template<typename T>
    concept vec3_write = requires() {
        requires vec_type<T>;
        requires vec_x_write<T>;
        requires vec_y_write<T>;
        requires vec_z_write<T>;
    };

    template<typename T>
    concept vec4_read = requires() {
        requires vec_type<T>;
        requires vec_x_read<const T>;
        requires vec_y_read<const T>;
        requires vec_z_read<const T>;
        requires vec_w_read<const T>;
    };

    template<typename T>
    concept vec4_write = requires() {
        requires vec_type<T>;
        requires vec_x_write<T>;
        requires vec_y_write<T>;
        requires vec_z_write<T>;
        requires vec_w_write<T>;
    };

    template<typename T>
    concept mat_type = requires(T v) {
        requires std::same_as<typename mat_traits<T>::type, T>;
        { mat_traits<T>::n_dims };
        { typename mat_traits<T>::scalar_type{} };
        { typename mat_traits<T>::scalar_type{0} };
        { typename mat_traits<T>::scalar_type{1} };
    };

    template<typename T, int n_dims>
    concept mat_type_n = requires() {
        requires n_dims == mat_traits<T>::n_dims;
        requires mat_type<T>;
    };

    template<typename T, int row, int col>
    concept mat_read = requires( T cm ) {
        { mat_traits<std::remove_const_t<T>>::template A<row,col>(cm) } -> std::same_as<typename mat_traits<std::remove_const_t<T>>::scalar_type>;
    };

    template<typename T, int row, int col>
    concept mat_write = requires( T m ) {
        { mat_traits<T>::template A<row,col>(m) } -> std::same_as<typename mat_traits<T>::scalar_type&>;
    };

    template<typename T>
    concept mat22_read = requires() {
        requires mat_read<const T, 0,0>;
        requires mat_read<const T, 0,1>;

        requires mat_read<const T, 1,0>;
        requires mat_read<const T, 1,1>;
    };

    template<typename T>
    concept mat22_write = requires() {
        requires mat_read<const T, 0,0>;
        requires mat_read<const T, 0,1>;

        requires mat_read<const T, 1,0>;
        requires mat_read<const T, 1,1>;
    };

    template<typename T>
    concept mat33_read = requires() {
        requires mat_read<const T, 0,0>;
        requires mat_read<const T, 0,1>;
        requires mat_read<const T, 0,2>;

        requires mat_read<const T, 1,0>;
        requires mat_read<const T, 1,1>;
        requires mat_read<const T, 1,2>;

        requires mat_read<const T, 2,0>;
        requires mat_read<const T, 2,1>;
        requires mat_read<const T, 2,2>;
    };

    template<typename T>
    concept mat33_write = requires() {
        requires mat_read<const T, 0,0>;
        requires mat_read<const T, 0,1>;
        requires mat_read<const T, 0,2>;

        requires mat_read<const T, 1,0>;
        requires mat_read<const T, 1,1>;
        requires mat_read<const T, 1,2>;

        requires mat_read<const T, 2,0>;
        requires mat_read<const T, 2,1>;
        requires mat_read<const T, 2,2>;
    };

    template<typename T>
    concept mat44_read = requires() {
        requires mat_read<const T, 0,0>;
        requires mat_read<const T, 0,1>;
        requires mat_read<const T, 0,2>;
        requires mat_read<const T, 0,3>;

        requires mat_read<const T, 1,0>;
        requires mat_read<const T, 1,1>;
        requires mat_read<const T, 1,2>;
        requires mat_read<const T, 1,3>;

        requires mat_read<const T, 2,0>;
        requires mat_read<const T, 2,1>;
        requires mat_read<const T, 2,2>;
        requires mat_read<const T, 2,3>;

        requires mat_read<const T, 3,0>;
        requires mat_read<const T, 3,1>;
        requires mat_read<const T, 3,2>;
        requires mat_read<const T, 3,3>;
    };

    template<typename T>
    concept mat44_write = requires() {
        requires mat_write<const T, 0,0>;
        requires mat_write<const T, 0,1>;
        requires mat_write<const T, 0,2>;
        requires mat_write<const T, 0,3>;

        requires mat_write<const T, 1,0>;
        requires mat_write<const T, 1,1>;
        requires mat_write<const T, 1,2>;
        requires mat_write<const T, 1,3>;

        requires mat_write<const T, 2,0>;
        requires mat_write<const T, 2,1>;
        requires mat_write<const T, 2,2>;
        requires mat_write<const T, 2,3>;

        requires mat_write<const T, 3,0>;
        requires mat_write<const T, 3,1>;
        requires mat_write<const T, 3,2>;
        requires mat_write<const T, 3,3>;
    };



    // 2 dimensions
    template<typename T>
    concept vec2_type = requires() {
        requires vec_type_n<T,2>;
        requires vec2_read<T>;
        requires vec2_write<T>;
    };

    template<typename T>
    concept read_vec2_type = requires() {
        requires vec_type_n<T,2>;
        requires vec2_read<T>;
    };

    template<typename T>
    concept mat22_type = requires() {
        requires mat_type_n<T,2>;
        requires mat22_read<T>;
        requires mat22_write<T>;
    };

    template<typename T>
    concept read_mat22_type = requires() {
        requires mat_type_n<T,2>;
        requires mat22_read<T>;
    };

    // 3 dimensions
    template<typename T>
    concept vec3_type = requires(const T cv, T v) {
        requires vec_type_n<T,3>;
        requires vec3_read<T>;
        requires vec3_write<T>;
    };

    template<typename T>
    concept read_vec3_type = requires(const T cv, T v) {
        requires vec_type_n<T,3>;
        requires vec3_read<T>;
    };

    template<typename T>
    concept mat33_type = requires() {
        requires mat_type_n<T,3>;
        requires mat33_read<T>;
        requires mat33_write<T>;
    };

    template<typename T>
    concept read_mat33_type = requires() {
        requires mat_type_n<T,3>;
        requires mat33_read<T>;
    };

    // 4 dimensions
    template<typename T>
    concept vec4_type = requires() {
        requires vec_type_n<T,4>;
        requires vec4_read<T>;
        requires vec4_write<T>;
    };

    template<typename T>
    concept read_vec4_type = requires() {
        requires vec_type_n<T,4>;
        requires vec4_read<T>;
    };

    template<typename T>
    concept quat_type = requires() {
        requires vec4_type<T>;
        requires std::floating_point<typename vec_traits<T>::scalar_type>;
    };

    template<typename T>
    concept read_quat_type = requires() {
        requires read_vec4_type<T>;
        requires std::floating_point<typename vec_traits<T>::scalar_type>;
    };

    template<typename T>
    concept mat44_type = requires() {
        requires mat_type_n<T,4>;
        requires mat44_read<T>;
        requires mat44_write<T>;
    };

    template<typename T>
    concept read_mat44_type = requires() {
        requires mat_type_n<T,4>;
        requires mat44_read<T>;
        requires mat44_write<T>;
    };

}