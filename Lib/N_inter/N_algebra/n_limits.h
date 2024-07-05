#pragma once
// --------------------------------------------------------

#include <QVector>
#include "N_inter/N_motion_calc/n_motion_sections.h"

#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

// TODO: удалить пространство имён n_algebra
namespace N_inter {
    namespace n_algebra {
        namespace n_limits {
            // Максимум
            double max(double v1, double v2);

            // Минимум
            double min(double& v1, double& v2, double& v3, double& v4);
            double min(double& v1, double& v2);
            double min(QVector<double> &vec);
            double min(N_inter::n_global_types::C_m_line& line);

            // Максимум [Y]
            double max_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments);
            double max_y(N_inter::n_motion_calc::n_types::C_motion_section& segment);
            double max_y(QVector<N_inter::n_global_types::C_m_line> &lines);
            double max_y(QVector<N_inter::n_global_types::C_m_line>& lines, const int& begin, const int& end);
            double max_y(QVector<N_inter::n_global_types::C_point>& points);
            double max_y(N_inter::n_global_types::C_m_line& line);
            double max_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments, const int& begin, const int& end);

            // Минимум [Y]
            double min_y(QVector<N_inter::n_global_types::C_point>& points);
            double min_y(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments, const int& begin, const int& end);
            double min_y(N_inter::n_motion_calc::n_types::C_motion_section& segment);
            double min_y(N_inter::n_global_types::C_m_line& line);

            // Максимум [X]
            double max_x(N_inter::n_global_types::C_m_line& line);
        }
    }
}
// --------------------------------------------------------
