#pragma once
// --------------------------------------------------------

#include <QVector>
#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_geom {
        namespace n_angles {
            // Проверка отрезков на образование сверх-маленького угла (косинус стремится к 1)
            bool is_ultra_0_angle(N_inter::n_global_types::C_m_line &line1, N_inter::n_global_types::C_m_line &line2);

            // Проверка отрезков на образование сверх-развёрнутого угла (косинус стремится к -1)
            bool is_ultra_180_angle(N_inter::n_global_types::C_m_line &line1, N_inter::n_global_types::C_m_line &line2);

            // Получение косинуса образованного прямыми line1 и line2 угла
            double get_angle_cos(N_inter::n_global_types::C_m_line &line1, N_inter::n_global_types::C_m_line &line2);
        }
    }
}
// --------------------------------------------------------
