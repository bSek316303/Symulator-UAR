#include "pidconfig.h"

PIDConfig::PIDConfig() {}

void PIDConfig::powiadom(){
    m_obserwator(*this);
}

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

double PIDConfig::get_kp(){ return m_Kp; }
double PIDConfig::get_ti(){ return m_Ti; }
double PIDConfig::get_td(){ return m_Td; }

void PIDConfig::set_obserwator(obserwator obserwator){
    m_obserwator = std::move(obserwator);
}
