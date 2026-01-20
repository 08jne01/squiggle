#pragma once
#include <type_traits>
#include "sqg.h"
namespace sqg::coordinates
{

    template<typename T>
    struct SystemMat
    {
        // Here we define all the coordinate systems.
        // Below they are defined in terms of Local tangent plane coordinates (https://en.wikipedia.org/wiki/Local_tangent_plane_coordinates)
        // however this does not preclude the functions being used for other coordinate systems.
        //
        // To this end this just means:
        //
        // - north -> forward
        // - east -> right
        // - up -> up
        //
        // For a detailed explaination of how these transforms are calculated read below.
        // Let A' be the transform in frame **new** and A be the transform in frame (old).
        // Let v' be the vector in frame **new** and v be the vector in frame (new).
        // Let p' be the vector transformed by A' and p be the vector transformed by A.
        // Let M be the basis change from **old** to **new**
        // The transform A' is then given by the formula below.
        // See //https://stackoverflow.com/questions/1263072/changing-a-matrix-from-right-handed-to-left-handed-coordinate-system
        //
        // A' = M * A * M^-1 
        //
        // Intuitively we can understand this by first transforming v' -> v
        // this is going from new to old therefore we must inverse M.
        //
        // v = M^-1 * v'
        //
        // we can then apply the transform A to v as they both are in the old frame.
        //
        // p = A * v
        //
        // p is then in the **old** frame we can transform it back to **new** frame using M
        //
        // p' = M * p
        //
        // giving us
        //
        // p' = M * A * M^-1 * v'
    
        static constexpr sqg::mat33<T> NUE_TO_NWU = {{  // NUE to NWU Matrix
            {T{1},  T{0},  T{ 0}}, // stays same
            {T{0},  T{0},  T{-1}}, // z (east) becomes y (west), flips
            {T{0},  T{1},  T{ 0}}, // y (up) becomes z (up)
        }};

        static constexpr sqg::mat33<T> NUE_TO_NED = {{ // NUE to NED Matrix
            {T{1}, T{ 0},   T{0}}, // stays same
            {T{0}, T{ 0},   T{1}}, // z (east) becomes y (east) 
            {T{0}, T{-1},   T{0}}, // y (up) becomes z (down), flips
        }};

        static constexpr sqg::mat33<T> NWU_TO_NUE = sqg::inverse(NUE_TO_NWU);
        static constexpr sqg::mat33<T> NED_TO_NUE = sqg::inverse(NUE_TO_NED);

        static constexpr sqg::mat33<T> NWU_TO_NED = NUE_TO_NED * NWU_TO_NUE;
        static constexpr sqg::mat33<T> NED_TO_NWU = NWU_TO_NUE * NUE_TO_NED;

    };

    template<std::floating_point T>
    struct SystemQuat
    {
        // This is the same as the SystemMat but for quaternions instead - otherwise the maths is equivalent.
        // Calculated from sqg::convert_to<sqg::quatd>( basis matrix ) of the matricies above (since constexpr convert_to for quat to mat doesn't exist)
        static constexpr sqg::quat<T> NUE_TO_NED = {T{0.70710678118654746}, T{-0.70710678118654746}, T{0.0}, T{0.0}};
        static constexpr sqg::quat<T> NUE_TO_NWU = {T{0.70710678118654746}, T{ 0.70710678118654746}, T{0.0}, T{0.0}};

        static constexpr sqg::quat<T> NED_TO_NUE = sqg::inverse( NUE_TO_NED );
        static constexpr sqg::quat<T> NWU_TO_NUE = sqg::inverse( NUE_TO_NWU );

        static constexpr sqg::quat<T> NWU_TO_NED = NUE_TO_NED * NWU_TO_NUE;
        static constexpr sqg::quat<T> NED_TO_NWU = NWU_TO_NUE * NUE_TO_NED;
    };

    // Produces matrix with coordinates defined as:
    // +x -> forward (north)
    // +y -> left (west)
    // +z -> up
    //
    // +x rotation -> roll right
    // +y rotation -> pitch down
    // +z rotation -> yaw left
    //
    // from North,Up,East coordinates.
    template<concepts::read_mat33_type M>
    inline constexpr mat_value<M> NUEtoNWU( const M& matrix ) { return SystemMat<mat_scalar<M>>::NUE_TO_NWU * matrix * SystemMat<mat_scalar<M>>::NWU_TO_NUE; }

    // See Matrix Definition Above
    template<concepts::read_quat_type Q>
    inline constexpr vec_value<Q> NUEtoNWU( const Q& quaternion ) { return SystemQuat<vec_scalar<Q>>::NUE_TO_NWU * quaternion * SystemQuat<vec_scalar<Q>>::NWU_TO_NUE; }

    // See Matrix Definition Above
    template<concepts::read_vec3_type V>
    inline constexpr vec_value<V> NUEtoNWU( const V& vector ) { return SystemMat<vec_scalar<V>>::NUE_TO_NWU * vector; }

    // Produces matrix with coordinates defined as:
    // +x -> forward (north)
    // +y -> right (east)
    // +z -> down
    //
    // +x rotation -> roll right
    // +y rotation -> pitch up
    // +z rotation -> yaw right
    //
    // from North,Up,East coordinates.
    template<concepts::read_mat33_type M>
    inline constexpr mat_value<M> NUEtoNED( const M& matrix ) { return SystemMat<mat_scalar<M>>::NUE_TO_NED * matrix * SystemMat<mat_scalar<M>>::NED_TO_NUE; }

