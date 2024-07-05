#include "C_xy_line.h"
// --------------------------------------------------------

N_inter::n_global_types::C_xy_line::C_xy_line() { A = B = C = 0; }
// --------------------------------------------------------

QString N_inter::n_global_types::C_xy_line::m_to_string() {
    return QString("[%1, %2]").arg(m_first_point.m_to_string()).arg(m_second_point.m_to_string());
}
// --------------------------------------------------------
