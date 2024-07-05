#include "n_none_prof.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_types_calc/n_trapezoids.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_none_prof/n_data.h"
#include "N_inter/N_motion_vars/n_data.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
#include "N_inter/N_motion_calc/n_motion_sections.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_motion_calc/n_motion_sections.h"
#include <QDebug>
// --------------------------------------------------------

using N_inter::n_global_types::C_m_line;
using N_inter::n_global_types::C_point;
using N_inter::n_global_types::COORD;
using N_inter::S_exception;
using N_inter::n_motion_calc::n_types::C_motion_section;
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_none_prof::init() {
    N_inter::n_motion_calc::n_rounding_corners::n_none_prof::n_data::typical_arcs.write();
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_none_prof::round(n_motion_calc::n_types::C_motion &motion) {
    // Если разное количество секций, то кидать исключение
    int sections_count = motion[COORD::X].size();
    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        if (motion[i].size() != sections_count) {
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "motion[i].size() != sections_count";
            exc.m_decision = "Разное количество секций для движения";
            throw exc;
        }
    }

    // Предыдущая точка для смещения
    double prev_x_position = 0;

    // Перебор секций движения для каждой оси
    for (int i = 0; i < sections_count; i++) {
        // Вектор секций
        QVector<C_motion_section> sections;
        for (int j = 0; j < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; j++) {
            sections.push_back(motion[j][i]);
        }
        if (sections.size() != N_inter::n_data::n_motion_vars::n_calc_vars::axis_count) {
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "sections.size() != axis_count";
            exc.m_decision = "Кол-во секций не соответствуют коичеству осей";
            throw exc;
        }

        // Если часть движения в обратном направлении, то отобразить вдоль оси абсцисс
        QVector<bool> mirrored_sections = N_inter::n_motion_calc::n_motion_sections::positive_sections_morrored_by_x(sections);

        // Срез пиков для треугольников для каждой оси
        for (int j = 0; j < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; j++) {
            QVector<C_m_line> lines = sections[j].get_lines();
            N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::triangle_peak_slice(lines, j);
            N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::trapezoid_stretching(lines, j);
            sections[j].set_lines(lines);
        }

        // Расширение трапеций для каждой оси
        for (int j = 0; j < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; j++) {
            QVector<C_m_line> lines = sections[j].get_lines();
            N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::trapezoid_stretching(lines, j);
            sections[j].set_lines(lines);
        }

        // Смещение секций в точку 0
        N_inter::n_motion_calc::n_motion_sections::section_offset_x(sections, 0);

        // Вектор площадных разниц. Если окружность вписать нельзя, то 0
        QVector<double> diff_areas = N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::get_area_diff_round(sections);

        // TODO trapezoids перенести в пространство имён n_geom

        // Если в трапецию окружность вписать нельзя, то здесь ничего не поменяется
        // Дополнение прямоугольных составляющих исходных векторов
        QVector<C_motion_section> new_sections = {};
        for (int j = 0; j < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; j++) {
            N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::add_rectangular_component_for_trapezoids(sections[j], diff_areas[j]);
            new_sections.push_back(sections[j]);
        }

        // Получение результирующего времени
        double result_time = N_inter::n_motion_calc::n_motion_sections::get_max_width(new_sections);

        // Согласование по времени
        new_sections = N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::correct_area_by_time(new_sections, result_time);

        if (sections.size() != new_sections.size()) {
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "sections.size() != new_sections.size()";
            exc.m_decision = "Кол-во секций не совпадает";
            throw exc;
        }

        // Вписывание окружностей (если возможно)
        for (int j = 0; j < sections.size(); j++) {
            QVector<C_m_line> lines = N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::round_trapezoid(new_sections[j], j);

            // Если окружности вписать нельзя, то выполнить корректировку прямоугольной составляющей в обратную сторону
            // После выровнять по времени
            if (lines.size() == 3) {
                // Корректировка прямоугольной составляющей движения в обратную сторону
                N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::add_rectangular_component_for_trapezoids(new_sections[j], - diff_areas[j]);

                // Корректировка по времени
                lines = N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_trapezoids::correct_trapezoid_area(new_sections[j], result_time);
            }

            // Профиль был отображён вдоль оси абсцисс
            if (mirrored_sections[j]) {
                C_motion_section section;
                section.set_lines(lines);
                N_inter::n_motion_calc::n_motion_sections::section_morrored_by_x(section);
                lines = section.get_lines();
            }

            // sections[j].set_lines(lines);
            new_sections[j].set_lines(lines);
        }

        // Смещение секций в точку prev_x_position
        N_inter::n_motion_calc::n_motion_sections::section_offset_x(new_sections, prev_x_position);

        for (int j = 0; j < new_sections.size(); j++) {
            motion[j][i].set_lines(new_sections[j].get_lines());
        }

        prev_x_position = new_sections.back().get_end_point()[COORD::X];
    }
}
// --------------------------------------------------------
