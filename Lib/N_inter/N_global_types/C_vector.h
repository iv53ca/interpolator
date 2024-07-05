#pragma once
// --------------------------------------------------------

#include "C_point.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        class C_vector {
            N_inter::n_global_types::C_point m_coord;
        public:
            C_vector();
            ~C_vector();

            double &operator[](int a_index);
        };
    }
}
// --------------------------------------------------------
