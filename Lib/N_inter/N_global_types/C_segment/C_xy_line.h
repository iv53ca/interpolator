#pragma once
// --------------------------------------------------------

#include "C_segment.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        class C_xy_line : public n_global_types::C_segment {
        public:
            C_xy_line();
            QString m_to_string();

            double A, B, C;
        };
    }
}
// --------------------------------------------------------
