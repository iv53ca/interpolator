#include "n_calc_vars.h"
// --------------------------------------------------------

const double N_inter::n_data::n_motion_vars::n_calc_vars::max_position_error                           = 1.0 / 3;
const double N_inter::n_data::n_motion_vars::n_calc_vars::calculation_error                            = 10e-9;
const double N_inter::n_data::n_motion_vars::n_calc_vars::max_errors_segment_length                    = 2;
int          N_inter::n_data::n_motion_vars::n_calc_vars::split_segments_count                         = 2;
const int    N_inter::n_data::n_motion_vars::n_calc_vars::split_segments_count_for_vel                 = 3;
const bool   N_inter::n_data::n_motion_vars::n_calc_vars::enable_round                                 = true;
const int    N_inter::n_data::n_motion_vars::n_calc_vars::axis_count                                   = 2;
const double N_inter::n_data::n_motion_vars::n_calc_vars::elevation_velocity                           = 1;
const double N_inter::n_data::n_motion_vars::n_calc_vars::degree_peak_cutoff_for_triangles[axis_count] = { 0.001, 0.001 };
const double N_inter::n_data::n_motion_vars::n_calc_vars::max_velocity_round[axis_count]               = {1.0 / 3, 1.0 / 3};
const double N_inter::n_data::n_motion_vars::n_calc_vars::max_velocity[axis_count]                     = {1000, 1000};
const double N_inter::n_data::n_motion_vars::n_calc_vars::acceleration[axis_count]                     = { 1, 1 };
const double N_inter::n_data::n_motion_vars::n_calc_vars::kill_acceleration[axis_count]                = {5, 5};
const double N_inter::n_data::n_motion_vars::n_calc_vars::accident_stay_time                           = 10;
const int    N_inter::n_data::n_motion_vars::n_calc_vars::max_axis_count                               = 20;
const double N_inter::n_data::n_motion_vars::n_calc_vars::time_step_for_motion_table                   = 0.01;
// --------------------------------------------------------
