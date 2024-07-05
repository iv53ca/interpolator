#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion.h"
#include "N_inter/N_motion_calc/N_types/C_motion_velocity_lines.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_motion_velocity_lines {
            // Получение смещения движения на offset_t единиц времени
            void set_motion_offset_by_time(N_inter::n_motion_calc::n_types::C_motion_velocity_lines& motion, double time_offset);

            // Получение времени движения
            double get_motion_time(N_inter::n_motion_calc::n_types::C_motion_velocity_lines& motion);

            // TODO: переименовать
            // Получить смещение для выбранной оси по времени
            double get_time_offset_for_axis(N_inter::n_motion_calc::n_types::C_motion_velocity_lines& motion, double time, int axis);

            // TODO: переименовать
            // Получить скорость для выбранной оси по времени
            double get_vel_offset_for_axis(N_inter::n_motion_calc::n_types::C_motion_velocity_lines& motion, double time, int axis);

            // Получение профиля движения для аварии
            N_inter::n_motion_calc::n_types::C_motion_velocity_lines get_kill_motion(N_inter::n_global_types::C_point current_velocity);

            // Согласование по времени (добавление пустот)
            void add_voids_for_time(N_inter::n_motion_calc::n_types::C_motion_velocity_lines& motion);

            // Удержание движения
            void add_empty_time(N_inter::n_motion_calc::n_types::C_motion_velocity_lines& motion);
        }
    }
}
// --------------------------------------------------------
