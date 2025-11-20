#ifndef MENADZERUAR_H
#define MENADZERUAR_H
#include "ProstyUAR.h"
#include "obsluga_pliku.h"

class MenadzerUAR
{
    ProstyUAR prostyUar;
    Obsluga_pliku oblsugaPliku;
    QVector<double> Json_to_Wektor(const QJsonArray& dane_json);
public:
    MenadzerUAR();
    void zapisz_konfiguracje();
    void wczytaj_konfiguracje(const QJsonDocument& dane_json);
    void zastosuj_konfiguracje();
    void set_parametry_PID(double Kp, double Ti, double Td);
    void set_pid_tryb(RegulatorPID::LiczCalke mode);
    void reset_pamieci_pid();
    void set_parametry_ARX(const std::vector<double>& A, const std::vector<double>& B);
    void set_ograniczenia_sterowania_ARX(bool wlaczone, double min, double max) ;
    void set_ograniaczenia_wyjscia_ARX(bool wlaczone, double min, double max);
    void set_szum(double szum, bool czy_wlaczony);
    void set_opoznienie_ARX(int opoznienie_p);
};

#endif // MENADZERUAR_H
