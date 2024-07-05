#include "Plots/N_plots.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_algebra/n_math.h"
// --------------------------------------------------------

Ui::QMW_MAIN* n_plots::m_ui;
QMW_MAIN*     n_plots::m_parent;
// --------------------------------------------------------

void n_plots::n_slots::SLOT_VELOCITY_CP_X_RANGE_CHANGED(const QCPRange &range) {
    // Блокировка сигналов изменения области определения
    m_ui->CP_VELOCITY_X->xAxis->blockSignals(true);
    m_ui->CP_VELOCITY_Y->xAxis->blockSignals(true);

    // Обновление границ графиков
    if (m_ui->CP_VELOCITY_X->xAxis->range() == range) {
        m_ui->CP_VELOCITY_Y->xAxis->setRange(range);
    }
    else {
        m_ui->CP_VELOCITY_X->xAxis->setRange(range);
    }

    // Снятие блокировки сигналов изменения области определения
    m_ui->CP_VELOCITY_X->xAxis->blockSignals(false);
    m_ui->CP_VELOCITY_Y->xAxis->blockSignals(false);

    // Перерисовка графиков
    m_ui->CP_VELOCITY_X->replot();
    m_ui->CP_VELOCITY_Y->replot();
}
// --------------------------------------------------------

void n_plots::n_slots::SLOT_VELOCITY_CP_Y_RANGE_CHANGED(const QCPRange &range) {
    // Блокировка сигналов изменения области определения
    m_ui->CP_VELOCITY_X->yAxis->blockSignals(true);
    m_ui->CP_VELOCITY_Y->yAxis->blockSignals(true);

    // Обновление границ графиков
    if (m_ui->CP_VELOCITY_X->yAxis->range() == range) {
        m_ui->CP_VELOCITY_Y->yAxis->setRange(range);
    }
    else {
        m_ui->CP_VELOCITY_X->yAxis->setRange(range);
    }

    // Снятие блокировки сигналов изменения области определения
    m_ui->CP_VELOCITY_X->yAxis->blockSignals(false);
    m_ui->CP_VELOCITY_Y->yAxis->blockSignals(false);

    // Перерисовка графиков
    m_ui->CP_VELOCITY_X->replot();
    m_ui->CP_VELOCITY_Y->replot();
}
// --------------------------------------------------------

void n_plots::n_slots::SLOT_TRAJECTORY_CP_MOUSE_MOVE(QMouseEvent *event) {
    QCustomPlot* customPlot = qobject_cast<QCustomPlot*>(m_ui->CP_TRAJECTORY);
    double x = customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = customPlot->yAxis->pixelToCoord(event->pos().y());

    QString cord = QString("X: %1 Y: %2").arg(x).arg(y);
    m_ui->L_TRAJECTORY_COORD->setText(cord);
}
// --------------------------------------------------------

void n_plots::n_slots::SLOT_VELOCITY_X_CP_MOUSE_MOVE(QMouseEvent *event) {
    QCustomPlot* customPlot = qobject_cast<QCustomPlot*>(m_ui->CP_VELOCITY_X);
    double x = customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = customPlot->yAxis->pixelToCoord(event->pos().y());

    QString cord = QString("X: %1 Y: %2").arg(x).arg(y);
    m_ui->L_VELOCITY_COORD->setText(cord);
}
// --------------------------------------------------------

void n_plots::n_slots::SLOT_VELOCITY_Y_CP_MOUSE_MOVE(QMouseEvent *event) {
    QCustomPlot* customPlot = qobject_cast<QCustomPlot*>(m_ui->CP_VELOCITY_Y);
    double x = customPlot->xAxis->pixelToCoord(event->pos().x());
    double y = customPlot->yAxis->pixelToCoord(event->pos().y());

    QString cord = QString("X: %1 Y: %2").arg(x).arg(y);
    m_ui->L_VELOCITY_COORD->setText(cord);
}
// --------------------------------------------------------

