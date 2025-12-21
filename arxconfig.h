#ifndef ARXCONFIG_H
#define ARXCONFIG_H
#include "Config.h"
#include <vector>

class ARXConfig: public Config
{
private:
    std::vector<double> m_A;
    std::vector<double> m_B;
public:
    ARXConfig();
    void set_a(std::vector<double> a);
    void set_b(std::vector<double> b);
    std::vector<double> get_a() const;
    std::vector<double> get_b() const;
};

#endif // ARXCONFIG_H
