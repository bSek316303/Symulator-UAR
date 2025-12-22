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
std::vector<double> ARXConfig::get_a() const{
    return m_A;
}
std::vector<double> ARXConfig::get_b() const{
    return m_B;
}
