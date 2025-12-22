#include "fabryka_wykresow.h"

std::tuple<QChart*, std::vector<QLineSeries*>, QValueAxis*, QValueAxis*>
fabryka_wykresow::stworz_wykres(const konfiguracjaWykresu& cfg) {
    auto* wykres = new QChart();
    std::vector<QLineSeries*> tab_serii;
    wykres->setTitle(cfg.tytul);
    wykres->legend()->setVisible(true);
    wykres->legend()->setAlignment(Qt::AlignBottom);

    // Test
    wykres->legend()->setVisible(false);
    wykres->setTitle("");

    wykres->setMargins(QMargins(0,0,0,0));
    wykres->setContentsMargins(0,0,0,0);

    // Ograniczenie: 1–3 serie
    if (cfg.serie.isEmpty() || cfg.serie.size() > 3)
        return {wykres, {}, 0, 0};

    for (const auto& s : cfg.serie)
    {
        QLineSeries* seria = stworz_serie(s);
        wykres->addSeries(seria);
        tab_serii.push_back(seria);
    }
    std::pair<QValueAxis*, QValueAxis*> osie;
    osie = ustaw_osie(wykres, cfg.xOpis, cfg.yOpis);
    return {wykres, tab_serii, osie.first, osie.second};
}

QLineSeries* fabryka_wykresow::stworz_serie(const QString& nazwa_serii) {
    auto* seria = new QLineSeries();
    seria->setName(nazwa_serii);
    return seria;
}

std::pair<QValueAxis*, QValueAxis*>
fabryka_wykresow::ustaw_osie(QChart* wykres, const QString& xOpis, const QString& yOpis) {
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
    return { axisX, axisY };
}
