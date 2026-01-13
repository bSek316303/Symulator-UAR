#include "menedzer.h"
#include "qdebug.h"
#include "qglobal.h"

// USTAWIANIE PARAMETRÓW.

// ARX
void menedzer::set_parametry_arx(const std::vector<double>& A, const std::vector<double>& B){ m_uar.set_parametry_arx(A, B); }
void menedzer::set_szum(double szum, bool czy_wlaczony){ m_uar.set_szum(szum); }
void menedzer::set_opoznienie_ARX(int opoznienie) { m_uar.set_opoznienie(opoznienie); }

// PID
void menedzer::set_parametry_pid(double kp, double ti, double td){ m_uar.set_parametry_pid(kp, ti, td); }
void menedzer::set_pid_tryb(int index) {
    qDebug() << "menedzer";
    m_uar.set_licz_calke(RegulatorPID::LiczCalke(index));
}
void menedzer::resetuj_pamiec_calki(){ m_uar.resetuj_pamiec_calki(); }
void menedzer::resetuj_pamiec_rozniczki(){ m_uar.resetuj_pamiec_rozniczki(); }

// Generator
void menedzer::set_parametry_generator(double amplituda, double stala_skladowa, double okres, double wypelnienie){
    qDebug() << "menedzer";
    m_gen.set_amplituda(amplituda);
    m_gen.set_stala_skladowa(stala_skladowa);
    m_gen.set_okres(okres);
    m_gen.set_wypelnienie(wypelnienie);
    qDebug() << "koniec menedzera";
}
void menedzer::set_sygnal(int index) { m_gen.set_sygnal(Generator::Sygnaly(index)); }

// Symulacja
void set_taktowanie(double taktowanie_p);

menedzer::menedzer(ProstyUAR& uar, Generator& gen)
    : m_uar(uar), m_gen(gen)
{}

dane_do_wykresow menedzer::krok_wykresu(double interwal){
    // Symulacja
    double wart_zad = m_gen.generuj(interwal);
    double syg_wy = m_uar.symuluj(wart_zad);
    RegulatorPID& reg = m_uar.get_regulator();
    // Pakowanie danych
    dane_do_wykresow dane;
    dane.uar = syg_wy;
    dane.gen = wart_zad;
    dane.uchyb = m_uar.get_uchyb();
    dane.ster = m_uar.get_syg_ster();
    dane.p = reg.get_ostatni_P();
    dane.i = reg.get_ostatni_I();
    dane.d = reg.get_ostatni_D();
    return dane;
}

void menedzer::resetuj(){
    m_uar.resetuj();
    m_gen.resetuj();
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
// void menedzer::wczytaj_konfiguracje(const QJsonDocument& dane_json)
// {
//     if (dane_json.isNull() || !dane_json.isObject()) {
//         qDebug() << "Błąd: Dokument JSON jest pusty lub nie jest głównym obiektem.";
//         return;
//     }

//     QJsonObject obiekt_danych = dane_json.object();

//     if (obiekt_danych.contains("PID") && obiekt_danych["PID"].isObject()) {
//         QJsonObject pid_json = obiekt_danych["PID"].toObject();

//         set_parametry_PID(
//             pid_json["Kp"].toDouble(),
//             pid_json["Ti"].toDouble(),
//             pid_json["Td"].toDouble()
//             );
//     }

//     if (obiekt_danych.contains("ARX") && obiekt_danych["ARX"].isObject()) {
//         QJsonObject arx_json = obiekt_danych["ARX"].toObject();

//         if (arx_json.contains("Wektor_A") && arx_json["Wektor_A"].isArray() &&
//             arx_json.contains("Wektor_B") && arx_json["Wektor_B"].isArray())
//         {
//             QVector<double> wektor_A_qt = Json_to_Wektor(arx_json["Wektor_A"].toArray());
//             QVector<double> wektor_B_qt = Json_to_Wektor(arx_json["Wektor_B"].toArray());

//             std::vector<double> wektor_A(wektor_A_qt.begin(), wektor_A_qt.end());
//             std::vector<double> wektor_B(wektor_B_qt.begin(), wektor_B_qt.end());

//             set_parametry_ARX(wektor_A, wektor_B);
//         }
//         set_szum(
//             arx_json["szum"].toDouble(),
//             arx_json["Czy_wlaczony_szum"].toBool()
//             );

//         set_opoznienie_ARX(arx_json["Opoznienie"].toInt());

//         set_ograniczenia_sterowania_ARX(
//             arx_json["Ograniczenie_sterowania"].toBool(),
//             arx_json["Sterowanie_min"].toDouble(),
//             arx_json["Sterowanie_max"].toDouble()
//             );

//         set_ograniaczenia_wyjscia_ARX(
//             arx_json["Ograniczenie_wyjscia"].toBool(),
//             arx_json["Wyjscie_min"].toDouble(),
//             arx_json["Wyjscie_max"].toDouble()
//             );
//     }

//     if (obiekt_danych.contains("Parametry_Symulacji") && obiekt_danych["Parametry_Symulacji"].isObject()) {
//         QJsonObject uar_json = obiekt_danych["Parametry_Symulacji"].toObject();

//         this->set_taktowanie(uar_json["Taktowanie_ms"].toDouble());
//         this->set_okres(uar_json["Okres_rzeczywisty_s"].toDouble());
//     }
// }
// // void menedzer::zastosuj_konfiguracje()
// // {
// //     QJsonDocument dane = this->obsluga_pliku.wczytajKonfiguracje();
// //     this->wczytaj_konfiguracje(dane);
// // }
// void menedzer::set_parametry_PID(double Kp, double Ti, double Td) {
//     m_uar.get_regulator().set_kp(Kp);
//     m_uar.get_regulator().set_ti(Ti);
//     m_uar.get_regulator().set_td(Td);
// }
// void menedzer::set_pid_tryb(RegulatorPID::LiczCalke mode) {
//     m_uar.get_regulator().set_licz_calke(mode);
// }

// void menedzer::set_taktowanie(double taktowanie_p)
// {
//     taktowanie = taktowanie_p;
// }
double menedzer::get_taktowanie()
{
    return taktowanie;
}


QJsonObject menedzer::menedzer_to_json()
{
    QJsonObject menedzer;
    menedzer["Taktowanie_ms"] = this->get_taktowanie();
    menedzer["Okres_rzeczywisty_s"] = this->m_gen.get_okres();
    return menedzer;
}

