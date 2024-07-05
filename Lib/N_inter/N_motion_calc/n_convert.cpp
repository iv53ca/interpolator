#include "n_convert.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_algebra/n_math.h"
#include <QStringList>
#include "N_inter/N_motion_vars/n_commands.h"
#include "N_inter/N_motion_calc/n_motion_velocity_lines.h"
#include "N_inter/N_global_types/C_point.h"
// --------------------------------------------------------

using N_inter::n_global_types::C_point;
using N_inter::S_exception;
using N_inter::n_global_types::C_m_line;
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_m_line> N_inter::n_motion_calc::n_convert::kmotion_segments_vector_to_kline_vector(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments) {
    if (segments.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QVector<C_m_line> KConvert::kmotion_segments_vector_to_kline_vector(QVector<n_motion_calc::n_types::C_motion_section>& segments)";
        exc.m_condition = "segments.size() == 0";
        exc.m_decision = "Нет элементов для конвертирования";
        throw exc;
    }

    QVector<n_global_types::C_m_line> result;
    for (int i = 0; i < segments.size(); i++) {
        QVector<n_global_types::C_m_line> lines = kmotion_segment_to_kline_vector(segments[i]);
        for (int j = 0; j < lines.size(); j++) {
            result.push_back(lines.at(j));
        }
    }

    return result;
}
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_m_line> N_inter::n_motion_calc::n_convert::kmotion_segment_to_kline_vector(N_inter::n_motion_calc::n_types::C_motion_section &segment) {
    if (segment.get_size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QVector<C_m_line> KConvert::kmotion_segment_to_kline_vector(n_motion_calc::n_types::C_motion_section& segment)";
        exc.m_condition = "segment.get_size() == 0";
        exc.m_decision = "Нет элементов для конвертирования";
        throw exc;
    }

    QVector<n_global_types::C_m_line> result;
    for (int i = 0; i < segment.get_size(); i++) {
        result.push_back(segment[i]);
    }

    return result;
}
// --------------------------------------------------------

QVector<N_inter::n_motion_calc::n_types::C_motion_section> N_inter::n_motion_calc::n_convert::kline_vector_to_kmotion_segment_vector(QVector<n_global_types::C_m_line> &lines) {
    if (lines.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "QVector<n_motion_calc::n_types::C_motion_section> KConvert::kline_vector_to_kmotion_segment_vector(QVector<C_m_line>& lines)";
        exc.m_condition = "lines.size() == 0";
        exc.m_decision = "Нет элементов для конвертирования";
        throw exc;
    }

    // Перевод вектора отрезков в вектор сегментов движения. Опорной точкой считается точка с нулевой скоростью (ординатой)
    QVector<N_inter::n_motion_calc::n_types::C_motion_section> result;
    N_inter::n_motion_calc::n_types::C_motion_section segment;

    // Разбиение на сегменты
    for (int i = 0; i < lines.size(); i++) {
        // Проверка прямой на точку (в таком случае добавлять её не нужно)
        if (n_geom::n_lines::is_empty_line(lines[i])) {
            lines.removeAt(i);
            i--;
            continue;
            // N_inter::S_exception exc;
            // exc.m_calling_object = "QVector<n_motion_calc::n_types::C_motion_section> KConvert::kline_vector_to_kmotion_segment_vector(QVector<C_m_line>& lines)";
            // exc.m_condition = "n_geom::n_lines::is_empty_line(lines[i])";
            // exc.m_decision = "Прямая является точкой";
            // throw exc;
        }
        if (lines[i].m_second_point[n_global_types::Y] == 0) {
            segment.push_back(lines.at(i));
            result.push_back(segment);
            segment.clear();
        }
        else {
            segment.push_back(lines.at(i));
        }
    }

    return result;
}
// --------------------------------------------------------

