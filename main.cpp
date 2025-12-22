#include "mainwindow.h"
#include "menedzer.h"
#include "stale.h"

#include <QApplication>

int main (int argc, char *argv[]){
    QApplication a(argc, argv);

    // Abstrakcje
    PIDConfig pidconfig;
    ARXConfig arxconfig;
    GENConfig genconfig;

    ProstyUAR uar(POCZ_KP, POCZ_TI, POCZ_TD, RegulatorPID::LiczCalke(POCZ_LICZ_CALKE), POCZ_A, POCZ_B, POCZ_OPOZNIENIE, POCZ_SZUM);
    Generator gen(POCZ_AMP, POCZ_S, POCZ_P, Generator::Sygnaly(POCZ_SYGNAL));

    MainWindow w;
    menedzer menedzer(uar, gen, w.get_pid(), w.get_arx(), w.get_gen());
    w.set_wartosci_domyslne();
    w.show();
    return a.exec();
}
