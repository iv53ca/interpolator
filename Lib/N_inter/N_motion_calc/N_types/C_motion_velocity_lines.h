#pragma once
// --------------------------------------------------------

#include <QVector>
#include "N_inter/C_object.h"
#include "N_inter/N_global_types/C_segment/C_m_lines.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_types {
            class C_motion_velocity_lines : public N_inter::C_object {
                QVector<N_inter::n_global_types::C_m_lines> lines;
            public:
                C_motion_velocity_lines();
                QVector<N_inter::n_global_types::C_m_line> &operator[](int index);
                N_inter::n_global_types::C_m_line &operator()(const int i, const int j);
                QString m_to_string();
            };
        }
    }
}
// --------------------------------------------------------
