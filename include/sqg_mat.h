#pragma once
#include "sqg_struct.h"
#include "sqg_mat22.h"
#include "sqg_mat33.h"
#include "sqg_mat44.h"

namespace sqg
{
    template<typename T, int dims>
    [[nodiscard]] SQUIGGLE_INLINE constexpr detail::mat_type_dims<T,dims>::mat_type identity_mat()
    {
        typename detail::mat_type_dims<T, dims>::mat_type m;
        set_identity(m);
        return m;
    }

    
}