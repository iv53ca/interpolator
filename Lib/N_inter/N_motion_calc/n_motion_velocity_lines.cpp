#include "n_motion_velocity_lines.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include <QDebug>
#include <QVector>
// --------------------------------------------------------

using N_inter::n_global_types::COORD;
using N_inter::S_exception;
using N_inter::n_global_types::C_m_line;
using N_inter::n_motion_calc::n_types::C_motion_velocity_lines;
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_velocity_lines::set_motion_offset_by_time(n_types::C_motion_velocity_lines &motion, double time_offset) {
    if (time_offset == 0) {
        return;
    }
    // Перебор осей
    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        // Перебор отрезков
        for (int j = 0; j < motion[i].size(); j++) {
            // Смещение по времени для каждого отрезка
            motion[i][j].m_first_point[COORD::X] = motion[i][j].m_first_point[COORD::X] + time_offset;
            motion[i][j].m_second_point[COORD::X] = motion[i][j].m_second_point[COORD::X] + time_offset;
        }
    }
}
// --------------------------------------------------------

double N_inter::n_motion_calc::n_motion_velocity_lines::get_motion_time(n_types::C_motion_velocity_lines &motion) {
    if (motion[0].size() == 0) {
        return 0;
    }
    return motion[0].back().m_second_point[COORD::X];
}
// --------------------------------------------------------

double N_inter::n_motion_calc::n_motion_velocity_lines::get_time_offset_for_axis(n_types::C_motion_velocity_lines &motion, double time, int axis) {
    // Если ось неиспользуемая, то кидать исключение
    if (axis >= N_inter::n_data::n_motion_vars::n_calc_vars::axis_count) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "axis >= N_inter::n_data::n_motion_vars::n_calc_vars::axis_count";
        exc.m_decision = "Попытка получить смещение по времени для неиспользуемой оси";
        throw exc;
    }
    // Если время выходит за пределы движения, то кидать исключение
    if (N_inter::n_algebra::n_math::is_more_than(time, get_motion_time(motion))) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(time, get_motion_time(motion))";
        exc.m_decision = "Попытка получить смещение для завершённого движения";
        throw exc;
    }

    int line_index = -1;
    // Определение отрезка, содержащего указаное время
    for (int i = 0; i < motion[axis].size(); i++) {
        // TODO дубляж функции в n_lines. Раздробить одно большое пространство имён на несколько маленьких
        if (N_inter::n_geom::n_lines::is_segment_contain_x(motion[axis][i], time)) {
            line_index = i;
            break;
        }
    }
    if (line_index == -1) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "line_index == -1";
        exc.m_decision = "Содержащий это время отрезок не найден";
        throw exc;
    }

    // Расчёт смещения для всех предыдущих отрезков
    double offset = 0;
    for (int i = 0; i < line_index; i++) {
        offset = offset + N_inter::n_geom::n_lines::get_line_definite_integral(motion[axis][i]);
    }

    // Расчёт смещения для этого вектора
    C_m_line line = motion[axis][line_index];
    double begin_x = line.m_first_point[COORD::X];
    double end_x = time;
    // qDebug() << "Int:" << N_inter::n_geom::n_lines::get_line_definite_integral(line, begin_x, end_x) << "begin_x:" << begin_x << "end_x" << end_x;
    offset = offset + N_inter::n_geom::n_lines::get_line_definite_integral(line, begin_x, end_x);

    return offset;
}
// --------------------------------------------------------

