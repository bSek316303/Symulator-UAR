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
private:
    std::vector<QLineSeries*> tab_serii;
    std::vector<QChart*> tab_wykresow;
    std::vector<QValueAxis*> tab_osi_x;
    std::vector<QValueAxis*> tab_osi_y;
    std::vector<double> tab_max;
    std::vector<double> tab_min;
    double zakres_osi_x;
    skalowanie_wykresow skalowanie;
public:
    MainWindow(menedzer* menedzer_p, QWidget *parent = nullptr);
    ~MainWindow();
    void set_wartosci_domyslne();
    void set_menedzer(menedzer* m){ menedzer = m; }
    void append(dane_do_wykresow dane, double czas);

    void dodaj_serie(QLineSeries* seria);
    void dodaj_wykres(QChart* wykres);
    void dodaj_os_x(QValueAxis* os);
    void dodaj_os_y(QValueAxis* os);
    void set_czas_wykresu(double nowy_czas);
    void zwieksz_zakres_osi_x(double czas);
    void ustaw_dane_po_wczytaniu();
private slots:
    void on_btn_nastawy_arx_clicked();

    void on_btn_resetuj_pamiec_calki_clicked();

    void on_btn_reset_pamieci_rozniczki_clicked();

    void on_rdio_w_calce_toggled(bool checked);

    void on_rdio_poza_calka_toggled(bool checked);

    void on_btn_stop_clicked();

    void on_btn_start_clicked();

    void on_btn_reset_clicked();

    void on_comboBox_typ_sygnalu_currentIndexChanged(int index);

    //void on_zapisz_konfiguracje_clicked();

    //void on_wczytaj_konfiguracje_clicked();


    void on_spnbx_wzmocnienie_editingFinished();

    void on_spnbx_stal_calkowania_editingFinished();

    void on_spnbx_stala_rozniczkowania_editingFinished();

    void on_spnbx_czas_wykresu_editingFinished();

    void on_spnbx_okres_editingFinished();

    void on_spnbx_taktowanie_editingFinished();

    void on_spnbx_amplituda_editingFinished();

    void on_spnbx_stala_skladowa_editingFinished();

    void on_spnbx_wypelnienie_editingFinished();

private:
    Ui::MainWindow *ui;
    menedzer* menedzer;
};
#endif // MAINWINDOW_H
