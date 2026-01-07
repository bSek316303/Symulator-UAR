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
    void dodaj_do_listy(QTextBrowser *lista_wspolczynnikow, QDoubleSpinBox *wsp);

private slots:
    void on_a_confirm_clicked();

    void on_b_confirm_clicked();

    void on_remove_a_clicked();

    void on_remove_b_clicked();


private:
    Ui::arx_dialog *ui;
    std::vector<double> wsp_a;
    std::vector<double> wsp_b;
    double oponienie;
    double zaklocenia;
};

#endif // ARX_DIALOG_H
