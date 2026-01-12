#pragma once
#include "ProstyUAR.h"
#include "Generator.h"
#include "config.h"
#include "pidconfig.h"
#include "arxconfig.h"
#include "genconfig.h"
#include "testy_setterow.h"


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
    friend class Testy_setterow;
private:
    ProstyUAR m_uar;
    Generator m_gen;
    void set_parametry_pid(Config& cfg);
    void set_parametry_arx(Config& cfg);
    void set_parametry_generator(Config& cfg);
public:
    explicit menedzer(ProstyUAR uar, Generator gen, PIDConfig* pid_cfg, ARXConfig* arx_cfg, GENConfig* gen_cfg);
    void resetuj_pamiec_calki();
    void resetuj_pamiec_rozniczki();
    dane_do_wykresow krok_wykresu(double interwal);
    void resetuj();
};

