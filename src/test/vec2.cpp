#include <catch2/catch_test_macros.hpp>
#include <sqg_vec.h>

template<typename T>
struct Vector2
{
    T a[2] = { -1, -1 };
};

namespace sqg
{
    template<typename T>
    struct vec_traits<Vector2<T>>
    {
        using scalar_type = T;
        using type = Vector2<T>;
        using const_type = const Vector2<T>;
        static constexpr int n_dims = 2;
        static inline constexpr scalar_type X(const type& v) { return v.a[0]; }
        static inline constexpr scalar_type Y(const type& v) { return v.a[1]; }
        static inline constexpr scalar_type& X(type& v) { return v.a[0]; }
        static inline constexpr scalar_type& Y(type& v) { return v.a[1]; }
    };
}

TEST_CASE("vec2")
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
        Vector2<int> v = sqg::vec2<int>{ 1, 2 };
        REQUIRE( v.a[0] == 1 );
        REQUIRE( v.a[1] == 2 );
    }

    SECTION("set_zero")
    {
        Vector2<int> v;
        sqg::set_zero(v);
        REQUIRE( v.a[0] == 0 );
        REQUIRE( v.a[1] == 0 );
    }

    SECTION("cross")
    {
        sqg::vec2<int> v0 = { 1, 2 };
        sqg::vec2<int> v1 = { 3, 4 };
        REQUIRE( sqg::cross(v0, v1) == -2 );
    }

    SECTION("dot")
    {
        sqg::vec2<int> v0 = { 1, 2 };
        sqg::vec2<int> v1 = { 3, 4 };
        REQUIRE(sqg::dot(v0, v1) == 11);
    }

    SECTION("mag2")
    {
        sqg::vec2<int> v0 = { -5, 2 };
        REQUIRE(sqg::mag2(v0) == 25 + 4);
    }

    SECTION("mag")
    {
        sqg::vec2<float> v0 = { -5.0f, 2.0f };
        REQUIRE(sqg::mag(v0) == std::sqrt(25.0f + 4.0f));
    }

    SECTION("normalize")
    {
        sqg::vec2<float> v0 = { -5.0f, 2.0f };
        normalize(v0);
        REQUIRE( sqg::mag(v0) == 1.0f );
    }

    SECTION("normalized")
    {
        const sqg::vec2<float> v0 = { -5.0f, 2.0f };
        const sqg::vec2<float> v1 = normalized(v0);
        REQUIRE( sqg::mag(v0) != 1.0f );
        REQUIRE( sqg::mag(v1) == 1.0f );
    }

    SECTION("scalar_cast")
    {
        const sqg::vec2<double> v0 = { -4.0, 2.0 };
        const sqg::vec2<float> v1 = sqg::scalar_cast<float>(v0);
        REQUIRE( v1.x == -4.0f );
        REQUIRE( v1.y == 2.0 );
    }

    SECTION("operator- unary")
    {
        sqg::vec2<int> v0 = { 1, 2 };
        const auto v1 = -v0;
        REQUIRE( v1.x == -1 );
        REQUIRE( v1.y == -2 );
    }

    SECTION("operator+")
    {
        sqg::vec2<int> v0 = { 1, 2 };
        sqg::vec2<int> v1 = { 3, 4 };
        const auto v2 = v0 + v1;
        REQUIRE(v2.x == 4);
        REQUIRE(v2.y == 6);
    }

    SECTION("operator-")
    {
        sqg::vec2<int> v0 = { 1, 2 };
        sqg::vec2<int> v1 = { 3, 4 };
        const auto v2 = v0 - v1;
        REQUIRE(v2.x == -2);
        REQUIRE(v2.y == -2);
    }

    SECTION("operator* left")
    {
        sqg::vec2<int> v0 = { 1, 2 };

        const auto v2 = 10 * v0;
        REQUIRE(v2.x == 10);
        REQUIRE(v2.y == 20);
    }

    SECTION("operator* right")
    {
        sqg::vec2<int> v0 = { 1, 2 };

        const auto v2 = v0 * 10;
        REQUIRE(v2.x == 10);
        REQUIRE(v2.y == 20);
    }

    SECTION("operator*=")
    {
        sqg::vec2<int> v0 = { 1, 2 };
        sqg::vec2<int>& v1 = v0 *= 10;
        REQUIRE(v0.x == 10);
        REQUIRE(v0.y == 20);
        REQUIRE(&v1 == &v0);
    }

    SECTION("operator/")
    {
        sqg::vec2<int> v0 = { 10, 20 };

        const auto v2 = v0 / 10;
        REQUIRE(v2.x == 1);
        REQUIRE(v2.y == 2);
    }

    SECTION("operator/=")
    {
        sqg::vec2<int> v0 = { 10, 20 };
        sqg::vec2<int>& v1 = v0 /= 10;
        REQUIRE(v0.x == 1);
        REQUIRE(v0.y == 2);
        REQUIRE(&v1 == &v0);
    }

    SECTION("operator==")
    {
        sqg::vec2<int> v0 = { 1, 2 };
        sqg::vec2<int> v1 = { 1, 2 };
        sqg::vec2<int> v2 = { 3, 4 };

        const bool equal = v0 == v1;
        CAPTURE(equal,v0,v1);
        REQUIRE(equal);

        const bool not_equal = v0 == v2;
        CAPTURE(not_equal,v0,v2);
        REQUIRE(!not_equal);
    }

    SECTION("operator!=")
    {
        sqg::vec2<int> v0 = { 1, 2 };
        sqg::vec2<int> v1 = { 1, 2 };
        sqg::vec2<int> v2 = { 3, 4 };

        const bool not_equal = v0 != v1;
        CAPTURE(not_equal,v0,v1);
        REQUIRE(!not_equal);

        const bool equal = v0 != v2;
        CAPTURE(equal,v0,v2);
        REQUIRE(equal);
    }
}