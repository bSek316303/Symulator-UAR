#include "ProstyUAR.h"

QJsonObject ProstyUAR::Model_UAR_to_json() const
{
    QJsonObject obiekt_UAR;
    obiekt_UAR["Taktowanie"] = m_taktowanie;
    obiekt_UAR["Okres"] = m_okres;
    obiekt_UAR["ARX"] = m_ARX.Model_ARX_to_Json();
    obiekt_UAR["PID"] = m_regulator.Regulator_PID_to_json();

    return obiekt_UAR;
}

void ProstyUAR::zapis_do_pliku(const ProstyUAR& uar, const QString& sciezka_do_pliku)
{
    QFile plik(sciezka_do_pliku);
    if(!plik.open(QIODevice::WriteOnly)) return;

    QJsonObject konwersja = uar.Model_UAR_to_json();
    QJsonDocument doc(konwersja);

    plik.write(doc.toJson(QJsonDocument::Indented));
    plik.close();
}
