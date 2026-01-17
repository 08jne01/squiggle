#pragma once
#include "sqg_concepts.h"
#include "sqg_struct.h"
#include "sqg_traits.h"

namespace sqg::detail
{
    template<typename V, typename M>
    concept valid_read_vec_view = 
        (mat_traits<M>::n_dims == 2 && read_vec2_type<V>) ||
        (mat_traits<M>::n_dims == 3 && read_vec3_type<V>) ||
        (mat_traits<M>::n_dims == 4 && read_vec4_type<V>);

    template<typename V, typename M>
    concept valid_vec_view = 
        (mat_traits<M>::n_dims == 2 && vec2_type<V>) ||
        (mat_traits<M>::n_dims == 3 && vec3_type<V>) ||
        (mat_traits<M>::n_dims == 4 && vec4_type<V>);

    template<typename V, typename M>
    concept valid_read_mat_view = 
        (mat_traits<M>::n_dims == 2 && read_mat22_type<V>) ||
        (mat_traits<M>::n_dims == 3 && read_mat33_type<V>) ||
        (mat_traits<M>::n_dims == 4 && read_mat44_type<V>);
}

namespace sqg
{
    template<detail::mat_type M, int row>
    struct read_row_view
    {
        const M& matrix;
        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        static_assert( detail::valid_read_vec_view<read_row_view,M>, "Must Satisfy read vec constraints" );
    };


    template<detail::mat_type M, int col>
    struct read_col_view
    {
        const M& matrix;
        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        static_assert( detail::valid_read_vec_view<read_col_view,M>, "Must Satisfy read vec constraints" );
    };


    // because we need const matrices to pass their const through to the reference
    template<detail::mat_type M, int row>
    struct row_view
    {
        M& matrix;

        template<detail::vec_type V>
        SQUIGGLE_INLINE constexpr row_view& operator=( const V& vector )
        {
            assign(*this, vector);
            return *this;
        }

        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        static_assert( detail::valid_vec_view<row_view,M>, "Must Satisfy vec constraints" );
    };

    template<detail::mat_type M, int row>
    struct col_view
    {
        M& matrix;

        template<detail::vec_type V>
        SQUIGGLE_INLINE constexpr col_view& operator=( const V& vector )
        {
            assign(*this, vector);
            return *this;
        }

        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        static_assert( detail::valid_vec_view<col_view,M>, "Must Satisfy vec constraints" );
    };

