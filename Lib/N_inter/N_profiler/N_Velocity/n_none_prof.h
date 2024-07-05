#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_calc/N_types/C_motion_velocity_lines.h"
#include "N_inter/N_motion_calc/N_types/C_motion.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_profiler {
        namespace n_velocity {
            namespace n_none_prof {
                namespace {
                    // TODO переименовать
                    namespace n_aux {
                        QVector<N_inter::n_global_types::C_point> proxy_inter(N_inter::n_global_types::C_m_line& line, double& ts, int axis); // Профилирование скорости вдоль конкретной линии (произвольная ось)
                        QVector<N_inter::n_global_types::C_point> inter(N_inter::n_global_types::C_m_line& line, double& ts, int axis);
                        void opposite_speed_profile_x(N_inter::n_global_types::C_m_line& line, int axis); // Разворот направленного в обратную сторону движения
                        void opposite_points_speed_profile_y(QVector<N_inter::n_global_types::C_point>& points);
                        bool movement_in_opposite_direction(N_inter::n_global_types::C_m_line& line, int axis); // Проверка обратного движения вдоль оси
                    }
                }
                N_inter::n_motion_calc::n_types::C_motion_velocity_lines proxy_inter(QVector<N_inter::n_global_types::C_m_line>& lines);
                N_inter::n_motion_calc::n_types::C_motion_velocity_lines inter(QVector<N_inter::n_global_types::C_m_line>& lines); // Профилирование

                // TODO: убрать
                extern N_inter::n_motion_calc::n_types::C_motion motion;
            }
        }
    }
}
// --------------------------------------------------------
