#include "n_motion_sections.h"
#include <QDebug>
#include "N_inter/N_motion_calc/n_point_elevation.h"
#include "N_inter/N_algebra/n_math.h"
#include "N_inter/N_algebra/n_limits.h"
#include "N_inter/N_motion_calc/N_types/C_motion_section.h"
#include "N_inter/N_geom/n_lines.h"
#include "N_inter/S_exception.h"
#include "N_inter/N_global_types/C_point.h"
// --------------------------------------------------------

using N_inter::n_global_types::COORD;
using N_inter::n_global_types::C_point;
using N_inter::n_motion_calc::n_types::C_motion_section;
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_sections::n_aux::segmentBorders(N_inter::n_motion_calc::n_types::C_motion_section &segment, n_global_types::C_m_line &leftBorder, n_global_types::C_m_line &rightBorder, double h, double leftA, double rightA) {
    N_inter::n_global_types::C_point leftPoint  = segment.get_begin_point(), rightPoint = segment.get_end_point(); // Граничные точки: левая и правая

    // Установка параметров для прямых
    n_geom::n_lines::set_line_params(segment.get_begin_line());
    n_geom::n_lines::set_line_params(segment.get_end_line());

    // Получение наклонных потенциальных границ
    leftBorder  = n_geom::n_lines::get_line(leftPoint, -rightA); // Левая
    rightBorder = n_geom::n_lines::get_line(rightPoint, leftA); // Прямая

    // Точка пересечения прямых
    N_inter::n_global_types::C_point interPoint = n_geom::n_lines::get_intersection_point(leftBorder, rightBorder);

    // Если ордината меньше нуля, то укоротить прямые
    if (N_inter::n_algebra::n_math::is_more_than(0, interPoint[n_global_types::Y])) {
        double leftX  = n_geom::n_lines::get_line_x_by_y(leftBorder,  0);
        double rightX = n_geom::n_lines::get_line_x_by_y(rightBorder, 0);

        leftBorder.m_first_point[COORD::X] = leftPoint[COORD::X];
        leftBorder.m_first_point[COORD::Y] = leftPoint[COORD::Y];

        leftBorder.m_second_point[COORD::X]  = leftX;
        leftBorder.m_second_point[COORD::Y]  = 0;

        rightBorder.m_first_point[COORD::X] = rightX;
        rightBorder.m_first_point[COORD::Y] = 0;

        rightBorder.m_second_point[COORD::X] = rightPoint[COORD::X];
        rightBorder.m_second_point[COORD::Y] = rightPoint[COORD::Y];
    }
    else {
        leftBorder.m_first_point[COORD::X]  = leftPoint[COORD::X];
        leftBorder.m_first_point[COORD::Y]  = leftPoint[COORD::Y];

        leftBorder.m_second_point[COORD::X] = interPoint[COORD::X];
        leftBorder.m_second_point[COORD::Y] = interPoint[COORD::Y];

        rightBorder.m_first_point[COORD::X] = interPoint[COORD::X];
        rightBorder.m_first_point[COORD::Y] = interPoint[COORD::Y];

        rightBorder.m_second_point[COORD::X] = rightPoint[COORD::X];
        rightBorder.m_second_point[COORD::Y] = rightPoint[COORD::Y];
    }

    // Уточнение левой границы
    if (!n_geom::n_lines::is_line_contain_y(leftBorder, h)) {
        if (!n_geom::n_lines::is_line_contain_y(segment.get_begin_line(), h)) {
            N_inter::S_exception exc;
            exc.m_calling_object = "void MotionSegment::_segmentBorders(n_motion_calc::n_types::C_motion_section& segment, C_m_line& leftBorder, C_m_line& rightBorder, double h, double leftA, double rightA)";
            exc.m_condition = "!n_geom::n_lines::is_line_contain_y(segment.get_begin_line(), h)";
            exc.m_decision = "Некорректно заданная левая граница leftBorder (не содержит h)";
            throw exc;
        }
        leftBorder = segment.get_begin_line();
    }

    if (N_inter::n_algebra::n_math::is_more_than(0, N_inter::n_algebra::n_limits::min(leftBorder))) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void MotionSegment::_segmentBorders(n_motion_calc::n_types::C_motion_section& segment, C_m_line& leftBorder, C_m_line& rightBorder, double h, double leftA, double rightA)";
        exc.m_condition = "n_algebra::n_math::is_more_than(0, n_algebra::n_limits::min(leftBorder))";
        exc.m_decision = "Одна из ординат для leftBorder отрицательная";
        throw exc;
    }

    // Уточнение правой границы
    if (!n_geom::n_lines::is_line_contain_y(rightBorder, h)) {
        if (!n_geom::n_lines::is_line_contain_y(segment.get_end_line(), h)) {
            N_inter::S_exception exc;
            exc.m_calling_object = "void MotionSegment::_segmentBorders(n_motion_calc::n_types::C_motion_section& segment, C_m_line& leftBorder, C_m_line& rightBorder, double h, double leftA, double rightA)";
            exc.m_condition = "!n_geom::n_lines::is_line_contain_y(segment.get_end_line(), h)";
            exc.m_decision = "Некорректно заданная правая граница rightBorder (не содержит h)";
            throw exc;
        }
        rightBorder = segment.get_end_line();
    }

    if (N_inter::n_algebra::n_math::is_more_than(0, N_inter::n_algebra::n_limits::min(rightBorder))) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void MotionSegment::_segmentBorders(n_motion_calc::n_types::C_motion_section& segment, C_m_line& leftBorder, C_m_line& rightBorder, double h, double leftA, double rightA)";
        exc.m_condition = "n_algebra::n_math::is_more_than(0, n_algebra::n_limits::min(rightBorder))";
        exc.m_decision = "Одна из координат отрицательная";
        throw exc;
    }

    // Коэффициенты A, B и C для прямых
    n_geom::n_lines::set_line_params(leftBorder);
    n_geom::n_lines::set_line_params(rightBorder);
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_section N_inter::n_motion_calc::n_motion_sections::n_aux::augmentedSegmentLines(N_inter::n_motion_calc::n_types::C_motion_section &segment, n_global_types::C_m_line &leftBorder, n_global_types::C_m_line &rightBorder, double h) {
    // Получение абсцисс по границам на высоте h (где должна закончится граничный отрезок под наклоном)
    double leftX  = n_geom::n_lines::get_line_x_by_y(leftBorder, h);  // Левая
    double rightX = n_geom::n_lines::get_line_x_by_y(rightBorder, h); // Правая

    // Выделить три отрезка: начальный, промежуточный и конечный
    N_inter::n_global_types::C_m_line begin, middle, end;

    // Инициализация начального отрезка
    begin.m_first_point[n_global_types::X] = segment.get_begin_point()[n_global_types::X]; begin.m_first_point[n_global_types::Y] = segment.get_begin_point()[n_global_types::Y];
    begin.m_second_point[n_global_types::X] = leftX; begin.m_second_point[n_global_types::Y] = h;

    // Инициализация промежуточного отрезка
    middle.m_first_point[n_global_types::X] = leftX; middle.m_first_point[n_global_types::Y] = h;
    middle.m_second_point[n_global_types::X] = rightX; middle.m_second_point[n_global_types::Y] = h;

    // Инициализация конечного отрезка
    end.m_first_point[n_global_types::X] = rightX; end.m_first_point[n_global_types::Y] = h;
    end.m_second_point[n_global_types::X] = segment.get_end_point()[n_global_types::X]; end.m_second_point[n_global_types::Y] = segment.get_end_point()[n_global_types::Y];

    // Формирование результата
    N_inter::n_motion_calc::n_types::C_motion_section result;

    // Если левая абсцисса не равна левой границе, то записать в ответ начальный отрезок
    if(!N_inter::n_algebra::n_math::is_equal(leftX, segment.get_begin_point()[n_global_types::X])) {
        result.push_back(begin);
    }

    // Если промежуточный отрезок имеет отличную от нуля длину, то записать его в ответ
    if (!N_inter::n_algebra::n_math::is_equal(middle.m_first_point[n_global_types::X], middle.m_second_point[n_global_types::X])) {
        result.push_back(middle);
    }

    // Если правая абсцисса не равна правой границе, то записать в ответ начальный отрезок
    if (!N_inter::n_algebra::n_math::is_equal(rightX, segment.get_end_point()[n_global_types::X])) {
        result.push_back(end);
    }

    // Если сегмент состоит минимум из двух отрезков, причём два последние являются горизонтальными прямыми, то это ошибка
    if ((result.get_size() >= 2) && (n_geom::n_lines::is_hor_line(result[result.get_size() - 1])) && (n_geom::n_lines::is_hor_line(result[result.get_size() - 2]))) {
        N_inter::S_exception exc;
        exc.m_calling_object = "n_motion_calc::n_types::C_motion_section MotionSegment::_augmentedSegmentLines(n_motion_calc::n_types::C_motion_section& segment, C_m_line& leftBorder, C_m_line& rightBorder, double h)";
        exc.m_condition = "(result.get_size() >= 2) && (n_geom::n_lines::is_hor_line(result[result.get_size() - 1])) && (n_geom::n_lines::is_hor_line(result[result.get_size() - 2]))";
        exc.m_decision = "Некорректный сегмент: два последних отрезка горизонтальные [TruncatedSegment]";
        throw exc;
    }

    return result;
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_motion_sections::K_SIGN N_inter::n_motion_calc::n_motion_sections::sign(N_inter::n_motion_calc::n_types::C_motion_section &segment) {
    if (segment.get_size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "MotionSegment::K_SIGN MotionSegment::sign(n_motion_calc::n_types::C_motion_section& segment)";
        exc.m_condition = "segment.get_size() == 0";
        exc.m_decision = "Сегмент не содержит отрезков";
        throw exc;
    }
    // Положительное направление
    if ((N_inter::n_algebra::n_math::is_more_than(N_inter::n_algebra::n_limits::max_y(segment), 0)) && (N_inter::n_algebra::n_math::is_more_or_equal(abs(N_inter::n_algebra::n_limits::min_y(segment)), 0))) {
        return K_SIGN::POSITIVE;
    }
    // Отрицательное направление
    else if (N_inter::n_algebra::n_math::is_more_than(0, N_inter::n_algebra::n_limits::min_y(segment))) {
        return K_SIGN::NEGATIVE;
    }
    // Движение отсутствует (проверка на равенство нулю избыточна)
    else if (N_inter::n_algebra::n_math::is_equal(N_inter::n_algebra::n_limits::max_y(segment), N_inter::n_algebra::n_limits::min_y(segment)) && N_inter::n_algebra::n_math::is_equal(N_inter::n_algebra::n_limits::max_y(segment), 0)) {
        return K_SIGN::ZERO;
    }
    else {
        double max_y = N_inter::n_algebra::n_limits::max_y(segment); // debug
        double min_y = N_inter::n_algebra::n_limits::min_y(segment);
        N_inter::S_exception exc;
        exc.m_calling_object = "MotionSegment::K_SIGN MotionSegment::sign(n_motion_calc::n_types::C_motion_section& segment)";
        exc.m_condition = "else";
        exc.m_decision = "Двусторонее движение вдоль одного сегмента";
        throw exc;
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_sections::unidirectionalSegments(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, int &begin, int &end) {
    if (segments.size() == 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void MotionSegment::unidirectionalSegments(QVector<n_motion_calc::n_types::C_motion_section>& segments, int& begin, int& end)";
        exc.m_condition = "segments.size() == 0";
        exc.m_decision = "Сегмент не содержит отрезков";
        throw exc;
    }

    if (begin >= segments.size()) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void MotionSegment::unidirectionalSegments(QVector<n_motion_calc::n_types::C_motion_section>& segments, int& begin, int& end)";
        exc.m_condition = "begin >= segments.size()";
        exc.m_decision = "Выход за пределы массива";
        throw exc;
    }

    if (begin < 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void MotionSegment::unidirectionalSegments(QVector<n_motion_calc::n_types::C_motion_section>& segments, int& begin, int& end)";
        exc.m_condition = "begin < 0";
        exc.m_decision = "Начальный параметр меньше нуля";
        throw exc;
    }

    K_SIGN seg_sign = sign(segments[begin]);
    // bool sign = n_algebra::n_math::is_more_than(segmentHeight(segments[begin]), 0);
    for (int i = begin; i < segments.size(); i++) {
        if (seg_sign == sign(segments[i])) {
        // if (sign == n_algebra::n_math::is_more_than(segmentHeight(segments[i]), 0)) {
            end = i;
        }
        else {
            break;
        }
    }

    if (end < begin) {
        N_inter::S_exception exc;
        exc.m_calling_object = "void MotionSegment::unidirectionalSegments(QVector<n_motion_calc::n_types::C_motion_section>& segments, int& begin, int& end)";
        exc.m_condition = "end < begin";
        exc.m_decision = "Конечный параметр не больше начального параметра";
        throw exc;
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_sections::segmentMirroredByY(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &segments, int begin, int end) {
    for (int i = begin; i <= end; i++) {
        segmentMirroredByY(segments[i]);
    }
}
// --------------------------------------------------------

// TODO: сделать вычитание -2 Y
void N_inter::n_motion_calc::n_motion_sections::segmentMirroredByY(N_inter::n_motion_calc::n_types::C_motion_section &a_segments_kms) {
    for (int i = 0; i < a_segments_kms.get_size(); i++) {
        a_segments_kms[i].m_first_point[n_global_types::Y] *= -1;
        a_segments_kms[i].m_second_point[n_global_types::Y] *= -1;
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_sections::section_morrored_by_x(n_types::C_motion_section &section) {
    segmentMirroredByY(section);
}
// --------------------------------------------------------

QVector<bool> N_inter::n_motion_calc::n_motion_sections::positive_sections_morrored_by_x(QVector<N_inter::n_motion_calc::n_types::C_motion_section> &sections) {
    // Если движения вдоль секции нет, то изменений не будет
    QVector<bool> result = {};
    for (int i = 0; i < sections.size(); i++) {
        // Если движение в обратную сторону, то отобразить и добавить true
        if (N_inter::n_algebra::n_math::is_more_than(0, sections[i].get_begin_line().m_second_point[COORD::Y])) {
            section_morrored_by_x(sections[i]);
            result.push_back(true);
        }
        // Если движение в прямую сторону, то не отображать и добавить false
        else {
            result.push_back(false);
        }
    }
    return result;
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion_section N_inter::n_motion_calc::n_motion_sections::truncatedSegment(N_inter::n_motion_calc::n_types::C_motion_section &segment, double h, double leftA, double rightA) {
    // Отзеркаленные отрезки-границы для сегмента
    N_inter::n_global_types::C_m_line leftBorder, rightBorder;
    n_aux::segmentBorders(segment, leftBorder, rightBorder, h, leftA, rightA);

    // Части дополненного сегмента
    N_inter::n_motion_calc::n_types::C_motion_section result = n_aux::augmentedSegmentLines(segment, leftBorder, rightBorder, h);
    return result;
}
// --------------------------------------------------------

double N_inter::n_motion_calc::n_motion_sections::get_max_width(QVector<n_types::C_motion_section> &sections) {
    if (sections.size() == 0) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "QVector<n_types::C_motion_section> &sections";
        exc.m_decision = "Вектор секций пустой";
        throw exc;
    }

    double result = 0;
    for (int i = 0; i < sections.size(); i++) {
        double curr_width = sections[i].get_lines().back().m_second_point[COORD::X] - sections[i].get_lines().front().m_first_point[COORD::X];
        if (N_inter::n_algebra::n_math::is_more_than(curr_width, result)) {
            result = curr_width;
        }
    }
    return result;
}
// --------------------------------------------------------

double N_inter::n_motion_calc::n_motion_sections::segmentHeight(N_inter::n_motion_calc::n_types::C_motion_section &segment) {
    double h = 0;

    for (int i = 0; i < segment.get_size(); i++) {
        if (h < N_inter::n_algebra::n_limits::max_y(segment.get_lines())) {
            h = N_inter::n_algebra::n_limits::max_y(segment.get_lines());
        }
    }

    return h;
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_motion_sections::is_segment_contain_hor_lines(n_types::C_motion_section &segment) {
    for (int i = 0; i < segment.get_size(); i++) {
        if (N_inter::n_geom::n_lines::is_hor_line(segment[i])) {
            return true;
        }
    }
    return false;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_sections::section_offset_x(n_types::C_motion_section &section, double new_x_position) {
    // Смещение не требуется
    if (N_inter::n_algebra::n_math::is_equal(section.get_begin_point()[COORD::X], new_x_position)) {
        return;
    }

    // Перебор отрезков, смещение каждого
    double offset = new_x_position - section.get_begin_point()[COORD::X];
    for (int i = 0; i < section.get_size(); i++) {
        double current_x_position = section[i].m_first_point[COORD::X] + offset;
        N_inter::n_geom::n_lines::section_offset_x(section[i], current_x_position);
    }
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_sections::section_offset_x(QVector<n_types::C_motion_section> &sections, double new_x_position) {
    // Перебор секций, смещение каждой
    for (int i = 0; i < sections.size(); i++) {
        section_offset_x(sections[i], new_x_position);
    }
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_motion_sections::is_section_correct(QVector<n_global_types::C_m_line> &lines) {
    C_motion_section section;
    section.set_lines(lines);
    return is_section_correct(section);
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_motion_sections::is_section_correct(n_types::C_motion_section &section) {
    // Перебор отрезков, сравнение абсцисс
    for (int i = 0; i < section.get_size(); i++) {
        C_point begin_point = section[i].m_first_point;
        C_point end_point   = section[i].m_second_point;

        if (N_inter::n_algebra::n_math::is_more_than(begin_point[COORD::X], end_point[COORD::X])) {
            return false;
        }
    }
    return true;
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_motion_sections::is_section_correct(QVector<n_types::C_motion_section> &sections) {
    for (int i = 0; i < sections.size(); i++) {
        if (!is_section_correct(sections[i])) {
            return false;
        }
    }
    return true;
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_sections::throw_is_section_correct(QVector<n_global_types::C_m_line> &lines) {
    C_motion_section section;
    section.set_lines(lines);
    throw_is_section_correct(section);
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_sections::throw_is_section_correct(n_types::C_motion_section &section) {
    QVector<n_types::C_motion_section> sections = { section };
    throw_is_section_correct(sections);
}
// --------------------------------------------------------

void N_inter::n_motion_calc::n_motion_sections::throw_is_section_correct(QVector<n_types::C_motion_section> &sections) {
    if (!N_inter::n_motion_calc::n_motion_sections::is_section_correct(sections)) {
        S_exception exc;
        exc.m_calling_object = Q_FUNC_INFO;
        exc.m_condition = "N_inter::n_motion_calc::n_motion_sections::is_section_correct(sections)";
        exc.m_decision = "Секции некорректные";
        throw exc;
    }
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_motion_sections::is_zero_displacement_section(n_types::C_motion_section &section) {
    // Единственный отрезок
    if (section.get_size() == 1) {
        // Начальная и конечная абсциссы 0
        if (N_inter::n_algebra::n_math::is_equal(section.get_begin_point()[COORD::Y], 0)) {
            if (N_inter::n_algebra::n_math::is_equal(section.get_end_point()[COORD::Y], 0)) {
                return true;
            }
        }
    }

    return false;
}
// --------------------------------------------------------

bool N_inter::n_motion_calc::n_motion_sections::is_zero_displacement_section(QVector<n_global_types::C_m_line> &lines) {
    C_motion_section section;
    section.set_lines(lines);
    return is_zero_displacement_section(section);
}
// --------------------------------------------------------
