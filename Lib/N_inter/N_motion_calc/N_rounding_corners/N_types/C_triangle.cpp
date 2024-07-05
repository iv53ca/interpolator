#include "C_triangle.h"
// --------------------------------------------------------

#include "N_inter/S_exception.h"
// --------------------------------------------------------

N_inter::n_global_types::C_m_line &N_inter::n_motion_calc::n_rounding_corners::n_types::C_triangle::operator[](int index) {
    if (index < 0) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "index < 0";
        exc.m_decision = "Отрицательный индекс";
        throw exc;
    }

    if (index > 3) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "index > 2";
        exc.m_decision = "Выход за пределы треугольника";
        throw exc;
    }

    return lines[index];
}
// --------------------------------------------------------
