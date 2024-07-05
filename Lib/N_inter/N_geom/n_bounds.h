#pragma once
// --------------------------------------------------------

#include <QVector>
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/S_bounds.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_geom {
        namespace n_bounds {
            // Нахождение границ
            n_global_types::S_bounds find(N_inter::n_global_types::C_m_line& line);
            n_global_types::S_bounds find(N_inter::n_global_types::C_m_line& line1, n_global_types::C_m_line& line2);
            n_global_types::S_bounds find(QVector<n_global_types::C_m_line>& lines);

            // Корректировка границ для первой линии (line1) в зависимости от значения точки касания interPoint
            n_global_types::C_m_line correct_first_line_bound(n_global_types::C_m_line& line1, n_global_types::C_m_line& line2, n_global_types::C_point& interPoint);

            // Корректировка границ для второй линии (line2) в зависимости от значения точки касания interPoint
            n_global_types::C_m_line correct_second_line_bound(n_global_types::C_m_line& line1, n_global_types::C_m_line& line2, n_global_types::C_point& interPoint);
        }
    }
}
// --------------------------------------------------------
