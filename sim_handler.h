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
    std::vector<dane_do_wykresow> tab_danych;

    void skaluj_wykresy_po_appendzie(dane_do_wykresow dane){
        // Wykres 1
        double min_dane = (dane.uar < dane.gen) ? dane.uar : dane.gen;
        double max_dane = (dane.uar > dane.gen) ? dane.uar : dane.gen;
        if(tab_min[0] > min_dane){
            if(min_dane < 0) tab_min[0] = min_dane * 1.15;
            else tab_min[0] = min_dane * 0.85;
            tab_osi_y[0]->setMin(tab_min[0]);
        }
        if(tab_max[0] < max_dane){
            if(max_dane > 0) tab_max[0] = max_dane * 1.15;
            else tab_max[0] = max_dane * 0.85;
            tab_osi_y[0]->setMax(tab_max[0]);
        }

        // Wykres 2
        double dane_min_max = dane.uchyb;
        if(tab_min[1] > dane_min_max){
            if(dane_min_max < 0) tab_min[1] = dane_min_max * 1.15;
            else tab_min[1] = dane_min_max * 0.85;
            tab_osi_y[1]->setMin(tab_min[1]);
        }
        else if(tab_max[1] < dane_min_max){
            if(dane_min_max > 0) tab_max[1] = dane_min_max * 1.15;
            else tab_max[1] = dane_min_max * 0.85;
            tab_osi_y[1]->setMax(tab_max[1]);
        }

        // Wykres 3
        dane_min_max = dane.ster;
        if(tab_min[2] > dane_min_max){
            if(dane_min_max < 0) tab_min[2] = dane_min_max * 1.15;
            else tab_min[2] = dane_min_max * 0.85;
            tab_osi_y[2]->setMin(tab_min[2]);
        }
        else if(tab_max[2] < dane_min_max){
            if(dane_min_max > 0) tab_max[2] = dane_min_max * 1.15;
            else tab_max[2] = dane_min_max * 0.85;
            tab_osi_y[2]->setMax(tab_max[2]);
        }

        // Wykres 4
        max_dane = std::max({dane.p, dane.i, dane.d});
        min_dane = std::min({dane.p, dane.i, dane.d});
        if(tab_min[3] > min_dane){
            if(min_dane < 0) tab_min[3] = min_dane * 1.15;
            else tab_min[3] = min_dane * 0.85;
            tab_osi_y[3]->setMin(tab_min[3]);
        }
        if(tab_max[3] < max_dane){
            if(max_dane > 0) tab_max[3] = max_dane * 1.15;
            else tab_max[3] = max_dane * 0.85;
            tab_osi_y[3]->setMax(tab_max[3]);
        }
    }
    void zwieksz_zakres_osi_x(double czas){
        for(auto& x: tab_osi_x){ x->setRange(czas - zakres_osi_x / 2,czas + zakres_osi_x / 2); }
        skaluj_wykresy_przy_resizie(czas - zakres_osi_x / 2, czas + zakres_osi_x / 2);
    }
    void skaluj_wykresy_przy_resizie(double min_range, double max_range){
        for(int i = 0; i < tab_wykresow.size(); i++){
            tab_min[i] = static_cast<double>(INT_MAX);
            tab_max[i] = static_cast<double>(INT_MIN);

            for (QAbstractSeries *abstractSeries : tab_wykresow[i]->series()) {
                QLineSeries *seria = qobject_cast<QLineSeries*>(abstractSeries);
                if (!seria) continue;
                const auto &punkty = seria->pointsVector();

                for (const auto &p : punkty) {
                    double argument = p.x();
                    double wartosc = p.y();
                    if (argument >= min_range && argument <= max_range) {
                        if(tab_min[i] > wartosc){
                            tab_min[i] = wartosc;
                        } else if(tab_max[i] < wartosc){
                            tab_max[i] = wartosc;
                        }
                    }
                }
            }

            if(tab_min[i] > 0) tab_osi_y[i]->setMin(tab_min[i] * 0.85);
            else tab_osi_y[i]->setMin(tab_min[i] * 1.15);
            if(tab_max[i] > 0) tab_osi_y[i]->setMax(tab_max[i] * 1.15);
            else tab_osi_y[i]->setMax(tab_max[i] * 0.85);
        }
    }
