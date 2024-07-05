#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_point.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_types {
            namespace n_motion_table {
                struct S_motion_table_item {
                    N_inter::n_global_types::C_point m_position;
                    N_inter::n_global_types::C_point m_velocity;
                    double m_time;
                };
            }
        }
    }
}
// --------------------------------------------------------
