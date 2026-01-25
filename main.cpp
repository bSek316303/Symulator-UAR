#include "mainwindow.h"
#include "menedzer.h"
#include "stale.h"
#include "skalowanie_wykresow.h"
#include "testy_symulacji.h"
#include <QApplication>

int main (int argc, char *argv[]){
    QApplication a(argc, argv);

#ifdef TEST
    // --- SEKCJA TESTÓW ---
    std::cout << "Uruchamianie testow jednostkowych..." << std::endl;
    Testy_symulacji tester;
    std::vector<std::string> bledy = tester.wykonaj_testy();

    if (bledy.empty()) {
        std::cout << "SUKCES: Wszystkie testy przeszly poprawnie!" << std::endl;
    } else {
        std::cerr << "PORAZKA: Nastepujace testy nie powiodly sie:" << std::endl;
        for (const std::string& nazwa_testu : bledy) {
            std::cerr << " - " << nazwa_testu << std::endl;
        }
    }
    std::cout << "---------------------------------------" << std::endl;
    // ---------------------

    qRegisterMetaType<std::vector<double>>("std::vector<double>");
#endif
    ProstyUAR uar(POCZ_KP, POCZ_TI, POCZ_TD, RegulatorPID::LiczCalke(POCZ_LICZ_CALKE),
                  POCZ_A, POCZ_B, POCZ_OPOZNIENIE, POCZ_SZUM);
    Generator gen(POCZ_OKRES, POCZ_AMP, POCZ_S, POCZ_P, Generator::Sygnaly(POCZ_SYGNAL));

    menedzer menedzer(uar, gen);
    MainWindow w(&menedzer);
    w.show();

    return a.exec();
}
