#pragma once
#include "sqg_concepts.h"
#include "sqg_traits.h"

namespace sqg::detail
{
    template<typename M>
    concept mat_type_or_const = mat_type<M> || mat_type<std::remove_const_t<M>>;
}

namespace sqg
{
    template<detail::mat_type M, int row>
    struct read_row_view
    {
        const M& matrix;
        template<typename R>
        inline constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }
    };


    template<detail::mat_type M, int col>
    struct read_col_view
    {
        const M& matrix;
        template<typename R>
        inline constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }
    };


    // because we need const matrices to pass their const through to the reference
    template<detail::mat_type M, int row>
    struct row_view
    {
        M& matrix;

        template<detail::vec_type V>
        inline constexpr row_view& operator=( const V& vector )
        {
            assign(*this, vector);
            return *this;
        }

        template<typename R>
        inline constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }
    };

    template<detail::mat_type M, int row>
    struct col_view
    {
        M& matrix;

        template<detail::vec_type V>
        inline constexpr col_view& operator=( const V& vector )
        {
            assign(*this, vector);
            return *this;
        }

        template<typename R>
        inline constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }
    };

    template<detail::read_mat22_type M, int row>
    struct vec_traits<read_row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = read_row_view<M,row>;
        static constexpr int n_dims = 2;

        static inline constexpr scalar_type X(type v) { return A<row,0>(v.matrix); }
        static inline constexpr scalar_type Y(type v) { return A<row,1>(v.matrix); }
    };

    template<detail::mat22_type M, int row>
    struct vec_traits<row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = row_view<M,row>;
        static constexpr int n_dims = 2;

        static inline constexpr scalar_type X(const type& v) { return A<row,0>(v.matrix); }
        static inline constexpr scalar_type Y(const type& v) { return A<row,1>(v.matrix); }

        static inline constexpr scalar_type& X(type& v) { return A<row,0>(v.matrix); }
        static inline constexpr scalar_type& Y(type& v) { return A<row,1>(v.matrix); }
    };

    template<int row, detail::mat22_type M, detail::read_vec2_type V>
    inline constexpr void assign( row_view<M,row> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
    }

    template<detail::read_mat33_type M, int row>
    struct vec_traits<read_row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = read_row_view<M,row>;
        static constexpr int n_dims = 3;

        static inline constexpr scalar_type X(type v) { return A<row,0>(v.matrix); }
        static inline constexpr scalar_type Y(type v) { return A<row,1>(v.matrix); }
        static inline constexpr scalar_type Z(type v) { return A<row,2>(v.matrix); }
    };

    template<detail::mat33_type M, int row>
    struct vec_traits<row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = row_view<M,row>;
        static constexpr int n_dims = 3;

        static inline constexpr scalar_type X(const type& v) { return A<row,0>(v.matrix); }
        static inline constexpr scalar_type Y(const type& v) { return A<row,1>(v.matrix); }
        static inline constexpr scalar_type Z(const type& v) { return A<row,2>(v.matrix); }

        static inline constexpr scalar_type& X(type& v) { return A<row,0>(v.matrix); }
        static inline constexpr scalar_type& Y(type& v) { return A<row,1>(v.matrix); }
        static inline constexpr scalar_type& Z(type& v) { return A<row,2>(v.matrix); }
    };

    template<int row, detail::mat33_type M, detail::read_vec3_type V>
    inline constexpr void assign( row_view<M,row> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
        Z(view) = Z(vector);
    }

    template<detail::read_mat44_type M, int row>
    struct vec_traits<read_row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = read_row_view<M,row>;
        static constexpr int n_dims = 4;

        static inline constexpr scalar_type X(type v) { return A<row,0>(v.matrix); }
        static inline constexpr scalar_type Y(type v) { return A<row,1>(v.matrix); }
        static inline constexpr scalar_type Z(type v) { return A<row,2>(v.matrix); }
        static inline constexpr scalar_type W(type v) { return A<row,4>(v.matrix); }
    };

    template<detail::mat44_type M, int row>
    struct vec_traits<row_view<M,row>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = row_view<M,row>;
        static constexpr int n_dims = 4;

        static inline constexpr scalar_type X(const type& v) { return A<row,0>(v.matrix); }
        static inline constexpr scalar_type Y(const type& v) { return A<row,1>(v.matrix); }
        static inline constexpr scalar_type Z(const type& v) { return A<row,2>(v.matrix); }
        static inline constexpr scalar_type W(const type& v) { return A<row,4>(v.matrix); }

        static inline constexpr scalar_type& X(type& v) { return A<row,0>(v.matrix); }
        static inline constexpr scalar_type& Y(type& v) { return A<row,1>(v.matrix); }
        static inline constexpr scalar_type& Z(type& v) { return A<row,2>(v.matrix); }
        static inline constexpr scalar_type& W(type& v) { return A<row,4>(v.matrix); }
    };

    template<int row, detail::mat44_type M, detail::read_vec4_type V>
    inline constexpr void assign( row_view<M,row> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
        Z(view) = Z(vector);
        W(view) = W(vector);
    }

    template<int row_index, detail::mat_type T>
    inline constexpr read_row_view<T,row_index> row( const T& matrix )
    {
        return {matrix};
    }

    template<int row_index, detail::mat_type M>
    inline constexpr row_view<M, row_index> row( M& matrix )
    {
        return {matrix};
    }

    template<detail::read_mat22_type M, int col>
    struct vec_traits<read_col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = read_col_view<M,col>;
        static constexpr int n_dims = 2;

        static inline constexpr scalar_type X(type v) { return A<0,col>(v.matrix); }
        static inline constexpr scalar_type Y(type v) { return A<1,col>(v.matrix); }
    };

    template<detail::mat22_type M, int col>
    struct vec_traits<col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = col_view<M,col>;
        static constexpr int n_dims = 2;

        static inline constexpr scalar_type X(const type& v) { return A<0,col>(v.matrix); }
        static inline constexpr scalar_type Y(const type& v) { return A<1,col>(v.matrix); }

        static inline constexpr scalar_type& X(type& v) { return A<0,col>(v.matrix); }
        static inline constexpr scalar_type& Y(type& v) { return A<1,col>(v.matrix); }
    };

    template<int col, detail::mat22_type M, detail::read_vec2_type V>
    inline constexpr void assign( col_view<M,col> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
    }

    template<detail::read_mat33_type M, int col>
    struct vec_traits<read_col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = read_col_view<M,col>;
        static constexpr int n_dims = 3;

        static inline constexpr scalar_type X(type v) { return A<0,col>(v.matrix); }
        static inline constexpr scalar_type Y(type v) { return A<1,col>(v.matrix); }
        static inline constexpr scalar_type Z(type v) { return A<2,col>(v.matrix); }
    };

    template<detail::mat33_type M, int col>
    struct vec_traits<col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = col_view<M,col>;
        static constexpr int n_dims = 3;

        static inline constexpr scalar_type X(const type& v) { return A<0,col>(v.matrix); }
        static inline constexpr scalar_type Y(const type& v) { return A<1,col>(v.matrix); }
        static inline constexpr scalar_type Z(const type& v) { return A<2,col>(v.matrix); }

        static inline constexpr scalar_type& X(type& v) { return A<0,col>(v.matrix); }
        static inline constexpr scalar_type& Y(type& v) { return A<1,col>(v.matrix); }
        static inline constexpr scalar_type& Z(type& v) { return A<2,col>(v.matrix); }
    };

    template<int col, detail::mat33_type M, detail::read_vec3_type V>
    inline constexpr void assign( col_view<M,col> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
        Z(view) = Z(vector);
    }

    template<detail::read_mat44_type M, int col>
    struct vec_traits<read_col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = read_col_view<M,col>;
        static constexpr int n_dims = 4;

        static inline constexpr scalar_type X(type v) { return A<0,col>(v.matrix); }
        static inline constexpr scalar_type Y(type v) { return A<1,col>(v.matrix); }
        static inline constexpr scalar_type Z(type v) { return A<2,col>(v.matrix); }
        static inline constexpr scalar_type W(type v) { return A<4,col>(v.matrix); }
    };

    template<detail::mat44_type M, int col>
    struct vec_traits<col_view<M,col>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = col_view<M,col>;
        static constexpr int n_dims = 4;

        static inline constexpr scalar_type X(const type& v) { return A<0,col>(v.matrix); }
        static inline constexpr scalar_type Y(const type& v) { return A<1,col>(v.matrix); }
        static inline constexpr scalar_type Z(const type& v) { return A<2,col>(v.matrix); }
        static inline constexpr scalar_type W(const type& v) { return A<4,col>(v.matrix); }

        static inline constexpr scalar_type& X(type& v) { return A<0,col>(v.matrix); }
        static inline constexpr scalar_type& Y(type& v) { return A<1,col>(v.matrix); }
        static inline constexpr scalar_type& Z(type& v) { return A<2,col>(v.matrix); }
        static inline constexpr scalar_type& W(type& v) { return A<4,col>(v.matrix); }
    };

    template<int col, detail::mat44_type M, detail::read_vec4_type V>
    inline constexpr void assign( col_view<M,col> view, const V& vector )
    {
        X(view) = X(vector);
        Y(view) = Y(vector);
        Z(view) = Z(vector);
        W(view) = W(vector);
    }

    template<int col_index, detail::mat_type T>
    inline constexpr read_col_view<T,col_index> col( const T& matrix )
    {
        return {matrix};
    }

    template<int col_index, detail::mat_type M>
    inline constexpr col_view<M, col_index> col( M& matrix )
    {
        return {matrix};
    }

    template<detail::mat_type M>
    struct transposed_view
    {
        const M& matrix;
        template<typename R>
        inline constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }
    };

    template<detail::read_mat22_type M>
    struct mat_traits<transposed_view<M>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = transposed_view<M>;
        static constexpr int n_dims = 2;

        template<int row, int col> static inline constexpr scalar_type A(const type& m) { return mat_traits<M>::template A<col,row>(m.matrix); }
    };

    template<detail::read_mat33_type M>
    struct mat_traits<transposed_view<M>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = transposed_view<M>;
        static constexpr int n_dims = 3;

        template<int row, int col> static inline constexpr scalar_type A(const type& m) { return mat_traits<M>::template A<col,row>(m.matrix); }
    };

    template<detail::read_mat44_type M>
    struct mat_traits<transposed_view<M>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = transposed_view<M>;
        static constexpr int n_dims = 4;

        template<int row, int col> static inline constexpr scalar_type A(const type& m) { return mat_traits<M>::template A<col,row>(m.matrix); }
    };

    template<detail::mat_type M>
    inline constexpr transposed_view<M> transposed( const M& matrix )
    {
        return {matrix};
    }

    template<detail::mat44_type M>
    struct read_orientation_view
    {
        const M& matrix;

        template<typename R>
        inline constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }
    };

    template<detail::mat44_type M44>
    struct orientation_view
    {
        M44& matrix;

        template<detail::read_mat33_type M33>
        inline constexpr orientation_view& operator=( const M33& matrix )
        {
            assign(*this, matrix);
            return *this;
        }

        template<typename R>
        inline constexpr operator R() const
        {
            R r;
            assign(r, *this);
            return r;
        }
    };

    template<detail::mat44_type M>
    struct mat_traits<orientation_view<M>>
    {
        using scalar_type = mat_traits<M>::scalar_type;
        using type = orientation_view<M>;
        static constexpr int n_dims = 3;
        
        template<int row, int col> static inline constexpr scalar_type A(const type& m) { return mat_traits<M>::template A<row,col>(m.matrix); }
        template<int row, int col> static inline constexpr scalar_type& A(type& m) { return mat_traits<M>::template A<row,col>(m.matrix); }
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
        using type = read_orientation_view<M>;
        static constexpr int n_dims = 3;
        
        template<int row, int col> static inline constexpr scalar_type A(const type& m) { return mat_traits<M>::template A<row,col>(m.matrix); }
    };

    template<detail::mat44_type M>
    inline constexpr read_orientation_view<M> orientation( const M& matrix )
    {
        return {matrix};
    }

    template<detail::mat44_type M>
    inline constexpr orientation_view<M> orientation( M& matrix )
    {
        return {matrix};
    }

    template<detail::read_mat44_type M>
    inline constexpr read_col_view<M, 3> position( const M& matrix )
    {
        return col<3>(matrix);
    }

    template<detail::mat44_type M>
    inline constexpr col_view<M, 3> position( M& matrix )
    {
        return col<3>(matrix);
    }
}