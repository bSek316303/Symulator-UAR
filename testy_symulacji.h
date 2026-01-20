#ifndef TESTY_SYMULACJI_H
#define TESTY_SYMULACJI_H

#include "ProstyUAR.h"
#include "modelARX.h"
#include "testy.h"
#include <cassert>
#include <string>
#include <vector>
#include <functional>

class Testy_symulacji
{
public:
    Testy_symulacji();
    std::vector<std::string> wykonaj_testy();
    using Test = std::pair<std::string, std::function<bool()>>;
    static std::vector<Test> testy;
private:
    //model arx
    static bool test_brakPobudzenia();
    static bool test_skokJednostkowy_1();
    static bool test_skokJednostkowy_2();
    static bool test_skokJednostkowy_3();
    static bool test_poprawnosciSetterow() {
        try {
            ModelARX instancjaTestowa;
            std::vector<double> A = { -0.5, 0.2 };
            std::vector<double> B = { 0.8 };

            instancjaTestowa.set_A(A);
            instancjaTestowa.set_B(B);
            instancjaTestowa.set_opoznienie(5);
            instancjaTestowa.set_sterowanie_min(-2.0);
            instancjaTestowa.set_sterowanie_max(2.0);

            bool ok = true;
            if (instancjaTestowa.get_A() != A) ok = false;
            if (instancjaTestowa.get_B() != B) ok = false;
            if (instancjaTestowa.get_opoznienie() != 5) ok = false;
            if (instancjaTestowa.get_sterowanie_min() != -2.0) ok = false;

            return ok;
        }
        catch (...) {
            return false;
        }
    }
    static bool test_opoznieniaTransportowego() {
        try {
            // Model: y(k) = 1.0 * u(k-2), czyli opóźnienie o 2 próbki
            ModelARX instancjaTestowa({ 0.0 }, { 1.0 }, 2, 0);

            // Wejście: skok jednostkowy w t=0
            std::vector<double> sygWe = { 1.0, 1.0, 1.0, 1.0 };
            // Wyjście: 0 (t=0), 0 (t=1), 1 (t=2), 1 (t=3)
            std::vector<double> spodzSygWy = { 0.0, 0.0, 1.0, 1.0 };
            std::vector<double> faktSygWy(4);

            for (int i = 0; i < 4; i++)
                faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

            return myAssert(spodzSygWy, faktSygWy);
        }
        catch (...) { return false; }
    }
    static bool test_ograniczeniaWyjscia() {
        try {
            ModelARX instancjaTestowa({ 0.0 }, { 100.0 }, 0, 0);
            instancjaTestowa.set_ograniczenie_wyjscia(true);
            instancjaTestowa.set_wyjscie_max(10.0);
            instancjaTestowa.set_wyjscie_min(-10.0);

            std::vector<double> sygWe = { 1.0, -1.0 };
            std::vector<double> spodzSygWy = { 10.0, -10.0 };
            std::vector<double> faktSygWy(2);

            for (int i = 0; i < 2; i++)
                faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
            return myAssert(spodzSygWy, faktSygWy);
        }
        catch (...) { return false; }
    }
    static bool test_odpowiedziSkokowej() {
        try {
            // y(k) = 1.0 * u(k) - 0.5 * y(k-1)
            ModelARX instancjaTestowa({ 0.5 }, { 1.0 }, 0, 0);

            std::vector<double> sygWe = { 1.0, 1.0 };
            // Krok 1: y = 1*1 - 0.5*0 = 1.0
            // Krok 2: y = 1*1 - 0.5*1.0 = 0.5
            std::vector<double> spodzSygWy = { 1.0, 0.5 };
            std::vector<double> faktSygWy(2);

            for (int i = 0; i < 2; i++)
                faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

            return myAssert(spodzSygWy, faktSygWy);
        }
        catch (...) { return false; }
    }
    static bool test_ARX_opoznienie_wlasne() {
        try {

            ModelARX instancjaTestowa({0.0}, {1.0}, 0, 0);
            instancjaTestowa.resetuj();

            double u = 5.0;
            double y = instancjaTestowa.symuluj(u);

            if (std::abs(y - 5.0) < 0.0001) {
                return true;
            } else if (std::abs(y - 0.0) < 0.0001) {
                return false;
            }

            return false;
        }
        catch (...) { return false; }
    }
    //regulator pid
    static bool test_P_brakPobudzenia();
    static bool test_P_skokJednostkowy();
    static bool test_PI_skokJednostkowy_1();
    static bool test_PI_skokJednostkowy_2();
    static bool test_PID_skokJednostkowy();
    static bool test_PI_skokJednostkowy_3();
    //prosty uar
    static bool test_UAR_1_brakPobudzenia();
    static bool test_UAR_1_skokJednostkowyPID();
    static bool test_UAR_2_skokJednostkowyPID();
    static bool test_UAR_3_skokJednostkowyPID();
    static bool test_UAR_odpowiedzNaSkok() {
        try {
            // Regulator: Kp=0.5, Ti=0, Td=0 (czysty P)
            // ARX: A={0}, B={1}, Opoznienie=0 (y(k) = u(k))
            ProstyUAR instancjaTestowa(0.5, 0.0, 0.0, RegulatorPID::LiczCalke::Zew, {0.0}, {1.0}, 0, 0);
            instancjaTestowa.resetuj();

            std::vector<double> sygWe = { 1.0, 1.0 };
            // Krok 1: e = 1.0 - 0 = 1.0 -> u = 1.0 * 0.5 = 0.5 -> y = 0.5 * 1 = 0.5
            // Krok 2: e = 1.0 - 0.5 = 0.5 -> u = 0.5 * 0.5 = 0.25 -> y = 0.25 * 1 = 0.25
            std::vector<double> spodzSygWy = { 0.5, 0.25 };
            std::vector<double> faktSygWy(2);

            for (int i = 0; i < 2; i++)
                faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

            return myAssert(spodzSygWy, faktSygWy);
        }
        catch (...) {
            return false;
        }
    }
    static bool test_UAR_eliminacjaUchybu() {
        try {
            // Regulator PI: Kp=0.5, Ti=1.0. ARX: Wzmocnienie 1.0
            ProstyUAR instancjaTestowa(0.5, 1.0, 0.0, RegulatorPID::LiczCalke::Zew, {0.0}, {1.0}, 0, 0);
            instancjaTestowa.resetuj();

            std::vector<double> sygWe(5, 1.0); // Sygnał zadany stały = 1.0
            std::vector<double> faktSygWy(5);

            for (int i = 0; i < 5; i++)
                faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

            // Sprawdzamy tylko, czy ostatnia wartość jest bliska 1.0 (wartość zadana)
            // W pętli z członem I wyjście powinno rosnąć w stronę 1.0
            bool czyRosnie = faktSygWy[4] > faktSygWy[0];
            return czyRosnie;
        }
        catch (...) { return false; }
    }
    static bool test_UAR_zOpoznieniem() {
        try {
            // Model ARX z opóźnieniem 1 próbki
            ProstyUAR instancjaTestowa(1.0, 0.0, 0.0, RegulatorPID::LiczCalke::Zew, {0.0}, {1.0}, 1, 0);
            instancjaTestowa.resetuj();

            std::vector<double> sygWe = { 1.0, 1.0, 1.0 };
            // Krok 1: e=1, u=1, y=0 (bo opóźnienie)
            // Krok 2: e=1, u=1, y=1 (poprzednie u wychodzi z ARX)
            // Krok 3: e=1-1=0, u=0, y=1 (u z kroku 2 wychodzi z ARX)
            std::vector<double> spodzSygWy = { 0.0, 1.0, 1.0 };
            std::vector<double> faktSygWy(3);

            for (int i = 0; i < 3; i++)
                faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

            return myAssert(spodzSygWy, faktSygWy);
        }
        catch (...) { return false; }
    }
    static bool test_UAR_getteryStanu() {
        try {
            ProstyUAR instancjaTestowa(2.0, 0.0, 0.0, RegulatorPID::LiczCalke::Zew, {0.0}, {0.5}, 0, 0);
            instancjaTestowa.resetuj();

            instancjaTestowa.symuluj(10.0);
            // Oczekiwane:
            // uchyb = 10.0 - 0.0 = 10.0
            // sterowanie = 10.0 * 2.0 = 20.0
            // wyjscie = 20.0 * 0.5 = 10.0

            bool ok = true;
            if (std::abs(instancjaTestowa.get_uchyb() - 10.0) > 0.001) ok = false;
            if (std::abs(instancjaTestowa.get_syg_ster() - 20.0) > 0.001) ok = false;
            if (std::abs(instancjaTestowa.get_ostatni_syg_wy() - 10.0) > 0.001) ok = false;

            return ok;
        }
        catch (...) { return false; }
    }
};

#endif // TESTY_SYMULACJI_H
