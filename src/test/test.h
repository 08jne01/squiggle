#pragma once
#include <array>
#include <random>
#include <sqg.h>

#include <sqg_vec.h>
#include <sqg_mat.h>
#include <sqg_mat_view.h>

#include <cassert>
namespace sqg_test
{
    template<typename T, int rows, int cols>
    using matrix = std::array<std::array<T,cols>,rows>; //T[rows][cols] ;// 

    template<typename T, int n_dims>
    using vector = std::array<T,n_dims>;

    static inline constexpr matrix<int,4,4> basic_matrix = {{
        { 1, 2, 3, 4},
        { 5, 6, 7, 8},
        { 9,10,11,12},
        {13,14,15,16}
    }};

    static inline constexpr matrix<int,4,4> identity_matrix = {{
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    }};

    template<typename T, int rows, int cols>
    inline constexpr void set_basic_matrix(matrix<T,rows,cols>& A) 
    {
        for ( int row = 0; row < rows; row++ )
        {
            for ( int col = 0; col < cols; col++ )
            {
                A[row][col] = static_cast<T>(basic_matrix[row][col]);
            }
        }
    };

    template<typename T, int rows, int cols>
    inline constexpr void set_identity_matrix(matrix<T,rows,cols>& A) 
    {
        for ( int row = 0; row < rows; row++ )
        {
            for ( int col = 0; col < cols; col++ )
            {
                A[row][col] = static_cast<T>(identity_matrix[row][col]);
            }
        }
    };

    template<typename T, int n_dims>
    inline void set_basic_vector(vector<T,n_dims>& A)
    {
        for ( int dim = 0; dim < n_dims; dim++ )
        {
            A[dim] = static_cast<T>(basic_matrix[0][dim]);
        }
    }

    template<typename T>
    concept not_number = !std::integral<T> && !std::floating_point<T>;

    template<not_number TyDistribution, typename T, int rows, int cols>
    inline constexpr void set_random_matrix( TyDistribution distribution, std::mt19937& generator, matrix<T,rows,cols>& A) 
    {
        for ( int row = 0; row < rows; row++ )
        {
            for ( int col = 0; col < cols; col++ )
            {
                A[row][col] = distribution(generator);
            }
        }
    }

    template<not_number TyDistribution, typename T, int n_dims>
    inline void set_random_vector(TyDistribution distribution, std::mt19937& generator, vector<T,n_dims>& A)
    {
        for ( int dim = 0; dim < n_dims; dim++ )
        {
            A[dim] = distribution(generator);
        }
    }

    template<typename T, int rows, int cols>
    inline void transpose( matrix<T,rows,cols>& A )
    {
        matrix<T,rows,cols> copy = A;
        for ( int row = 0; row < rows; row++ )
        {
            for ( int col = 0; col < cols; col++ )
            {
                A[row][col] = copy[col][row];
            }
        }
    }

    template<std::floating_point T, int rows, int cols>
    inline constexpr void set_random_matrix(std::mt19937& generator, matrix<T,rows,cols>& A, T min, T max) 
    {
        std::uniform_real_distribution<T> distribution{ min, max };
        set_random_matrix<decltype(distribution), T, rows, cols>( distribution, generator, A );
    };

    template<std::floating_point T, int n_dims>
    inline void set_random_vector(std::mt19937& generator, vector<T,n_dims>& A, T min, T max)
    {
        std::uniform_real_distribution<T> distribution{ min, max };
        set_random_vector<decltype(distribution), T,n_dims>(distribution, generator, A);
    }

    template<std::integral T, int rows, int cols>
    inline constexpr void set_random_matrix(std::mt19937& generator, matrix<T,rows,cols>& A, T min, T max) 
    {
        std::uniform_int_distribution<T> distribution{ min, max };
        set_random_matrix<decltype(distribution), T,rows,cols>(distribution, generator, A);
    };

    template<std::integral T, int n_dims>
    inline void set_random_vector(std::mt19937& generator, vector<T,n_dims>& A, T min, T max)
    {
        std::uniform_int_distribution<T> distribution{ min, max };
        set_random_vector<decltype(distribution), T,n_dims>(distribution, generator, A);
    }

    template<typename T, typename M>
    [[nodiscard]] bool vec_equal( const T& sqg_vector, const M& test_vector )
    {
        if constexpr ( sqg::vec_traits<T>::n_dims != sqg::vec_traits<M>::n_dims )
            return false;

        if constexpr ( sqg::vec_traits<T>::n_dims <= 2 )
        {
            if ( X(sqg_vector) != test_vector[0] )
                return false;

            if ( Y(sqg_vector) != test_vector[1] )
                return false;
        }

        if constexpr ( sqg::vec_traits<T>::n_dims <= 3 )
        {
            if ( Z(sqg_vector) != test_vector[2] )
                return false;
        }

        if constexpr ( sqg::vec_traits<T>::n_dims <= 4 )
        {
            if ( W(sqg_vector) != test_vector[3] )
                return false;
        }

        return true;
    }

