#pragma once
#include "regulatorPID.h"
#include "modelARX.h"

class ProstyUAR {
    double m_ostatniSygWy;
    RegulatorPID m_regulator;
    ModelARX m_ARX;
public:
    ProstyUAR(double Kp, double Ti, double Td, RegulatorPID::LiczCalke sposob,
              const std::vector<double>& A_p, const std::vector<double>& B_p, int opoznienie_p, double szum_p);
    ProstyUAR(ModelARX arx, RegulatorPID regulator);
    double symuluj(double sygWe);
    RegulatorPID& get_regulator();
    ModelARX& get_ARX();
    double get_ostatni_syg_wy();
    void resetuj();
};
