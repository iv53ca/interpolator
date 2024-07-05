#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_point_elevation {
            namespace {
                namespace n_aux {
                    enum KElevation {
                        Begin, End
                    };

                    void sign_segment_points_elevation(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments);
                    void master_sign_segment_points_elevation(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments, const int& begin, const int& end);
                    void sign_segment_points_elevation(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments, const int& begin, const int& end);

                    // Возвышение одной из крайних опорной точки сегмента
                    void segment_point_elevation(N_inter::n_motion_calc::n_types::C_motion_section& segment, KElevation a_begin_flag, double a_velocity);

                    void segment_begin_point_elevation(N_inter::n_motion_calc::n_types::C_motion_section& segment, double a_velocity); // Возвышение начальной опорной точки
                    void segment_end_point_elevation(N_inter::n_motion_calc::n_types::C_motion_section& segment, double a_velocity);   // Возвышение конечной опорной точки
                }
            }
            // Возвышение опроных точек вверх
            void elevationOfReferencePoints(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments);
            void elevationOfReferencePoints(N_inter::n_motion_calc::n_types::C_motion& motion);

        }
    }
}
// --------------------------------------------------------
