#ifndef QMW_MAIN_H
#define QMW_MAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class QMW_MAIN; }
QT_END_NAMESPACE

class QMW_MAIN : public QMainWindow
{
    Q_OBJECT

public:
    QMW_MAIN(QWidget *parent = nullptr);
    ~QMW_MAIN();

private slots:
    void on_PB_CALC_MOTION_clicked();
    void on_PB_CLEAR_clicked();

    // Загрузка отрезков с файла и работа интерполятора
    void on_PB_TEST_clicked();

    // TODO: переместить эти слоты в отдельное пространство имён
    // Генерирование отрезков и запись их в файл
    void on_PB_GENERATE_TURN_clicked();
    void on_PB_GENERATE_POLYGON_clicked();
    void on_PB_GENERATE_NINJA_clicked();
    void on_PB_GENERATE_SAW_clicked();

private:
    Ui::QMW_MAIN *ui;
};
#endif // QMW_MAIN_H
