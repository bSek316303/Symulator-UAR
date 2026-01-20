#pragma once
#include "regulatorPID.h"
#include "modelARX.h"
#include <cassert>

class ProstyUAR {
    double m_ostatni_syg_wy;
    RegulatorPID m_regulator;
    ModelARX m_arx;
    double m_uchyb;
    double m_syg_ster;
public:
    ProstyUAR(double Kp, double Ti, double Td, RegulatorPID::LiczCalke sposob,
              const std::vector<double>& A_p, const std::vector<double>& B_p, int opoznienie_p, double szum_p);
    ProstyUAR(ModelARX arx, RegulatorPID regulator);
    double symuluj(double sygWe);
    RegulatorPID& get_regulator();
    ModelARX& get_ARX();
    double get_ostatni_syg_wy();
    double get_uchyb();
    double get_syg_ster();
    void resetuj();

    // PID
    void set_parametry_pid(double kp, double ti, double td){
        m_regulator.set_kp(kp);
        m_regulator.set_ti(ti);
        m_regulator.set_td(td);
    }
    void set_licz_calke(RegulatorPID::LiczCalke mode) { m_regulator.set_licz_calke(mode); }
    void resetuj_pamiec_calki(){ m_regulator.resetuj_pamiec_calki(); }
    void resetuj_pamiec_rozniczki(){ m_regulator.resetuj_pamiec_rozniczki(); }

    //ARX
    void set_parametry_arx(const std::vector<double>& A, const std::vector<double>& B)
    {

        m_arx.set_A(A);
        m_arx.set_B(B);
    }
    void set_opoznienie(double opoznienie){ m_arx.set_opoznienie(opoznienie); }
    void set_szum(double szum){ m_arx.set_szum(szum); }
    void set_ograniczenie_ster(bool wlaczone) {m_arx.set_ograniczenie_sterowania(wlaczone);}
    void set_ograniczenie_wyj(bool wlaczone) {m_arx.set_ograniczenie_wyjscia(wlaczone);}
};
