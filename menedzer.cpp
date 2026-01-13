#include "menedzer.h"
#include "qdebug.h"
#include "qglobal.h"

// USTAWIANIE PARAMETRÓW.
void menedzer::set_parametry_pid(Config& cfg){
    try {
        auto* pid = dynamic_cast<PIDConfig*>(&cfg);
        m_uar.get_regulator().set_kp(pid->get_kp());
        m_uar.get_regulator().set_ti(pid->get_ti());
        m_uar.get_regulator().set_td(pid->get_td());
        m_uar.get_regulator().set_licz_calke(RegulatorPID::LiczCalke(pid->get_licz_calke()));
    } catch (const std::bad_cast&) {
        qDebug() << "castowanie na zły typ pliku w set_parametry_pid!";
    }
}

void menedzer::set_parametry_arx(Config& cfg){
    try {
        auto* arx = dynamic_cast<ARXConfig*>(&cfg);
        m_uar.get_ARX().set_A(arx->get_a());
        m_uar.get_ARX().set_B(arx->get_b());
        m_uar.get_ARX().set_opoznienie(arx->get_opoznienie());
        m_uar.get_ARX().set_szum(arx->get_szum());
    } catch (const std::bad_cast&) {
        qDebug() << "castowanie na zły typ pliku w set_parametry_arx!";
    }
}

void menedzer::set_parametry_generator(Config& cfg){
    try {
        auto* gen = dynamic_cast<GENConfig*>(&cfg);
        m_gen.setAmplituda(gen->get_a());
        m_gen.setWypelnienie(gen->get_p());
        m_gen.setStalaSkladowa(gen->get_s());
        m_gen.setOkres(gen->get_okres());
        m_gen.setSygnal(Generator::Sygnaly(gen->get_syg()));
    } catch (const std::bad_cast&) {
        qDebug() << "castowanie na zły typ pliku w set_parametry_generator!";
    }
}

menedzer::menedzer(ProstyUAR uar, Generator gen, PIDConfig* pid_cfg, ARXConfig* arx_cfg, GENConfig* gen_cfg)
    : m_uar(uar), m_gen(gen)
{
    // Ustawienie abstrakcji do wspólpracy z GUI.
    pid_cfg->set_obserwator(std::bind(&menedzer::set_parametry_pid, this, std::placeholders::_1));
    pid_cfg->set_obserwator_calki(std::bind(&menedzer::resetuj_pamiec_calki, this));
    pid_cfg->set_obserwator_rozniczki(std::bind(&menedzer::resetuj_pamiec_rozniczki, this));
    arx_cfg->set_obserwator(std::bind(&menedzer::set_parametry_arx, this, std::placeholders::_1));
    gen_cfg->set_obserwator(std::bind(&menedzer::set_parametry_generator, this, std::placeholders::_1));
}

void menedzer::resetuj_pamiec_calki() { m_uar.get_regulator().resetuj_pamiec_calki(); }
void menedzer::resetuj_pamiec_rozniczki() { m_uar.get_regulator().resetuj_pamiec_rozniczki(); }

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
void menedzer::set_okres(double okres_p)
{
    okres = okres_p;
}

double menedzer::get_taktowanie()
{
    return taktowanie;
}
double menedzer::get_okres()
{
    return okres;
}

QJsonObject menedzer::menedzer_to_json()
{
    QJsonObject menedzer;
    menedzer["Taktowanie_ms"] = this->get_taktowanie();
    menedzer["Okres_rzeczywisty_s"] = this->get_okres();
    return menedzer;
}

