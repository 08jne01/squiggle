#include <boost/qvm.hpp>
#include <sqg.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_get_random_seed.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../test.h"
#include <concepts>
#include <iostream>

template<typename T, int n>
struct vec_type;

template<typename T>
struct vec_type<T,2>
{
    using type = sqg::vec2<T>;
};

template<typename T>
struct vec_type<T,3>
{
    using type = sqg::vec3<T>;
};

template<typename T>
struct vec_type<T,4>
{
    using type = sqg::vec4<T>;
};

static constexpr int ulp = 100000000;

template<typename T>
struct tol;

template<> struct tol<double> { 
    static constexpr double abs = 1.0e-30; 
    static constexpr double rel = 1.0e-15; 
};
template<> struct tol<float> { 
    static constexpr float abs = 1.0e-6f; 
    static constexpr float rel = 1.0e-6f; 
};

template<typename T>
void random_vec_real( std::mt19937& generator, sqg::vec2<T>& vec, boost::qvm::vec<T,2>& qvm_vec )
{
    std::uniform_real_distribution<T> distribution{ T{-100}, T{100} };
    vec.x = distribution(generator);
    vec.y = distribution(generator);

    X(qvm_vec) = vec.x;
    Y(qvm_vec) = vec.y;
}

template<typename T>
void random_vec_int( std::mt19937& generator, sqg::vec2<T>& vec, boost::qvm::vec<T,2>& qvm_vec )
{
    std::uniform_int_distribution<T> distribution{ T{-100}, T{100} };
    vec.x = distribution(generator);
    vec.y = distribution(generator);

    X(qvm_vec) = vec.x;
    Y(qvm_vec) = vec.y;
}

template<typename T>
void random_vec_real( std::mt19937& generator, sqg::vec3<T>& vec, boost::qvm::vec<T,3>& qvm_vec )
{
    std::uniform_real_distribution<T> distribution{ T{-100}, T{100} };
    vec.x = distribution(generator);
    vec.y = distribution(generator);
    vec.z = distribution(generator);

    X(qvm_vec) = vec.x;
    Y(qvm_vec) = vec.y;
    Z(qvm_vec) = vec.z;
}

template<typename T>
void random_vec_int( std::mt19937& generator, sqg::vec3<T>& vec, boost::qvm::vec<T,3>& qvm_vec )
{
    std::uniform_int_distribution<T> distribution{ T{-100}, T{100} };
    vec.x = distribution(generator);
    vec.y = distribution(generator);
    vec.z = distribution(generator);

    X(qvm_vec) = vec.x;
    Y(qvm_vec) = vec.y;
    Z(qvm_vec) = vec.z;
}

template<typename T>
void random_vec_real( std::mt19937& generator, sqg::vec4<T>& vec, boost::qvm::vec<T,4>& qvm_vec )
{
    std::uniform_real_distribution<T> distribution{ T{-100}, T{100} };
    vec.x = distribution(generator);
    vec.y = distribution(generator);
    vec.z = distribution(generator);
    vec.w = distribution(generator);

    X(qvm_vec) = vec.x;
    Y(qvm_vec) = vec.y;
    Z(qvm_vec) = vec.z;
    W(qvm_vec) = vec.w;
}

template<typename T>
void random_vec_int( std::mt19937& generator, sqg::vec4<T>& vec, boost::qvm::vec<T,4>& qvm_vec )
{
    std::uniform_int_distribution<T> distribution{ T{-100}, T{100} };
    vec.x = distribution(generator);
    vec.y = distribution(generator);
    vec.z = distribution(generator);
    vec.w = distribution(generator);

    X(qvm_vec) = vec.x;
    Y(qvm_vec) = vec.y;
    Z(qvm_vec) = vec.z;
    W(qvm_vec) = vec.w;
}

