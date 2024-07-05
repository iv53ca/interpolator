#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_velocities {
            // Нахождение проекции скорости на одну из осей
            double get_speed_projection(N_inter::n_global_types::C_m_line& line, double& F, int& axis);
        }
    }
}
// --------------------------------------------------------
