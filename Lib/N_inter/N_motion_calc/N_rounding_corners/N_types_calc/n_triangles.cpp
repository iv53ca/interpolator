#include "n_triangles.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_geom/n_lines.h"
// --------------------------------------------------------

using N_inter::n_global_types::COORD;
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_triangles::is_triangle(QVector<n_global_types::C_m_line> &lines) {
    // Линий 2
    if (lines.size() != 2) {
        return false;
    }

    // Наклон у крайних линий
    double x_length_1 = lines[0].m_second_point[COORD::X] - lines[0].m_first_point[COORD::X];
    double x_length_2 = lines[1].m_second_point[COORD::X] - lines[1].m_first_point[COORD::X];

    double y_length_1 = lines[0].m_second_point[COORD::Y] - lines[0].m_first_point[COORD::Y];
    double y_length_2 = lines[1].m_first_point[COORD::Y] - lines[1].m_second_point[COORD::Y];

    if (!N_inter::n_algebra::n_math::is_equal(x_length_1, x_length_2)) {
        return false;
    }
    if (!N_inter::n_algebra::n_math::is_equal(y_length_1, y_length_2)) {
        return false;
    }

    // Начальная и конечная точка нули
    if (!N_inter::n_algebra::n_math::is_equal(lines[0].m_first_point[COORD::X], 0)) {
        return false;
    }
    if (!N_inter::n_algebra::n_math::is_equal(lines[1].m_second_point[COORD::X], 0)) {
        return false;
    }

    // Точки пересечения
    if (lines[0].m_second_point != lines[1].m_first_point) {
        return false;
    }

    return true;
}
// --------------------------------------------------------
