#include "n_prof.h"
#include "N_inter/N_motion_calc/n_motion_sections.h"
#include <QDebug>
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_algebra/n_limits.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
// --------------------------------------------------------

using N_inter::n_global_types::C_point;
using N_inter::S_exception;
// --------------------------------------------------------

void N_inter::n_motion_calc::n_alignment::n_area::n_prof::n_aux::binary_area_correct(N_inter::n_motion_calc::n_types::C_motion_section &realSegment, N_inter::n_motion_calc::n_types::C_motion_section &newSegment) {
    // Ожидаемая площадь
    double realS = N_inter::n_algebra::n_math::get_segment_area(realSegment);

    // Фактическая площадь
    double factS = N_inter::n_algebra::n_math::get_segment_area(newSegment);

    if (N_inter::n_algebra::n_math::is_equal(realS, factS)) {
        // qDebug() << "Корректировка площади не нужна";
    }
    else if (N_inter::n_algebra::n_math::is_more_than(realS, factS)) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KProfAreaAlignment::_binary_area_correct(N_inter::n_motion_calc::n_types::C_motion_section& realSegment, N_inter::n_motion_calc::n_types::C_motion_section& newSegment)";
        exc.m_condition = "n_algebra::n_math::is_more_than(realS, factS)";
        exc.m_decision = "Невозможна корректировка площади";
        throw exc;
    }
    else {
        // TODO Сделать перерасчёт для ускорений
        // Определение ускорения разгона для этой оси [!!! пока что по умолчанию 1]
        double leftA = 1;
        // Определение ускорения замедления для этой оси [!!! пока что по умолчанию -1]
        double rightA = 1;

        // Получение границ для высоты h
        // TODO Возможно, здесь нужно вместо newSegment использовать realSegment
        C_point intersection_point;
        try {
            intersection_point = n_aux::get_low_section_borders_intersection_point(newSegment, leftA, rightA);
        }
        catch(S_exception exc) {
            exc.show_message();
        }

        double lowH  = intersection_point[N_inter::n_global_types::Y]; // Нижняя
        if (lowH < 0) { lowH = 0; }
        double highH = N_inter::n_motion_calc::n_motion_sections::segmentHeight(newSegment); // Верхняя

        // Промежуточная высота сегмента
        double h = lowH + (highH - lowH) / 2;

        // qDebug() << "h = " << h << ", lowH = " << lowH << ", highH = " << highH;

        // Искомый сегмент
        N_inter::n_motion_calc::n_types::C_motion_section tempSegment;
        while (true) {
            // Получить серидину интервала
            double middleH = lowH + (highH - lowH) / 2;

            // Найти площадь сегмента, усечённого этой высотой
            tempSegment = N_inter::n_motion_calc::n_motion_sections::truncatedSegment(newSegment, middleH, leftA, rightA);
            double S = N_inter::n_algebra::n_math::get_segment_area(tempSegment);

            // Если полученная площадь равна искомой, то остановить работу цикла
            if (N_inter::n_algebra::n_math::is_equal(S, realS)) {
                // qDebug() << "n_algebra::n_math::is_equal(S, realS)" << S << realS;
                newSegment = tempSegment;
                return;
            }
            // Если полученная площадь меньше искомой, то корректировка нижней границы
            else if (N_inter::n_algebra::n_math::is_more_than(realS, S)) {
                lowH = middleH;
            }
            // Если полученная площадь больше искомой, то корректировка верхней границы
            else {
                highH = middleH;
            }
        }
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_alignment::n_area::n_prof::n_aux::proxy_binary_area_correct(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &realSegments, QVector<N_inter::n_motion_calc::n_types::C_motion_section> &newSegments) {
    if (realSegments.size() != newSegments.size()) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KProfAreaAlignment::_proxy_binary_area_correct(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& realSegments, QVector<N_inter::n_motion_calc::n_types::C_motion_section>& newSegments)";
        exc.m_condition = "realSegments.size() != newSegments.size()";
        exc.m_decision = "Несоответствие длин сегментов";
        throw exc;
    }

    for (int i = 0; i < newSegments.size(); i++) {
        // Получить интервал с сегментами одного направления
        int _begin = i, _end = i;
        N_inter::n_motion_calc::n_motion_sections::unidirectionalSegments(newSegments, _begin, _end);

        // Флаг отражения вдоль оси абсцисс
        bool _mirrored_flag = false;
        if (N_inter::n_algebra::n_math::is_more_than(0, N_inter::n_algebra::n_limits::min_y(realSegments[i]))) {
            N_inter::n_motion_calc::n_motion_sections::segmentMirroredByY(newSegments, _begin, _end);
            _mirrored_flag = true;
        }

        for (int j = _begin; j <= _end; j++) {
            n_aux::binary_area_correct(realSegments[j], newSegments[j]);
        }

        i = _end;

        // Обратное отражение вдоль оси абсцисс
        if (_mirrored_flag) {
            N_inter::n_motion_calc::n_motion_sections::segmentMirroredByY(newSegments, _begin, _end);
        }
    }
}
// --------------------------------------------------------

