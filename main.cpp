#include "mainwindow.h"
#include "main.h"
#include "ProstyUAR.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    /* Zakomentowałem do testu zapisu 20.11.2025
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
    QCoreApplication a(argc, argv);

    double Kp_test = 2.5;
    double Ti_test = 0.8;
    double Td_test = 0.1;
    std::vector<double> A_test = {0.8, -0.2};
    std::vector<double> B_test = {0.0, 0.5};
    int opoznienie_test = 2;
    double szum_test = 0.05;

    ProstyUAR testUAR(Kp_test, Ti_test, Td_test, A_test, B_test, opoznienie_test, szum_test);

    testUAR.get_ARX().set_ograniczenie_sterowania(true, -5.0, 5.0);
    testUAR.get_ARX().set_ograniczenie_wyjscia(true, -100.0, 100.0);

    QString sciezkaPliku = "test_uar_config.json";

    testUAR.zapis_do_pliku(testUAR, sciezkaPliku);
    return 0;

}
