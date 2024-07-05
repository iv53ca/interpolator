#pragma once
// --------------------------------------------------------

#include "N_inter/N_motion_calc/N_rounding_corners/N_types/C_arc_circle.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
// --------------------------------------------------------

// TODO перенести в пространство имён  n_geom
// TODO перенести часть функций в n_aux
namespace N_inter {
    namespace n_motion_calc {
        namespace n_rounding_corners {
            namespace n_types_calc {
                namespace n_trapezoids {
                    namespace {
                        namespace n_aux {
                            // Закругление левого и правого углов трапеции
                            void left_corner_round(QVector<N_inter::n_global_types::C_m_line>& lines, int axis);
                            void right_corner_round(QVector<n_global_types::C_m_line> &lines, int axis);

                            bool is_h_correct(n_global_types::C_m_line &left, n_global_types::C_m_line &right, double h, double S);
                        }
                    }
                    // Проверка совокупности отрезков на трапецию
                    bool is_trapezoid(QVector<N_inter::n_global_types::C_m_line>& lines);
                    bool is_trapezoid(N_inter::n_motion_calc::n_types::C_motion_section& section);
                    bool is_trapezoids(QVector<N_inter::n_motion_calc::n_types::C_motion_section>& sections);

                    // TODO: в отдельное пространство имён n_triangles
                    // Проверка совокупности отрезков на треугольник
                    bool is_triangle(QVector<N_inter::n_global_types::C_m_line>& lines);

                    // Проверка, можно ли закруглить углы для этой трапеции
                    bool is_fit_possible(QVector<N_inter::n_global_types::C_m_line>& lines, int axis);
                    bool is_fit_possible(N_inter::n_motion_calc::n_types::C_motion_section& section, int axis);

                    // Закругление углов для трапеции
                    QVector<N_inter::n_global_types::C_m_line> round_trapezoid(QVector<N_inter::n_global_types::C_m_line>& lines, int axis);
                    QVector<N_inter::n_global_types::C_m_line> round_trapezoid(N_inter::n_motion_calc::n_types::C_motion_section& section, int axis);

                    // Получение разницы площадей ДО и ПОСЛЕ вписывания окружности
                    QVector<double> get_area_diff_round(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &sections);

                    // Добавление прямоугольной составляющей для трапеции
                    void add_rectangular_component_for_trapezoids(N_inter::n_motion_calc::n_types::C_motion_section &section, double diff_area);

                    // Корректировка площади по времени
                    QVector<N_inter::n_motion_calc::n_types::C_motion_section> correct_area_by_time(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &sections, double diff_time);

                    // Растяжение трапеции (по необходимости)
                    void trapezoid_stretching(QVector<N_inter::n_global_types::C_m_line>& lines, int axis);

                    // Срез пика треугольника
                    void triangle_peak_slice(QVector<N_inter::n_global_types::C_m_line>& lines, int axis);

                    // Корректировка площади трапеции
                    QVector<N_inter::n_global_types::C_m_line> correct_trapezoid_area(N_inter::n_motion_calc::n_types::C_motion_section& motion_section, double new_time);
                    QVector<N_inter::n_global_types::C_m_line> correct_trapezoid_area(QVector<N_inter::n_global_types::C_point>& points, double new_time);
                    QVector<N_inter::n_global_types::C_m_line> correct_trapezoid_area(QVector<N_inter::n_global_types::C_m_line>& lines, double new_time);
                }
            }
        }
    }
}
// --------------------------------------------------------
