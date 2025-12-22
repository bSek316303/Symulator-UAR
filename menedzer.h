#pragma once
#include "ProstyUAR.h"
#include "Generator.h"
#include "config.h"
#include "pidconfig.h"
#include "arxconfig.h"
#include "genconfig.h"
#include <QTimer>


struct dane_do_wykresow{
    double uar;
    double gen;
    double uchyb;
    double ster;
    double p;
    double i;
    double d;
};

class menedzer {
private:
    ProstyUAR m_uar;
    Generator m_gen;

    // USTAWIANIE PARAMETRÓW.
    void set_parametry_pid(Config& cfg){
        auto* pid = dynamic_cast<PIDConfig*>(&cfg);
        m_uar.get_regulator().set_kp(pid->get_kp());
        m_uar.get_regulator().set_ti(pid->get_ti());
        m_uar.get_regulator().set_td(pid->get_td());
        m_uar.get_regulator().setLiczCalke(RegulatorPID::LiczCalke(pid->get_licz_calke()));
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
        m_gen.setOkres(gen->get_okres());
        m_gen.setSygnal(Generator::Sygnaly(gen->get_syg()));
    }
    // TODO Poprawić wartswę abstrakcji ARXConfig, aby przyjmowała pozostałe parametry
public:

    explicit menedzer(ProstyUAR uar, Generator gen, PIDConfig& pid_cfg, ARXConfig& arx_cfg, GENConfig& gen_cfg)
        : m_uar(uar), m_gen(gen)
    {
        // Ustawienie abstrakcji do wspólpracy z GUI.
        pid_cfg.set_obserwator(std::bind(&menedzer::set_parametry_pid, this, std::placeholders::_1));
        pid_cfg.set_obserwator_calki(std::bind(&menedzer::resetuj_pamiec_calki, this));
        pid_cfg.set_obserwator_rozniczki(std::bind(&menedzer::resetuj_pamiec_rozniczki, this));
        arx_cfg.set_obserwator(std::bind(&menedzer::set_parametry_arx, this, std::placeholders::_1));
        gen_cfg.set_obserwator(std::bind(&menedzer::set_parametry_generator, this, std::placeholders::_1));
    }

    void resetuj_pamiec_calki() { m_uar.get_regulator().resetujPamiecCalki(); }
    void resetuj_pamiec_rozniczki() { m_uar.get_regulator().resetujPamiecRozniczki(); }

    dane_do_wykresow krok_wykresu(double interwal){
        // Symulacja
        double sygSter = m_gen.generuj(interwal);
        double sygWy = m_uar.symuluj(sygSter);
        RegulatorPID& reg = m_uar.get_regulator();

        // Pakowanie danych
        dane_do_wykresow wynik;
        wynik.uar = sygWy;
        wynik.gen = sygSter;
        wynik.uchyb = sygSter - m_uar.get_ostatni_syg_wy();
        wynik.ster = m_uar.get_ostatni_syg_wy();
        wynik.p = reg.get_ostatni_P();
        wynik.i = reg.get_ostatni_I();
        wynik.d = reg.get_ostatni_D();

        return wynik;
    }
};

