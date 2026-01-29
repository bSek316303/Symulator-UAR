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
    double i = 0;
public:
    Generator(double okres, double A, double S, double P = 0.0, Generator::Sygnaly sygnal = Generator::Sygnaly::prostokatny);
    void set_amplituda(double nowaAmplituda);
    void set_wypelnienie(double noweWypelnienie);
    void set_sygnal(Generator::Sygnaly nowySygnal);
    void set_stala_skladowa(double nowaStala);
    void set_okres(double okres);
    double get_okres() const;
    double get_amplituda() const;
    double get_wypelnienie() const;
    int get_sygnal() const;
    double get_stala_skladowa() const;
    double generuj(int T);
    void resetuj();
};
