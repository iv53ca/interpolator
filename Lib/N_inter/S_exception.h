#pragma once
// --------------------------------------------------------

#include <QString>
// --------------------------------------------------------

namespace N_inter {
    struct S_exception {
        QString m_condition;
        QString m_calling_object;
        QString m_decision;

        S_exception();
        S_exception(QString a_condition, QString a_calling_object, QString a_decision);

        void show_message();
    };
}
// --------------------------------------------------------
