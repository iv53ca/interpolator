#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_point.h"
#include "N_inter/C_object.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        struct C_segment : public N_inter::C_object {
        public:
            N_inter::n_global_types::C_point m_first_point;
            N_inter::n_global_types::C_point m_second_point;

            virtual QString m_to_string();
        };
    }
}
// --------------------------------------------------------
