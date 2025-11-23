#include "regulatorPID.h"
#include <cmath>
#include <cstdlib>

RegulatorPID::LiczCalke RegulatorPID::LiczCalk = RegulatorPID::LiczCalke::Zew;

bool RegulatorPID::ZeroweTi() {
    return std::abs(m_Ti) < m_epsilon;
}
bool RegulatorPID::ZeroweTi(double Ti) {
    return std::abs(Ti) < m_epsilon;
}

RegulatorPID::RegulatorPID(double Kp)
    : m_Kp(Kp), m_Ti(0.0), m_Td(0.0), m_poprzedniSygWe(0)
{}

RegulatorPID::RegulatorPID(double Kp, double Ti)
    : m_Kp(Kp), m_Ti(Ti), m_Td(0.0), m_poprzedniSygWe(0)
{}

RegulatorPID::RegulatorPID(double Kp, double Ti, double Td)
    : m_Kp(Kp), m_Ti(Ti), m_Td(Td), m_poprzedniSygWe(0)
{}
void RegulatorPID::setWzmocnienie(double noweKp) { m_Kp = noweKp;  }
void RegulatorPID::setStalaRozn(double noweTd) { m_Td = noweTd;  }

//Calkujacy
void RegulatorPID::resetujPamiec() { m_wartosci = 0.0; }
void RegulatorPID::setStalaCalk(double noweTi) { m_Ti = noweTi; }
void RegulatorPID::setLiczCalke(LiczCalke noweLiczCalk) {
    // Ustawia czy uchyb jest dzielony w sumie czy wartosc sumy jest dzielona przez uchyb
    if (noweLiczCalk == LiczCalk) return;
    if (noweLiczCalk == LiczCalke::Wew) {
        if (!ZeroweTi())
            m_wartosci /= m_Ti; // Zew -> Wew
    }
    else {
        if (!ZeroweTi())
            m_wartosci *= m_Ti; // Wew -> Zew
    }
    LiczCalk = noweLiczCalk;
}

double RegulatorPID::symuluj(double sygWe) { // Sposob na testy -> jezeli chcemy przetestowac tylko jedna czesc to pozostale stale ustawiamy na 0.0
    //proporcja
    m_last_P = sygWe * m_Kp;
    //rozniczka
    m_last_D = m_Td * (sygWe - m_poprzedniSygWe);
    m_poprzedniSygWe = sygWe;
    //calka
    if (!ZeroweTi()) {
        if (LiczCalk == LiczCalke::Wew) {
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

double RegulatorPID::getLastP() { return m_last_P; }
double RegulatorPID::getLastI() { return m_last_I; }
double RegulatorPID::getLastD() { return m_last_D; }



