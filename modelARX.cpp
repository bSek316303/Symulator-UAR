#include "modelARX.h"
#include <random>
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
    :opoznienie(opoznienie_p)
{
    set_A(A_p);
    set_B(B_p);
    set_szum(szum_p);
    bufor_sterujacy.assign(opoznienie + B.size(), 0.0);
    bufor_wyjsciowy.assign(A.size(), 0.0);
    if (szum > 0.0)
    {
        czy_wlaczony_szum = true;
    }
    //idx_ster = 0;
    //idx_wyjscie = 0;
}
void ModelARX::set_ograniczenie_sterowania(bool czy_wlaczone, double sterowanie_min_p, double sterowanie_max_p)
{
    ograniczenie_sterowania = czy_wlaczone;
    sterowanie_min = sterowanie_min_p;
    sterowanie_max = sterowanie_max_p;
}
void ModelARX::set_ograniczenie_wyjscia(bool czy_wlaczone, double wyjscie_min_p, double wyjscie_max_p)
{
    ograniczenie_wyjscia = czy_wlaczone;
    wyjscie_min = wyjscie_min_p;
    wyjscie_max = wyjscie_max_p;
}
void ModelARX::set_wyjscie_max(double wyjscie_max_p)
{
    wyjscie_max = wyjscie_max_p;
}
void ModelARX::set_A(const std::vector<double>& A_p)
{
    A = A_p;
}
void ModelARX::set_B(const std::vector<double>& B_p)
{
    B = B_p;
}
void ModelARX::set_opoznienie(int opoznienie_p)
{
    if(opoznienie_p >= 1)
    {
        opoznienie = opoznienie_p;
    }
    else opoznienie = 1;

}
void ModelARX::set_sterowanie_min(double sterowanie_min_p)
{
    sterowanie_min = sterowanie_min_p;
}

double ModelARX::symuluj(double nowe_sterowanie)
{
    nowe_sterowanie = sprawdzanie_ograniczenia_sterowania(nowe_sterowanie);
    bufor_sterujacy.push_front(nowe_sterowanie);

    size_t wymagany_rozmiar_u = B.size() + opoznienie;
    while (bufor_sterujacy.size() > wymagany_rozmiar_u) {
        bufor_sterujacy.pop_back();
    }
    while (bufor_sterujacy.size() < wymagany_rozmiar_u) {
        bufor_sterujacy.push_back(0.0);
    }
    double suma_B = 0.0;
    for (size_t i = 0; i < B.size(); i++) {
        suma_B += B[i] * bufor_sterujacy[opoznienie + i];
    }

    double suma_A = 0.0;
    for (size_t i = 0; i < A.size(); i++) {
        if (i < bufor_wyjsciowy.size()) {
            suma_A += A[i] * bufor_wyjsciowy[i];
        }
    }

    double yi = suma_B - suma_A;
    if (czy_wlaczony_szum && szum > 0) {
        static std::mt19937 gen(std::random_device{}());
        std::normal_distribution<double> d(0.0, szum);
        yi += d(gen);
    }

    yi = sprawdzanie_ograniczenia_wyjscia(yi);

    bufor_wyjsciowy.push_front(yi);

    while (bufor_wyjsciowy.size() > A.size()) {
        bufor_wyjsciowy.pop_back();
    }
    while (bufor_wyjsciowy.size() < A.size() && A.size() > 0) {
        bufor_wyjsciowy.push_back(0.0);
    }

    return yi;
}
/*
double ModelARX::symuluj(double nowe_sterowanie) //Wersja "zoptymalizowana"
{
    // 1. ograniczenie sterowania
    nowe_sterowanie = sprawdzanie_ograniczenia_sterowania(nowe_sterowanie);

    // 2. zapis sterowania do bufora ring
    bufor_sterujacy[idx_ster] = nowe_sterowanie;
    idx_ster = (idx_ster + 1) % bufor_sterujacy.size();

    // 3. obliczenie wyjścia
    double y = 0.0;
    for (size_t i = 0; i < A.size(); ++i)
    {
        // indeksowanie ring bufferów
        size_t idx_wy = (idx_wyjscie + i) % bufor_wyjsciowy.size();
        y -= A[i] * bufor_wyjsciowy[idx_wy];

        size_t idx_st = (idx_ster + i + opoznienie) % bufor_sterujacy.size();
        y += B[i] * bufor_sterujacy[idx_st];
    }

    if (czy_wlaczony_szum)
        y += szum;

    y = sprawdzanie_ograniczenia_wyjscia(y);

    // 4. zapis wyjścia do bufora ring
    bufor_wyjsciowy[idx_wyjscie] = y;
    idx_wyjscie = (idx_wyjscie + 1) % bufor_wyjsciowy.size();

    return y;
}
*/

std::vector<double> ModelARX::get_A() const
{
    return A;
}
std::vector<double> ModelARX::get_B() const
{
    return B;
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
    return ograniczenie_wyjscia;
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
void ModelARX::resetuj(){
    //TODO
}

