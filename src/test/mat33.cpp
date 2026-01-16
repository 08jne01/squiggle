#include <sqg.h>
#include "test.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_get_random_seed.hpp>

#include <sqg_mat.h>
#include <sqg_mat_view.h>

template<typename T>
void valididate_rotation_matrix( const sqg::mat33<T>& matrix )
{
    // Rotation matrices should have normalized cols and rows
    using scalar = sqg::mat_traits<sqg::mat33<T>>::scalar_type;
    REQUIRE( sqg::mag(sqg::col<0>(matrix)) == scalar{1} );
    REQUIRE( sqg::mag(sqg::col<1>(matrix)) == scalar{1} );
    REQUIRE( sqg::mag(sqg::col<2>(matrix)) == scalar{1} );

    REQUIRE( sqg::mag(sqg::row<0>(matrix)) == scalar{1} );
    REQUIRE( sqg::mag(sqg::row<1>(matrix)) == scalar{1} );
    REQUIRE( sqg::mag(sqg::row<2>(matrix)) == scalar{1} );
}

template<int n, typename M>
void validate_basis_vector_angle( const M& matrix, sqg::mat_scalar<M> angle )
{
    const auto cosa = std::cos(angle);
    const sqg::mat_value<M> identity = sqg::identity_mat<sqg::mat_scalar<M>, sqg::mat_traits<M>::n_dims>();
    const auto cos_actual = sqg::dot( sqg::col<n>(matrix), sqg::col<n>(identity) );
    REQUIRE(cosa == cos_actual);
}

TEST_CASE("Rotation")
{
    sqg::mat33<double> matrix = sqg::rotx_mat(0.0);
    valididate_rotation_matrix(matrix);
    validate_basis_vector_angle<0>(matrix, 0.0);
    validate_basis_vector_angle<1>(matrix, 0.0);
    validate_basis_vector_angle<2>(matrix, 0.0);

    sqg::set_rotx(matrix, 1.0);
    valididate_rotation_matrix(matrix);
    validate_basis_vector_angle<0>(matrix, 0.0);
    validate_basis_vector_angle<1>(matrix, 1.0);
    validate_basis_vector_angle<2>(matrix, 1.0);
}