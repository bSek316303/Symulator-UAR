#pragma once
#include "main.h"
#include "Generator.h"
#include "regulatorPID.h"
#include "ModelARX.h"

class ProstyUAR {
    double m_taktowanie;
    double m_okres;
    double ostatniSygWy;
    RegulatorPID m_regulator;
    ModelARX m_ARX;

public:
    ProstyUAR(double Kp, double Ti, double Td, const std::vector<double>& A_p, const std::vector<double>& B_p, int opoznienie_p, double szum_p)
        : m_regulator(Kp, Ti, Td), m_ARX(A_p, B_p, opoznienie_p, szum_p), ostatniSygWy(0.0)
    {
    }
    ProstyUAR(ModelARX arx, RegulatorPID regulator)
        : m_regulator(std::move(regulator)), m_ARX(std::move(arx))
    {
    }
    double symuluj(double sygWe) {
        double uchyb = sygWe - ostatniSygWy;
        double sygSter = m_regulator.symuluj(uchyb);
        double sygWy = m_ARX.symuluj(sygSter);
        ostatniSygWy = sygWy;
        return sygWy;
    }
    RegulatorPID get_regulator() const
    {
        return m_regulator;
    }
    ModelARX get_ARX() const
    {
        return m_ARX;
    }
    QJsonObject Model_UAR_to_json() const;
    void zapis_do_pliku(const ProstyUAR& uar, const QString& sciezka_do_pliku);
};


