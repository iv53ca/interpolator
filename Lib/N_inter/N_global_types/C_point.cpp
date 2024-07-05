#include "C_point.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_algebra/n_math.h"
// --------------------------------------------------------

// TODO убрать этот и другие
using N_inter::n_data::n_motion_vars::n_calc_vars::axis_count;

// А вот это убирать не надо
using N_inter::n_global_types::COORD;
// --------------------------------------------------------

N_inter::n_global_types::C_point::C_point() {
    if (axis_count <= 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_global_types::C_point::C_point()";
        exc.m_condition = "axis_count <= 0";
        exc.m_decision = "Отрицательное количество осей";
        throw exc;
    }
    else if (axis_count >= N_inter::n_data::n_motion_vars::n_calc_vars::max_axis_count) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_global_types::C_point::C_point()";
        exc.m_condition = "axis_count >= n_data::n_motion_vars::n_calc_vars::max_axis_count";
        exc.m_decision = "Слишком большое количество осей";
        throw exc;
    }

    m_position.clear();
    for (int i = 0; i < axis_count; i++) {
        m_position.push_back(0);
    }
}
// --------------------------------------------------------

N_inter::n_global_types::C_point::C_point(int a_value) {
    if (axis_count <= 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_global_types::C_point::C_point(int a_value)";
        exc.m_condition = "axis_count <= 0";
        exc.m_decision = "Отрицательное количество осей";
        throw exc;
    }
    else if (axis_count >= N_inter::n_data::n_motion_vars::n_calc_vars::max_axis_count) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_global_types::C_point::C_point(int a_value)";
        exc.m_condition = "axis_count >= n_data::n_motion_vars::n_calc_vars::max_axis_count";
        exc.m_decision = "Слишком большое количество осей";
        throw exc;
    }

    m_position.clear();
    for (int i = 0; i < axis_count; i++) {
        m_position.push_back(a_value);
    }
}
// --------------------------------------------------------

N_inter::n_global_types::C_point::~C_point() {
    m_position.clear();
}
// --------------------------------------------------------

double &N_inter::n_global_types::C_point::operator[](int index) {
    if (index < 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double &n_global_types::C_point::operator[](int index)";
        exc.m_condition = "index < 0";
        exc.m_decision = "Отрицательный индекс";
        throw exc;
    }
    else if (index >= axis_count) {
        N_inter::S_exception exc;
        exc.m_calling_object = "double &n_global_types::C_point::operator[](int index)";
        exc.m_condition = "index >= axis_count";
        exc.m_decision = "Индекс превышает размер массива";
        throw exc;
    }
    return m_position[index];
}
// --------------------------------------------------------

N_inter::n_global_types::C_point &N_inter::n_global_types::C_point::operator=(const C_point &new_point) {
    for (int i = 0; i < axis_count; i++) {
        this->m_position[i] = new_point.m_position[i];
    }
    return *(this);
}
// --------------------------------------------------------

bool N_inter::n_global_types::C_point::operator==(C_point &point) {
    for (int axis = 0; axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; axis++) {
        if (!N_inter::n_algebra::n_math::is_equal((*this)[axis], point[axis])) {
            return false;
        }
    }
    return true;
}
// --------------------------------------------------------

bool N_inter::n_global_types::C_point::operator!=(C_point &point) {
    return !((*this) == point);
}
// --------------------------------------------------------

N_inter::n_global_types::C_point N_inter::n_global_types::C_point::operator-(C_point &sec_point) {
    C_point result;

    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        result[i] = (*this)[i] -sec_point[i];
    }

    return result;
}
// --------------------------------------------------------

N_inter::n_global_types::C_point N_inter::n_global_types::C_point::operator+(C_point &sec_point) {
    C_point result;

    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        result[i] = (*this)[i] + sec_point[i];
    }

    return result;
}
// --------------------------------------------------------

QString N_inter::n_global_types::C_point::m_to_string() {
    QString res = "(";
    for (int i = 0; i < axis_count; i++) {
        res = res + QString::number(m_position[i]) + ", ";
    }
    res = res.remove(res.size() - 2, 2);
    res = res + ")";
    return res;
}
// --------------------------------------------------------
