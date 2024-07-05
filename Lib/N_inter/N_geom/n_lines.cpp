#include "n_lines.h"
#include <QVector>
#include <QDebug>
#include <cmath>
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_vector.h"
#include "N_inter/N_global_types/S_bounds.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_geom/n_bounds.h"
#include "N_inter/N_geom/n_points.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
#include "N_inter/N_geom/n_vectors.h"
#include "N_inter/N_algebra/n_limits.h"
// --------------------------------------------------------

using N_inter::n_global_types::C_m_line;
using N_inter::n_global_types::C_vector;
using N_inter::n_global_types::C_point;
using N_inter::S_exception;
using N_inter::n_global_types::COORD;
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_line_length_more_than_max_line_error(n_global_types::C_m_line &line) {
    // Если линия вырожденная, то исключение
    if (is_empty_line(line)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "is_empty_line(line)";
        throw exc;
    }

    // Если её длина больше, чем max_errors_segment_length, то истина
    double line_length = get_abs_line(line);
    double min_windth = N_inter::n_data::n_motion_vars::n_calc_vars::max_errors_segment_length * N_inter::n_data::n_motion_vars::n_calc_vars::max_position_error;
    return N_inter::n_algebra::n_math::is_more_than(line_length, min_windth);
}
// --------------------------------------------------------

double N_inter::n_geom::n_lines::get_line_y_by_x(n_global_types::C_m_line &line, double x) {
    if (is_ver_line(line)) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_geom::n_lines::get_line_y_by_x(n_global_types::C_m_line &line, double x)";
        exc.m_condition = "is_ver_line(line)";
        exc.m_decision = "Прямая вертикальная";
        throw exc;
    }

    set_line_params(line);

    if (line.B == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_geom::n_lines::get_line_y_by_x(n_global_types::C_m_line &line, double x)";
        exc.m_condition = "";
        exc.m_decision = "line.B == 0";
        throw exc;
    }

    // Ax * By + C = 0
    // x = (-By - C) / A
    // y = (-Ax - C) / B

    return (-line.A * x - line.C) / line.B;
}
// --------------------------------------------------------

double N_inter::n_geom::n_lines::get_line_x_by_y(n_global_types::C_m_line &line, double y) {
    if (is_hor_line(line)) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_geom::n_lines::get_line_x_by_y(n_global_types::C_m_line &line, double y)";
        exc.m_condition = "is_hor_line(line)";
        exc.m_decision = "Прямая горизонтальная";
        throw exc;
    }

    set_line_params(line);

    if (line.A == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_geom::n_lines::get_line_x_by_y(n_global_types::C_m_line &line, double y)";
        exc.m_condition = "line.A == 0";
        exc.m_decision = "Попытка получить значение X по координате Y для прямой с коэффициентом A = 0";
        throw exc;
    }

    // Ax * By + C = 0
    // x = (-By - C) / A
    // y = (-Ax - C) / B

    return (-line.B * y - line.C) / line.A;
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::remove_empty_lines(QVector<n_global_types::C_m_line> &lines) {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void n_geom::n_lines::remove_empty_lines(QVector<n_global_types::C_m_line> &lines)";
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Вектор линий для удаления пустой";
        throw exc;
    }

    for (int i = 0; i < lines.size(); i++) {
        if (is_empty_line(lines[i])) {
            lines.removeAt(i);
            i--;
        }
    }
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::to_necessary_zero(QVector<n_global_types::C_m_line> &lines) {
    for (int i = 0; i < lines.size(); i++) {
        N_inter::n_algebra::n_math::to_necessary_zero(lines[i].m_first_point[COORD::X]);
        N_inter::n_algebra::n_math::to_necessary_zero(lines[i].m_first_point[COORD::Y]);
        N_inter::n_algebra::n_math::to_necessary_zero(lines[i].m_second_point[COORD::X]);
        N_inter::n_algebra::n_math::to_necessary_zero(lines[i].m_second_point[COORD::Y]);
    }
}
// --------------------------------------------------------

