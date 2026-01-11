#include "ProstyUAR.h"

ProstyUAR::ProstyUAR(double Kp, double Ti, double Td, RegulatorPID::LiczCalke sposob, const std::vector<double>& A_p, const std::vector<double>& B_p, int opoznienie_p, double szum_p)
    : m_ostatniSygWy(0.0), m_regulator(Kp, Ti, Td, sposob), m_ARX(A_p, B_p, opoznienie_p, szum_p)
{}
ProstyUAR::ProstyUAR(ModelARX arx, RegulatorPID regulator)
    : m_regulator(std::move(regulator)), m_ARX(std::move(arx))
{}
double ProstyUAR::symuluj(double sygWe) {
    double uchyb = sygWe - m_ostatniSygWy;
    double sygSter = m_regulator.symuluj(uchyb);
    double sygWy = m_ARX.symuluj(sygSter);
    m_ostatniSygWy = sygWy;
    return sygWy;
}
RegulatorPID& ProstyUAR::get_regulator() { return m_regulator; }
ModelARX& ProstyUAR::get_ARX() { return m_ARX; }
double ProstyUAR::get_ostatni_syg_wy(){ return m_ostatniSygWy; }

