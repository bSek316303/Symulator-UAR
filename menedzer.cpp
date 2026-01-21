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
    : QObject(parent), m_uar(uar), m_gen(gen)
{
    stoper = new QTimer(this);
    stoper->setInterval(POCZ_TAKTOWANIE);
    connect(stoper, &QTimer::timeout, this, &menedzer::krok);
    czas = 0.0;
}

void menedzer::krok() {
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

    to_append(dane, czas);
    czas += static_cast<double>(stoper->interval()) / 1000.0;
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

void menedzer::set_interwal(int time_in_ms){ stoper->setInterval(time_in_ms); }

// SYMULACJA

void menedzer::zacznij_symulacje() { stoper->start(); }
void menedzer::zakoncz_symulacje() { stoper->stop(); }
void menedzer::resetuj_symulacje(){
    stoper->stop();
    czas = 0.0;
    m_uar.resetuj();
    m_gen.resetuj();
}
