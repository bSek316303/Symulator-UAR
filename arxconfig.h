#ifndef ARXCONFIG_H
#define ARXCONFIG_H
#include "Config.h"
#include <vector>

class ARXConfig: public Config
{
private:
    std::vector<double> m_A;
    std::vector<double> m_B;
    double m_opoznienie;
    double m_zaklocenie;
public:
    ARXConfig();
    void set_a(std::vector<double> a);
    void set_b(std::vector<double> b);
    void set_opoznienie(double opoznienie);
    void set_zaklocenie(double zaklocenie);
    std::vector<double> get_a() const;
    std::vector<double> get_b() const;
};

#endif // ARXCONFIG_H
