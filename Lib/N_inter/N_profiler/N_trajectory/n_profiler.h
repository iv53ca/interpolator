#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_calc/N_types/C_motion_velocity_lines.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_profiler {
        namespace {
            namespace n_aux {
                QVector<N_inter::n_global_types::C_m_line> trajectory(QVector<N_inter::n_global_types::C_m_line>& lines, bool profStat); // Скорость
            }
        }
        void clear_data();
        void proxy_trajectory(QString a_lines_string, const bool a_prof_stat, QVector<N_inter::n_global_types::C_m_line>& trajectory);
        N_inter::n_motion_calc::n_types::C_motion_velocity_lines Velocity(QVector<N_inter::n_global_types::C_m_line>& lines, bool profStat); // Траектория
    }
}
// --------------------------------------------------------
