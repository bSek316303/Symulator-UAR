#include "fabryka_wykresow.h"

QChart* fabryka_wykresow::stworz_wykres(const konfiguracjaWykresu& cfg) {
    auto* wykres = new QChart();
    wykres->setTitle(cfg.tytul);
    wykres->legend()->setVisible(true);
    wykres->legend()->setAlignment(Qt::AlignBottom);

    wykres->setMargins(QMargins(0,0,0,0));
    wykres->setContentsMargins(0,0,0,0);

    // Ograniczenie: 1–3 serie
    if (cfg.serie.isEmpty() || cfg.serie.size() > 3)
        return wykres;

    for (const auto& s : cfg.serie)
    {
        wykres->addSeries(stworz_serie(s));
    }

    ustaw_osie(wykres, cfg.xOpis, cfg.yOpis);
    return wykres;
}

QLineSeries* fabryka_wykresow::stworz_serie(const QString& nazwa_serii) {
    auto* seria = new QLineSeries();
    seria->setName(nazwa_serii);
    return seria;
}

void fabryka_wykresow::ustaw_osie(QChart* wykres, const QString& xOpis, const QString& yOpis) {
    auto* axisX = new QValueAxis();
    auto* axisY = new QValueAxis();

    axisX->setTitleText(xOpis);
    axisY->setTitleText(yOpis);

    wykres->addAxis(axisX, Qt::AlignBottom);
    wykres->addAxis(axisY, Qt::AlignLeft);

    for (auto* s : wykres->series())
    {
        s->attachAxis(axisX);
        s->attachAxis(axisY);
    }
}