template<typename T>
boost::qvm::vec<T,2> error( const sqg::vec2<T>& vec, const boost::qvm::vec<T,2>& qvm_vec )
{
    boost::qvm::vec<T,2> difference;
    X(difference) = X(qvm_vec) - vec.x;
    Y(difference) = Y(qvm_vec) - vec.y;
    return difference;
}

template<typename T>
boost::qvm::vec<T,3> error( const sqg::vec3<T>& vec, const boost::qvm::vec<T,3>& qvm_vec )
{
    boost::qvm::vec<T,3> difference;
    X(difference) = X(qvm_vec) - vec.x;
    Y(difference) = Y(qvm_vec) - vec.y;
    Z(difference) = Z(qvm_vec) - vec.z;
    return difference;
}

template<typename T>
boost::qvm::vec<T,4> error( const sqg::vec4<T>& vec, const boost::qvm::vec<T,4>& qvm_vec )
{
    boost::qvm::vec<T,4> difference;
    X(difference) = X(qvm_vec) - vec.x;
    Y(difference) = Y(qvm_vec) - vec.y;
    Z(difference) = Z(qvm_vec) - vec.z;
    W(difference) = W(qvm_vec) - vec.w;
    return difference;
}

template<typename T>
boost::qvm::vec<T,4> error( const sqg::vec4<T>& vec, const boost::qvm::quat<T>& qvm_vec )
{
    boost::qvm::vec<T,4> difference;
    X(difference) = X(qvm_vec) - vec.x;
    Y(difference) = Y(qvm_vec) - vec.y;
    Z(difference) = Z(qvm_vec) - vec.z;
    W(difference) = S(qvm_vec) - vec.w;
    return difference;
}

template<typename T, int n, typename operation>
void test_vec_operation( std::mt19937& generator, operation op )
{
    using sqg_vec = sqg::vec_traits<sqg_test::vector<T, n>>::sqg_vector;
    using qvm_vec = boost::qvm::vec<T,n>;

    sqg_vec vec;
    qvm_vec qvec;
    
    for ( int i = 0; i < 100; i++ )
    {
        if constexpr ( std::integral<T> )
        {
            random_vec_int(generator, vec, qvec);
        }
        else
        {
            random_vec_real(generator, vec, qvec);
        }
        
        REQUIRE(boost::qvm::mag_sqr(error(vec, qvec)) == T{0});
        CAPTURE(n, i);
        op(vec,qvec);
    }
}

template<typename T, int n, typename operation>
void test_vec_operation2( std::mt19937& generator, operation op )
{
    using sqg_vec = sqg::vec_traits<sqg_test::vector<T, n>>::sqg_vector;
    using qvm_vec = boost::qvm::vec<T,n>;

    qvm_vec qvec0;
    qvm_vec qvec1;
    
    sqg_vec vec0;
    sqg_vec vec1;

    for ( int i = 0; i < 100; i++ )
    {
        if constexpr ( std::integral<T> )
        {
            random_vec_int(generator, vec0, qvec0);
            random_vec_int(generator, vec1, qvec1);
        }
        else
        {
            random_vec_real(generator, vec0, qvec0);
            random_vec_real(generator, vec1, qvec1);
        }
        
        REQUIRE(boost::qvm::mag_sqr(error(vec0, qvec0)) == T{0});
        REQUIRE(boost::qvm::mag_sqr(error(vec1, qvec1)) == T{0});
        CAPTURE(n,i);
        op(vec0,vec1,qvec0,qvec1);
    }
}

template<typename T, int n>
using qvec = boost::qvm::vec<T,n>;

template<typename T, int n>
using vec = vec_type<T, n>::type;

