#include "n_vertical.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_algebra/n_limits.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include <QDebug>
// --------------------------------------------------------

using N_inter::S_exception;
using N_inter::n_global_types::C_point;
using N_inter::n_global_types::C_m_line;
using N_inter::n_global_types::COORD;
// --------------------------------------------------------

bool N_inter::n_geom::n_half_plane::n_vertical::is_lines_in_one_half_plane(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Если прямые не образуют угол (нет общих точек), то исключение
    if (!N_inter::n_algebra::n_math::is_equal(line1.m_second_point, line2.m_first_point)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!N_inter::n_algebra::n_math::is_equal(line1.m_second_point, line2.m_first_point)";
        exc.m_decision = "Отрезки не имеют общей точки и не образуют угол";
        throw exc;
    }

    // Если прямые сонаправленные, то исключение
    if (N_inter::n_geom::n_lines::is_co_directional_lines(line1, line2)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "is_co_directional_lines(line1, line2)";
        exc.m_decision = "Прямые сонаправленные и не требуют нахождения биссектрисы";
        throw exc;
    }

    // Получить точку пересечения прямых
    C_point inter_point = line1.m_second_point;

    // Оставшиеся граничные точки
    C_point point1 = line1.m_first_point;
    C_point point2 = line2.m_second_point;

    // Если граничные точки прямых все левее точки пересечения, то отрезки лежат в одной полуплоскости
    if (N_inter::n_algebra::n_math::is_more_than(inter_point[COORD::X], point1[COORD::X])) {
        if (N_inter::n_algebra::n_math::is_more_than(inter_point[COORD::X], point2[COORD::X])) {
            return true;
        }
    }

    // Если граничные точки прямых все правее точки пересечения, то отрезки лежат в одной полуплоскости
    if (!N_inter::n_algebra::n_math::is_more_than(inter_point[COORD::X], point1[COORD::X])) {
        if (!N_inter::n_algebra::n_math::is_more_than(inter_point[COORD::X], point2[COORD::X])) {
            return true;
        }
    }

    // Отрезки лежат в разных полуплоскостиях
    return false;
}
// --------------------------------------------------------

double N_inter::n_geom::n_half_plane::n_vertical::find_lines_width(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2, bool half_plane_orientation) {
    // Если прямые не образуют угол, то кидать исключение
    if (line1.m_second_point != line2.m_first_point) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "line1.m_second_point != line2.m_first_point";
        exc.m_decision = "Прямые не образуют отрезок";
        throw exc;
    }

    // Граничные точки
    C_point inter_point = line1.m_second_point;
    C_point point1 = line1.m_first_point;
    C_point point2 = line2.m_second_point;

    // Длины
    double l1 = abs(inter_point[COORD::X] - point1[COORD::X]);
    double l2 = abs(inter_point[COORD::X] - point2[COORD::X]);

    return N_inter::n_algebra::n_limits::min(l1, l2);
}
// --------------------------------------------------------

