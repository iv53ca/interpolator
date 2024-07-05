#pragma once
// --------------------------------------------------------

#include "N_inter/C_object.h"
#include "N_inter/N_motion_vars/n_calc_vars.h"
#include <vector>
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        enum COORD {
            X,
            Y,
            Z
        };
    }
}
// --------------------------------------------------------

namespace N_inter {
    namespace n_global_types {
        class C_point : public N_inter::C_object {
            std::vector<double> m_position;
        public:
            C_point();
            C_point(int a_value);
            ~C_point();

            double &operator[](int index);
            C_point &operator=(const C_point &new_point);

            bool operator==(C_point &point);
            bool operator!=(C_point &point);

            #warning Здесь аргумент не const
            C_point operator-(C_point &sec_point);
            C_point operator+(C_point &sec_point);

            QString m_to_string();
        };
    }
}
// --------------------------------------------------------
