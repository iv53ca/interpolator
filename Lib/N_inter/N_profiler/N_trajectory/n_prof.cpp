#include "n_prof.h"
#include <QVector>
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_geom/n_bounds.h"
#include "N_inter/N_geom/n_circles.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_geom/n_points.h"
#include "N_inter/S_exception.h"
#include <QDebug>
#include "N_inter/N_geom/n_angles.h"
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_m_line> N_inter::n_profiler::n_trajectory::n_prof::n_aux::master_inter(QVector<n_global_types::C_m_line> &lines, double max_error, int split_segments_count) {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QVector<C_m_line> ProfTrajectory::_master_inter(QVector<C_m_line>& lines)";
        exc.m_condition = "lines.size() == 0)";
        exc.m_decision = "Вектор отрезков пуст";
        throw exc;
    }

    QVector<N_inter::n_global_types::C_m_line> result, sourceLinesCopy(lines); // Результат и копия входных отрезков

    // Обход массива прямых, сглаживание углов
    for (int i = 0; i < sourceLinesCopy.size() - 1; i++) {
        // Образующие (или нет) угол прямые
        N_inter::n_global_types::C_m_line line1 = sourceLinesCopy.at(i), line2 = sourceLinesCopy.at(i + 1);

        // Установка параметров для прямых
        n_geom::n_lines::set_line_params(line1); n_geom::n_lines::set_line_params(line2);

        n_global_types::S_inter_circle circle; // Вписываемая в угол окружность
        QVector<N_inter::n_global_types::C_point> circlePoints; // Массив точек окружности

        bool stat = false; // Статус выполнения операции профилирования

        // Профилирование линий
        n_aux::segments_inter(line1, line2, circle, circlePoints, stat, max_error, split_segments_count);

        // Корректировка границ
        n_geom::n_lines::set_line_params(line1); n_geom::n_lines::set_line_params(line2);
        sourceLinesCopy[i] = line1;
        sourceLinesCopy[i + 1] = line2;

        // В зависимости от статуса выполнения операции профилирования в результат записываются либо только две исходные прямые
        if (!stat) {
            result.push_back(line1);
            // result.push_back(line2);
        }
        // Либо и отрезки окружности
        else {
            // Первая линия
            result.push_back(line1);

            // Минимальная скорость
            double minF = line1.velocity;
            if (minF < line2.velocity) {
                minF = line2.velocity;
            }

            // Отрезки окружности
            for (int i = 0; i < circlePoints.size() - 1; i++) {
                // Точки
                N_inter::n_global_types::C_point point1 = circlePoints.at(i), point2 = circlePoints.at(i + 1);

                // Формирование отрезка
                N_inter::n_global_types::C_m_line line;
                line.m_first_point[n_global_types::X] = point1[n_global_types::X]; line.m_first_point[n_global_types::Y] = point1[n_global_types::Y];
                line.m_second_point[n_global_types::X] = point2[n_global_types::X]; line.m_second_point[n_global_types::Y] = point2[n_global_types::Y];
                line.velocity = minF;
                result.push_back(line);
            }
        }
    }

    return result;
}
// --------------------------------------------------------

void N_inter::n_profiler::n_trajectory::n_prof::n_aux::segments_inter(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2, n_global_types::S_inter_circle &circle, QVector<n_global_types::C_point> &circlePoints, bool &stat, double max_error, int split_segments_count) {
    // Вписывание окружности в угол, определение статуса успешности операции
    bool fitCircleStat = false;
    circle = n_geom::n_circles::fit(line1, line2, fitCircleStat, max_error);

    // Если окружность в угол вписать нельзя, то прервать работу профилировщика
    if (!fitCircleStat) {
        if (N_inter::n_geom::n_lines::is_co_directional_lines(line1, line2)) {
            // qDebug() << "Не удалось вписать окружность для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(сонаправленные)";
        }
        else if (!N_inter::n_geom::n_lines::is_line_length_more_than_max_line_error(line1)) {
            // qDebug() << "Не удалось вписать окружность для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(line1 слишком короткая)";
        }
        else if (N_inter::n_geom::n_angles::is_ultra_0_angle(line1, line2)) {
            // qDebug() << "Не удалось вписать окружность для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(сверх-маленький угол)";
        }
        else if (N_inter::n_geom::n_angles::is_ultra_180_angle(line1, line2)) {
            // qDebug() << "Не удалось вписать окружность для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(сверх-развёрнутый угол)";
        }
        else if (!N_inter::n_geom::n_lines::is_line_length_more_than_max_line_error(line2)) {
            // qDebug() << "Не удалось вписать окружность для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(line2 слишком короткая)";
        }
        else {
            qDebug() << "Не удалось вписать окружность для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(причина неизвестна)";
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "else";
            exc.m_decision = QString("Не удалось вписать окружность для прямых %1 и %2 (причина неизвестна)").arg(line1.m_to_string()).arg(line2.m_to_string());
            throw exc;
        }
        stat = false;
        return;
    }

    // Точки касания для окружности и угла
    N_inter::n_global_types::C_point point1, point2;

    point1[n_global_types::X] = circle.m_intersec_point_1[n_global_types::X];
    point1[n_global_types::Y] = circle.m_intersec_point_1[n_global_types::Y];

    point2[n_global_types::X] = circle.m_intersec_point_2[n_global_types::X];
    point2[n_global_types::Y] = circle.m_intersec_point_2[n_global_types::Y];

    // Сопоставление точек касания прямым, корректировка отрезков
    N_inter::n_global_types::C_m_line newLine1, newLine2;
    if (n_geom::n_points::is_in_line(line1, point1)) {
        newLine1 = n_geom::n_bounds::correct_first_line_bound(line1, line2, point1);
        newLine2 = n_geom::n_bounds::correct_second_line_bound(line1, line2, point2);
    }
    else {
        newLine1 = n_geom::n_bounds::correct_first_line_bound(line1, line2, point2);
        newLine2 = n_geom::n_bounds::correct_second_line_bound(line1, line2, point1);
    }

    // Сортировка точек окружности для корректного обхода машиной
    n_geom::n_circles::sort_circle_points(circlePoints, circle, point1, point2, split_segments_count);

    // Обновление границ для прямых
    line1 = newLine1;
    line2 = newLine2;

    stat = true;
}
// --------------------------------------------------------

