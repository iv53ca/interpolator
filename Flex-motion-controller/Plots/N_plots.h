#pragma once
// --------------------------------------------------------

#include "Plots/QCustomPlot/qcustomplot.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_motion_vars/n_data.h"
#include "ui_QMW_MAIN.h"
#include "QMW_MAIN.h"
// --------------------------------------------------------

namespace n_plots {
    namespace {
        namespace n_slots {
            void SLOT_VELOCITY_CP_X_RANGE_CHANGED(const QCPRange& range);
            void SLOT_VELOCITY_CP_Y_RANGE_CHANGED(const QCPRange& range);

            void SLOT_TRAJECTORY_CP_MOUSE_MOVE(QMouseEvent* event);
            void SLOT_VELOCITY_X_CP_MOUSE_MOVE(QMouseEvent* event);
            void SLOT_VELOCITY_Y_CP_MOUSE_MOVE(QMouseEvent* event);
        }
        namespace n_draw {
            // Очистка данных для графика
            void Clear(QCustomPlot* plot);

            // Построение графика вектора отрезков с параметрами QPen и QBrush
            void Draw(QCustomPlot* plot, QVector<N_inter::n_global_types::C_m_line>& lines, QPen pen, QBrush brush);

            // Построение графика вектора отрезков с параметром QPen
            void Draw(QCustomPlot* plot, QVector<N_inter::n_global_types::C_m_line>& lines, QPen pen);

            // Построение графика вектора отрезков с параметром QBrush
            void Draw(QCustomPlot* plot, QVector<N_inter::n_global_types::C_m_line>& lines, QBrush brush);

            // Построение графика вектора отрезков без параметров
            void Draw(QCustomPlot* plot, QVector<N_inter::n_global_types::C_m_line>& lines);

            // Установка настроек для графика
            void SetParams(QCustomPlot* plot, QString xAxisLabel, QString yAxisLabel, QString title);

            // Запись лога для графика разложения движения по оси
            void WriteVelocityAxisLog(QTextBrowser* textBrowser, QVector<N_inter::n_global_types::C_m_line>& lines);
        }
    }
    extern Ui::QMW_MAIN* m_ui;
    extern QMW_MAIN* m_parent;
    void set_params();
    void draw_plots(QVector<N_inter::n_global_types::C_m_line>& trajectory, QVector<N_inter::n_global_types::C_m_line>& VelAxisX, QVector<N_inter::n_global_types::C_m_line>& VelAxisY);
    void set_signals();
    void clear();
}
