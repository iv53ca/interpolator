#include "n_velocities.h"
#include "N_inter/N_geom/n_lines.h"
#include <cmath>
// --------------------------------------------------------

double N_inter::n_motion_calc::n_velocities::get_speed_projection(n_global_types::C_m_line &line, double &F, int &axis) {
    // Направляющий вектор для оси абсцисс
    n_global_types::C_m_line iVector;
    iVector.m_first_point[n_global_types::X] = 0;
    iVector.m_first_point[n_global_types::Y] = 0;
    iVector.m_second_point[n_global_types::X] = 1;
    iVector.m_second_point[n_global_types::Y] = 0;

    // Угол для вектора скорости
    double angle = n_geom::n_lines::get_rad_angle(line, iVector);

    // Проекция скорости
    double projectionVel = F;

    // Ось абсцисс
    switch(axis) {
    case n_global_types::X:
        projectionVel = F * cos(angle);
        break;
    case n_global_types::Y:
        projectionVel = F * sin(angle);
        break;
    default:
        // TODO: make exception ось не добавлена
        projectionVel = 0;
        break;
    }

    return projectionVel;
}
// --------------------------------------------------------
