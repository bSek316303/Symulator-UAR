#pragma once

class RegulatorPID {
public:
    enum class LiczCalke { Zew, Wew };
private:
    friend class testyPID;
    double m_Kp;
    double m_Ti;
    double m_Td;
    double m_last_P;
    double m_last_I;
    double m_last_D;
    double m_ostatni_sygWy;
    //calkujacy
    double m_epsilon = 1e-4;
    LiczCalke m_sposob; // do zmiany przy implementacji gui
    double m_wartosci = 0.0;
    //rozniczkujacy
    double m_poprzedniSygWe;
    bool ZeroweTi();
    bool ZeroweTi(double Ti);
public:
    RegulatorPID(double Kp, double Ti = 0.0, double Td = 0.0, LiczCalke sposob = RegulatorPID::LiczCalke::Zew);
    void set_kp(double noweKp);
    void set_td(double noweTd);
    void set_ti(double noweTi);

    void resetujPamiecCalki();
    void resetujPamiecRozniczki();

    void setLiczCalke(LiczCalke LiczCalk);
    double symuluj(double sygWe);

    double getKp() const;
    double getTi() const;
    double getTd() const;
    double get_ostatni_P();
    double get_ostatni_I();
    double get_ostatni_D();
    double get_ostatni_sygWy();
};
