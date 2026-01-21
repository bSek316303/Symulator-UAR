#pragma once
#include "ProstyUAR.h"
#include "Generator.h"
#include "obsluga_pliku.h"
#include "qcoreapplication.h"
#include "qdir.h"
#include "qlineseries.h"
#include "qtimer.h"
#include "qvalueaxis.h"
#include "testy_setterow.h"
#include "qjsonarray.h"
#include <QJsonObject>
#include <qvector>
#include <QJsonDocument>
#include <QMetaType>
#include "skalowanie_wykresow.h"
#include <functional>

Q_DECLARE_METATYPE(std::vector<double>)

class menedzer: public QObject {
    Q_OBJECT
    friend class Testy_setterow;
private:
    ProstyUAR m_uar;
    Generator m_gen;
    QVector<double> Json_to_Wektor(const QJsonArray& dane_json);

    QTimer* stoper;
    double czas;
    std::function<void(dane_do_wykresow, double)> to_append;
public:
    explicit menedzer(ProstyUAR uar, Generator gen, QObject* parent = nullptr);
    void krok();
    void wyslij_arx();

    void set_wyjscie_kroku(std::function<void(dane_do_wykresow, double)> to_append_arg){ to_append = to_append_arg; }

    // PRZYGOTOWANIE SYMULACJI


    void set_interwal(int interwal);
    int get_interwal() const;
    double get_czas() const;

    // SYMULACJA

    void zacznij_symulacje();
    void zakoncz_symulacje();
    void resetuj_symulacje();

    // ARX

    void set_parametry_arx(const std::vector<double>& A, const std::vector<double>& B);
    void set_ograniczenia_sterowania_ARX(bool wlaczone, double min, double max)
    {
        m_uar.get_ARX().set_ograniczenie_sterowania(wlaczone);
        m_uar.get_ARX().set_sterowanie_min(min);
        m_uar.get_ARX().set_sterowanie_max(max);
    };
    void set_ograniaczenia_wyjscia_ARX(bool wlaczone, double min, double max)
    {
        m_uar.get_ARX().set_ograniczenie_wyjscia(wlaczone);
        m_uar.get_ARX().set_wyjscie_min(min);
        m_uar.get_ARX().set_wyjscie_max(max);
    }
    void set_ograniczenia_ster_ARX(bool wlaczone);
    void set_ograniczenia_wyj_ARX(bool wlaczone);
    void set_szum(double szum, bool czy_wlaczony);
    void set_opoznienie_ARX(int opoznienie_p);
    // PID
    void set_parametry_pid(double kp, double ti, double td);
    void set_pid_tryb(int index);
    void resetuj_pamiec_calki();
    void resetuj_pamiec_rozniczki();

    // Generator
    void set_parametry_generator(double amplituda, double stala_skladowa, double okres, double wypelnienie);
    void set_sygnal(int index);

    QJsonObject menedzer_to_json();
    QJsonObject Model_ARX_to_Json(const ModelARX& model_arx) const
    {
        QJsonObject obiekt_ARX;
        QJsonArray wektor_A;
        QJsonArray wektor_B;

        for(double wartosc: model_arx.get_A()) wektor_A.append(wartosc);
        for(double wartosc: model_arx.get_B()) wektor_B.append(wartosc);

        obiekt_ARX["Wektor_A"] = wektor_A;
        obiekt_ARX["Wektor_B"] = wektor_B;
        obiekt_ARX["Czy_wlaczony_szum"] = model_arx.get_czy_wlaczony_szum();
        obiekt_ARX["szum"] = model_arx.get_szum();
        obiekt_ARX["Opoznienie"] = model_arx.get_opoznienie();
        obiekt_ARX["Ograniczenie_sterowania"] = model_arx.get_ograniczenie_sterowania();
        obiekt_ARX["Sterowanie_min"] = model_arx.get_sterowanie_min();
        obiekt_ARX["Sterowanie_max"] = model_arx.get_sterowanie_max();
        obiekt_ARX["Ograniczenie_wyjscia"] = model_arx.get_ograniczenie_wyjscia();
        obiekt_ARX["Wyjscie_min"] = model_arx.get_wyjscie_min();
        obiekt_ARX["Wyjscie_max"] = model_arx.get_wyjscie_max();
        return obiekt_ARX;
    }
    QJsonObject RegulatorPID_to_Json(const RegulatorPID& Regulator_PID) const
    {
        QJsonObject regulator_pid;

        regulator_pid["Kp"] = Regulator_PID.getKp();
        regulator_pid["Ti"] = Regulator_PID.getTi();
        regulator_pid["Td"] = Regulator_PID.getTd();

        return regulator_pid;
    }

