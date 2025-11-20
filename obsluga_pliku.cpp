#include "obsluga_pliku.h"

Obsluga_pliku::Obsluga_pliku() {}

QJsonObject Obsluga_pliku::Model_ARX_to_Json(const ModelARX& model_arx) const
{
    QJsonObject obiekt_ARX;
    QJsonArray wektor_A;
    QJsonArray wektor_B;

    for(double wartosc: model_arx.get_A()) wektor_A.append(wartosc);
    for(double wartosc: model_arx.get_B()) wektor_B.append(wartosc);

    obiekt_ARX["Wektor_A"] = wektor_A;
    obiekt_ARX["Wektor_B"] = wektor_B;
    obiekt_ARX["Czy_wlaczony_szum"] = model_arx.get_czy_wlaczony_szum();
    obiekt_ARX["szum"] = model_arx.get_szum();
    obiekt_ARX["Opoznienie"] = model_arx.get_opoznienie();
    obiekt_ARX["Ograniczenie_sterowania"] = model_arx.get_ograniczenie_sterowania();
    obiekt_ARX["Sterowanie_min"] = model_arx.get_sterowanie_min();
    obiekt_ARX["Sterowanie_max"] = model_arx.get_sterowanie_max();
    obiekt_ARX["Ograniczenie_wyjscia"] = model_arx.get_ograniczenie_wyjscia();
    obiekt_ARX["Wyjscie_min"] = model_arx.get_wyjscie_min();
    obiekt_ARX["Wyjscie_max"] = model_arx.get_wyjscie_max();
    return obiekt_ARX;
}

QJsonObject Obsluga_pliku::RegulatorPID_to_Json(const RegulatorPID& Regulator_PID) const
{
    QJsonObject regulator_pid;

    regulator_pid["Kp"] = Regulator_PID.getKp();
    regulator_pid["Ti"] = Regulator_PID.getTi();
    regulator_pid["Td"] = Regulator_PID.getTd();

    return regulator_pid;
}

QJsonObject Obsluga_pliku::ProstyUAR_to_Json(const ProstyUAR& prosty_uar) const
{
    QJsonObject obiekt_UAR;
    obiekt_UAR["Taktowanie_ms"] = prosty_uar.get_taktowanie();
    obiekt_UAR["Okres_rzeczywisty_s"] = prosty_uar.get_m_okres();
    return obiekt_UAR;
}

void Obsluga_pliku::zapiszKonfiguracje(const ProstyUAR& uar,const ModelARX& arx,const RegulatorPID& pid)const
{
    QJsonObject UAR_json = ProstyUAR_to_Json(uar);
    QJsonObject arx_json = Model_ARX_to_Json(arx);
    QJsonObject pid_json = RegulatorPID_to_Json(pid);

    QJsonObject glowny_obiekt;

    glowny_obiekt["Parametry_Symulacji"] = UAR_json;
    glowny_obiekt["ARX"] = arx_json;
    glowny_obiekt["PID"] = pid_json;

    QJsonDocument dokument(glowny_obiekt);

    QByteArray jsonData = dokument.toJson(QJsonDocument::Indented);

    QFile plik("default_config.json");
    plik.write(jsonData);
    plik.close();
}



