#include "menedzer.h"
#include "qdebug.h"
#include "qglobal.h"

// USTAWIANIE PARAMETRÓW.
void menedzer::set_parametry_pid(Config& cfg){
    try {
        auto* pid = dynamic_cast<PIDConfig*>(&cfg);
        m_uar.get_regulator().set_kp(pid->get_kp());
        m_uar.get_regulator().set_ti(pid->get_ti());
        m_uar.get_regulator().set_td(pid->get_td());
        m_uar.get_regulator().set_licz_calke(RegulatorPID::LiczCalke(pid->get_licz_calke()));
    } catch (const std::bad_cast&) {
        qDebug() << "castowanie na zły typ pliku w set_parametry_pid!";
    }
}

void menedzer::set_parametry_arx(Config& cfg){
    try {
        auto* arx = dynamic_cast<ARXConfig*>(&cfg);
        m_uar.get_ARX().set_A(arx->get_a());
        m_uar.get_ARX().set_B(arx->get_b());
        m_uar.get_ARX().set_opoznienie(arx->get_opoznienie());
        m_uar.get_ARX().set_szum(arx->get_szum());
    } catch (const std::bad_cast&) {
        qDebug() << "castowanie na zły typ pliku w set_parametry_arx!";
    }
}

void menedzer::set_parametry_generator(Config& cfg){
    try {
        auto* gen = dynamic_cast<GENConfig*>(&cfg);
        m_gen.setAmplituda(gen->get_a());
        m_gen.setWypelnienie(gen->get_p());
        m_gen.setStalaSkladowa(gen->get_s());
        m_gen.setOkres(gen->get_okres());
        m_gen.setSygnal(Generator::Sygnaly(gen->get_syg()));
    } catch (const std::bad_cast&) {
        qDebug() << "castowanie na zły typ pliku w set_parametry_generator!";
    }
}

menedzer::menedzer(ProstyUAR uar, Generator gen, PIDConfig* pid_cfg, ARXConfig* arx_cfg, GENConfig* gen_cfg)
    : m_uar(uar), m_gen(gen)
{
    // Ustawienie abstrakcji do wspólpracy z GUI.
    pid_cfg->set_obserwator(std::bind(&menedzer::set_parametry_pid, this, std::placeholders::_1));
    pid_cfg->set_obserwator_calki(std::bind(&menedzer::resetuj_pamiec_calki, this));
    pid_cfg->set_obserwator_rozniczki(std::bind(&menedzer::resetuj_pamiec_rozniczki, this));
    arx_cfg->set_obserwator(std::bind(&menedzer::set_parametry_arx, this, std::placeholders::_1));
    gen_cfg->set_obserwator(std::bind(&menedzer::set_parametry_generator, this, std::placeholders::_1));
}

void menedzer::resetuj_pamiec_calki() { m_uar.get_regulator().resetuj_pamiec_calki(); }
void menedzer::resetuj_pamiec_rozniczki() { m_uar.get_regulator().resetuj_pamiec_rozniczki(); }

dane_do_wykresow menedzer::krok_wykresu(double interwal){
    // Symulacja
    double wart_zad = m_gen.generuj(interwal);
    double syg_wy = m_uar.symuluj(wart_zad);
    RegulatorPID& reg = m_uar.get_regulator();
    // Pakowanie danych
    dane_do_wykresow dane;
    dane.uar = syg_wy;
    dane.gen = wart_zad;
    dane.uchyb = m_uar.get_uchyb();
    dane.ster = m_uar.get_syg_ster();
    dane.p = reg.get_ostatni_P();
    dane.i = reg.get_ostatni_I();
    dane.d = reg.get_ostatni_D();
    return dane;
}

void menedzer::resetuj(){
    m_uar.resetuj();
    m_gen.resetuj();
}
