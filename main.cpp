#include "mainwindow.h"
#include "menedzer.h"
#include "stale.h"
#include "skalowanie_wykresow.h"
#include <QApplication>

int main (int argc, char *argv[]){
    QApplication a(argc, argv);
    qRegisterMetaType<std::vector<double>>("std::vector<double>");
    ProstyUAR uar(POCZ_KP, POCZ_TI, POCZ_TD, RegulatorPID::LiczCalke(POCZ_LICZ_CALKE), POCZ_A, POCZ_B, POCZ_OPOZNIENIE, POCZ_SZUM);
    Generator gen(POCZ_OKRES, POCZ_AMP, POCZ_S, POCZ_P, Generator::Sygnaly(POCZ_SYGNAL));
    menedzer menedzer(uar, gen);
    MainWindow w(&menedzer);
    w.show();
    return a.exec();
}
