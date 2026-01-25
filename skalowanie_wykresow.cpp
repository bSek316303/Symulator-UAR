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

void skalowanie_wykresow::skaluj_z_zakresu_x(double zakres_min, double zakres_max)
{
    for (int i = 0; i < tab_wykresow->size(); ++i) {

        double minY = std::numeric_limits<double>::max();
        double maxY = std::numeric_limits<double>::lowest();

        for (QAbstractSeries* abstractSeries : (*tab_wykresow)[i]->series()) {

            QLineSeries* seria = qobject_cast<QLineSeries*>(abstractSeries);
            if (!seria) continue;

            const auto& pts = seria->pointsVector();

            for (int k = pts.size() - 1; k >= 0; --k) {
                const QPointF& p = pts[k];

                if (p.x() > zakres_max) continue;
                if (p.x() < zakres_min) break;

                if (p.y() < minY) minY = p.y();
                if (p.y() > maxY) maxY = p.y();
            }
        }

        if (minY == std::numeric_limits<double>::max())
            continue;

        double zakresY = maxY - minY;
        if (zakresY < 1e-9) zakresY = 1.0;

        double margines = 0.1 * zakresY;

        double nowyMin = minY - margines;
        double nowyMax = maxY + margines;

        if (std::abs((*tab_min)[i] - nowyMin) > 1e-6) {
            (*tab_min)[i] = nowyMin;
            (*tab_osi_y)[i]->setMin(nowyMin);
        }

        if (std::abs((*tab_max)[i] - nowyMax) > 1e-6) {
            (*tab_max)[i] = nowyMax;
            (*tab_osi_y)[i]->setMax(nowyMax);
        }
    }
}
