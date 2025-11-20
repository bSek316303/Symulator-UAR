#include "main.h"
#pragma once

class ModelARX {
    std::vector<double> A;
    std::vector<double> B;
    std::deque<double> bufor_sterujacy;
    std::deque<double> bufor_wyjsciowy;

    bool czy_wlaczony_szum = false;
    double szum;
    int opoznienie;

    bool ograniczenie_sterowania = true;
    double sterowanie_min = -10.0;
    double sterowanie_max = 10.0;

    bool ograniczenie_wyjscia = true;
    double wyjscie_min = -10.0;
    double wyjscie_max = 10.0;

    double sprawdzanie_ograniczenia_sterowania(double u) const;
    double sprawdzanie_ograniczenia_wyjscia(double y) const;

public:
    ModelARX(const std::vector<double>& A_p, const std::vector<double>& B_p, int opoznienie_p = 0, double szum_p = 0);
    double symuluj(double nowe_sterowanie);
    void set_ograniczenie_sterowania(bool czy_wlaczone, double sterowanie_min_p, double sterowanie_max_p);
    void set_ograniczenie_wyjscia(bool czy_wlaczone, double wyjscie_min_p, double wyjscie_max_p);
    void set_A(const std::vector<double>& A_p);
    void set_B(const std::vector<double>& B_p);
    void set_sterowanie_min(double sterowanie_min_p);
    void set_wyjscie_max(double wyjscie_max_p);

    double get_wyjscie_max()const;
    double get_wyjscie_min() const;
    bool get_ograniczenie_wyjscia()const;
    bool get_ograniczenie_sterowania()const;
    double get_sterowanie_min()const;
    double get_sterowanie_max()const;
    double get_szum()const;
    bool get_czy_wlaczony_szum()const;
    std::vector<double> get_B()const;
    std::vector<double> get_A()const;
    QJsonObject Model_ARX_to_Json() const;
};
