#include "menedzer.h"
#include "qdebug.h"
#include "qglobal.h"

// USTAWIANIE PARAMETRÓW.

// ARX
void menedzer::set_parametry_arx(const std::vector<double>& A, const std::vector<double>& B){ m_uar.set_parametry_arx(A, B); }
void menedzer::set_szum(double szum, bool czy_wlaczony){ m_uar.set_szum(szum); }
void menedzer::set_opoznienie_ARX(int opoznienie) { m_uar.set_opoznienie(opoznienie); }
void menedzer::set_ograniczenia_ster_ARX(bool wlaczone){m_uar.set_ograniczenie_ster(wlaczone);}
void menedzer::set_ograniczenia_wyj_ARX(bool wlaczone) {m_uar.set_ograniczenie_wyj(wlaczone);}

// PID
void menedzer::set_parametry_pid(double kp, double ti, double td){ m_uar.set_parametry_pid(kp, ti, td); }
void menedzer::set_pid_tryb(int index) {
    m_uar.set_licz_calke(RegulatorPID::LiczCalke(index));
}
void menedzer::resetuj_pamiec_calki(){ m_uar.resetuj_pamiec_calki(); }
void menedzer::resetuj_pamiec_rozniczki(){ m_uar.resetuj_pamiec_rozniczki(); }

// Generator
void menedzer::set_parametry_generator(double amplituda, double stala_skladowa, double okres, double wypelnienie){
    m_gen.set_amplituda(amplituda);
    m_gen.set_stala_skladowa(stala_skladowa);
    m_gen.set_okres(okres);
    m_gen.set_wypelnienie(wypelnienie);
}
void menedzer::set_sygnal(int index) { m_gen.set_sygnal(Generator::Sygnaly(index)); }

menedzer::menedzer(ProstyUAR uar, Generator gen, QObject* parent)
    : QObject(parent), m_uar(uar), m_gen(gen), skalowanie()
{
    stoper = new QTimer(this);
    stoper->setInterval(POCZ_TAKTOWANIE);
    connect(stoper, &QTimer::timeout, this, &menedzer::krok);
    zakres_osi_x = POCZ_ZAKRES_X;
    aktualny_czas_wykresu = zakres_osi_x;
    czas = 0.0;
    skalowanie.setup(&tab_serii, &tab_wykresow, &tab_osi_x, &tab_osi_y, &tab_max, &tab_min);
}

void menedzer::krok() {
    auto start = std::chrono::high_resolution_clock::now();

    czas += static_cast<double>(stoper->interval()) / 1000.0;
    double wart_zad = m_gen.generuj(stoper->interval());
    double syg_wy = m_uar.symuluj(wart_zad);
    RegulatorPID& reg = m_uar.get_regulator();
    dane_do_wykresow dane;
    dane.uar = syg_wy;
    dane.gen = wart_zad;
    dane.uchyb = m_uar.get_uchyb();
    dane.ster = m_uar.get_syg_ster();
    dane.p = reg.get_ostatni_P();
    dane.i = reg.get_ostatni_I();
    dane.d = reg.get_ostatni_D();

    skalowanie.skaluj_wykresy_po_appendzie(dane);
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

    auto end = std::chrono::high_resolution_clock::now();
    auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    qDebug() << "Czas: " << czas.count() << " ms\n";
}

QVector<double> menedzer::Json_to_Wektor(const QJsonArray& tablica_json)
{
    QVector<double> wektor;
    for(const QJsonValue& wartosc: tablica_json)
    {
        if (wartosc.isDouble() || wartosc.isString()) {
            wektor.append(wartosc.toDouble());
        }
    }
    return wektor;
}
void menedzer::wyslij_arx()
{

    emit wyslij_dane_do_arx_dialog(
        m_uar.get_ARX().get_A(),
        m_uar.get_ARX().get_B(),
        m_uar.get_ARX().get_ograniczenie_sterowania(),
        m_uar.get_ARX().get_ograniczenie_wyjscia(),
        m_uar.get_ARX().get_szum(),
        m_uar.get_ARX().get_opoznienie(),
        m_uar.get_ARX().get_sterowanie_max(),
        m_uar.get_ARX().get_sterowanie_min(),
        m_uar.get_ARX().get_wyjscie_max(),
        m_uar.get_ARX().get_wyjscie_min()
        );
}

QJsonObject menedzer::menedzer_to_json()
{
    QJsonObject menedzer;
    menedzer["Taktowanie_ms"] = stoper->interval();
    menedzer["Okres_rzeczywisty_s"] = this->m_gen.get_okres();
    return menedzer;
}

// PRZYGOTOWANIE SYMULACJI

void menedzer::dodaj_serie(QLineSeries* seria){ tab_serii.push_back(seria); }
void menedzer::dodaj_wykres(QChart* wykres) {
    tab_wykresow.push_back(wykres);
    tab_max.push_back(std::numeric_limits<double>::min());
    tab_min.push_back(std::numeric_limits<double>::max());
}
void menedzer::dodaj_os_x(QValueAxis* os) {
    tab_osi_x.push_back(os);
    os->setRange(0, zakres_osi_x);
}
void menedzer::dodaj_os_y(QValueAxis* os) {
    tab_osi_y.push_back(os);
    os->setRange(-10, 10);
}
void menedzer::set_interwal(int time_in_ms){ stoper->setInterval(time_in_ms); }

void menedzer::zwieksz_zakres_osi_x(double czas){
    for(auto& x: tab_osi_x){ x->setRange(czas - zakres_osi_x / 2,czas + zakres_osi_x / 2); }
    skalowanie.skaluj_wykresy_przy_resizie(czas - zakres_osi_x / 2, czas + zakres_osi_x / 2);
}
void menedzer::set_czas_wykresu(double nowy_czas){ skalowanie.set_czas_wykresu(nowy_czas, &zakres_osi_x, &aktualny_czas_wykresu, &czas);}

// SYMULACJA

void menedzer::zacznij_symulacje() { stoper->start(); }
void menedzer::zakoncz_symulacje() { stoper->stop(); }
void menedzer::resetuj_symulacje(){
    stoper->stop();
    czas = 0.0;
    m_uar.resetuj();
    m_gen.resetuj();
    for(auto &wykres: tab_wykresow){
        for (QAbstractSeries *abstractSeries : wykres->series()) {
            QLineSeries *seria = qobject_cast<QLineSeries*>(abstractSeries);
            if (!seria) continue;
            seria->clear();
        }
    }
    for(auto& x: tab_osi_x){ x->setRange(0, zakres_osi_x); }
    aktualny_czas_wykresu = zakres_osi_x;
}
