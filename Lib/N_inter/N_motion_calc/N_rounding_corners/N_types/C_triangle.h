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
                enum TRIAGNLE_SEG {
                    LEFT = 0,
                    RIGHT = 1
                };
                // --------------------------------------------------------

                class C_triangle {
                public:
                    N_inter::n_global_types::C_point angle_pos;  // Угол

                    QVector<N_inter::n_global_types::C_m_line> lines; // Образующие треугольник отрезки

                    N_inter::n_global_types::C_m_line &operator[](int index);
                };
            }
        }
    }
}
// --------------------------------------------------------
