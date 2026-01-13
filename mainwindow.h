#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pidconfig.h"
#include "arxconfig.h"
#include "genconfig.h"
#include "sim_handler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(PIDConfig* pidcfg, ARXConfig* arxcfg, GENConfig* gencfg, sim_handler* simhandler, QWidget *parent = nullptr);
    ~MainWindow();
    PIDConfig* get_pid() {
        return pidconfig;
    }
    ARXConfig* get_arx(){
        return arxconfig;
    }
    GENConfig* get_gen(){
        return genconfig;
    }
    sim_handler* get_sim_handler() {
        return sim_handler;
    }
    void set_wartosci_domyslne();

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

<<<<<<< HEAD
    void on_zapisz_btn_clicked();
=======
    void on_zapisz_konfiguracje_clicked();

    void on_wczytaj_konfiguracje_clicked();
>>>>>>> c6255763ca7bc2bea758582c9a5e722534261237

private:
    Ui::MainWindow *ui;
    PIDConfig* pidconfig;
    ARXConfig* arxconfig;
    GENConfig* genconfig;
    sim_handler* sim_handler;
};
#endif // MAINWINDOW_H
