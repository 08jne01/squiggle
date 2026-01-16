#include "test.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_get_random_seed.hpp>



template<typename T, int rows, int cols>
void test_assign(std::mt19937& generator )
{
    using test_matrix = sqg_test::matrix<T,rows,cols>;
    using sqg_matrix = typename sqg::mat_traits<test_matrix>::sqg_matrix;

    SECTION("Basic Test")
    {
        sqg_test::matrix<T,rows,cols> matrix;
        sqg_test::set_basic_matrix<T,rows,cols>(matrix);
        
        sqg_matrix smatrix;
        assign(smatrix, matrix);

        CAPTURE(rows, cols);
        REQUIRE(sqg_test::mat_equal(smatrix, matrix));
    }

    SECTION("Randomised Test")
    {
        for ( int i = 0; i < 100; i++ )
        {
            sqg_test::matrix<T,rows,cols> matrix;
            T min{-10};
            T max{10};
            sqg_test::set_random_matrix<T,rows,cols>(generator, matrix, min, max);
            
            sqg_matrix smatrix;
            assign(smatrix, matrix);
            CAPTURE(rows, cols);
            REQUIRE(sqg_test::mat_equal(smatrix, matrix));
        }
    }
}

TEST_CASE("Assign")
{
    std::mt19937 generator(Catch::getSeed());

    test_assign<double, 2,2>(generator);
    test_assign<int,    2,2>(generator);
    test_assign<float,  2,2>(generator);
    test_assign<short,  2,2>(generator);

    test_assign<double, 3,3>(generator);
    test_assign<int,    3,3>(generator);
    test_assign<float,  3,3>(generator);
    test_assign<short,  3,3>(generator);

    test_assign<double, 4,4>(generator);
    test_assign<int,    4,4>(generator);
    test_assign<float,  4,4>(generator);
    test_assign<short,  4,4>(generator);
}

template<typename T, int rows, int cols>
void test_identity(std::mt19937& generator )
{
    using test_matrix = sqg_test::matrix<T,rows,cols>;
    using sqg_matrix = typename sqg::mat_traits<test_matrix>::sqg_matrix;

    sqg_test::matrix<T,rows,cols> matrix;
    sqg_test::set_identity_matrix<T,rows,cols>(matrix);
    
    const sqg_matrix smatrix = sqg::identity_mat<T, rows>(); 
    CAPTURE(rows, cols);
    REQUIRE(sqg_test::mat_equal(smatrix, matrix));
}

TEST_CASE("Identity")
{
    std::mt19937 generator(Catch::getSeed());

    test_identity<double, 2,2>(generator);
    test_identity<int,    2,2>(generator);
    test_identity<float,  2,2>(generator);
    test_identity<short,  2,2>(generator);

    test_identity<double, 3,3>(generator);
    test_identity<int,    3,3>(generator);
    test_identity<float,  3,3>(generator);
    test_identity<short,  3,3>(generator);

    test_identity<double, 4,4>(generator);
    test_identity<int,    4,4>(generator);
    test_identity<float,  4,4>(generator);
    test_identity<short,  4,4>(generator);
}

template<typename T, int rows, int cols>
void test_transpose(std::mt19937& generator )
{
    using test_matrix = sqg_test::matrix<T,rows,cols>;
    using sqg_matrix = typename sqg::mat_traits<test_matrix>::sqg_matrix;

    SECTION("Basic Test")
    {
        sqg_test::matrix<T,rows,cols> matrix;
        sqg_test::set_basic_matrix<T,rows,cols>(matrix);
        
        sqg_matrix smatrix;
        assign(smatrix, matrix);

        sqg_test::transpose<T,rows,cols>(matrix);
        sqg::transpose(smatrix);

        CAPTURE(rows, cols);
        REQUIRE(sqg_test::mat_equal(smatrix, matrix));
    }

    SECTION("Randomised Test")
    {
        for ( int i = 0; i < 100; i++ )
        {
            sqg_test::matrix<T,rows,cols> matrix;
            T min{-10};
            T max{10};
            sqg_test::set_random_matrix<T,rows,cols>(generator, matrix, min, max);
            
            sqg_matrix smatrix;
            assign(smatrix, matrix);

            sqg_test::transpose<T,rows,cols>(matrix);
            sqg::transpose(smatrix);

            CAPTURE(rows, cols);
            REQUIRE(sqg_test::mat_equal(smatrix, matrix));
        }
    }
}