    ProstyUAR& get_m_uar()
    {
        return m_uar;
    }
    void zapisz_konfiguracje()
    {
        QJsonObject arx_json = Model_ARX_to_Json(m_uar.get_ARX());
        QJsonObject pid_json = RegulatorPID_to_Json(m_uar.get_regulator());
        QJsonObject menedzer_json = menedzer_to_json();

        QJsonObject glowny_obiekt;

        glowny_obiekt["Parametry_Symulacji"] = menedzer_json;
        glowny_obiekt["ARX"] = arx_json;
        glowny_obiekt["PID"] = pid_json;

        QJsonDocument dokument(glowny_obiekt);

        QByteArray jsonData = dokument.toJson(QJsonDocument::Indented);

        QString sciezka = QCoreApplication::applicationDirPath() + "/konfiguracja.json";

        QFile plik(sciezka);

        if (!plik.open(QIODevice::WriteOnly)) {
            qCritical() << "Nie mozna otworzyc pliku do zapisu!";
            return;
        }
        plik.write(jsonData);
        plik.close();
    }
    QJsonDocument wczytajKonfiguracje()
    {
        QFile plik("konfiguracja.json");

        if(!plik.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() <<"Nie mozna otworzyc pliku" << plik.error();
        }
        QByteArray dane_json = plik.readAll();
        plik.close();
        if (dane_json.isEmpty()) {
            qDebug() << "Plik JSON jest pusty.";
        }
        QJsonDocument dane;
        dane = QJsonDocument::fromJson(dane_json);
        return dane;
    }

    void wczytaj_konfiguracje(const QJsonDocument& dane_json)
    {
        if (dane_json.isNull() || !dane_json.isObject()) {
            qDebug() << "Błąd: Dokument JSON jest pusty lub nie jest głównym obiektem.";
            return;
        }

        QJsonObject obiekt_danych = dane_json.object();

        if (obiekt_danych.contains("PID") && obiekt_danych["PID"].isObject()) {
            QJsonObject pid_json = obiekt_danych["PID"].toObject();

            set_parametry_pid(
                pid_json["Kp"].toDouble(),
                pid_json["Ti"].toDouble(),
                pid_json["Td"].toDouble()
                );
        }

        if (obiekt_danych.contains("ARX") && obiekt_danych["ARX"].isObject()) {
            QJsonObject arx_json = obiekt_danych["ARX"].toObject();

            if (arx_json.contains("Wektor_A") && arx_json["Wektor_A"].isArray() &&
                arx_json.contains("Wektor_B") && arx_json["Wektor_B"].isArray())
            {
                QVector<double> wektor_A_qt = Json_to_Wektor(arx_json["Wektor_A"].toArray());
                QVector<double> wektor_B_qt = Json_to_Wektor(arx_json["Wektor_B"].toArray());

                std::vector<double> wektor_A(wektor_A_qt.begin(), wektor_A_qt.end());
                std::vector<double> wektor_B(wektor_B_qt.begin(), wektor_B_qt.end());

                set_parametry_arx(wektor_A, wektor_B);
            }
            set_szum(
                arx_json["szum"].toDouble(),
                arx_json["Czy_wlaczony_szum"].toBool()
                );

            set_opoznienie_ARX(arx_json["Opoznienie"].toInt());

            set_ograniczenia_sterowania_ARX(
                arx_json["Ograniczenie_sterowania"].toBool(),
                arx_json["Sterowanie_min"].toDouble(),
                arx_json["Sterowanie_max"].toDouble()
                );

            set_ograniaczenia_wyjscia_ARX(
                arx_json["Ograniczenie_wyjscia"].toBool(),
                arx_json["Wyjscie_min"].toDouble(),
                arx_json["Wyjscie_max"].toDouble()
                );
        }

        if (obiekt_danych.contains("Parametry_Symulacji") && obiekt_danych["Parametry_Symulacji"].isObject()) {
            QJsonObject uar_json = obiekt_danych["Parametry_Symulacji"].toObject();

            stoper->setInterval(uar_json["Taktowanie_ms"].toDouble());
            this->m_gen.set_okres(uar_json["Okres_rzeczywisty_s"].toDouble());
        }
    }
    void zastosuj_konfiguracje()
    {
        QJsonDocument dane = this->wczytajKonfiguracje();
        this->wczytaj_konfiguracje(dane);
    }
signals:
    void wyslij_dane_do_arx_dialog(std::vector<double> a_wsp, std::vector<double> b_wsp, bool ograniczenie_sterowania, bool ograniczenie_wyjscia, double szum, int opoznienie, double ster_gora, double ster_dol, double wyj_gora, double wyj_dol);


};

