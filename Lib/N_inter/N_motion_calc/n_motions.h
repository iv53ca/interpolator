#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_motion_calc/n_motion_velocity_lines.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_motions {
            // Удаление пустых линий
            void remove_empty_lines(N_inter::n_motion_calc::n_types::C_motion& motion);

            // Удаление пустых секций
            void remove_empty_sections(N_inter::n_motion_calc::n_types::C_motion& motion);

            // Получение смещения движения на offset_t единиц времени
            void set_motion_offset_by_time(N_inter::n_motion_calc::n_types::C_motion& motion, double time_offset);

            // Получение времени движения
            double get_motion_time(N_inter::n_motion_calc::n_types::C_motion& motion);
        }
    }
}
// --------------------------------------------------------
