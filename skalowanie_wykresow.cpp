#include "skalowanie_wykresow.h"

skalowanie_wykresow::skalowanie_wykresow() {}
void skalowanie_wykresow::setup(std::vector<QLineSeries*>* tab_serii_arg,
                                std::vector<QChart*>* tab_wykresow_arg,
                                std::vector<QValueAxis*>* tab_osi_x_arg,
                                std::vector<QValueAxis*>* tab_osi_y_arg,
                                std::vector<double>* tab_max_arg,
                                std::vector<double>* tab_min_arg){
    tab_serii = tab_serii_arg;
    tab_wykresow = tab_wykresow_arg;
    tab_osi_x = tab_osi_x_arg;
    tab_osi_y = tab_osi_y_arg;
    tab_max = tab_max_arg;
    tab_min = tab_min_arg;
}

void skalowanie_wykresow::skaluj_wykresy_po_appendzie(dane_do_wykresow dane){
    // Wykres 1
    double min_dane = (dane.uar < dane.gen) ? dane.uar : dane.gen;
    double max_dane = (dane.uar > dane.gen) ? dane.uar : dane.gen;
    if((*tab_min)[0] > min_dane){
        if(min_dane < 0) (*tab_min)[0] = min_dane * 1.15;
        else (*tab_min)[0] = min_dane * 0.85;
        (*tab_osi_y)[0]->setMin((*tab_min)[0]);
    }
    if((*tab_max)[0] < max_dane){
        if(max_dane > 0) (*tab_max)[0] = max_dane * 1.15;
        else (*tab_max)[0] = max_dane * 0.85;
        (*tab_osi_y)[0]->setMax((*tab_max)[0]);
    }

    // Wykres 2
    double dane_min_max = dane.uchyb;
    if((*tab_min)[1] > dane_min_max){
        if(dane_min_max < 0) (*tab_min)[1] = dane_min_max * 1.15;
        else (*tab_min)[1] = dane_min_max * 0.85;
        (*tab_osi_y)[1]->setMin((*tab_min)[1]);
    }
    else if((*tab_max)[1] < dane_min_max){
        if(dane_min_max > 0) (*tab_max)[1] = dane_min_max * 1.15;
        else (*tab_max)[1] = dane_min_max * 0.85;
        (*tab_osi_y)[1]->setMax((*tab_max)[1]);
    }

    // Wykres 3
    dane_min_max = dane.ster;
    if((*tab_min)[2] > dane_min_max){
        if(dane_min_max < 0) (*tab_min)[2] = dane_min_max * 1.15;
        else (*tab_min)[2] = dane_min_max * 0.85;
        (*tab_osi_y)[2]->setMin((*tab_min)[2]);
    }
    else if((*tab_max)[2] < dane_min_max){
        if(dane_min_max > 0) (*tab_max)[2] = dane_min_max * 1.15;
        else (*tab_max)[2] = dane_min_max * 0.85;
        (*tab_osi_y)[2]->setMax((*tab_max)[2]);
    }

    // Wykres 4
    max_dane = std::max({dane.p, dane.i, dane.d});
    min_dane = std::min({dane.p, dane.i, dane.d});
    if((*tab_min)[3] > min_dane){
        if(min_dane < 0) (*tab_min)[3] = min_dane * 1.15;
        else (*tab_min)[3] = min_dane * 0.85;
        (*tab_osi_y)[3]->setMin((*tab_min)[3]);
    }
    if((*tab_max)[3] < max_dane){
        if(max_dane > 0) (*tab_max)[3] = max_dane * 1.15;
        else (*tab_max)[3] = max_dane * 0.85;
        (*tab_osi_y)[3]->setMax((*tab_max)[3]);
    }
}

void skalowanie_wykresow::skaluj_wykresy_w_zakresie(double min_range, double max_range){
    for(int i = 0; i < tab_wykresow->size(); i++){
        (*tab_min)[i] = std::numeric_limits<double>::max();
        (*tab_max)[i] = std::numeric_limits<double>::min();

        for (QAbstractSeries *abstractSeries : (*tab_wykresow)[i]->series()) {
            QLineSeries *seria = qobject_cast<QLineSeries*>(abstractSeries);
            if (!seria) continue;
            const auto &punkty = seria->pointsVector();

            for (const auto &p : punkty) {
                double argument = p.x();
                double wartosc = p.y();
                if (argument >= min_range && argument <= max_range) {
                    if((*tab_min)[i] > wartosc){
                        (*tab_min)[i] = wartosc;
                    } else if((*tab_max)[i] < wartosc){
                        (*tab_max)[i] = wartosc;
                    }
                }
            }
        }

        if((*tab_min)[i] > 0) (*tab_osi_y)[i]->setMin((*tab_min)[i] * 0.85);
        else (*tab_osi_y)[i]->setMin((*tab_min)[i] * 1.15);
        if((*tab_max)[i] > 0) (*tab_osi_y)[i]->setMax((*tab_max)[i] * 1.15);
        else (*tab_osi_y)[i]->setMax((*tab_max)[i] * 0.85);
    }
}