N_inter::n_global_types::C_m_line N_inter::n_geom::n_lines::get_line(n_global_types::C_point beginPoint, double k) {
    // y - y0 = k (x - x0)
    // y - y0 = kx - kx0
    // y = kx - kx0 + y0

    // Начальная точка
    double y0 = beginPoint[n_global_types::Y];
    double x0 = beginPoint[n_global_types::X];

    // Шаг и коэффициент b
    double dx = 1;
    double b = - k * x0 + y0;

    // Конечная точка
    double x1 = x0 + dx;
    double y1 = k * x1 + b;

    // Формирование результата
    N_inter::n_global_types::C_m_line result;

    result.m_first_point[n_global_types::X] = x0;
    result.m_first_point[n_global_types::Y] = y0;

    result.m_second_point[n_global_types::X] = x1;
    result.m_second_point[n_global_types::Y] = y1;

    return result;
}
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_empty_line(n_global_types::C_m_line &line) {
    bool result = true;
    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        result = result && N_inter::n_algebra::n_math::is_equal(line.m_first_point[current_axis], line.m_second_point[current_axis]);
    }
    return result;
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::remove_repeats(QVector<n_global_types::C_m_line> &lines) {
    // Объединение прямых вида Y1 == Y2 == Y3 == Y4
    for (int i = 0; i < lines.size() - 1; i++) {
        N_inter::n_global_types::C_m_line line = lines[i], nextLine = lines[i + 1];
        // TODO слабое место для расширения количества осей
        if (N_inter::n_algebra::n_math::is_equal(line.m_first_point[n_global_types::Y], line.m_second_point[n_global_types::Y]) && N_inter::n_algebra::n_math::is_equal(line.m_second_point[n_global_types::Y], nextLine.m_first_point[n_global_types::Y]) && N_inter::n_algebra::n_math::is_equal(nextLine.m_first_point[n_global_types::Y], nextLine.m_second_point[n_global_types::Y])) {
            // qDebug() << QString("[Lines::RemoveRepeats]");
            // Lines::Print(lines[i]);
            // Lines::Print(lines[i + 1]);
            lines[i].m_second_point[n_global_types::X] = nextLine.m_second_point[n_global_types::X];
            lines.removeAt(i + 1);
            i--;
        }
    }
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::set_line_params(n_global_types::C_m_line &line) {
    // Ax + By + C = 0
    // By = -Ax - C
    // y = -A / B * x - C / B

    double x1 = line.m_first_point[n_global_types::X];
    double y1 = line.m_first_point[n_global_types::Y];

    double x2 = line.m_second_point[n_global_types::X];
    double y2 = line.m_second_point[n_global_types::Y];

    // Коэффициенты содержащей прямой A, B и C
    line.A = y1 - y2;
    line.B = x2 - x1;
    line.C = x1 * y2 - x2 * y1;

    // Границы
    N_inter::n_global_types::S_bounds bound = n_geom::n_bounds::find(line);

    // line.m_first_point[n_global_types::X] = bound.m_min_coords[n_global_types::X];
    // line.m_first_point[n_global_types::Y] = bound.m_min_coords[n_global_types::Y];

    // line.m_second_point[n_global_types::X] = bound.m_max_coords[n_global_types::X];
    // line.m_second_point[n_global_types::Y] = bound.m_max_coords[n_global_types::Y];
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::segment_offset_by_X(QVector<n_global_types::C_m_line> &segment, double dx) {
    for (int i = 0; i < segment.size(); i++) {
        segment[i].m_first_point[n_global_types::X] += dx;
        segment[i].m_second_point[n_global_types::X] += dx;
    }
}
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_ver_line(n_global_types::C_m_line &line) {
    return N_inter::n_algebra::n_math::is_equal(line.m_first_point[n_global_types::X], line.m_second_point[n_global_types::X]);
}
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_hor_line(n_global_types::C_m_line &line) {
    return N_inter::n_algebra::n_math::is_equal(line.m_first_point[n_global_types::Y], line.m_second_point[n_global_types::Y]);
}
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_oblique_line(n_global_types::C_m_line &line) {
    return (!is_hor_line(line)) && (!is_ver_line(line));
}
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_line_contain_x(n_global_types::C_m_line &line, double x) {
    double x1 = line.m_first_point[n_global_types::X], x2 = line.m_second_point[n_global_types::X];

    bool result = N_inter::n_algebra::n_math::is_more_than(x, x1) && N_inter::n_algebra::n_math::is_more_than(x2, x);
    result = result || N_inter::n_algebra::n_math::is_more_than(x, x2) && N_inter::n_algebra::n_math::is_more_than(x1, x);
    return result;
}
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_line_contain_y(n_global_types::C_m_line &line, double y) {
    double y1 = line.m_first_point[n_global_types::Y], y2 = line.m_second_point[n_global_types::Y];

    bool result = N_inter::n_algebra::n_math::is_more_or_equal(y, y1) && N_inter::n_algebra::n_math::is_more_or_equal(y2, y);
    result = result || (N_inter::n_algebra::n_math::is_more_or_equal(y, y2) && N_inter::n_algebra::n_math::is_more_or_equal(y1, y));
    return result;
}
// --------------------------------------------------------

N_inter::n_global_types::C_m_line N_inter::n_geom::n_lines::get_hor_segment_line(N_inter::n_motion_calc::n_types::C_motion_section &segment) {
    // Поиск горизонтальной линии
    for (int i = 0; i < segment.get_size(); i++) {
        if (is_hor_line(segment[i])) {
            return segment[i];
        }
    }

    // Если не найдена - вернуть точку
    N_inter::n_global_types::C_m_line line;
    line.m_first_point[n_global_types::X] = line.m_second_point[n_global_types::X] = line.m_first_point[n_global_types::Y] = line.m_second_point[n_global_types::Y] = 0;

    return line;
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::transfer_line_along_y_axis(n_global_types::C_m_line &a_line, double &a_dy, double &a_begin_x, double &a_end_x) {
    a_line.m_first_point[n_global_types::Y] += a_dy;
    a_line.m_second_point[n_global_types::Y] += a_dy;

    a_line.m_first_point[n_global_types::X] = a_begin_x;
    a_line.m_second_point[n_global_types::X] = a_end_x;
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::transfer_line_along_x_axis(n_global_types::C_m_line &a_line, double &a_dx, double &a_begin_y, double &a_end_y) {
    a_line.m_first_point[n_global_types::X] += a_dx;
    a_line.m_second_point[n_global_types::X] += a_dx;

    a_line.m_first_point[n_global_types::Y] = a_begin_y;
    a_line.m_second_point[n_global_types::Y] = a_end_y;
}
// --------------------------------------------------------

N_inter::n_global_types::C_point N_inter::n_geom::n_lines::get_intersection_point(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Определение коэффициентов содеращих отрезки line1 и line2 прямых A B и C
    double x11 = line1.m_first_point[n_global_types::X], x12 = line1.m_second_point[n_global_types::X], y11 = line1.m_first_point[n_global_types::Y], y12 = line1.m_second_point[n_global_types::Y];
    double x21 = line2.m_first_point[n_global_types::X], x22 = line2.m_second_point[n_global_types::X], y21 = line2.m_first_point[n_global_types::Y], y22 = line2.m_second_point[n_global_types::Y];
    double A1 = y11 - y12, B1 = x12 - x11, C1 = x11 * y12 - x12 * y11;
    double A2 = y21 - y22, B2 = x22 - x21, C2 = x21 * y22 - x22 * y21;

    N_inter::n_global_types::C_point result;

    // В зависимости от равенства нулю коэффициентов A и B первой прямой используются различные формулы расчёта координат общей точки
    if (A1 == 0) {
        result[n_global_types::X] = (B1 * C2 - B2 * C1) / (A1 * B2 - A2 * B1);
        result[n_global_types::Y] = (-A1 * result[n_global_types::X] - C1) / B1;
    }
    else {
        result[n_global_types::Y] = (-A1 * C2 + A2 * C1) / (A1 * B2 - A2 * B1);
        result[n_global_types::X] = (-B1 * result[n_global_types::Y] - C1) / A1;
    }

    return result;
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::set_direction_vectors(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2, n_global_types::C_vector &vec1, n_global_types::C_vector &vec2) {
    N_inter::n_global_types::C_point E = n_geom::n_points::get_lines_boundary_common_point(line1, line2);

    N_inter::n_global_types::C_point point;
    point[n_global_types::X] = line1.m_first_point[n_global_types::X];
    point[n_global_types::Y] = line1.m_first_point[n_global_types::Y];

    N_inter::n_global_types::C_point point11, point12, point21, point22;

    // Формирование граничных точек для направляющего вектора первой прямой
    if (n_geom::n_points::is_equal(point, E)) {
        point11[n_global_types::X] = line1.m_first_point[n_global_types::X];
        point11[n_global_types::Y] = line1.m_first_point[n_global_types::Y];
        point12[n_global_types::X] = line1.m_second_point[n_global_types::X];
        point12[n_global_types::Y] = line1.m_second_point[n_global_types::Y];
    }
    else {
        point11[n_global_types::X] = line1.m_second_point[n_global_types::X];
        point11[n_global_types::Y] = line1.m_second_point[n_global_types::Y];
        point12[n_global_types::X] = line1.m_first_point[n_global_types::X];
        point12[n_global_types::Y] = line1.m_first_point[n_global_types::Y];
    }

    // Формирование граничных точек для направляющего вектора второй прямой
    point[n_global_types::X] = line2.m_first_point[n_global_types::X];
    point[n_global_types::Y] = line2.m_first_point[n_global_types::Y];
    if (n_geom::n_points::is_equal(point, E)) {
        point21[n_global_types::X] = line2.m_first_point[n_global_types::X];
        point21[n_global_types::Y] = line2.m_first_point[n_global_types::Y];
        point22[n_global_types::X] = line2.m_second_point[n_global_types::X];
        point22[n_global_types::Y] = line2.m_second_point[n_global_types::Y];
    }
    else {
        point21[n_global_types::X] = line2.m_second_point[n_global_types::X];
        point21[n_global_types::Y] = line2.m_second_point[n_global_types::Y];
        point22[n_global_types::X] = line2.m_first_point[n_global_types::X];
        point22[n_global_types::Y] = line2.m_first_point[n_global_types::Y];
    }

    // Направляющий вектор для прямой line1
    vec1[n_global_types::X] = point12[n_global_types::X] - point11[n_global_types::X];
    vec1[n_global_types::Y] = point12[n_global_types::Y] - point11[n_global_types::Y];

    // Направляющий вектор для прямой line2
    vec2[n_global_types::X] = point22[n_global_types::X] - point21[n_global_types::X];
    vec2[n_global_types::Y] = point22[n_global_types::Y] - point21[n_global_types::Y];
}
// --------------------------------------------------------

double N_inter::n_geom::n_lines::get_abs_line(n_global_types::C_m_line &line) {
    // Координаты направляй-вектора прямой
    double x = line.m_first_point[n_global_types::X] - line.m_second_point[n_global_types::X];
    double y = line.m_first_point[n_global_types::Y] - line.m_second_point[n_global_types::Y];
    return sqrt(x*x + y*y);
}
// --------------------------------------------------------

double N_inter::n_geom::n_lines::get_rad_angle(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Координаты направляющих векторов для прямых line1 и line2
    double x1 = line1.m_first_point[n_global_types::X] - line1.m_second_point[n_global_types::X];
    double y1 = line1.m_first_point[n_global_types::Y] - line1.m_second_point[n_global_types::Y];

    double x2 = line2.m_first_point[n_global_types::X] - line2.m_second_point[n_global_types::X];
    double y2 = line2.m_first_point[n_global_types::Y] - line2.m_second_point[n_global_types::Y];

    // Модули линий
    double A1 = get_abs_line(line1);
    double A2 = get_abs_line(line2);

    return acos((x1*x2 + y1*y2) / (A1 * A2));
}
// --------------------------------------------------------

QVector<double> N_inter::n_geom::n_lines::to_double_vector(n_global_types::C_m_line &line) {
    QVector<double> result;

    result.push_back(line.m_first_point[n_global_types::X]);
    result.push_back(line.m_second_point[n_global_types::X]);

    result.push_back(line.m_first_point[n_global_types::Y]);
    result.push_back(line.m_second_point[n_global_types::Y]);

    return result;
}
// --------------------------------------------------------

N_inter::n_global_types::C_m_line N_inter::n_geom::n_lines::to_line(n_global_types::C_point &point1, n_global_types::C_point &point2) {
    N_inter::n_global_types::C_m_line line;

    line.m_first_point[n_global_types::X] = point1[n_global_types::X];
    line.m_first_point[n_global_types::Y] = point1[n_global_types::Y];

    line.m_second_point[n_global_types::X] = point2[n_global_types::X];
    line.m_second_point[n_global_types::Y] = point2[n_global_types::Y];

    return line;
}
// --------------------------------------------------------

N_inter::n_global_types::C_m_line N_inter::n_geom::n_lines::get_line_from_coords(double x1, double y1, double x2, double y2) {
    N_inter::n_global_types::C_m_line line;

    line.m_first_point[n_global_types::X] = x1;
    line.m_first_point[n_global_types::Y] = y1;

    line.m_second_point[n_global_types::X] = x2;
    line.m_second_point[n_global_types::Y] = y2;

    return line;
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::append_to_line_lines_from_points(QVector<n_global_types::C_m_line> &lines, QVector<n_global_types::C_point> &points) {
    // Если все точки нули, то добавить единственную прямую
    if (n_geom::n_points::is_empty_points_y(points)) {
        N_inter::n_global_types::C_m_line line;

        line.m_first_point[n_global_types::X] = points.front()[n_global_types::X];
        line.m_second_point[n_global_types::X] = points.back()[n_global_types::X];

        line.m_first_point[n_global_types::Y] = points.front()[n_global_types::Y];
        line.m_second_point[n_global_types::Y] = points.back()[n_global_types::Y];
    }
    // Если график в виде треугольника, то точки 2 и 3 равны и не образуют прямой. Сл-но её добавлять не нужно
    if (points.size() == 3) {
        lines.push_back(to_line(points[0], points[1]));
        lines.push_back(to_line(points[1], points[2]));
    }
    // График в виде трапеции
    else if (points.size() == 4) {
        lines.push_back(to_line(points[0], points[1]));
        lines.push_back(to_line(points[1], points[2]));
        lines.push_back(to_line(points[2], points[3]));
    }
    else {
        N_inter::S_exception exc;
        exc.m_calling_object = "void n_geom::n_lines::append_to_line_lines_from_points(QVector<n_global_types::C_m_line> &lines, QVector<n_global_types::C_point> &points)";
        exc.m_condition = "else";
        exc.m_decision = "Неизвестный профиль движения";
        throw exc;
    }
}
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_co_directional_lines(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Направляющие векторы прямых line1 и line2
    C_vector dir_vec_1, dir_vec_2;
    set_direction_vectors(line1, line2, dir_vec_1, dir_vec_2);

    // Модуль векторного произведения
    double mul_vec = N_inter::n_geom::n_vectors::get_vec_mul(dir_vec_1, dir_vec_2);

    // Если "0", то прямые сонаправленные
    return N_inter::n_algebra::n_math::is_equal(mul_vec, 0);
}
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_ver_or_hor_lines(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Если одна из прямых горизонтальная, то полуплоскость не определяется
    if (N_inter::n_geom::n_lines::is_hor_line(line1) || N_inter::n_geom::n_lines::is_hor_line(line2)) {
        return true;
    }
    // Если одна из прямых вертикальная, то полуплоскость не определяется
    if (N_inter::n_geom::n_lines::is_ver_line(line1) || N_inter::n_geom::n_lines::is_ver_line(line2)) {
        return true;
    }
    return false;
}
// --------------------------------------------------------

bool N_inter::n_geom::n_lines::is_segment_contain_x(n_global_types::C_m_line &line, double x) {
    double x0 = line.m_first_point[COORD::X];
    double x1 = line.m_second_point[COORD::X];

    // x0 <= x <= x1
    if (N_inter::n_algebra::n_math::is_more_or_equal(x1, x) && N_inter::n_algebra::n_math::is_more_or_equal(x, x0)) {
        return true;
    }
    // x1 <= x <= x0
    if (N_inter::n_algebra::n_math::is_more_or_equal(x0, x) && N_inter::n_algebra::n_math::is_more_or_equal(x, x1)) {
        return true;
    }

    return false;
}
// --------------------------------------------------------

double N_inter::n_geom::n_lines::get_line_definite_integral(n_global_types::C_m_line &line) {
    // Если прямая вертикальная, то вернуть 0
    if (is_ver_line(line)) {
        return 0;
    }

    // Определённый интеграл
    return get_line_definite_integral(line, line.m_first_point[COORD::X], line.m_second_point[COORD::X]);
}
// --------------------------------------------------------

double N_inter::n_geom::n_lines::get_lines_definite_integral(QVector<n_global_types::C_m_line> &lines) {
    double result = 0;
    for (int i = 0; i < lines.size(); i++) {
        result += get_line_definite_integral(lines[i]);
    }
    return result;
}
// --------------------------------------------------------

double N_inter::n_geom::n_lines::get_lines_definite_integral(n_motion_calc::n_types::C_motion_section &section) {
    return get_lines_definite_integral(section.get_lines());
}
// --------------------------------------------------------

double N_inter::n_geom::n_lines::get_line_definite_integral(n_global_types::C_m_line &line, double begin_x, double end_x) {
    // Если begin_x > end_x, то кидать исключение
    if (N_inter::n_algebra::n_math::is_more_than(begin_x, end_x)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(begin_x, end_x)";
        exc.m_decision = "Начальная точка лежит правее конечной";
        throw exc;
    }
    // Если отрезок не содержит begin_x, то кидать исключение
    if (!is_segment_contain_x(line, begin_x)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_segment_contain_x(line, begin_x)";
        exc.m_decision = "Отрезок не содержит begin_x";
        throw exc;
    }
    // Если отрезок не содержит end_x, то кидать исключение
    if (!is_segment_contain_x(line, end_x)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_segment_contain_x(line, end_x)";
        exc.m_decision = "Отрезок не содержит end_x";
        throw exc;
    }

    // Если прямая вертикальная, то вернуть 0
    if (is_ver_line(line)) {
        return 0;
    }
    // Если точки равны, то вернуть ноль
    if (N_inter::n_algebra::n_math::is_equal(begin_x, end_x)) {
        return 0;
    }

    // Координаты начала и конца отрезка
    double x0, y0, x1, y1;
    x0 = y0 = x1 = y1 = 0;

    x0 = begin_x;
    y0 = get_line_y_by_x(line, x0);

    x1 = end_x;
    y1 = get_line_y_by_x(line, x1);

    // Определённый интеграл
    // BUG Проверить, а правильно ли здесь я переписал
    double result = -(x0*x0*y0)/(2*x0-2*x1) - (x0*x0*y1)/(2*x0-2*x1) + (x0*x1*y0)/(x0-x1) + (x0*x1*y1)/(x0-x1) - (x1*x1*y0)/(2*x0-2*x1) - (x1*x1*y1)/(2*x0-2*x1);

    // if (abs(result) > 100) {
    //     int debug_stop;
    //     return -666;
    // }

    return result;
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::move(n_global_types::C_m_line &line, n_global_types::C_point &new_position) {
    // Перебор осей, перенос
    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        C_point offset = new_position - line.m_first_point;
        line.m_first_point = line.m_first_point + offset;
        line.m_second_point = line.m_second_point + offset;
    }
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::mirroring_along_axis_y(n_global_types::C_m_line &line) {
    // Отображение первой точки
    N_inter::n_geom::n_points::mirroring_along_axis_y(line.m_first_point);

    // Отображение второй точки
    N_inter::n_geom::n_points::mirroring_along_axis_y(line.m_second_point);
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::mirroring_along_axis_y(QVector<n_global_types::C_m_line> &lines) {
    for (int i = 0; i < lines.size(); i++) {
        N_inter::n_geom::n_lines::mirroring_along_axis_y(lines[i]);
    }
}
// --------------------------------------------------------

void N_inter::n_geom::n_lines::section_offset_x(n_global_types::C_m_line &line, double new_x_position) {
    double offset_x = line.m_first_point[COORD::X] - new_x_position;
    line.m_first_point[COORD::X]  = line.m_first_point[COORD::X]  - offset_x;
    line.m_second_point[COORD::X] = line.m_second_point[COORD::X] - offset_x;
}
// --------------------------------------------------------
