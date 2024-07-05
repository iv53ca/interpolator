#pragma once
// --------------------------------------------------------

#include "C_xy_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        class C_xy_line_with_vel : public C_xy_line {
        public:
            C_xy_line_with_vel();
            double velocity;

            QString m_to_string();
        };
    }
}
// --------------------------------------------------------
