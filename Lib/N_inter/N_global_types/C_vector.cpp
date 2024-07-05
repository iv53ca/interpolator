#include "C_vector.h"
//

N_inter::n_global_types::C_vector::C_vector() {}
// --------------------------------------------------------

N_inter::n_global_types::C_vector::~C_vector() {}
// --------------------------------------------------------

double &N_inter::n_global_types::C_vector::operator[](int a_index) {
    return m_coord[a_index];
}
// --------------------------------------------------------
