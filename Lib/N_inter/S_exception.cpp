#include "S_exception.h"
#include <QMessageBox>
// --------------------------------------------------------

N_inter::S_exception::S_exception() {}
// --------------------------------------------------------

N_inter::S_exception::S_exception(QString a_condition, QString a_calling_object, QString a_decision) :
    m_condition(a_condition),
    m_calling_object(a_calling_object),
    m_decision(a_decision) {}
// --------------------------------------------------------

void N_inter::S_exception::show_message() {
    QMessageBox message_box;

    // message_box.setIcon(QMessageBox::Critical);
    message_box.setText("S_exception");
    message_box.setInformativeText(m_calling_object + "\n" + m_condition + "\n" + m_decision);
    message_box.setStandardButtons(QMessageBox::Ok);
    message_box.setDefaultButton(QMessageBox::Ok);
    message_box.setStyleSheet("QLabel{min-width: 500px;}");

    message_box.exec();
}
// --------------------------------------------------------
