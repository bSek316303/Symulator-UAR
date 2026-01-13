#ifndef SIM_HANDLER_H
#define SIM_HANDLER_H
#include "qobject.h"
#include <QTimer>
#include "menedzer.h"
#include <QtCharts/QtCharts>
#include <QDebug>
#include <chrono>

class sim_handler: public QObject
{
    Q_OBJECT
private:
    QTimer* stoper;
    menedzer* m_menedzer;
    std::vector<QLineSeries*> tab_serii;
    std::vector<QChart*> tab_wykresow;
    std::vector<QValueAxis*> tab_osi_x;
    std::vector<QValueAxis*> tab_osi_y;
    std::vector<double> tab_max;
    std::vector<double> tab_min;
    double czas;
    int zakres_osi_x;
    int aktualny_czas_wykresu;

    void skaluj_wykresy_po_appendzie(dane_do_wykresow dane);
    void zwieksz_zakres_osi_x(double czas);
    void skaluj_wykresy_przy_resizie(double min_range, double max_range);
public:
    sim_handler();
    QTimer& get_stoper();
    void set_menedzer(menedzer* m);
    void dodaj_serie(QLineSeries* seria);
    void dodaj_wykres(QChart* wykres);
    void dodaj_os_x(QValueAxis* os);
    void dodaj_os_y(QValueAxis* os);
    void set_interwal(int time_in_ms);
    void set_czas_wykresu(double nowyCzas);

    void zacznij_symulacje();
    void zakoncz_symulacje();
    void resetuj_symulacje();

    void test_czasowy();
    void krok();

    void zapisz_konfiguracje();
    void wczytaj_konfiguracje();
};

#endif // SIM_HANDLER_H
