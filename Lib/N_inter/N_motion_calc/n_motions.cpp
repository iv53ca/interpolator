#include "n_motions.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

using N_inter::n_global_types::COORD;
using N_inter::n_motion_calc::n_types::C_motion;
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motions::remove_empty_lines(n_types::C_motion &motion) {
    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        for (int i = 0; i < motion[current_axis].size(); i++) {
            for (int j = 0; j < motion[current_axis][i].get_size(); j++) {
                N_inter::n_global_types::C_m_line current_line = motion[current_axis][i][j];
                if (N_inter::n_geom::n_lines::is_empty_line(current_line)) {
                    motion[current_axis][i].remove_at(j);
                    j--;
                }
            }
        }
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motions::remove_empty_sections(N_inter::n_motion_calc::n_types::C_motion& motion) {
    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        for (int i = 0; i < motion[current_axis].size(); i++) {
            if (motion[current_axis][i].get_size() == 0) {
                motion[current_axis].removeAt(i);
                i--;
            }
        }
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motions::set_motion_offset_by_time(n_types::C_motion &motion, double time_offset) {
    // Перебор осей
    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        // Перебор секций
        for (int j = 0; j < motion[i].size(); i++) {
            // Перебор отрезков, из которых состоит секция
            for (int k = 0; k < motion[i][j].get_size(); k++) {
                // Смещение по времени для каждого отрезка
                motion[i][j][k].m_first_point[COORD::X] = motion[i][j][k].m_first_point[COORD::X] + time_offset;
                motion[i][j][k].m_second_point[COORD::X] = motion[i][j][k].m_second_point[COORD::X] + time_offset;
            }
        }
    }
}
// --------------------------------------------------------

double N_inter::n_motion_calc::n_motions::get_motion_time(n_types::C_motion &motion) {
    return motion[0].back().get_end_line().m_second_point[COORD::X];
}
// --------------------------------------------------------