// --------------------------------------------------------

/*void N_inter::n_profiler::n_trajectory::n_prof::n_aux::parabolic_segments_inter(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2, n_global_types::S_inter_circle &circle, QVector<n_global_types::C_point> &circlePoints, bool &stat, double max_error, int split_segments_count) {
    // Вписывание окружности в угол, определение статуса успешности операции
    bool fitCircleStat = false;
    circle = n_geom::n_parabolas::fit(line1, line2, fitCircleStat, max_error);

    // Если окружность в угол вписать нельзя, то прервать работу профилировщика
    if (!fitCircleStat) {
        if (N_inter::n_geom::n_lines::is_co_directional_lines(line1, line2)) {
            // qDebug() << "Не удалось вписать параболу для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(сонаправленные)";
        }
        else if (!N_inter::n_geom::n_lines::is_line_length_more_than_max_line_error(line1)) {
            // qDebug() << "Не удалось вписать параболу для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(line1 слишком короткая)";
        }
        else if (N_inter::n_geom::n_angles::is_ultra_0_angle(line1, line2)) {
            // qDebug() << "Не удалось вписать параболу для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(сверх-маленький угол)";
        }
        else if (N_inter::n_geom::n_angles::is_ultra_180_angle(line1, line2)) {
            // qDebug() << "Не удалось вписать параболу для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(сверх-развёрнутый угол)";
        }
        else if (!N_inter::n_geom::n_lines::is_line_length_more_than_max_line_error(line2)) {
            // qDebug() << "Не удалось вписать параболу для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(line2 слишком короткая)";
        }
        else {
            qDebug() << "Не удалось вписать параболу для прямых" << line1.m_to_string() << "и" << line2.m_to_string() << "(причина неизвестна)";
            S_exception exc;
            exc.m_calling_object = Q_FUNC_INFO;
            exc.m_condition = "else";
            exc.m_decision = QString("Не удалось вписать параболу для прямых %1 и %2 (причина неизвестна)").arg(line1.m_to_string()).arg(line2.m_to_string());
            throw exc;
        }
        stat = false;
        return;
    }

    // Точки касания для окружности и угла
    N_inter::n_global_types::C_point point1, point2;

    point1[n_global_types::X] = parabola.m_intersec_point_1[n_global_types::X];
    point1[n_global_types::Y] = parabola.m_intersec_point_1[n_global_types::Y];

    point2[n_global_types::X] = parabola.m_intersec_point_2[n_global_types::X];
    point2[n_global_types::Y] = parabola.m_intersec_point_2[n_global_types::Y];

    // Сопоставление точек касания прямым, корректировка отрезков
    N_inter::n_global_types::C_m_line newLine1, newLine2;
    if (n_geom::n_points::is_in_line(line1, point1)) {
        newLine1 = n_geom::n_bounds::correct_first_line_bound(line1, line2, point1);
        newLine2 = n_geom::n_bounds::correct_second_line_bound(line1, line2, point2);
    }
    else {
        newLine1 = n_geom::n_bounds::correct_first_line_bound(line1, line2, point2);
        newLine2 = n_geom::n_bounds::correct_second_line_bound(line1, line2, point1);
    }

    // Сортировка точек окружности для корректного обхода машиной
    n_geom::n_parabolas::sort_parabola_points(circlePoints, circle, point1, point2, split_segments_count);

    // Обновление границ для прямых
    line1 = newLine1;
    line2 = newLine2;

    stat = true;
}
// --------------------------------*/

QVector<N_inter::n_global_types::C_m_line> N_inter::n_profiler::n_trajectory::n_prof::inter(QVector<n_global_types::C_m_line> &lines, double max_error, int split_segments_count) {
    QVector<N_inter::n_global_types::C_m_line> result = n_aux::master_inter(lines, max_error, split_segments_count);

    // Добавление крайнего справа отрезка
    N_inter::n_global_types::C_m_line back = lines.back();
    back.m_first_point[n_global_types::X] = result.back().m_second_point[n_global_types::X];
    back.m_first_point[n_global_types::Y] = result.back().m_second_point[n_global_types::Y];

    result.push_back(back);

    // debug
    if (!N_inter::n_algebra::n_math::is_equal(lines.back().m_second_point[n_global_types::X], result.back().m_second_point[n_global_types::X])) {
        N_inter::S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!n_algebra::n_math::is_equal(lines.back().m_second_point[n_global_types::X], result.back().m_second_point[n_global_types::X])";
        exc.m_decision = "Точки не совпадают (Х)";
        throw exc;
    }

    // debug
    if (!N_inter::n_algebra::n_math::is_equal(lines.back().m_second_point[n_global_types::Y], result.back().m_second_point[n_global_types::Y])) {
        N_inter::S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!n_algebra::n_math::is_equal(lines.back().m_second_point[n_global_types::Y], result.back().m_second_point[n_global_types::Y])";
        exc.m_decision = "Точки не совпадают (У)";
        throw exc;
    }

    return result;
}
// --------------------------------------------------------
