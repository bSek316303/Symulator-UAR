#include "Generator.h"
#include "qdebug.h"
#include "qglobal.h"
Generator::Generator(double okres, double A, double S, double P, Generator::Sygnaly sygnal)
    : m_S(S), m_sygnal(sygnal), m_okres(okres)
{
    set_wypelnienie(P);
    set_amplituda(A);
}
void Generator::set_amplituda(double nowaAmplituda) {
    m_A = nowaAmplituda;
    if (m_A < 0.0) m_A = 0.0;
}
void Generator::set_wypelnienie(double noweWypelnienie) {
    m_P = noweWypelnienie;
    if (m_P > 1.0)
        m_P = 1.0;
    else if (m_P < 0.0)
        m_P = 0.0;
}
void Generator::set_sygnal(Generator::Sygnaly nowySygnal){ m_sygnal = nowySygnal; }
void Generator::set_stala_skladowa(double nowaStala){ m_S = nowaStala; }
void Generator::set_okres(double okres){ m_okres = okres; }
double Generator::get_okres() const{ return m_okres; }

double Generator::generuj(int T) {
    double dt = T / 1000.0;
    i += dt;

    double sygWy;

    if (m_sygnal == Sygnaly::sinusoidalny) {
        double omega = 2.0 * M_PI / m_okres;
        sygWy = m_A * std::sin(omega * i) + m_S;
    }
    else if (m_sygnal == Sygnaly::prostokatny) {
        double faza = std::fmod(i, m_okres);
        sygWy = (faza < m_P * m_okres) ? (m_A + m_S) : m_S;
    }
    else {
        throw std::invalid_argument("podano nieprawidlowy rodzaj sygnalu!");
    }

    return sygWy;
}

void Generator::resetuj(){
    i = 0.0;
}
double Generator::get_amplituda() const{
    return m_A;
}

double Generator::get_wypelnienie() const{
    return m_P;
}
int Generator::get_sygnal() const
{
    return (int)m_sygnal;
}

double Generator::get_stala_skladowa() const
{
    return m_S;
};
