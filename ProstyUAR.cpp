#include "ProstyUAR.h"

ProstyUAR::ProstyUAR(double Kp, double Ti, double Td, RegulatorPID::LiczCalke sposob, const std::vector<double>& A_p, const std::vector<double>& B_p, int opoznienie_p, double szum_p)
    : m_ostatni_syg_wy(0.0), m_regulator(Kp, Ti, Td, sposob), m_arx(A_p, B_p, opoznienie_p, szum_p)
{}
ProstyUAR::ProstyUAR(ModelARX& arx, RegulatorPID& regulator)
    : m_regulator(regulator), m_arx(arx)
{}
double ProstyUAR::symuluj(double syg_we) {
    m_uchyb = syg_we - m_ostatni_syg_wy;
    m_syg_ster = m_regulator.symuluj(m_uchyb);
    double syg_wy = m_arx.symuluj(m_syg_ster);
    m_ostatni_syg_wy = syg_wy;
    return syg_wy;
}
RegulatorPID& ProstyUAR::get_regulator() { return m_regulator; }
ModelARX& ProstyUAR::get_ARX() { return m_arx; }
double ProstyUAR::get_ostatni_syg_wy(){ return m_ostatni_syg_wy; }
double ProstyUAR::get_uchyb(){ return m_uchyb; }
double ProstyUAR::get_syg_ster() { return m_syg_ster; }

void ProstyUAR::resetuj(){
    m_arx.resetuj();
    m_regulator.resetuj();
    m_ostatni_syg_wy = 0.0;
}
