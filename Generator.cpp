#include "Generator.h"
Generator::Generator(double okres, double A, double S, double P, Generator::Sygnaly sygnal)
    : m_S(S), m_sygnal(sygnal), m_okres(okres)
{
    setWypelnienie(P);
    setAmplituda(A);
}
void Generator::setAmplituda(double nowaAmplituda) {
    m_A = nowaAmplituda;
    if (m_A < 0.0) m_A = 0.0;
}
void Generator::setWypelnienie(double noweWypelnienie) {
    m_P = noweWypelnienie;
    if (m_P > 1.0)
        m_P = 1.0;
    else if (m_P < 0.0)
        m_P = 0.0;
}
void Generator::setSygnal(Generator::Sygnaly nowySygnal){ m_sygnal = nowySygnal; }
void Generator::setStalaSkladowa(double nowaStala){ m_S = nowaStala; }
void Generator::setOkres(double okres){ m_okres = okres; }
double Generator::get_okres() const{ return m_okres; }

double Generator::generuj(int T) {
    int okres_dyskretny = static_cast<int>(m_okres / (T / 1000.0));
    double sygWy;
    if (m_sygnal == Sygnaly::sinusoidalny) {
        sygWy = m_A * std::sin((i++ % okres_dyskretny) * 2.0 * M_PI / okres_dyskretny) + m_S;
    }
    else if (m_sygnal == Sygnaly::prostokatny) {
        if (i++ % okres_dyskretny < m_P * okres_dyskretny) sygWy  = m_A + m_S;
        else sygWy = m_S;
    }
    else throw std::invalid_argument("podano nieprawidlowy rodzaj sygnalu!");
    if (i == 5*okres_dyskretny) i = 0; // Zabezpieczenie przed przepełnieniem i
    return sygWy;
}
