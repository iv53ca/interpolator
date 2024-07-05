#include "n_prof.h"
#include <QDebug>
#include "N_inter/N_motion_calc/n_point_elevation.h"
#include "N_inter/N_motion_calc/N_alignment/N_area/n_prof.h"
#include "N_inter/N_motion_calc/n_convert.h"
#include "N_inter/N_motion_calc/n_motion_spaces.h"
#include "N_inter/N_profiler/N_Velocity/n_none_prof.h"
#include "N_inter/N_motion_calc/n_motions.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_profiler/n_profiler.h"
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion N_inter::n_profiler::n_velocity::n_prof::motion;
// --------------------------------------------------------

using N_inter::S_exception;
// --------------------------------------------------------

void N_inter::n_profiler::n_velocity::n_prof::n_aux::check_motion_time_difference(n_motion_calc::n_types::C_motion &motion) {
    double time = motion[0].back().get_end_point()[N_inter::n_global_types::X];
    for (int curr_axis = 0; curr_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; curr_axis++) {
        double curr_time = motion[curr_axis].back().get_end_point()[N_inter::n_global_types::X];
        if (!n_algebra::n_math::is_equal(time, curr_time)) {
            S_exception exc;
            exc.m_calling_object = "N_inter::n_profiler::n_velocity::n_prof::n_aux::check_motion_time_difference(n_motion_calc::n_types::C_motion &motion)";
            exc.m_condition = "!n_algebra::n_math::is_equal(time, curr_time)";
            exc.m_decision = "Рассогласование движения по времени";
            throw exc;
        }
    }
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_velocity_lines N_inter::n_profiler::n_velocity::n_prof::inter(QVector<n_global_types::C_m_line> &lines) {
    N_inter::n_motion_calc::n_types::C_motion motion;

    N_inter::n_motion_calc::n_types::C_motion_velocity_lines motion_lines = n_profiler::n_velocity::n_none_prof::inter(lines); // Разложение движения по осям без профилирования
    motion = N_inter::n_motion_calc::n_convert::C_motion_velocity_lines_to_C_motion(motion_lines);

    n_profiler::n_velocity::n_none_prof::motion = motion;

    // Если количество отрезков равно единице, то профилирование не требуется
    if (lines.size() == 1) {
        // Формирование результата
        return N_inter::n_motion_calc::n_convert::kmotion_to_motion_velocity(motion);
    }

    N_inter::n_motion_calc::n_motions::remove_empty_lines(motion); // Удаление вырожденных отрезков
    n_aux::check_motion_time_difference(motion); // Проверка на рассогласование движения по времени

    N_inter::n_motion_calc::n_motions::remove_empty_sections(motion); // Удаление пустых секций

    // BUG !!! удалить пустоты для режима без профилирования
    N_inter::n_motion_calc::n_motions::remove_empty_lines(n_profiler::n_velocity::n_none_prof::motion); // Удаление вырожденных отрезков
    N_inter::n_motion_calc::n_motions::remove_empty_sections(n_profiler::n_velocity::n_none_prof::motion); // Удаление пустых секций
    n_aux::check_motion_time_difference(n_profiler::n_velocity::n_none_prof::motion); // Проверка на рассогласование движения по времени

    // Возвышение опорных точек
    N_inter::n_motion_calc::n_point_elevation::elevationOfReferencePoints(motion);

    N_inter::n_motion_calc::n_motions::remove_empty_lines(motion); // Удаление вырожденных отрезков
    n_aux::check_motion_time_difference(motion); // Проверка на рассогласование движения по времени

    // Удаление максимально допустимой площади из прямоугольных составляющих профилей
    N_inter::n_motion_calc::n_alignment::n_area::n_prof::correct_rectangle_area_part(motion, n_profiler::n_velocity::n_none_prof::motion);

    N_inter::n_motion_calc::n_motions::remove_empty_lines(motion); // Удаление вырожденных отрезков
    n_aux::check_motion_time_difference(motion); // Проверка на рассогласование движения по времени

    // Удаление пробелов (появляются после корректировки прямоугольных составляющих движений)
    N_inter::n_motion_calc::n_motion_spaces::remove(motion);

    N_inter::n_motion_calc::n_motions::remove_empty_lines(motion); // Удаление вырожденных отрезков
    n_aux::check_motion_time_difference(motion); // Проверка на рассогласование движения по времени

    // Уточнение площадей бинарным методом
    N_inter::n_motion_calc::n_alignment::n_area::n_prof::binary_correct(n_profiler::n_velocity::n_none_prof::motion, motion);

    N_inter::n_motion_calc::n_motions::remove_empty_lines(motion); // Удаление вырожденных отрезков
    n_aux::check_motion_time_difference(motion); // Проверка на рассогласование движения по времени

    return N_inter::n_motion_calc::n_convert::kmotion_to_motion_velocity(motion);
}
// --------------------------------------------------------
