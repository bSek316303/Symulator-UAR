#include "menadzeruar.h"

MenadzerUAR::MenadzerUAR()
    : prostyUar(), oblsugaPliku()
{}
void MenadzerUAR::zapisz_konfiguracje()
{
    const ProstyUAR& uar = this->prostyUar;
    const ModelARX& arx = uar.get_ARX();
    const RegulatorPID& pid = uar.get_regulator();

    this->oblsugaPliku.zapiszKonfiguracje(uar, arx, pid);
}

