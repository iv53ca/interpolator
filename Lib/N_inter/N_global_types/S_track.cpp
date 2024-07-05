#include "S_track.h"
#include "N_inter/S_exception.h"
// --------------------------------------------------------

N_inter::n_global_types::C_point &N_inter::n_global_types::S_track::operator[](int index) {
    if (index < 0) {
        N_inter::S_exception exc;
        exc.m_calling_object = "S_track &S_track::operator[](int index)";
        exc.m_condition = "index < 0";
        exc.m_decision = "Отрицательный индекс";
        throw exc;
    }
    else if (index >= track.size()) {
        N_inter::S_exception exc;
        exc.m_calling_object = "S_track &S_track::operator[](int index)";
        exc.m_condition = "index >= track.size()";
        exc.m_decision = "Индекс превышает размер массива";
        throw exc;
    }
    return track[index];
}
// --------------------------------------------------------
