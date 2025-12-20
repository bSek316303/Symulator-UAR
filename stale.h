#ifndef STALE_H
#define STALE_H
#include "regulatorPID.h" // do zmiany, wrzucic enumy do enums czy cos
#include "Generator.h"
#include <vector>

constexpr double POCZ_KP = 1.0;
constexpr double POCZ_TI = 1.0;
constexpr double POCZ_TD = 1.0;
constexpr RegulatorPID::LiczCalke POCZ_LICZ_CALKE = RegulatorPID::LiczCalke::Zew;
const std::vector<double> POCZ_A = {1,1,1};
const std::vector<double> POCZ_B = {1,1,1};
constexpr int POCZ_OPOZNIENIE = 1;
constexpr int POCZ_SZUM = 0;

// Generator

constexpr double POCZ_AMP = 1.0;
constexpr double POCZ_S = 1.0;
constexpr double POCZ_P = 1.0;
constexpr Generator::Sygnaly POCZ_SYGNAL = Generator::Sygnaly::prostokatny;


#endif // STALE_H
