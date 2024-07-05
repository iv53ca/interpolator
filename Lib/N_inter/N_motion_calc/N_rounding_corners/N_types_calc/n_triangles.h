#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_rounding_corners/N_types/C_arc_circle.h"
#include "N_inter/N_global_types/C_point.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_rounding_corners {
            namespace n_types_calc {
                namespace n_triangles {
                    // Проверка совокупности отрезков на треугольник
                    bool is_triangle(QVector<N_inter::n_global_types::C_m_line>& lines);
                }
            }
        }
    }
}
// --------------------------------------------------------
