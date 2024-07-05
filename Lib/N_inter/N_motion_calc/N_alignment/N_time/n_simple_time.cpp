#include "n_simple_time.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
// --------------------------------------------------------

void N_inter::n_motion_calc::n_alignment::n_time::n_simple_time::align(N_inter::n_motion_calc::n_types::C_motion &motion) {
    for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        align_segments(motion[current_axis]);
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_alignment::n_time::n_simple_time::align_segments(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments) {
    // Выравнивание времени для сегментов
    for (int i = 0; i < segments.size() - 1; i++) {
        if (N_inter::n_algebra::n_math::is_not_equal(segments[i].get_end_line().m_second_point[n_global_types::X], segments[i + 1].get_begin_line().m_first_point[n_global_types::X])) {
            // Разница времени (либо положительная, либо отрицательная
            double dX = segments[i + 1].get_begin_line().m_first_point[n_global_types::X] - segments[i].get_end_line().m_second_point[n_global_types::X];
            for (int j = 0; j < segments[i + 1].get_size(); j++) {
                segments[i + 1][j].m_first_point[n_global_types::X] -= dX;
                segments[i + 1][j].m_second_point[n_global_types::X] -= dX;
            }
        }
    }
}
// --------------------------------------------------------
