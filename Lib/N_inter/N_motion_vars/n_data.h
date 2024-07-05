#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_calc/N_types/C_motion_velocity_lines.h"
#include "N_inter/N_motion_calc/N_types/N_motion_table/S_motion_table.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_data {
        namespace n_motion_vars {
            extern N_inter::n_motion_calc::n_types::C_motion_velocity_lines motion;  // Разложенное по осям движение
            extern QVector<N_inter::n_global_types::C_m_line> trajectory; // Траектория
            extern N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table motion_table; // Таблица движений
        }
    }
}
// --------------------------------------------------------
