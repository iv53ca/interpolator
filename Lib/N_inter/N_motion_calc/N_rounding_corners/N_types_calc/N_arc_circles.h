#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_rounding_corners/N_types/C_arc_circle.h"
#include "N_inter/N_global_types/C_point.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_rounding_corners {
            namespace n_types_calc {
                namespace n_arc_circles {
                    // Параллельный перенос дуги окружности в новую точку
                    void move(N_inter::n_motion_calc::n_rounding_corners::n_types::C_arc_circle &arr_circle, N_inter::n_global_types::C_point new_angle_position);

                    // Отображение дуги вдоль оси Y
                    void mirroring_along_axis_y(n_types::C_arc_circle &arr_circle);
                }
            }
        }
    }
}
// --------------------------------------------------------
