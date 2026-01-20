#include "sqg.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

using Catch::Matchers::WithinRel;

static constexpr double tol = 1.0e-8;

TEST_CASE("Coordinates", "[Coordinates][Math]")
{
    SECTION("NUE to NED Mat")
    {
        const sqg::mat33d rx = sqg::rotx_mat(std::numbers::pi / 2.0);
        const sqg::mat33d rx_ned = sqg::coordinates::NUEtoNED(rx);

        const sqg::vec3d rx_ned_x = sqg::col<0>(rx_ned);
        const sqg::vec3d rx_ned_y = sqg::col<1>(rx_ned);
        const sqg::vec3d rx_ned_z = sqg::col<2>(rx_ned);

        REQUIRE((( rx_ned_x.x == 1.0 ))); // pointing north
        REQUIRE(( rx_ned_y.z == 1.0 )); // pointing down
        REQUIRE(( rx_ned_z.y == -1.0 )); // pointing west

        const sqg::mat33d ry = sqg::roty_mat(std::numbers::pi / 2.0);
        const sqg::mat33d ry_ned = sqg::coordinates::NUEtoNED(ry);

        const sqg::vec3d ry_ned_x = sqg::col<0>(ry_ned);
        const sqg::vec3d ry_ned_y = sqg::col<1>(ry_ned);
        const sqg::vec3d ry_ned_z = sqg::col<2>(ry_ned);

        REQUIRE(( ry_ned_x.y == -1.0 )); // pointing west
        REQUIRE(( ry_ned_y.x == 1.0 )); // pointing north
        REQUIRE(( ry_ned_z.z == 1.0 )); // pointing down

        const sqg::mat33d rz = sqg::rotz_mat(std::numbers::pi / 2.0);
        const sqg::mat33d rz_ned = sqg::coordinates::NUEtoNED(rz);

        const sqg::vec3d rz_ned_x = sqg::col<0>(rz_ned);
        const sqg::vec3d rz_ned_y = sqg::col<1>(rz_ned);
        const sqg::vec3d rz_ned_z = sqg::col<2>(rz_ned);

        REQUIRE(( rz_ned_x.z == -1.0 )); // pointing up
        REQUIRE(( rz_ned_y.y ==  1.0 )); // pointing east
        REQUIRE(( rz_ned_z.x ==  1.0 )); // pointing north
    }

    SECTION("NUE to NWU Mat")
    {
        const sqg::mat33d rx = sqg::rotx_mat(std::numbers::pi / 2.0);
        const sqg::mat33d rx_nwu = sqg::coordinates::NUEtoNWU(rx);

        const sqg::vec3d rx_nwu_x = sqg::col<0>(rx_nwu);
        const sqg::vec3d rx_nwu_y = sqg::col<1>(rx_nwu);
        const sqg::vec3d rx_nwu_z = sqg::col<2>(rx_nwu);

        REQUIRE(( rx_nwu_x.x == 1.0 )); // pointing north
        REQUIRE(( rx_nwu_y.z == 1.0 )); // pointing up
        REQUIRE(( rx_nwu_z.y == -1.0 )); // pointing east

        const sqg::mat33d ry = sqg::roty_mat(std::numbers::pi / 2.0);
        const sqg::mat33d ry_nwu = sqg::coordinates::NUEtoNWU(ry);

        const sqg::vec3d ry_nwu_x = sqg::col<0>(ry_nwu);
        const sqg::vec3d ry_nwu_y = sqg::col<1>(ry_nwu);
        const sqg::vec3d ry_nwu_z = sqg::col<2>(ry_nwu);

        REQUIRE(( ry_nwu_x.y == 1.0 )); // pointing west
        REQUIRE(( ry_nwu_y.x == -1.0 )); // pointing south
        REQUIRE(( ry_nwu_z.z == 1.0 )); // pointing up

        const sqg::mat33d rz = sqg::rotz_mat(std::numbers::pi / 2.0);
        const sqg::mat33d rz_nwu = sqg::coordinates::NUEtoNWU(rz);

        const sqg::vec3d rz_nwu_x = sqg::col<0>(rz_nwu);
        const sqg::vec3d rz_nwu_y = sqg::col<1>(rz_nwu);
        const sqg::vec3d rz_nwu_z = sqg::col<2>(rz_nwu);

        REQUIRE(( rz_nwu_x.z == 1.0 )); // pointing up
        REQUIRE(( rz_nwu_y.y == 1.0 )); // pointing west
        REQUIRE(( rz_nwu_z.x == -1.0 )); // pointing south
    }

    SECTION("NUE to NED Quat")
    {
        const sqg::quatd rx = sqg::rotx_quat(std::numbers::pi / 2.0);
        const sqg::quatd rx_ned = sqg::coordinates::NUEtoNED(rx);

        const sqg::vec3d rx_ned_x = rx_ned * sqg::col<0>(sqg::identity_mat<double, 3>());
        const sqg::vec3d rx_ned_y = rx_ned * sqg::col<1>(sqg::identity_mat<double, 3>());
        const sqg::vec3d rx_ned_z = rx_ned * sqg::col<2>(sqg::identity_mat<double, 3>());

        REQUIRE_THAT( rx_ned_x.x, WithinRel(1.0 ,tol) ); // pointing north
        REQUIRE_THAT( rx_ned_y.z, WithinRel(1.0 ,tol) ); // pointing down
        REQUIRE_THAT( rx_ned_z.y, WithinRel(-1.0 ,tol) ); // pointing west

        const sqg::quatd ry = sqg::roty_quat(std::numbers::pi / 2.0);
        const sqg::quatd ry_ned = sqg::coordinates::NUEtoNED(ry);

        const sqg::vec3d ry_ned_x = ry_ned * sqg::col<0>(sqg::identity_mat<double, 3>());
        const sqg::vec3d ry_ned_y = ry_ned * sqg::col<1>(sqg::identity_mat<double, 3>());
        const sqg::vec3d ry_ned_z = ry_ned * sqg::col<2>(sqg::identity_mat<double, 3>());

        REQUIRE_THAT( ry_ned_x.y, WithinRel(-1.0 ,tol) ); // pointing west
        REQUIRE_THAT( ry_ned_y.x, WithinRel(1.0 ,tol) ); // pointing north
        REQUIRE_THAT( ry_ned_z.z, WithinRel(1.0 ,tol) ); // pointing down

        const sqg::quatd rz = sqg::rotz_quat(std::numbers::pi / 2.0);
        const sqg::quatd rz_ned = sqg::coordinates::NUEtoNED(rz);

        const sqg::vec3d rz_ned_x = rz_ned * sqg::col<0>(sqg::identity_mat<double, 3>());
        const sqg::vec3d rz_ned_y = rz_ned * sqg::col<1>(sqg::identity_mat<double, 3>());
        const sqg::vec3d rz_ned_z = rz_ned * sqg::col<2>(sqg::identity_mat<double, 3>());

        REQUIRE_THAT( rz_ned_x.z, WithinRel(-1.0 ,tol) ); // pointing up
        REQUIRE_THAT( rz_ned_y.y, WithinRel( 1.0 ,tol) ); // pointing east
        REQUIRE_THAT( rz_ned_z.x, WithinRel( 1.0 ,tol) ); // pointing north
    }

    SECTION("NUE to NWU Mat")
    {
        const sqg::quatd rx = sqg::rotx_quat(std::numbers::pi / 2.0);
        const sqg::quatd rx_nwu = sqg::coordinates::NUEtoNWU(rx);

        const sqg::vec3d rx_nwu_x = rx_nwu * sqg::col<0>(sqg::identity_mat<double, 3>());
        const sqg::vec3d rx_nwu_y = rx_nwu * sqg::col<1>(sqg::identity_mat<double, 3>());
        const sqg::vec3d rx_nwu_z = rx_nwu * sqg::col<2>(sqg::identity_mat<double, 3>());

        REQUIRE_THAT( rx_nwu_x.x, WithinRel(1.0 ,tol) ); // pointing north
        REQUIRE_THAT( rx_nwu_y.z, WithinRel(1.0 ,tol) ); // pointing up
        REQUIRE_THAT( rx_nwu_z.y, WithinRel(-1.0 ,tol) ); // pointing east

        const sqg::quatd ry = sqg::roty_quat(std::numbers::pi / 2.0);
        const sqg::quatd ry_nwu = sqg::coordinates::NUEtoNWU(ry);

        const sqg::vec3d ry_nwu_x = ry_nwu * sqg::col<0>(sqg::identity_mat<double, 3>());
        const sqg::vec3d ry_nwu_y = ry_nwu * sqg::col<1>(sqg::identity_mat<double, 3>());
        const sqg::vec3d ry_nwu_z = ry_nwu * sqg::col<2>(sqg::identity_mat<double, 3>());

        REQUIRE_THAT( ry_nwu_x.y, WithinRel(1.0 ,tol) ); // pointing west
        REQUIRE_THAT( ry_nwu_y.x, WithinRel(-1.0 ,tol) ); // pointing south
        REQUIRE_THAT( ry_nwu_z.z, WithinRel(1.0 ,tol) ); // pointing up

        const sqg::quatd rz = sqg::rotz_quat(std::numbers::pi / 2.0);
        const sqg::quatd rz_nwu = sqg::coordinates::NUEtoNWU(rz);

        const sqg::vec3d rz_nwu_x = rz_nwu * sqg::col<0>(sqg::identity_mat<double, 3>());
        const sqg::vec3d rz_nwu_y = rz_nwu * sqg::col<1>(sqg::identity_mat<double, 3>());
        const sqg::vec3d rz_nwu_z = rz_nwu * sqg::col<2>(sqg::identity_mat<double, 3>());

        REQUIRE_THAT( rz_nwu_x.z, WithinRel(1.0 ,tol) ); // pointing up
        REQUIRE_THAT( rz_nwu_y.y, WithinRel(1.0 ,tol) ); // pointing west
        REQUIRE_THAT( rz_nwu_z.x, WithinRel(-1.0 ,tol) ); // pointing south
    }

    SECTION("NWU to NED")
    {
        const sqg::vec3d north = { 1.0, 0.0, 0.0 };
        const sqg::vec3d west = { 0.0, 1.0, 0.0 };
        const sqg::vec3d up = { 0.0, 0.0, 1.0 };

        using value = sqg::vec_value<sqg::vec3d>;
        REQUIRE(( sqg::coordinates::NWUtoNED(north) == north ));
        REQUIRE(( (sqg::coordinates::NWUtoNED(west) == sqg::vec3d{ 0.0, -1.0, 0.0 } )));
        REQUIRE(( (sqg::coordinates::NWUtoNED(up) == sqg::vec3d{ 0.0, 0.0, -1.0 } )));
    }

    SECTION("NED to NWU")
    {
        const sqg::vec3d north = { 1.0, 0.0, 0.0 };
        const sqg::vec3d east = { 0.0, 1.0, 0.0 };
        const sqg::vec3d down = { 0.0, 0.0, 1.0 };

        REQUIRE(( sqg::coordinates::NWUtoNED(north) == north ));
        REQUIRE(( sqg::coordinates::NWUtoNED(east) == sqg::vec3d{ 0.0, -1.0, 0.0 } ));
        REQUIRE(( sqg::coordinates::NWUtoNED(down) == sqg::vec3d{ 0.0, 0.0, -1.0 } ));
    }
    
    
}