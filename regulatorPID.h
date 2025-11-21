#pragma once
#include "main.h"
class RegulatorPID {
public:
    enum class LiczCalke {
        Zew,
        Wew
    };
private:
    friend class testyPID;
    double m_Kp;
    double m_Ti;
    double m_Td;
    //calkujacy
    double m_epsilon = 1e-4;
    static LiczCalke LiczCalk; // do zmiany przy implementacji gui
    double m_wartosci = 0.0;
    //rozniczkujacy
    double m_poprzedniSygWe;
    bool ZeroweTi();
    bool ZeroweTi(double Ti);
public:
    RegulatorPID(){};
    RegulatorPID(double Kp);
    RegulatorPID(double Kp, double Ti);
    RegulatorPID(double Kp, double Ti, double Td);
    void setWzmocnienie(double noweKp);
    void setStalaRozn(double noweTd);

    void resetujPamiec();
    void setStalaCalk(double noweTi);
    void setLiczCalke(LiczCalke LiczCalk);
    double symuluj(double sygWe);

    double getKp() const;
    double getTi() const;
    double getTd() const;
};
