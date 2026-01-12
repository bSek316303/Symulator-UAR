#include "testy_setterow.h"
#include "pidconfig.h"
#include "menedzer.h"


Testy_setterow::Testy_setterow() {}

bool Testy_setterow::test_ustawienia_parametrow_pid(){
    try {
        PIDConfig pidconfig;
        ARXConfig arxconfig;
        GENConfig genconfig;

        ProstyUAR uar(POCZ_KP, POCZ_TI, POCZ_TD, RegulatorPID::LiczCalke(0), POCZ_A, POCZ_B, POCZ_OPOZNIENIE, POCZ_SZUM);
        Generator gen(POCZ_OKRES, POCZ_AMP, POCZ_S, POCZ_P, Generator::Sygnaly(POCZ_SYGNAL));

        menedzer test_menedzer(uar, gen, &pidconfig , &arxconfig, &genconfig);
        pidconfig.set_kp(10.0);
        pidconfig.set_licz_calke(1);
        pidconfig.set_td(15.0);
        pidconfig.set_ti(20.0);
        RegulatorPID test_pid = test_menedzer.m_uar.get_regulator();
        if(test_pid.getKp() == 10.0 && test_pid.getTd() == 15.0 && test_pid.getTi() == 20.0 && test_pid.get_licz_calke() == RegulatorPID::LiczCalke(1)) return true;
        return false;
    } catch(...) {
        std::cerr << "INTERRUPTED!\n";
        return false;
    }
}
bool Testy_setterow::test_resetu_pamieci_roznicznki(){
    try {
        PIDConfig pidconfig;
        ARXConfig arxconfig;
        GENConfig genconfig;

        ProstyUAR uar(1, 1, 1, RegulatorPID::LiczCalke(0), {1}, {1}, 1, 1);
        Generator gen(1, 5, 1, 1, Generator::Sygnaly(1));

        menedzer test_menedzer(uar, gen, &pidconfig , &arxconfig, &genconfig);
        for(int i = 0; i < 3; i++) test_menedzer.krok_wykresu(i);
        test_menedzer.m_uar.get_regulator().resetuj_pamiec_rozniczki();
        if(test_menedzer.m_uar.get_regulator().m_poprzedni_syg_we == 0.0) return true;
        return false;
    } catch(...) {
        std::cerr << "INTERRUPTED!\n";
        return false;
    }
}
bool Testy_setterow::test_resetu_pamieci_calki(){
    try {
        PIDConfig pidconfig;
        ARXConfig arxconfig;
        GENConfig genconfig;

        ProstyUAR uar(1, 1, 1, RegulatorPID::LiczCalke(0), {1}, {1}, 1, 1);
       Generator gen(1, 5, 1, 1, Generator::Sygnaly(1));

        menedzer test_menedzer(uar, gen, &pidconfig , &arxconfig, &genconfig);
        for(int i = 0; i < 3; i++) test_menedzer.krok_wykresu(i);
        test_menedzer.m_uar.get_regulator().resetuj_pamiec_rozniczki();
        if(test_menedzer.m_uar.get_regulator().m_wartosci == 0.0) return true;
        return false;
    } catch(...) {
        std::cerr << "INTERRUPTED!\n";
        return false;
    }
}
