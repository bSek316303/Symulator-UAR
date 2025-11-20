#include "menadzeruar.h"
#include "ProstyUAR.h"

MenadzerUAR::MenadzerUAR()
    : prostyUar(1.0, 0.0, 0.0, {1.0, -0.5}, {0.0, 0.6}, 1, 0.0),
    oblsugaPliku()
{}
void MenadzerUAR::zapisz_konfiguracje()
{
    ProstyUAR& uar = this->prostyUar;
    ModelARX& arx = uar.get_ARX();
    RegulatorPID& pid = uar.get_regulator();

    this->oblsugaPliku.zapiszKonfiguracje(uar, arx, pid);
}

