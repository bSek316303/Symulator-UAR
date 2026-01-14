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
signals:
    void ograniczenie_sterowania_checked(int wartosc);
public:
    explicit arx_dialog(QWidget *parent = nullptr);
    ~arx_dialog();
    void zastosuj_konfiguracje();
    std::vector<double> get_wsp_a();
    std::vector<double> get_wsp_b();
    double get_opoznienie();
    double get_zaklocenie();
    bool get_ograniczenie_sterowania()
    {
        return ograniczenie_sterowania;
    }
    double get_ograniczenie_sterowania_dol()
    {
        return ograniczenie_sterowania_dol;
    }
    double get_ograniczenie_sterowania_gora()
    {
        return ograniczenie_sterowania_gora;
    }
    bool get_ograniczenie_wyjscia()
    {
        return ograniczenie_wyjscia;
    }
    double get_ograniczenie_wyjscia_dol()
    {
        return ograniczenie_wyjscia_dol;
    }
    double get_ograniczenie_wyjscia_gora()
    {
        return ograniczenie_wyjscia_gora;
    }

private slots:
    void on_a_confirm_clicked();

    void on_b_confirm_clicked();

    void on_remove_a_clicked();

    void on_remove_b_clicked();

    void on_ok_arx_clicked();

    void on_opoznienie_input_valueChanged(double arg1);

    void on_zaklocenie_input_valueChanged(double arg1);

    void on_ograniczenia_sterowania_checked_stateChanged(int arg1);

    void on_ograniczenia_wyjscia_checked_stateChanged(int arg1);
    void on_gorna_sterowanie_valueChanged(double arg1);

    void on_dolna_sterowanie_valueChanged(double arg1);


    void on_gorna_wyjscie_valueChanged(double arg1);

    void on_dolna_wyjscie_valueChanged(double arg1);

signals:
    void konfiguracja_zatwierdzona();
private:
    Ui::arx_dialog *ui;
    std::vector<double> wsp_a;
    std::vector<double> wsp_b;
    double opoznienie = 0;
    double zaklocenia = 0;
    bool ograniczenie_sterowania = false;
    bool ograniczenie_wyjscia = false;
    double ograniczenie_sterowania_dol= -10.0;
    double ograniczenie_sterowania_gora = 10.0;
    double ograniczenie_wyjscia_gora = 10.0;
    double ograniczenie_wyjscia_dol = -10.0;

};

#endif // ARX_DIALOG_H
