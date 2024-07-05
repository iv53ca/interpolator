#include "n_vectors.h"
#include <cmath>
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/N_global_types/S_bounds.h"
#include "N_inter/N_geom/n_bounds.h"
#include "N_inter/N_geom/n_points.h"
// --------------------------------------------------------

N_inter::n_global_types::C_m_line N_inter::n_geom::n_vectors::get_angle_bisector(n_global_types::C_m_line &line1, n_global_types::C_m_line &line2) {
    N_inter::n_global_types::S_bounds bound = n_geom::n_bounds::find(line1, line2);
    double x1 = bound.m_min_coords[n_global_types::X], x2 = bound.m_max_coords[n_global_types::X];

    double A1 = line1.A, B1 = line1.B, C1 = line1.C; // Коэффициенты A, B и C содержащей отрезок line1 прямой
    double A2 = line2.A, B2 = line2.B, C2 = line2.C; // Коэффициенты A, B и C содержащей отрезок line2 прямой

    // Вектор бисектрисы первого направления
    N_inter::n_global_types::C_m_line Bisector1;
    Bisector1.m_first_point[n_global_types::X] = bound.m_min_coords[n_global_types::X];
    Bisector1.m_second_point[n_global_types::X]   = bound.m_max_coords[n_global_types::X];
    Bisector1.m_first_point[n_global_types::Y] = -(sqrt(A1*A1 + B1*B1)*(C2 + A2*x1) + sqrt(A2*A2 + B2*B2)*(C1 + A1*x1))/(B2*sqrt(A1*A1 + B1*B1) + B1*sqrt(A2*A2 + B2*B2));
    Bisector1.m_second_point[n_global_types::Y]   = -(sqrt(A1*A1 + B1*B1)*(C2 + A2*x2) + sqrt(A2*A2 + B2*B2)*(C1 + A1*x2))/(B2*sqrt(A1*A1 + B1*B1) + B1*sqrt(A2*A2 + B2*B2));

    // Вектор бисектрисы второго направления
    N_inter::n_global_types::C_m_line Bisector2;
    Bisector2.m_first_point[n_global_types::X] = bound.m_min_coords[n_global_types::X];
    Bisector2.m_second_point[n_global_types::X]   = bound.m_max_coords[n_global_types::X];
    Bisector2.m_first_point[n_global_types::Y] = -(sqrt(A1*A1 + B1*B1)*(C2 + A2*x1) - sqrt(A2*A2 + B2*B2)*(C1 + A1*x1))/(B2*sqrt(A1*A1 + B1*B1) - B1*sqrt(A2*A2 + B2*B2));
    Bisector2.m_second_point[n_global_types::Y]   = -(sqrt(A1*A1 + B1*B1)*(C2 + A2*x2) - sqrt(A2*A2 + B2*B2)*(C1 + A1*x2))/(B2*sqrt(A1*A1 + B1*B1) - B1*sqrt(A2*A2 + B2*B2));

    N_inter::n_global_types::C_point E = n_geom::n_points::get_lines_boundary_common_point(line1, line2);

    // Корректировка точек вектора первой (first point совпадает с точкой пересечения прямых)
    // N_inter::n_global_types::C_point point;
    // point[n_global_types::X] = Bisector1.m_second_point[n_global_types::X];
    // point[n_global_types::Y] = Bisector1.m_second_point[n_global_types::Y];
    // if (n_geom::n_points::is_equal(E, point)) {
    //     N_inter::n_global_types::C_point temp;
    //     temp[n_global_types::X] = Bisector1.m_first_point[n_global_types::X];
    //     temp[n_global_types::Y] = Bisector1.m_first_point[n_global_types::Y];
    //     Bisector1.m_first_point[n_global_types::X] = Bisector1.m_second_point[n_global_types::X];
    //     Bisector1.m_first_point[n_global_types::Y] = Bisector1.m_second_point[n_global_types::Y];
    //     Bisector1.m_second_point[n_global_types::X] = temp[n_global_types::X];
    //     Bisector1.m_second_point[n_global_types::Y] = temp[n_global_types::Y];
    // }

    // // Корректировка точек вектора второй биссектрисы (first point совпадает с точкой пересечения прямых)
    // point[n_global_types::X] = Bisector2.m_second_point[n_global_types::X];
    // point[n_global_types::Y] = Bisector2.m_second_point[n_global_types::Y];
    // if (n_geom::n_points::is_equal(E, point)) {
    //     N_inter::n_global_types::C_point temp;
    //     temp[n_global_types::X] = Bisector2.m_first_point[n_global_types::X];
    //     temp[n_global_types::Y] = Bisector2.m_first_point[n_global_types::Y];
    //     Bisector2.m_first_point[n_global_types::X] = Bisector2.m_second_point[n_global_types::X];
    //     Bisector2.m_first_point[n_global_types::Y] = Bisector2.m_second_point[n_global_types::Y];
    //     Bisector2.m_second_point[n_global_types::X] = temp[n_global_types::X];
    //     Bisector2.m_second_point[n_global_types::Y] = temp[n_global_types::Y];
    // }

    // Первый направляющий вектор биссектрисы
    N_inter::n_global_types::C_vector Bisector1v;
    Bisector1v[n_global_types::X] = Bisector1.m_second_point[n_global_types::X] - Bisector1.m_first_point[n_global_types::X];
    Bisector1v[n_global_types::Y] = Bisector1.m_second_point[n_global_types::Y] - Bisector1.m_first_point[n_global_types::Y];

    // Второй направляющий вектор биссектрисы
    N_inter::n_global_types::C_vector Bisector2v;
    Bisector2v[n_global_types::X] = Bisector2.m_second_point[n_global_types::X] - Bisector2.m_first_point[n_global_types::X];
    Bisector2v[n_global_types::Y] = Bisector2.m_second_point[n_global_types::Y] - Bisector2.m_first_point[n_global_types::Y];

    N_inter::n_global_types::C_vector lineVec1, lineVec2; // Направляющие векторы для прямых line1 и line2
    n_geom::n_lines::set_direction_vectors(line1, line2, lineVec1, lineVec2);

    // Уточнение векторов биссектрисы по нахождению в пределах установленного прямыми line1 и line2 угла
    N_inter::n_global_types::C_vector bisVec11, bisVec12, bisVec21, bisVec22;
    bisVec11[n_global_types::X] = Bisector1v[n_global_types::X];
    bisVec11[n_global_types::Y] = Bisector1v[n_global_types::Y];

    bisVec12[n_global_types::X] = - Bisector1v[n_global_types::X];
    bisVec12[n_global_types::Y] = - Bisector1v[n_global_types::Y];

    bisVec21[n_global_types::X] = Bisector2v[n_global_types::X];
    bisVec21[n_global_types::Y] = Bisector2v[n_global_types::Y];

    bisVec22[n_global_types::X] = - Bisector2v[n_global_types::X];
    bisVec22[n_global_types::Y] = - Bisector2v[n_global_types::Y];

    // Определение принадлежащего углу вектора
    N_inter::n_global_types::C_m_line result;
    if (is_in_angle(lineVec1, lineVec2, bisVec11) || is_in_angle(lineVec1, lineVec2, bisVec12)) {
        result.m_first_point[n_global_types::X]  = Bisector1.m_first_point[n_global_types::X];
        result.m_first_point[n_global_types::Y]  = Bisector1.m_first_point[n_global_types::Y];
        result.m_second_point[n_global_types::X] = Bisector1.m_second_point[n_global_types::X];
        result.m_second_point[n_global_types::Y] = Bisector1.m_second_point[n_global_types::Y];
    }
    else {
        result.m_first_point[n_global_types::X]  = Bisector2.m_first_point[n_global_types::X];
        result.m_first_point[n_global_types::Y]  = Bisector2.m_first_point[n_global_types::Y];
        result.m_second_point[n_global_types::X] = Bisector2.m_second_point[n_global_types::X];
        result.m_second_point[n_global_types::Y] = Bisector2.m_second_point[n_global_types::Y];
    }
    n_geom::n_lines::set_line_params(result);
    return result;
}
// --------------------------------------------------------

bool N_inter::n_geom::n_vectors::is_in_angle(n_global_types::C_vector &lineVec1, n_global_types::C_vector &lineVec2, n_global_types::C_vector &vector) {
    double VM11 = get_vec_mul(lineVec1, vector);
    double VM12 = get_vec_mul(lineVec1, lineVec2);

    double VM21 = get_vec_mul(lineVec2, vector);
    double VM22 = get_vec_mul(lineVec2, lineVec1);

    // Проверка на сохранение знака соответствующих векторных произведений
    bool result1 = (VM11 >= 0) && (VM12 >= 0) && (VM21 <= 0) && (VM22 <= 0);
    bool result2 = (VM11 <= 0) && (VM12 <= 0) && (VM21 >= 0) && (VM22 >= 0);

    return result1 || result2;
}
// --------------------------------------------------------

double N_inter::n_geom::n_vectors::get_vec_mul(n_global_types::C_vector &vector1, n_global_types::C_vector &vector2) {
    return vector1[n_global_types::X] * vector2[n_global_types::Y] - vector1[n_global_types::Y] * vector2[n_global_types::X];
}
// --------------------------------------------------------
