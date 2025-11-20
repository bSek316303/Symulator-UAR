#include "mainwindow.h"
#include "main.h"
#include "ProstyUAR.h"
#include "menadzeruar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    /* Zakomentowałem do testu zapisu 20.11.2025
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
    QCoreApplication a(argc, argv);
    double Kp_test = 4.5;
    double Ti_test = 0.8;
    double Td_test = 0.5;
    std::vector<double> A_test = {1.5, 0.2, 6.4,7.5};
    std::vector<double> B_test = {0.0, 0.5, 0.5,0.6};
    int opoznienie_test = 2;
    double szum_test = 0.05;

    MenadzerUAR menadzer;
    menadzer.set_parametry_PID(Kp_test, Ti_test, Td_test);
    menadzer.set_pid_tryb(RegulatorPID::LiczCalke::Wew);
    menadzer.set_parametry_ARX(A_test, B_test);
    menadzer.set_szum(szum_test, true);
    menadzer.set_ograniczenia_sterowania_ARX(true, -5.0, 5.0);
    menadzer.set_ograniaczenia_wyjscia_ARX(true, -100.0, 100.0);
    menadzer.set_opoznienie_ARX(opoznienie_test);
    menadzer.zapisz_konfiguracje();

    menadzer.zastosuj_konfiguracje();
}
