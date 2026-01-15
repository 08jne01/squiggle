#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "sqg.h"


TEST_CASE("vec3")
{

}

TEST_CASE("vec4")
{

}

TEST_CASE("mat22")
{

}

TEST_CASE("mat33")
{

}

TEST_CASE("mat44")
{

}

TEST_CASE("vec2")
{
    sqg::vec3<int> v0 = { 1, 0, 0 };
    sqg::vec3<int> v1 = { 0, 1, 0 };

    using f = sqg::vec_traits<decltype(v0)>::type;

    sqg::mat33<int> m = sqg::identity_mat<int,3>();

    const int x = A<0,1>(m);

    //sqg::col<0>(m);

    auto z = m * v0;

    static_assert( sqg::detail::vec3_type<f>, "Hello" );

    auto v = sqg::cross(v0, v1);
    auto s = sqg::dot(v0, v1);

    v0 + v1;


    std::format("test {}", 1);
    std::println(std::cout, "Hello");
}