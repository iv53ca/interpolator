#pragma once
// --------------------------------------------------------

#include "C_point.h"
#include <QVector>
#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        struct S_trajectory_input : public N_inter::C_object  {
            QString trajectory; // Траектория
            bool prof_stat; // Нужно ли применять алгоритм профилирования
            QString m_to_string() {}
        };
    }
}
// --------------------------------------------------------
