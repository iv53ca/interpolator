#include "n_profiler.h"
#include <QDebug>
#include "N_inter/N_motion_calc/n_convert.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_motion_vars/n_data.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/N_profiler/N_trajectory/n_none_prof.h"
#include "N_inter/N_profiler/N_trajectory/n_prof.h"
#include "N_inter/N_profiler/N_Velocity/n_none_prof.h"
#include "N_inter/N_profiler/N_Velocity/n_prof.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_motion_calc/N_rounding_corners/N_none_prof/n_none_prof.h"
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_m_line> N_inter::n_profiler::n_aux::trajectory(QVector<N_inter::n_global_types::C_m_line> &lines, bool profStat) {
    if (profStat) {
        return n_profiler::n_trajectory::n_prof::inter(lines, N_inter::n_data::n_motion_vars::n_calc_vars::max_position_error, N_inter::n_data::n_motion_vars::n_calc_vars::split_segments_count);
    }
    return n_profiler::n_trajectory::n_none_prof::inter(lines);
}
// --------------------------------------------------------

void N_inter::n_profiler::clear_data() {
    // Траектория, очистка векторов
    N_inter::n_data::n_motion_vars::trajectory.clear();

    // Оси, очистка векторов
    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        N_inter::n_data::n_motion_vars::motion[current_axis].clear();
    }
}
// --------------------------------------------------------

void N_inter::n_profiler::proxy_trajectory(QString a_lines_string, const bool a_prof_stat, QVector<n_global_types::C_m_line> &trajectory) {
    // Если линий нет, то профилирование не нужно
    if (a_lines_string == "") {
        qDebug() << "Массив с линиями для профилирования пустой:" << a_lines_string;
        return;
    }

    // Перевод текстового представления строк в машинное
    try {
        trajectory = N_inter::n_motion_calc::n_convert::save_lines_from_qstring(a_lines_string);

        // Округение точек до нуля (если в окрестности вычислительной ошибки)
        N_inter::n_geom::n_lines::to_necessary_zero(trajectory);

        // Если линий нет, то профилирование не нужно
        if (trajectory.size() == 0) {
            qDebug() << "Массив с линиями для профилирования пустой:" << a_lines_string;
            return;
        }

        // Если a_none_prof_track содержит единственную прямую, то профилирование не нужно
        // if (a_none_prof_track.size() == 1) {
        //     a_prof_track = a_none_prof_track;
        // }
        // else {
        trajectory = n_aux::trajectory(trajectory, a_prof_stat);
        // }

        if (trajectory.size() == 0) {
            N_inter::S_exception exc;
            exc.m_calling_object = "void n_profiler::proxy_trajectory(QString a_lines_string, const bool a_prof_stat, QVector<n_global_types::C_m_line> &a_none_prof_track, QVector<n_global_types::C_m_line> &a_prof_track)";
            exc.m_condition = "a_prof_track.size() == 0";
            exc.m_decision = "Массив с профилированными линиями пустой";
            throw exc;
        }
    }
    catch (N_inter::S_exception exc) {
        N_inter::n_data::n_motion_vars::trajectory.clear();
        exc.show_message();
    }
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_velocity_lines N_inter::n_profiler::Velocity(QVector<n_global_types::C_m_line> &lines, bool profStat) {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_motion_calc::n_types::C_motion_velocity_lines n_profiler::Velocity(QVector<n_global_types::C_m_line> &lines, bool profStat)";
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Массив с линиями пустой";
        throw exc;
    }

    // TODO перенести в пространство имён N_inter::n_init
    // Инициализация пространства имён с алгоритмом закругления для профилей скорости
    N_inter::n_motion_calc::n_rounding_corners::n_none_prof::init();

    if (profStat) {
        try {
            return n_profiler::n_velocity::n_prof::inter(lines);
        }
        catch (N_inter::S_exception exc) {
            exc.show_message();
        }
    }

    // Профиль скорости без профилирования
    N_inter::n_motion_calc::n_types::C_motion_velocity_lines vel_lines = n_profiler::n_velocity::n_none_prof::proxy_inter(lines);
    N_inter::n_motion_calc::n_types::C_motion motion = N_inter::n_motion_calc::n_convert::C_motion_velocity_lines_to_C_motion(vel_lines);

    // Закругление углов
    N_inter::n_motion_calc::n_rounding_corners::n_none_prof::round(motion);

    // Результат
    return N_inter::n_motion_calc::n_convert::kmotion_to_motion_velocity(motion);
}
// --------------------------------------------------------
