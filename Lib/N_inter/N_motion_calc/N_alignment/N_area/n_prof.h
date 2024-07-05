#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion.h"
#include "N_inter/N_global_types/C_point.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_alignment {
            namespace n_area {
                namespace n_prof {
                    namespace {
                        namespace n_aux {
                            // Уточнение площади сегментов
                            void binary_area_correct(N_inter::n_motion_calc::n_types::C_motion_section& realSegment, N_inter::n_motion_calc::n_types::C_motion_section& newSegment);
                            void proxy_binary_area_correct(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &realSegments, QVector<N_inter::n_motion_calc::n_types::C_motion_section> &newSegments);

                            // Максимальное допустимое время, которое можно отнять от прямоугольной составляющей
                            double rectangle_time(N_inter::n_motion_calc::n_types::C_motion_section& segment, N_inter::n_motion_calc::n_types::C_motion_section& true_segment);

                            // Корректирование площади отдельного сегмента
                            void correct_segment_rectangle_area(N_inter::n_motion_calc::n_types::C_motion_section& segment, double& rectangle_time);

                            // Получение нижней точки пересечения условных границ сегмента
                            N_inter::n_global_types::C_point get_low_section_borders_intersection_point(N_inter::n_motion_calc::n_types::C_motion_section& section, double leftA, double rightA);
                        }
                    }
                    // Уточнение площади сегментов
                    void binary_correct(N_inter::n_motion_calc::n_types::C_motion& realMotion, N_inter::n_motion_calc::n_types::C_motion& newMotion);

                    // Корректировка площиди прямоугольных составляющих
                    void correct_rectangle_area_part(N_inter::n_motion_calc::n_types::C_motion& motion, N_inter::n_motion_calc::n_types::C_motion& real_motion);
                }
            }
        }
    }
}
// --------------------------------------------------------
