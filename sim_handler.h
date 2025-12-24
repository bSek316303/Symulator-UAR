#ifndef SIM_HANDLER_H
#define SIM_HANDLER_H
#include "qobject.h"
#include <QTimer>
#include "menedzer.h"
#include <QtCharts/QtCharts>
#include <QDebug>
#include <fstream>
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
    int licznik_krokow = 0;
    int zakres_osi_x;
    std::vector<dane_do_wykresow> tab_danych;
    void skaluj_wykresy_y(dane_do_wykresow dane){
        // Wykres 1
        double min_dane = (dane.uar < dane.gen) ? dane.uar : dane.gen;
        double max_dane = (dane.uar > dane.gen) ? dane.uar : dane.gen;
        if(tab_min[0] > min_dane){
            tab_min[0] = min_dane;
            tab_osi_y[0]->setMin(min_dane);
        }
        if(tab_max[0] < max_dane){
            tab_max[0] = max_dane;
            tab_osi_y[0]->setMax(max_dane);
        }

        // Wykres 2
        double dane_min_max = dane.uchyb;
        if(tab_min[1] > dane_min_max){
            tab_min[1] = dane_min_max;
            tab_osi_y[1]->setMin(dane_min_max);
        }
        else if(tab_max[1] < dane_min_max){
            tab_max[1] = dane_min_max;
            tab_osi_y[1]->setMax(dane_min_max);
        }

        // Wykres 3
        dane_min_max = dane.ster;
        if(tab_min[2] > dane_min_max){
            tab_min[2] = dane_min_max;
            tab_osi_y[2]->setMin(dane_min_max);
        }
        else if(tab_max[2] < dane_min_max){
            tab_max[2] = dane_min_max;
            tab_osi_y[2]->setMax(dane_min_max);
        }

        // Wykres 4
        min_dane = std::max({dane.p, dane.i, dane.d});
        max_dane = std::min({dane.p, dane.i, dane.d});
        if(tab_min[3] > min_dane){
            tab_min[3] = min_dane;
            tab_osi_y[3]->setMin(min_dane);
        }
        if(tab_max[3] < max_dane){
            tab_max[3] = max_dane;
            tab_osi_y[3]->setMax(max_dane);
        }
    }

    int steps_low;
    int steps_high;
public:
    void zapisz_do_pliku_csv(const std::string& nazwa_pliku){
        double dt = stoper->interval() / 1000;
        std::ofstream file(nazwa_pliku);
        if (!file.is_open()) {
            qDebug() << "Nie mozna otworzyc pliku!";
            return;
        }

        // Nagłówek
        file << "czas,uar,gen,uchyb,ster,p,i,d\n";

        double czas = 0.0;
        for (const auto& d : tab_danych) {
            file << czas << ","
                 << d.uar << ","
                 << d.gen << ","
                 << d.uchyb << ","
                 << d.ster << ","
                 << d.p << ","
                 << d.i << ","
                 << d.d << "\n";
            czas += dt;
        }

        file.close();
    }
    sim_handler() {
        stoper = new QTimer(this);
        stoper->setInterval(POCZ_TAKTOWANIE);
        connect(stoper, &QTimer::timeout, this, &sim_handler::krok);
        tab_danych.reserve(2000);
        zakres_osi_x = POCZ_ZAKRES_X;
    }
    QTimer& get_stoper() { return *stoper; }
    void set_menedzer(menedzer* m) { m_menedzer = m; }
    void dodaj_serie(QLineSeries* seria){ tab_serii.push_back(seria); }
    void dodaj_wykres(QChart* wykres) {
        tab_wykresow.push_back(wykres);
        tab_max.push_back(0);
        tab_min.push_back(0);
    }
    void dodaj_os_x(QValueAxis* os) {
        tab_osi_x.push_back(os);
        os->setRange(0, zakres_osi_x);
    }
    void dodaj_os_y(QValueAxis* os) { tab_osi_y.push_back(os); os->setRange(-100, 100); }
    void zwieksz_zakres_osi_x(){
        int stary_zakres = zakres_osi_x;
        zakres_osi_x += zakres_osi_x / 2;
        for(auto& x: tab_osi_x){
            x->setRange(stary_zakres / 2, zakres_osi_x);
        }
    }
    // Symulacja
    void set_interwal(int time_in_ms){
        if(time_in_ms > 1000) time_in_ms = 1000;
        if(time_in_ms < 10) time_in_ms = 10;
        stoper->setInterval(time_in_ms);
    }
    void zacznij_symulacje() {
        qDebug() << "test czasowy";
        test_czasowy();
    }
    void zakoncz_symulacje() { stoper->stop(); }
    void test_czasowy(){
        using clock = std::chrono::high_resolution_clock;
        auto start = clock::now();
        for(int i = 0; i < 1000; i++){
            krok();
        }
        auto koniec = clock::now();
        std::chrono::duration<double> elapsed = koniec - start;
        qDebug() << "Czas 1000 wykonan: " << elapsed.count() << " s\n";
        qDebug() << "Sredni czas jednego wykonania: "
                  << elapsed.count() / 1000 << " s\n";
    }
    void krok(){
        int czas = (licznik_krokow++ * stoper->interval()) / 1000;
        dane_do_wykresow dane = m_menedzer->krok_wykresu(stoper->interval());
        skaluj_wykresy_y(dane);
        //tab_danych.push_back(dane);
        /*
        tab_serii[0]->append(czas, dane.uar);
        tab_serii[1]->append(czas, dane.gen);
        tab_serii[2]->append(czas, dane.uchyb);
        tab_serii[3]->append(czas, dane.ster);
        tab_serii[4]->append(czas, dane.p);
        tab_serii[5]->append(czas, dane.i);
        tab_serii[6]->append(czas, dane.d);
        */
        if(czas >= zakres_osi_x){
            zwieksz_zakres_osi_x();
        }
    }
    /* Sam generator
    void krok(){
        double czas = static_cast<double>(licznik_krokow++ * stoper->interval()) / 1000.0;
        qDebug() << "czas: " << czas;
        dane_do_wykresow dane = m_menedzer->krok_wykresu(stoper->interval());
        //tab_danych.push_back(dane);
        tab_serii[1]->append(czas, dane.gen);
        if(czas >= zakres_osi_x){
            zwieksz_zakres_osi_x();
        }
    }
*/
};

#endif // SIM_HANDLER_H
