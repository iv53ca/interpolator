#pragma once
// --------------------------------------------------------

#include <QString>
// --------------------------------------------------------

// TODO: переименовать, дать нормальные имена
namespace N_inter {
    namespace n_motion_calc {
        namespace n_generate {
            // Генерирование отрезков (2) и запись их в файл
            void write_to_file_2(QString filename, double x0, double y0, double seg1_length, double seg2_length, double angle_div);

            // Генерирование отрезков (3) и запись их в файл
            void write_to_file_3(QString filename, double x0, double y0, double seg1_length, double seg2_length, double seg3_length, double angle_div);

            // Генерирование отрезков (правильный многоугольник) и запись их в файл
            void write_to_file_polygon(QString filename, double x0, double y0, double R, double n, double phi);

            // Генерирование отрезков (сюрикен) и запись их в файл
            void write_to_file_ninja(QString filename, double x0, double y0, double inner_radius, double outer_radius, double n);

            // Генерирование отрезков (пилообразный сигнал) и запись их в файл
            void write_to_file_saw(QString filename, double A, double step, int count);
        }
    }
}
// --------------------------------------------------------
