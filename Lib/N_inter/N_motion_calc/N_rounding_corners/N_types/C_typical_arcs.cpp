#include "C_typical_arcs.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_profiler/N_trajectory/n_prof.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_types_calc/N_arc_circles.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_none_prof/n_data.h"
// --------------------------------------------------------

using N_inter::n_global_types::C_point;
using N_inter::n_global_types::COORD;
using N_inter::n_global_types::C_m_line;
using N_inter::n_motion_calc::n_rounding_corners::n_types::C_arc_circle;
using N_inter::S_exception;
// --------------------------------------------------------

double N_inter::n_motion_calc::n_rounding_corners::n_types::C_typical_arcs::get_min_width_for_axis(int axis) {
    if (axis < 0) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "axis < 0";
        exc.m_decision = "Отрицательный индекс";
        throw exc;
    }

    if (axis > N_inter::n_data::n_motion_vars::n_calc_vars::axis_count) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "axis > N_inter::n_data::n_motion_vars::n_calc_vars::axis_count";
        exc.m_decision = "Индекс превышает кол-во осей";
        throw exc;
    }

    return N_inter::n_motion_calc::n_rounding_corners::n_none_prof::n_data::typical_arcs.min_widths[axis];
}
// --------------------------------------------------------

double N_inter::n_motion_calc::n_rounding_corners::n_types::C_typical_arcs::get_min_high_for_axis(int axis) {
    if (axis < 0) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "axis < 0";
        exc.m_decision = "Отрицательный индекс";
        throw exc;
    }

    if (axis > N_inter::n_data::n_motion_vars::n_calc_vars::axis_count) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "axis > N_inter::n_data::n_motion_vars::n_calc_vars::axis_count";
        exc.m_decision = "Индекс превышает кол-во осей";
        throw exc;
    }

    return N_inter::n_motion_calc::n_rounding_corners::n_none_prof::n_data::typical_arcs.min_heights[axis];
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_types::C_typical_arcs::write() {
    // Запись типовых дуг для вписывания
    write_typical_arcs();

    // Записать минимально допустимые ширины и высоты
    write_min_values();
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_types::C_typical_arcs::write_typical_arcs() {
    // Очистка списка с типовыми дугами
    left_typical_arcs.clear();
    right_typical_arcs.clear();

    // Перебор осей
    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        C_point zero_point = 0;

        // Составление типового угла для вписывания
        QVector<C_m_line> lines = get_type_lines(i);
        QVector<C_m_line> prof_lines = lines;

        C_point angle_point = lines[0].m_second_point;

        // Запуск профилировщика траектории для составления типовой дуги
        prof_lines = N_inter::n_profiler::n_trajectory::n_prof::inter(prof_lines, N_inter::n_data::n_motion_vars::n_calc_vars::max_velocity_round[i], N_inter::n_data::n_motion_vars::n_calc_vars::split_segments_count_for_vel);
        prof_lines.pop_front();
        prof_lines.pop_back();

        // Запись типовой дуги для вписывания в трапецию слева
        C_arc_circle left;
        left.angle_position = angle_point;
        left.arc = prof_lines;
        N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_arc_circles::move(left, zero_point);
        left_typical_arcs.push_back(left);

        // Запись типовой дуги для вписывания в трапению справа
        C_arc_circle right = left;
        N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_arc_circles::mirroring_along_axis_y(right);
        C_arc_circle new_right;
        new_right.angle_position = right.angle_position;
        // Перебор в обратном направлении и обмен точек
        for (int j = right.size() - 1; j >= 0; j--) {
            C_m_line new_line = right[j];
            C_point point = new_line.m_first_point;
            new_line.m_first_point = new_line.m_second_point;
            new_line.m_second_point = point;
            new_right.arc.push_back(new_line);
        }
        N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_arc_circles::move(new_right, zero_point);

        right_typical_arcs.push_back(new_right);
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_types::C_typical_arcs::write_min_values() {
    // Очистка списков
    min_widths.clear();
    min_heights.clear();

    // Перебор осей
    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        C_arc_circle right = right_typical_arcs[i];
        // double min_width = 2 * abs(curr.arc.front().m_first_point[COORD::X] - curr.arc.back().m_second_point[COORD::X]);
        double min_width = 2 * abs(right.angle_position[COORD::X] - right.arc.front().m_first_point[COORD::X]);
        double min_high = abs(right.arc.front().m_first_point[COORD::Y] - right.arc.back().m_second_point[COORD::Y]);

        if (N_inter::n_algebra::n_math::is_more_than(0, min_width)) {
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(0, min_width)";
            exc.m_decision = "Отрицательная ширина";
            throw exc;
        }

        if (N_inter::n_algebra::n_math::is_more_than(0, min_high)) {
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(0, min_high)";
            exc.m_decision = "Отрицательная высота";
            throw exc;
        }

        min_widths.push_back(min_width);
        min_heights.push_back(min_high);
    }
}
// --------------------------------------------------------

QVector<C_m_line> N_inter::n_motion_calc::n_rounding_corners::n_types::C_typical_arcs::get_type_lines(int axis) {
    QVector<C_m_line> result;

    // Типовая наклонная прямая

    C_point first_point;
    first_point[COORD::X] = 0;
    first_point[COORD::Y] = 0;

    C_point second_point;
    second_point[COORD::Y] = N_inter::n_data::n_motion_vars::n_calc_vars::max_velocity[axis];
    second_point[COORD::X] = second_point[COORD::Y] / N_inter::n_data::n_motion_vars::n_calc_vars::acceleration[axis];

    C_m_line angle_line;
    angle_line.m_first_point  = first_point;
    angle_line.m_second_point = second_point;

    // Типовая горизонтальная прямая

    first_point = second_point;
    second_point[COORD::X] = second_point[COORD::X] * 2;

    C_m_line hor_line;
    hor_line.m_first_point = first_point;
    hor_line.m_second_point = second_point;

    result.push_back(angle_line);
    result.push_back(hor_line);

    return result;
}
// --------------------------------------------------------
