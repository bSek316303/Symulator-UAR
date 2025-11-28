#include "menedzerUAR.h"
#include "ProstyUAR.h"

MenadzerUAR::MenadzerUAR(){};
void MenadzerUAR::zapisz_konfiguracje()
{
    ProstyUAR uar = *this->prostyUar;
    ModelARX& arx = uar.get_ARX();
    RegulatorPID& pid = uar.get_regulator();

    this->oblsugaPliku.zapiszKonfiguracje(uar, arx, pid);
}
QVector<double> MenadzerUAR::Json_to_Wektor(const QJsonArray& tablica_json)
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
void MenadzerUAR::wczytaj_konfiguracje(const QJsonDocument& dane_json)
{
    if (dane_json.isNull() || !dane_json.isObject()) {
        qDebug() << "Błąd: Dokument JSON jest pusty lub nie jest głównym obiektem.";
        return;
    }

    QJsonObject obiekt_danych = dane_json.object();

    if (obiekt_danych.contains("PID") && obiekt_danych["PID"].isObject()) {
        QJsonObject pid_json = obiekt_danych["PID"].toObject();

        set_parametry_PID(
            pid_json["Kp"].toDouble(),
            pid_json["Ti"].toDouble(),
            pid_json["Td"].toDouble()
            );
    }

    if (obiekt_danych.contains("ARX") && obiekt_danych["ARX"].isObject()) {
        QJsonObject arx_json = obiekt_danych["ARX"].toObject();

        if (arx_json.contains("Wektor_A") && arx_json["Wektor_A"].isArray() &&
            arx_json.contains("Wektor_B") && arx_json["Wektor_B"].isArray())
        {
            QVector<double> wektor_A_qt = Json_to_Wektor(arx_json["Wektor_A"].toArray());
            QVector<double> wektor_B_qt = Json_to_Wektor(arx_json["Wektor_B"].toArray());

            std::vector<double> wektor_A(wektor_A_qt.begin(), wektor_A_qt.end());
            std::vector<double> wektor_B(wektor_B_qt.begin(), wektor_B_qt.end());

            set_parametry_ARX(wektor_A, wektor_B);
        }
        set_szum(
            arx_json["szum"].toDouble(),
            arx_json["Czy_wlaczony_szum"].toBool()
            );

        set_opoznienie_ARX(arx_json["Opoznienie"].toInt());

        set_ograniczenia_sterowania_ARX(
            arx_json["Ograniczenie_sterowania"].toBool(),
            arx_json["Sterowanie_min"].toDouble(),
            arx_json["Sterowanie_max"].toDouble()
            );

        set_ograniaczenia_wyjscia_ARX(
            arx_json["Ograniczenie_wyjscia"].toBool(),
            arx_json["Wyjscie_min"].toDouble(),
            arx_json["Wyjscie_max"].toDouble()
            );
    }

    if (obiekt_danych.contains("Parametry_Symulacji") && obiekt_danych["Parametry_Symulacji"].isObject()) {
        QJsonObject uar_json = obiekt_danych["Parametry_Symulacji"].toObject();

        prostyUar->set_taktowanie(uar_json["Taktowanie_ms"].toDouble());
        prostyUar->set_okres(uar_json["Okres_rzeczywisty_s"].toDouble());
    }
}
void MenadzerUAR::zastosuj_konfiguracje()
{
    QJsonDocument dane = this->oblsugaPliku.wczytajKonfiguracje();
    this->wczytaj_konfiguracje(dane);
}
void MenadzerUAR::set_parametry_PID(double Kp, double Ti, double Td) {
    prostyUar->get_regulator().setWzmocnienie(Kp);
    prostyUar->get_regulator().setStalaCalk(Ti);
    prostyUar->get_regulator().setStalaRozn(Td);
    prostyUar->get_regulator().setWzmocnienie(Kp);
    prostyUar->get_regulator().setStalaCalk(Ti);
    prostyUar->get_regulator().setStalaRozn(Td);
}
void MenadzerUAR::set_pid_tryb(RegulatorPID::LiczCalke mode) {
    prostyUar->get_regulator().setLiczCalke(mode);
}

void MenadzerUAR::reset_pamieci_pid() {
    prostyUar->get_regulator().resetujPamiec();
}

void MenadzerUAR::set_parametry_ARX(const std::vector<double>& A, const std::vector<double>& B) {
    prostyUar->get_ARX().set_A(A);
    prostyUar->get_ARX().set_B(B);
}

void MenadzerUAR::set_ograniczenia_sterowania_ARX(bool wlaczone, double min, double max) {
    prostyUar->get_ARX().set_ograniczenie_sterowania(wlaczone, min, max);
}
void MenadzerUAR::set_ograniaczenia_wyjscia_ARX(bool wlaczone, double min, double max) {
    prostyUar->get_ARX().set_ograniczenie_wyjscia(wlaczone, min, max);
}
void MenadzerUAR::set_szum(double szum, bool czy_wlaczony) {
    prostyUar->get_ARX().set_szum(szum);
    prostyUar->get_ARX().set_czy_wlaczony_szum(czy_wlaczony);
}
void MenadzerUAR::set_opoznienie_ARX(int opoznienie_p)
{
    prostyUar->get_ARX().set_opoznienie(opoznienie_p);
}

