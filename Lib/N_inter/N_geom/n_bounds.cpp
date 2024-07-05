#include "n_bounds.h"
#include "N_inter/N_geom/n_points.h"
// --------------------------------------------------------
// Возвращает тип данных bound, который задает прямоугольник, в котором определена линия

N_inter::n_global_types::S_bounds N_inter::n_geom::n_bounds::find(n_global_types::C_m_line &line) {
    N_inter::n_global_types::S_bounds bound;

    // Определение границ для абсцисс
    if (line.m_first_point[n_global_types::X] > line.m_second_point[n_global_types::X]) {
        bound.m_min_coords[n_global_types::X] = line.m_second_point[n_global_types::X];
        bound.m_max_coords[n_global_types::X] = line.m_first_point[n_global_types::X];
    }
    else {
        bound.m_min_coords[n_global_types::X] = line.m_first_point[n_global_types::X];
        bound.m_max_coords[n_global_types::X] = line.m_second_point[n_global_types::X];
    }

    // Определение границ для ординат
    if (line.m_first_point[n_global_types::Y] > line.m_second_point[n_global_types::Y]) {
        bound.m_min_coords[n_global_types::Y] = line.m_second_point[n_global_types::Y];
        bound.m_max_coords[n_global_types::Y] = line.m_first_point[n_global_types::Y];
    }
    else {
        bound.m_min_coords[n_global_types::Y] = line.m_first_point[n_global_types::Y];
        bound.m_max_coords[n_global_types::Y] = line.m_second_point[n_global_types::Y];
    }

    return bound;
}
// --------------------------------------------------------
// Возвращает тип данных bound, который задает прямоугольник, в котором определены две линии

N_inter::n_global_types::S_bounds N_inter::n_geom::n_bounds::find(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    N_inter::n_global_types::S_bounds boundLine1 = find(line1);
    N_inter::n_global_types::S_bounds boundLine2 = find(line2);

    N_inter::n_global_types::S_bounds bound;

    // Начало для абсциссы: взять минимальное значение
    if (boundLine1.m_min_coords[n_global_types::X] < boundLine2.m_min_coords[n_global_types::X]) {
        bound.m_min_coords[n_global_types::X] = boundLine1.m_min_coords[n_global_types::X];
    }
    else {
        bound.m_min_coords[n_global_types::X] = boundLine2.m_min_coords[n_global_types::X];
    }

    // Начало для ординаты: взять минимальное значение
    if (boundLine1.m_min_coords[n_global_types::Y] < boundLine2.m_min_coords[n_global_types::Y]) {
        bound.m_min_coords[n_global_types::Y] = boundLine1.m_min_coords[n_global_types::Y];
    }
    else {
        bound.m_min_coords[n_global_types::Y] = boundLine2.m_min_coords[n_global_types::Y];
    }

    // Конец для абсциссы: взять максимальное значение
    if (boundLine1.m_max_coords[n_global_types::X] > boundLine2.m_max_coords[n_global_types::X]) {
        bound.m_max_coords[n_global_types::X] = boundLine1.m_max_coords[n_global_types::X];
    }
    else {
        bound.m_max_coords[n_global_types::X] = boundLine2.m_max_coords[n_global_types::X];
    }

    // Конец для ординаты: взять максимальное значение
    if (boundLine1.m_max_coords[n_global_types::Y] > boundLine2.m_max_coords[n_global_types::Y]) {
        bound.m_max_coords[n_global_types::Y] = boundLine1.m_max_coords[n_global_types::Y];
    }
    else {
        bound.m_max_coords[n_global_types::Y] = boundLine2.m_max_coords[n_global_types::Y];
    }

    return bound;
}
// --------------------------------------------------------
// Возвращает тип данных bound, который задает прямоугольник, в котором определены все линии вектора