    template<detail::read_mat22_type M, int row>
    struct vec_traits<read_row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = sqg::vec2<scalar_type>;
        using view = read_row_view<M,row>;
        static constexpr int n_dims = 2;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<row,0>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<row,1>(v.matrix); }
    };

    template<detail::mat22_type M, int row>
    struct vec_traits<row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = sqg::vec2<scalar_type>;
        using view = row_view<M,row>;
        static constexpr int n_dims = 2;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<row,0>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<row,1>(v.matrix); }

        static SQUIGGLE_INLINE constexpr scalar_type& X(view& v) { return A<row,0>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(view& v) { return A<row,1>(v.matrix); }
    };

    template<int row, detail::mat22_type M, detail::read_vec2_type V>
    SQUIGGLE_INLINE constexpr void assign( row_view<M,row> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
    }

    template<detail::read_mat33_type M, int row>
    struct vec_traits<read_row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec3<scalar_type>;
        using view = read_row_view<M,row>;
        static constexpr int n_dims = 3;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<row,0>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<row,1>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<row,2>(v.matrix); }
    };

    template<detail::mat33_type M, int row>
    struct vec_traits<row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec3<scalar_type>;
        using view = row_view<M,row>;
        static constexpr int n_dims = 3;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<row,0>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<row,1>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<row,2>(v.matrix); }

        static SQUIGGLE_INLINE constexpr scalar_type& X(view& v) { return A<row,0>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(view& v) { return A<row,1>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Z(view& v) { return A<row,2>(v.matrix); }
    };

    template<int row, detail::mat33_type M, detail::read_vec3_type V>
    SQUIGGLE_INLINE constexpr void assign( row_view<M,row> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
        Z(view) = Z(vector);
    }

    template<detail::read_mat44_type M, int row>
    struct vec_traits<read_row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec4<scalar_type>;
        using view = read_row_view<M,row>;
        static constexpr int n_dims = 4;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<row,0>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<row,1>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<row,2>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type W(const view& v) { return A<row,3>(v.matrix); }
    };

    template<detail::mat44_type M, int row>
    struct vec_traits<row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec4<scalar_type>;
        using view = row_view<M,row>;
        static constexpr int n_dims = 4;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<row,0>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<row,1>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<row,2>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type W(const view& v) { return A<row,3>(v.matrix); }

        static SQUIGGLE_INLINE constexpr scalar_type& X(view& v) { return A<row,0>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(view& v) { return A<row,1>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Z(view& v) { return A<row,2>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& W(view& v) { return A<row,3>(v.matrix); }
    };

    template<int row, detail::mat44_type M, detail::read_vec4_type V>
    SQUIGGLE_INLINE constexpr void assign( row_view<M,row> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
        Z(view) = Z(vector);
        W(view) = W(vector);
    }

    template<int row_index, detail::mat_type T>
    SQUIGGLE_INLINE constexpr read_row_view<T,row_index> row( const T& matrix )
    {
        return {matrix};
    }

    template<int row_index, detail::mat_type M>
    SQUIGGLE_INLINE constexpr row_view<M, row_index> row( M& matrix )
    {
        return {matrix};
    }

    template<detail::read_mat22_type M, int col>
    struct vec_traits<read_col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = sqg::vec2<scalar_type>;
        using view = read_col_view<M,col>;
        static constexpr int n_dims = 2;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<1,col>(v.matrix); }
    };

    template<detail::mat22_type M, int col>
    struct vec_traits<col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = sqg::vec2<scalar_type>;
        using view = col_view<M,col>;
        static constexpr int n_dims = 2;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<1,col>(v.matrix); }

        static SQUIGGLE_INLINE constexpr scalar_type& X(view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(view& v) { return A<1,col>(v.matrix); }
    };

    template<int col, detail::mat22_type M, detail::read_vec2_type V>
    SQUIGGLE_INLINE constexpr void assign( col_view<M,col> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
    }

    template<detail::read_mat33_type M, int col>
    struct vec_traits<read_col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec3<scalar_type>;
        using view = read_col_view<M,col>;
        static constexpr int n_dims = 3;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<1,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<2,col>(v.matrix); }
    };

    template<detail::mat33_type M, int col>
    struct vec_traits<col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec3<scalar_type>;
        using view = col_view<M,col>;
        static constexpr int n_dims = 3;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<1,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<2,col>(v.matrix); }

        static SQUIGGLE_INLINE constexpr scalar_type& X(view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(view& v) { return A<1,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Z(view& v) { return A<2,col>(v.matrix); }
    };

    template<int col, detail::mat33_type M, detail::read_vec3_type V>
    SQUIGGLE_INLINE constexpr void assign( col_view<M,col> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
        Z(view) = Z(vector);
    }

    template<detail::read_mat44_type M, int col>
    struct vec_traits<read_col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec4<scalar_type>;
        using view = read_col_view<M,col>;
        static constexpr int n_dims = 4;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<1,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<2,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type W(const view& v) { return A<3,col>(v.matrix); }
    };

    template<detail::mat44_type M, int col>
    struct vec_traits<col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec4<scalar_type>;
        using view = col_view<M,col>;
        static constexpr int n_dims = 4;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<1,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<2,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type W(const view& v) { return A<3,col>(v.matrix); }

        static SQUIGGLE_INLINE constexpr scalar_type& X(view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(view& v) { return A<1,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Z(view& v) { return A<2,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& W(view& v) { return A<3,col>(v.matrix); }
    };

    template<int col, detail::mat44_type M, detail::read_vec4_type V>
    SQUIGGLE_INLINE constexpr void assign( col_view<M,col> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
        Z(view) = Z(vector);
        W(view) = W(vector);
    }

    template<int col_index, detail::mat_type T>
    SQUIGGLE_INLINE constexpr read_col_view<T,col_index> col( const T& matrix )
    {
        return {matrix};
    }

    template<int col_index, detail::mat_type M>
    SQUIGGLE_INLINE constexpr col_view<M, col_index> col( M& matrix )
    {
        return {matrix};
    }

    template<detail::mat_type M>
    struct transposed_view
    {
        const M& matrix;
        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        //static_assert( detail::valid_read_mat_view<transposed_view,M>, "Must Satisfy read mat constraints" );
    };

    template<detail::read_mat22_type M>
    struct mat_traits<transposed_view<M>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = sqg::mat22<scalar_type>;
        using view = transposed_view<M>;
        static constexpr int n_dims = 2;

        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type A(const view& m) { return mat_traits<M>::template A<col,row>(m.matrix); }
    };

    template<detail::read_mat33_type M>
    struct mat_traits<transposed_view<M>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = sqg::mat33<scalar_type>;
        using view = transposed_view<M>;
        static constexpr int n_dims = 3;

        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type A(const view& m) { return mat_traits<M>::template A<col,row>(m.matrix); }
    };

    template<detail::read_mat44_type M>
    struct mat_traits<transposed_view<M>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = sqg::mat44<scalar_type>;
        using view = transposed_view<M>;
        static constexpr int n_dims = 4;
        
        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type A(const view& m) { return mat_traits<M>::template A<col,row>(m.matrix); }
    };

    template<detail::mat_type M>
    SQUIGGLE_INLINE constexpr transposed_view<M> transposed( const M& matrix )
    {
        return {matrix};
    }

    template<detail::mat44_type M>
    struct read_orientation_view
    {
        const M& matrix;

        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        static_assert( detail::read_mat33_type<read_orientation_view>, "Must Satisfy read mat33 constraints" );
    };

    template<detail::mat44_type M44>
    struct orientation_view
    {
        M44& matrix;

        template<detail::read_mat33_type M33>
        SQUIGGLE_INLINE constexpr orientation_view& operator=( const M33& matrix )
        {
            assign(*this, matrix);
            return *this;
        }

        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        static_assert( detail::mat33_type<orientation_view>, "Must Satisfy mat33 constraints" );
    };

    template<detail::mat44_type M>
    struct mat_traits<orientation_view<M>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = mat33<scalar_type>;
        using view = orientation_view<M>;
        static constexpr int n_dims = 3;
        
        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type A(const view& m) { return mat_traits<M>::template A<row,col>(m.matrix); }
        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type& A(view& m) { return mat_traits<M>::template A<row,col>(m.matrix); }
    };

    template<detail::mat44_type M44, detail::read_mat33_type M33>
    void assign( orientation_view<M44> view, const M33& matrix )
    {
        A00(view) = A00(matrix);
        A01(view) = A01(matrix);
        A02(view) = A02(matrix);

        A10(view) = A10(matrix);
        A11(view) = A11(matrix);
        A12(view) = A12(matrix);

        A20(view) = A20(matrix);
        A21(view) = A21(matrix);
        A22(view) = A22(matrix);
    }

    template<detail::mat44_type M>
    struct mat_traits<read_orientation_view<M>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = mat33<scalar_type>;
        using view = read_orientation_view<M>;
        static constexpr int n_dims = 3;
        
        template<int row, int col> static SQUIGGLE_INLINE constexpr scalar_type A(const view& m) { return mat_traits<M>::template A<row,col>(m.matrix); }
    };

    template<detail::mat44_type M>
    struct read_position_view
    {
        const M& matrix;

        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        static_assert( detail::read_vec3_type<read_position_view>, "Must Satisfy read vec3 constraints" );
    };

    template<detail::mat44_type M44>
    struct position_view
    {
        M44& matrix;

        template<detail::read_vec3_type V>
        SQUIGGLE_INLINE constexpr position_view& operator=( const V& vector )
        {
            assign(*this, matrix);
            return *this;
        }

        template<typename R>
        SQUIGGLE_INLINE constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }

        static_assert( detail::vec3_type<position_view>, "Must Satisfy read vec3 constraints" );
    };

    template<detail::read_mat44_type M>
    struct vec_traits<read_position_view<M>>
    {
        static constexpr int col = 3;
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec3<scalar_type>;
        using view = read_position_view<M>;
        static constexpr int n_dims = 3;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<1,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<2,col>(v.matrix); }
    };

    template<detail::mat44_type M>
    struct vec_traits<position_view<M>>
    {
        static constexpr int col = 3;
        using scalar_type = mat_traits<M>::scalar_type;
        using type = vec3<scalar_type>;
        using view = read_position_view<M>;
        static constexpr int n_dims = 3;

        static SQUIGGLE_INLINE constexpr scalar_type X(const view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Y(const view& v) { return A<1,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type Z(const view& v) { return A<2,col>(v.matrix); }

        static SQUIGGLE_INLINE constexpr scalar_type& X(view& v) { return A<0,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Y(view& v) { return A<1,col>(v.matrix); }
        static SQUIGGLE_INLINE constexpr scalar_type& Z(view& v) { return A<2,col>(v.matrix); }
    };

    template<detail::mat44_type M>
    SQUIGGLE_INLINE constexpr read_orientation_view<M> orientation( const M& matrix )
    {
        return {matrix};
    }

    template<detail::mat44_type M>
    SQUIGGLE_INLINE constexpr orientation_view<M> orientation( M& matrix )
    {
        return {matrix};
    }

    template<detail::mat44_type M>
    SQUIGGLE_INLINE constexpr read_position_view<M> position( const M& matrix )
    {
        return {matrix};
    }

    template<detail::mat44_type M>
    SQUIGGLE_INLINE constexpr position_view<M> position( M& matrix )
    {
        return {matrix};
    }
}