#include "n_simple.h"
#include "N_inter/N_motion_calc/N_alignment/N_time/n_simple_time.h"
#include <QDebug>
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_algebra/n_limits.h"
#include "N_inter/S_exception.h"
// --------------------------------------------------------

void N_inter::n_motion_calc::n_alignment::n_area::n_simple::n_aux::correct_segment_base(N_inter::n_motion_calc::n_types::C_motion_section &segment, double dT) {
    // Профиль - треугольник, отнять площадь нельзя
    if (segment.get_size() == 2) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KSimpleAreaAlignment::_correct_segment_base(n_motion_calc::n_types::C_motion_section& segment, double dT)";
        exc.m_condition = "segment.get_size() == 2";
        exc.m_decision = "Профиль движения треугольник, а должен быть трапеция";
        throw exc;
    }
    // Профиль - трапеция
    else if (segment.get_size() == 3) {
        segment[1].m_second_point[n_global_types::X] = segment[1].m_second_point[n_global_types::X] - dT;

        segment[2].m_first_point[n_global_types::X] = segment[2].m_first_point[n_global_types::X] - dT;
        segment[2].m_second_point[n_global_types::X] = segment[2].m_second_point[n_global_types::X] - dT;
    }
    else {
        // qDebug() << "Движение отсутствует";
        N_inter::S_exception exc;
        exc.m_calling_object = "void KSimpleAreaAlignment::_correct_segment_base(n_motion_calc::n_types::C_motion_section& segment, double dT)";
        exc.m_condition = "else";
        exc.m_decision = "Неизвестный профиль движения: ожидается трапеция";
        throw exc;
    }
}
// --------------------------------------------------------

double N_inter::n_motion_calc::n_alignment::n_area::n_simple::n_aux::rectangle_time(N_inter::n_motion_calc::n_types::C_motion_section &realSegment, N_inter::n_motion_calc::n_types::C_motion_section &newSegment) {
    // Профиль - треугольник, отнять площадь нельзя
    if (newSegment.get_size() == 2) {
        return 0;
    }

    // Профиль - трапеция
    else if (newSegment.get_size() == 3) {
        double realS = N_inter::n_algebra::n_math::get_segment_area(realSegment); // Ожидаемая площадь
        double newS = N_inter::n_algebra::n_math::get_segment_area(newSegment);   // Фактическая площадь
        double dS = abs(newS - realS); // Разница между площадями

        // Если разница площадей совпадает с прямоугольной составляющей движения
        if (N_inter::n_algebra::n_math::is_equal(dS, N_inter::n_algebra::n_math::get_line_area(newSegment[1]))) {
            return newSegment[1].m_second_point[n_global_types::X] - newSegment[1].m_first_point[n_global_types::X]; // t
        }
        // Если разница площадей превышает площадь прямоугольной составляющей движения
        else if (N_inter::n_algebra::n_math::is_more_than(dS, N_inter::n_algebra::n_math::get_line_area(newSegment[1]))) {
            return newSegment[1].m_second_point[n_global_types::X] - newSegment[1].m_first_point[n_global_types::X]; // t
        }
        // Если разница площадей меньше площади прямоугольной составляющей движения
        else {
            double h = newSegment[1].m_first_point[n_global_types::Y]; // Высота прямоугольника
            return dS / h; // t
        }
    }
    else {
        return 0; // Движения нет
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_alignment::n_area::n_simple::align(N_inter::n_motion_calc::n_types::C_motion &realMotion, N_inter::n_motion_calc::n_types::C_motion &newMotion) {
    for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        if (realMotion[current_axis].size() != newMotion[current_axis].size()) {
            // TODO exception Различная длина векторов сегментов для AreaAdjustment
        }
    }

    // WARNING Длины могут различаться
    // Для начала нужно по возможности сократить длины прямоугольных составляющих сегментов - получим выигрыш по времени
    int count = realMotion[0].count();

    for (int i = 0; i < count; i++) {
        // Вычисление удаляемого времени
        QVector<double> t_arr;
        for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
            t_arr.push_back(n_aux::rectangle_time(realMotion[current_axis][i], newMotion[current_axis][i]));
        }
        double dT = *std::min(t_arr.begin(), t_arr.end());

        // Корректировка длины сегмента по необходимости
        if (!N_inter::n_algebra::n_math::is_equal(dT, 0)) {
            for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
                n_aux::correct_segment_base(newMotion[current_axis][i], dT);
            }
        }
    }

    for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        N_inter::n_motion_calc::n_alignment::n_time::n_simple_time::align_segments(newMotion[current_axis]);
    }
}
// --------------------------------------------------------
