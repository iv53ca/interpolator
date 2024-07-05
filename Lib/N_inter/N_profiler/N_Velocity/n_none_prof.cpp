#include "n_none_prof.h"
#include "N_inter/N_motion_calc/n_motion_sections.h"
#include "N_inter/N_motion_calc/n_velocities.h"
#include "N_inter/N_motion_calc/N_types/C_motion.h"
#include <cmath>
#include <QDebug>
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_algebra/n_limits.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_motion_calc/n_convert.h"
#include "N_inter/N_geom/n_points.h"
#include "N_inter/N_geom/n_points.h"
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion N_inter::n_profiler::n_velocity::n_none_prof::motion;
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_point> N_inter::n_profiler::n_velocity::n_none_prof::n_aux::proxy_inter(n_global_types::C_m_line &line, double &ts, int axis) {
    // Если движение идёт в обратную сторону, то
    // 1. Поменять соответствующие координаты местами
    // 2. Выставить флаг
    bool mirror_status = false;
    if (n_aux::movement_in_opposite_direction(line, axis)) {
        n_aux::opposite_speed_profile_x(line, axis);
        mirror_status = true;
    }

    QVector<N_inter::n_global_types::C_point> result = n_aux::inter(line, ts, axis);

    // Разворот профиля скорости
    if (mirror_status) {
        n_aux::opposite_points_speed_profile_y(result);
    }

    return result;
}
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_point> N_inter::n_profiler::n_velocity::n_none_prof::n_aux::inter(n_global_types::C_m_line &line, double &ts, int axis) {
    // Желаемая максимальная достижимая скорость
    double F = N_inter::n_motion_calc::n_velocities::get_speed_projection(line, line.velocity, axis);

    // Ускорение вдоль выбранной оси
    double a = N_inter::n_data::n_motion_vars::n_calc_vars::acceleration[axis];

    // Перевод линии в массив координат
    QVector<double> lineArray = n_geom::n_lines::to_double_vector(line);

    // axis принимает значения от нуля
    double start = lineArray.at(2 * axis);
    double end = lineArray.at(2 * axis + 1);

    // Если движение идёт в обратном направлении, то
    // 1. Определить, вдоль какой оси

    // Если движение происходит в обратном направлении, то корректировать ускорение и скорость
    if (N_inter::n_algebra::n_math::is_more_than(start, end)) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QVector<C_point> NoneProfVelocity::_inter(C_m_line& line, double& ts, int axis)";
        exc.m_condition = "n_algebra::n_math::is_more_than(start, end)";
        exc.m_decision = "Начальное значение больше конечного";
        throw exc;
    }

    double tp = F / a; // Время разгона
    double tz = tp;    // Время замедления
    N_inter::n_algebra::n_math::to_necessary_zero(tp);
    N_inter::n_algebra::n_math::to_necessary_zero(tz);

    // Перемещение
    double L = end - start;
    N_inter::n_algebra::n_math::to_necessary_zero(L);

    // qDebug() << "L =" << L;

    // Время движения с рабочей скоростью
    // double t = (1.0 / F) * (2.0 * L - F * tp - F * tz);
    double t = 0;
    if (F != 0) {
        t = (L / F) - tp;
        N_inter::n_algebra::n_math::to_necessary_zero(t);
    }
    // TODO здесь t может быть 0/0

    // Результат
    QVector<N_inter::n_global_types::C_point> points;

    // Удалось выйти на рабочую скорость
    if (t > 0) {
        double t1 = ts,      f1 = 0;
        double t2 = t1 + tp, f2 = F;
        double t3 = t2 + t,  f3 = F;
        double t4 = t3 + tz, f4 = 0;

        N_inter::n_global_types::C_point point1; point1[n_global_types::X] = t1; point1[n_global_types::Y] = f1;
        N_inter::n_global_types::C_point point2; point2[n_global_types::X] = t2; point2[n_global_types::Y] = f2;
        N_inter::n_global_types::C_point point3; point3[n_global_types::X] = t3; point3[n_global_types::Y] = f3;
        N_inter::n_global_types::C_point point4; point4[n_global_types::X] = t4; point4[n_global_types::Y] = f4;

        points.push_back(point1);
        points.push_back(point2);
        points.push_back(point3);
        points.push_back(point4);

        ts = t4;

        // qDebug() << "newL =" << 0.5 * (t4 - t1 + t3 - t2) * f3;
    }

    // Не удалось выйти на рабочую скорость
    else {
        double t = sqrt(L / a);

        double t1 = ts,     f1 = 0;
        double t2 = t1 + t, f2 = a * t;
        double t3 = t2 + t, f3 = 0;

        N_inter::n_global_types::C_point point1; point1[n_global_types::X] = t1; point1[n_global_types::Y] = f1;
        N_inter::n_global_types::C_point point2; point2[n_global_types::X] = t2; point2[n_global_types::Y] = f2;
        N_inter::n_global_types::C_point point3; point3[n_global_types::X] = t3; point3[n_global_types::Y] = f3;

        points.push_back(point1);
        points.push_back(point2);
        points.push_back(point3);

        ts = t3;

        // qDebug() << "newL =" << 0.5 * (t3 - t1) * f2;
    }

    return points;
}
// --------------------------------------------------------

