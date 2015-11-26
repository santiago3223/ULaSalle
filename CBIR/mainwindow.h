#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnMatrizNumerica_clicked();

    void on_btn_CargarConsultas_clicked();

    void on_btn_CargarDatos_clicked();

    void on_btnCalcularResultados_clicked();

private:
    Ui::MainWindow *ui;

    void CargarAlternativas(const char * fileName);
};

#endif // MAINWINDOW_H