double N_inter::n_motion_calc::n_alignment::n_area::n_prof::n_aux::rectangle_time(N_inter::n_motion_calc::n_types::C_motion_section& segment, N_inter::n_motion_calc::n_types::C_motion_section& true_segment) {
    N_inter::n_global_types::C_m_line true_segment_hor_line = n_geom::n_lines::get_hor_segment_line(true_segment);
    N_inter::n_global_types::C_m_line segment_hor_line      = n_geom::n_lines::get_hor_segment_line(segment);

    // Если один из профилей скорости не содержит прямоугольной составляющей
    if (n_geom::n_lines::is_empty_line(true_segment_hor_line) || n_geom::n_lines::is_empty_line(segment_hor_line)) {
        return 0;
    }

    // Если движение в пределах сегмента отсутствует
    if ((segment.get_size() == 1) && (N_inter::n_algebra::n_math::is_equal(segment[0].m_first_point[n_global_types::Y], 0)) && (N_inter::n_algebra::n_math::is_equal(segment[0].m_second_point[n_global_types::Y], 0))) {
        return 0;
    }

    // Площадь real_segment
    double real_area = N_inter::n_algebra::n_math::get_segment_area(true_segment);
    double new_area = N_inter::n_algebra::n_math::get_segment_area(segment);

    // Сколько площади можно убрать
    double d_area = new_area - real_area;

    // Площадь убрать нельзя
    if (N_inter::n_algebra::n_math::is_equal(d_area, 0)) {
        return 0;
    }

    // Проверка площадей истинного и фактического сегментов на положительность
    if (N_inter::n_algebra::n_math::is_more_or_equal(0, real_area) || N_inter::n_algebra::n_math::is_more_or_equal(0, new_area)) {
        qDebug() << real_area << new_area << d_area;
        N_inter::S_exception exc;
        exc.m_calling_object = "double KProfAreaAlignment::_rectangle_time(N_inter::n_motion_calc::n_types::C_motion_section& segment, N_inter::n_motion_calc::n_types::C_motion_section& true_segment)";
        exc.m_condition = "n_algebra::n_math::is_more_or_equal(0, real_area) || n_algebra::n_math::is_more_or_equal(0, new_area)";
        exc.m_decision = "Отрицательная площадь";
        throw exc;
    }

    // Если убирать площадь не требуется
    if (N_inter::n_algebra::n_math::is_equal(d_area, 0)) {
        return 0;
    }

    // Площадь прямоугольной составляющей нового сегмента
    double rect_area = abs(segment_hor_line.m_second_point[n_global_types::Y]) * (segment_hor_line.m_second_point[n_global_types::X] - segment_hor_line.m_first_point[n_global_types::X]);

    // Вычисление отнимаемой площади
    double remove_area = 0;
    // 1. Можно убрать прямоугольную составляющую целиком
    if (N_inter::n_algebra::n_math::is_more_or_equal(d_area, rect_area)) {
        remove_area = d_area;
    }
    // 2. Можно убрать только часть прямоугольной составляющей
    else {
        remove_area = d_area;
    }

    // Вычисление отнимаемого времени
    double d_time = 0;
    if (N_inter::n_algebra::n_math::is_equal(remove_area, new_area)) {
        d_time = segment_hor_line.m_second_point[n_global_types::X] - segment_hor_line.m_first_point[n_global_types::X];
    }
    else {
        d_time = remove_area / abs(segment_hor_line.m_first_point[n_global_types::Y]);
    }

    if (!N_inter::n_algebra::n_math::is_more_than(d_time, 0)) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double KProfAreaAlignment::_rectangle_time(N_inter::n_motion_calc::n_types::C_motion_section& segment, N_inter::n_motion_calc::n_types::C_motion_section& true_segment)";
        exc.m_condition = "!n_algebra::n_math::is_more_than(d_time, 0)";
        exc.m_decision = "Отрицательное время корректировки";
        throw exc;
    }

    return d_time;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_alignment::n_area::n_prof::n_aux::correct_segment_rectangle_area(N_inter::n_motion_calc::n_types::C_motion_section &segment, double &rectangle_time) {
    if (!N_inter::n_motion_calc::n_motion_sections::is_segment_contain_hor_lines(segment)) {
        return;
    }
    N_inter::n_global_types::C_m_line hor_line = n_geom::n_lines::get_hor_segment_line(segment);
    if (n_geom::n_lines::is_empty_line(hor_line)) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KProfAreaAlignment::_correct_segment_rectangle_area(N_inter::n_motion_calc::n_types::C_motion_section& segment, double& rectangle_time)";
        exc.m_condition = "n_geom::n_lines::is_empty_line(hor_line)";
        exc.m_decision = "Площадная корректировка для сегмента без прямоугольной составляющей";
        throw exc;
    }

    // Выделение прямоугольной составляющей движения
    for (int i = 0; i < segment.get_size(); i++) {
        if (n_geom::n_lines::is_hor_line(segment[i])) {
            if (N_inter::n_algebra::n_math::is_more_than(segment[i].m_first_point[n_global_types::X] + rectangle_time, segment[i].m_second_point[n_global_types::X])) {
                N_inter::S_exception exc;
                exc.m_calling_object = "void KProfAreaAlignment::_correct_segment_rectangle_area(N_inter::n_motion_calc::n_types::C_motion_section& segment, double& rectangle_time)";
                exc.m_condition = "n_algebra::n_math::is_more_than(segment[i].m_first_point[n_global_types::X] + rectangle_time, segment[i].m_second_point[n_global_types::X])";
                exc.m_decision = "Неправильное время корректировки";
                throw exc;
            }

            if (N_inter::n_algebra::n_math::is_more_than(segment[i].m_first_point[n_global_types::X], segment[i].m_second_point[n_global_types::X] - rectangle_time)) {
                N_inter::S_exception exc;
                exc.m_calling_object = "void KProfAreaAlignment::_correct_segment_rectangle_area(N_inter::n_motion_calc::n_types::C_motion_section& segment, double& rectangle_time)";
                exc.m_condition = "n_algebra::n_math::is_more_than(segment[i].m_first_point[n_global_types::X], segment[i].m_second_point[n_global_types::X] - rectangle_time)";
                exc.m_decision = "Время начала превышает время конца";
                throw exc;
            }

            // Сокращение основания
            segment[i].m_second_point[n_global_types::X] = segment[i].m_second_point[n_global_types::X] - rectangle_time;

            // Выход из цикла
            break;
        }
    }
}
// --------------------------------------------------------

