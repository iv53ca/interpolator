#include "n_math.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
#include "N_inter/S_exception.h"
// --------------------------------------------------------
// Функция сравнения для всех элементов вектора - возвращает false, если разница между числами больше ошибки вычисления, true во всех остальных случаях

bool N_inter::n_algebra::n_math::is_equal(QVector<double> &values) {
    for (int i = 0; i < values.size() - 1; i++) {
        if (abs(values.at(i) - values.at(i + 1)) > n_data::n_motion_vars::n_calc_vars::calculation_error) {
            return false;
        }
    }
    return true;
}
// --------------------------------------------------------
// Функция сравнения для для двух чисел - возвращает false, если разница между числами больше ошибки вычисления, true во всех остальных случаях


bool N_inter::n_algebra::n_math::is_equal(double t1, double t2) {
    return abs(t1 - t2) <= n_data::n_motion_vars::n_calc_vars::calculation_error;
}
// --------------------------------------------------------
// Функция сравнения для двух точек - возвращает false, если разница между числами больше ошибки вычисления, true во всех остальных случаях


bool N_inter::n_algebra::n_math::is_equal(n_global_types::C_point &point1, n_global_types::C_point &point2) {
    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        if (!is_equal(point1[i], point2[i])) {
            return false;
        }
    }
    return true;
}
// --------------------------------------------------------
// Функция замены очень маленького числа на 0

void N_inter::n_algebra::n_math::to_necessary_zero(double &value) {
    if (abs(value) <= N_inter::n_data::n_motion_vars::n_calc_vars::calculation_error) {
        value = 0;
    }
}
// --------------------------------------------------------
// Функция возвращает число со знаком производения двух чисел

bool N_inter::n_algebra::n_math::is_one_sign(double &h1, double &h2) {
    if (is_equal(h1, 0) || is_equal(h2, 0)) {
        N_inter::S_exception exc;
        exc.m_calling_object = "bool n_algebra::n_math::is_one_sign(double &h1, double &h2)";
        exc.m_condition = "is_equal(h1, 0) || is_equal(h2, 0)";
        exc.m_decision = "Одно из чисел не имеет знака";
        throw exc;
    }

    return is_more_than(h1 * h2, 0);
}
// --------------------------------------------------------
// Функция возвращает площадь трапеции из вектора точек

double N_inter::n_algebra::n_math::get_trapezoid_area(QVector<n_global_types::C_point> &points) {
    if (points.size() == 3) {
        return 0.5 * (points[2][n_global_types::COORD::X] - points[0][n_global_types::X]) * points[1][n_global_types::Y];
    }
    return 0.5 * (points[3][n_global_types::X] - points[0][n_global_types::X] + points[2][n_global_types::X] - points[1][n_global_types::X]) * points[1][n_global_types::Y];
}
// --------------------------------------------------------
// Функция возвращает площадь сегмента из сегмента в линиях

double N_inter::n_algebra::n_math::get_segment_area(QVector<n_global_types::C_m_line> &segment) {
    // Результат
    double S = 0;

    // Перебор отрезков сегмента
    for (int i = 0; i < segment.size(); i++) {
        // Координаты границ отрезка
        double x1 = segment[i].m_first_point[n_global_types::X], x2 = segment[i].m_second_point[n_global_types::X];
        double y1 = segment[i].m_first_point[n_global_types::Y], y2 = segment[i].m_second_point[n_global_types::Y];

        // Если прямая под наклоном и не пересекает ось абсцисс, то это трапеция
        if (is_not_equal(y1, y2) && (is_not_equal(y1, 0) && is_not_equal(y2, 0))) {
            S = S + abs(0.5 * (abs(y1) + abs(y2)) * (x2 - x1));
        }
        // Если прямая под наклоном и пересекает ось абсцисс, то это прямоугольный треугольник
        else if (is_not_equal(y1, y2)) {
            S = S + abs(0.5 * (abs(y2) - abs(y1)) * (x2 - x1));
        }
        // Иначе это прямоугольник
        else {
            S = S + abs((x2 - x1) * abs(y1));
            // S = S + (y2 - y1) * (x2 - x1);
        }
    }

    return S;
}
// --------------------------------------------------------
// Функция возвращает площадь сегмента из сегмента без заранеее определенных линий

double N_inter::n_algebra::n_math::get_segment_area(N_inter::n_motion_calc::n_types::C_motion_section &segment) {
    return get_segment_area(segment.get_lines());
}
// --------------------------------------------------------
// Функция возвращает площадь сегмента при условии добавления в него новой линии

double N_inter::n_algebra::n_math::get_line_area(n_global_types::C_m_line &line) {
    QVector<N_inter::n_global_types::C_m_line> segment;
    segment.push_back(line);
    return get_segment_area(segment);
}
// --------------------------------------------------------
// Функция сравнивает два числа с ошибкой вычисления и выводит то, которое не меньше ошибки вычисления

double N_inter::n_algebra::n_math::is_none_zero(double &value1, double &value2) {
    if (abs(value1) < n_data::n_motion_vars::n_calc_vars::calculation_error) {
        return value2;
    }
    else {
        return value1;
    }
}
// --------------------------------------------------------
// Функция выдает сумму двух чисел

double N_inter::n_algebra::n_math::get_sum(double &value1, double &value2) {
    return value1 + value2;
}
// --------------------------------------------------------
// Выдает true, если числа разные, и false, если числа одинаковые

bool N_inter::n_algebra::n_math::is_not_equal(double v1, double v2) {
    return !(abs(v1 - v2) < n_data::n_motion_vars::n_calc_vars::calculation_error);
}
// --------------------------------------------------------

bool N_inter::n_algebra::n_math::is_more_than(double v1, double v2) {
    return is_not_equal(v1, v2) && (v1 > v2);
}
// --------------------------------------------------------

bool N_inter::n_algebra::n_math::is_more_or_equal(double v1, double v2) {
    return is_equal(v1, v2) || is_more_than(v1, v2);
}
// --------------------------------------------------------
