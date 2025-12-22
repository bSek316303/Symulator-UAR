#pragma once
#include "regulatorPID.h"
#include "modelARX.h"

class ProstyUAR {
    double m_taktowanie;
    double m_okres;
    double m_ostatniSygWy;
    RegulatorPID m_regulator;
    ModelARX m_ARX;

public:
    ProstyUAR(double Kp, double Ti, double Td, RegulatorPID::LiczCalke sposob, const std::vector<double>& A_p, const std::vector<double>& B_p, int opoznienie_p, double szum_p)
        : m_ostatniSygWy(0.0), m_regulator(Kp, Ti, Td, sposob), m_ARX(A_p, B_p, opoznienie_p, szum_p)
    {
    }
    ProstyUAR(ModelARX arx, RegulatorPID regulator)
        : m_regulator(std::move(regulator)), m_ARX(std::move(arx))
    {
    }
    double symuluj(double sygWe) {
        double uchyb = sygWe - m_ostatniSygWy;
        double sygSter = m_regulator.symuluj(uchyb);
        double sygWy = m_ARX.symuluj(sygSter);
        m_ostatniSygWy = sygWy;
        return sygWy;
    }
    RegulatorPID& get_regulator()
    {
        return m_regulator;
    }

    ModelARX& get_ARX()
    {
        return m_ARX;
    }
    double get_ostatni_syg_wy(){
        return m_ostatniSygWy;
    }
};



