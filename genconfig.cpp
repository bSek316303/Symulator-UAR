#include "genconfig.h"

GENConfig::GENConfig()
    : m_A(POCZ_AMP), m_S(POCZ_S), m_P(POCZ_P), m_sygnal(POCZ_SYGNAL)
{}

void GENConfig::set_a(double a){
    m_A = a;
}
void GENConfig::set_s(double s){
    m_S = s;
}
void GENConfig::set_p(double p){
    m_P = p;
}
void GENConfig::set_syg(int value){
    m_sygnal = value;
}
double GENConfig::get_a() const {
    return m_A;
}
double GENConfig::get_s() const {
    return m_S;
}
double GENConfig::get_p() const {
    return m_P;
}
int GENConfig::get_syg() const {
    return m_sygnal;
}

