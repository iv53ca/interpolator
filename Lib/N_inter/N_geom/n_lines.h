#pragma once
// --------------------------------------------------------

#include <QVector>
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_vector.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
#include "N_inter/N_global_types/C_vector.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_geom {
        namespace n_lines {
            // TODO переименовать
            // Проверка линии на допустимую для профилирования (вписывание окружности в угол)
            bool is_line_length_more_than_max_line_error(N_inter::n_global_types::C_m_line& line);

            double get_line_y_by_x(N_inter::n_global_types::C_m_line& line, double x); // Получение значения y по координате x
            double get_line_x_by_y(N_inter::n_global_types::C_m_line& line, double y); // Получение значения x по координате y

            // Удаление вырожденных линий
            void remove_empty_lines(QVector<N_inter::n_global_types::C_m_line>& lines);

            // Округение точек до нуля (если в окрестности вычислительной ошибки)
            void to_necessary_zero(QVector<N_inter::n_global_types::C_m_line>& lines);

            // Получение уравнения прямой по начальной точке и коэффициенту
            N_inter::n_global_types::C_m_line get_line(N_inter::n_global_types::C_point beginPoint, double k);

            // Проверка прямой на вырожденную (точка)
            bool is_empty_line(N_inter::n_global_types::C_m_line& line);

            // Удаление избыточных точек разбиения для прямых
            void remove_repeats(QVector<N_inter::n_global_types::C_m_line>& lines);

            // Вычисление и установка параметров A, B, C, Begin, End для прямой
            void set_line_params(N_inter::n_global_types::C_m_line& line);

            // Смещение сегмента на dx единиц вдоль оси абсцисс вправо
            void segment_offset_by_X(QVector<N_inter::n_global_types::C_m_line>& segment, double dx);

            // Проверка прямых
            bool is_ver_line(N_inter::n_global_types::C_m_line& line);     // На вертикальную
            bool is_hor_line(N_inter::n_global_types::C_m_line& line);     // На горизонтальную
            bool is_oblique_line(N_inter::n_global_types::C_m_line& line); // На наклонную

            // Проверка прямой на содержание
            bool is_line_contain_x(N_inter::n_global_types::C_m_line& line, double x); // Абсциссы X
            bool is_line_contain_y(N_inter::n_global_types::C_m_line& line, double y); // Ординаты Y

            N_inter::n_global_types::C_m_line get_hor_segment_line(N_inter::n_motion_calc::n_types::C_motion_section& segment); // Получение прямоугольной составляющей сегмента

            // TODO Удалить
            // Перенос линии вдоль оси ординат
            void transfer_line_along_y_axis(N_inter::n_global_types::C_m_line& a_line, double& a_dy, double& a_begin_x, double& a_end_x);

            // TODO Удалить
            // Перенос линии вдоль оси абсцисс
            void transfer_line_along_x_axis(N_inter::n_global_types::C_m_line& a_line, double& a_dx, double& a_begin_y, double& a_end_y);

            // Точка пересечения двух прямых
            N_inter::n_global_types::C_point get_intersection_point(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

            // Получение направляющих векторой для прямых line1 и line2
            void set_direction_vectors(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2, n_global_types::C_vector& vec1, n_global_types::C_vector& vec2);

            // Длина прямой (модуль)
            double get_abs_line(N_inter::n_global_types::C_m_line& line);

            // Определение угла в радианах между прямыми line1 и line2
            double get_rad_angle(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

            // Перевод линии в массив координат
            QVector<double> to_double_vector(N_inter::n_global_types::C_m_line& line);

            // Перевод точек в прямую
            // TODO перенести в n_convert
            N_inter::n_global_types::C_m_line to_line(N_inter::n_global_types::C_point& point1, N_inter::n_global_types::C_point& point2);

            // Получить линию из координат
            N_inter::n_global_types::C_m_line get_line_from_coords(double x1, double y1, double x2, double y2);

            // Перевод массива точек в отрезки и их запись в вектор прямых
            void append_to_line_lines_from_points(QVector<N_inter::n_global_types::C_m_line>& lines, QVector<N_inter::n_global_types::C_point>& points);

            // Проверка прямых на сонаправленные
            bool is_co_directional_lines(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

            // Хотя бы одна из двух прямых горизонтальная или вертикальная
            bool is_ver_or_hor_lines(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

            // Провека отрезка на содержание X
            bool is_segment_contain_x(N_inter::n_global_types::C_m_line& line, double x);

            // TODO: интегралы перенести в отдельное пространство имён
            // Получение значения определённого интеграла для отезка пямой
            double get_line_definite_integral(N_inter::n_global_types::C_m_line& line);
            double get_lines_definite_integral(QVector<N_inter::n_global_types::C_m_line> &lines);
            double get_lines_definite_integral(N_inter::n_motion_calc::n_types::C_motion_section &section);
            double get_line_definite_integral(N_inter::n_global_types::C_m_line& line, double begin_x, double end_x);

            // Перенос линии на заданное смещение
            void move(N_inter::n_global_types::C_m_line& line, N_inter::n_global_types::C_point& new_position);

            // TODO В отдельное пространство имён
            // Отображение отрезка вдоль прямой x = const
            void mirroring_along_axis_y(N_inter::n_global_types::C_m_line& line);
            void mirroring_along_axis_y(QVector<N_inter::n_global_types::C_m_line>& lines);

            // TODO: в отдельное пространство имён offset
            // Смещение отрезка вдоль оси X
            void section_offset_x(N_inter::n_global_types::C_m_line& line, double new_x_position);
        }
    }
}
// --------------------------------------------------------
