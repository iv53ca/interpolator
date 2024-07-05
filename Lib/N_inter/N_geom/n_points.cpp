#include "n_points.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_vector.h"
#include "N_inter/N_global_types/S_bounds.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_geom/n_bounds.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_geom/n_vectors.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_algebra/n_limits.h"
#include <cmath>
// --------------------------------------------------------

using N_inter::n_global_types::COORD;
using N_inter::n_global_types::C_point;
// --------------------------------------------------------

N_inter::n_global_types::C_point N_inter::n_geom::n_points::get_lines_boundary_common_point(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2, bool &stat) {
    // Условное начало прямой line1
    N_inter::n_global_types::C_point point11;
    point11[n_global_types::X] = line1.m_first_point[n_global_types::X];
    point11[n_global_types::Y] = line1.m_first_point[n_global_types::Y];

    // Условный конец прямой line1
    N_inter::n_global_types::C_point point12;
    point12[n_global_types::X] = line1.m_second_point[n_global_types::X];
    point12[n_global_types::Y] = line1.m_second_point[n_global_types::Y];

    // Условное начало прямой line2
    N_inter::n_global_types::C_point point21;
    point21[n_global_types::X] = line2.m_first_point[n_global_types::X];
    point21[n_global_types::Y] = line2.m_first_point[n_global_types::Y];

    // Условный конец прямой line2
    N_inter::n_global_types::C_point point22;
    point22[n_global_types::X] = line2.m_second_point[n_global_types::X];
    point22[n_global_types::Y] = line2.m_second_point[n_global_types::Y];

    // Проверка точки point11 на искомую
    if (is_equal(point11, point21) || is_equal(point11, point22)) {
        stat = true;
        return point11;
    }
    // Проверка точки point12 на искомую
    else if (is_equal(point12, point21) || is_equal(point12, point22)) {
        stat = true;
        return point12;
    }
    stat = false;
    return point11;
}
// --------------------------------------------------------

N_inter::n_global_types::C_point N_inter::n_geom::n_points::get_lines_boundary_common_point(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    bool stat = false;
    return get_lines_boundary_common_point(line1, line2, stat);
}
// --------------------------------------------------------

void N_inter::n_geom::n_points::to_necessary_zero(QVector<n_global_types::C_point> &points) {
    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; j++) {
            N_inter::n_algebra::n_math::to_necessary_zero(points[i][j]);
        }
    }
}
// --------------------------------------------------------

bool N_inter::n_geom::n_points::is_equal(n_global_types::C_point &point1, n_global_types::C_point &point2) {
    bool res1 = abs(point1[n_global_types::X] - point2[n_global_types::X]) <= N_inter::n_data::n_motion_vars::n_calc_vars::calculation_error;
    bool res2 = abs(point1[n_global_types::Y] - point2[n_global_types::Y]) <= N_inter::n_data::n_motion_vars::n_calc_vars::calculation_error;
    return res1 && res2;
}
// --------------------------------------------------------

bool N_inter::n_geom::n_points::is_in_angle(n_global_types::C_point &point, n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Общая граничная точка для прямых
    N_inter::n_global_types::C_point E = get_lines_boundary_common_point(line1, line2);

    // Направляющие векторы прямых line1 и line2
    N_inter::n_global_types::C_vector lineVec1, lineVec2;
    lineVec1[n_global_types::X] = line1.m_first_point[n_global_types::X] - line1.m_second_point[n_global_types::X];
    lineVec1[n_global_types::Y] = line1.m_first_point[n_global_types::Y] - line1.m_second_point[n_global_types::Y];
    lineVec2[n_global_types::X] = line2.m_second_point[n_global_types::X] - line2.m_first_point[n_global_types::X];
    lineVec2[n_global_types::Y] = line2.m_second_point[n_global_types::Y] - line2.m_first_point[n_global_types::Y];

    // Вектор для точки
    N_inter::n_global_types::C_vector pointVector;
    pointVector[n_global_types::X] = point[n_global_types::X] - E[n_global_types::X];
    pointVector[n_global_types::Y] = point[n_global_types::Y] - E[n_global_types::Y];

    return n_geom::n_vectors::is_in_angle(lineVec1, lineVec2, pointVector);
}
// --------------------------------------------------------

bool N_inter::n_geom::n_points::is_in_line(n_global_types::C_m_line &line, n_global_types::C_point &point) {
    double x0 = point[n_global_types::X], y0 = point[n_global_types::Y];
    double A = line.A, B = line.B, C = line.C;

    return (abs(A*x0 + B*y0 + C) <= N_inter::n_data::n_motion_vars::n_calc_vars::calculation_error) && (is_in_boundary_line(point, line));
}
// --------------------------------------------------------

