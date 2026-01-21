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
void random_vec_real( std::mt19937& generator, sqg::mat33<T>& mat, boost::qvm::mat<T,3,3>& qvm_mat )
{
    std::uniform_real_distribution<T> distribution{ -std::numbers::pi_v<T>, std::numbers::pi_v<T> };
    
    boost::qvm::vec<T,3> axis;
    X(axis) = distribution(generator);
    Y(axis) = distribution(generator);
    Z(axis) = distribution(generator);
    normalize(axis);

    T angle = distribution(generator);

    qvm_mat = boost::qvm::rot_mat<3>(axis, angle);

    sqg::A00(mat, boost::qvm::A00(qvm_mat));
    sqg::A01(mat, boost::qvm::A01(qvm_mat));
    sqg::A02(mat, boost::qvm::A02(qvm_mat));

    sqg::A10(mat, boost::qvm::A10(qvm_mat));
    sqg::A11(mat, boost::qvm::A11(qvm_mat));
    sqg::A12(mat, boost::qvm::A12(qvm_mat));

    sqg::A20(mat, boost::qvm::A20(qvm_mat));
    sqg::A21(mat, boost::qvm::A21(qvm_mat));
    sqg::A22(mat, boost::qvm::A22(qvm_mat));
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
boost::qvm::mat<T,3,3> error( const sqg::mat33<T>& mat, const boost::qvm::mat<T,3,3>& qvm_mat )
{
    boost::qvm::mat<T,3,3> difference;
    boost::qvm::A00(difference) = boost::qvm::A00(qvm_mat) - sqg::A00(mat);
    boost::qvm::A01(difference) = boost::qvm::A01(qvm_mat) - sqg::A01(mat);
    boost::qvm::A02(difference) = boost::qvm::A02(qvm_mat) - sqg::A02(mat);
    boost::qvm::A10(difference) = boost::qvm::A10(qvm_mat) - sqg::A10(mat);
    boost::qvm::A11(difference) = boost::qvm::A11(qvm_mat) - sqg::A11(mat);
    boost::qvm::A12(difference) = boost::qvm::A12(qvm_mat) - sqg::A12(mat);
    boost::qvm::A20(difference) = boost::qvm::A20(qvm_mat) - sqg::A20(mat);
    boost::qvm::A21(difference) = boost::qvm::A21(qvm_mat) - sqg::A21(mat);
    boost::qvm::A22(difference) = boost::qvm::A22(qvm_mat) - sqg::A22(mat);
    return difference;
}

template<typename T, typename operation>
void test_quat_operation( std::mt19937& generator, operation op )
{
    using sqg_quat = sqg::mat33<T>;
    using qvm_quat = boost::qvm::mat<T,3,3>;

    sqg::mat33<T> mat;
    boost::qvm::mat<T,3,3> qmat;
    
    for ( int i = 0; i < 100; i++ )
    {
        random_vec_real(generator, mat, qmat);
        
        REQUIRE(error(mat, qmat) == boost::qvm::zero_mat<T,3>());
        CAPTURE(i);
        op(mat,qmat);
    }
}

template<typename T, typename operation>
void test_quat_operation2( std::mt19937& generator, operation op )
{
    boost::qvm::mat<T,3,3> qmat0;
    boost::qvm::mat<T,3,3> qmat1;
    
    sqg::mat33<T> mat0;
    sqg::mat33<T> mat1;

    for ( int i = 0; i < 100; i++ )
    {
        random_vec_real(generator, mat0, qmat0);
        random_vec_real(generator, mat1, qmat1);
        
        REQUIRE(error(mat0, qmat0) == boost::qvm::zero_mat<T,3>());
        REQUIRE(error(mat1, qmat1) == boost::qvm::zero_mat<T,3>());
        CAPTURE(i);
        op(mat0,mat1,qmat0,qmat1);
    }
}

template<typename T, typename operation>
void test_quat_vec_operation2( std::mt19937& generator, operation op )
{
    boost::qvm::mat<T,3,3> qmat;
    boost::qvm::vec<T,3> qvec;
    
    sqg::mat33<T> mat;
    sqg::vec3<T> vec;

    for ( int i = 0; i < 100; i++ )
    {
        random_vec_real(generator, mat, qmat);
        random_vec_real(generator, vec, qvec);
        
        REQUIRE(error(mat, qmat) == boost::qvm::zero_mat<T,3>());
        REQUIRE(boost::qvm::mag_sqr(error(vec, qvec)) == T{0});
        CAPTURE(i);
        op(mat,vec,qmat,qvec);
    }
}

template<typename T>
using qmat = boost::qvm::mat<T,3,3>;

template<typename T>
using mat = sqg::mat33<T>;

template<typename T, int n>
void test_vec(std::mt19937& generator)
{
    SECTION("set_identity")
    {
        test_quat_operation<T>(generator, [](mat<T> q, qmat<T> qq){
            boost::qvm::set_identity(qq);
            sqg::set_identity(q);
            REQUIRE(error(q, qq) == boost::qvm::zero_mat<T,3>());
        });
    }

    SECTION("identity_quat")
    {
        test_quat_operation<T>(generator, [](mat<T> q, qmat<T> qq){
            qq = boost::qvm::identity_mat<T,3>();
            q = sqg::identity_mat<T,3>();
            REQUIRE(error(q, qq) == boost::qvm::zero_mat<T,3>());
        });
    }

    SECTION("operator*")
    {
        test_quat_operation2<T>(generator, [](mat<T> q0, mat<T> q1, qmat<T> qq0, qmat<T> qq1){
            auto rq = qq0 * qq1;
            auto r = q0 * q1;
            
            REQUIRE(error(r, rq) == boost::qvm::zero_mat<T,3>());
        });

        test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
            auto rq = qq * qv;
            auto r = q * v;
            
            REQUIRE(error(r, rq) == boost::qvm::zero_vec<T,3>());
        });
    }

    SECTION("set_rotx")
    {
        test_quat_operation2<T>(generator, [](mat<T> q0, mat<T> q1, qmat<T> qq0, qmat<T> qq1){
            boost::qvm::set_rotx(qq0, boost::qvm::A00(qq1));
            sqg::set_rotx(q0, sqg::A00(q1));            
            REQUIRE(error(q0,qq0) == boost::qvm::zero_mat<T,3>());
        });
    }

    SECTION("set_roty")
    {
        test_quat_operation2<T>(generator, [](mat<T> q0, mat<T> q1, qmat<T> qq0, qmat<T> qq1){
            boost::qvm::set_roty(qq0, boost::qvm::A00(qq1));
            sqg::set_roty(q0, sqg::A00(q1));             
            REQUIRE(error(q0,qq0) == boost::qvm::zero_mat<T,3>());
        });
    }

    SECTION("set_rotz")
    {
        test_quat_operation2<T>(generator, [](mat<T> q0, mat<T> q1, qmat<T> qq0, qmat<T> qq1){
            boost::qvm::set_rotz(qq0, boost::qvm::A00(qq1));
            sqg::set_rotz(q0, sqg::A00(q1));                   
            REQUIRE(error(q0,qq0) == boost::qvm::zero_mat<T,3>());
        });
    }

    SECTION("set_rot")
    {
        test_quat_operation2<T>(generator, [](mat<T> q0, mat<T> q1, qmat<T> qq0, qmat<T> qq1){
            boost::qvm::set_rot(qq0, boost::qvm::col<1>(qq1), boost::qvm::A00(qq1));
            sqg::set_rot(q0, sqg::col<1>(q1), sqg::A00(q1)); 
            auto m = error(q0,qq0);          
            REQUIRE(m == boost::qvm::zero_mat<T,3>());
        });
    }

    SECTION("Euler")
    {

        SECTION("set_rotxzx")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_xzx(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotxzx(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotxyx")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_xyx(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotxyx(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotyxy")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_yxy(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotyxy(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotyzy")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_yzy(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotyzy(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotzyz")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_zyz(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotzyz(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotzxz")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_zxz(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotzxz(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }
        
    }

    SECTION("Tait-Bryan")
    {
        SECTION("set_rotxzy")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_xzy(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotxzy(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotxyz")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_xyz(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotxyz(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotyxz")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_yxz(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotyxz(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotyzx")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_yzx(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotyzx(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotzyx")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_zyx(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotzyx(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }

        SECTION("set_rotzxy")
        {
            test_quat_vec_operation2<T>(generator, [](mat<T> q, sqg::vec3<T> v, qmat<T> qq, boost::qvm::vec<T,3> qv){
                boost::qvm::set_rot_zxy(qq, X(qv), Y(qv), Z(qv));
                sqg::set_rotzxy(q, X(v), Y(v), Z(v)); 
                REQUIRE(error(q,qq) == boost::qvm::zero_mat<T,3>());
            });
        }
    }
}


TEST_CASE("qvm mat")
{
    std::mt19937 generator{ Catch::getSeed() };
    SECTION("double") { test_vec<double, 4>(generator); }
    SECTION("float") { test_vec<float, 4>(generator); }
}