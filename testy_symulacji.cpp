#include "testy_symulacji.h"
#include "ProstyUAR.h"
#include "testy.h"
#include <iostream>

Testy_symulacji::Testy_symulacji() {}

std::vector<Testy_symulacji::Test> Testy_symulacji::testy = {
    // model ARX
     {"brak pobudzenia", Testy_symulacji::test_brakPobudzenia},
     {"skok jednostkowy 1", Testy_symulacji::test_skokJednostkowy_1},
     {"skok jednostkowy 2", Testy_symulacji::test_skokJednostkowy_2},
     {"skok jednostkowy 3", Testy_symulacji::test_skokJednostkowy_3},
     {"test poprawnosci seterow", Testy_symulacji::test_poprawnosciSetterow},
     {"test opozneinia", Testy_symulacji::test_opoznieniaTransportowego},
     {"test ograniczenia wyjscia", Testy_symulacji::test_ograniczeniaWyjscia},
     {"test odpowiedzi skokowej", Testy_symulacji::test_odpowiedziSkokowej},
    {"test opoznienie wlasne", Testy_symulacji::test_ARX_opoznienie_wlasne},

     // regulator PID
     {"P brak pobudzenia", Testy_symulacji::test_P_brakPobudzenia},
     {"P skok jednostkowy", Testy_symulacji::test_P_skokJednostkowy},
     {"PI skok 1", Testy_symulacji::test_PI_skokJednostkowy_1},
     {"PI skok 2", Testy_symulacji::test_PI_skokJednostkowy_2},
     {"PID skok", Testy_symulacji::test_PID_skokJednostkowy},
     {"PI skok 3", Testy_symulacji::test_PI_skokJednostkowy_3},

    //UAR
    //{"UAR1 brak", Testy_symulacji::test_UAR_1_brakPobudzenia},
    //{"UAR1 PID", Testy_symulacji::test_UAR_1_skokJednostkowyPID},
    //{"UAR2 PID", Testy_symulacji::test_UAR_2_skokJednostkowyPID},
    //{"UAR3 PID", Testy_symulacji::test_UAR_3_skokJednostkowyPID},
    {"test  odpowiedzi na skok", Testy_symulacji::test_UAR_odpowiedzNaSkok},
    {"test  eliminacja uchybu", Testy_symulacji::test_UAR_eliminacjaUchybu},
    {"test  z opoznieniem", Testy_symulacji::test_UAR_zOpoznieniem},
    {"test  getery stanu", Testy_symulacji::test_UAR_getteryStanu}
};

std::vector<std::string> Testy_symulacji::wykonaj_testy() {
    std::vector<std::string> testy_fail;
    testy_fail.reserve(testy.size());
    for(auto &test: testy) if(!test.second()) testy_fail.push_back(test.first);
    return testy_fail;
}

