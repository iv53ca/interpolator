#include "C_inter.h"
#include "S_exception.h"
#include "N_inter/N_motion_vars/n_data.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_global_types/S_trajectory_input.h"
#include "N_inter/N_motion_calc/n_convert.h"
#include "N_inter/N_motion_calc/n_motion_velocity_lines.h"
#include "N_inter/N_geom/n_points.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>/*
#include <DAQmx.h>*/

// --------------------------------------------------------

using N_inter::S_exception;
// --------------------------------------------------------

// Накопительное движение (вектор)
QVector<N_inter::n_motion_calc::n_types::C_motion_velocity_lines> C_inter::m_sum_motion;
QVector<N_inter::n_global_types::C_m_lines>                       C_inter::m_sum_trajectory;

// Накопительное движение
N_inter::n_motion_calc::n_types::C_motion_velocity_lines C_inter::m_motion;
N_inter::n_global_types::C_m_lines                       C_inter::m_trajectory;

// Таблица движений
N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table C_inter::m_motion_table;
// --------------------------------------------------------

void C_inter::trajectory_calc(QString source_lines, bool prof_enable) {
    N_inter::n_profiler::proxy_trajectory(source_lines, prof_enable, N_inter::n_data::n_motion_vars::trajectory);

    // Округение точек до нуля (если в окрестности вычислительной ошибки)
    N_inter::n_geom::n_lines::to_necessary_zero(N_inter::n_data::n_motion_vars::trajectory);

    m_trajectory = N_inter::n_data::n_motion_vars::trajectory;
    m_sum_trajectory.push_back(m_trajectory);
}
// --------------------------------------------------------

void C_inter::velocity_calc(bool prof_enable) {
    m_motion = N_inter::n_profiler::Velocity(m_trajectory, prof_enable);
    m_sum_motion.push_back(m_motion);
}
// --------------------------------------------------------

void C_inter::elementary_calc(QString source_lines, bool prof_enable) {
    try {
        trajectory_calc(source_lines, prof_enable);
        velocity_calc(prof_enable);
    }
    catch (S_exception exc) {
        exc.show_message();
    }
}
// --------------------------------------------------------

void C_inter::join_trajectory() {
    // Очистка m_trajectory
    m_trajectory.clear();

    // Объединение траекторий
    for (int i = 0; i < m_sum_trajectory.size(); i++) {
        m_trajectory.append(m_sum_trajectory[i]);
    }
    N_inter::n_data::n_motion_vars::trajectory = m_trajectory;
}
// --------------------------------------------------------

void C_inter::join_motion() {
    // Очистка m_motion
    for (int i = 0; i < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        m_motion[i].clear();
    }

    // Объединение движения
    for (int i = 0; i < m_sum_motion.size(); i++) {
        // Время смещения
        double time_offset = N_inter::n_motion_calc::n_motion_velocity_lines::get_motion_time(m_motion);
        // Смещение
        N_inter::n_motion_calc::n_motion_velocity_lines::set_motion_offset_by_time(m_sum_motion[i], time_offset);
        // Объединение движения
        for (int j = 0; j < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; j++) {
            m_motion[j].append(m_sum_motion[i][j]);
        }
    }
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table C_inter::get_kill_motion_table(N_inter::n_global_types::C_point &current_velocity) {
    N_inter::n_motion_calc::n_types::C_motion_velocity_lines motion = N_inter::n_motion_calc::n_motion_velocity_lines::get_kill_motion(current_velocity);
    return N_inter::n_motion_calc::n_convert::to_motion_table(motion);
}
// --------------------------------------------------------


void C_inter::calc(QString source_lines) {
    // Очистка списков
    clear_data();

    // Профилирование по частям
    QVector<N_inter::n_global_types::S_trajectory_input> trajectory_input = N_inter::n_motion_calc::n_convert::split_lines_from_qstring_by_commands(source_lines);
    for (int i = 0; i < trajectory_input.size(); i++) {
        elementary_calc(trajectory_input[i].trajectory, trajectory_input[i].prof_stat);
    }

    // Объединение траектории и движения
    join_trajectory();
    join_motion();

    // Обновление глобальных переменных
    N_inter::n_data::n_motion_vars::trajectory = m_trajectory;
    N_inter::n_data::n_motion_vars::motion     = m_motion;

    // Составление табицы движений
    m_motion_table = N_inter::n_motion_calc::n_convert::to_motion_table(m_motion);
    N_inter::n_data::n_motion_vars::motion_table = m_motion_table;
    size_t length = m_motion_table.size();

    QFile file("/Users/sofiakanukova/Documents/PosVelTime.txt"); // create a QFile object
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) { // open the file in write-only text mode
        QTextStream out(&file); // create a QTextStream object
        for(size_t i = 0; i < length; i++){
            N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table_item element = m_motion_table.at(i);
            N_inter::n_global_types::C_point position = element.m_position;
            N_inter::n_global_types::C_point velocity = element.m_velocity;
            double time = element.m_time;
            double x_pos = position[N_inter::n_global_types::X];
            double y_pos = position[N_inter::n_global_types::Y];
            double x_vel = velocity[N_inter::n_global_types::X];
            double y_vel = velocity[N_inter::n_global_types::Y];
            out << "x: " << x_pos << ", y: " << y_pos << ", Vx: " << x_vel << ", Vy: " << y_vel << ", time " << time << "\n"; // write to the file
        }
        file.close(); // close the file
    } else {
        qDebug() << "Failed to open file for writing.";
    }

}
// --------------------------------------------------------

void C_inter::clear_data() {
    // Очистка списков
    m_sum_motion.clear();
    m_sum_trajectory.clear();
    N_inter::n_profiler::clear_data();
}
// --------------------------------------------------------
