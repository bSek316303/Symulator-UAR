#include "menadzeruar.h"
#include "ProstyUAR.h"
std::vector<double> ARX_A_DEFAULT = {1.0, -0.5};
std::vector<double> ARX_B_DEFAULT = {0.0, 0.6};
constexpr double PID_KP_DEFAULT = 1.0;
constexpr int ARX_DELAY_DEFAULT = 1;
constexpr double ARX_NOISE_DEFAULT = 0.0;

MenadzerUAR::MenadzerUAR()
    : prostyUar(
          PID_KP_DEFAULT, 0.0, 0.0,
          ARX_A_DEFAULT, ARX_B_DEFAULT,
          ARX_DELAY_DEFAULT, ARX_NOISE_DEFAULT
          ),
    oblsugaPliku()
{}
void MenadzerUAR::zapisz_konfiguracje()
{
    const ProstyUAR& uar = this->prostyUar;
    const ModelARX& arx = uar.get_ARX();
    const RegulatorPID& pid = uar.get_regulator();

    this->oblsugaPliku.zapiszKonfiguracje(uar, arx, pid);
}

