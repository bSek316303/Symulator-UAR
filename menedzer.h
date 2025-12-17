#pragma once
#include "ProstyUAR.h"
#include "Generator.h"
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
    Generator::Sygnaly m_rodzajSygnalu;
    QTimer* stoper;
    void aktualizuj_wykres_uar(double gen, double uar){

    }
    void aktualizuj_wykres_uchyb(double uchyb){

    }
    void aktualizuj_wykres_ster(double ster){

    }
    void aktualizuj_wykres_pid(double p, double i, double d){

    }
public:

    explicit menedzer(ProstyUAR uar, Generator gen)
        : m_uar(uar), m_gen(gen)
    {
        stoper = new QTimer(this);
        connect(stoper, &QTimer::timeout, this, &menedzer::krok_wykresu);
    }

    void krok_wykresu(){
        double sygSter = m_gen.generuj(stoper->interval(), m_rodzajSygnalu);
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
    void set_pid_params(double Kp, double Ti, double Td){
        m_uar.
    }
};