void N_inter::n_geom::n_half_plane::n_vertical::short_one_half_plane_segments_to_equal_widths(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Если прямые не нужно укорачивать
    if (N_inter::n_algebra::n_math::is_equal(line1.m_first_point[COORD::X], line2.m_second_point[COORD::X])) {
        return;
    }

    // Если прямые не лежат в одной плоскости, то исключение
    if (!is_lines_in_one_half_plane(line1, line2)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_lines_in_one_ver_half_plane(line1, line2)";
        exc.m_decision = "Попытка сокращения для отрезков, которые не лежат в одной горизонтальной полуплоскости";
    }

    // Определение полуплоскости (правая или левая)
    bool half_plane_orientation = is_lines_in_right_ver_half_plane(line1, line2);

    // Поиск меньшей длины
    double length = find_lines_width(line1, line2, half_plane_orientation);

    // Если прямые не образуют угол, то кидать исключение
    if (line1.m_second_point != line2.m_first_point) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "line1.m_second_point != line2.m_first_point";
        exc.m_decision = "Прямые не образуют угол";
        throw exc;
    }

    // Укорачивание прямой с большей длиной
    C_point inter_point = line1.m_second_point;
    C_point point1 = line1.m_first_point;
    C_point point2 = line2.m_second_point;

    // Высоты прямых
    double line1_length = abs(inter_point[COORD::X] - point1[COORD::X]);
    double line2_length = abs(inter_point[COORD::X] - point2[COORD::X]);

    // Если нужно укоротить первую прямую
    if (!N_inter::n_algebra::n_math::is_equal(line1_length, length)) {
        C_m_line new_line_1;
        new_line_1.m_second_point = line1.m_second_point;

        C_point begin_point;

        // Если полуплоскость правая
        if (half_plane_orientation) {
            begin_point[COORD::X] = inter_point[COORD::X] + length;
        }
        // Если полуплоскость верхняя
        else {
            begin_point[COORD::X] = inter_point[COORD::X] - length;
        }
        begin_point[COORD::Y] = N_inter::n_geom::n_lines::get_line_y_by_x(line1, begin_point[COORD::X]);

        new_line_1.m_first_point = begin_point;
        line1 = new_line_1;
    }
    // Если нужно укоротить вторую прямую
    else if (!N_inter::n_algebra::n_math::is_equal(line2_length, length)) {
        C_m_line new_line_2;
        new_line_2.m_first_point = line2.m_first_point;

        C_point end_point;

        // Если полуплоскость правая
        if (half_plane_orientation) {
            end_point[COORD::X] = inter_point[COORD::X] + length;
        }
        // Если полуплоскость верхняя
        else {
            end_point[COORD::X] = inter_point[COORD::X] - length;
        }
        end_point[COORD::Y] = N_inter::n_geom::n_lines::get_line_y_by_x(line2, end_point[COORD::X]);

        new_line_2.m_second_point = end_point;
        line2 = new_line_2;
    }
    // Длина посчитана некорректно
    else {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "else";
        exc.m_decision = "Длина отрезков посчитана неправильно";
        qDebug() << "Длина отрезков посчитана неправильно:" << line1.m_to_string() << "и" << line2.m_to_string();
        throw exc;
    }
}
// --------------------------------------------------------

bool N_inter::n_geom::n_half_plane::n_vertical::is_angle_bisector_horizontal(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Прямые не лежит в одной вертикальной полуплоскости, и как минимум, не имеют горизонтальной биссектрисы
    if (!is_lines_in_one_half_plane(line1, line2)) {
        return false;
    }

    // Одна из прямых горизонтальная или вертикальная, поэтому о полуплоскостях в рамках этой задачи говорить нельзя
    if (N_inter::n_geom::n_lines::is_ver_or_hor_lines(line1, line2)) {
        return false;
    }

    // Укоротить по длине одну из прямых, чтобы высоты обеих прямых были равны
    C_m_line line1_copy = line1;
    C_m_line line2_copy = line2;
    short_one_half_plane_segments_to_equal_widths(line1_copy, line2_copy);

    // Сравнить расстояния от крайних точек до центра. Если равны - биссектриса вертикальная
    C_point inter_point = line1_copy.m_second_point;
    C_point point1 = line1_copy.m_first_point;
    C_point point2 = line2_copy.m_second_point;

    QVector<double> y_arr = { inter_point[COORD::Y], point1[COORD::Y], point2[COORD::Y] };
    std::sort(y_arr.begin(), y_arr.end());

    double l1 = abs(y_arr[1] - y_arr[0]);
    double l2 = abs(y_arr[2] - y_arr[1]);

    return N_inter::n_algebra::n_math::is_equal(l1, l2);
}
// --------------------------------------------------------

bool N_inter::n_geom::n_half_plane::n_vertical::is_lines_in_right_ver_half_plane(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Если прямые не лежат в одной плоскости, то исключение
    if (!is_lines_in_one_half_plane(line1, line2)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!n_aux::is_lines_in_one_ver_half_plane(line1, line2)";
        exc.m_decision = "Попытка сокращения для отрезков, которые не лежат в одной вертикалльной полуплоскости";
    }

    C_point inter_point = line1.m_second_point;

    C_point point1 = line1.m_first_point;
    C_point point2 = line2.m_second_point;

    if (N_inter::n_algebra::n_math::is_more_than(point1[COORD::X], inter_point[COORD::X])) {
        if (N_inter::n_algebra::n_math::is_more_than(point2[COORD::X], inter_point[COORD::X])) {
            return true;
        }
    }

    return false;
}
// --------------------------------------------------------
