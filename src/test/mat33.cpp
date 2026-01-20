#include <iostream>
#include <sqg.h>
#include "test.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_get_random_seed.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <numbers>

#include <sqg_mat.h>
#include <sqg_mat_view.h>
#include <sqg_mat_vec.h>

using Catch::Matchers::WithinRelMatcher;

template<typename T>
void valididate_rotation_matrix( const sqg::mat33<T>& matrix )
{
    constexpr T tolerance = T{1.0e-8};
    // Rotation matrices should have normalized cols and rows
    using scalar = sqg::mat_traits<sqg::mat33<T>>::scalar_type;
    REQUIRE_THAT( sqg::mag(sqg::col<0>(matrix)), WithinRelMatcher( scalar{1}, tolerance ) );
    REQUIRE_THAT( sqg::mag(sqg::col<1>(matrix)), WithinRelMatcher( scalar{1}, tolerance ) );
    REQUIRE_THAT( sqg::mag(sqg::col<2>(matrix)), WithinRelMatcher( scalar{1}, tolerance ) );

    REQUIRE_THAT( sqg::mag(sqg::row<0>(matrix)), WithinRelMatcher( scalar{1}, tolerance ) );
    REQUIRE_THAT( sqg::mag(sqg::row<1>(matrix)), WithinRelMatcher( scalar{1}, tolerance ) );
    REQUIRE_THAT( sqg::mag(sqg::row<2>(matrix)), WithinRelMatcher( scalar{1}, tolerance ) );

    //sqg::transposed(matrix)
    // sqg::mat33<T> I = sqg::transposed(matrix) * matrix;
    // const bool equal = I == sqg::identity_mat<T, 3>();
    // REQUIRE(equal);
}

template<int n, typename M>
void validate_basis_vector_angle( const M& matrix, sqg::mat_scalar<M> angle )
{
    const auto cosa = std::cos(angle);
    const sqg::mat_value<M> identity = sqg::identity_mat<sqg::mat_scalar<M>, sqg::mat_traits<M>::n_dims>();
    const auto cos_actual = sqg::dot( sqg::col<n>(matrix), sqg::col<n>(identity) );
    REQUIRE(cosa == cos_actual);
}

template<typename T>
void test_rotx(std::mt19937& generator )
{
    SECTION("Randomised Test")
    {
        std::uniform_real_distribution<T> distribution{T{-2.0 * std::numbers::pi},T{2.0 * std::numbers::pi}};

        for ( int i = 0; i < 100; i++ )
        {
            const T angle = distribution(generator);
            const sqg::mat33<T> smatrix = sqg::rotx_mat(angle);
            CAPTURE(angle);
            valididate_rotation_matrix(smatrix);
            CAPTURE(angle);
            validate_basis_vector_angle<0>(smatrix, T{0});
            validate_basis_vector_angle<1>(smatrix, angle);
            validate_basis_vector_angle<2>(smatrix, angle);
        }
    }
}

template<typename T>
void test_roty(std::mt19937& generator )
{
    SECTION("Randomised Test")
    {
        std::uniform_real_distribution<T> distribution{T{-2.0 * std::numbers::pi},T{2.0 * std::numbers::pi}};

        for ( int i = 0; i < 100; i++ )
        {
            const T angle = distribution(generator);
            const sqg::mat33<T> smatrix = sqg::roty_mat(angle);
            CAPTURE(angle);
            valididate_rotation_matrix(smatrix);
            CAPTURE(angle);
            validate_basis_vector_angle<0>(smatrix, angle);
            validate_basis_vector_angle<1>(smatrix, T{0});
            validate_basis_vector_angle<2>(smatrix, angle);
        }
    }
}

template<typename T>
void test_rotz(std::mt19937& generator )
{
    SECTION("Randomised Test")
    {
        std::uniform_real_distribution<T> distribution{T{-2.0 * std::numbers::pi},T{2.0 * std::numbers::pi}};

        for ( int i = 0; i < 100; i++ )
        {
            const T angle = distribution(generator);
            const sqg::mat33<T> smatrix = sqg::rotz_mat(angle);
            CAPTURE(angle);
            valididate_rotation_matrix(smatrix);
            CAPTURE(angle);
            validate_basis_vector_angle<0>(smatrix, angle);
            validate_basis_vector_angle<1>(smatrix, angle);
            validate_basis_vector_angle<2>(smatrix, T{0});
        }
    }
}

template<typename T>
void test_rot(std::mt19937& generator )
{
    SECTION("Randomised Test")
    {
        std::uniform_real_distribution<T> distribution_angle{T{-2.0 * std::numbers::pi},T{2.0 * std::numbers::pi}};
        std::uniform_real_distribution<T> distribution_axis{T{-1},T{1}};

        

        for ( int i = 0; i < 100; i++ )
        {
            sqg_test::vector<T, 3> v;
            sqg_test::set_random_vector<decltype(distribution_axis), T,3>(distribution_axis, generator, v);
            const auto axis = sqg::convert_to<sqg::vec3<T>>(v);
            const T angle = distribution_angle(generator);

            const sqg::mat33<T> smatrix = sqg::rot_mat(sqg::normalized(axis), angle);
            CAPTURE(angle);
            valididate_rotation_matrix(smatrix);
        }
    }
}

TEST_CASE("Rotation")
{
    std::mt19937 generator(Catch::getSeed());
    test_rotx<double>(generator);
    test_rotx<float>(generator);

    test_roty<double>(generator);
    test_roty<float>(generator);

    test_rotz<double>(generator);
    test_rotz<float>(generator);

    test_rot<double>(generator);
    test_rot<float>(generator);
}