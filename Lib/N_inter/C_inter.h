#pragma once
// --------------------------------------------------------

#include "N_inter/N_profiler/n_profiler.h"
#include "N_inter/N_global_types/C_segment/C_m_lines.h"
#include "N_inter/N_motion_calc/N_types/N_motion_table/S_motion_table.h"
#include "N_inter/N_global_types/C_point.h"
// --------------------------------------------------------

class C_inter  {
private:
    static void trajectory_calc(QString source_lines, bool prof_enable);
    static void velocity_calc(bool prof_enable);
    static void elementary_calc(QString source_lines, bool prof_enable);

    // Объединение траектории
    static void join_trajectory();

    // Объединение движения
    static void join_motion();

    // Накопительное движение (вектор)
    static QVector<N_inter::n_motion_calc::n_types::C_motion_velocity_lines> m_sum_motion;
    static QVector<N_inter::n_global_types::C_m_lines> m_sum_trajectory;
public:
    // TODO убрать и сделать доступ к переменным из n_data
    // Накопительное движение
    static N_inter::n_motion_calc::n_types::C_motion_velocity_lines m_motion;
    static N_inter::n_global_types::C_m_lines m_trajectory;
    static N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table m_motion_table;

    // Получить таблицу движения для аварии
    static N_inter::n_motion_calc::n_types::n_motion_table::S_motion_table get_kill_motion_table(N_inter::n_global_types::C_point& current_velocity);

    static void calc(QString source_lines);
    static void clear_data();
};
// --------------------------------------------------------
