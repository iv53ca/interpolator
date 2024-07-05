#pragma once
// --------------------------------------------------------

#include <QStringList>
// --------------------------------------------------------

// TODO: переименовать, дать нормальные имена
namespace N_inter {
    namespace n_motion_calc {
        namespace n_load {
            // Разделитель для строк
            extern const QString separator;

            // Загрузка совокупности отрезков из файла для последующего перебора
            QStringList load_from_file(QString filename);
        }
    }
}
// --------------------------------------------------------