#warning Отрезки движения должны иметь прерывный профиль. За сегмент движения считается набор отрезков, конечный их которых в качестве второй точки по оси скорости имеет ноль
N_inter::n_motion_calc::n_types::C_motion N_inter::n_motion_calc::n_convert::C_motion_velocity_lines_to_C_motion(n_types::C_motion_velocity_lines &motion_velocity_lines) {
    N_inter::n_motion_calc::n_types::C_motion result;
    QVector<n_motion_calc::n_types::C_motion_section> current_sections;
    n_motion_calc::n_types::C_motion_section current_section;

    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        current_sections.clear();
        current_section.clear();
        for (int i = 0; i < motion_velocity_lines[current_axis].size(); i++) {
            N_inter::n_global_types::C_m_line current_line = motion_velocity_lines[current_axis][i];
            // Если этот отрезок завершает начатый сегмент
            if (N_inter::n_algebra::n_math::is_equal(current_line.m_second_point[N_inter::n_global_types::Y], 0)) {
                current_section.push_back(current_line);
                current_sections.push_back(current_section);
                current_section.clear();
            }
            // Если этот отрезок продолжает существующий или начинает новый сегмент
            else {
                current_section.push_back(current_line);
            }
        }
        result[current_axis] = current_sections;
    }
    return result;
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_velocity_lines N_inter::n_motion_calc::n_convert::kmotion_to_motion_velocity(N_inter::n_motion_calc::n_types::C_motion &motion) {
    for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        if (motion[current_axis].size() == 0) {
            // TODO make mistake "Нет элементов для конвертирования"
        }
    }

    N_inter::n_motion_calc::n_types::C_motion_velocity_lines result;

    for (int current_axis = 0; current_axis < n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        result[current_axis] = kmotion_segments_vector_to_kline_vector(motion[current_axis]);
    }

    return result;
}
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_m_line> N_inter::n_motion_calc::n_convert::save_lines_from_qstring(QString sourceLines) {
    QVector<n_global_types::C_m_line> result;
    // Разделение на строки, удаление символов "[", "]", и ","
    QString linesTeContent = sourceLines;
    linesTeContent.replace("[", "");
    linesTeContent.replace("]", "");
    linesTeContent.replace(",", "");

    if (linesTeContent == "") {
        N_inter::S_exception exc;
        exc.m_calling_object = "QVector<C_m_line> Convert::SaveLinesFromQstring(QString sourceLines)";
        exc.m_condition = "linesTeContent == \"\"";
        exc.m_decision = "Строка не содержит текстовое представение отрезков";
        throw exc;
        throw "[Convert::SaveLinesFromQstring] linesTeContent == \"\"";
    }

    // Запись линий в C_m_lines
    QStringList lines = linesTeContent.split("\n");

    // Удаление пустых строк
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].isEmpty()) {
            lines.removeAt(i);
            i--;
        }
    }

    // qDebug() << lines;
    for (int i = 0; i < lines.size(); i++) {
        QString line = lines.at(i);
        QStringList numbers = line.split(" ");

        if (numbers.size() != N_inter::n_data::n_motion_vars::n_calc_vars::axis_count*N_inter::n_data::n_motion_vars::n_calc_vars::axis_count + 1) {
            N_inter::S_exception exc;
            exc.m_calling_object = "QVector<C_m_line> Convert::SaveLinesFromQstring(QString sourceLines)";
            exc.m_condition = "numbers.size() != N_inter::n_data::n_motion_vars::n_calc_vars::axis_count*N_inter::n_data::n_motion_vars::n_calc_vars::axis_count + 1";
            exc.m_decision = QString("Неверное количество аргументов: <<%1>>").arg(line);
            throw exc;
        }

        n_global_types::C_m_line kLine;
        int step = 0;
        for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
            // Округление до 0, если значение находится в пределах ошибки вычислений
            double val = numbers.at(step).toDouble();
            N_inter::n_algebra::n_math::to_necessary_zero(val);
            kLine.m_first_point[current_axis] = val;
            step++;
        }
        for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
            // Округление до 0, если значение находится в пределах ошибки вычислений
            double val = numbers.at(step).toDouble();
            N_inter::n_algebra::n_math::to_necessary_zero(val);
            kLine.m_second_point[current_axis] = val;
            step++;
        }
        kLine.velocity  = numbers.at(step).toDouble();
        // A B C Begin End поля не инициализированы

        // Если линия пустая (типа [10, 10, 10, 10, velocity]), то её добавлять не нужно
        if (!N_inter::n_geom::n_lines::is_empty_line(kLine)) {
            result.append(kLine);
        }
    }

    return result;
}
// --------------------------------------------------------

