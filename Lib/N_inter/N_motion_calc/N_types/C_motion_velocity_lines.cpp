#include "C_motion_velocity_lines.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/S_exception.h"
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_velocity_lines::C_motion_velocity_lines() {
    for (int i = 0; i < n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        QVector<n_global_types::C_m_line> temp;
        lines.push_back(temp);
    }
}
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_m_line> &N_inter::n_motion_calc::n_types::C_motion_velocity_lines::operator[](int index) {
    if ((index < 0) || (index > lines.size())) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QVector<n_global_types::C_m_line> &n_motion_calc::n_types::C_motion_velocity_lines::operator[](int index)";
        exc.m_condition = "(index < 0) || (index > lines.size())";
        exc.m_decision = "Выход за пределы границ массива";
        throw exc;
    }
    return lines[index];
}
// --------------------------------------------------------

N_inter::n_global_types::C_m_line &N_inter::n_motion_calc::n_types::C_motion_velocity_lines::operator()(const int i, const int j) {
    if ((i < 0) || (i > lines.size())) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_types::C_m_line &S_motion_velocity_lines::operator()(const int i, const int j)";
        exc.m_condition = "(i < 0) || (i > lines.size())";
        exc.m_decision = "Выход за пределы границ массива";
        throw exc;
    }

    if ((j < 0) || (j > lines[i].size())) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_types::C_m_line &S_motion_velocity_lines::operator()(const int i, const int j)";
        exc.m_condition = "((j < 0) || (j > lines[i].size())";
        exc.m_decision = "Выход за пределы границ массива";
        throw exc;
    }

    return lines[i][j];
}
// --------------------------------------------------------

QString N_inter::n_motion_calc::n_types::C_motion_velocity_lines::m_to_string() {

}
// --------------------------------------------------------

