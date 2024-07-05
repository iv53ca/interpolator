#include "n_circles.h"
#include <cmath>
#include "N_inter/N_geom/n_points.h"
#include "N_inter/N_geom/n_vectors.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/N_geom/n_angles.h"
#include "N_inter/N_geom/N_half_plane/n_horizontal.h"
#include "N_inter/N_geom/N_half_plane/n_vertical.h"
// --------------------------------------------------------

using N_inter::n_global_types::C_point;
using N_inter::n_global_types::COORD;
// --------------------------------------------------------

N_inter::n_global_types::S_inter_circle N_inter::n_geom::n_circles::fit(N_inter::n_global_types::C_m_line &line1, N_inter::n_global_types::C_m_line &line2, bool &stat, double max_error) {
    N_inter::n_global_types::S_inter_circle circle; // Искомая окружность

    // Если линии сонаправленные, то вписать окружность нельзя
    if (N_inter::n_geom::n_lines::is_co_directional_lines(line1, line2)) {
        stat = false;
        return circle;
    }

    // Если угол сверх-малый, то вписать окружность нельзя
    if (N_inter::n_geom::n_angles::is_ultra_0_angle(line1, line2)) {
        stat = false;
        return circle;
    }

    // Если угол сверх-развёрнутый, то вписать окружность нельзя
    if (N_inter::n_geom::n_angles::is_ultra_180_angle(line1, line2)) {
        stat = false;
        return circle;
    }

    // Биссектриса и принадлежащая ей точка
    N_inter::n_global_types::C_m_line bisector;
    C_point point;

    // Если биссектриса вертикальная
    if (N_inter::n_geom::n_half_plane::n_horizontal::is_angle_bisector_vertical(line1, line2)) {
        // Получить точку пересечения прямых
        C_point inter_point = line1.m_second_point;

        // Получить новую точку, отложив точку пересечения прямых вверх на величину error
        point = inter_point;

        // Если угол лежит в верхней горизонтальной полуплоскости, то сдвинуть inter_point на error единиц вверх
        if (N_inter::n_geom::n_half_plane::n_horizontal::is_lines_in_upper_hor_half_plane(line1, line2)) {
            point[COORD::Y] = point[COORD::Y] + max_error;
        }
        // Иначе на error единиц вниз
        else {
            point[COORD::Y] = point[COORD::Y] - max_error;
        }
    }
    // Если биссектриса горизонтальная
    else if (N_inter::n_geom::n_half_plane::n_vertical::is_angle_bisector_horizontal(line1, line2)) {
        // Получить точку пересечения прямых
        C_point inter_point = line1.m_second_point;

        // Получить новую точку, отложив точку пересечения прямых вверх на величину error
        point = inter_point;

        // Если угол лежит в правой вертикальной полуплоскости, то сдвинуть inter_point на error единиц вправо
        if (N_inter::n_geom::n_half_plane::n_vertical::is_lines_in_right_ver_half_plane(line1, line2)) {
            point[COORD::X] = point[COORD::X] + max_error;
        }
        // Иначе на error единиц влево
        else {
            point[COORD::X] = point[COORD::X] - max_error;
        }
    }
    // Если биссектриса имеет угол
    else {
        bisector = n_geom::n_vectors::get_angle_bisector(line1, line2); // Биссектриса угла

        // Коэффициенты содержащей вектор прямой A, B и С
        double A = bisector.A, B = bisector.B, C = bisector.C;

        N_inter::n_global_types::C_point E = n_geom::n_points::get_lines_boundary_common_point(line1, line2);
        double x0 = E[n_global_types::X], y0 = E[n_global_types::Y]; // Предполагаемый центр окружности

        // Определение первой лежащей на биссектрисе точки
        N_inter::n_global_types::C_point point1;
        point1[n_global_types::Y] = (A*A*y0 - B*C + A*sqrt(A*A*max_error*max_error - A*A*x0*x0 - 2*A*B*x0*y0 - 2*A*C*x0 + B*B*max_error*max_error - B*B*y0*y0 - 2*B*C*y0 - C*C) - A*B*x0)/(A*A + B*B);
        point1[n_global_types::X] = (-B*point1[n_global_types::Y] - C) / A;

        // Определение второй лежащей на биссектрисе точки
        N_inter::n_global_types::C_point point2;
        point2[n_global_types::Y] = -(B*C - A*A*y0 + A*sqrt(A*A*max_error*max_error - A*A*x0*x0 - 2*A*B*x0*y0 - 2*A*C*x0 + B*B*max_error*max_error - B*B*y0*y0 - 2*B*C*y0 - C*C) + A*B*x0)/(A*A + B*B);
        point2[n_global_types::X] = (-B*point2[n_global_types::Y] - C) / A;

        // Уточнение лежащей точки на биссектрисе внутри угла
        point = point1;
        if (!n_geom::n_points::is_in_angle(point, line1, line2)) {
            point = point2;
        }
    }

    // Точки касания окружности
    N_inter::n_global_types::C_point interPoint1 = n_geom::n_points::get_project_onto_line(line1, point);
    N_inter::n_global_types::C_point interPoint2 = n_geom::n_points::get_project_onto_line(line2, point);

    circle.m_intersec_point_1[n_global_types::X] = interPoint1[n_global_types::X];
    circle.m_intersec_point_1[n_global_types::Y] = interPoint1[n_global_types::Y];

    circle.m_intersec_point_2[n_global_types::X] = interPoint2[n_global_types::X];
    circle.m_intersec_point_2[n_global_types::Y] = interPoint2[n_global_types::Y];

    // Характеристики окружности: радиус и центр
    double R = sqrt((interPoint1[n_global_types::X] - point[n_global_types::X]) * (interPoint1[n_global_types::X] - point[n_global_types::X]) + (interPoint1[n_global_types::Y] - point[n_global_types::Y]) * (interPoint1[n_global_types::Y] - point[n_global_types::Y]));
    double x0 = point[n_global_types::X];
    double y0 = point[n_global_types::Y];

    circle.m_radius = R;
    circle.m_center[n_global_types::X] = x0;
    circle.m_center[n_global_types::Y] = y0;

    // Проверка на нахождение точек касания окружности в пределах соответствующих отрезков
    if (n_geom::n_points::is_in_line(line1, interPoint1) && n_geom::n_points::is_in_line(line2, interPoint2)) {
        stat = true;
    }
    else {
        stat = false;
    }

    return circle;
}
// --------------------------------------------------------

