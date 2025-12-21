#ifndef PIDCONFIG_H
#define PIDCONFIG_H
#include "config.h"
#include "RegulatorPID.h"

class PIDConfig: public Config
{
private:
    double m_Kp;
    double m_Ti;
    double m_Td;
    RegulatorPID::LiczCalke m_sposob;
public:
    PIDConfig();
    void set_kp(double value);
    void set_ti(double value);
    void set_td(double value);
    void set_licz_calke(RegulatorPID::LiczCalke sposob);
    double get_kp();
    double get_ti();
    double get_td();
    RegulatorPID::LiczCalke get_licz_calke() const;
};

#endif // PIDCONFIG_H
