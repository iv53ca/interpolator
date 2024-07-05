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
                class C_arc_circle {
                public:
                    N_inter::n_global_types::C_point angle_position; // Точка восстановления полуокружности
                    QVector<N_inter::n_global_types::C_m_line> arc;  // Дуга окружности

                    int size(); // Кол-во отрезков

                    N_inter::n_global_types::C_m_line &operator[](int index);
                };
            }
        }
    }
}
// --------------------------------------------------------