TEST_CASE("Transpose")
{
    std::mt19937 generator(Catch::getSeed());

    test_transpose<double, 2,2>(generator);
    test_transpose<int,    2,2>(generator);
    test_transpose<float,  2,2>(generator);
    test_transpose<short,  2,2>(generator);

    test_transpose<double, 3,3>(generator);
    test_transpose<int,    3,3>(generator);
    test_transpose<float,  3,3>(generator);
    test_transpose<short,  3,3>(generator);

    test_transpose<double, 4,4>(generator);
    test_transpose<int,    4,4>(generator);
    test_transpose<float,  4,4>(generator);
    test_transpose<short,  4,4>(generator);
}

template<typename T, int rows, int cols>
void test_transposed(std::mt19937& generator )
{
    using test_matrix = sqg_test::matrix<T,rows,cols>;
    using sqg_matrix = typename sqg::mat_traits<test_matrix>::sqg_matrix;

    SECTION("Basic Test")
    {
        sqg_test::matrix<T,rows,cols> matrix;
        sqg_test::set_basic_matrix<T,rows,cols>(matrix);
        
        sqg_matrix smatrix;
        assign(smatrix, matrix);

        sqg_test::transpose<T,rows,cols>(matrix);

        sqg_matrix copy_smatrix = sqg::transposed(smatrix);

        CAPTURE(rows, cols);
        REQUIRE(sqg_test::mat_equal(copy_smatrix, matrix));
    }

    SECTION("Randomised Test")
    {
        for ( int i = 0; i < 100; i++ )
        {
            sqg_test::matrix<T,rows,cols> matrix;
            T min{-10};
            T max{10};
            sqg_test::set_random_matrix<T,rows,cols>(generator, matrix, min, max);
            
            sqg_matrix smatrix;
            assign(smatrix, matrix);

            sqg_test::transpose<T,rows,cols>(matrix);
            sqg_matrix copy_smatrix = sqg::transposed(smatrix);

            CAPTURE(rows, cols);
            REQUIRE(sqg_test::mat_equal(copy_smatrix, matrix));
        }
    }
}

TEST_CASE("Transposed View")
{
    std::mt19937 generator(Catch::getSeed());

    test_transposed<double, 2,2>(generator);
    test_transposed<int,    2,2>(generator);
    test_transposed<float,  2,2>(generator);
    test_transposed<short,  2,2>(generator);

    test_transposed<double, 3,3>(generator);
    test_transposed<int,    3,3>(generator);
    test_transposed<float,  3,3>(generator);
    test_transposed<short,  3,3>(generator);

    test_transposed<double, 4,4>(generator);
    test_transposed<int,    4,4>(generator);
    test_transposed<float,  4,4>(generator);
    test_transposed<short,  4,4>(generator);
}

TEST_CASE("Orientation View")
{
    using view = sqg::row_view<sqg::mat33<double>, 0>;
    using type = sqg::orientation_view<sqg::mat44<double>>;
    //static_assert(sqg::detail::mat33_type<type>, "something");

    std::mt19937 generator(Catch::getSeed());

    sqg_test::matrix<double, 4,4> M1;
    sqg::mat44<double> M2;

    sqg::mat_value2<decltype(M2), decltype(M1)>;

    auto M3 = M2 * M1;


    //sqg::mat44<double> T = sqg::identity_mat<double, 4>();
    //sqg::orientation(T) = sqg::rotx_mat(1.0);
}