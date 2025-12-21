#ifndef ARXCONFIG_H
#define ARXCONFIG_H
#include "Config.h"
#include <vector>

class ARXConfig: public Config
{
private:
    std::vector<double> m_A;
    std::vector<double> m_B;
    void powiadom() override;
public:
    ARXConfig();
    void set_obserwator(obserwator obserwator) override;
};

#endif // ARXCONFIG_H
