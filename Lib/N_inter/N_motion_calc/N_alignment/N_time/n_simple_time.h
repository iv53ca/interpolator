#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_alignment {
            namespace n_time {
                namespace n_simple_time {
                    // Выравнивание сегментов по времени
                    void align(N_inter::n_motion_calc::n_types::C_motion& motion);

                    // Выравнивание отрезков по времени вдоль одной из осей
                    void align_segments(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments);
                }
            }
        }
    }
}
// --------------------------------------------------------