    template<typename T, typename M>
    [[nodiscard]] bool mat_equal( const T& sqg_matrix, const M& test_matrix )
    {
        if constexpr ( sqg::mat_traits<T>::n_dims != sqg::mat_traits<M>::n_dims )
            return false;

        constexpr int dims = sqg::mat_traits<T>::n_dims;
        for ( int row = 0; row < dims; row++ )
        {
            for ( int col = 0; col < dims; col++ )
            {
                if ( sqg_matrix.a[row][col] != test_matrix[row][col] )
                    return false;
            }
        }

        return true;
    }
}

namespace sqg
{
    template<typename T>
    struct vec_traits<sqg_test::vector<T, 2>>
    {
        using scalar_type = T;
        using type = sqg_test::vector<T, 2>;
        static constexpr int n_dims = 2;
        static inline constexpr scalar_type X(const type& v) { return v[0]; }
        static inline constexpr scalar_type Y(const type& v) { return v[1]; }
        static inline constexpr scalar_type& X(type& v) { return v[0]; }
        static inline constexpr scalar_type& Y(type& v) { return v[1]; }

        using sqg_vector = sqg::vec2<T>;
    };

    template<typename T>
    struct vec_traits<sqg_test::vector<T, 3>>
    {
        using scalar_type = T;
        using type = sqg_test::vector<T, 3>;
        static constexpr int n_dims = 3;
        static inline constexpr scalar_type X(const type& v) { return v[0]; }
        static inline constexpr scalar_type Y(const type& v) { return v[1]; }
        static inline constexpr scalar_type Z(const type& v) { return v[2]; }
        static inline constexpr scalar_type& X(type& v) { return v[0]; }
        static inline constexpr scalar_type& Y(type& v) { return v[1]; }
        static inline constexpr scalar_type& Z(type& v) { return v[2]; }

        using sqg_vector = sqg::vec3<T>;
    };

    template<typename T>
    struct vec_traits<sqg_test::vector<T, 4>>
    {
        using scalar_type = T;
        using type = sqg_test::vector<T, 4>;
        static constexpr int n_dims = 4;
        static inline constexpr scalar_type X(const type& v) { return v[0]; }
        static inline constexpr scalar_type Y(const type& v) { return v[1]; }
        static inline constexpr scalar_type Z(const type& v) { return v[2]; }
        static inline constexpr scalar_type W(const type& v) { return v[3]; }
        static inline constexpr scalar_type& X(type& v) { return v[0]; }
        static inline constexpr scalar_type& Y(type& v) { return v[1]; }
        static inline constexpr scalar_type& Z(type& v) { return v[2]; }
        static inline constexpr scalar_type& W(type& v) { return v[3]; }

        using sqg_vector = sqg::vec4<T>;
    };

    template<typename T>
    struct mat_traits<sqg_test::matrix<T,2,2>>
    {
        using scalar_type = T;
        using type = sqg_test::matrix<T, 2,2>;
        static constexpr int n_dims = 2;
        template<int row, int col> static inline constexpr scalar_type A(const type& m) { assert( row < n_dims && col < n_dims ); return m[row][col]; }
        template<int row, int col> static inline constexpr scalar_type& A(type& m) { assert( row < n_dims && col < n_dims ); return m[row][col]; }

        using sqg_matrix = sqg::mat22<T>;
    };

    template<typename T>
    struct mat_traits<sqg_test::matrix<T,3,3>>
    {
        using scalar_type = T;
        using type = sqg_test::matrix<T, 3,3>;
        static constexpr int n_dims = 3;
        template<int row, int col> static inline constexpr scalar_type A(const type& m) { assert( row < n_dims && col < n_dims ); return m[row][col]; }
        template<int row, int col> static inline constexpr scalar_type& A(type& m) { assert( row < n_dims && col < n_dims ); return m[row][col]; }

        using sqg_matrix = sqg::mat33<T>;
    };

    template<typename T>
    struct mat_traits<sqg_test::matrix<T,4,4>>
    {
        using scalar_type = T;
        using type = sqg_test::matrix<T, 4,4>;
        static constexpr int n_dims = 4;
        template<int row, int col> static inline constexpr scalar_type A(const type& m) { assert( row < n_dims && col < n_dims ); return m[row][col]; }
        template<int row, int col> static inline constexpr scalar_type& A(type& m) { assert( row < n_dims && col < n_dims ); return m[row][col]; }

        using sqg_matrix = sqg::mat44<T>;
    };
}