template<typename T, int n>
void test_vec(std::mt19937& generator)
{
    SECTION("assign")
    {
        test_vec_operation<T,n>(generator, [](const vec<T,n>& v, const qvec<T,n>& qv) {
            qvec<T,n> qr;
            assign(qr, qv);
            vec<T,n> r;
            assign(r, v);
            REQUIRE(boost::qvm::mag_sqr(error(r, qr)) == T{0});
        });
    }

    SECTION("set_zero")
    {
        test_vec_operation<T,n>(generator, [](vec<T,n>& v, qvec<T,n>& qv) {
            sqg::set_zero(v);
            boost::qvm::set_zero(qv);
            REQUIRE(boost::qvm::mag_sqr(error(v, qv)) == T{0});
        });
    }

    SECTION("set_zero")
    {
        test_vec_operation<T,n>(generator, [](vec<T,n>& v, qvec<T,n>& qv) {
            qv = boost::qvm::zero_vec<T,n>();
            v = sqg::zero_vec<T,n>();
            REQUIRE(boost::qvm::mag_sqr(error(v, qv)) == T{0});
        });
    }

    SECTION("cross")
    {
        if constexpr ( n == 2 )
        {
            test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
                T qr = boost::qvm::cross(qv0,qv1);
                T r = sqg::cross(v0,v1);
                REQUIRE(qr == r);
            });
        }
        else if constexpr ( n == 3 )
        {
            test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
                qvec<T,n> qr = boost::qvm::cross(qv0,qv1);
                vec<T,n> r = sqg::cross(v0,v1);
                REQUIRE(boost::qvm::mag_sqr(error(r, qr)) == T{0});
            });
        }
    }

    SECTION("dot")
    {
        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
            
            if constexpr ( n == 4 )
            {
                boost::qvm::quat<T> q0;
                boost::qvm::quat<T> q1;

                boost::qvm::S(q0) = boost::qvm::W(qv0);
                boost::qvm::X(q0) = boost::qvm::X(qv0);
                boost::qvm::Y(q0) = boost::qvm::Y(qv0);
                boost::qvm::Z(q0) = boost::qvm::Z(qv0);

                boost::qvm::S(q1) = boost::qvm::W(qv1);
                boost::qvm::X(q1) = boost::qvm::X(qv1);
                boost::qvm::Y(q1) = boost::qvm::Y(qv1);
                boost::qvm::Z(q1) = boost::qvm::Z(qv1);

                T qqr = boost::qvm::dot(q0,q1);
                T qr = boost::qvm::dot(qv0,qv1);
                T r = sqg::dot(v0,v1);

                // check quat case (W*W comes at the front)
                REQUIRE( r == qqr );

                if constexpr ( std::integral<T> )
                    REQUIRE(r == qr);
                else // approx the same since W*W component comes last with this one (just floating point shennanigans)
                    REQUIRE_THAT( r, Catch::Matchers::WithinRel(qr) );
            }
            else
            {
                T qr = boost::qvm::dot(qv0,qv1);
                T r = sqg::dot(v0,v1);
                REQUIRE( r == qr );
            }
        });
    }

    SECTION("operator- unary")
    {
        test_vec_operation<T,n>(generator, [](vec<T,n>& v, qvec<T,n>& qv) {
            REQUIRE(boost::qvm::mag_sqr(error(-v, -qv)) == T{0});
        });

        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
            qvec<T,n> qr = qv0 - qv1;
            vec<T,n> r = v0 - v1;
            REQUIRE(boost::qvm::mag_sqr(error(r, qr)) == T{0});
        });
    }

    SECTION("operator+")
    {
        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
            qvec<T,n> qr = qv0 + qv1;
            vec<T,n> r = v0 + v1;
            REQUIRE(boost::qvm::mag_sqr(error(r, qr)) == T{0});
        });
    }

    SECTION("operator*")
    {
        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
            qvec<T,n> qr = X(qv0) * qv1;
            vec<T,n> r = v0.x * v1;
            REQUIRE(boost::qvm::mag_sqr(error(r, qr)) == T{0});
        });

        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
            qvec<T,n> qr = qv1 * X(qv0);
            vec<T,n> r = v1 * v0.x;
            REQUIRE(boost::qvm::mag_sqr(error(r, qr)) == T{0});
        });
    }

    SECTION("operator/")
    {
        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
            if ( X(qv0) != T{0} )
            {
                qvec<T,n> qr = qv1 / X(qv0);
                vec<T,n> r = v1 / v0.x;
                REQUIRE(boost::qvm::mag_sqr(error(r, qr)) == T{0});
            }
        });
    }

    SECTION("operator*=")
    {
        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, vec<T,n>& v1, const qvec<T,n>& qv0, qvec<T,n>& qv1) {
            qv1 *= X(qv0);
            v1 *= v0.x;
            REQUIRE(boost::qvm::mag_sqr(error(v1, qv1)) == T{0});
        });
    }

    SECTION("operator/=")
    {
        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, vec<T,n>& v1, const qvec<T,n>& qv0, qvec<T,n>& qv1) {
            if ( X(qv0) != T{0} )
            {
                qv1 /= X(qv0);
                v1 /= v0.x;
                REQUIRE(boost::qvm::mag_sqr(error(v1, qv1)) == T{0});
            }
        });
    }

    SECTION("operator==")
    {
        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
            bool qr = qv0 == qv1;
            bool r = v0 == v1;
            REQUIRE(qr == r);
        });
    }

    SECTION("operator!=")
    {
        test_vec_operation2<T,n>(generator, [](const vec<T,n>& v0, const vec<T,n>& v1, const qvec<T,n>& qv0, const qvec<T,n>& qv1) {
            bool qr = qv0 != qv1;
            bool r = v0 != v1;
            REQUIRE(qr == r);
        });
    }

    SECTION("mag2")
    {
        test_vec_operation<T,n>(generator, [](const vec<T,n>& v0, const qvec<T,n>& qv0) {
            
            if constexpr ( n == 4 )
            {
                boost::qvm::quat<T> q0;

                boost::qvm::S(q0) = boost::qvm::W(qv0);
                boost::qvm::X(q0) = boost::qvm::X(qv0);
                boost::qvm::Y(q0) = boost::qvm::Y(qv0);
                boost::qvm::Z(q0) = boost::qvm::Z(qv0);

                T qqr = boost::qvm::mag_sqr(q0);
                T qr = boost::qvm::mag_sqr(qv0);
                T r = sqg::mag2(v0);

                // check quat case (W*W comes at the front)
                REQUIRE( r == qqr );

                if constexpr ( std::integral<T> )
                    REQUIRE(r == qr);
                else // approx the same since W*W component comes last with this one (just floating point shennanigans)
                    REQUIRE_THAT( r, Catch::Matchers::WithinRel(qr) );
            }
            else
            {
                T qr = boost::qvm::mag_sqr(qv0);
                T r = sqg::mag2(v0);
                REQUIRE( r == qr );
            }
        });
    }

    SECTION("mag")
    {
        test_vec_operation<T,n>(generator, [](const vec<T,n>& v0, const qvec<T,n>& qv0) {
            if constexpr ( std::floating_point<T> )
            {
                if constexpr ( n == 4 )
                {
                    boost::qvm::quat<T> q0;

                    boost::qvm::S(q0) = boost::qvm::W(qv0);
                    boost::qvm::X(q0) = boost::qvm::X(qv0);
                    boost::qvm::Y(q0) = boost::qvm::Y(qv0);
                    boost::qvm::Z(q0) = boost::qvm::Z(qv0);

                    T qqr = boost::qvm::mag(q0);
                    T qr = boost::qvm::mag(qv0);
                    T r = sqg::mag(v0);

                    // check quat case (W*W comes at the front)
                    REQUIRE( r == qqr );
                    // approx the same since W*W component comes last with this one (just floating point shennanigans)
                    REQUIRE_THAT( r, Catch::Matchers::WithinRel(qr) );
                }
                else
                {
                    T qr = boost::qvm::mag(qv0);
                    T r = sqg::mag(v0);
                    REQUIRE( r == qr );
                }

            }
        });
    }

    SECTION("normalize")
    {
        test_vec_operation<T,n>(generator, [](vec<T,n>& v0, qvec<T,n>& qv0) {
            if constexpr ( std::floating_point<T> )
            {
                if constexpr ( n == 4 )
                {
                    boost::qvm::quat<T> q0;

                    boost::qvm::S(q0) = boost::qvm::W(qv0);
                    boost::qvm::X(q0) = boost::qvm::X(qv0);
                    boost::qvm::Y(q0) = boost::qvm::Y(qv0);
                    boost::qvm::Z(q0) = boost::qvm::Z(qv0);

                    boost::qvm::normalize(q0);
                    boost::qvm::normalize(qv0);
                    sqg::normalize(v0);

                    // check quat case (W*W comes at the front)
                    REQUIRE(boost::qvm::mag_sqr(error(v0,q0)) == T{0});
                    // approx the same since W*W component comes last with this one (just floating point shennanigans)
                    REQUIRE_THAT( boost::qvm::mag_sqr(error(v0,qv0)), Catch::Matchers::WithinAbs(T{0}, tol<T>::abs) );
                }
                else
                {
                    boost::qvm::normalize(qv0);
                    sqg::normalize(v0);
                    REQUIRE( boost::qvm::mag_sqr(error(v0,qv0)) == T{0} );
                }

            }
        });
    }

    SECTION("normalized")
    {
        test_vec_operation<T,n>(generator, [](vec<T,n>& v0, qvec<T,n>& qv0) {
            if constexpr ( std::floating_point<T> )
            {
                if constexpr ( n == 4 )
                {
                    boost::qvm::quat<T> q0;

                    boost::qvm::S(q0) = boost::qvm::W(qv0);
                    boost::qvm::X(q0) = boost::qvm::X(qv0);
                    boost::qvm::Y(q0) = boost::qvm::Y(qv0);
                    boost::qvm::Z(q0) = boost::qvm::Z(qv0);

                    auto rq = boost::qvm::normalized(q0);
                    auto rqv = boost::qvm::normalized(qv0);
                    auto r = sqg::normalized(v0);

                    // check quat case (W*W comes at the front)
                    REQUIRE(boost::qvm::mag_sqr(error(r,rq)) == T{0});
                    // approx the same since W*W component comes last with this one (just floating point shennanigans)
                    T err = boost::qvm::mag_sqr(error(r,rqv));
                    REQUIRE_THAT( err, Catch::Matchers::WithinAbs(T{0}, tol<T>::abs) );
                }
                else
                {
                    auto rqv = boost::qvm::normalized(qv0);
                    auto r = sqg::normalized(v0);
                    REQUIRE( boost::qvm::mag_sqr(error(r,rqv)) == T{0} );
                }

            }
        });
    }
}


TEST_CASE("qvm vec2")
{
    std::mt19937 generator{ Catch::getSeed() };
    SECTION("double") { test_vec<double, 2>(generator); }
    SECTION("float") { test_vec<float, 2>(generator); }
    SECTION("short") { test_vec<short, 2>(generator); }
    SECTION("int") { test_vec<int, 2>(generator);    }
}

TEST_CASE("qvm vec3")
{
    std::mt19937 generator{ Catch::getSeed() };
    SECTION("double") { test_vec<double, 3>(generator); }
    SECTION("float") { test_vec<float, 3>(generator); }
    SECTION("short") { test_vec<short, 3>(generator); }
    SECTION("int") { test_vec<int, 3>(generator);    }
}

TEST_CASE("qvm vec4 + quat")
{
    std::mt19937 generator{ 1949253684 };
    SECTION("double") { test_vec<double, 4>(generator); }
    SECTION("float") { test_vec<float, 4>(generator); }
    SECTION("short") { test_vec<short, 4>(generator); }
    SECTION("int") { test_vec<int, 4>(generator); }
}