bool N_inter::n_geom::n_points::is_in_boundary_line(n_global_types::C_point &point, n_global_types::C_m_line &line) {
    // Нахождение границ и проверка точки на принадлежность этому отрезку
    N_inter::n_global_types::S_bounds bound = n_geom::n_bounds::find(line);
    return ((bound.m_min_coords[n_global_types::X] <= point[n_global_types::X]) && (point[n_global_types::X] <= bound.m_max_coords[n_global_types::X])) &&
           ((bound.m_min_coords[n_global_types::Y] <= point[n_global_types::Y]) && (point[n_global_types::Y] <= bound.m_max_coords[n_global_types::Y]));
}
// --------------------------------------------------------

N_inter::n_global_types::C_point N_inter::n_geom::n_points::get_project_onto_line(n_global_types::C_m_line &line, n_global_types::C_point &point) {
    N_inter::n_global_types::C_point result;

    // Если прямая вертикальная, то координаты искомой точки следующие: (line.m_first_point[n_geom::X], point.Y)
    if (n_geom::n_lines::is_ver_line(line)) {
        result[n_global_types::X] = line.m_first_point[n_global_types::X];
        result[n_global_types::Y] = point[n_global_types::Y];
    }
    // Если прямая горизонтальная, то координаты искомой точки следующие: (point[n_geom::X], line.m_first_point[n_geom::Y])
    else if (n_geom::n_lines::is_hor_line(line)) {
        result[n_global_types::X] = point[n_global_types::X];
        result[n_global_types::Y] = line.m_first_point[n_global_types::Y];
    }
    // Если прямая мод углом, то уоординаты точки находятся как точка пересечения двух прямых: line и с прямой с  направляющим вектором (-B, A),
    // проходящей через точку point
    else {
        // Направляющий вектор перпендикулярной прямой к прямой line
        N_inter::n_global_types::C_vector p;
        p[n_global_types::X] = line.A;
        p[n_global_types::Y] = line.B;

        // Формирование точек для перпендикулярной прямой
        N_inter::n_global_types::C_point point1 = point;
        N_inter::n_global_types::C_point point2;
        point2[n_global_types::X] = point1[n_global_types::X] + p[n_global_types::X];
        point2[n_global_types::Y] = point1[n_global_types::Y] + p[n_global_types::Y];

        // Перпендикулярная прямая
        N_inter::n_global_types::C_m_line line2;
        line2.m_first_point[n_global_types::X] = point1[n_global_types::X];
        line2.m_first_point[n_global_types::Y] = point1[n_global_types::Y];
        line2.m_second_point[n_global_types::X] = point2[n_global_types::X];
        line2.m_second_point[n_global_types::Y] = point2[n_global_types::Y];

        result = n_geom::n_lines::get_intersection_point(line, line2);
    }

    return result;
}
// --------------------------------------------------------

bool N_inter::n_geom::n_points::is_empty_points_x(QVector<n_global_types::C_point> &points) {
    for (int i = 0; i < points.size(); i++) {
        if (!N_inter::n_algebra::n_math::is_equal(points[i][n_global_types::X], 0)) {
            return false;
        }
    }
    return true;
}
// --------------------------------------------------------

bool N_inter::n_geom::n_points::is_empty_points_y(QVector<n_global_types::C_point> &points) {
    for (int i = 0; i < points.size(); i++) {
        if (!N_inter::n_algebra::n_math::is_equal(points[i][n_global_types::Y], 0)) {
            return false;
        }
    }
    return true;
}
// --------------------------------------------------------

QString N_inter::n_geom::n_points::to_string(QVector<n_global_types::C_point> &points) {
    if (points.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QString n_geom::n_points::to_string(QVector<n_global_types::C_point> &points)";
        exc.m_condition = "points.size() == 0";
        exc.m_decision = "Нет точек для строкового представления";
        throw exc;
    }

    QString points_x = "[Points] [X]", points_y = "[Points] [Y]";

    // абсциссы и ординаты
    for (int i = 0; i < points.size(); i++) {
        points_x += QString(" %1").arg(points[i][n_global_types::X]);
        points_y += QString(" %1").arg(points[i][n_global_types::Y]);
    }

    return points_x + "\n" + points_y;
}
// --------------------------------------------------------

QString N_inter::n_geom::n_points::to_string_x(QVector<n_global_types::C_point> &points) {
    if (points.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QString n_geom::n_points::to_string_x(QVector<n_global_types::C_point> &points)";
        exc.m_condition = "points.size() == 0";
        exc.m_decision = "Нет точек для строкового представления";
        throw exc;
    }

    QString points_x = "[Points] [X]";

    // абсциссы и ординаты
    for (int i = 0; i < points.size(); i++) {
        points_x += QString(" %1").arg(points[i][n_global_types::X]);
    }

    return points_x;
}
// --------------------------------------------------------

