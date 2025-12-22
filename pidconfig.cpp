#include "pidconfig.h"

PIDConfig::PIDConfig()
    : m_Kp(POCZ_KP), m_Ti(POCZ_TI), m_Td(POCZ_TD), m_sposob(POCZ_LICZ_CALKE)
{}
void PIDConfig::set_obserwator_calki(obserwator_pamieci obserwator){ m_obserwator_calki = obserwator; }
void PIDConfig::set_obserwator_rozniczki(obserwator_pamieci obserwator){ m_obserwator_rozniczki = obserwator; }
void PIDConfig::powiadom_o_resecie_pamieci_calki(){ m_obserwator_calki(); }
void PIDConfig::powiadom_o_resecie_pamieci_rozniczki() { m_obserwator_rozniczki(); }

void PIDConfig::set_kp(double value){
    m_Kp = value;
    powiadom();
}
void PIDConfig::set_td(double value){
    m_Td = value;
    powiadom();
}
void PIDConfig::set_ti(double value){
    m_Ti = value;
    powiadom();
}
void PIDConfig::set_licz_calke(int value){
    m_sposob = value;
    powiadom();
}


double PIDConfig::get_kp(){ return m_Kp; }
double PIDConfig::get_ti(){ return m_Ti; }
double PIDConfig::get_td(){ return m_Td; }
int PIDConfig::get_licz_calke() const { return m_sposob; }
