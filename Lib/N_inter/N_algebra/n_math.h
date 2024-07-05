#pragma once
// --------------------------------------------------------

#include <QVector>
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
// --------------------------------------------------------

// TODO: удалить пространство имён n_algebra
namespace N_inter {
    namespace n_algebra {
        namespace n_math {
            // Проверка чисел на равенство
            bool is_equal(QVector<double>& values);
            bool is_equal(double t1, double t2);
            bool is_equal(n_global_types::C_point &point1, n_global_types::C_point &point2);

            // Округление значений в погрешности ошибки вычисления до нуля
            void to_necessary_zero(double &value);

            // Одного знака
            bool is_one_sign(double& h1, double &h2);

            // Площадь трапеции
            double get_trapezoid_area(QVector<n_global_types::C_point>& points);

            // Площадь сегмента
            double get_segment_area(QVector<N_inter::n_global_types::C_m_line>& segment);
            double get_segment_area(N_inter::n_motion_calc::n_types::C_motion_section& segment);
            double get_line_area(N_inter::n_global_types::C_m_line& line);

            // Отличное от нуля среди двух чисел
            double is_none_zero(double& value1, double& value2);

            // Сумма элементов
            double get_sum(double& value1, double& value2);

            // Неравенство элементов
            bool is_not_equal(double v1, double v2);
            bool is_more_than(double v1, double v2);
            bool is_more_or_equal(double v1, double v2);
        }
    }
}
// --------------------------------------------------------
