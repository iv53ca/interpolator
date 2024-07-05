#pragma once
// --------------------------------------------------------

#include "C_point.h"
#include <vector>
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        struct S_track : public N_inter::C_object  {
            std::vector<N_inter::n_global_types::C_point> track;
            N_inter::n_global_types::C_point &operator[](int index);
        };
    }
}
// --------------------------------------------------------
