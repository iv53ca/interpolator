#pragma once
// --------------------------------------------------------

#include <QVector>
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_rounding_corners {
            namespace n_types {
                enum TRAPEZOID_SEG {
                    LEFT = 0,
                    CENTER = 1,
                    RIGHT = 2
                };
                // --------------------------------------------------------

                class C_trapezoid {
                public:
                    N_inter::n_global_types::C_point first_angle_pos;  // Первый угол
                    N_inter::n_global_types::C_point second_angle_pos; // Второй угол

                    QVector<N_inter::n_global_types::C_m_line> lines; // Образующие трапецию отрезки

                    N_inter::n_global_types::C_m_line &operator[](int index);
                };
            }
        }
    }
}
// --------------------------------------------------------
