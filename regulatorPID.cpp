#include "regulatorPID.h"
#include <cmath>
#include <cstdlib>

bool RegulatorPID::ZeroweTi() { return std::abs(m_Ti) < m_epsilon; }
bool RegulatorPID::ZeroweTi(double Ti) { return std::abs(Ti) < m_epsilon; }

RegulatorPID::RegulatorPID(double Kp, double Ti, double Td, LiczCalke sposob)
    : m_Kp(Kp), m_Ti(Ti), m_Td(Td), m_sposob(sposob), m_poprzedniSygWe(0.0)
{}
void RegulatorPID::set_kp(double noweKp) { m_Kp = noweKp;  }
void RegulatorPID::set_td(double noweTd) { m_Td = noweTd;  }

//Calkujacy
void RegulatorPID::resetujPamiecCalki() { m_wartosci = 0.0; }
void RegulatorPID::resetujPamiecRozniczki() { m_poprzedniSygWe = 0.0; }
void RegulatorPID::set_ti(double noweTi) { m_Ti = noweTi; }
void RegulatorPID::setLiczCalke(LiczCalke noweLiczCalk) {
    // Ustawia czy uchyb jest dzielony w sumie czy wartosc sumy jest dzielona przez uchyb
    if (noweLiczCalk == m_sposob) return;
    if (noweLiczCalk == LiczCalke::Wew) {
        if (!ZeroweTi())
            m_wartosci /= m_Ti; // Zew -> Wew
    }
    else {
        if (!ZeroweTi())
            m_wartosci *= m_Ti; // Wew -> Zew
    }
    m_sposob = noweLiczCalk;
}

double RegulatorPID::symuluj(double sygWe) { // Sposob na testy -> jezeli chcemy przetestowac tylko jedna czesc to pozostale stale ustawiamy na 0.0
    //proporcja
    m_last_P = sygWe * m_Kp;
    //rozniczka
    m_last_D = m_Td * (sygWe - m_poprzedniSygWe);
    m_poprzedniSygWe = sygWe;
    //calka
    if (!ZeroweTi()) {
        if (m_sposob == LiczCalke::Wew) {
            m_wartosci += sygWe / m_Ti;
            m_last_I = m_wartosci;
        }
        else {
            m_wartosci += sygWe;
            m_last_I = m_wartosci / m_Ti;
        }
    }
    return m_last_P + m_last_I + m_last_D;
}
double RegulatorPID::getKp() const { return m_Kp; }
double RegulatorPID::getTi() const { return m_Ti; }
double RegulatorPID::getTd() const { return m_Td; }

double RegulatorPID::get_ostatni_P() { return m_last_P; }
double RegulatorPID::get_ostatni_I() { return m_last_I; }
double RegulatorPID::get_ostatni_D() { return m_last_D; }
double RegulatorPID::get_ostatni_sygWy() {return m_ostatni_sygWy;}

