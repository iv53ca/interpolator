#include "C_xy_line_with_vel.h"
#include <QString>
// --------------------------------------------------------

N_inter::n_global_types::C_xy_line_with_vel::C_xy_line_with_vel() {}
// --------------------------------------------------------

QString N_inter::n_global_types::C_xy_line_with_vel::m_to_string() {
    return QString("[%1, %2]").arg(m_first_point.m_to_string()).arg(m_second_point.m_to_string());
}
// --------------------------------------------------------
