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
void random_vec_real( std::mt19937& generator, sqg::quat<T>& vec, boost::qvm::quat<T>& qvm_vec )
{
    std::uniform_real_distribution<T> distribution{ T{-100}, T{100} };
    vec.x = distribution(generator);
    vec.y = distribution(generator);
    vec.z = distribution(generator);
    vec.w = distribution(generator);

    X(qvm_vec) = vec.x;
    Y(qvm_vec) = vec.y;
    Z(qvm_vec) = vec.z;
    S(qvm_vec) = vec.w;
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
boost::qvm::quat<T> error( const sqg::quat<T>& vec, const boost::qvm::quat<T>& qvm_vec )
{
    boost::qvm::quat<T> difference;
    X(difference) = X(qvm_vec) - vec.x;
    Y(difference) = Y(qvm_vec) - vec.y;
    Z(difference) = Z(qvm_vec) - vec.z;
    S(difference) = S(qvm_vec) - vec.w;
    return difference;
}

template<typename T, typename operation>
void test_quat_operation( std::mt19937& generator, operation op )
{
    using sqg_quat = sqg::quat<T>;
    using qvm_quat = boost::qvm::quat<T>;

    sqg_quat quat;
    qvm_quat qquat;
    
    for ( int i = 0; i < 100; i++ )
    {
        random_vec_real(generator, quat, qquat);
        
        REQUIRE(boost::qvm::mag_sqr(error(quat, qquat)) == T{0});
        CAPTURE(i);
        op(quat,qquat);
    }
}

template<typename T, typename operation>
void test_quat_operation2( std::mt19937& generator, operation op )
{
    using sqg_quat = sqg::quat<T>;
    using qvm_quat = boost::qvm::quat<T>;

    qvm_quat qquat0;
    qvm_quat qquat1;
    
    sqg_quat quat0;
    sqg_quat quat1;

    for ( int i = 0; i < 100; i++ )
    {
        random_vec_real(generator, quat0, qquat0);
        random_vec_real(generator, quat1, qquat1);
        
        REQUIRE(boost::qvm::mag_sqr(error(quat0, qquat0)) == T{0});
        REQUIRE(boost::qvm::mag_sqr(error(quat1, qquat1)) == T{0});
        CAPTURE(i);
        op(quat0,quat1,qquat0,qquat1);
    }
}

template<typename T, typename operation>
void test_quat_vec_operation2( std::mt19937& generator, operation op )
{
    using sqg_quat = sqg::quat<T>;
    using qvm_quat = boost::qvm::quat<T>;

    qvm_quat qquat;
    boost::qvm::vec<T,3> qvec;
    
    sqg_quat quat;
    sqg::vec3<T> vec;

    for ( int i = 0; i < 100; i++ )
    {
        random_vec_real(generator, quat, qquat);
        random_vec_real(generator, vec, qvec);
        
        REQUIRE(boost::qvm::mag_sqr(error(quat, qquat)) == T{0});
        REQUIRE(boost::qvm::mag_sqr(error(vec, qvec)) == T{0});
        CAPTURE(i);
        op(quat,vec,qquat,qvec);
    }
}

template<typename T>
using qquat = boost::qvm::quat<T>;

template<typename T>
using quat = sqg::quat<T>;

template<typename T, int n>
void test_vec(std::mt19937& generator)
{
    SECTION("set_identity")
    {
        test_quat_operation<T>(generator, [](quat<T> q, qquat<T> qq){
            boost::qvm::set_identity(qq);
            sqg::set_identity(q);
            REQUIRE(boost::qvm::mag_sqr(error(q, qq)) == T{0});
        });
    }

    SECTION("identity_quat")
    {
        test_quat_operation<T>(generator, [](quat<T> q, qquat<T> qq){
            qq = boost::qvm::identity_quat<T>();
            q = sqg::identity_quat<T>();
            REQUIRE(boost::qvm::mag_sqr(error(q, qq)) == T{0});
        });
    }

    SECTION("operator*")
    {
        test_quat_operation2<T>(generator, [](quat<T> q0, quat<T> q1, qquat<T> qq0, qquat<T> qq1){
            auto rq = qq0 * qq1;
            auto r = q0 * q1;
            
            REQUIRE(boost::qvm::mag_sqr(error(r, rq)) == T{0});
        });

        test_quat_vec_operation2<T>(generator, [](quat<T> q, sqg::vec3<T> v, qquat<T> qq, boost::qvm::vec<T,3> qv){
            auto rq = qq * qv;
            auto r = q * v;
            
            REQUIRE(boost::qvm::mag_sqr(error(r, rq)) == T{0});
        });
    }

    SECTION("set_rotx")
    {
        test_quat_operation2<T>(generator, [](quat<T> q0, quat<T> q1, qquat<T> qq0, qquat<T> qq1){
            boost::qvm::set_rotx(qq0, boost::qvm::S(qq1));
            sqg::set_rotx(q0, q1.w);            
            REQUIRE(boost::qvm::mag_sqr(error(q0,qq0)) == T{0});
        });
    }

    SECTION("set_roty")
    {
        test_quat_operation2<T>(generator, [](quat<T> q0, quat<T> q1, qquat<T> qq0, qquat<T> qq1){
            boost::qvm::set_roty(qq0, boost::qvm::S(qq1));
            sqg::set_roty(q0, q1.w);            
            REQUIRE(boost::qvm::mag_sqr(error(q0,qq0)) == T{0});
        });
    }

    SECTION("set_rotz")
    {
        test_quat_operation2<T>(generator, [](quat<T> q0, quat<T> q1, qquat<T> qq0, qquat<T> qq1){
            boost::qvm::set_rotz(qq0, boost::qvm::S(qq1));
            sqg::set_rotz(q0, q1.w);            
            REQUIRE(boost::qvm::mag_sqr(error(q0,qq0)) == T{0});
        });
    }

    SECTION("set_rot")
    {
        test_quat_operation2<T>(generator, [](quat<T> q0, quat<T> q1, qquat<T> qq0, qquat<T> qq1){
            boost::qvm::set_rot(qq0, boost::qvm::V(qq1), boost::qvm::S(qq1));
            
            // qvm has inconsistant behaviour between mat and quat
            // qvm rot normalises the axis and mat does not
            // so we will never normalise to give user preference if they have a normalised vector already
            sqg::set_rot(q0, sqg::normalized(sqg::V(q1)), sqg::S(q1));            
            REQUIRE(boost::qvm::mag_sqr(error(q0,qq0)) == T{0});
        });
    }
}


TEST_CASE("qvm quat")
{
    std::mt19937 generator{ Catch::getSeed() };
    SECTION("double") { test_vec<double, 4>(generator); }
    SECTION("float") { test_vec<float, 4>(generator); }
}