void n_plots::n_draw::Clear(QCustomPlot *plot) {
    plot->clearPlottables();
    plot->clearGraphs();
    plot->replot();
}
// --------------------------------------------------------

void n_plots::n_draw::Draw(QCustomPlot *plot, QVector<N_inter::n_global_types::C_m_line> &lines, QPen pen, QBrush brush) {
    // Очистка графиков
    Clear(plot);

    // Идентификатор графа
    int count = 0;

    // Перебор отрезков
    for (int i = 0; i < lines.size(); i++) {
        // Формирование данных
        QVector<double> X, Y;

        X.push_back(lines[i].m_first_point[N_inter::n_global_types::X]);
        X.push_back(lines[i].m_second_point[N_inter::n_global_types::X]);

        Y.push_back(lines[i].m_first_point[N_inter::n_global_types::Y]);
        Y.push_back(lines[i].m_second_point[N_inter::n_global_types::Y]);

        // Добавление данных на график
        plot->addGraph();
        plot->graph(count)->addData(X, Y);
        plot->graph(count)->setPen(pen);
        plot->graph(count)->setBrush(brush);
        count++;

        // Перерисовка графика
        plot->replot();
    }
}
// --------------------------------------------------------

void n_plots::n_draw::Draw(QCustomPlot *plot, QVector<N_inter::n_global_types::C_m_line> &lines, QPen pen) {
    Draw(plot, lines, pen, QBrush());
}
// --------------------------------------------------------

void n_plots::n_draw::Draw(QCustomPlot *plot, QVector<N_inter::n_global_types::C_m_line> &lines, QBrush brush) {
    Draw(plot, lines, QPen(Qt::blue), brush);
}
// --------------------------------------------------------

void n_plots::n_draw::Draw(QCustomPlot *plot, QVector<N_inter::n_global_types::C_m_line> &lines) {
    Draw(plot, lines, QPen(Qt::blue), QBrush());
}
// --------------------------------------------------------

void n_plots::n_draw::SetParams(QCustomPlot *plot, QString xAxisLabel, QString yAxisLabel, QString title) {
    plot->setInteraction(QCP::iRangeDrag, true);
    plot->setInteraction(QCP::iRangeZoom, true);

    plot->xAxis->setLabel(xAxisLabel);
    plot->yAxis->setLabel(yAxisLabel);

    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, title, QFont("sans", 12, QFont::Bold)));

    plot->replot();
}
// --------------------------------------------------------

void n_plots::n_draw::WriteVelocityAxisLog(QTextBrowser *textBrowser, QVector<N_inter::n_global_types::C_m_line> &lines) {
    // Очистка
    textBrowser->clear();
    textBrowser->append(">>> S");

    double S = 0;

    // Запись информации о перемещениях
    for (int i = 0; i < lines.size(); i++) {
        N_inter::n_global_types::C_m_line line = lines.at(i);

        // Перемещение
        S = S + 0.5 * (line.m_first_point[N_inter::n_global_types::Y] + line.m_second_point[N_inter::n_global_types::Y]) * (line.m_second_point[N_inter::n_global_types::X] - line.m_first_point[N_inter::n_global_types::X]);

        QString str = "x1: %1\ny1: %2\nx2: %3\ny2: %4\ndx: %5\ndy: %6\nS: %7\n-------------------------";
        double x1 = std::trunc(lines[i].m_first_point[N_inter::n_global_types::X] * 100) / 100;
        double y1 = std::trunc(lines[i].m_first_point[N_inter::n_global_types::Y] * 100) / 100;
        double x2 = std::trunc(lines[i].m_second_point[N_inter::n_global_types::X] * 100) / 100;
        double y2 = std::trunc(lines[i].m_second_point[N_inter::n_global_types::Y] * 100) / 100;

        double dx = x2 - x1;
        double dy = y2 - y1;

        if (N_inter::n_algebra::n_math::is_equal(dx, dy) && N_inter::n_algebra::n_math::is_equal(dx, 0)) {
            continue;
        }
        str = str.arg(x1).arg(y1).arg(x2).arg(y2).arg(dx).arg(dy).arg(S);
        str = QString::number(S);
        textBrowser->append(str);
    }
}
// --------------------------------------------------------

