#ifndef UARCONFIG_H
#define UARCONFIG_H
#include <vector>

class UARConfig
{
private:
    // Parametry regulatora PID
    double Kp;
    double Ti;
    double Td;
    // Parametry modelu ARX
    std::vector<double> a;
    std::vector<double> b;
public:
    UARConfig();
};

#endif // UARCONFIG_H
