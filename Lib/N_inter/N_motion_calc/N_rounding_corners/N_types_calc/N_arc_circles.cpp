#include "N_arc_circles.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_global_types/C_point.h"
#include "N_inter/N_geom/n_points.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_geom/n_points.h"
#include "N_inter/N_geom/n_lines.h"
// --------------------------------------------------------

// TODO Переименовать файл

using N_inter::n_global_types::C_point;
using N_inter::S_exception;
using N_inter::n_global_types::COORD;
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_arc_circles::move(n_types::C_arc_circle &arr_circle, n_global_types::C_point new_angle_position) {
    // Перебор отрезков дуги
    C_point offset = new_angle_position - arr_circle.angle_position;
    for (int i = 0; i < arr_circle.arc.size(); i++) {
        // Перенос отрезка
        arr_circle[i].m_first_point = arr_circle[i].m_first_point + offset;
        arr_circle[i].m_second_point = arr_circle[i].m_second_point + offset;
    }

    // Перенос угловой точки
    N_inter::n_geom::n_points::move(arr_circle.angle_position, new_angle_position);
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_rounding_corners::n_types_calc::n_arc_circles::mirroring_along_axis_y(n_types::C_arc_circle &arr_circle) {
    if (arr_circle.arc.size() == 0) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "arr_circle.arc.size() == 0";
        exc.m_decision = "Дуга пустая";
        throw exc;
    }

    // Примечание: дуга левая
    double x = arr_circle[0].m_first_point[COORD::X];

    // Отображение угловой точки
    N_inter::n_geom::n_points::mirroring_along_axis_y(arr_circle.angle_position);

    // Отображение отрезков
    for (int i = 0; i < arr_circle.size(); i++) {
        N_inter::n_geom::n_lines::mirroring_along_axis_y(arr_circle[i]);
    }
}
// --------------------------------------------------------
