#ifndef ARX_DIALOG_H
#define ARX_DIALOG_H
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
    void dodaj_do_listy(QTextBrowser lista_wspolczynnikow, QDoubleSpinBox wsp);

private:
    Ui::arx_dialog *ui;
    std::vector<double> wsp_a;
    std::vector<double> wsp_b;
    double oponienie;
    double zaklocenia;
};

#endif // ARX_DIALOG_H
