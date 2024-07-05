#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_motion_calc {
        namespace n_motion_sections {
            namespace {
                namespace n_aux {
                    // Отзеркаленные отрезки-границы для сегмента
                    void segmentBorders(N_inter::n_motion_calc::n_types::C_motion_section& segment, N_inter::n_global_types::C_m_line& leftBorder, N_inter::n_global_types::C_m_line& rightBorder, double h, double leftA, double rightA);

                    // Части дополненного сегмента
                    N_inter::n_motion_calc::n_types::C_motion_section augmentedSegmentLines(N_inter::n_motion_calc::n_types::C_motion_section& segment, N_inter::n_global_types::C_m_line& leftBorder, N_inter::n_global_types::C_m_line& rightBorder, double h);
                }
            }
            enum K_SIGN {
                POSITIVE,
                NEGATIVE,
                ZERO
            };

            K_SIGN sign(N_inter::n_motion_calc::n_types::C_motion_section& segment);

            // Выборка сегментов одинакового знака
            void unidirectionalSegments(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments, int& begin, int& end);

            // TODO переименовать
            // Зеркальное отражение сегмента вдоль оси абсцисс
            void segmentMirroredByY(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& segments, int begin, int end);
            void segmentMirroredByY(N_inter::n_motion_calc::n_types::C_motion_section& a_segments_kms);
            void section_morrored_by_x(N_inter::n_motion_calc::n_types::C_motion_section& section);
            QVector<bool> positive_sections_morrored_by_x(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& sections);

            // Получение усечённого сегмента прямой, проходящей по высоте h
            N_inter::n_motion_calc::n_types::C_motion_section truncatedSegment(N_inter::n_motion_calc::n_types::C_motion_section& segment, double h, double leftA, double rightA);

            // Получение наибольшей ширины сегментов
            double get_max_width(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &sections);

            // Получение высоты сегмента
            double segmentHeight(N_inter::n_motion_calc::n_types::C_motion_section &segment);

            // Содержит ли секция прямоугольный сегмент (хотя бы один)
            bool is_segment_contain_hor_lines(N_inter::n_motion_calc::n_types::C_motion_section &segment);

            // TODO: в отдельное пространство имён offset
            // Смещение секции вдоль оси X на offset_x единиц
            void section_offset_x(N_inter::n_motion_calc::n_types::C_motion_section &section, double new_x_position);
            void section_offset_x(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &sections, double new_x_position);

            // Проверка секции на корректную
            bool is_section_correct(QVector<N_inter::n_global_types::C_m_line> &lines);
            bool is_section_correct(N_inter::n_motion_calc::n_types::C_motion_section &section);
            bool is_section_correct(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &sections);

            // Если секции некорректные, то кидать исключение
            void throw_is_section_correct(QVector<N_inter::n_global_types::C_m_line> &lines);
            void throw_is_section_correct(N_inter::n_motion_calc::n_types::C_motion_section &section);
            void throw_is_section_correct(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &sections);

            // Проверка на секцию с нулевым перемещением
            bool is_zero_displacement_section(N_inter::n_motion_calc::n_types::C_motion_section &section);
            bool is_zero_displacement_section(QVector<N_inter::n_global_types::C_m_line> &lines);
        }
    }
}
// --------------------------------------------------------
