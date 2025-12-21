#pragma once
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <cmath>
#include <corecrt_math_defines.h>

class Generator {
public:
    enum class Sygnaly {
        sinusoidalny,
        prostokatny
    };
    double m_A;
    double m_S;
    double m_P;
    Generator::Sygnaly m_sygnal;
    int i = 0;
public:
    Generator(double A, double S, double P = 0.0, Generator::Sygnaly sygnal = Generator::Sygnaly::prostokatny)
        : m_S(S), m_sygnal(sygnal)
    {
        setWypelnienie(P);
        setAmplituda(A);
    }
    void setAmplituda(double nowaAmplituda) {
        m_A = nowaAmplituda;
        if (m_A < 0.0) m_A = 0.0;
    }
    void setWypelnienie(double noweWypelnienie) {
        m_P = noweWypelnienie;
        if (m_P > 1.0)
            m_P = 1.0;
        else if (m_P < 0.0)
            m_P = 0.0;
    }
    void setSygnal(Generator::Sygnaly nowySygnal){
        m_sygnal = nowySygnal;
    }
    void setStalaSkladowa(double nowaStala){
        m_S = nowaStala;
    }
    double generuj(int T) {
        double sygWy;
        if (m_sygnal == Sygnaly::sinusoidalny) {
            sygWy = m_A * std::sin((i % T) * 2.0 * M_PI / T) + m_S;
            // uwaga, w przypadku potrzeby szybszego liczenia sinusa lub większej dokładności zmienić biblioteke z funkcją sin
        }
        else if (m_sygnal == Sygnaly::prostokatny) {
            if (i++ % T < m_P * T) sygWy  = m_A + m_S;
            else sygWy = m_S;
        }
        else throw std::invalid_argument("podano nieprawidlowy rodzaj sygnalu!");
        return sygWy;
    }
};
