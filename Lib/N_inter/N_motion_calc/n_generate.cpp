#include "n_generate.h"
#include <QFile>
#include "N_inter/S_exception.h"
#include <QVector>
#include <cmath>
#include "N_inter/N_motion_calc/n_load.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include "N_inter/N_algebra/n_math.h"
// --------------------------------------------------------

using N_inter::S_exception;
// --------------------------------------------------------

// TODO: если отрезки не образуют угол, то сообщать

void N_inter::n_motion_calc::n_generate::write_to_file_2(QString filename, double x0, double y0, double seg1_length, double seg2_length, double angle_div) {
    // Открытие файла
    QFile file;
    file.setFileName(filename);
    file.open(QFile::WriteOnly);

    // Если файл не открыт - кидать исключение
    if (!file.isOpen()) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!file.isOpen()";
        exc.m_decision = "Файл не открыт";
        throw exc;
    }

    // Очистка содержимого
    file.resize(0);

    // Формирование строк

    // Число пи, угловое деление
    double pi = 3.1415926535;
    double step = angle_div;

    // Углы
    QVector<double> angles = {};
    double angle = 0;
    while (angle <= 2 * pi) {
        angles.push_back(angle);
        angle = angle + 2 * pi / step;
    }
    angles.push_back(2 * pi);

    // Строка для записи в файл
    QString file_str = "";

    // Цикл для угла (поворот первой прямой)
    for (int i_angle_1 = 0; i_angle_1 < angles.size(); i_angle_1++) {
        // Цикл для угла (поворот второй прямой)
        for (int i_angle_2 = 0; i_angle_2 < angles.size(); i_angle_2++) {
            // Поворот первой прямой
            double sourceX1 = seg1_length;
            double sourceY1 = 0;
            double rotatedX1 = sourceX1 * cos(angles[i_angle_1]) - sourceY1 * sin(angles[i_angle_1]);
            double rotatedY1 = sourceX1 * sin(angles[i_angle_1]) + sourceY1 * cos(angles[i_angle_1]);

            // Поворот второй прямой
            double sourceX2 = seg2_length;
            double sourceY2 = 0;
            double rotatedX2 = sourceX2 * cos(angles[i_angle_2]) - sourceY2 * sin(angles[i_angle_2]);
            double rotatedY2 = sourceX2 * sin(angles[i_angle_2]) + sourceY2 * cos(angles[i_angle_2]);

            // Подготовка строки для записи в файл
            QString line_str_1 = QString("[%1, %2, %3, %4, 1]").arg(rotatedX1 + x0).arg(rotatedY1 + y0).arg(x0).arg(y0);
            QString line_str_2 = QString("[%1, %2, %3, %4, 1]").arg(x0).arg(y0).arg(rotatedX2 + x0).arg(rotatedY2 + y0);
            file_str = file_str + line_str_1 + "\n" + line_str_2 + "\n" + N_inter::n_motion_calc::n_load::separator + "\n";
        }
    }
    // Запись в файл
    file.write(file_str.toLocal8Bit());

    // Закрытие файла
    file.close();
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_generate::write_to_file_3(QString filename, double x0, double y0, double seg1_length, double seg2_length, double seg3_length, double angle_div) {
    // Открытие файла
    QFile file;
    file.setFileName(filename);
    file.open(QFile::WriteOnly);

    // Если файл не открыт - кидать исключение
    if (!file.isOpen()) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!file.isOpen()";
        exc.m_decision = "Файл не открыт";
        throw exc;
    }

    // Очистка содержимого
    file.resize(0);

    // Формирование строк

    // Число пи, угловое деление
    double pi = 3.1415926535;
    double step = angle_div;

    // Углы
    QVector<double> angles = {};
    double angle = 0;
    while (angle <= 2 * pi) {
        angles.push_back(angle);
        angle = angle + 2 * pi / step;
    }
    angles.push_back(2 * pi);

    // Строка для записи в файл
    QString file_str = "";

    // Цикл для угла (поворот первой прямой)
    for (int i_angle_1 = 0; i_angle_1 < angles.size(); i_angle_1++) {
        // Первая прямая, поворот
        double sourceX1 = seg1_length;
        double sourceY1 = 0;
        double rotatedX1 = sourceX1 * cos(angles[i_angle_1]) - sourceY1 * sin(angles[i_angle_1]);
        double rotatedY1 = sourceX1 * sin(angles[i_angle_1]) + sourceY1 * cos(angles[i_angle_1]);

        // Цикл для угла (поворот второй прямой)
        for (int i_angle_2 = 0; i_angle_2 < angles.size(); i_angle_2++) {
            // Вторая прямая, поворот
            double sourceX2 = seg2_length;
            double sourceY2 = 0;
            double rotatedX2 = sourceX2 * cos(angles[i_angle_2]) - sourceY2 * sin(angles[i_angle_2]);
            double rotatedY2 = sourceX2 * sin(angles[i_angle_2]) + sourceY2 * cos(angles[i_angle_2]);

            // Цикл для угла (поворот третьей прямой)
            for (int i_angle_3 = 0; i_angle_3 < angles.size(); i_angle_3++) {
                // Третья прямая, поворот
                double sourceX3 = rotatedX2 + seg3_length;
                double sourceY3 = rotatedY2;

                double rotatedX3 = sourceX3 * cos(angles[i_angle_3]) - sourceY3 * sin(angles[i_angle_3]);
                double rotatedY3 = sourceX3 * sin(angles[i_angle_3]) + sourceY3 * cos(angles[i_angle_3]);

                // Подготовка строки для записи в файл
                QString line_str_1 = QString("[%1, %2, %3, %4, 1]").arg(rotatedX1).arg(rotatedY1).arg(x0).arg(y0);
                QString line_str_2 = QString("[%1, %2, %3, %4, 1]").arg(x0).arg(y0).arg(rotatedX2 + x0).arg(rotatedY2 + y0);
                QString line_str_3 = QString("[%1, %2, %3, %4, 1]").arg(rotatedX2).arg(rotatedY2).arg(rotatedX3).arg(rotatedY3);

                file_str = file_str + line_str_1 + "\n" + line_str_2 + "\n" + line_str_3 + "\n" + N_inter::n_motion_calc::n_load::separator + "\n";
            }
        }
    }
    // Запись в файл
    file.write(file_str.toLocal8Bit());

    // Закрытие файла
    file.close();
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_generate::write_to_file_polygon(QString filename, double x0, double y0, double R, double n, double phi) {
    // Открытие файла
    QFile file;
    file.setFileName(filename);
    file.open(QFile::WriteOnly);

    // Если файл не открыт - кидать исключение
    if (!file.isOpen()) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!file.isOpen()";
        exc.m_decision = "Файл не открыт";
        throw exc;
    }

    // Очистка содержимого
    file.resize(0);

    // Формирование строк

    // Число пи
    double pi = 3.1415926535;

    // Вершины правильного многоугольника
    QVector<double> x_arr = {};
    QVector<double> y_arr = {};

    // Формирование вершин правильного многоугольника
    for (int i = 0; i < n; i++) {
        x_arr.push_back(x0 + R * cos(phi + (2 * pi * (i - 1)) / n));
        y_arr.push_back(y0 + R * sin(phi + (2 * pi * (i - 1)) / n));
    }
    x_arr.push_back(x_arr[0]);
    y_arr.push_back(y_arr[0]);

    // Формирование строки для записи в файл
    QString file_str = "";
    for (int i = 0; i < x_arr.size() - 1; i++) {
        QString line_str = QString("[%1, %2, %3, %4, 1]").arg(x_arr[i]).arg(y_arr[i]).arg(x_arr[i + 1]).arg(y_arr[i + 1]);
        file_str = file_str + line_str + "\n";
    }

    // Запись в файл
    file.write(file_str.toLocal8Bit());

    // Закрытие файла
    file.close();
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_generate::write_to_file_ninja(QString filename, double x0, double y0, double inner_radius, double outer_radius, double n) {
    // Открытие файла
    QFile file;
    file.setFileName(filename);
    file.open(QFile::WriteOnly);

    // Если файл не открыт - кидать исключение
    if (!file.isOpen()) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!file.isOpen()";
        exc.m_decision = "Файл не открыт";
        throw exc;
    }

    // Очистка содержимого
    file.resize(0);


    // Формирование строк

    // Число пи
    double pi = 3.1415926535;
    double Phi0 = 0;
    double Phi1 = Phi0 + pi / 6;

    // Вершины правильного многоугольника
    QVector<double> inner_x_arr = {};
    QVector<double> inner_y_arr = {};
    QVector<double> outer_x_arr = {};
    QVector<double> outer_y_arr = {};
    QVector<double> x_arr = {};
    QVector<double> y_arr = {};

    // for (int i = 0; i < 2 * n - 1; i++) {
    for (int i = 0; i < n; i++) {
        outer_x_arr.push_back(x0 + outer_radius * cos(Phi0 + (2 * pi * (i - 1)) / n));
        outer_y_arr.push_back(y0 + outer_radius * sin(Phi0 + (2 * pi * (i - 1)) / n));

        inner_x_arr.push_back(x0 + inner_radius * cos(Phi1 + (2 * pi * (i - 1)) / n));
        inner_y_arr.push_back(y0 + inner_radius * sin(Phi1 + (2 * pi * (i - 1)) / n));
    }

    // for (int i = 0; i < 2 * n - 1; i++) {
    for (int i = 0; i < n; i++) {
        x_arr.push_back(outer_x_arr[i]);
        y_arr.push_back(outer_y_arr[i]);

        x_arr.push_back(inner_x_arr[i]);
        y_arr.push_back(inner_y_arr[i]);
    }
    x_arr.push_back(x_arr[0]);
    y_arr.push_back(y_arr[0]);

    // Формирование строки для записи в файл
    QString file_str = "";

    for (int i = 0; i < x_arr.size() - 1; i++) {
        QString line_str = QString("[%1, %2, %3, %4, 1]").arg(x_arr[i]).arg(y_arr[i]).arg(x_arr[i + 1]).arg(y_arr[i + 1]);
        file_str = file_str + line_str + "\n";
    }

    // Запись в файл
    file.write(file_str.toLocal8Bit());

    // Закрытие файла
    file.close();
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_generate::write_to_file_saw(QString filename, double A, double step, int count) {
    // Открытие файла
    QFile file;
    file.setFileName(filename);
    file.open(QFile::WriteOnly);

    // Если файл не открыт - кидать исключение
    if (!file.isOpen()) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "!file.isOpen()";
        exc.m_decision = "Файл не открыт";
        throw exc;
    }

    // Очистка содержимого
    file.resize(0);


    // Формирование строк

   double new_x = 0;
   double new_y = 0;

   QVector<double> x_arr = {};
   QVector<double> y_arr = {};

   for (int i = 0; i < count * 2; i++) {
       x_arr.push_back(new_x);
       y_arr.push_back(new_y);

       new_x = new_x + step;
       new_y = pow(-1, i) * A;
   }

    // Формирование строки для записи в файл
    QString file_str = "";

    for (int i = 0; i < x_arr.size() - 1; i++) {
        QString line_str = QString("[%1, %2, %3, %4, 1]").arg(x_arr[i]).arg(y_arr[i]).arg(x_arr[i + 1]).arg(y_arr[i + 1]);
        file_str = file_str + line_str + "\n";
    }

    // Запись в файл
    file.write(file_str.toLocal8Bit());

    // Закрытие файла
    file.close();
}
// --------------------------------------------------------
