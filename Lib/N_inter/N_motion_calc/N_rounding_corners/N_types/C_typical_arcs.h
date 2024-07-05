#pragma once
// --------------------------------------------------------

#include <QVector>
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_types/C_arc_circle.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_rounding_corners {
            namespace n_types {
                class C_typical_arcs {
                public:
                    // TODO: продумать механизм инкапсуляции

                    // Типовые дуги для вписывания
                    QVector<N_inter::n_motion_calc::n_rounding_corners::n_types::C_arc_circle> left_typical_arcs;
                    QVector<N_inter::n_motion_calc::n_rounding_corners::n_types::C_arc_circle> right_typical_arcs;

                    // Минимально допустимые ширины прямоугольных составляющих трапеций трапеций
                    QVector<double> min_widths;

                    // Минимально допустимые высоты трапеций
                    QVector<double> min_heights; // TODO: переименовать

                    // Минимальная ширина прямоугольной составляющей трапеции
                    double get_min_width_for_axis(int axis);

                    // Минимальная высота трапеции
                    double get_min_high_for_axis(int axis);

                    // Запись типовых значений
                    void write();

                private:
                    // Запись типовых дуг для вписывания
                    void write_typical_arcs();

                    // Запись минимально допустимые ширины прямоугольных составляющих трапеций трапеций и минимально допустимые высоты трапеций
                    void write_min_values();

                    // Типовая наклонная прямая
                    QVector<N_inter::n_global_types::C_m_line> get_type_lines(int axis);
                };
            }
        }
    }
}
// --------------------------------------------------------
