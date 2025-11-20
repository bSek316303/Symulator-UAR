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
    void setPidParameters(double Kp, double Ti, double Td) {
        // Wymaga, aby prostyUar.get_regulator() zwracało referencję (RegulatorPID&)
        prostyUar.get_regulator().ustawKp(Kp);
        prostyUar.get_regulator().setStalaCalk(Ti);
        prostyUar.get_regulator().setStalaRozn(Td);
    }

    // Ustawia tryb liczenia całki
    void setPidIntegralMode(RegulatorPID::LiczCalke mode) {
        prostyUar.get_regulator().setLiczCalke(mode);
    }

    void resetPidMemory() {
        prostyUar.get_regulator().resetujPamiec();
    }
    void setArxCoefficients(const std::vector<double>& A, const std::vector<double>& B) {
        prostyUar.get_ARX().set_A(A);
        prostyUar.get_ARX().set_B(B);
    }

    // Ustawia stan i wartości ograniczeń sterowania (u)
    void setArxControlLimits(bool wlaczone, double min, double max) {
        prostyUar.get_ARX().set_ograniczenie_sterowania(wlaczone, min, max);
    }

    // Ustawia stan i wartości ograniczeń wyjścia (y)
    void setArxOutputLimits(bool wlaczone, double min, double max) {
        prostyUar.get_ARX().set_ograniczenie_wyjscia(wlaczone, min, max);
    }

    // Ustawia szum
    void setArxNoise(double szum, bool czy_wlaczony) {
        // Zakładam, że masz odpowiednie settery dla szumu w ModelARX
        // prostyUar.get_ARX().set_szum(szum);
        // prostyUar.get_ARX().set_czy_wlaczony_szum(czy_wlaczony);
    }
};

#endif // MENADZERUAR_H
