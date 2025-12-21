#ifndef PIDCONFIG_H
#define PIDCONFIG_H
#include "config.h"

class PIDConfig: public Config
{
private:
    double m_Kp;
    double m_Ti;
    double m_Td;
    obserwator m_obserwator;
    void powiadom() override;
public:
    PIDConfig();
    void set_kp(double value);
    void set_ti(double value);
    void set_td(double value);
    double get_kp();
    double get_ti();
    double get_td();
    void set_obserwator(obserwator obserwator) override;
};

#endif // PIDCONFIG_H
