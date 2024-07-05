#include "n_point_elevation.h"
#include <QDebug>
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_algebra/n_limits.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"

#include "N_inter/N_geom/n_lines.h"
#include "N_inter/S_exception.h"
// --------------------------------------------------------

void N_inter::n_motion_calc::n_point_elevation::n_aux::sign_segment_points_elevation(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments) {
    if (segments.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KPointElevation::_sign_segment_points_elevation(QVector<n_motion_calc::n_types::C_motion_section>& segments)";
        exc.m_condition = "segments.size() == 0";
        exc.m_decision = "Массив сегментов пустой";
        throw exc;
    }

    int begin = 0, end = begin;
    N_inter::n_motion_calc::n_motion_sections::K_SIGN sign = N_inter::n_motion_calc::n_motion_sections::sign(segments[0]);
    while (end != segments.size() - 1) {
        // Если знак сегмента с индексом end не равен sign, то вызвать _sign_segment_points_elevation с границами и обновить begin/end
        if (N_inter::n_motion_calc::n_motion_sections::sign(segments[end]) != sign) {
            n_aux::master_sign_segment_points_elevation(segments, begin, end - 1);

            // Если корректируемый сегмент состоял из единственного отрезка, то обновить правую границу
            if (begin == end) {
                end = end + 1;
            }

            begin = end;
            if (end + 1 != segments.size()) {
                sign = N_inter::n_motion_calc::n_motion_sections::sign(segments[end + 1]);
            }
        }
        else {
            end++;
        }
    }
    // Если крайний справа сегмент сонаправлен с начальным
    if (N_inter::n_motion_calc::n_motion_sections::sign(segments[begin]) != N_inter::n_motion_calc::n_motion_sections::sign(segments[end])) {
        // Если сегментов для возвышения точек два и больше
        if (begin < end - 1) {
            n_aux::master_sign_segment_points_elevation(segments, begin, end - 1);
        }
    }
    else {
        n_aux::master_sign_segment_points_elevation(segments, begin, end);
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_point_elevation::n_aux::master_sign_segment_points_elevation(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end) {
    if (segments.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KPointElevation::_master_sign_segment_points_elevation(QVector<n_motion_calc::n_types::C_motion_section>& segments, const int& begin, const int& end)";
        exc.m_condition = "segments.size() == 0";
        exc.m_decision = "Сегмент не содержит отрезков";
        throw exc;
    }
    // begin == end -> begin == end + 1
    else if (begin == end + 1) {
        return;
    }
    else if (begin > end) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KPointElevation::_master_sign_segment_points_elevation(QVector<n_motion_calc::n_types::C_motion_section>& segments, const int& begin, const int& end)";
        exc.m_condition = "begin > end";
        exc.m_decision = "Индекс начального сегмента превышает индекс конечного сегмента";
        throw exc;
    }
    else if ((begin >= segments.size()) || (end >= segments.size())) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KPointElevation::_master_sign_segment_points_elevation(QVector<n_motion_calc::n_types::C_motion_section>& segments, const int& begin, const int& end)";
        exc.m_condition = "(begin >= segments.size()) || (end >= segments.size())";
        exc.m_decision = "Выход за границы segments";
        throw exc;
    }
    else if (N_inter::n_algebra::n_math::is_equal(N_inter::n_algebra::n_limits::max_y(segments, begin, end), 0) && N_inter::n_algebra::n_math::is_equal(N_inter::n_algebra::n_limits::min_y(segments, begin, end), 0)) {
        return;
    }

    bool mirrored_flag = false;
    // Если движение на участке идёт в обратную сторону
    if (N_inter::n_algebra::n_math::is_more_than(0, N_inter::n_algebra::n_limits::min_y(segments, begin, end))) {
        mirrored_flag = true;
        N_inter::n_motion_calc::n_motion_sections::segmentMirroredByY(segments, begin, end);
    }

    sign_segment_points_elevation(segments, begin, end);

    // Если движение было направлено в обратную сторону, то отобразить сегмент
    if (mirrored_flag) {
        N_inter::n_motion_calc::n_motion_sections::segmentMirroredByY(segments, begin, end);
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_point_elevation::n_aux::sign_segment_points_elevation(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end) {
    if (N_inter::n_algebra::n_math::is_more_than(0, N_inter::n_algebra::n_limits::min_y(segments[begin]))) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KPointElevation::_sign_segment_points_elevation(QVector<n_motion_calc::n_types::C_motion_section>& segments, const int& begin, const int& end)";
        exc.m_condition = "n_algebra::n_math::is_more_than(0, n_algebra::n_limits::min_y(segments[begin]))";
        exc.m_decision = "Профиль скорости отрицательный";
        throw exc;
    }

    for (int i = begin; i < end; i++) {
        double current_segment_vel = N_inter::n_algebra::n_limits::max_y(segments[i].get_lines());     // Получить максимальное значение для этого сегмента
        double next_segment_vel    = N_inter::n_algebra::n_limits::max_y(segments[i + 1].get_lines()); // Получить максимальное значение для следующего сегмента

        double elevation_velocity = N_inter::n_algebra::n_limits::min(current_segment_vel, next_segment_vel); // Взять минимум

        qDebug() << "elevation_velocity" << elevation_velocity;

        // Если есть остановка движения, то ничего не делать
        if (elevation_velocity == 0) {
            return;
        }

        // Если current_segment_vel == next_segment_vel
        if (N_inter::n_algebra::n_math::is_equal(current_segment_vel, next_segment_vel)) {
            double deg = N_inter::n_data::n_motion_vars::n_calc_vars::elevation_velocity;

            qDebug() << "elevation_velocity / deg" << elevation_velocity / deg;

            segment_point_elevation(segments[i],     n_aux::KElevation::End,   elevation_velocity / deg); // Возвышение конечной точки
            segment_point_elevation(segments[i + 1], n_aux::KElevation::Begin, elevation_velocity / deg); // Возвышение начальной точки
            continue;
        }
        segment_point_elevation(segments[i],     n_aux::KElevation::End,   elevation_velocity); // Возвышение конечной точки
        segment_point_elevation(segments[i + 1], n_aux::KElevation::Begin, elevation_velocity); // Возвышение начальной точки
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_point_elevation::n_aux::segment_point_elevation(N_inter::n_motion_calc::n_types::C_motion_section &segment, KElevation a_begin_flag, double a_velocity) {
    if (a_begin_flag == n_aux::KElevation::Begin) {
        segment_begin_point_elevation(segment, a_velocity);
    }
    else {
        segment_end_point_elevation(segment, a_velocity);
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_point_elevation::n_aux::segment_begin_point_elevation(N_inter::n_motion_calc::n_types::C_motion_section &segment, double a_velocity) {
    // Максимальная скорость на участке
    double segment_vel = N_inter::n_algebra::n_limits::max_y(segment);

    // Если скорость возвышения равна максимальной скорости на участке, то ординату точки возвышения сделать равной segment_vel
    if (N_inter::n_algebra::n_math::is_equal(segment_vel, a_velocity)) {
        // Если участок - треугольник, то поднять левую сторону
        // [Отлажен]
        if (segment.get_size() == 2) {
            segment.get_begin_line().m_first_point[n_global_types::Y] = a_velocity;
        }
        // Если участок - трапеция, то поднять левую сторону и объединить её с основанием
        // [Отлажен]
        else if (segment.get_size() == 3) {
            segment[1].m_first_point[n_global_types::X] = segment[0].m_first_point[n_global_types::X];
            segment[1].m_second_point[n_global_types::X] = segment[1].m_second_point[n_global_types::X];

            segment[1].m_first_point[n_global_types::Y] = segment[1].m_first_point[n_global_types::Y];
            segment[1].m_second_point[n_global_types::Y] = segment[1].m_first_point[n_global_types::Y];

            segment.remove_at(0);
        }
        else {
            N_inter::S_exception exc;
            exc.m_calling_object = "void KPointElevation::_segment_begin_point_elevation(n_motion_calc::n_types::C_motion_section& segment, double a_velocity)";
            exc.m_condition = "else";
            exc.m_decision = "Неизвестный профиль движения";
            throw exc;
        }
    }
    // Если скорость возвышения меньше максимальной скорости на участке, то ординату сделать равной segment_vel
    else {
        // Если участок - треугольник, то обновить левую сторону и добавить основание
        // [Отлажен]
        if (segment.get_size() == 2) {
            // Начальные границы
            double begin_x = segment[0].m_first_point[n_global_types::X], end_x = segment[0].m_second_point[n_global_types::X];

            // Возвышение левой линии вверх
            n_geom::n_lines::transfer_line_along_y_axis(segment[0], a_velocity, begin_x, end_x);

            // Обновление правой границы левой линии
            end_x = n_geom::n_lines::get_line_x_by_y(segment[0], segment[1].m_first_point[n_global_types::Y]);
            segment[0].m_second_point[n_global_types::X] = end_x;
            segment[0].m_second_point[n_global_types::Y] = segment[1].m_first_point[n_global_types::Y];

            // Добавление основания для трапеции
            N_inter::n_global_types::C_m_line new_line;
            new_line.m_first_point[n_global_types::X] = segment[0].m_second_point[n_global_types::X];
            new_line.m_first_point[n_global_types::Y] = segment[0].m_second_point[n_global_types::Y];
            new_line.m_second_point[n_global_types::X] = segment[1].m_first_point[n_global_types::X];
            new_line.m_second_point[n_global_types::Y] = segment[1].m_first_point[n_global_types::Y];
            segment.insert_at(1, new_line);
            // TODO Поменять местами new_line и 1
        }
        // Если участок - трапеция, то обновить левую сторону и основание
        // [Отлажен]
        else if (segment.get_size() == 3) {
            // Начальные границы
            double begin_x = segment[0].m_first_point[n_global_types::X], end_x = segment[0].m_second_point[n_global_types::X];

            // Возвышение левой линии вверх
            n_geom::n_lines::transfer_line_along_y_axis(segment[0], a_velocity, begin_x, end_x);

            // Обновление правой границы левой линии
            end_x = n_geom::n_lines::get_line_x_by_y(segment[0], segment[1].m_first_point[n_global_types::Y]);
            segment[0].m_second_point[n_global_types::X] = end_x;
            segment[0].m_second_point[n_global_types::Y] = segment[1].m_first_point[n_global_types::Y];

            // Удлинение основания
            segment[1].m_first_point[n_global_types::X] = segment[0].m_second_point[n_global_types::X];
        }
        else {
            N_inter::S_exception exc;
            exc.m_calling_object = "void KPointElevation::_segment_begin_point_elevation(n_motion_calc::n_types::C_motion_section& segment, double a_velocity)";
            exc.m_condition = "else";
            exc.m_decision = "Неизвестный профиль движения";
            throw exc;
        }
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_point_elevation::n_aux::segment_end_point_elevation(N_inter::n_motion_calc::n_types::C_motion_section &segment, double a_velocity) {
    // Максимальная скорость на участке
    double segment_vel = N_inter::n_algebra::n_limits::max_y(segment);

    // Если скорость возвышения равна скорости на участке, то ординату точки возвышения сделать равной segment_vel
    if (N_inter::n_algebra::n_math::is_equal(segment_vel, a_velocity)) {
        // Если участок состоит из двух отрезков
        // [Отлажен]
        if (segment.get_size() == 2) {
            segment.get_end_line().m_second_point[n_global_types::Y] = a_velocity;
            // Слияние линий по необходимости
            if (N_inter::n_algebra::n_math::is_equal(segment[0].m_first_point[n_global_types::Y], segment[0].m_second_point[n_global_types::Y])) {
                segment[0].m_second_point[n_global_types::X] = segment[1].m_second_point[n_global_types::X];
                segment[0].m_second_point[n_global_types::Y] = segment[1].m_second_point[n_global_types::Y];
                segment.remove_at(1);
            }
        }
        // Если участок состоит из трёх линий
        // [Отлажен]
        else if (segment.get_size() == 3) {
            segment[1].m_first_point[n_global_types::X] = segment[1].m_first_point[n_global_types::X];
            segment[1].m_second_point[n_global_types::X] = segment[2].m_second_point[n_global_types::X];

            segment[1].m_first_point[n_global_types::Y] = segment[1].m_first_point[n_global_types::Y];
            segment[1].m_second_point[n_global_types::Y] = segment[1].m_first_point[n_global_types::Y];

            segment.remove_at(2);
        }
        else {
            N_inter::S_exception exc;
            exc.m_calling_object = "void KPointElevation::_segment_end_point_elevation(n_motion_calc::n_types::C_motion_section& segment, double a_velocity)";
            exc.m_condition = "else";
            exc.m_decision = "Неизвестный профиль движения";
            throw exc;
        }
    }
    else {
        // Если участок состоит из двух отрезков
        // [Отлажен]
        if (segment.get_size() == 2) {
            // Начальные границы
            double begin_x = segment[1].m_first_point[n_global_types::X], end_x = segment[1].m_second_point[n_global_types::X];

            // Возвышение правой линии
            n_geom::n_lines::transfer_line_along_y_axis(segment[1], a_velocity, begin_x, end_x);

            // Корректировка левой границы правой линии
            begin_x = n_geom::n_lines::get_line_x_by_y(segment[1], segment[0].m_second_point[n_global_types::Y]);
            segment[1].m_first_point[n_global_types::X] = begin_x;
            segment[1].m_first_point[n_global_types::Y] = segment[0].m_second_point[n_global_types::Y];

            // Удлинение условного основания
            segment[0].m_second_point[n_global_types::X] = segment[1].m_first_point[n_global_types::X];
        }
        // Если участок состоит из трёх отрезков
        // [Отлажен]
        else if (segment.get_size() == 3) {
            // Начальные границы
            double begin_x = segment[2].m_first_point[n_global_types::X], end_x = segment[2].m_second_point[n_global_types::X];

            // Перенос правой линии вверх
            n_geom::n_lines::transfer_line_along_y_axis(segment[2], a_velocity, begin_x, end_x);

            // Обновление границ правой линии для этого сегмента
            begin_x = n_geom::n_lines::get_line_x_by_y(segment[2], segment[1].m_first_point[n_global_types::Y]);
            segment[2].m_first_point[n_global_types::X] = begin_x;
            segment[2].m_first_point[n_global_types::Y] = segment[1].m_first_point[n_global_types::Y];

            // Удлинение основания
            segment[1].m_second_point[n_global_types::X] = segment[2].m_first_point[n_global_types::X];
        }
        else {
            N_inter::S_exception exc;
            exc.m_calling_object = "void KPointElevation::_segment_end_point_elevation(n_motion_calc::n_types::C_motion_section& segment, double a_velocity)";
            exc.m_condition = "else";
            exc.m_decision = "Неизвестный профиль движения";
            throw exc;
        }
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_point_elevation::elevationOfReferencePoints(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments) {
    if (segments.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void KPointElevation::elevationOfReferencePoints(QVector<n_motion_calc::n_types::C_motion_section>& segments)";
        exc.m_condition = "segments.size() == 0";
        exc.m_decision = "Сегмент не содержит отрезков";
        throw exc;
    }
    for (int i = 0; i < segments.size() - 1; i++) {
        double current_segment_vel = N_inter::n_algebra::n_limits::max_y(segments[i].get_lines());     // Получить максимальное значение для этого сегмента
        double next_segment_vel    = N_inter::n_algebra::n_limits::max_y(segments[i + 1].get_lines()); // Получить максимальное значение для следующего сегмента

        double elevation_velocity = N_inter::n_algebra::n_limits::min(current_segment_vel, next_segment_vel); // Взять минимум

        // Если есть остановка движения, то ничего не делать
        if (elevation_velocity == 0) {
            return;
        }

        // Если current_segment_vel == next_segment_vel
        if (N_inter::n_algebra::n_math::is_equal(current_segment_vel, next_segment_vel)) {
            n_aux::segment_point_elevation(segments[i],     n_aux::KElevation::End,   elevation_velocity / 2); // Возвышение конечной точки
            n_aux::segment_point_elevation(segments[i + 1], n_aux::KElevation::Begin, elevation_velocity / 2); // Возвышение начальной точки
            continue;
        }
        n_aux::segment_point_elevation(segments[i],     n_aux::KElevation::End,   elevation_velocity); // Возвышение конечной точки
        n_aux::segment_point_elevation(segments[i + 1], n_aux::KElevation::Begin, elevation_velocity); // Возвышение начальной точки
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_point_elevation::elevationOfReferencePoints(N_inter::n_motion_calc::n_types::C_motion &motion) {
    for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        n_aux::sign_segment_points_elevation(motion[current_axis]);
    }
}
// --------------------------------------------------------
