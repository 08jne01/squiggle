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
        SQUIGGLE_INLINE constexpr operator R() const {
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
        SQUIGGLE_INLINE constexpr operator R() const {
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
        SQUIGGLE_INLINE constexpr operator R() const {
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
        SQUIGGLE_INLINE constexpr operator R() const {
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
        SQUIGGLE_INLINE constexpr explicit operator R() const {
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
        SQUIGGLE_INLINE constexpr explicit operator R() const {
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

        template<typename R>
        SQUIGGLE_INLINE constexpr explicit operator R() const {
            R r;
            assign(r, *this);
            return r;
        }
    };

    using vec2d = vec2<double>;
    using vec2f = vec2<float>;
    using vec2i = vec2<int>;

    using vec3d = vec3<double>;
    using vec3f = vec3<float>;
    using vec3i = vec3<int>;

    using vec4d = vec4<double>;
    using vec4f = vec4<float>;
    using vec4i = vec4<int>;

    using mat22d = mat22<double>;
    using mat22f = mat22<float>;
    using mat22i = mat22<int>;

    using mat33d = mat33<double>;
    using mat33f = mat33<float>;
    using mat33i = mat33<int>;

    using mat44d = mat44<double>;
    using mat44f = mat44<float>;
    using mat44i = mat44<int>;

    using quatd = quat<double>;
    using quatf = quat<float>;

    // ========== Traits ========== //

    // 2 dimensions
    template<typename T>
    struct mat_traits<mat22<T>>
    {
        using scalar_type = T;
        using type = mat22<T>;
        static constexpr int n_dims = 2;

        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type A(const type& m) { return m.a[row][col]; }
        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type& A(type& m) { return m.a[row][col]; }
    };

    template<typename T>
    struct vec_traits<vec2<T>>
    {
        using scalar_type = T;
        using type = vec2<T>;
        static constexpr int n_dims = 2;

        static SQUIGGLE_INLINE constexpr scalar_type X(const type& v) { return v.x; }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const type& v) { return v.y; }

        static SQUIGGLE_INLINE constexpr scalar_type& X(type& v) { return v.x; }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(type& v) { return v.y; }
    };

    // 3 dimensions
    template<typename T>
    struct mat_traits<mat33<T>>
    {
        using scalar_type = T;
        using type = mat33<T>;
        static constexpr int n_dims = 3;

        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type A(const type& m) { return m.a[row][col]; }
        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type& A(type& m) { return m.a[row][col]; }
    };

    template<typename T>
    struct vec_traits<vec3<T>>
    {
        using scalar_type = T;
        using type = vec3<T>;
        static constexpr int n_dims = 3;

        static SQUIGGLE_INLINE constexpr scalar_type X(const type& v) { return v.x; }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const type& v) { return v.y; }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const type& v) { return v.z; }

        static SQUIGGLE_INLINE constexpr scalar_type& X(type& v) { return v.x; }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(type& v) { return v.y; }
        static SQUIGGLE_INLINE constexpr scalar_type& Z(type& v) { return v.z; }
    };

    // 4 dimensions
    template<typename T>
    struct mat_traits<mat44<T>>
    {
        using scalar_type = T;
        using type = mat44<T>;
        static constexpr int n_dims = 4;

        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type A(const type& m) { return m.a[row][col]; }
        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type& A(type& m) { return m.a[row][col]; }
    };

    template<typename T>
    struct vec_traits<vec4<T>>
    {
        using scalar_type = T;
        using type = vec4<T>;
        static constexpr int n_dims = 4;

        static SQUIGGLE_INLINE constexpr scalar_type X(const type& v) { return v.x; }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const type& v) { return v.y; }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const type& v) { return v.z; }
        static SQUIGGLE_INLINE constexpr scalar_type W(const type& v) { return v.w; }

        static SQUIGGLE_INLINE constexpr scalar_type& X(type& v) { return v.x; }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(type& v) { return v.y; }
        static SQUIGGLE_INLINE constexpr scalar_type& Z(type& v) { return v.z; }
        static SQUIGGLE_INLINE constexpr scalar_type& W(type& v) { return v.w; }
    };

    // quat
    template<typename T>
    struct vec_traits<quat<T>>
    {
        using scalar_type = T;
        using type = quat<T>;
        static constexpr int n_dims = 4;

        static SQUIGGLE_INLINE constexpr scalar_type W(const type& v) { return v.w; }
        static SQUIGGLE_INLINE constexpr scalar_type X(const type& v) { return v.x; }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const type& v) { return v.y; }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const type& v) { return v.z; }

        static SQUIGGLE_INLINE constexpr scalar_type& W(type& v) { return v.w; }
        static SQUIGGLE_INLINE constexpr scalar_type& X(type& v) { return v.x; }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(type& v) { return v.y; }
        static SQUIGGLE_INLINE constexpr scalar_type& Z(type& v) { return v.z; }
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