void n_plots::set_params() {
    n_draw::SetParams(m_ui->CP_TRAJECTORY, "X", "Y", "Траектория движения в Oxy координатах");
    n_draw::SetParams(m_ui->CP_VELOCITY_X,  "t, с", "v, мм / с", "Профиль движения для оси X");
    n_draw::SetParams(m_ui->CP_VELOCITY_Y,  "t, с", "v, мм / с", "Профиль движения для оси Y");
}
// --------------------------------------------------------

void n_plots::draw_plots(QVector<N_inter::n_global_types::C_m_line> &trajectory, QVector<N_inter::n_global_types::C_m_line> &VelAxisX, QVector<N_inter::n_global_types::C_m_line> &VelAxisY) {
    // График траектории
    n_draw::Draw(m_ui->CP_TRAJECTORY, trajectory);

    // Графики скоростей без профилирования
    n_draw::Draw(m_ui->CP_VELOCITY_X, VelAxisX, QBrush(QColor(0, 0, 255, 20))); // X
    n_draw::Draw(m_ui->CP_VELOCITY_Y, VelAxisY, QBrush(QColor(0, 0, 255, 20))); // Y

    n_draw::WriteVelocityAxisLog(m_ui->TB_LOG_X, VelAxisX);
    n_draw::WriteVelocityAxisLog(m_ui->TB_LOG_Y, VelAxisY);
}
// --------------------------------------------------------

void n_plots::set_signals() {
    // Изменение области определения для оси абсцисс
    QObject::connect(m_ui->CP_VELOCITY_X->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), m_parent, &n_slots::SLOT_VELOCITY_CP_X_RANGE_CHANGED);
    QObject::connect(m_ui->CP_VELOCITY_Y->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), m_parent, &n_slots::SLOT_VELOCITY_CP_X_RANGE_CHANGED);

    QObject::connect(m_ui->CP_VELOCITY_X->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), m_parent, &n_slots::SLOT_VELOCITY_CP_X_RANGE_CHANGED);
    QObject::connect(m_ui->CP_VELOCITY_Y->xAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), m_parent, &n_slots::SLOT_VELOCITY_CP_X_RANGE_CHANGED);

    // Изменение области определения для оси ординат
    QObject::connect(m_ui->CP_VELOCITY_X->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), m_parent, &n_slots::SLOT_VELOCITY_CP_Y_RANGE_CHANGED);
    QObject::connect(m_ui->CP_VELOCITY_Y->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), m_parent, &n_slots::SLOT_VELOCITY_CP_Y_RANGE_CHANGED);

    QObject::connect(m_ui->CP_VELOCITY_X->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), m_parent, &n_slots::SLOT_VELOCITY_CP_Y_RANGE_CHANGED);
    QObject::connect(m_ui->CP_VELOCITY_Y->yAxis, QOverload<const QCPRange&>::of(&QCPAxis::rangeChanged), m_parent, &n_slots::SLOT_VELOCITY_CP_Y_RANGE_CHANGED);

    // Наведение мышкой
    QObject::connect(m_ui->CP_TRAJECTORY, &QCustomPlot::mouseMove, m_parent, &n_slots::SLOT_TRAJECTORY_CP_MOUSE_MOVE);
    QObject::connect(m_ui->CP_VELOCITY_X, &QCustomPlot::mouseMove, m_parent, &n_slots::SLOT_VELOCITY_X_CP_MOUSE_MOVE);
    QObject::connect(m_ui->CP_VELOCITY_Y, &QCustomPlot::mouseMove, m_parent, &n_slots::SLOT_VELOCITY_Y_CP_MOUSE_MOVE);
}
// --------------------------------------------------------

void n_plots::clear() {
    n_draw::Clear(m_ui->CP_TRAJECTORY);
    n_draw::Clear(m_ui->CP_VELOCITY_X);
    n_draw::Clear(m_ui->CP_VELOCITY_Y);
}
