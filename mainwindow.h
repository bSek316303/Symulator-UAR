#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menedzer.h"
#include "skalowanie_wykresow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(menedzer* menedzer_p, QWidget *parent = nullptr);
    ~MainWindow();
    void set_wartosci_domyslne();
    void set_menedzer(menedzer* m){ menedzer = m; }
private slots:
    void on_btn_nastawy_arx_clicked();

    void on_spnbx_wzmocnienie_valueChanged(double arg1);

    void on_spnbx_stal_calkowania_valueChanged(double arg1);

    void on_spnbx_stala_rozniczkowania_valueChanged(double arg1);

    void on_btn_resetuj_pamiec_calki_clicked();

    void on_btn_reset_pamieci_rozniczki_clicked();

    void on_rdio_w_calce_toggled(bool checked);

    void on_rdio_poza_calka_toggled(bool checked);

    void on_spnbx_amplituda_valueChanged(double arg1);

    void on_spnbx_stala_skladowa_valueChanged(double arg1);

    void on_spnbx_wypelnienie_valueChanged(double arg1);

    void on_spnbx_taktowanie_valueChanged(int arg1);

    void on_spnbx_okres_valueChanged(double arg1);

    void on_btn_stop_clicked();

    void on_btn_start_clicked();

    void on_btn_reset_clicked();

    void on_spnbx_czas_wykresu_valueChanged(int arg1);

    void on_comboBox_typ_sygnalu_currentIndexChanged(int index);

    //void on_zapisz_konfiguracje_clicked();

    //void on_wczytaj_konfiguracje_clicked();


private:
    Ui::MainWindow *ui;
    menedzer* menedzer;
};
#endif // MAINWINDOW_H