double N_inter::n_motion_calc::n_motion_velocity_lines::get_vel_offset_for_axis(n_types::C_motion_velocity_lines &motion, double time, int axis) {
    // Если ось неиспользуемая, то кидать исключение
    if (axis >= N_inter::n_data::n_motion_vars::n_calc_vars::axis_count) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "axis >= N_inter::n_data::n_motion_vars::n_calc_vars::axis_count";
        exc.m_decision = "Попытка получить смещение по времени для неиспользуемой оси";
        throw exc;
    }
    // Если время выходит за пределы движения, то кидать исключение
    if (N_inter::n_algebra::n_math::is_more_than(time, get_motion_time(motion))) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_algebra::n_math::is_more_than(time, get_motion_time(motion))";
        exc.m_decision = "Попытка получить смещение для завершённого движения";
        throw exc;
    }

    // Поиск отрезка, содержащего это время
    for (int i = 0; i < motion[axis].size(); i++) {
        // Отрезок найден
        if (N_inter::n_geom::n_lines::is_segment_contain_x(motion[axis][i], time)) {
            return N_inter::n_geom::n_lines::get_line_y_by_x(motion[axis][i], time);
        }
    }

    S_exception exc;
    exc.m_calling_object = Q_FUNC_INFO;
    exc.m_condition = "-";
    exc.m_decision = "Отрезок движения по такому времени не найден";
    throw exc;
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_velocity_lines N_inter::n_motion_calc::n_motion_velocity_lines::get_kill_motion(n_global_types::C_point current_velocity) {
    // Движение при аварии
    C_motion_velocity_lines motion;

    // Остановка движения для каждой оси
    for (int axis = 0; axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; axis++) {
        C_m_line motion_part;

        // Первая точка
        motion_part.m_first_point[COORD::X] = 0;
        motion_part.m_first_point[COORD::Y] = current_velocity[axis];


        // Вторая точка
        motion_part.m_second_point[COORD::Y] = 0;

        // Точки прямой
        double a = N_inter::n_data::n_motion_vars::n_calc_vars::kill_acceleration[axis];
        double x0 = 0;
        double y0 = current_velocity[axis];
        double y1 = 0;

        // Вычисление X координаты второй точки
        if (N_inter::n_algebra::n_math::is_more_than(current_velocity[axis], 0)) {
            motion_part.m_second_point[COORD::X] = (-1 / a) * (y1 - y0 + a * x0);
        }
        else if (N_inter::n_algebra::n_math::is_more_than(0, current_velocity[axis])) {
            motion_part.m_second_point[COORD::X] = (1 / a) * (y1 - y0 + a * x0);
        }
        else {
            motion_part.m_second_point[COORD::X] = motion_part.m_first_point[COORD::X];
        }

        // Обновление движения
        motion[axis].push_back(motion_part);
    }

    // Согласование по времени (добавление пустот)
    add_voids_for_time(motion);

    // Добавление временных задержек (удержание движения)
    add_empty_time(motion);

    return motion;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_velocity_lines::add_voids_for_time(n_types::C_motion_velocity_lines &motion) {
    double time = 0;

    // Перебор осей, поиск максимального времени
    for (int axis = 0; axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; axis++) {
        // Последний отрезок движения
        C_m_line last_segment = motion[axis][motion[axis].size() - 1];
        if (N_inter::n_algebra::n_math::is_more_than(last_segment.m_second_point[COORD::X], time)) {
            time = motion[axis].back().m_second_point[COORD::X];
        }
    }

    // Приведение осей в соответствие с максимальным временем (добавление пустот)
    for (int axis = 0; axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; axis++) {
        if (!N_inter::n_algebra::n_math::is_equal(motion[axis].back().m_second_point[COORD::X], time)) {
            // Последний отрезок движения
            C_m_line last_segment = motion[axis][motion[axis].size() - 1];

            C_m_line motion_part;
            motion_part.m_first_point = last_segment.m_second_point;
            motion_part.m_second_point[COORD::X] = time;
            motion_part.m_second_point[COORD::Y] = 0;

            motion[axis].push_back(motion_part);
        }
    }

}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_velocity_lines::add_empty_time(n_types::C_motion_velocity_lines &motion) {
    // Перебор осей
    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        // Последний отрезок движения
        C_m_line last_segment = motion[i][motion[i].size() - 1];

         // Дополнительный отрезок движения
        C_m_line motion_part;
        motion_part.m_first_point = last_segment.m_second_point;
        motion_part.m_second_point[COORD::X] = motion_part.m_first_point[COORD::X] + N_inter::n_data::n_motion_vars::n_calc_vars::accident_stay_time;
        motion_part.m_second_point[COORD::Y] = 0;

        motion[i].push_back(motion_part);
    }
}
// --------------------------------------------------------
