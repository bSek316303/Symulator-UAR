#ifndef PIDCONFIG_H
#define PIDCONFIG_H
#include <functional>

class PIDConfig
{
private:
    using obserwator = std::function<void(PIDConfig&)>;
    double m_Kp;
    double m_Ti;
    double m_Td;
    obserwator m_obserwator;
    void powiadom();
public:
    PIDConfig();
    void set_kp(double value);
    void set_ti(double value);
    void set_td(double value);
    double get_kp();
    double get_ti();
    double get_td();
    void set_obserwator(obserwator obserwator);
};

#endif // PIDCONFIG_H
