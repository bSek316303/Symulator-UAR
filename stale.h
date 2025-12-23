#ifndef STALE_H
#define STALE_H
#include <vector>
#define _USE_MATH_DEFINES
#include <corecrt_math_defines.h>

/*
constexpr double POCZ_KP = 1.0;
constexpr double POCZ_TI = 1.0;
constexpr double POCZ_TD = 1.0;
constexpr int POCZ_LICZ_CALKE = 0;
const std::vector<double> POCZ_A = {1,1,1};
const std::vector<double> POCZ_B = {1,1,1};
constexpr int POCZ_OPOZNIENIE = 1;
constexpr int POCZ_SZUM = 0;

// Generator

constexpr double POCZ_AMP = 1.0;
constexpr double POCZ_S = 1.0;
constexpr double POCZ_P = 1.0;
constexpr int POCZ_SYGNAL = 0;
constexpr double POCZ_OKRES = 1.0;
constexpr int POCZ_TAKTOWANIE = 200;
constexpr double POCZ_ZAKRES_X = 10.0;
*/

// Stabilne dane
constexpr double POCZ_KP = 1.0;
constexpr double POCZ_TI = 0.1;
constexpr double POCZ_TD = 0.05;
constexpr int POCZ_LICZ_CALKE = 0;
const std::vector<double> POCZ_A = {0.7};
const std::vector<double> POCZ_B = {0.2};
constexpr int POCZ_OPOZNIENIE = 1;
constexpr int POCZ_SZUM = 0;

// Generator

constexpr double POCZ_AMP = 5.0;
constexpr double POCZ_S = 1.0;
constexpr double POCZ_P = 1.0;
constexpr int POCZ_SYGNAL = 0;
constexpr double POCZ_OKRES = 1.0;
constexpr int POCZ_TAKTOWANIE = 200;
constexpr double POCZ_ZAKRES_X = 10.0;


#endif // STALE_H
