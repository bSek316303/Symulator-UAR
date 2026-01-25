#ifndef SKALOWANIE_WYKRESOW_H
#define SKALOWANIE_WYKRESOW_H
#include <QTimer>
#include <QtCharts/QtCharts>
#include <QDebug>

struct dane_do_wykresow{
    double czas;
    double uar;
    double gen;
    double uchyb;
    double ster;
    double p;
    double i;
    double d;
};

class skalowanie_wykresow
{
private:

    std::vector<QLineSeries*>* tab_serii;
    std::vector<QChart*>* tab_wykresow;
    std::vector<QValueAxis*>* tab_osi_x;
    std::vector<QValueAxis*>* tab_osi_y;
    std::vector<double>* tab_max;
    std::vector<double>* tab_min;
public:
    void skaluj_z_zakresu_x(double zakres_min, double zakres_max);
    skalowanie_wykresow();
    void setup(std::vector<QLineSeries*>* tab_serii_arg,
               std::vector<QChart*>* tab_wykresow_arg,
               std::vector<QValueAxis*>* tab_osi_x_arg,
               std::vector<QValueAxis*>* tab_osi_y_arg,
               std::vector<double>* tab_max_arg,
               std::vector<double>* tab_min_arg);
};

#endif // SKALOWANIE_WYKRESOW_H