bool Testy_symulacji::test_brakPobudzenia() {
    try {
        ModelARX instancjaTestowa({ -0.4 }, { 0.6 }, 1, 0);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_skokJednostkowy_1() {
    try {
        ModelARX instancjaTestowa({ -0.4 }, { 0.6 }, 1, 0);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0, 0.6, 0.84, 0.936, 0.9744, 0.98976, 0.995904, 0.998362,
                      0.999345, 0.999738, 0.999895, 0.999958, 0.999983, 0.999993, 0.999997, 0.999999,
                      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_skokJednostkowy_2() {
    try {
        ModelARX instancjaTestowa({ -0.4 }, { 0.6 }, 2, 0);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu,
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0, 0, 0.6, 0.84, 0.936, 0.9744, 0.98976, 0.995904, 0.998362, 0.999345, 0.999738, 0.999895, 0.999958, 0.999983, 0.999993, 0.999997, 0.999999, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_skokJednostkowy_3() {
    try {
        ModelARX instancjaTestowa({ -0.4,0.2 }, { 0.6, 0.3 }, 2, 0);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu,
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0, 0, 0.6, 1.14, 1.236, 1.1664, 1.11936, 1.11446, 1.12191, 1.12587, 1.12597, 1.12521, 1.12489, 1.12491, 1.12499, 1.12501, 1.12501, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125, 1.125 };

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_P_brakPobudzenia() {
    try {
        RegulatorPID instancjaTestowa(0.5);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_P_skokJednostkowy() {
    try {
        RegulatorPID instancjaTestowa(0.5);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
                      0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_PI_skokJednostkowy_1() {
    try {
        RegulatorPID instancjaTestowa(0.5, 1.0);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5,
                      13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22.5, 23.5,
                      24.5, 25.5, 26.5, 27.5, 28.5, 29.5 };

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_PI_skokJednostkowy_2() {
    try {
        RegulatorPID instancjaTestowa(0.5, 10.0);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9,
                      2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4 };

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_PID_skokJednostkowy() {
    try {
        RegulatorPID instancjaTestowa(0.5, 10.0, 0.2);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0.8, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1,
                      2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4 };

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_PI_skokJednostkowy_3() {
    try {
        RegulatorPID instancjaTestowa(0.5, 10.0);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.8, 2, 2.2, 2.4,
                      2.6, 2.8, 3, 3.2, 3.4, 3.6, 3.8, 4, 2.35, 2.45, 2.55, 2.65, 2.75, 2.85 };

        for (int i = 0; i < LICZ_ITER; i++)
        {
            if (i == LICZ_ITER * 1 / 5) // przelaczenie na wew. liczenie calki - nie powinno być zauważalane;
                instancjaTestowa.set_licz_calke(RegulatorPID::LiczCalke::Wew);
            if (i == LICZ_ITER * 2 / 5) // zmiana stalej calkowania - powinna byc tylko zmiana nachylenia
                instancjaTestowa.set_ti(5.0);
            if (i == LICZ_ITER * 3 / 5) // przelaczenie na zew. liczenie calki - nie powinno być zauważalane
                instancjaTestowa.set_licz_calke(RegulatorPID::LiczCalke::Zew);
            if (i == LICZ_ITER * 4 / 5) // zmiana stalej calkowania - powinien wsytapic skok wartosci i zmiana nachylenia
                instancjaTestowa.set_ti(10.0);
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
        }
        // Uwaga przy poprawnej implementacji zmiany sposobu liczenia całki, nie powinno dość do sytuacji, gdy
        // zmiana sposobu liczenia powoduje skokową zmianę wartości sterowania. dla liczenia całki zwenetrznie
        // zmiana stalej calkowania powinna powodować skok. dla liczenia wewnętrznego, powinno sie tylko zmienic
        // nachylenie.

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_UAR_1_brakPobudzenia() {
    try {
        RegulatorPID testPID(0.5, 5.0, 0.2);
        ModelARX testARX({ -0.4 }, { 0.6 });
        ProstyUAR instancjaTestowa(testARX, testPID);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_UAR_1_skokJednostkowyPID() {
    try {
        RegulatorPID testPID(0.5, 5.0, 0.2);
        ModelARX testARX({ -0.4 }, { 0.6 });
        ProstyUAR instancjaTestowa(testARX, testPID);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0.0, 0.0, 0.54, 0.756, 0.6708, 0.64008, 0.729, 0.810437, 0.834499,
            0.843338, 0.8664, 0.8936, 0.911886, 0.923312, 0.93404, 0.944929,
            0.954065, 0.961042, 0.966815, 0.971965, 0.97642, 0.980096, 0.983143,
            0.985741, 0.987964, 0.989839, 0.991411, 0.992739, 0.993865, 0.994818
        };

        for (int i = 0; i < LICZ_ITER; i++) {
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
        }

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_UAR_2_skokJednostkowyPID() {
    try {
        RegulatorPID testPID(0.5, 5.0, 0.2);
        ModelARX testARX({ -0.4 }, { 0.6 }, 2);
        ProstyUAR instancjaTestowa(testARX, testPID);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0.0, 0.0, 0.0, 0.54, 0.756, 0.9624, 0.87336, 0.841104, 0.771946, 0.821644,
            0.863453, 0.93272, 0.952656, 0.965421, 0.954525, 0.955787, 0.957472,
            0.969711, 0.978075, 0.985968, 0.987821, 0.989149, 0.989053, 0.990645,
            0.992248, 0.994403, 0.995707, 0.996677, 0.997024, 0.997388
        };

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

bool Testy_symulacji::test_UAR_3_skokJednostkowyPID() {
    try {
        RegulatorPID testPID(1.0, 2.0, 0.2);
        ModelARX testARX({ -0.4 }, { 0.6 }, 1);
        ProstyUAR instancjaTestowa(testARX, testPID);
        constexpr size_t LICZ_ITER = 30;
        std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
        std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
        std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy

        for (int i = 0; i < LICZ_ITER; i++)
            sygWe[i] = !!i;
        spodzSygWy = { 0.0, 0.0, 1.02, 1.608, 1.1028, 0.41736, 0.546648, 1.20605, 1.43047,
            0.999176, 0.615056, 0.799121, 1.21304, 1.26025, 0.939289, 0.748507,
            0.927166, 1.17292, 1.14155, 0.921616, 0.843258, 0.990018, 1.12577,
            1.068, 0.927024, 0.908125, 1.01702, 1.08484, 1.02618, 0.941508
        };

        for (int i = 0; i < LICZ_ITER; i++)
            faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);

        return myAssert(spodzSygWy, faktSygWy);
    }
    catch (...) {
        std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
        return false;
    }
}

