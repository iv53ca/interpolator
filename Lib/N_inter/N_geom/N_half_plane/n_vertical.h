#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_geom {
        namespace n_half_plane {
            // Полуплоскости, разделённые вертикальной прямой. Обнаружение горизонтальных биссектрис
            namespace n_vertical {
                // Проверка прямых на принадлежность одной вертикальной полуплоскости
                bool is_lines_in_one_half_plane(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

                // Поиск длин прямых (модуль разницы между координатами X граничных точек)
                double find_lines_width(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2, bool half_plane_orientation);

                // Укорачивание лежащих в одной горизонтальной полуплоскости отрезков до равных длин
                void short_one_half_plane_segments_to_equal_widths(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

                // Проверка биссектрисы угла на горизонтальную
                bool is_angle_bisector_horizontal(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

                // Проверка отрезков на принадлежность правой вертикальной полуплоскости
                bool is_lines_in_right_ver_half_plane(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);
            }
        }
    }
}
// --------------------------------------------------------
