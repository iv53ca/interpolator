#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_rounding_corners/N_types/C_arc_circle.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_types/C_typical_arcs.h"
#include "N_inter/N_motion_calc/N_types/C_motion.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_rounding_corners {
            namespace n_none_prof {
                // Запись параметров для типовых дуг
                void init();

                // Закругление углов
                void round(N_inter::n_motion_calc::n_types::C_motion &motion);
            }
        }
    }
}
// --------------------------------------------------------
