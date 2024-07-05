#include "n_trapezoids.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_none_prof/n_data.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_types/C_arc_circle.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_types_calc/N_arc_circles.h"
#include "N_inter/N_motion_calc/n_convert.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_calc/n_motion_sections.h"
#include "N_inter/N_geom/n_points.h"
#include <cmath>
#include "N_inter/N_algebra/n_limits.h"
// --------------------------------------------------------

using N_inter::n_global_types::COORD;
using N_inter::n_motion_calc::n_rounding_corners::n_types::C_arc_circle;
using N_inter::n_global_types::C_point;
using N_inter::n_global_types::C_m_line;
using N_inter::n_motion_calc::n_types::C_motion_section;
// --------------------------------------------------------


void N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::n_aux::left_corner_round(QVector<n_global_types::C_m_line> &lines, int axis) {
    // Получение типовой левой дуги для этой оси
    C_arc_circle left = N_inter::n_motion_calc::n_rounding_corners::n_none_prof::n_data::typical_arcs.left_typical_arcs[axis];

    if (left.size() == 0) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "left.size() == 0";
        exc.m_decision = "Типовая дуга не содержит отрезков";
        throw exc;
    }

    // Точка пересечения двух прямых
    C_point inter_point = lines[0].m_second_point;

    // Разница между точкой пересечения и угловой точкой дуги
    // TODO разобраться с const-аргументами для класса C_point
    // C_point offset = left.angle_position - inter_point;

    // Параллельный перенос дуги
    N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_arc_circles::move(left, inter_point);

    // Первая, вторая и третья прямые трапеции
    C_m_line line_1 = lines[0];
    C_m_line line_2 = lines[1];
    C_m_line line_3 = lines[2];

    // Укорачивание первой прямой
    line_1.m_second_point = left.arc.front().m_first_point;

    // Укорачивание второй прямой
    line_2.m_first_point = left.arc.back().m_second_point;

    // Формирование результата
    lines.clear();
    lines.push_back(line_1);
    for (int i = 0; i < left.size(); i++) {
        lines.push_back(left[i]);
    }
    lines.push_back(line_2);
    lines.push_back(line_3);

    // Проверка на корректность операции
    if (!N_inter::n_motion_calc::n_motion_sections::is_section_correct(lines)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!N_inter::n_motion_calc::n_motion_sections::is_section_correct(lines)";
        exc.m_decision = "Полученная в результате округления углов фигура не является секцией движения";
        throw exc;
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::n_aux::right_corner_round(QVector<n_global_types::C_m_line> &lines, int axis) {
    // Получение типовой правой дуги для этой оси
    C_arc_circle right = N_inter::n_motion_calc::n_rounding_corners::n_none_prof::n_data::typical_arcs.right_typical_arcs[axis];

    // Вектор начальных отрезков
    QVector<C_m_line> source_lines = lines;

    if (right.size() == 0) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "right.size() == 0";
        exc.m_decision = "Типовая дуга не содержит отрезков";
        throw exc;
    }

    // Точка пересечения двух прямых
    C_point inter_point = lines.back().m_first_point;

    // Разница между точкой пересечения и угловой точкой дуги
    // TODO разобраться с const-аргументами для класса C_point
    // C_point offset = right.angle_position - inter_point;

    // Параллельный перенос дуги
    N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_arc_circles::move(right, inter_point);

    // Сохранение двух крайних справа прямых
    // Последняя прямая
    C_m_line line_1 = lines[lines.size() - 1];
    lines.pop_back();

    // Предпоследняя прямая
    C_m_line line_2 = lines[lines.size() - 1];
    lines.pop_back();

    // Укорачивание последней и предпоследней прямых

    // Укорачивание предпоследней прямой
    line_2.m_second_point = right.arc.front().m_first_point;

    // Укорачивание последней прямой
    line_1.m_first_point = right.arc.back().m_second_point;

    // Формирование результата

    // Добавление старой предпоследней линии
    lines.push_back(line_2);

    // Добавление линий полуокружности
    for (int i = 0; i < right.size(); i++) {
        lines.push_back(right[i]);
    }

    // Добавление старой последней линии
    lines.push_back(line_1);

    // TODO удаить все throw_ функции

    // Проверка на корректность операции
    if (!N_inter::n_motion_calc::n_motion_sections::is_section_correct(lines)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!N_inter::n_motion_calc::n_motion_sections::is_section_correct(lines)";
        exc.m_decision = "Полученная в результате округления углов фигура не является секцией движения";
        throw exc;
    }
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::n_aux::is_h_correct(n_global_types::C_m_line &left, n_global_types::C_m_line &right, double h, double S) {
    // Проверка на пригодность высоты h

    C_point inter_point = N_inter::n_geom::n_lines::get_intersection_point(left, right);

    // 1. Не превосходит ординату inter_point
    if (N_inter::n_algebra::n_math::is_more_than(inter_point[COORD::Y], h)) {
        // 2. Образует трапецию
        C_m_line line1, line2, line3;

        C_point point_1;
        C_point point_2;
        C_point point_3;
        C_point point_4;

        point_1 = left.m_first_point;

        point_2[COORD::X] = N_inter::n_geom::n_lines::get_line_x_by_y(left, h);
        point_2[COORD::Y] = h;

        point_3[COORD::X] = N_inter::n_geom::n_lines::get_line_x_by_y(right, h);
        point_3[COORD::Y] = h;

        point_4 = right.m_second_point;


        line1.m_first_point = point_1;
        line1.m_second_point = point_2;

        line2.m_first_point = point_2;
        line2.m_second_point = point_3;

        line3.m_first_point = point_3;
        line3.m_second_point = point_4;

        QVector<C_m_line> lines = {line1, line2, line3};
        if (is_trapezoid(lines)) {
            // 3. Трапеция нужной площади
            double cur_s = N_inter::n_geom::n_lines::get_lines_definite_integral(lines);
            if (N_inter::n_algebra::n_math::is_equal(cur_s, S)) {
                return true;
            }
        }
    }
    return false;
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::is_trapezoid(QVector<n_global_types::C_m_line> &lines) {
    // Линий 3
    if (lines.size() != 3) {
        return false;
    }

    // Наклон у крайних линий
    double x_length_1 = lines[0].m_second_point[COORD::X] - lines[0].m_first_point[COORD::X];
    double x_length_2 = lines[2].m_second_point[COORD::X] - lines[2].m_first_point[COORD::X];

    double y_length_1 = lines[0].m_second_point[COORD::Y] - lines[0].m_first_point[COORD::Y];
    double y_length_2 = lines[2].m_first_point[COORD::Y] - lines[2].m_second_point[COORD::Y];

    if (!N_inter::n_algebra::n_math::is_equal(x_length_1, x_length_2)) {
        return false;
    }
    if (!N_inter::n_algebra::n_math::is_equal(y_length_1, y_length_2)) {
        return false;
    }

    // Начальная и конечная точка нули
    if (!N_inter::n_algebra::n_math::is_equal(lines[0].m_first_point[COORD::Y], 0)) {
        return false;
    }
    if (!N_inter::n_algebra::n_math::is_equal(lines[2].m_second_point[COORD::Y], 0)) {
        return false;
    }

    // Средняя линия горизонтальная
    if (!N_inter::n_geom::n_lines::is_hor_line(lines[1])) {
        return false;
    }

    // Точки пересечения
    if (lines[0].m_second_point != lines[1].m_first_point) {
        return false;
    }
    if (lines[1].m_second_point != lines[2].m_first_point) {
        return false;
    }

    // Вторая точка лежит правее третьей
    if (N_inter::n_algebra::n_math::is_more_than(lines[0].m_second_point[COORD::X], lines[1].m_second_point[COORD::X])) {
        return false;
    }

    return true;
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::is_trapezoid(N_inter::n_motion_calc::n_types::C_motion_section& section) {
    return is_trapezoid(section.get_lines());
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::is_trapezoids(QVector<n_motion_calc::n_types::C_motion_section> &sections) {
    for (int i = 0; i < sections.size(); i++) {
        if (!is_trapezoid(sections[i])) {
            return false;
        }
    }
    return true;
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::is_triangle(QVector<n_global_types::C_m_line> &lines) {
    // Проверка на треугольник. Две стороны
    if (lines.size() != 2) {
        return false;
    }

    // Проверка на треугольник. Начальная и конечная точка с нулевой ординатой
    if (!N_inter::n_algebra::n_math::is_equal(lines.front().m_first_point[COORD::Y], 0)) {
        return false;
    }
    if (!N_inter::n_algebra::n_math::is_equal(lines.back().m_second_point[COORD::Y], 0)) {
        return false;
    }

    // Проверка на треугольник. Последняя точка первой прямой равна первой точке второй прямой
    if (!N_inter::n_algebra::n_math::is_equal(lines[0].m_second_point, lines[1].m_first_point)) {
        return false;
    }

    return true;
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::is_fit_possible(QVector<n_global_types::C_m_line> &lines, int axis) {
    if (!is_trapezoid(lines)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_trapezoid(lines)";
        exc.m_decision = "Переданные функции отрезки не образуют отрезки";
        throw exc;
    }

    // Высота трапеции
    double high = lines[0].m_second_point[COORD::Y];
    double min_high = N_inter::n_motion_calc::n_rounding_corners::n_none_prof::n_data::typical_arcs.min_heights[axis];

    // Ширина прямоугольной составляющей
    double width = lines[1].m_second_point[COORD::X] - lines[1].m_first_point[COORD::X];
    double min_width = N_inter::n_motion_calc::n_rounding_corners::n_none_prof::n_data::typical_arcs.min_widths[axis];

    // Высота слишком маленькая
    if (N_inter::n_algebra::n_math::is_more_than(min_high, high)) {
        return false;
    }

    // Ширина слишком маленькая
    if (N_inter::n_algebra::n_math::is_more_than(min_width, width)) {
        return false;
    }

    return true;
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::is_fit_possible(n_motion_calc::n_types::C_motion_section &section, int axis) {
    return is_fit_possible(section.get_lines(), axis);
}
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_m_line> N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::round_trapezoid(QVector<n_global_types::C_m_line> &lines, int axis) {
    // Если это не трапеция
    if (!is_trapezoid(lines)) {
        // Если это секция с нулевым перемещением
        if (N_inter::n_motion_calc::n_motion_sections::is_zero_displacement_section(lines)) {
            return lines;
        }
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_trapezoid(lines)";
        exc.m_decision = "Переданный вектор отрезков не образует трапецию";
        throw exc;
    }
    // Если углы для трапеции закруглить нельзя
    if (!is_fit_possible(lines, axis)) {
        return lines;
    }

    QVector<n_global_types::C_m_line> new_lines = lines;

    // ERROR Тут считает неправильно

    // Закругление левого угла
    n_aux::left_corner_round(new_lines, axis);

    // Закругление правого угла
    n_aux::right_corner_round(new_lines, axis);

    return new_lines;
}
// --------------------------------------------------------

QVector<C_m_line> N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::round_trapezoid(n_motion_calc::n_types::C_motion_section &section, int axis) {
    return round_trapezoid(section.get_lines(), axis);
}
// --------------------------------------------------------

QVector<double> N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::get_area_diff_round(QVector<C_motion_section> &sections) {
    QVector<double> result = {};
    for (int i = 0; i < sections.size(); i++) {
        // Если это не трапеция, то кидать исключение
        if (!is_trapezoid(sections[i])) {
            // Если это секция с нулевым перемещением
            if (N_inter::n_motion_calc::n_motion_sections::is_zero_displacement_section(sections[i])) {
                result.push_back(0);
                continue;
            }
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "!is_trapezoid(sections[i])";
            exc.m_decision = "Секция не является трапецией";
            throw exc;
        }

        // Если движение в отрицательном направлении, то отобразит трапецию вдоль оси Х
        C_motion_section curr_section = sections[i];
        if (N_inter::n_algebra::n_math::is_more_than(0, curr_section[1].m_first_point[COORD::Y])) {
            N_inter::n_motion_calc::n_motion_sections::segmentMirroredByY(curr_section);
        }

        // Получить площадь текущей секции
        double curr_area = N_inter::n_geom::n_lines::get_lines_definite_integral(sections[i]);

        // Если площадь нулевая, то добавить 0
        if (N_inter::n_algebra::n_math::is_equal(curr_area, 0)) {
            result.push_back(0);
            continue;
        }

        // Если окружности вписать нельзя, то добавить ноль
        if (!is_fit_possible(sections[i], i)) {
            result.push_back(0);
            continue;
        }

        // Иначе вписать окружности и вычислить разницу
        QVector<C_m_line> new_section = round_trapezoid(sections[i], i);

        double new_area = N_inter::n_geom::n_lines::get_lines_definite_integral(new_section);

        if (N_inter::n_algebra::n_math::is_more_than(0, curr_area - new_area)) {
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(0, curr_area - new_area)";
            exc.m_decision = "Разница большей и меньшей площадей отрицательная";
            throw exc;
        }

        result.push_back(curr_area - new_area);
    }
    return result;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::add_rectangular_component_for_trapezoids(n_motion_calc::n_types::C_motion_section &section, double diff_area) {
    // Если это не трапеция, то кидать исключение
    if (!is_trapezoid(section)) {
        if (N_inter::n_motion_calc::n_motion_sections::is_zero_displacement_section(section)) {
            return;
        }
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_trapezoid(section)";
        exc.m_decision = "Секция не является трапецией";
        throw exc;
    }

    C_motion_section new_section = section;

    // Если добавляемая площадь равна нулю, то добавлять её не нужно
    if (N_inter::n_algebra::n_math::is_equal(0, diff_area)) {
        return;
    }

    // Временная разница
    double v = new_section[0].m_second_point[COORD::Y];
    double dt = abs(diff_area) / v;

    // Перенос крайней справа прямой на dt единиц вправо, если площадь положительная
    if (N_inter::n_algebra::n_math::is_more_than(diff_area, 0)) {
        new_section[1].m_second_point[COORD::X] = new_section[1].m_second_point[COORD::X] + dt;
        new_section[2].m_first_point[COORD::X]  = new_section[2].m_first_point[COORD::X]  + dt;
        new_section[2].m_second_point[COORD::X] = new_section[2].m_second_point[COORD::X] + dt;
    }
    else {
        new_section[1].m_second_point[COORD::X] = new_section[1].m_second_point[COORD::X] - dt;
        new_section[2].m_first_point[COORD::X]  = new_section[2].m_first_point[COORD::X]  - dt;
        new_section[2].m_second_point[COORD::X] = new_section[2].m_second_point[COORD::X] - dt;
    }

    section = new_section;

    if (!is_trapezoid(section)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_trapezoid(section)";
        exc.m_decision = "Полученная секция не является трапецией";
        throw exc;
    }
}
// --------------------------------------------------------

QVector<N_inter::n_motion_calc::n_types::C_motion_section> N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::correct_area_by_time(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &sections, double new_time) {
    QVector<C_motion_section> result;

    // Если секций слишком мало
    if (sections.size() != N_inter::n_data::n_motion_vars::n_calc_vars::axis_count) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "sections.size() != N_inter::n_data::n_motion_vars::n_calc_vars::axis_count";
        exc.m_decision = "Кол-во секций не равно кол-ву осей";
        throw exc;
    }

    // Если секция не является трапецией, то кидать исключение
    for (int i = 0; i < sections.size(); i++) {
        if (!is_trapezoid(sections[i])) {
            // Если это секция с пустым перемещением, то просто удиннить её
            if (N_inter::n_motion_calc::n_motion_sections::is_zero_displacement_section(sections[i])) {
                continue;
            }
            else {
                S_exception exc;
                exc.m_calling_object = Q_FUNC_INFO;
                exc.m_condition = "!is_trapezoid(sections[i])";
                exc.m_decision = "Одна из секций не является трапецией";
                throw exc;
            }
        }
    }

    // Перебор секций
    for (int i = 0; i < sections.size(); i++) {
        // Если это секция с нулевым перемещением, то просто удлинить её
        if (N_inter::n_motion_calc::n_motion_sections::is_zero_displacement_section(sections[i])) {
            C_point new_end_point = sections[i].get_end_point();
            new_end_point[COORD::X] = new_time;
            sections[i].set_end_point(new_end_point);

            result.push_back(sections[i]);
            continue;
        }

        // Массив точек
        C_motion_section curr_section = sections[i];
        QVector<C_point> points = { curr_section[0].m_first_point, curr_section[0].m_second_point, curr_section[1].m_second_point, curr_section[2].m_second_point };

        // Преобразование площади
        // TODO: найти и заменить сложную функцию в профилировщике траектории: она сложная и непонятная. Есть новая функция с задокументированным алгоритмом
        QVector<C_m_line> lines = correct_trapezoid_area(points, new_time);

        // Обновление результата
        C_motion_section new_section;
        new_section.set_lines(lines);
        if (!is_trapezoid(new_section)) {
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "!is_trapezoid(new_section)";
            exc.m_decision = "Полученная секция не является трапецией";
            throw exc;
        }

        result.push_back(new_section);
    }
    return result;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::triangle_peak_slice(QVector<n_global_types::C_m_line> &lines, int axis) {
    // Проверка на треугольник
    if (!is_triangle(lines)) {
        return;
    }

    // Если движение в обратном направлении, то отобразить треугольник вдоль оси X
    bool mirr_flag = false;
    if (N_inter::n_algebra::n_math::is_more_than(0, lines[0].m_second_point[COORD::Y])) {
        N_inter::n_geom::n_lines::mirroring_along_axis_y(lines);
        mirr_flag = true;
    }


    // Начальная площадь
    double source_S = N_inter::n_geom::n_lines::get_lines_definite_integral(lines);

    // Высота треугольника
    double h = lines[0].m_second_point[COORD::Y];

    // Срез высоты
    h = h - h * N_inter::n_data::n_motion_vars::n_calc_vars::degree_peak_cutoff_for_triangles[axis];

    // Корректировка высоты первой линии
    double new_x_1 = N_inter::n_geom::n_lines::get_line_x_by_y(lines[0], h);
    lines[0].m_second_point[COORD::X] = new_x_1;
    lines[0].m_second_point[COORD::Y] = h;

    // Корректировка высоты второй линии
    double new_x_2 = N_inter::n_geom::n_lines::get_line_x_by_y(lines[1], h);
    lines[1].m_first_point[COORD::X] = new_x_2;
    lines[1].m_first_point[COORD::Y] = h;

    // Добавление основания, достроение треугольника в трапецию

    C_m_line new_line;

    new_line.m_first_point[COORD::X] = new_x_1;
    new_line.m_first_point[COORD::Y] = h;

    new_line.m_second_point[COORD::X] = new_x_2;
    new_line.m_second_point[COORD::Y] = h;

    lines.insert(1, new_line);

    // Новая площадь
    double new_S = N_inter::n_geom::n_lines::get_lines_definite_integral(lines);

    // Корректировка площади
    C_motion_section section;
    section.set_lines(lines);
    add_rectangular_component_for_trapezoids(section, source_S - new_S);
    lines = section.get_lines();

    // Если полученная фигура не является трапецией, то кидать исключение
    if (!is_trapezoid(lines)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_trapezoid(lines)";
        exc.m_decision = "В результате среза пика треугольника получена фигура, которая не является треугольником";
        throw exc;
    }

    // Новая площадь
    new_S = N_inter::n_geom::n_lines::get_lines_definite_integral(lines);

    // Если площади не совпадают, то кидать исключение
    if (!N_inter::n_algebra::n_math::is_equal(source_S, new_S)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!N_inter::n_algebra::n_math::is_equal(source_S, new_S)";
        exc.m_decision = "В результате среза пика для треугольника изменена площадь фигуры";
        throw exc;
    }

    // Если движение в обратном направлении, то отобразить треугольник вдоль оси X
    if (mirr_flag) {
        N_inter::n_geom::n_lines::mirroring_along_axis_y(lines);
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::trapezoid_stretching(QVector<n_global_types::C_m_line> &lines, int axis) {
    // Если это не трапеция, то кидать исключение
    if (!is_trapezoid(lines)) {
        // Если это секция с нулевым перемещением
        if (N_inter::n_motion_calc::n_motion_sections::is_zero_displacement_section(lines)) {
            return;
        }
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_trapezoid(section)";
        exc.m_decision = "Вектор отрезков не является трапецией";
        throw exc;
    }

    // Получение минимальной длины верхнего основания
    double min_width = N_inter::n_motion_calc::n_rounding_corners::n_none_prof::n_data::typical_arcs.get_min_width_for_axis(axis);
    double real_width = lines.back().m_first_point[COORD::X] - lines.front().m_second_point[COORD::X];

    // Если верхнее основание достаточно длинное
    if (!N_inter::n_algebra::n_math::is_more_than(min_width, real_width)) {
        return;
    }

    // Если верхнее основание слишком короткое
    N_inter::n_geom::n_lines::set_line_params(lines[0]);
    double A1 = lines[0].A, B1 = lines[0].B, C1 = lines[0].C;
    double X_A = lines[0].m_first_point[COORD::X], MIN_W = min_width;
    double S = N_inter::n_geom::n_lines::get_lines_definite_integral(lines);

    // Первое потенциальное смещение
    double dp1 = - MIN_W/2 - X_A/2 - sqrt(A1*A1*MIN_W*MIN_W - 2*A1*A1*MIN_W*X_A + A1*A1*X_A*X_A - 2*A1*C1*MIN_W + 2*A1*C1*X_A - 4*B1*S*A1 + C1*C1)/(2*A1) - C1/(2*A1);
    // Второе потенциальное смещение
    double dp2 = sqrt(A1*A1*MIN_W*MIN_W - 2*A1*A1*MIN_W*X_A + A1*A1*X_A*X_A - 2*A1*C1*MIN_W + 2*A1*C1*X_A - 4*B1*S*A1 + C1*C1)/(2*A1) - X_A/2 - MIN_W/2 - C1/(2*A1);
    // Требуемое смещение
    double result_dp = 0;

    // Если dp1 и dp2 оба больше нуля
    if (N_inter::n_algebra::n_math::is_more_than(dp1, 0) && N_inter::n_algebra::n_math::is_more_than(dp2, 0)) {
        result_dp = N_inter::n_algebra::n_limits::min(dp1, dp2);
    }
    // Если dp1 и dp2 оба меньше нуля, то кидать исключение
    else if (N_inter::n_algebra::n_math::is_more_than(0, dp1) && N_inter::n_algebra::n_math::is_more_than(0, dp2)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(0, dp1) && N_inter::n_algebra::n_math::is_more_than(0, dp2)";
        exc.m_decision = "Обе высоты отрицательные";
        throw exc;
    }
    // Если dp1 и dp2 оба нули, то кидать исключение
    else if (N_inter::n_algebra::n_math::is_equal(dp1, 0) && N_inter::n_algebra::n_math::is_equal(dp2, 0)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_equal(dp1, 0) && N_inter::n_algebra::n_math::is_equal(dp2, 0)";
        exc.m_decision = "Обе высоты нулевые";
        throw exc;
    }
    // Только одно смещение положительная
    if (N_inter::n_algebra::n_math::is_more_than(dp1, 0) || N_inter::n_algebra::n_math::is_more_than(dp2, 0)) {
        result_dp = N_inter::n_algebra::n_limits::max(dp1, dp2);
    }
    // Неизвестная ситуация
    else {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "else";
        exc.m_decision = "Неизвестный случай для знаков смещений";
        throw exc;
    }

    // Точки исходной трапеции
    C_point A = lines[0].m_first_point;
    C_point B = lines[0].m_second_point;
    C_point C = lines[2].m_first_point;
    C_point D = lines[2].m_second_point;

    // Корректировка точки B
    B[COORD::X] = A[COORD::X] + result_dp;
    B[COORD::Y] = N_inter::n_geom::n_lines::get_line_y_by_x(lines[0], B[COORD::X]);

    // Корректировка точки C
    C[COORD::X] = B[COORD::X] + min_width;
    C[COORD::Y] = B[COORD::Y];

    // Корректировка точки D
    D[COORD::X] = C[COORD::X] + result_dp;
    D[COORD::Y] = 0;

    // Корректировка прямых исходной трапеции
    C_m_line line1, line2, line3;

    line1.m_first_point = A;
    line1.m_second_point = B;

    line2.m_first_point = B;
    line2.m_second_point = C;

    line3.m_first_point = C;
    line3.m_second_point = D;

    // Результат
    QVector<C_m_line> result = { line1, line2, line3 };

    // Если в результате получилась не трапеция, то кидать исключение
    if (!is_trapezoid(result)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_trapezoid(result)";
        exc.m_decision = "Полученная в результате преобразования прямых фигура не является трапецией, а должна";
        throw exc;
    }

    lines = result;
}
// --------------------------------------------------------

QVector<C_m_line> N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::correct_trapezoid_area(n_motion_calc::n_types::C_motion_section &motion_section, double new_time) {
    return correct_trapezoid_area(motion_section.get_lines(), new_time);
}
// --------------------------------------------------------

// TODO: переименовать
QVector<N_inter::n_global_types::C_m_line> N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::correct_trapezoid_area(QVector<n_global_types::C_point> &points, double new_time) {
    if (points.size() != 4) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "points.size() != 4";
        exc.m_decision = "Размер точек не равен четырём и не задаёт трапецию";
        throw exc;
    }

    // Составление линий

    C_m_line line1, line2, line3;

    line1.m_first_point = points[0];
    line1.m_second_point = points[1];

    line2.m_first_point = points[1];
    line2.m_second_point = points[2];

    line3.m_first_point = points[2];
    line3.m_second_point = points[3];

    QVector<C_m_line> lines = { line1, line2, line3 };

    // Корректировка площади

    return correct_trapezoid_area(lines, new_time);
}
// --------------------------------------------------------

// TODO: вынести расчёт высоты в отдельную функцию: эта слишком большая
// TODO: перенести корректировку точек в отдельную функцию: эта слишком большая
QVector<N_inter::n_global_types::C_m_line> N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::correct_trapezoid_area(QVector<n_global_types::C_m_line> &lines, double new_time) {
    // Если фигура не трапеция, то кидать исключение
    if (!is_trapezoid(lines)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_trapezoid(lines)";
        exc.m_decision = "Переданная фигура для корректировки площади не является трапецией";
        throw exc;
    }

    // Результат
    QVector<C_m_line> result = lines;

    // Получение смещения по времени
    double diff_time = new_time - (result.back().m_second_point[COORD::X] - result.front().m_first_point[COORD::X]);

    // Если смещение по времени равно нулю, то ничего смещать не нужно
    if (N_inter::n_algebra::n_math::is_equal(diff_time, 0)) {
        return result;
    }

    // Если смещение отрицательное, то кидать исключение
    if (N_inter::n_algebra::n_math::is_more_than(0, diff_time)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(0, diff_time)";
        exc.m_decision = "Отрицательное смещение по времени, корректировка невозможна";
        throw exc;
    }

    // Начальная площадь
    double source_area = N_inter::n_geom::n_lines::get_lines_definite_integral(result);

    // Растяжение трапеции по времени
    result[1].m_second_point[COORD::X] = result[1].m_second_point[COORD::X] + diff_time;
    result[2].m_first_point[COORD::X]  = result[2].m_first_point[COORD::X]  + diff_time;
    result[2].m_second_point[COORD::X] = result[2].m_second_point[COORD::X] + diff_time;

    // Достраивание трапеции до треугольника

    // Левая и правая стороны треугольника
    C_m_line left = result.front();
    C_m_line right = result.back();

    // Точка пересечения этих сторон
    C_point inter_point = N_inter::n_geom::n_lines::get_intersection_point(left, right);

    // Если точка пересечения прямых отрицательная, то кидать исключение
    if (N_inter::n_algebra::n_math::is_more_than(0, inter_point[COORD::X])) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(0, inter_point[COORD::X])";
        exc.m_decision = "Отрицательная координата точки пересечения";
        throw exc;
    }
    if (N_inter::n_algebra::n_math::is_more_than(0, inter_point[COORD::Y])) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(0, inter_point[COORD::Y])";
        exc.m_decision = "Отрицательная координата точки пересечения";
        throw exc;
    }

    // Достираивание сторон треугольника
    left.m_second_point = inter_point;
    right.m_first_point = inter_point;

    // Если площадь треугольника меньше достигаемой площади, то кидать исключение

    // Поиск высоты

    // запись параметров

    double A1 = 0, A2 = 0, B1 = 0, B2 = 0, C1 = 0, C2 = 0, X_A = 0, X_D = 0, S = 0;

    // line1
    N_inter::n_geom::n_lines::set_line_params(result[0]);
    A1 = result[0].A;
    B1 = result[0].B;
    C1 = result[0].C;

    // line2
    N_inter::n_geom::n_lines::set_line_params(result[2]);
    A2 = result[2].A;
    B2 = result[2].B;
    C2 = result[2].C;

    // X_A, X_D, S_new
    X_A = result.front().m_first_point[COORD::X];
    X_D = result.back().m_second_point[COORD::X];
    S = source_area;

    double new_area = N_inter::n_geom::n_lines::get_lines_definite_integral(result);

    // Если трапеция не изменила площадь, то время добавилось некорректно
    if (N_inter::n_algebra::n_math::is_equal(new_area, source_area)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_equal(new_area, source_area)";
        exc.m_decision = "Площадь трапеции не изменилась";
        throw exc;
    }

    if (N_inter::n_algebra::n_math::is_equal(A1*B2 - A2*B1, 0)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_equal(A1*B2 - A2*B1, 0)";
        exc.m_decision = "Рассчёт высот невозможен: деление на ноль";
        throw exc;
    }
    // Первая потенциальная высота
    double h1 = (A2*C1 - A1*C2 - sqrt(A1*A1*A2*A2*X_A*X_A + 2*A1*A1*A2*A2*X_A*X_D + A1*A1*A2*A2*X_D*X_D - 2*A1*A1*A2*C2*X_A - 2*A1*A1*A2*C2*X_D - 8*B2*S*A1*A1*A2 + A1*A1*C2*C2 + 2*A1*A2*A2*C1*X_A + 2*A1*A2*A2*C1*X_D + 8*B1*S*A1*A2*A2 - 2*A1*A2*C1*C2 + A2*A2*C1*C1) + A1*A2*X_A + A1*A2*X_D)/(2*A1*B2 - 2*A2*B1);
    // Вторая потенциальная
    double h2 = (sqrt(A1*A1*A2*A2*X_A*X_A + 2*A1*A1*A2*A2*X_A*X_D + A1*A1*A2*A2*X_D*X_D - 2*A1*A1*A2*C2*X_A - 2*A1*A1*A2*C2*X_D - 8*B2*S*A1*A1*A2 + A1*A1*C2*C2 + 2*A1*A2*A2*C1*X_A + 2*A1*A2*A2*C1*X_D + 8*B1*S*A1*A2*A2 - 2*A1*A2*C1*C2 + A2*A2*C1*C1) - A1*C2 + A2*C1 + A1*A2*X_A + A1*A2*X_D)/(2*A1*B2 - 2*A2*B1);
    // Требуемая высота
    double result_h = 0;

    // Если h1 и h2 неположительные, то кидать исключение
    if (N_inter::n_algebra::n_math::is_equal(h1, 0) && N_inter::n_algebra::n_math::is_equal(h2, 0)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_equal(h1, 0) && N_inter::n_algebra::n_math::is_equal(h2, 0)";
        exc.m_decision = "Обе высоты неположительные";
        throw exc;
    }

    result_h = -1;

    // Проверка на пригодность высоты h1
    if (n_aux::is_h_correct(left, right, h1, source_area)) {
        result_h = h1;
    }
    if (n_aux::is_h_correct(left, right, h2, source_area)) {
        result_h = h2;
    }

    // Если высота не выбрана
    if (result_h == -1) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "result_h == -1";
        exc.m_decision = "Ни одна из найденных высот не удовлетворяет условию";
        throw exc;
    }

    // Точки исходной трапеции
    C_point A = result[0].m_first_point;
    C_point B = result[0].m_second_point;
    C_point C = result[2].m_first_point;
    C_point D = result[2].m_second_point;

    // Корректировка точек B и C

    B[COORD::Y] = result_h;
    C[COORD::Y] = result_h;

    B[COORD::X] = N_inter::n_geom::n_lines::get_line_x_by_y(result[0], result_h);
    C[COORD::X] = N_inter::n_geom::n_lines::get_line_x_by_y(result[2], result_h);

    // Корректировка точек исходной трапеции

    C_m_line line1, line2, line3;

    line1.m_first_point  = A;
    line1.m_second_point = B;

    line2.m_first_point  = B;
    line2.m_second_point = C;

    line3.m_first_point  = C;
    line3.m_second_point = D;

    // Результат
    result.clear();
    result = { line1, line2, line3 };

    // Если в результате получилась не трапеция, то кидать исключение
    if (!is_trapezoid(result)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!is_trapezoid(result)";
        exc.m_decision = "Полученная в результате преобразования прямых фигура не является трапецией, а должна";
        throw exc;
    }

    return result;
}
// --------------------------------------------------------
