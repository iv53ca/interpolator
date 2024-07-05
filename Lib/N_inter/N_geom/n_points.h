#pragma once
// --------------------------------------------------------

#include <QVector>

#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_global_types/C_segment/C_m_line.h"
// --------------------------------------------------------

namespace N_inter {
    namespace n_geom {
        namespace n_points {
            // Определение общей граничной точки для прямых со статусом операции
            N_inter::n_global_types::C_point get_lines_boundary_common_point(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2, bool& stat);
            // Определение общей граничной точки для прямых без статуса операции
            N_inter::n_global_types::C_point get_lines_boundary_common_point(N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

            // TODO Создать отдельное пространство имён для округления (значений, прямых, точек)

            // Округение точек до нуля (если в окрестности вычислительной ошибки)
            void to_necessary_zero(QVector<N_inter::n_global_types::C_point>& points);

            // Проверка точек на равенство
            bool is_equal(N_inter::n_global_types::C_point& point1, N_inter::n_global_types::C_point& point2);

            // Проверка на принадлежности точки полуплоскости, образованной углом line1-line2
            bool is_in_angle(N_inter::n_global_types::C_point& point, N_inter::n_global_types::C_m_line& line1, N_inter::n_global_types::C_m_line& line2);

            // Проверка на принадлежность точки отрезку
            bool is_in_line(N_inter::n_global_types::C_m_line& line, N_inter::n_global_types::C_point& point);

            // Проверка точки на принадлежность границам
            bool is_in_boundary_line(N_inter::n_global_types::C_point& point, N_inter::n_global_types::C_m_line& line);

            // Проекция точки на прямую
            N_inter::n_global_types::C_point get_project_onto_line(N_inter::n_global_types::C_m_line& line, N_inter::n_global_types::C_point& point);

            // Проверка точек на пустые абсциссы
            bool is_empty_points_x(QVector<N_inter::n_global_types::C_point>& points);

            // Проверка точек на пустые ординаты
            bool is_empty_points_y(QVector<N_inter::n_global_types::C_point>& points);

            // TODO удалить
            // Конвертирование вектора точек в строку
            QString to_string(QVector<N_inter::n_global_types::C_point>& points);
            QString to_string_x(QVector<N_inter::n_global_types::C_point>& points);
            QString to_string_y(QVector<N_inter::n_global_types::C_point>& points);

            // Перенос точки на заданное смещение
            void move(N_inter::n_global_types::C_point& point, N_inter::n_global_types::C_point& new_position);

            // Отображение точки вдоль прямой x = cosnt
            void mirroring_along_axis_y(N_inter::n_global_types::C_point& point);

            // TODO: переименовать
            // TODO: написать версии для отрезков
            // TODO: в отдельное пространство имён
            // Временная корректировка профиля скорости (трапеция или треугольник)
            QVector<N_inter::n_global_types::C_point> correct_area_by_time(QVector<N_inter::n_global_types::C_point>& points, double newTime, int axis); // Согласование движений для режима без профилирования
            QVector<N_inter::n_global_types::C_point> proxy_correct_area_by_time(QVector<N_inter::n_global_types::C_point>& points, double newTime, int axis);
        }
    }
}
// --------------------------------------------------------
