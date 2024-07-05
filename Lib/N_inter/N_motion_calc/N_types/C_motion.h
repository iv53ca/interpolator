#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_types {
            class C_motion {
                QVector<QVector<n_motion_calc::n_types::C_motion_section>> motion;
            public:
                C_motion();
                ~C_motion();

                C_motion &operator=(const C_motion& new_motion);
                QVector<n_motion_calc::n_types::C_motion_section> &operator[](int axis_num);
            };
        }
    }
}
// --------------------------------------------------------
