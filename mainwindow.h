#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_nastawy_arx_clicked();

    void on_spnbx_wzmocnienie_valueChanged(double arg1);

    void on_spnbx_stal_calkowania_valueChanged(double arg1);

    void on_spnbx_stala_rozniczkowania_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