C_point N_inter::n_motion_calc::n_alignment::n_area::n_prof::n_aux::get_low_section_borders_intersection_point(n_types::C_motion_section &section, double leftA, double rightA) {
    // Угловые коэффициенты прямых
    double k1 = -leftA;
    double k2 = rightA;

    if (k1 == k2) {
        N_inter::S_exception exc;
        exc.m_calling_object = "N_inter::n_motion_calc::n_alignment::n_area::n_prof::n_aux::get_low_section_borders_intersection_point(n_types::C_motion_section &section, double leftA, double rightA)";
        exc.m_condition = "k1 == k2";
        exc.m_decision = "Прямые параллельные";
        throw exc;
    }

    double x1 = section.get_begin_point()[N_inter::n_global_types::X];
    double x2 = section.get_end_point()[N_inter::n_global_types::X];

    double y1 = section.get_begin_point()[N_inter::n_global_types::Y];
    double y2 = section.get_end_point()[N_inter::n_global_types::Y];

    // Нужны только X и Y координаты (операция происходит на плоскости)
    C_point point;
    point[N_inter::n_global_types::X] = (k1 * x1 - k2 * x2 - y1 + y2) / (k1 - k2);
    point[N_inter::n_global_types::Y] = (k1 * k2 * x1 - k1 * k2 * x2 + k1 * y2 - k2 * y1) / (k1 - k2);

    return point;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_alignment::n_area::n_prof::binary_correct(N_inter::n_motion_calc::n_types::C_motion &realMotion, N_inter::n_motion_calc::n_types::C_motion &newMotion) {
    try {
        for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
            n_aux::proxy_binary_area_correct(realMotion[current_axis], newMotion[current_axis]);
        }
    }
    catch (N_inter::S_exception exc) {
        exc.show_message();
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_alignment::n_area::n_prof::correct_rectangle_area_part(N_inter::n_motion_calc::n_types::C_motion &motion, N_inter::n_motion_calc::n_types::C_motion &real_motion) {
    for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        if (motion[current_axis].size() == 0) {
            N_inter::S_exception exc;
            exc.m_calling_object = "void N_inter::n_motion_calc::n_alignment::n_area::n_prof::correct_rectangle_area_part(N_inter::n_motion_calc::n_types::C_motion &motion, N_inter::n_motion_calc::n_types::C_motion &real_motion)";
            exc.m_condition = "motion[current_axis].size() == 0";
            exc.m_decision = "Нет сегментов для площадной корректировки";
        }
        if (real_motion[current_axis].size() == 0) {
            N_inter::S_exception exc;
            exc.m_calling_object = "void N_inter::n_motion_calc::n_alignment::n_area::n_prof::correct_rectangle_area_part(N_inter::n_motion_calc::n_types::C_motion &motion, N_inter::n_motion_calc::n_types::C_motion &real_motion)";
            exc.m_condition = "real_motion[current_axis].size() == 0";
            exc.m_decision = "Нет сегментов для площадной корректировки";
        }
    }
    // WARNING размеры сегментов могут отличаться, нужно проверить
    int size = motion[0].size();

    for (int i = 0; i < size; i++) {
        // Получение максимально допустимого значения времени, которое можно убрать
        QVector<double> time_arr;
        for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
            time_arr.push_back(n_aux::rectangle_time(motion[current_axis][i], real_motion[current_axis][i]));
        }
        double time_d = N_inter::n_algebra::n_limits::min(time_arr);

        // Корректировка прямоугольной составляющей профиля скорости для осей по необходимости
        if (!N_inter::n_algebra::n_math::is_equal(time_d, 0)) {
            for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
                n_aux::correct_segment_rectangle_area(motion[current_axis][i], time_d);
            }
        }
    }
}
// --------------------------------------------------------
