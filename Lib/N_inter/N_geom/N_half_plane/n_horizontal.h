#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_geom {
        namespace n_half_plane {
            // Полуплоскости, разделённые горизонтальной прямой. Обнаружение вертикальных биссектрис
            namespace n_horizontal {
                // Проверка прямых на принадлежность одной горизонтальной полуплоскости
                bool is_lines_in_one_half_plane(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

                // Поиск высот прямых (модуль разницы между координатами Y граничных точек)
                double find_lines_height(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2, bool half_plane_orientation);

                // Укорачивание лежащих в одной горизонтальной полуплоскости отрезков до равных высот
                void short_one_half_plane_segments_to_equal_heights(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

                // Проверка биссектрисы угла на вертикальную
                bool is_angle_bisector_vertical(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

                // Проверка отрезков на принадлежность верхней горизонтальной полуплоскости
                bool is_lines_in_upper_hor_half_plane(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);
            }
        }
    }
}
// --------------------------------------------------------
