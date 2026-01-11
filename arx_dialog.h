#ifndef ARX_DIALOG_H
#define ARX_DIALOG_H
#include "ui_arx_dialog.h"
#include<vector>
#include <QDialog>
#include<QTextBrowser>
#include<QDoubleSpinBox>
#include<QString>

namespace Ui {
class arx_dialog;
}

class arx_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit arx_dialog(QWidget *parent = nullptr);
    ~arx_dialog();
    void zastosuj_konfiguracje();
    std::vector<double> get_wsp_a();
    std::vector<double> get_wsp_b();
    double get_opoznienie();
    double get_zaklocenie();

private slots:
    void on_a_confirm_clicked();

    void on_b_confirm_clicked();

    void on_remove_a_clicked();

    void on_remove_b_clicked();

    void on_ok_arx_clicked();

    void on_opoznienie_input_valueChanged(double arg1);

    void on_zaklocenie_input_valueChanged(double arg1);

private:
    Ui::arx_dialog *ui;
    std::vector<double> wsp_a;
    std::vector<double> wsp_b;
    double opoznienie = 0;
    double zaklocenia = 0;
};

#endif // ARX_DIALOG_H
