#pragma once
// --------------------------------------------------------

#include <QVector>

#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/C_object.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_types {
            class C_motion_section : public N_inter::C_object {
                QVector<N_inter::n_global_types::C_m_line> lines; // Отрезки
            public:
                C_motion_section();
                ~C_motion_section();

                int get_size(); // Количество отрезков

                QVector<N_inter::n_global_types::C_m_line> &get_lines(); // Получение отрезков
                void set_lines(QVector<N_inter::n_global_types::C_m_line> new_lines);

                N_inter::n_global_types::C_point get_begin_point(); // Начальная точка
                N_inter::n_global_types::C_point get_end_point();   // Конечная точка

                void set_begin_point(N_inter::n_global_types::C_point new_point); // Начальная точка
                void set_end_point(N_inter::n_global_types::C_point new_point);   // Конечная точка

                N_inter::n_global_types::C_m_line &get_begin_line(); // Получение крайнего слева отрезка
                N_inter::n_global_types::C_m_line &get_end_line();   // Получение крайнего справа отрезка

                QString m_to_string();

                void insert_at(int index, N_inter::n_global_types::C_m_line new_line); // Добавить новый отрезок по индексу
                void push_back(N_inter::n_global_types::C_m_line line); // Вставка отрезка в конец

                void remove_at(int index); // Удаление отрезка по индексу

                void clear(); // Очистка отрезков

                N_inter::n_global_types::C_m_line &operator[](int index);
            };
        }
    }
}
// --------------------------------------------------------
