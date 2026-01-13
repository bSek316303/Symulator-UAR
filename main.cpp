#include "mainwindow.h"
#include "menedzer.h"
#include "stale.h"
#include "sim_handler.h"
#include <QApplication>

int main (int argc, char *argv[]){
    QApplication a(argc, argv);
    ProstyUAR uar(POCZ_KP, POCZ_TI, POCZ_TD, RegulatorPID::LiczCalke(POCZ_LICZ_CALKE), POCZ_A, POCZ_B, POCZ_OPOZNIENIE, POCZ_SZUM);
    Generator gen(POCZ_OKRES, POCZ_AMP, POCZ_S, POCZ_P, Generator::Sygnaly(POCZ_SYGNAL));
    menedzer menedzer(uar, gen);
    sim_handler simhandler;
    MainWindow w(&menedzer, &simhandler);
    //w.set_wartosci_domyslne();
    w.show();
    return a.exec();
}
