#pragma once
// --------------------------------------------------------

#include <QVector>
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_global_types/S_circle/S_inter_circle.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_geom {
        namespace n_circles {
            // Получение вписанной в образованный прямыми угол line1 и line2 окружности
            n_global_types::S_inter_circle fit(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2, bool& stat, double max_error);

            // Сортировка точек окружности в последовательном представлении
            void sort_circle_points(QVector<n_global_types::C_point>& circlePoints, n_global_types::S_inter_circle& circle, n_global_types::C_point& point1, n_global_types::C_point& point2, int split_segments_count);
        }
    }
}
// --------------------------------------------------------
