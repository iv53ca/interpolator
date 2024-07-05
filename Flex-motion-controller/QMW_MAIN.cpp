#include "QMW_MAIN.h"
#include "ui_QMW_MAIN.h"
#include "Plots/N_plots.h"
#include "N_inter/C_inter.h"
#include "N_inter/S_exception.h"
#include <QMessageBox>
#include "N_inter/N_motion_calc/n_load.h"
#include "N_inter/N_motion_calc/n_generate.h"
#include "N_inter/N_global_types/S_trajectory_input.h"
#include "N_inter/N_motion_calc/n_convert.h"
#include "N_inter/N_global_types/C_point.h"
#include <chrono>
#include <QDebug>
// --------------------------------------------------------

using N_inter::S_exception;
// --------------------------------------------------------

QMW_MAIN::QMW_MAIN(QWidget *parent) : QMainWindow(parent), ui(new Ui::QMW_MAIN) {
    ui->setupUi(this);

    n_plots::m_ui = ui;
    n_plots::m_parent = this;
    n_plots::set_signals();
    n_plots::set_params();

    ui->LE_TEST_FILENAME->setText("Test_lines.txt");
    ui->TE_LINES->setText("[0, 0, 5, 2, 1]");

    ui->LE_X0_TURN->setText("0");
    ui->LE_Y0_TURN->setText("0");
    ui->LE_SEG1_LENGTH_TURN->setText("5");
    ui->LE_SEG2_LENGTH_TURN->setText("5");
    ui->LE_SEG3_LENGTH_TURN->setText("5");
    ui->LE_ANGLE_DIV_TURN->setText("12");
    ui->LE_CIRCLE_DIV_TURN->setText("2");

    ui->LE_SEG_COUNT_POLYGON->setText("3");
    ui->LE_SEG_LENGTH_POLYGON->setText("1");
    ui->LE_ANGLE_POLYGON->setText("0");
    ui->LE_X0_POLYGON->setText("0");
    ui->LE_Y0_POLYGON->setText("0");

    ui->LE_X0_NINJA->setText("0");
    ui->LE_Y0_NINJA->setText("0");
    ui->LE_OUTER_RADIUS_NINJA->setText("2");
    ui->LE_INNEAR_RADIUS_NINJA->setText("1");
    ui->LE_SEG_COUNT_NINJA->setText("8");

    ui->LE_A_SAW->setText("2");
    ui->LE_STEP_SAW->setText("1");
    ui->LE_COUNT_SAW->setText("4");
}
// --------------------------------------------------------

QMW_MAIN::~QMW_MAIN() { delete ui; }
// --------------------------------------------------------

void QMW_MAIN::on_PB_CALC_MOTION_clicked() {
    int circle_dev = ui->LE_CIRCLE_DIV_TURN->text().toInt();
    N_inter::n_data::n_motion_vars::n_calc_vars::split_segments_count = circle_dev;

    // Очистка графиков
    n_plots::clear();

    // Очистка списков
    C_inter::clear_data();

    try {
        // Расчёт
        C_inter::calc(ui->TE_LINES->toPlainText());

        // Отображение таблицы движений
        ui->TB_MOVE_TABLE->setText(N_inter::n_motion_calc::n_convert::to_string(C_inter::m_motion_table));
        // Отображение графиков

        n_plots::draw_plots(C_inter::m_trajectory, C_inter::m_motion[N_inter::n_global_types::X], C_inter::m_motion[N_inter::n_global_types::Y]);
        if (!ui->CB_IGNORE_SUCCESS_QMB->isChecked()) {
            QMessageBox::information(this, "Успех", "Разложение движения прошло успешно");
        }
        // qDebug() << "Успех, разложение движения просто успешно";
        // qDebug() << ui->TE_LINES->toPlainText();
    }
    catch(N_inter::S_exception exc) {
        // qDebug() << "К сожалению, что-то пошло не так не унывай, всё получится";
        // exc.show_message();
        // return;
        n_plots::draw_plots(C_inter::m_trajectory, C_inter::m_motion[N_inter::n_global_types::X], C_inter::m_motion[N_inter::n_global_types::Y]);
        throw exc;
    }
}
// --------------------------------------------------------

void QMW_MAIN::on_PB_CLEAR_clicked() {
    ui->TB_MOVE_TABLE->clear();
    ui->TE_LINES->clear();
    // TODO обвернуть в пространство имён QMW_MAIN
    n_plots::clear();
}
// --------------------------------------------------------