void N_inter::n_geom::n_circles::sort_circle_points(QVector<N_inter::n_global_types::C_point> &circlePoints, N_inter::n_global_types::S_inter_circle &circle, N_inter::n_global_types::C_point &point1, N_inter::n_global_types::C_point &point2, int split_segments_count) {
    // Характеристики окружности
    double x0 = circle.m_center[n_global_types::X], y0 = circle.m_center[n_global_types::Y], R = circle.m_radius;

    // Координаты точек касания
    double x1 = point1[n_global_types::X], y1 = point1[n_global_types::Y];
    double x2 = point2[n_global_types::X], y2 = point2[n_global_types::Y];

    // Радиус-прямые для точек касания
    N_inter::n_global_types::C_m_line line1, line2;

    line1.m_first_point[n_global_types::X] = x0; line1.m_first_point[n_global_types::Y] = y0;
    line1.m_second_point[n_global_types::X] = x1; line1.m_second_point[n_global_types::Y] = y1;

    line2.m_first_point[n_global_types::X] = x0; line2.m_first_point[n_global_types::Y] = y0;
    line2.m_second_point[n_global_types::X] = x2; line2.m_second_point[n_global_types::Y] = y2;

    // Единичный отрезок вдоль оси абсцисс
    N_inter::n_global_types::C_m_line iLine;
    iLine.m_first_point[n_global_types::X] = 0; iLine.m_first_point[n_global_types::Y] = 0;
    iLine.m_second_point[n_global_types::X] = 1; iLine.m_second_point[n_global_types::Y] = 0;

    // Граничные условия для угла и шаг - обход окружности
    double phi0 = n_geom::n_lines::get_rad_angle(line1, iLine);
    double deltaPhi = abs(n_geom::n_lines::get_rad_angle(line1, line2));
    double phi1 = 0;

    // Если угол лежит ниже оси абсцисс, то нужно сменить знак
    if (y1 - y0 < 0) {
        phi0 = -phi0;
    }

    // Радиус-векторы для точек касания
    N_inter::n_global_types::C_vector vec1, vec2;

    vec1[n_global_types::X] = x0 - x1;
    vec1[n_global_types::Y] = y0 - y1;

    vec2[n_global_types::X] = x0 - x2;
    vec2[n_global_types::Y] = y0 - y2;

    // Корректировка конечного угла
    if (n_geom::n_vectors::get_vec_mul(vec1, vec2) >= 0) {
        phi1 = phi0 + deltaPhi;
    }
    else {
        phi1 = phi0 - deltaPhi;
    }

    double h = split_segments_count;

    // Формирование точек окружности
    // Направление 1: от меньшего к большему
    if (phi0 < phi1) {
        for (double i = phi0; i <= phi1; i += (phi1 - phi0) / h) {
            N_inter::n_global_types::C_point point;
            point[n_global_types::X] = R * cos(i) + x0;
            point[n_global_types::Y] = R * sin(i) + y0;
            circlePoints.push_back(point);
        }
    }
    // Направление 2: от большего к меньшему
    else {
        for (double i = phi0; i >= phi1; i += (phi1 - phi0) / h) {
            N_inter::n_global_types::C_point point;
            point[n_global_types::X] = R * cos(i) + x0;
            point[n_global_types::Y] = R * sin(i) + y0;
            circlePoints.push_back(point);
        }
    }

    // Ввиду погрешности вычислений контуры могут не замкнуться (окружность и вторая линия)
    // Дополнительная проверка
    if (!n_geom::n_points::is_equal(circlePoints.back(), point2)) {
        circlePoints.push_back(point2);
    }
}
// --------------------------------------------------------
