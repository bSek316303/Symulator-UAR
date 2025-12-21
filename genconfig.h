#ifndef GENCONFIG_H
#define GENCONFIG_H
#include "Config.h"
#include "Generator.h"

class GENConfig: public Config
{
private:
    double m_A;
    double m_S;
    double m_P;
    Generator::Sygnaly m_sygnal;
    void powiadom() override;
public:
    GENConfig();
    void set_obserwator(obserwator obserwator) override;

};

#endif // GENCONFIG_H
