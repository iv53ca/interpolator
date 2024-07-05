#include "n_angles.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_geom/n_lines.h"
// --------------------------------------------------------

using N_inter::S_exception;
using N_inter::n_global_types::C_point;
using N_inter::n_global_types::COORD;
// --------------------------------------------------------

// Проверка угла на равенство 0

bool N_inter::n_geom::n_angles::is_ultra_0_angle(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Если прямые не образуют угол, то кидать исключение
    if (!N_inter::n_algebra::n_math::is_equal(line1.m_second_point, line2.m_first_point)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!N_inter::n_algebra::n_math::is_equal(line1.m_second_point, line2.m_first_point)";
        exc.m_decision = "Прямые не образуют угол";
        throw exc;
    }

    // Если косинус в окрестности ошибки позиционирования для 1, то угол сверх-малый
    double cosinus = get_angle_cos(line1, line2);
    return N_inter::n_algebra::n_math::is_equal(cosinus, 1);
}
// --------------------------------------------------------

// Проверка угла на равенство 180 градусов

bool N_inter::n_geom::n_angles::is_ultra_180_angle(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Если прямые не образуют угол, то кидать исключение
    if (!N_inter::n_algebra::n_math::is_equal(line1.m_second_point, line2.m_first_point)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!N_inter::n_algebra::n_math::is_equal(line1.m_second_point, line2.m_first_point)";
        exc.m_decision = "Прямые не образуют угол";
        throw exc;
    }

    // Если косинус в окрестности ошибки позиционирования для 0, то угол сверх-развёрнутый
    double cosinus = get_angle_cos(line1, line2);
    return N_inter::n_algebra::n_math::is_equal(cosinus, -1);
}
// --------------------------------------------------------


// Проверка на образование угла + выдача косинуса угла между прямыми через скалярное произведение

double N_inter::n_geom::n_angles::get_angle_cos(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    // Если прямые не образуют угол, то кидать исключение
    if (!N_inter::n_algebra::n_math::is_equal(line1.m_second_point, line2.m_first_point)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!N_inter::n_algebra::n_math::is_equal(line1.m_second_point, line2.m_first_point)";
        exc.m_decision = "Прямые не образуют угол";
        throw exc;
    }

    C_point vec1 = line1.m_first_point - line1.m_second_point;
    C_point vec2 = line2.m_second_point - line2.m_first_point;

    double vec_length_1 = N_inter::n_geom::n_lines::get_abs_line(line1);
    double vec_length_2 = N_inter::n_geom::n_lines::get_abs_line(line2);

    return (vec1[COORD::X] * vec2[COORD::X] + vec1[COORD::Y] * vec2[COORD::Y]) / (vec_length_1 * vec_length_2);
}
// --------------------------------------------------------
