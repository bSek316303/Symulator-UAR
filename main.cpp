#include "mainwindow.h"
#include "ProstyUAR.h"
#include "Generator.h"
#include "menedzer.h"
#include "stale.h"
#include "pidconfig.h"

#include <QApplication>

int main (int argc, char *argv[]){
    QApplication a(argc, argv);

    // Abstrakcje
    PIDConfig pidconfig;


    ProstyUAR uar(POCZ_KP, POCZ_TI, POCZ_TD, POCZ_LICZ_CALKE, POCZ_A, POCZ_B, POCZ_OPOZNIENIE, POCZ_SZUM);
    Generator gen(POCZ_AMP, POCZ_S, POCZ_P, POCZ_SYGNAL);
    menedzer menedzer(uar, gen, pidconfig);

    MainWindow w;
    w.show();
    return a.exec();
}
