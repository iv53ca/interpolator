#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_vector.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_global_types/S_circle/S_inter_circle.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_profiler {
        namespace n_trajectory {
            namespace n_prof {
                namespace {
                    namespace n_aux {
                        QVector<N_inter::n_global_types::C_m_line> master_inter(QVector<N_inter::n_global_types::C_m_line>& lines, double max_error, int split_segments_count);

                        void segments_inter(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2, n_global_types::S_inter_circle& circle, QVector<n_global_types::C_point>& circlePoints, bool& stat, double max_error, int split_segments_count); // Профилирование двух отрезков
                    }
                }
                QVector<N_inter::n_global_types::C_m_line> inter(QVector<N_inter::n_global_types::C_m_line>& lines, double max_error, int split_segments_count);
            }
        }
    }
}
// --------------------------------------------------------
