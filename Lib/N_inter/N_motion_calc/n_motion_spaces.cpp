#include "n_motion_spaces.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_algebra/n_math.h"
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_spaces::n_aux::remove(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments) {
    for (int i = 0; i < segments.size() - 1; i++) {
        // Удаление пробелов в пределах сегмента по необходимости
        n_aux::remove(segments[i]);

        // Удаление пробелов между сегментами по необходимости
        n_aux::remove(segments[i], segments[i + 1]);
    }
    n_aux::remove(segments[segments.size() - 1]);
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_spaces::n_aux::remove(N_inter::n_motion_calc::n_types::C_motion_section &segment) {
    if (segment.get_size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void n_motion_calc::n_motion_spaces::n_aux::remove(n_types::C_motion_section &segment)";
        exc.m_condition = "segment.Lines.size() == 0";
        exc.m_decision = "Пустой сегмент движения";
        throw exc;
    }

    for (int i = 0; i < segment.get_size() - 1; i++) {
        if (!N_inter::n_algebra::n_math::is_equal(segment[i].m_second_point[n_global_types::X], segment[i + 1].m_first_point[n_global_types::X])) {
            // Разница
            double d_x = segment[i + 1].m_first_point[n_global_types::X] - segment[i].m_second_point[n_global_types::X];

            // Смещение следующей линии
            segment[i + 1].m_first_point[n_global_types::X] -= d_x;
            segment[i + 1].m_second_point[n_global_types::X] -= d_x;
        }
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_spaces::n_aux::remove(N_inter::n_motion_calc::n_types::C_motion_section &first_segment, N_inter::n_motion_calc::n_types::C_motion_section &next_segment) {
    if (!N_inter::n_algebra::n_math::is_equal(first_segment.get_end_line().m_second_point[n_global_types::X], next_segment.get_begin_line().m_first_point[n_global_types::X])) {
        // Разница
        double d_x = next_segment.get_begin_line().m_first_point[n_global_types::X] - first_segment.get_end_line().m_second_point[n_global_types::X];

        // Смещение первой линии следующего сегмента
        next_segment[0].m_first_point[n_global_types::X] -= d_x;
        next_segment[0].m_second_point[n_global_types::X] -= d_x;
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_spaces::remove(N_inter::n_motion_calc::n_types::C_motion &motion) {
    for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        n_aux::remove(motion[current_axis]);
    }
}
// --------------------------------------------------------
