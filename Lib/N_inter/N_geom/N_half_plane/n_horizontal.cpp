#include "n_horizontal.h"
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

bool N_inter::n_geom::n_half_plane::n_horizontal::is_lines_in_one_half_plane(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
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
        exc.m_calling_object = "bool N_inter::n_geom::n_lines::n_aux::is_lines_in_one_half_plane(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2)";
        exc.m_condition = "is_co_directional_lines(line1, line2)";
        exc.m_decision = "Прямые сонаправленные и не требуют нахождения биссектрисы";
        throw exc;
    }

    // Получить точку пересечения прямых
    C_point inter_point = line1.m_second_point;

    // Оставшиеся граничные точки
    C_point point1 = line1.m_first_point;
    C_point point2 = line2.m_second_point;

    // Если граничные точки прямых все выше точки пересечения, то отрезки лежат в одной полуплоскости
    if (N_inter::n_algebra::n_math::is_more_than(inter_point[COORD::Y], point1[COORD::Y])) {
        if (N_inter::n_algebra::n_math::is_more_than(inter_point[COORD::Y], point2[COORD::Y])) {
            return true;
        }
    }

    // Если граничные точки прямых все ниже точки пересечения, то отрезки лежат в одной полуплоскости
    if (!N_inter::n_algebra::n_math::is_more_than(inter_point[COORD::Y], point1[COORD::Y])) {
        if (!N_inter::n_algebra::n_math::is_more_than(inter_point[COORD::Y], point2[COORD::Y])) {
            return true;
        }
    }

    // Отрезки лежат в разных полуплоскостиях
    return false;
}
// --------------------------------------------------------

double N_inter::n_geom::n_half_plane::n_horizontal::find_lines_height(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2, bool half_plane_orientation) {
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

    // Высоты
    double h1 = abs(inter_point[COORD::Y] - point1[COORD::Y]);
    double h2 = abs(inter_point[COORD::Y] - point2[COORD::Y]);

    return N_inter::n_algebra::n_limits::min(h1, h2);
}
// --------------------------------------------------------

void N_inter::n_geom::n_half_plane::n_horizontal::short_one_half_plane_segments_to_equal_heights(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Если прямые не нужно укорачивать
    if (N_inter::n_algebra::n_math::is_equal(line1.m_first_point[COORD::Y], line2.m_second_point[COORD::Y])) {
        return;
    }

    // Если прямые не лежат в одной плоскости, то исключение
    if (!is_lines_in_one_half_plane(line1, line2)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_lines_in_one_hor_half_plane(line1, line2)";
        exc.m_decision = "Попытка сокращения для отрезков, которые не лежат в одной горизонтальной полуплоскости";
    }

    // Если прямые не образуют угол, то кидать исключение
    if (line1.m_second_point != line2.m_first_point) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "line1.m_second_point != line2.m_first_point";
        exc.m_decision = "Прямые не образуют угол";
        throw exc;
    }

    // Определение полуплоскости (верхняя или нижняя)
    bool half_plane_orientation = is_lines_in_upper_hor_half_plane(line1, line2);

    // Поиск меньшей высоты
    double h = find_lines_height(line1, line2, half_plane_orientation);

    // Укорачивание прямой с большей высотой
    C_point inter_point = line1.m_second_point;
    C_point point1 = line1.m_first_point;
    C_point point2 = line2.m_second_point;

    // Высоты прямых
    double line1_high = abs(inter_point[COORD::Y] - point1[COORD::Y]);
    double line2_high = abs(inter_point[COORD::Y] - point2[COORD::Y]);

    // Если нужно укоротить первую прямую
    if (!N_inter::n_algebra::n_math::is_equal(line1_high, h)) {
        C_m_line new_line_1;
        new_line_1.m_second_point = line1.m_second_point;

        C_point begin_point;

        // Если полуплоскость верхняя
        if (half_plane_orientation) {
            begin_point[COORD::Y] = inter_point[COORD::Y] + h;
        }
        // Если полуплоскость нижняя
        else {
            begin_point[COORD::Y] = inter_point[COORD::Y] - h;
        }

        begin_point[COORD::X] = N_inter::n_geom::n_lines::get_line_x_by_y(line1, begin_point[COORD::Y]);

        new_line_1.m_first_point = begin_point;
        line1 = new_line_1;
    }
    // Если нужно укоротить вторую прямую
    else if (!N_inter::n_algebra::n_math::is_equal(line2_high, h)) {
        C_m_line new_line_2;
        new_line_2.m_first_point = line2.m_first_point;

        C_point end_point;

        // Если полуплоскость верхняя
        if (half_plane_orientation) {
            end_point[COORD::Y] = inter_point[COORD::Y] + h;
        }
        // Если полуплоскость нижняя
        else {
            end_point[COORD::Y] = inter_point[COORD::Y] - h;
        }

        end_point[COORD::X] = N_inter::n_geom::n_lines::get_line_x_by_y(line2, end_point[COORD::Y]);

        new_line_2.m_second_point = end_point;
        line2 = new_line_2;
    }
    // Высота посчитана некорректно
    else {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "else";
        exc.m_decision = "Высота отрезков посчитана неправильно";
        qDebug() << "Высота отрезков посчитана неправильно:" << line1.m_to_string() << "и" << line2.m_to_string();
        throw exc;
    }
}
// --------------------------------------------------------

