#pragma once
// --------------------------------------------------------

#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
#include "N_inter/N_motion_calc/N_types/C_motion.h"
#include "N_inter/N_motion_calc/N_types/C_motion_velocity_lines.h"
#include "N_inter/N_global_types/S_trajectory_input.h"
#include "N_inter/N_motion_calc/N_types/N_motion_table/S_motion_table.h"
// --------------------------------------------------------

// TODO: переименовать, дать нормальные имена
namespace N_inter {
    namespace n_motion_calc {
        namespace n_convert {
            // Вектор сегментов в вектор отрезков
            QVector<N_inter::n_global_types::C_m_line> kmotion_segments_vector_to_kline_vector(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments);

            // Сегмент в вектор отрезков
            QVector<N_inter::n_global_types::C_m_line> kmotion_segment_to_kline_vector(N_inter::n_motion_calc::n_types::C_motion_section& segment);

            // Вектор отрезков в вектор сегментов
            QVector<N_inter::n_motion_calc::n_types::C_motion_section> kline_vector_to_kmotion_segment_vector(QVector<N_inter::n_global_types::C_m_line>& lines);

            // Перевод одного движения в другое
            N_inter::n_motion_calc::n_types::C_motion C_motion_velocity_lines_to_C_motion(N_inter::n_motion_calc::n_types::C_motion_velocity_lines &motion_velocity_lines);

            // Перевод одного движения в другое
            // Есть подозрение, что подобная структура сложная, и её можно упростить
            N_inter::n_motion_calc::n_types::C_motion_velocity_lines kmotion_to_motion_velocity(N_inter::n_motion_calc::n_types::C_motion& motion);

            // TODO перенести куда-нибудь в другое место. Это вспомогательная функция
            // Строку в вектор линий
            QVector<N_inter::n_global_types::C_m_line> save_lines_from_qstring(QString lines);
            QVector<N_inter::n_global_types::S_trajectory_input> split_lines_from_qstring_by_commands(QString lines);

            // Конвертирование движения в таблицу движений
            N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table to_motion_table(N_inter::n_motion_calc::n_types::C_motion_velocity_lines &motion_lines);

            // TODO переименовать все методы в соответствие с этим (to_type_name)
            // TODO to_string функции реализовать как m_to_string функции-члены соответствующих классов и структур
            // Таблицу движений в строку
            QString to_string(N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table& motion_table);

            // Элемент таблицы движений в строку
            QString to_string(N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table_item& motion_table_item);

            // Массив точек в массив линий
            QVector<N_inter::n_global_types::C_m_line> to_lines_vector(QVector<N_inter::n_global_types::C_point> points);
        }
    }
}
// --------------------------------------------------------