QVector<N_inter::n_global_types::S_trajectory_input> N_inter::n_motion_calc::n_convert::split_lines_from_qstring_by_commands(QString lines) {
    // Обработка команд начала и конца профилирования
    QVector<N_inter::n_global_types::S_trajectory_input> result;

    QVector<QString> str_lines = lines.split("\n").toVector();

    bool prof_stat = false; // Не задействовать профилирование
    QString curr_str_lines = "";
    for (int i = 0; i < str_lines.size(); i++) {
        // Команды "Начать профилирование" или "Завершить профилирование"
        if ((str_lines[i] == N_inter::n_data::n_motion_vars::n_commands::begin_prof) || (str_lines[i] == N_inter::n_data::n_motion_vars::n_commands::end_prof)) {
            // Запись текущего curr_track в result со статусом prof_stat
            // Если есть линии
            if (curr_str_lines != "") {
                N_inter::n_global_types::S_trajectory_input curr_input;
                curr_input.trajectory = curr_str_lines;
                curr_input.prof_stat = prof_stat;
                result.push_back(curr_input);
                curr_str_lines.clear();
            }
            // Смена статуса операции профилирования (true - begin_prof, false - end_prof)
            prof_stat = (str_lines[i] == N_inter::n_data::n_motion_vars::n_commands::begin_prof);
        }
        // Отрезок движения
        else {
            curr_str_lines = curr_str_lines + str_lines[i] + "\n";
        }
    }
    // Если остаись ещё строки, то записать
    if (curr_str_lines != "") {
        N_inter::n_global_types::S_trajectory_input curr_input;
        curr_input.trajectory = curr_str_lines;
        curr_input.prof_stat = prof_stat;
        result.push_back(curr_input);
        curr_str_lines.clear();
    }

    return result;
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table N_inter::n_motion_calc::n_convert::to_motion_table(n_types::C_motion_velocity_lines &motion_lines) {
    // Временной шаг
    double time_step = N_inter::n_data::n_motion_vars::n_calc_vars::time_step_for_motion_table;

    // Время начала и остановки движения
    double begin_time = 0;
    double end_time = N_inter::n_motion_calc::n_motion_velocity_lines::get_motion_time(motion_lines);

    // Таблица движений
    N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table motion_table;

    // Перебор движения, составление таблицы движения
    while (!N_inter::n_algebra::n_math::is_more_than(begin_time, end_time)) {
        // Добавляемая точка смещения
        C_point current_offset;

        // Добавляемая проекция скорости
        C_point current_velocity;

        // Получение смещений вдоль каждой из осей
        for (int axis = 0; axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; axis++) {
            // Смещение
            current_offset[axis] = N_inter::n_motion_calc::n_motion_velocity_lines::get_time_offset_for_axis(motion_lines, begin_time, axis);
            // Скорость
            current_velocity[axis] = N_inter::n_motion_calc::n_motion_velocity_lines::get_vel_offset_for_axis(motion_lines, begin_time, axis);
        }

        // Элемент таблицы движений
        N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table_item motion_table_item;
        motion_table_item.m_position = current_offset;
        motion_table_item.m_velocity = current_velocity;
        motion_table_item.m_time = begin_time;

        // Обновление таблицы движений
        motion_table.push_back(motion_table_item);

        // Временной шаг
        begin_time = begin_time + time_step;
    }

    return motion_table;
}
// --------------------------------------------------------

QString N_inter::n_motion_calc::n_convert::to_string(n_types::n_motion_table::S_motion_table &motion_table) {
    QString result = "";

    // Перебор таблицы движений
    for (int i = 0; i < motion_table.size(); i++) {
        result = result + to_string(motion_table[i]) + "\n";
    }

    // Удаление последнего символа переноса строки
    result = result.remove(result.size() - 1, 1);

    return result;
}
// --------------------------------------------------------

QString N_inter::n_motion_calc::n_convert::to_string(n_types::n_motion_table::S_motion_table_item &motion_table_item) {
    QString result = QString("POS: %1, VEL: %2, TIME: %3")
            .arg(motion_table_item.m_position.m_to_string())
            .arg(motion_table_item.m_velocity.m_to_string())
            .arg(motion_table_item.m_time);
    return result;
}
// --------------------------------------------------------

QVector<N_inter::n_global_types::C_m_line> N_inter::n_motion_calc::n_convert::to_lines_vector(QVector<n_global_types::C_point> points) {
    if (points.size() == 0) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "points.size() == 0";
        exc.m_decision = "Массив точек пустой";
        throw exc;
    }

    if (points.size() == 1) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "points.size() == 0";
        exc.m_decision = "Массив точек состоит из единственной точки";
        throw exc;
    }

    QVector<N_inter::n_global_types::C_m_line> result = {};

    for (int i = 0; i < points.size() - 1; i++) {
        C_m_line line;
        line.m_first_point = points[i];
        line.m_second_point = points[i + 1];
        result.push_back(line);
    }

    return result;
}
// --------------------------------------------------------
