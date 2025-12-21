#pragma once
#include "ProstyUAR.h"
#include "Generator.h"
#include "config.h"
#include "pidconfig.h"
#include "arxconfig.h"
#include "genconfig.h"
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

    // AKTUALIZOWANIE WYKRESÓW.
    void aktualizuj_wykres_uar(double gen, double uar){

    }
    void aktualizuj_wykres_uchyb(double uchyb){

    }
    void aktualizuj_wykres_ster(double ster){

    }
    void aktualizuj_wykres_pid(double p, double i, double d){

    }


    // USTAWIANIE PARAMETRÓW.
    void set_parametry_pid(Config& cfg){
        auto* pid = dynamic_cast<PIDConfig*>(&cfg);
        m_uar.get_regulator().set_kp(pid->get_kp());
        m_uar.get_regulator().set_ti(pid->get_ti());
        m_uar.get_regulator().set_td(pid->get_td());
    }

    void set_parametry_arx(Config& cfg){
        auto* arx = dynamic_cast<ARXConfig*>(&cfg);
        m_uar.get_ARX().set_A(arx->get_a());
        m_uar.get_ARX().set_B(arx->get_b());
    }

    void set_parametry_generator(Config& cfg){
        auto* gen = dynamic_cast<GENConfig*>(&cfg);
        m_gen.setAmplituda(gen->get_a());
        m_gen.setWypelnienie(gen->get_p());
        m_gen.setStalaSkladowa(gen->get_s());
        m_gen.setSygnal(gen->get_syg());
    }
    // TODO Poprawić wartswę abstrakcji ARXConfig, aby przyjmowała pozostałe parametry
public:

    explicit menedzer(ProstyUAR uar, Generator gen, PIDConfig& pid_cfg, ARXConfig& arx_cfg, GENConfig& gen_cfg)
        : m_uar(uar), m_gen(gen)
    {
        stoper = new QTimer(this);
        connect(stoper, &QTimer::timeout, this, &menedzer::krok_wykresu);

        // Ustawienie abstrakcji do wspólpracy z GUI.
        pid_cfg.set_obserwator(std::bind(&menedzer::set_parametry_pid, this, std::placeholders::_1));
        arx_cfg.set_obserwator(std::bind(&menedzer::set_parametry_arx, this, std::placeholders::_1));
        gen_cfg.set_obserwator(std::bind(&menedzer::set_parametry_generator, this, std::placeholders::_1));
    }

    void krok_wykresu(){
        double sygSter = m_gen.generuj(stoper->interval());
        double sygWy = m_uar.symuluj(sygSter);
        RegulatorPID& reg = m_uar.get_regulator();
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

