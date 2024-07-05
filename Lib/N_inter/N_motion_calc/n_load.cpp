#include "n_load.h"
#include "N_inter/S_exception.h"
#include <QFile>
// --------------------------------------------------------

using N_inter::S_exception;
// --------------------------------------------------------

const QString N_inter::n_motion_calc::n_load::separator = "--------------------";
// --------------------------------------------------------

QStringList N_inter::n_motion_calc::n_load::load_from_file(QString filename) {
    if (filename.isEmpty()) {
        S_exception exc;
        exc.m_calling_object = "QStringList N_inter::n_motion_calc::n_load::load_from_file(QString filename)";
        exc.m_condition = "filename.isEmpty()";
        exc.m_decision = "Не указано имя файла";
        throw exc;
    }

    // Открытие файла
    QFile file;
    file.setFileName(filename);
    file.open(QFile::ReadOnly);
    if (!file.isOpen()) {
        S_exception exc;
        exc.m_calling_object = "QStringList N_inter::n_motion_calc::n_load::load_from_file(QString filename)";
        exc.m_condition = "!file.isOpen()";
        exc.m_decision = "Файл со строками не открыт";
        throw exc;
    }

    // Чтение строк
    QString file_content = file.readAll();
    QStringList result = file_content.split(separator);

    if (result.size() == 0) {
        S_exception exc;
        exc.m_calling_object = "QStringList N_inter::n_motion_calc::n_load::load_from_file(QString filename)";
        exc.m_condition = "result.size() == 0";
        exc.m_decision = "Файл со строками не содержит строк";
        throw exc;
    }

    // Удаление пустых строк
    for (int i = 0; i < result.size(); i++) {
        if ((result[i] == "") || (result[i] == "\n") || (result[i] == "\r")) {
            result.removeAt(i);
            i--;
        }
    }

    // Удаление символов \n \r с начала первых и с конца последних строк
    for (int i = 0; i < result.size(); i++) {
        // Два раза проверка
        for (int j = 0; j < 2; j++) {
            // Первый символ
            QChar first = result[i][0];

            // Последний символ
            QChar last = result[i].back();

            // Удаление первого символа по необходимости
            if ((first == QChar('\n')) || (first == QChar('\r'))) {
                result[i] = result[i].remove(0, 1);
            }

            // Удаление последнего символа по необходимости
            if ((last == QChar('\n')) || (last == QChar('\r'))) {
                result[i] = result[i].remove(result[i].size() - 1, 1);
            }
        }
    }

    return result;
}
// --------------------------------------------------------
