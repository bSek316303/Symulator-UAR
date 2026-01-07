#ifndef PIDCONFIG_H
#define PIDCONFIG_H
#include "config.h"

class PIDConfig: public Config
{
private:
    using obserwator_pamieci = std::function<void()>;
    double m_Kp;
    double m_Ti;
    double m_Td;
    int m_sposob;
    obserwator_pamieci m_obserwator_calki;
    obserwator_pamieci m_obserwator_rozniczki;
public:
    PIDConfig();
    void set_obserwator_calki(obserwator_pamieci obserwator);
    void set_obserwator_rozniczki(obserwator_pamieci obserwator);
    void powiadom_o_resecie_pamieci_calki();
    void powiadom_o_resecie_pamieci_rozniczki();

    void set_kp(double value);
    void set_ti(double value);
    void set_td(double value);
    void set_licz_calke(int value);

    double get_kp();
    double get_ti();
    double get_td();
    int get_licz_calke() const;
};

#endif // PIDCONFIG_H
