#pragma once
#include "sqg_concepts.h"
namespace sqg
{
    // ========== Structures ========== //

    // 2 dimensions
    template<typename T>
    struct mat22
    {
        T a[2][2]{};

        template<typename R>
        inline constexpr operator R() const {
            R r;
            assign(r, *this);
            return r;
        }
    };

    template<typename T>
    struct vec2
    {
        T x{};
        T y{};

        template<typename R>
        inline constexpr operator R() const {
            R r;
            assign(r, *this);
            return r;
        }
    };

    // 3 dimensions
    template<typename T>
    struct mat33
    {
        T a[3][3]{};

        template<typename R>
        inline constexpr operator R() const {
            R r;
            assign(r, *this);
            return r;
        }
    };

    template<typename T>
    struct vec3
    {
        T x{};
        T y{};
        T z{};

        template<typename R>
        inline constexpr operator R() const {
            R r;
            assign(r, *this);
            return r;
        }
    };

    // 4 dimensions
    template<typename T>
    struct mat44
    {
        T a[4][4]{};

        template<typename R>
        inline constexpr explicit operator R() const {
            R r;
            assign(r, *this);
            return r;
        }
    };

    template<typename T>
    struct vec4
    {
        T x{};
        T y{};
        T z{};
        T w{};

        template<typename R>
        inline constexpr explicit operator R() const {
            R r;
            assign(r, *this);
            return r;
        }
    };

    // quaternion - same as vec4 essentially

    template<std::floating_point T>
    struct quat
    {   // Initialise to identity
        T w{1};
        T x{0};
        T y{0};
        T z{0};
    };

    // ========== Traits ========== //

    // 2 dimensions
    template<typename T>
    struct mat_traits<mat22<T>>
    {
        using scalar_type = T;
        using type = mat22<T>;
        static constexpr int n_dims = 2;

        template<int row, int col> static inline constexpr scalar_type A(const type& m) { return m.a[row][col]; }
        template<int row, int col> static inline constexpr scalar_type& A(type& m) { return m.a[row][col]; }
    };

    template<typename T>
    struct vec_traits<vec2<T>>
    {
        using scalar_type = T;
        using type = vec2<T>;
        static constexpr int n_dims = 2;

        static inline constexpr scalar_type X(const type& v) { return v.x; }
        static inline constexpr scalar_type Y(const type& v) { return v.y; }

        static inline constexpr scalar_type& X(type& v) { return v.x; }
        static inline constexpr scalar_type& Y(type& v) { return v.y; }
    };

    // 3 dimensions
    template<typename T>
    struct mat_traits<mat33<T>>
    {
        using scalar_type = T;
        using type = mat33<T>;
        static constexpr int n_dims = 3;

        template<int row, int col> static inline constexpr scalar_type A(const type& m) { return m.a[row][col]; }
        template<int row, int col> static inline constexpr scalar_type& A(type& m) { return m.a[row][col]; }
    };

    template<typename T>
    struct vec_traits<vec3<T>>
    {
        using scalar_type = T;
        using type = vec3<T>;
        static constexpr int n_dims = 3;

        static inline constexpr scalar_type X(const type& v) { return v.x; }
        static inline constexpr scalar_type Y(const type& v) { return v.y; }
        static inline constexpr scalar_type Z(const type& v) { return v.z; }

        static inline constexpr scalar_type& X(type& v) { return v.x; }
        static inline constexpr scalar_type& Y(type& v) { return v.y; }
        static inline constexpr scalar_type& Z(type& v) { return v.z; }
    };

    // 4 dimensions
    template<typename T>
    struct mat_traits<mat44<T>>
    {
        using scalar_type = T;
        using type = mat44<T>;
        static constexpr int n_dims = 4;

        template<int row, int col> static inline constexpr scalar_type A(const type& m) { return m.a[row][col]; }
        template<int row, int col> static inline constexpr scalar_type& A(type& m) { return m.a[row][col]; }
    };

    template<typename T>
    struct vec_traits<vec4<T>>
    {
        using scalar_type = T;
        using type = vec4<T>;
        static constexpr int n_dims = 4;

        static inline constexpr scalar_type X(const type& v) { return v.x; }
        static inline constexpr scalar_type Y(const type& v) { return v.y; }
        static inline constexpr scalar_type Z(const type& v) { return v.z; }
        static inline constexpr scalar_type W(const type& v) { return v.w; }

        static inline constexpr scalar_type& X(type& v) { return v.x; }
        static inline constexpr scalar_type& Y(type& v) { return v.y; }
        static inline constexpr scalar_type& Z(type& v) { return v.z; }
        static inline constexpr scalar_type& W(type& v) { return v.w; }
    };

    // quat
    template<typename T>
    struct vec_traits<quat<T>>
    {
        using scalar_type = T;
        using type = quat<T>;
        static constexpr int n_dims = 4;

        static inline constexpr scalar_type W(const type& v) { return v.w; }
        static inline constexpr scalar_type X(const type& v) { return v.x; }
        static inline constexpr scalar_type Y(const type& v) { return v.y; }
        static inline constexpr scalar_type Z(const type& v) { return v.z; }

        static inline constexpr scalar_type& W(type& v) { return v.w; }
        static inline constexpr scalar_type& X(type& v) { return v.x; }
        static inline constexpr scalar_type& Y(type& v) { return v.y; }
        static inline constexpr scalar_type& Z(type& v) { return v.z; }
    };

    // Setup Deduction for Return Types
    // Select native vec2 over other vectors

    template<typename T, typename V> struct deduce_vec_traits<V, vec2<T>> { using traits = vec_traits<vec2<T>>; };
    template<typename T, typename V> struct deduce_vec_traits<V, vec3<T>> { using traits = vec_traits<vec3<T>>; };
    template<typename T, typename V> struct deduce_vec_traits<V, vec4<T>> { using traits = vec_traits<vec4<T>>; };

    template<typename T, typename V> struct deduce_mat_traits<V, mat22<T>> { using traits = mat_traits<mat22<T>>; };
    template<typename T, typename V> struct deduce_mat_traits<V, mat33<T>> { using traits = mat_traits<mat33<T>>; };
    template<typename T, typename V> struct deduce_mat_traits<V, mat44<T>> { using traits = mat_traits<mat44<T>>; };
}

namespace sqg::detail
{
    template<typename T, int dims>
    struct vec_type_dims;
    
    template<typename T>
    struct vec_type_dims<T,2>
    {
        using vec_type = vec2<T>;
        static constexpr vec2<T> zero_vector = { T{0}, T{0} };
    };

    template<typename T>
    struct vec_type_dims<T,3>
    {
        using vec_type = vec3<T>;
        static constexpr vec3<T> zero_vector = { T{0}, T{0}, T{0} };
    };

    template<typename T>
    struct vec_type_dims<T,4>
    {
        using vec_type = vec4<T>;
        static constexpr vec4<T> zero_vector = { T{0}, T{0}, T{0}, T{0} };
    };

    template<typename T, int dims>
    struct mat_type_dims;
    
    template<typename T>
    struct mat_type_dims<T,2>
    {
        using mat_type = mat22<T>;
    };

    template<typename T>
    struct mat_type_dims<T,3>
    {
        using mat_type = mat33<T>;
    };

    template<typename T>
    struct mat_type_dims<T,4>
    {
        using mat_type = mat44<T>;
    };
}