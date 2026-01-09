#include "arxconfig.h"

ARXConfig::ARXConfig()
    : m_A(POCZ_A), m_B(POCZ_B)
{}

void ARXConfig::set_a(std::vector<double> a){
    m_A = a;
    powiadom();
}
void ARXConfig::set_b(std::vector<double> b){
    m_B = b;
    powiadom();
}
void ARXConfig::set_opoznienie(double opoznienie)
{
    m_opoznienie = opoznienie;
    powiadom();
}
void ARXConfig::set_zaklocenie(double zaklocenie)
{
    m_zaklocenie = zaklocenie;
    powiadom();
}
std::vector<double> ARXConfig::get_a() const{
    return m_A;
}
std::vector<double> ARXConfig::get_b() const{
    return m_B;
}

double ARXConfig::get_opoznienie()
{
    return m_opoznienie;
}

double ARXConfig::get_szum()
{
    return m_zaklocenie;
}
