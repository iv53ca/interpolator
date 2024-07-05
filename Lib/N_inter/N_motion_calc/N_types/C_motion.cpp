#include "C_motion.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion::C_motion() {
    motion.clear();
    for (int current_axis = 0; current_axis < N_inter::n_data::n_motion_vars::n_calc_vars::axis_count; current_axis++) {
        motion.push_back({});
    }
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion::~C_motion() {
    motion.clear();
}
// --------------------------------------------------------

N_inter::n_motion_calc::n_types::C_motion &N_inter::n_motion_calc::n_types::C_motion::operator=(const C_motion &new_motion) {
    for (int i = 0; i < n_data::n_motion_vars::n_calc_vars::axis_count; i++) {
        motion[i] = new_motion.motion[i];
    }
    return *this;
}
// --------------------------------------------------------

QVector<N_inter::n_motion_calc::n_types::C_motion_section> &N_inter::n_motion_calc::n_types::C_motion::operator[](int axis_num) {
    if (axis_num < 0) {
        // TODO make exception
    }
    else if (axis_num >= n_data::n_motion_vars::n_calc_vars::axis_count) {
        // TODO make exception
    }

    return motion[axis_num];
}
// --------------------------------------------------------
