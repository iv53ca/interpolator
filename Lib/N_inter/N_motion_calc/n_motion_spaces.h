#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_motion_spaces {
            namespace {
                namespace n_aux {
                    void remove(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments);
                    void remove(N_inter::n_motion_calc::n_types::C_motion_section& segment);
                    void remove(N_inter::n_motion_calc::n_types::C_motion_section& first_segment, N_inter::n_motion_calc::n_types::C_motion_section& next_segment);
                }
            }
            void remove(N_inter::n_motion_calc::n_types::C_motion& motion);
        }
    }
}
// --------------------------------------------------------
