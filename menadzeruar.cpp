#include "menadzeruar.h"
std::vector<double> default_A = {1.0, -0.5}; // Przykładowe współczynniki A
std::vector<double> default_B = {0.0, 0.6}; // Przykładowe współczynniki B
constexpr double DEFAULT_KP = 1.0;
constexpr double DEFAULT_TI = 0.5;
constexpr double DEFAULT_TD = 0.0;
constexpr int DEFAULT_DELAY = 1;
constexpr double DEFAULT_NOISE = 0.0;
MenadzerUAR::MenadzerUAR()
    : prostyUar(

          DEFAULT_KP,
          DEFAULT_TI,
          DEFAULT_TD,
          default_A,
          default_B,
          DEFAULT_DELAY,
          DEFAULT_NOISE
          ),
    oblsugaPliku()
{
}
void MenadzerUAR::zapisz_konfiguracje()
{
    const ProstyUAR& uar = this->prostyUar;
    const ModelARX& arx = uar.get_ARX();
    const RegulatorPID& pid = uar.get_regulator();

    this->oblsugaPliku.zapiszKonfiguracje(uar, arx, pid);
}

