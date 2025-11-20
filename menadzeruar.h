#ifndef MENADZERUAR_H
#define MENADZERUAR_H
#include "ProstyUAR.h"
#include "obsluga_pliku.h"

class MenadzerUAR
{
    ProstyUAR prostyUar;
    Obsluga_pliku oblsugaPliku;
public:
    MenadzerUAR();
    void zapisz_konfiguracje();
    void set_parametry_PID(double Kp, double Ti, double Td) {
        prostyUar.get_regulator().ustawKp(Kp);
        prostyUar.get_regulator().setStalaCalk(Ti);
        prostyUar.get_regulator().setStalaRozn(Td);
    }
    void set_pid_tryb(RegulatorPID::LiczCalke mode) {
        prostyUar.get_regulator().setLiczCalke(mode);
    }

    void reset_pamieci_pid() {
        prostyUar.get_regulator().resetujPamiec();
    }

    void set_parametry_ARX(const std::vector<double>& A, const std::vector<double>& B) {
        prostyUar.get_ARX().set_A(A);
        prostyUar.get_ARX().set_B(B);
    }

    void set_ograniczenia_sterowania_ARX(bool wlaczone, double min, double max) {
        prostyUar.get_ARX().set_ograniczenie_sterowania(wlaczone, min, max);
    }
    void set_ograniaczenia_wyjscia_ARX(bool wlaczone, double min, double max) {
        prostyUar.get_ARX().set_ograniczenie_wyjscia(wlaczone, min, max);
    }
    void set_szum(double szum, bool czy_wlaczony) {
        prostyUar.get_ARX().set_szum(szum);           // jeśli masz taką metodę
        prostyUar.get_ARX().set_czy_wlaczony_szum(czy_wlaczony);
    }
};

#endif // MENADZERUAR_H
