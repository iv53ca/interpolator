#include "C_motion_section.h"
#include "N_inter/S_exception.h"
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_section::C_motion_section() {
    lines.clear();
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_section::~C_motion_section() {
    lines.clear();
}
// --------------------------------------------------------

int N_inter::n_motion_calc::n_types::C_motion_section::get_size() {
    return lines.size();
}
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_m_line> &N_inter::n_motion_calc::n_types::C_motion_section::get_lines() {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QVector<n_global_types::C_m_line> n_motion_calc::n_types::C_motion_section::get_lines()";
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Пустой список отрезков";
        throw exc;
    }
    return lines;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_types::C_motion_section::set_lines(QVector<n_global_types::C_m_line> new_lines) {
    lines = new_lines;
}
// --------------------------------------------------------

N_inter::n_global_types::C_point N_inter::n_motion_calc::n_types::C_motion_section::get_begin_point() {
    n_global_types::C_point result;
    result[n_global_types::X] = get_begin_line().m_first_point[n_global_types::X];
    result[n_global_types::Y] = get_begin_line().m_first_point[n_global_types::Y];
    return result;
}
// --------------------------------------------------------

N_inter::n_global_types::C_point N_inter::n_motion_calc::n_types::C_motion_section::get_end_point() {
    n_global_types::C_point result;
    result[n_global_types::X] = get_end_line().m_second_point[n_global_types::X];
    result[n_global_types::Y] = get_end_line().m_second_point[n_global_types::Y];
    return result;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_types::C_motion_section::set_begin_point(n_global_types::C_point new_point) {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Сегмент движения не содержит отрезков";
        throw exc;
    }

    lines.front().m_first_point = new_point;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_types::C_motion_section::set_end_point(n_global_types::C_point new_point) {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Сегмент движения не содержит отрезков";
        throw exc;
    }

    lines.back().m_second_point = new_point;
}
// --------------------------------------------------------

N_inter::n_global_types::C_m_line &N_inter::n_motion_calc::n_types::C_motion_section::get_begin_line() {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_global_types::C_m_line &n_motion_calc::n_types::C_motion_section::get_begin_line()";
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Сегмент движения не содержит отрезков";
        throw exc;
    }
    return lines[0];
}
// --------------------------------------------------------

N_inter::n_global_types::C_m_line &N_inter::n_motion_calc::n_types::C_motion_section::get_end_line() {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_global_types::C_m_line &n_motion_calc::n_types::C_motion_section::get_end_line()";
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Сегмент движения не содержит отрезков";
        throw exc;
    }
    return lines[lines.size() - 1];
}
// --------------------------------------------------------

QString N_inter::n_motion_calc::n_types::C_motion_section::m_to_string() {

}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_types::C_motion_section::insert_at(int index, n_global_types::C_m_line new_line) {
    if (index < 0) {
        // TODO: добавить исключение
    }
    if (index >= lines.size()) {
        // TODO: добавить исключение
    }
    lines.insert(index, new_line);
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_types::C_motion_section::push_back(n_global_types::C_m_line line) {
    lines.push_back(line);
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_types::C_motion_section::remove_at(int index) {
    if (index < 0) {
        // TODO: добавить исключение
    }
    if (index >= lines.size()) {
        // TODO: добавить исключение
    }
    lines.removeAt(index);
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_types::C_motion_section::clear() {
    lines.clear();
}
// --------------------------------------------------------

N_inter::n_global_types::C_m_line &N_inter::n_motion_calc::n_types::C_motion_section::operator[](int index) {
    if (index < 0) {
        N_inter::S_exception exc;
        exc.m_condition = "index < 0";
        exc.m_decision = "Выход за пределы массива";
        exc.m_calling_object = "n_global_types::C_m_line &n_motion_calc::n_types::C_motion_section::operator[](int index)";
        throw exc;
    }

    if (index >= lines.size()) {
        N_inter::S_exception exc;
        exc.m_condition = "index >= lines.size()";
        exc.m_decision = "Выход за пределы массива";
        exc.m_calling_object = "n_global_types::C_m_line &n_motion_calc::n_types::C_motion_section::operator[](int index)";
        throw exc;
    }

    return lines[index];
}
// --------------------------------------------------------
