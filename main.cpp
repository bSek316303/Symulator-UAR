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

    // 1. Definicja parametrów testowych
    double Kp_test = 4.5;
    double Ti_test = 0.8;
    double Td_test = 0.5;
    std::vector<double> A_test = {0.8, -0.2};
    std::vector<double> B_test = {0.0, 0.5};
    int opoznienie_test = 2;
    double szum_test = 0.05;

    MenadzerUAR menadzer;
    menadzer.setPidParameters(Kp_test, Ti_test, Td_test);
    menadzer.setPidIntegralMode(RegulatorPID::LiczCalke::Wew);
    menadzer.setArxCoefficients(A_test, B_test);
    menadzer.setArxNoise(szum_test, true);
    menadzer.setArxControlLimits(true, -5.0, 5.0);
    menadzer.setArxOutputLimits(true, -100.0, 100.0);
    qDebug() << "-> Rozpoczynanie zapisu do pliku JSON...";
    menadzer.zapisz_konfiguracje();
    qDebug() << "   Zapis wykonany pomyślnie.";

    return 0;

}
