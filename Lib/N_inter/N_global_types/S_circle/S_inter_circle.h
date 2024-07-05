#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/S_circle/S_circle.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        struct S_inter_circle : public N_inter::n_global_types::S_circle {
            N_inter::n_global_types::C_point m_intersec_point_1;
            N_inter::n_global_types::C_point m_intersec_point_2;
        };
    }
}
// --------------------------------------------------------
