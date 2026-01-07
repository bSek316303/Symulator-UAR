#ifndef FABRYKA_WYKRESOW_H
#define FABRYKA_WYKRESOW_H
#include <QVector>
#include <QString>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

struct konfiguracjaWykresu {
    QString tytul;
    QString xOpis;
    QString yOpis;
    QVector<QString> serie; // od 1 do 3 serii
};

class fabryka_wykresow {
public:
    static std::tuple<QChart*, std::vector<QLineSeries*>, QValueAxis*, QValueAxis*> stworz_wykres(const konfiguracjaWykresu& cfg);

private:
    static QLineSeries* stworz_serie(const QString& nazwa_serii);
    static std::pair<QValueAxis*, QValueAxis*> ustaw_osie(QChart* wykres, const QString& xOpis, const QString& y0pis);
};

#endif // FABRYKA_WYKRESOW_H
