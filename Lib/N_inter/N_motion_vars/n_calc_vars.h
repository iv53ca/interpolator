#pragma once
// --------------------------------------------------------

namespace N_inter {
    namespace n_data {
        namespace n_motion_vars {
            namespace n_calc_vars {
                extern const double max_position_error;                 // Ошибка позиционирования
                extern const double calculation_error;                  // Погрешность вычислений
                extern const double max_errors_segment_length;          // Минимально допустимая длина отрезка в количестве ошибок позиционирования (например, 2) для профилирования
                extern int          split_segments_count;               // Количество поворотных отрезков
                extern const int    split_segments_count_for_vel;       // Количество поворотных отрезков для скорости
                extern const bool   enable_round;                       // Задействовать алгоритм плавных скоростных переходов
                extern const int    axis_count;                         // Колличество осей
                extern const double elevation_velocity;                 // Степень падения скорости при возвышении опорных точек (1 - не снижать, 2 - снижать вдвое)
                extern const double degree_peak_cutoff_for_triangles[]; // Степень среза углов для треугольников (режим без профилирования) (чем выше - тем сильнее срез)
                extern const double max_velocity_round[];               // Закругление для скорости
                extern const double max_velocity[];                     // Максимально допустимая скорость
                extern const double acceleration[];                     // Ускорение для осей
                extern const double kill_acceleration[];                // Ускорение для осей при аварии
                extern const double accident_stay_time;                 // Время задержки для аварии (удержание движения)
                extern const int    max_axis_count;                     // Максимально допустимое количество осей
                extern const double time_step_for_motion_table;         // Временной шаг для составления таблицы движений
            }
        }
    }
}
// --------------------------------------------------------
