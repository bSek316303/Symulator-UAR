#include "pidconfig.h"

PIDConfig::PIDConfig() {}

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

void PIDConfig::set_licz_calke(RegulatorPID::LiczCalke sposob){
    m_sposob = sposob;
}

double PIDConfig::get_kp(){ return m_Kp; }
double PIDConfig::get_ti(){ return m_Ti; }
double PIDConfig::get_td(){ return m_Td; }
RegulatorPID::LiczCalke PIDConfig::get_licz_calke() const { return m_sposob; }
