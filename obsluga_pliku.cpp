#include "obsluga_pliku.h"

Obsluga_pliku::Obsluga_pliku() {}

QJsonObject ModelARX::Model_ARX_to_Json() const
{
    QJsonObject obiekt_ARX;
    QJsonArray wektor_A;
    QJsonArray wektor_B;

    for(double wartosc: A) wektor_A.append(wartosc);
    for(double wartosc: B) wektor_B.append(wartosc);

    obiekt_ARX["Wektor_A"] = wektor_A;
    obiekt_ARX["Wektor_B"] = wektor_B;
    obiekt_ARX["Czy_wlaczony_szum"] = czy_wlaczony_szum;
    obiekt_ARX["szum"] = szum;
    obiekt_ARX["Opoznienie"] = opoznienie;
    obiekt_ARX["Ograniczenie_sterowania"] = ograniczenie_sterowania;
    obiekt_ARX["Sterowanie_min"] = sterowanie_min;
    obiekt_ARX["Sterowanie_max"] = sterowanie_max;
    obiekt_ARX["Ograniczenie_wyjscia"] = ograniczenie_wyjscia;
    obiekt_ARX["Wyjscie_min"] = wyjscie_min;
    obiekt_ARX["Wyjscie_max"] = wyjscie_max;

    return obiekt_ARX;
}