N_inter::n_global_types::S_bounds N_inter::n_geom::n_bounds::find(QVector<n_global_types::C_m_line> &lines) {
    N_inter::n_global_types::S_bounds result = find(lines[0]);

    // Перебор линий, обновление результирующей границ
    for (int i = 1; i < lines.size(); i++) {
        N_inter::n_global_types::S_bounds bound = find(lines[i]);

        // Начало для абсцисс
        if (bound.m_min_coords[n_global_types::X] < result.m_min_coords[n_global_types::X]) {
            result.m_min_coords[n_global_types::X] = bound.m_min_coords[n_global_types::X];
        }
        // Конец для абсцисс
        if (bound.m_max_coords[n_global_types::X] > result.m_max_coords[n_global_types::X]) {
            result.m_max_coords[n_global_types::X] = bound.m_max_coords[n_global_types::X];
        }
        // Начало для ординат
        if (bound.m_min_coords[n_global_types::Y] < result.m_min_coords[n_global_types::Y]) {
            result.m_min_coords[n_global_types::Y] = bound.m_min_coords[n_global_types::Y];
        }
        // Конец для ординат
        if (bound.m_max_coords[n_global_types::Y] > result.m_max_coords[n_global_types::Y]) {
            result.m_max_coords[n_global_types::Y] = bound.m_max_coords[n_global_types::Y];
        }
    }

    return result;
}
// --------------------------------------------------------
// Обращаемся к функции нахождения общей точки границ между двумя линиями, переопределяем границы (конечная теперь - Т.П.), зачем-то сохраняем
// скорость

N_inter::n_global_types::C_m_line N_inter::n_geom::n_bounds::correct_first_line_bound(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2, n_global_types::C_point &interPoint) {
    N_inter::n_global_types::C_point E = n_geom::n_points::get_lines_boundary_common_point(line1, line2);

    // Условное начало для линии line1
    N_inter::n_global_types::C_point point1;
    point1[n_global_types::X]= line1.m_first_point[n_global_types::X];
    point1[n_global_types::Y]= line1.m_first_point[n_global_types::Y];

    // Условный конец для линии line1
    N_inter::n_global_types::C_point point2;
    point2[n_global_types::X]= line1.m_second_point[n_global_types::X];
    point2[n_global_types::Y]= line1.m_second_point[n_global_types::Y];

    // Истинные начало и конец линии line1
    N_inter::n_global_types::C_point lineBegin, lineEnd;
    if (n_geom::n_points::is_equal(point1, E)) {
        lineBegin = point2;
    }
    else {
        lineBegin = point1;
    }
    lineEnd = interPoint;

    // Корректировка границ
    N_inter::n_global_types::C_m_line newLine1;
    newLine1.m_first_point[n_global_types::X] = lineBegin[n_global_types::X];
    newLine1.m_first_point[n_global_types::Y] = lineBegin[n_global_types::Y];
    newLine1.m_second_point[n_global_types::X] = lineEnd[n_global_types::X];
    newLine1.m_second_point[n_global_types::Y] = lineEnd[n_global_types::Y];

    // Сохранение скорости
    newLine1.velocity = line1.velocity;

    return newLine1;
}
// --------------------------------------------------------
// То же самое для второй линии

N_inter::n_global_types::C_m_line N_inter::n_geom::n_bounds::correct_second_line_bound(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2, n_global_types::C_point &interPoint) {
    N_inter::n_global_types::C_point E = n_geom::n_points::get_lines_boundary_common_point(line1, line2);

    // Условное начало для линии line2
    N_inter::n_global_types::C_point point1;
    point1[n_global_types::X]= line2.m_first_point[n_global_types::X];
    point1[n_global_types::Y]= line2.m_first_point[n_global_types::Y];

    // Условный конец для линии line2
    N_inter::n_global_types::C_point point2;
    point2[n_global_types::X]= line2.m_second_point[n_global_types::X];
    point2[n_global_types::Y]= line2.m_second_point[n_global_types::Y];

    // Истинные начало и конец линии line2
    N_inter::n_global_types::C_point lineBegin, lineEnd;
    if (n_geom::n_points::is_equal(point1, E)) {
        lineEnd = point2;
    }
    else {
        lineEnd = point1;
    }
    lineBegin = interPoint;

    // Корректировка границ
    N_inter::n_global_types::C_m_line newLine2;
    newLine2.m_first_point[n_global_types::X] = lineBegin[n_global_types::X];
    newLine2.m_first_point[n_global_types::Y] = lineBegin[n_global_types::Y];
    newLine2.m_second_point[n_global_types::X] = lineEnd[n_global_types::X];
    newLine2.m_second_point[n_global_types::Y] = lineEnd[n_global_types::Y];

    // Сохранение скорости
    newLine2.velocity = line2.velocity;

    return newLine2;
}
// --------------------------------------------------------
