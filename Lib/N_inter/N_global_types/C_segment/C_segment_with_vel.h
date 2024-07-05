#pragma once
// --------------------------------------------------------

#include "C_segment.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        struct C_segment_with_vel : public C_segment {
        public:
            C_segment_with_vel();
            QString m_to_string();
        };
    }
}
// --------------------------------------------------------