bool N_inter::n_geom::n_half_plane::n_horizontal::is_angle_bisector_vertical(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Прямые не лежит в одной горизонтальной полуплоскости, и как минимум, не имеют вертикальной биссектрисы
    if (!is_lines_in_one_half_plane(line1, line2)) {
        return false;
    }

    // Одна из прямых горизонтальная или вертикальная, поэтому о полуплоскостях в рамках этой задачи говорить нельзя
    if (N_inter::n_geom::n_lines::is_ver_or_hor_lines(line1, line2)) {
        return false;
    }

    // Укоротить по высоте одну из прямых, чтобы высоты обеих прямых были равны
    C_m_line line1_copy = line1;
    C_m_line line2_copy = line2;
    short_one_half_plane_segments_to_equal_heights(line1_copy, line2_copy);

    // Сравнить расстояния от крайних точек до центра. Если равны - биссектриса вертикальной
    C_point inter_point = line1_copy.m_second_point;
    C_point point1 = line1_copy.m_first_point;
    C_point point2 = line2_copy.m_second_point;

    QVector<double> x_arr = { inter_point[COORD::X], point1[COORD::X], point2[COORD::X] };
    std::sort(x_arr.begin(), x_arr.end());

    double l1 = abs(x_arr[1] - x_arr[0]);
    double l2 = abs(x_arr[2] - x_arr[1]);

    return N_inter::n_algebra::n_math::is_equal(l1, l2);
}
// --------------------------------------------------------

bool N_inter::n_geom::n_half_plane::n_horizontal::is_lines_in_upper_hor_half_plane(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Если прямые не лежат в одной плоскости, то исключение
    if (!is_lines_in_one_half_plane(line1, line2)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!n_aux::is_lines_in_one_hor_half_plane(line1, line2)";
        exc.m_decision = "Попытка сокращения для отрезков, которые не лежат в одной вертикалльной полуплоскости";
    }

    C_point inter_point = line1.m_second_point;

    C_point point1 = line1.m_first_point;
    C_point point2 = line2.m_second_point;

    if (N_inter::n_algebra::n_math::is_more_than(point1[COORD::Y], inter_point[COORD::Y])) {
        if (N_inter::n_algebra::n_math::is_more_than(point2[COORD::Y], inter_point[COORD::Y])) {
            return true;
        }
    }

    return false;
}
// --------------------------------------------------------
