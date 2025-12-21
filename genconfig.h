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
public:
    GENConfig();
    void set_a(double a);
    void set_s(double s);
    void set_p(double p);
    void set_syg(Generator::Sygnaly sygnal);
    double get_a() const;
    double get_s() const;
    double get_p() const;
    Generator::Sygnaly get_syg() const;

};

#endif // GENCONFIG_H
