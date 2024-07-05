#include "C_arc_circle.h"
#include "N_inter/S_exception.h"
// --------------------------------------------------------

using N_inter::n_global_types::C_point;
// --------------------------------------------------------

// TODO: добавить проверку на случай, если дуги не правые

// N_inter::n_global_types::C_point N_inter::n_motion_calc::n_rounding_corners::n_types::C_arc_circle::low_point() {
//     // Примечание: дуга левая
//
//     C_point point_1 = arc.front().m_first_point;
//     C_point point_2 = arc.back().m_second_point;
//
//     if (point_1 == point_2) {
//         S_exception exc;
//         exc.m_calling_object = Q_FUNC_INFO;
//         exc.m_condition = "point_1 == point_2";
//         exc.m_decision = "Крайние точки окружности совпадают";
//         throw exc;
//     }
//
//     return point_1;
// }
// --------------------------------------------------------

// N_inter::n_global_types::C_point N_inter::n_motion_calc::n_rounding_corners::n_types::C_arc_circle::high_point() {
//     // Примечание: дуга левая
//
//     C_point point_1 = arc.front().m_first_point;
//     C_point point_2 = arc.back().m_second_point;
//
//     if (point_1 == point_2) {
//         S_exception exc;
//         exc.m_calling_object = Q_FUNC_INFO;
//         exc.m_condition = "point_1 == point_2";
//         exc.m_decision = "Крайние точки окружности совпадают";
//         throw exc;
//     }
//
//     return point_2;
// }
// --------------------------------------------------------

int N_inter::n_motion_calc::n_rounding_corners::n_types::C_arc_circle::size() {
    return arc.size();
}
// --------------------------------------------------------

N_inter::n_global_types::C_m_line &N_inter::n_motion_calc::n_rounding_corners::n_types::C_arc_circle::operator[](int index) {
    if (index < 0) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "index < 0";
        exc.m_decision = "Отрицательный индекс";
        throw exc;
    }

    if (index > arc.size()) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "index > arc.size()";
        exc.m_decision = "Выход за пределы дуги";
        throw exc;
    }

    return arc[index];
}
// --------------------------------------------------------