    template<concepts::read_quat_type Q>
    inline constexpr vec_value<Q> NUEtoNED( const Q& quaternion ) { return SystemQuat<vec_scalar<Q>>::NUE_TO_NED * quaternion * SystemQuat<vec_scalar<Q>>::NED_TO_NUE; }

    // See Matrix Definition Above
    template<concepts::read_vec3_type V>
    inline constexpr vec_value<V> NUEtoNED( const V& vector ) { return SystemMat<vec_scalar<V>>::NUE_TO_NED * vector; }

    // Produces matrix with coordinates defined as:
    // +x -> forward (north)
    // +y -> up
    // +z -> right (east)
    //
    // +x rotation -> roll right
    // +y rotation -> pitch up
    // +z rotation -> yaw left
    //
    // from North,East,Down
    template<sqg::concepts::read_mat33_type M>
    inline constexpr mat_value<M> NEDtoNUE( const M& matrix ) { return SystemMat<mat_scalar<M>>::NED_TO_NUE * matrix * SystemMat<mat_scalar<M>>::NUE_TO_NED; }

    // See Matrix Definition Above
    template<concepts::read_quat_type Q>
    inline constexpr vec_value<Q> NEDtoNUE( const Q& quaternion ) { return SystemQuat<vec_scalar<Q>>::NED_TO_NUE * quaternion * SystemQuat<vec_scalar<Q>>::NUE_TO_NED; }

    // See Matrix Definition Above
    template<concepts::read_vec3_type V>
    inline constexpr vec_value<V> NEDtoNUE( const V& vector ) { return SystemQuat<vec_scalar<V>>::NED_TO_NUE * vector; }

    // Produces matrix with coordinates defined as:
    // +x -> forward (north)
    // +y -> up
    // +z -> right (east)
    //
    // +x rotation -> roll right
    // +y rotation -> pitch up
    // +z rotation -> yaw left
    //
    // from North,West,Up
    template<concepts::read_mat33_type M>
    inline constexpr mat_value<M> NWUtoNUE( const M& matrix ) { return SystemMat<mat_scalar<M>>::NWU_TO_NUE * matrix * SystemMat<mat_scalar<M>>::NUE_TO_NWU; }

    template<concepts::read_quat_type Q>
    inline constexpr vec_value<Q> NWUtoNUE( const Q& quaternion ) { return SystemQuat<vec_scalar<Q>>::NWU_TO_NUE * quaternion * SystemQuat<vec_scalar<Q>>::NUE_TO_NWU; }

    // See Matrix Definition Above
    template<concepts::read_vec3_type V>
    inline constexpr vec_value<V> NWUtoNUE( const V& vector ) { return SystemMat<vec_scalar<V>>::NWU_TO_NUE * vector; }

    // Produces matrix with coordinates defined as:
    // +x -> forward (north)
    // +y -> right (east)
    // +z -> down
    //
    // +x rotation -> roll right
    // +y rotation -> pitch up
    // +z rotation -> yaw right
    //
    // from North,Up,East coordinates.
    template<concepts::read_mat33_type M>
    inline constexpr mat_value<M> NWUtoNED( const M& matrix ) { return SystemMat<mat_scalar<M>>::NWU_TO_NED * matrix * SystemMat<mat_scalar<M>>::NED_TO_NWU; }

    // See Matrix Definition Above
    template<concepts::read_quat_type Q>
    inline constexpr vec_value<Q> NWUtoNED( const Q& quaternion ) { return SystemQuat<vec_scalar<Q>>::NWU_TO_NED * quaternion * SystemQuat<vec_scalar<Q>>::NED_TO_NWU; }

    // See Matrix Definition Above
    template<concepts::read_vec3_type V>
    inline constexpr vec_value<V> NWUtoNED( const V& vector ) { return SystemMat<vec_scalar<V>>::NWU_TO_NED * vector; }

    // Produces matrix with coordinates defined as:
    // +x -> forward (north)
    // +y -> left (west)
    // +z -> up
    //
    // +x rotation -> roll right
    // +y rotation -> pitch down
    // +z rotation -> yaw left
    //
    // from North,East,Down coordinates.
    template<concepts::read_mat33_type M>
    inline constexpr mat_value<M> NEDtoNWU( const M& matrix ) { return SystemMat<mat_scalar<M>>::NED_TO_NWU * matrix * SystemMat<mat_scalar<M>>::NWU_TO_NED; }

    // See Matrix Definition Above
    template<concepts::read_quat_type Q>
    inline constexpr vec_value<Q> NEDtoNWU( const Q& quaternion ) { return SystemQuat<vec_scalar<Q>>::NED_TO_NWU * quaternion * SystemQuat<vec_scalar<Q>>::NWU_TO_NED; }

    // See Matrix Definition Above
    template<concepts::read_vec3_type V>
    inline constexpr vec_value<V> NEDtoNWU( const V& vector ) { return SystemMat<vec_scalar<V>>::NED_TO_NWU * vector; }
}