void N_inter::n_profiler::n_velocity::n_none_prof::n_aux::opposite_speed_profile_x(n_global_types::C_m_line &line, int axis) {
    // Ось X
    if (axis == 0) {
        double _temp = line.m_first_point[n_global_types::X];
        line.m_first_point[n_global_types::X] = line.m_second_point[n_global_types::X];
        line.m_second_point[n_global_types::X] = _temp;
    }
    // Ось Y
    else if (axis == 1) {
        double _temp = line.m_first_point[n_global_types::Y];
        line.m_first_point[n_global_types::Y] = line.m_second_point[n_global_types::Y];
        line.m_second_point[n_global_types::Y] = _temp;
    }
}
// --------------------------------------------------------

void N_inter::n_profiler::n_velocity::n_none_prof::n_aux::opposite_points_speed_profile_y(QVector<n_global_types::C_point> &points) {
    for (int i = 0; i < points.size(); i++) {
        points[i][n_global_types::Y] *= -1;
    }
}
// --------------------------------------------------------

bool N_inter::n_profiler::n_velocity::n_none_prof::n_aux::movement_in_opposite_direction(n_global_types::C_m_line &line, int axis) {
    // Ось X
    if (axis == 0) {
        return N_inter::n_algebra::n_math::is_more_than(line.m_first_point[n_global_types::X], line.m_second_point[n_global_types::X]);
    }
    // Ось Y
    else if (axis == 1) {
        return N_inter::n_algebra::n_math::is_more_than(line.m_first_point[n_global_types::Y], line.m_second_point[n_global_types::Y]);
    }
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_velocity_lines N_inter::n_profiler::n_velocity::n_none_prof::proxy_inter(QVector<n_global_types::C_m_line> &lines) {
    N_inter::n_motion_calc::n_types::C_motion_velocity_lines motionVel = inter(lines);

    // Удаление вырожденных прямых
    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        n_geom::n_lines::remove_empty_lines(motionVel[n_global_types::X]);
    }

    N_inter::n_motion_calc::n_types::C_motion motion; // Сегменты разложения движения по осям

    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        motion[current_axis] = N_inter::n_motion_calc::n_convert::kline_vector_to_kmotion_segment_vector(motionVel[current_axis]);
    }

    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        if (motion[current_axis].size() != lines.size()) {
            // TODO: make exception Число линий не равно числу сегментов
        }
    }

    // Удаление вырожденных прямых
    // Lines::remove_empty_lines(motionVel.Axis1);
    // Lines::remove_empty_lines(motionVel.Axis2);

    return N_inter::n_motion_calc::n_convert::kmotion_to_motion_velocity(motion);
}
// --------------------------------------------------------

// TODO: очень слабое место для расширения осей. Добавить циклы
N_inter::n_motion_calc::n_types::C_motion_velocity_lines N_inter::n_profiler::n_velocity::n_none_prof::inter(QVector<n_global_types::C_m_line> &lines) {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_motion_calc::n_types::C_motion_velocity_lines NoneProfVelocity::_inter(QVector<C_m_line>& lines)";
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Количество отрезков равно нулю";
        throw exc;
    }

    // Результат, очистка осей
    N_inter::n_motion_calc::n_types::C_motion_velocity_lines motionVel;
    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        motionVel[current_axis].clear();
    }

    // Накопленное время для осей
    double aTimeX = 0, aTimeY = 0;

    // Обход векторов, профилирование
    for (int i = 0; i < lines.size(); i++) {
        N_inter::n_global_types::C_m_line line = lines.at(i);

        double prevATimeX = aTimeX, prevATimeY = aTimeY;

        // TODO: слабое место для расширения осей

        QVector<N_inter::n_global_types::C_point> pointsX = n_aux::proxy_inter(line, aTimeX, 0);
        QVector<N_inter::n_global_types::C_point> pointsY = n_aux::proxy_inter(line, aTimeY, 1);

        // Округение точек до нуля (если в окрестности вычислительной ошибки)
        N_inter::n_geom::n_points::to_necessary_zero(pointsX);
        N_inter::n_geom::n_points::to_necessary_zero(pointsY);

        // Если хотя бы вдоль одной из осей есть движение
        if (!N_inter::n_algebra::n_math::is_equal(N_inter::n_algebra::n_math::get_sum(prevATimeX, prevATimeY), N_inter::n_algebra::n_math::get_sum(aTimeX, aTimeY))) {
            // Если необходимо выполнить синхронизацию осей
            if (!N_inter::n_algebra::n_math::is_equal(aTimeX, aTimeY)) {
                // Временная точка синхронизации
                double newTime = N_inter::n_algebra::n_limits::max(aTimeX, aTimeY);

                // TODO: Заменить тип исключения
                // Замедление по необходимости
                pointsX = N_inter::n_geom::n_points::correct_area_by_time(pointsX, newTime, 0);
                pointsY = N_inter::n_geom::n_points::correct_area_by_time(pointsY, newTime, 0);

                // qDebug() << "aTimeX:" << aTimeX << "aTimeY:" << aTimeY;

                aTimeX = newTime;
                aTimeY = newTime;
            }

            // Запись результата
            n_geom::n_lines::append_to_line_lines_from_points(motionVel[n_global_types::X], pointsX);
            n_geom::n_lines::append_to_line_lines_from_points(motionVel[n_global_types::Y], pointsY);
        }
    }

    return motionVel;
}
// --------------------------------------------------------
