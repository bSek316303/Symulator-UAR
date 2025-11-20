#include "modelARX.h"

double ModelARX::sprawdzanie_ograniczenia_sterowania(double u) const {
    if (!ograniczenie_sterowania)
        return u;
    if (u > sterowanie_max)
        return sterowanie_max;
    if (u < sterowanie_min)
        return sterowanie_min;
    return u;
}
double ModelARX::sprawdzanie_ograniczenia_wyjscia(double y) const {
    if (!ograniczenie_wyjscia) return y;
    if (y > wyjscie_max) return wyjscie_max;
    if (y < wyjscie_min) return wyjscie_min;
    return y;
}

ModelARX::ModelARX(const std::vector<double>& A_p, const std::vector<double>& B_p, int opoznienie_p, double szum_p)
    :A(A_p), B(B_p), opoznienie(opoznienie_p), szum(szum_p)
{
    if (A.empty() || B.empty())
    {
        throw std::invalid_argument("Wielomiany nie moga byc puste");
    }
    if (opoznienie < 1)
    {
        throw std::invalid_argument("Opoznienie wieksze od 1");
    }
    if (A.size() != B.size())
    {
        throw std::invalid_argument("Wielomiany musza byc tego samego stopnia");
    }
    bufor_sterujacy.assign(opoznienie + B.size(), 0.0);
    bufor_wyjsciowy.assign(A.size(), 0.0);
    if (szum > 0.0)
    {
        czy_wlaczony_szum = true;
    }
}
void ModelARX::set_ograniczenie_sterowania(bool czy_wlaczone, double sterowanie_min_p, double sterowanie_max_p)
{
    this->ograniczenie_sterowania = czy_wlaczone;
    this->sterowanie_min = sterowanie_min_p;
    this->sterowanie_max = sterowanie_max_p;
}
void ModelARX::set_ograniczenie_wyjscia(bool czy_wlaczone, double wyjscie_min_p, double wyjscie_max_p)
{
    this->ograniczenie_wyjscia = czy_wlaczone;
    this->wyjscie_min = wyjscie_min_p;
    this->wyjscie_max = wyjscie_max_p;
}
void ModelARX::set_wyjscie_max(double wyjscie_max_p)
{
    this->wyjscie_max = wyjscie_max_p;
}
void ModelARX::set_A(const std::vector<double>& A_p)
{
    this->A = A_p;
}
void ModelARX::set_B(const std::vector<double>& B_p)
{
    this->B = B_p;
}
void ModelARX::set_sterowanie_min(double sterowanie_min_p)
{
    this->sterowanie_min = sterowanie_min_p;
}
double ModelARX::symuluj(double nowe_sterowanie)
{
    nowe_sterowanie = sprawdzanie_ograniczenia_sterowania(nowe_sterowanie);
    bufor_sterujacy.push_front(nowe_sterowanie);
    if (bufor_sterujacy.size() > B.size() + opoznienie)
    {
        bufor_sterujacy.pop_back();
    }

    double y = 0.0;
    for (int i = 0; i < A.size(); i++)
    {
        y -= A[i] * bufor_wyjsciowy[i];
        y += B[i] * bufor_sterujacy[i + opoznienie];
    }
    if (czy_wlaczony_szum)
    {
        y += szum;
    }
    y = sprawdzanie_ograniczenia_wyjscia(y);
    bufor_wyjsciowy.push_front(y);
    if (bufor_wyjsciowy.size() > A.size())
    {
        bufor_wyjsciowy.pop_back();
    }
    return y;
}


std::vector<double> ModelARX::get_A() const
{
    return this->A;
}
std::vector<double> ModelARX::get_B() const
{
    return this->B;
}
double ModelARX::get_sterowanie_min() const
{
    return sterowanie_min;
}
double ModelARX::get_sterowanie_max() const
{
    return sterowanie_max;
}
double ModelARX::get_wyjscie_max() const
{
    return wyjscie_max;
}
double ModelARX::get_wyjscie_min() const
{
    return wyjscie_min;
}
bool ModelARX::get_ograniczenie_sterowania() const
{
    return ograniczenie_sterowania;
}
bool ModelARX::get_ograniczenie_wyjscia() const
{
    return ograniczenie_sterowania;
}
double ModelARX::get_szum() const
{
    return szum;
}
bool ModelARX::get_czy_wlaczony_szum() const
{
    return czy_wlaczony_szum;
}
int ModelARX::get_opoznienie() const
{
    return opoznienie;
}

