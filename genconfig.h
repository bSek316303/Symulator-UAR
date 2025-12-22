#ifndef GENCONFIG_H
#define GENCONFIG_H
#include "Config.h"

class GENConfig: public Config
{
private:
    double m_A;
    double m_S;
    double m_P;
    int m_sygnal;
    double m_okres;
public:
    GENConfig();
    void set_a(double a);
    void set_s(double s);
    void set_p(double p);
    void set_okres(double okres);
    void set_syg(int value);
    double get_a() const;
    double get_s() const;
    double get_p() const;
    double get_okres() const;
    int get_syg() const;

};

#endif // GENCONFIG_H
