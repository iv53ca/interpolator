#include "n_limits.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
#include "N_inter/S_exception.h"
// --------------------------------------------------------

using N_inter::S_exception;
// --------------------------------------------------------
//Функция нахождения максимального из двух чисел

double N_inter::n_algebra::n_limits::max(double v1, double v2) {
    if (v1 > v2) {
        return v1;
    }

    return v2;
}
// --------------------------------------------------------
//Функция нахождения минимального из четырех чисел

double N_inter::n_algebra::n_limits::min(double &v1, double &v2, double &v3, double &v4) {
    double r = v1;

    if (v2 < r) {
        r = v2;
    }
    if (v3 < r) {
        r = v3;
    }
    if (v4 < r) {
        r = v4;
    }

    return r;
}
// --------------------------------------------------------
//Функция нахождения минимального из двух чисел

double N_inter::n_algebra::n_limits::min(double &v1, double &v2) {
    if (v1 < v2) {
        return v1;
    }

    return v2;
}
// --------------------------------------------------------
// Функция нахождения минимального элемента вектора

double N_inter::n_algebra::n_limits::min(QVector<double> &vec) {
    if (vec.size() == 0) {
        S_exception exc;
        exc.m_calling_object = "double N_inter::n_algebra::n_limits::min(QVector<double> &vec)";
        exc.m_condition = "vec.size() == 0";
        exc.m_decision = "Нулевой вектор";
    }
    double result = vec[0];
    for (int i = 0; i < vec.size(); i++) {
        if (result > vec[i]) {
            result = vec[i];
        }
    }
    return result;
}
// --------------------------------------------------------
// Получает минимумальное значение ординаты прямой (очевидно, выбор из двух точек производится за счет строгой монотонности линии)

double N_inter::n_algebra::n_limits::min(n_global_types::C_m_line &line) {
    double y1 = line.m_first_point[n_global_types::Y], y2 = line.m_second_point[n_global_types::Y];
    if (y1 < y2) {
        return y1;
    }

    return y2;
}
// --------------------------------------------------------
// Бросаем исключение, если вектор сегментов пуст, иначе выводим максимальную координату по У среди всех сегментов

double N_inter::n_algebra::n_limits::max_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments) {
    if (segments.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::max_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments)";
        exc.m_condition = "segments.size() == 0";
        exc.m_decision = "Список сегментов пустой";
        throw exc;
    }

    double _max_d = max_y(segments[0].get_lines());
    for (int i = 1; i < segments.size(); i++) {
        double _temp_d = max_y(segments[i]);
        if (N_inter::n_algebra::n_math::is_more_than(_temp_d, _max_d)) {
            _max_d = _temp_d;
        }
    }

    return _max_d;
}
// --------------------------------------------------------
// Выводим максимальную координату У в одном сегменте

double N_inter::n_algebra::n_limits::max_y(N_inter::n_motion_calc::n_types::C_motion_section
 &segment) {
    return max_y(segment.get_lines());
}
// --------------------------------------------------------
// Выводим максимальную координату У среди всех линий в векторе

double N_inter::n_algebra::n_limits::max_y(QVector<n_global_types::C_m_line> &lines) {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::max_y(QVector<n_global_types::C_m_line> &lines)";
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Список линий пустой";
        throw exc;
    }

    double result = 0;
    for (int i = 0; i < lines.size(); i++) {
        double v = max(lines[i].m_first_point[n_global_types::Y], lines[i].m_second_point[n_global_types::Y]);
        if (result < v) {
            result = v;
        }
    }

    return result;
}
// --------------------------------------------------------
// Вопрос, чем глобально функции отличаются кроме эксептов и почему не кидает переопределение - непонятно, но здесь мы тоже ишем среди вектора
// отрезков максимальную У координату, только с условие непустоты вектора, что начало не превышает конец и что мы не выходим за границы вектора

double N_inter::n_algebra::n_limits::max_y(QVector<n_global_types::C_m_line> &lines, const int &begin, const int &end) {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::max_y(QVector<n_global_types::C_m_line> &lines, const int &begin, const int &end)";
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Вектор отрезков пустой";
        throw exc;
    }
    else if (begin > end) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::max_y(QVector<n_global_types::C_m_line> &lines, const int &begin, const int &end)";
        exc.m_condition = "begin > end";
        exc.m_decision = "Начальная граница превышает конечную";
        throw exc;
    }
    else if ((begin >= lines.size()) || (end >= lines.size())) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::max_y(QVector<n_global_types::C_m_line> &lines, const int &begin, const int &end)";
        exc.m_condition = "(begin >= lines.size()) || (end >= lines.size())";
        exc.m_decision = "Выход за границы вектора отрезков";
        throw exc;
    }

    double result = max_y(lines[begin]);
    for (int i = begin; i <= end; i++) {
       double local_max = max_y(lines[i]);
        if (N_inter::n_algebra::n_math::is_more_than(local_max, result)) {
           result = local_max;
       }
    }

    return result;
}
// --------------------------------------------------------
// Ищем максимумальную У координату среди вектора точек

