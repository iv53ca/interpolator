#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_calc/N_types/C_motion_velocity_lines.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_profiler {
        namespace n_velocity {
            namespace n_prof {
                namespace {
                    namespace n_aux {
                        // Проверка на рассогласование движения по времени
                        void check_motion_time_difference(N_inter::n_motion_calc::n_types::C_motion &motion);
                    }
                }
                N_inter::n_motion_calc::n_types::C_motion_velocity_lines inter(QVector<N_inter::n_global_types::C_m_line>& lines); // Профилирование
                extern N_inter::n_motion_calc::n_types::C_motion motion; // Сегменты разложения движения по осям
            }
        }
    }
}
// --------------------------------------------------------
