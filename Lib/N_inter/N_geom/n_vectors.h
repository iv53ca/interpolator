#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_vector.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_geom {
        namespace n_vectors {
            // Получение отрезка, лежащего на биссектрисе угла, образованного прямыми line1 и line2
            N_inter::n_global_types::C_m_line get_angle_bisector(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

            // Проверка на нахождение вектора vector в пределах образованного векторами lineVec1 и lineVec2 угла
            bool is_in_angle(N_inter::n_global_types::C_vector& lineVec1, N_inter::n_global_types::C_vector& lineVec2, N_inter::n_global_types::C_vector& vector);

            // Модуль векторного произведения векторов vector1 и vector2
            double get_vec_mul(N_inter::n_global_types::C_vector& vector1, N_inter::n_global_types::C_vector& vector2);
        }
    }
}
// --------------------------------------------------------
