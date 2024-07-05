#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_alignment {
            namespace n_area {
                namespace n_simple {
                    namespace {
                        namespace n_aux {
                            // Корректировка основания сегмента
                            void correct_segment_base(N_inter::n_motion_calc::n_types::C_motion_section& segment, double dT);

                            // Максимальное допустимое время, которое можно отнять от прямоугольной составляющей
                            double rectangle_time(N_inter::n_motion_calc::n_types::C_motion_section& realSegment, N_inter::n_motion_calc::n_types::C_motion_section& newSegment);
                        }
                    }
                    // Выравнивание площадей
                    void align(N_inter::n_motion_calc::n_types::C_motion& realMotion, N_inter::n_motion_calc::n_types::C_motion& newMotion);
                }
            }
        }
    }
}
// --------------------------------------------------------
