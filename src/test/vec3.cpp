#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <random>
#include <sqg_vec.h>
#include <catch2/catch_get_random_seed.hpp>
#include <sqg_quat.h>
#include <sqg_quat_vec3.h>

template<typename T>
struct Vector3
{
    T a[3] = { -1, -1, -1 };
};

namespace sqg
{
    template<typename T>
    struct vec_traits<Vector3<T>>
    {
        using scalar_type = T;
        using type = Vector3<T>;
        static constexpr int n_dims = 3;
        static inline constexpr scalar_type X(const type& v) { return v.a[0]; }
        static inline constexpr scalar_type Y(const type& v) { return v.a[1]; }
        static inline constexpr scalar_type Z(const type& v) { return v.a[2]; }
        static inline constexpr scalar_type& X(type& v) { return v.a[0]; }
        static inline constexpr scalar_type& Y(type& v) { return v.a[1]; }
        static inline constexpr scalar_type& Z(type& v) { return v.a[2]; }
    };
}

TEST_CASE("vec3")
{

    static_assert( sqg::concepts::vec2_type<sqg::vec2<int>>, "Should be vec2" );
    static_assert( ! sqg::concepts::vec3_type<sqg::vec2<int>>, "Shouldn't be vec3" );
    static_assert( ! sqg::concepts::vec4_type<sqg::vec2<int>>, "Shouldn't be vec4" );
    static_assert( ! sqg::concepts::mat22_type<sqg::vec2<int>>, "Shouldn't be mat22" );
    static_assert( ! sqg::concepts::mat33_type<sqg::vec2<int>>, "Shouldn't be mat33" );
    static_assert( ! sqg::concepts::mat44_type<sqg::vec2<int>>, "Shouldn't be mat44" );
    static_assert( ! sqg::concepts::quat_type<sqg::vec2<int>>, "Shouldn't be quat" );

    SECTION("assign")
    {
        Vector3<int> v = sqg::vec3<int>{ 1, 2, 3 };
        REQUIRE( v.a[0] == 1 );
        REQUIRE( v.a[1] == 2 );
        REQUIRE( v.a[2] == 3 );
    }

    SECTION("set_zero")
    {
        Vector3<int> v;
        sqg::set_zero(v);
        REQUIRE( v.a[0] == 0 );
        REQUIRE( v.a[1] == 0 );
        REQUIRE( v.a[2] == 0 );
    }

    SECTION("cross")
    {
        SECTION("1")
        {
            sqg::vec3<int> v001 = { 0, 0, 1 };
            sqg::vec3<int> v010 = { 0, 1, 0 };
            sqg::vec3<int> v100 = { 1, 0, 0 };

            auto test = [](auto v1, auto v2, int x, int y, int z) {
                auto v3 = sqg::cross(v1, v2);
                REQUIRE(v3.x == x);
                REQUIRE(v3.y == y);
                REQUIRE(v3.z == z);
            };


            // 001 001
            // 001 010
            // 001 100

            // 010 001
            // 010 010
            // 010 100
            
            // 100 001
            // 100 010
            // 100 100

            test( v001, v001, 0, 0, 0 );
            test( v001, v010,-1, 0, 0 );
            test( v001, v100, 0, 1, 0 );

            test( v010, v001, 1, 0, 0 );
            test( v010, v010, 0, 0, 0 );
            test( v010, v100, 0, 0,-1 );

            test( v100, v001, 0,-1, 0 );
            test( v100, v010, 0, 0, 1 );
            test( v100, v100, 0, 0, 0 );

            std::mt19937 generator(Catch::getSeed());
            std::uniform_int_distribution<> distribution{-100, 100};

            for ( size_t i = 0; i < 1000; i++ )
            {
                const sqg::vec3<int> v0 = { distribution(generator), distribution(generator), distribution(generator) };
                const sqg::vec3<int> v1 = { distribution(generator), distribution(generator), distribution(generator) };

                const sqg::vec3<int> v2 = sqg::cross(v0,v1);
                
                REQUIRE( sqg::dot( v0, v2 ) == 0);
            }
        }
        
    }

    SECTION("dot")
    {
        sqg::vec3<int> v0 = { 1, 2, 3 };
        sqg::vec3<int> v1 = { 4, 5, 6 };
        REQUIRE(sqg::dot(v0, v1) == 32);
    }

    SECTION("mag2")
    {
        sqg::vec3<int> v0 = { -5, 2, 7 };
        REQUIRE(sqg::mag2(v0) == 25 + 4 + 49);
    }

    SECTION("mag")
    {
        sqg::vec3<float> v0 = { -5.0f, 2.0f, 7.0f };
        REQUIRE(sqg::mag(v0) == std::sqrt(25.0f + 4.0f + 49.0f));
    }

    SECTION("normalize")
    {
        sqg::vec3<float> v0 = { -5.0f, 2.0f, 7.0f };
        normalize(v0);
        REQUIRE( sqg::mag(v0) == 1.0f );
    }

    SECTION("normalized")
    {
        const sqg::vec3<float> v0 = { -5.0f, 2.0f, 7.0f };
        const sqg::vec3<float> v1 = normalized(v0);
        REQUIRE( sqg::mag(v0) != 1.0f );
        REQUIRE( sqg::mag(v1) == 1.0f );
    }

    SECTION("scalar_cast")
    {
        const sqg::vec3<double> v0 = { -4.0, 2.0, 7.0 };
        const sqg::vec3<float> v1 = sqg::scalar_cast<float>(v0);
        REQUIRE( v1.x == -4.0f );
        REQUIRE( v1.y == 2.0f );
        REQUIRE( v1.z == 7.0f );
    }

    SECTION("operator- unary")
    {
        sqg::vec3<int> v0 = { 1, 2, 3 };
        const auto v1 = -v0;
        REQUIRE( v1.x == -1 );
        REQUIRE( v1.y == -2 );
        REQUIRE( v1.z == -3 );
    }

    SECTION("operator+")
    {
        sqg::vec3<int> v0 = { 1, 2, 3 };
        sqg::vec3<int> v1 = { 4, 5, 6 };
        const auto v2 = v0 + v1;
        REQUIRE(v2.x == 5);
        REQUIRE(v2.y == 7);
        REQUIRE(v2.z == 9);
    }

    SECTION("operator-")
    {
        sqg::vec3<int> v0 = { 1, 2, 3 };
        sqg::vec3<int> v1 = { 4, 5, 6 };
        const auto v2 = v0 - v1;
        REQUIRE(v2.x == -3);
        REQUIRE(v2.y == -3);
        REQUIRE(v2.z == -3);
    }

    SECTION("operator* left")
    {
        sqg::vec3<int> v0 = { 1, 2, 3 };

        const auto v2 = 10 * v0;
        REQUIRE(v2.x == 10);
        REQUIRE(v2.y == 20);
        REQUIRE(v2.z == 30);
    }

    SECTION("operator* right")
    {
        sqg::vec3<int> v0 = { 1, 2, 3 };

        const auto v2 = v0 * 10;
        REQUIRE(v2.x == 10);
        REQUIRE(v2.y == 20);
        REQUIRE(v2.z == 30);
    }

    SECTION("operator*=")
    {
        sqg::vec3<int> v0 = { 1, 2, 3 };
        sqg::vec3<int>& v1 = v0 *= 10;
        REQUIRE(v0.x == 10);
        REQUIRE(v0.y == 20);
        REQUIRE(v0.z == 30);
        REQUIRE(&v1 == &v0);
    }

    SECTION("operator/")
    {
        sqg::vec3<int> v0 = { 10, 20, 30 };

        const auto v2 = v0 / 10;
        REQUIRE(v2.x == 1);
        REQUIRE(v2.y == 2);
        REQUIRE(v2.z == 3);
    }

    SECTION("operator/=")
    {
        sqg::vec3<int> v0 = { 10, 20, 30 };
        sqg::vec3<int>& v1 = v0 /= 10;
        REQUIRE(v0.x == 1);
        REQUIRE(v0.y == 2);
        REQUIRE(v0.z == 3);
        REQUIRE(&v1 == &v0);
    }

    SECTION("operator==")
    {
        sqg::vec3<int> v0 = { 1, 2, 3 };
        sqg::vec3<int> v1 = { 1, 2, 3 };
        sqg::vec3<int> v2 = { 2, 2, 3 };
        sqg::vec3<int> v3 = { 1, 3, 3 };
        sqg::vec3<int> v4 = { 1, 2, 2 };

        const bool equal = v0 == v1;
        CAPTURE(equal,v0,v1);
        REQUIRE(equal);

        auto not_equal = [](auto v0, auto v1){
            const bool not_equal = v0 == v1;
            REQUIRE(!not_equal);
        };

        not_equal( v0, v2 );
        not_equal( v0, v3 );
        not_equal( v0, v4 );
    }

    SECTION("operator!=")
    {
        sqg::vec3<int> v0 = { 1, 2, 3 };
        sqg::vec3<int> v1 = { 1, 2, 3 };
        sqg::vec3<int> v2 = { 2, 2, 3 };
        sqg::vec3<int> v3 = { 1, 3, 3 };
        sqg::vec3<int> v4 = { 1, 2, 2 };

        const bool equal = v0 != v1;
        CAPTURE(equal,v0,v1);
        REQUIRE(!equal);

        auto not_equal = [](auto v0, auto v1){
            const bool not_equal = v0 != v1;
            REQUIRE(not_equal);
        };

        not_equal( v0, v2 );
        not_equal( v0, v3 );
        not_equal( v0, v4 );
    }
}

TEST_CASE("Testing")
{
    // sqg::quat<float> q = sqg::rotx_quat(4.0f);

    // sqg::mat22<double> M = {
    //     {{1.0, 2.0},{3.0, 4.0}},
    // };

    // sqg::mat44<double> M_T;
    // const sqg::mat22<double> d;

    // static_assert( sqg::detail::mat33_read<sqg::mat33<double>> );
    // static_assert( sqg::detail::mat33_write<sqg::mat33<double>> );

    // using view = sqg::transposed_view<sqg::mat22<double>>;

    // sqg::mat_traits<sqg::mat22<double>>::A<0,0>(d);

    // auto v = view{d};

    // sqg::mat_traits<view>::A<0, 0>( v );

    //sqg::assign( row<0>(d), sqg::vec3<double>{} );

    //orientation(M_T) = d;
    //position(M_T) = sqg::vec3<double>{};

    //assign(orientation(M_T), d);


    //const auto y = sqg::transposed(sqg::mat22<double>{});
    //static_assert( sqg::concepts::mat_type<decltype(y)> );
    //const double z = sqg::A<0,0>( y );

}