QString N_inter::n_geom::n_points::to_string_y(QVector<n_global_types::C_point> &points) {
    if (points.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QString n_geom::n_points::to_string_y(QVector<n_global_types::C_point> &points)";
        exc.m_condition = "points.size() == 0";
        exc.m_decision = "Нет точек для строкового представления";
        throw exc;
    }

    QString points_y = "[Points] [Y]";

    // абсциссы и ординаты
    for (int i = 0; i < points.size(); i++) {
        points_y += QString(" %1").arg(points[i][n_global_types::Y]);
    }

    return points_y;
}
// --------------------------------------------------------

void N_inter::n_geom::n_points::move(n_global_types::C_point &point, n_global_types::C_point &new_position) {
    // Перебор осей, смещение точки
    // C_point offset = new_position - point;
    // for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
    //     point[i] = point[i] + offset[i];
    // }
    point = new_position;
}
// --------------------------------------------------------

void N_inter::n_geom::n_points::mirroring_along_axis_y(n_global_types::C_point &point) {
    point[COORD::X] = -point[COORD::X];
}
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_point> N_inter::n_geom::n_points::correct_area_by_time(QVector<n_global_types::C_point> &points, double newTime, int axis) {
    // Перерасчёт не требуется
    if (abs(points.back()[n_global_types::X] - newTime) < N_inter::n_data::n_motion_vars::n_calc_vars::calculation_error) {
        return points;
    }
    // Если движения нет
    else if (N_inter::n_algebra::n_math::is_equal(N_inter::n_algebra::n_limits::max_y(points), 0) && N_inter::n_algebra::n_math::is_equal(N_inter::n_algebra::n_limits::min_y(points), 0)) {
        // points.back()[n_geom::X] = points[0][n_geom::X] + newTime;
        // points.insert(0, points[0]);
        points.back()[n_global_types::X] = newTime;
        return points;
    }

    return proxy_correct_area_by_time(points, newTime, axis);
}
// --------------------------------------------------------

// BUG переделать ЭТУ и ДРУГУЮ функции корректировки площади!!!!

QVector<N_inter::n_global_types::C_point> N_inter::n_geom::n_points::proxy_correct_area_by_time(QVector<n_global_types::C_point> &points, double newTime, int axis) {
    double L = N_inter::n_algebra::n_math::get_trapezoid_area(points); // Перемещение
    double a = N_inter::n_data::n_motion_vars::n_calc_vars::acceleration[axis]; // Ускорение

    // Достигнутая скорость
    double F = points[1][n_global_types::Y];

    // Если движение идёт в обратном направлении, то сменить значения достижимой скорости и ускорения
    if (points[1][n_global_types::Y] < 0) {
        F = -F;
        a = -a;
    }

    // Расчёт времени для разгона
    double t04 = newTime, t01 = points[0][n_global_types::X];

    double aTime1 = 0.5 * (t04 - t01) - sqrt(a * (-4 * L + a * t01 * t01 - 2 * a * t01 * t04 + a * t04 * t04)) / (2 * a);
    double aTime2 = 0.5 * (t04 - t01) + sqrt(a * (-4 * L + a * t01 * t01 - 2 * a * t01 * t04 + a * t04 * t04)) / (2 * a);

    // Новая достигнутая скорость
    double F1 = a * aTime1, F2 = a * aTime2;

    // Взятие максимальной доступной скорости
    double newF = F1;
    double aTime = aTime1;
    if ((newF > F) || ((newF <= F) && (F2 <= F) && (newF < F2))) {
        newF = F2;
        aTime = aTime2;
    }

    // Перерасчёт для времени и скорости
    N_inter::n_global_types::C_point point1, point2, point3, point4;

    double t1 = points[0][n_global_types::X], t2 = t1 + aTime, t3 = newTime - aTime, t4 = newTime;
    double v1 = 0, v2 = newF, v3 = newF, v4 = 0;

    point1[n_global_types::X] = t1; point2[n_global_types::X] = t2; point3[n_global_types::X] = t3; point4[n_global_types::X] = t4;
    point1[n_global_types::Y] = v1; point2[n_global_types::Y] = v2; point3[n_global_types::Y] = v3; point4[n_global_types::Y] = v4;

    // Формирование результата
    QVector<N_inter::n_global_types::C_point> result;
    result.push_back(point1); result.push_back(point2);
    result.push_back(point3); result.push_back(point4);

    // Если point2 лежит правее point3, то это ошибка
    if (N_inter::n_algebra::n_math::is_more_than(point2[n_global_types::X], point3[n_global_types::X])) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QVector<C_point> NoneProfVelocity::_proxy_reinter(QVector<C_point>& points, double newTime, int axis)";
        exc.m_condition = "n_algebra::n_math::is_more_than(point2[n_global_types::X], point3[n_global_types::X])";
        exc.m_decision = "Вторая точка лежит правее третьей";
        throw exc;
    }

    return result;
}
// --------------------------------------------------------