double N_inter::n_algebra::n_limits::max_y(QVector<n_global_types::C_point> &points) {
    if (points.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::max_y(QVector<n_global_types::C_point> &points)";
        exc.m_condition = "points.size() == 0";
        exc.m_decision = "Массив точек пустой";
        throw exc;
    }
    double max = points[0][n_global_types::Y];
    for (int i = 0; i < points.size(); i++) {
        if (N_inter::n_algebra::n_math::is_more_than(points[i][n_global_types::Y], max)) {
            max = points[i][n_global_types::Y];
        }
    }
    return max;
}
// --------------------------------------------------------
// Ишем максимальную координату вектора отрезков при условии добавления в него нового отрезка

double N_inter::n_algebra::n_limits::max_y(n_global_types::C_m_line &line) {
    QVector<N_inter::n_global_types::C_m_line> lines;
    lines.push_back(line);

    return max_y(lines);
}
// --------------------------------------------------------
// Вопрос, чем глобально функции отличаются кроме эксептов и почему не кидает переопределение - непонятно, но здесь мы тоже ишем среди вектора
// сегментов максимальную У координату, только с условие непустоты вектора, что начало не превышает конец и что мы не выходим за границы вектора

double N_inter::n_algebra::n_limits::max_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end) {
    if (segments.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::max_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end)";
        exc.m_condition = "segments.size() == 0";
        exc.m_decision = "Вектор отрезков пустой";
        throw exc;
    }
    else if (begin > end) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::max_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end)";
        exc.m_condition = "begin > end";
        exc.m_decision = "Начальная граница превышает конечную";
        throw exc;
    }
    else if ((begin >= segments.size()) || (end >= segments.size())) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::max_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end)";
        exc.m_condition = "(begin >= segments.size()) || (end >= segments.size())";
        exc.m_decision = "Выход за границы вектора отрезков";
        throw exc;
    }
    double result = max_y(segments[begin].get_lines());
    for (int i = begin; i <= end; i++) {
        double local_max = max_y(segments[i]);
        if (N_inter::n_algebra::n_math::is_more_than(local_max, result)) {
            result = local_max;
        }
    }

    return result;
}
// --------------------------------------------------------
// Ищем минимальную У координату среди вектора точек с эксептом о нулевом размере массива точек

double N_inter::n_algebra::n_limits::min_y(QVector<n_global_types::C_point> &points) {
    if (points.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::min_y(QVector<n_global_types::C_point> &points)";
        exc.m_condition = "points.size() == 0";
        exc.m_decision = "Массив точек пустой";
        throw exc;
    }

    double result = points[0][n_global_types::Y];
    for (int i = 0; i < points.size(); i++) {
        if (N_inter::n_algebra::n_math::is_more_than(result, points[i][n_global_types::Y])) {
            result = points[i][n_global_types::Y];
        }
    }
    return result;
}
// --------------------------------------------------------
// Поиск минимальной У координаты в векторе сегментов с эксептами о нулевом размере, превышении начальной границей конечной границы, выходе
// за границы вектора

double N_inter::n_algebra::n_limits::min_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end) {
    if (segments.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::min_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end)";
        exc.m_condition = "segments.size() == 0";
        exc.m_decision = "Вектор отрезков пустой";
        throw exc;
    }
    else if (begin > end) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::min_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end)";
        exc.m_condition = "begin > end";
        exc.m_decision = "Начальная граница превышает конечную";
        throw exc;
    }
    else if ((begin >= segments.size()) || (end >= segments.size())) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::min_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, const int &begin, const int &end)";
        exc.m_condition = "(begin >= segments.size()) || (end >= segments.size())";
        exc.m_decision = "Выход за границы вектора отрезков";
        throw exc;
    }

    double result = min_y(segments[begin]);
    for (int i = begin; i <= end; i++) {
        double local_min = min_y(segments[i]);
        if (N_inter::n_algebra::n_math::is_more_than(result, local_min)) {
            result = local_min;
        }
    }

    return result;
}
// --------------------------------------------------------
// Находим минимум У координаты внутри одного сегмента с эксептом о пустом сегменте

double N_inter::n_algebra::n_limits::min_y(N_inter::n_motion_calc::n_types::C_motion_section &segment) {
    if (segment.get_size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double n_algebra::n_limits::min_y(N_inter::n_motion_calc::n_types::C_motion_section &segment)";
        exc.m_condition = "segment.get_size() == 0";
        exc.m_decision = "Массив точек пустой";
        throw exc;
    }

    double _result = min_y(segment[0]);
    for (int i = 0; i < segment.get_size(); i++) {
        if (N_inter::n_algebra::n_math::is_more_than(_result, min_y(segment[i]))) {
            _result = min_y(segment[i]);
        }
    }

    return _result;
}
// --------------------------------------------------------
// Возвращаем минимальную У координату в одной линии (сравниваем конечную и начальную точки)

double N_inter::n_algebra::n_limits::min_y(n_global_types::C_m_line &line) {
    if (N_inter::n_algebra::n_math::is_more_than(line.m_first_point[n_global_types::Y], line.m_second_point[n_global_types::Y])) {
        return line.m_second_point[n_global_types::Y];
    }
    return line.m_first_point[n_global_types::Y];
}
// --------------------------------------------------------
// Возврашаем максимальную используемую Х координату

double N_inter::n_algebra::n_limits::max_x(n_global_types::C_m_line &line) {
    if (N_inter::n_algebra::n_math::is_more_than(line.m_first_point[n_global_types::X], line.m_second_point[n_global_types::X])) {
        return line.m_first_point[n_global_types::X];
    }

    return line.m_second_point[n_global_types::X];
}
// --------------------------------------------------------
