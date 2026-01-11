#pragma once
#include <stdexcept>
#include <cmath>
#include "stale.h"

class Generator {
public:
    enum class Sygnaly { sinusoidalny, prostokatny };
    double m_A;
    double m_S;
    double m_P;
    Generator::Sygnaly m_sygnal;
    double m_okres;
    int i = 0;
public:
    Generator(double okres, double A, double S, double P = 0.0, Generator::Sygnaly sygnal = Generator::Sygnaly::prostokatny);
    void setAmplituda(double nowaAmplituda);
    void setWypelnienie(double noweWypelnienie);
    void setSygnal(Generator::Sygnaly nowySygnal);
    void setStalaSkladowa(double nowaStala);
    void setOkres(double okres);
    double get_okres() const;
    double generuj(int T);
    void resetuj();
};