public:
    sim_handler() {
        stoper = new QTimer(this);
        stoper->setInterval(POCZ_TAKTOWANIE);
        connect(stoper, &QTimer::timeout, this, &sim_handler::krok);
        tab_danych.reserve(2000);
        zakres_osi_x = POCZ_ZAKRES_X;
        aktualny_czas_wykresu = zakres_osi_x;
        czas = 0.0;
    }
    QTimer& get_stoper() { return *stoper; }
    void set_menedzer(menedzer* m) { m_menedzer = m; }
    void dodaj_serie(QLineSeries* seria){ tab_serii.push_back(seria); }
    void dodaj_wykres(QChart* wykres) {
        tab_wykresow.push_back(wykres);
        tab_max.push_back(10.0);
        tab_min.push_back(-10.0);
    }
    void dodaj_os_x(QValueAxis* os) {
        tab_osi_x.push_back(os);
        os->setRange(0, zakres_osi_x);
    }
    void dodaj_os_y(QValueAxis* os) { tab_osi_y.push_back(os); os->setRange(-100, 100); }
    void set_interwal(int time_in_ms){
        if(time_in_ms > 1000) time_in_ms = 1000;
        if(time_in_ms < 10) time_in_ms = 10;
        stoper->setInterval(time_in_ms);
    }
    void set_czas_wykresu(double nowyCzas){
        zakres_osi_x = nowyCzas;
        if(czas == 0.0) for(auto& x: tab_osi_x) x->setRange(0, zakres_osi_x);
        else {
            if(czas - zakres_osi_x < 0) {
                for(auto& x: tab_osi_x) x->setRange(0.0, zakres_osi_x);
                skaluj_wykresy_przy_resizie(0.0, zakres_osi_x);
                aktualny_czas_wykresu = zakres_osi_x;
            } else {
                for(auto& x: tab_osi_x){ x->setRange(czas - zakres_osi_x / 2, czas + zakres_osi_x / 2);
                skaluj_wykresy_przy_resizie(czas - zakres_osi_x / 2, czas + zakres_osi_x / 2);
                aktualny_czas_wykresu = x->max();
                }
            }
        }
    }

    void zacznij_symulacje() { stoper->start(); }
    void zakoncz_symulacje() { stoper->stop(); }
    void resetuj_symulacje() {
        // TODO
    }

    void test_czasowy(){
        using clock = std::chrono::high_resolution_clock;
        auto start = clock::now();
        const int ilosc_wykonan = 1000;
        for(int i = 0; i < ilosc_wykonan; i++){ krok(); }
        auto koniec = clock::now();
        std::chrono::duration<double> czas = koniec - start;
        qDebug() << "Czas 1000 wykonan: " << czas.count() << " s\n";
        qDebug() << "Sredni czas jednego wykonania: "
                  << czas.count() / ilosc_wykonan << " s\n";
    }

    void krok(){
        czas += static_cast<double>(stoper->interval()) / 1000.0;
        dane_do_wykresow dane = m_menedzer->krok_wykresu(stoper->interval());
        skaluj_wykresy_po_appendzie(dane);
        tab_serii[0]->append(czas, dane.uar);
        tab_serii[1]->append(czas, dane.gen);
        tab_serii[2]->append(czas, dane.uchyb);
        tab_serii[3]->append(czas, dane.ster);
        tab_serii[4]->append(czas, dane.p);
        tab_serii[5]->append(czas, dane.i);
        tab_serii[6]->append(czas, dane.d);

        if(czas >= aktualny_czas_wykresu) {
            zwieksz_zakres_osi_x(czas);
            aktualny_czas_wykresu += zakres_osi_x / 2;
        }
    }
};

#endif // SIM_HANDLER_H