void QMW_MAIN::on_PB_TEST_clicked() {
    int circle_dev = ui->LE_CIRCLE_DIV_TURN->text().toInt();
    N_inter::n_data::n_motion_vars::n_calc_vars::split_segments_count = circle_dev;

    qDebug() << "Внимание: сегодня проверяем только профилирование скорости";
    // Чтение строк из заранее подготовленного файла

    QStringList segments = N_inter::n_motion_calc::n_load::load_from_file(ui->LE_TEST_FILENAME->text());

    // auto begin = std::chrono::steady_clock::now();

    // Перебор строк, запуск интерполятора
    for (int i = 0; i < segments.size(); i++) {
        ui->TE_LINES->clear();
        // ui->TE_LINES->append("M_BEGIN_PROF");
        ui->TE_LINES->append(segments[i]);
        // ui->TE_LINES->append("M_END_PROF");
        try {
            on_PB_CALC_MOTION_clicked();
        }
        catch(N_inter::S_exception exc) {
            qDebug() << "К сожалению, что-то пошло не так не унывай, всё получится";
            exc.show_message();
            return;
        }
    }
    // auto end = std::chrono::steady_clock::now();
    // qDebug() << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms";
}
// --------------------------------------------------------

void QMW_MAIN::on_PB_GENERATE_TURN_clicked() {
    QString file_name = ui->LE_TEST_FILENAME->text();

    double x0 = ui->LE_X0_TURN->text().toDouble();
    double y0 = ui->LE_Y0_TURN->text().toDouble();

    double length1 = ui->LE_SEG1_LENGTH_TURN->text().toDouble();
    double length2 = ui->LE_SEG2_LENGTH_TURN->text().toDouble();
    double length3 = ui->LE_SEG3_LENGTH_TURN->text().toDouble();

    double angle_div = ui->LE_ANGLE_DIV_TURN->text().toDouble();

    try {
        if (ui->RB_SEGC_COUNT_2_TURN->isChecked()) {
            N_inter::n_motion_calc::n_generate::write_to_file_2(file_name, x0, y0, length1, length2, angle_div);
        }
        else if (ui->RB_SEGC_COUNT_3_TURN->isChecked()) {
            N_inter::n_motion_calc::n_generate::write_to_file_3(file_name, x0, y0, length1, length2, length3, angle_div);
        }
    }
    catch (S_exception exc) {
        exc.show_message();
    }

    QMessageBox::information(this, "Успех", "Отрезки сгенерированы");
}
// --------------------------------------------------------

void QMW_MAIN::on_PB_GENERATE_POLYGON_clicked() {
    QString file_name = ui->LE_TEST_FILENAME->text();

    double x0 = ui->LE_X0_POLYGON->text().toDouble();
    double y0 = ui->LE_Y0_POLYGON->text().toDouble();

    double R = ui->LE_SEG_LENGTH_POLYGON->text().toDouble();
    double n = ui->LE_SEG_COUNT_POLYGON->text().toDouble();
    double phi = ui->LE_ANGLE_POLYGON->text().toDouble();

    try {
        N_inter::n_motion_calc::n_generate::write_to_file_polygon(file_name, x0, y0, R, n, phi);
    }
    catch (S_exception exc) {
        exc.show_message();
    }

    QMessageBox::information(this, "Успех", "Отрезки сгенерированы");
}
// --------------------------------------------------------

void QMW_MAIN::on_PB_GENERATE_NINJA_clicked() {
    QString file_name = ui->LE_TEST_FILENAME->text();

    double x0 = ui->LE_X0_NINJA->text().toDouble();
    double y0 = ui->LE_Y0_NINJA->text().toDouble();

    double outer_radius = ui->LE_OUTER_RADIUS_NINJA->text().toDouble();
    double innear_radius = ui->LE_INNEAR_RADIUS_NINJA->text().toDouble();

    double n = ui->LE_SEG_COUNT_NINJA->text().toDouble();

    try {
        N_inter::n_motion_calc::n_generate::write_to_file_ninja(file_name, x0, y0, innear_radius, outer_radius, n);
    }
    catch (S_exception exc) {
        exc.show_message();
    }

    QMessageBox::information(this, "Успех", "Отрезки сгенерированы");
}
// --------------------------------------------------------

void QMW_MAIN::on_PB_GENERATE_SAW_clicked() {
    QString file_name = ui->LE_TEST_FILENAME->text();

    double A     = ui->LE_A_SAW->text().toDouble();
    double step  = ui->LE_STEP_SAW->text().toDouble();
    int    count = ui->LE_COUNT_SAW->text().toInt();

    try {
        N_inter::n_motion_calc::n_generate::write_to_file_saw(file_name, A, step, count);
    }
    catch (S_exception exc) {
        exc.show_message();
    }

    QMessageBox::information(this, "Успех", "Отрезки сгенерированы");
}
// --------------------------------------------------------

