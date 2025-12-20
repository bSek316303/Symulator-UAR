#pragma once
#include "ProstyUAR.h"
#include "Generator.h"
#include "pidconfig.h"
#include <QTimer>

class menedzer: public QObject {
    Q_OBJECT
public:
    enum class wykresy {
        wykres_uar,
        wykres_uchybu,
        wykres_sterowania,
        wykres_skladowych_pid
    };
private:
    ProstyUAR m_uar;
    Generator m_gen;
    QTimer* stoper;
    void aktualizuj_wykres_uar(double gen, double uar){

    }
    void aktualizuj_wykres_uchyb(double uchyb){

    }
    void aktualizuj_wykres_ster(double ster){

    }
    void aktualizuj_wykres_pid(double p, double i, double d){

    }
    void set_parametry_pid(PIDConfig& cfg){
        m_uar.get_regulator().set_kp(cfg.get_kp());
        m_uar.get_regulator().set_ti(cfg.get_ti());
        m_uar.get_regulator().set_td(cfg.get_td());
    }

    void set_parametry_arx(){

    }

    void set_parametry_generator(){

    }
public:

    explicit menedzer(ProstyUAR uar, Generator gen, PIDConfig& cfg)
        : m_uar(uar), m_gen(gen)
    {
        stoper = new QTimer(this);
        connect(stoper, &QTimer::timeout, this, &menedzer::krok_wykresu);
        cfg.set_obserwator(std::bind(&menedzer::set_parametry_pid, this, std::placeholders::_1));
    }

    void krok_wykresu(){
        double sygSter = m_gen.generuj(stoper->interval());
        double sygWy = m_uar.symuluj(sygSter);
        RegulatorPID reg = m_uar.get_regulator();
        aktualizuj_wykres_uar(sygSter, sygWy);
        aktualizuj_wykres_uchyb(sygSter- m_uar.get_ostatni_syg_wy());
        aktualizuj_wykres_ster(reg.get_ostatni_sygWy());
        aktualizuj_wykres_pid(reg.get_ostatni_P(), reg.get_ostatni_I(),reg.get_ostatni_D());
    }
    void set_interwal(int time_in_ms){
        stoper->setInterval(time_in_ms);
    }
    void zacznij_symulacje(){

    }
    void zakoncz_symulacje(){

    }
};

