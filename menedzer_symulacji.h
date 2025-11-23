#pragma once
#include "ProstyUAR.h"
#include "qdebug.h"
#include <QObject>
#include <memory>
#include <array>
#include <utility>
#include <map>
#include <QTimer>
#include "ProstyUAR.h"
#include "Generator.h"
class menedzer_symulacji
{
public:
    enum class wykresy {
        wykres_uar,
        wykres_uchybu,
        wykres_sterowania,
        wykres_skladowych_pid
    };
private:
    ProstyUAR m_uar;
    Generator m_gen;
    Generator::Sygnaly m_rodzajSygnalu;
    std::unique_ptr<QTimer> stoper = std::make_unique<QTimer>(new QTimer());
    inline static constexpr std::array<wykresy, 4> tab_wykresow = {wykresy::wykres_uar, wykresy::wykres_uchybu, wykresy::wykres_sterowania, wykresy::wykres_skladowych_pid};
    std::pair<double, double> generuj_dane_wykres_uar(double sygWe, double czas){
        double sygSter = m_gen.generuj(czas, m_rodzajSygnalu);
        return std::make_pair(m_uar.symuluj(sygSter), czas);
    }
    std::pair<double, double> generuj_dane_wykres_uchybu(double sygWe, double czas){
        return std::make_pair(sygWe - m_uar.get_ostatni_syg_wy(), czas);
    }
    std::pair<double, double> generuj_dane_wykres_sterowania(double sygWe, double czas){
        return std::make_pair(m_uar.get_regulator().getLastP() + m_uar.get_regulator().getLastI() + m_uar.get_regulator().getLastD(), czas);
    }
    std::pair<double, double> generuj_dane_Wykres_skladowych_pid(double sygWe, double czas);
    std::map<wykresy, std::pair<double, double>(menedzer_symulacji::*)(double, double)> tab_funkcji_obliczania = { {wykresy::wykres_uar, &menedzer_symulacji::generuj_dane_wykres_uar},
                                                                                                     {wykresy::wykres_uchybu, &menedzer_symulacji::generuj_dane_wykres_uchybu},
                                                                                                     {wykresy::wykres_sterowania, &menedzer_symulacji::generuj_dane_wykres_sterowania},
                                                                                                     {wykresy::wykres_skladowych_pid, &menedzer_symulacji::generuj_dane_Wykres_skladowych_pid}};

    std::pair<double, double> aktualizuj_dane_wykres_uar();
    std::pair<double, double> aktualizuj_dane_wykres_uchybu();
    std::pair<double, double> aktualizuj_dane_wykres_sterowania();
    std::pair<double, double> aktualizuj_dane_Wykres_skladowych_pid();
    std::map<wykresy, std::pair<double, double>(menedzer_symulacji::*)()> tab_funkcji_aktualizacji = { {wykresy::wykres_uar, &menedzer_symulacji::aktualizuj_dane_wykres_uar},
                                                                                                       {wykresy::wykres_uchybu, &menedzer_symulacji::aktualizuj_dane_wykres_uchybu},
                                                                                                       {wykresy::wykres_sterowania, &menedzer_symulacji::aktualizuj_dane_wykres_sterowania},
                                                                                                       {wykresy::wykres_skladowych_pid, &menedzer_symulacji::aktualizuj_dane_Wykres_skladowych_pid}};
public:

    menedzer_symulacji(ProstyUAR uar, Generator gen)
        : m_uar(uar), m_gen(gen)
    {
    }

    std::pair<double, double> obliczWartosci(wykresy wyk, double sygWy, double interwal){
        return (this->*tab_funkcji_obliczania[wyk])(sygWy, interwal);
    }
    void aktualizujWykres(wykresy wyk, std::pair<double, double> wartosci){
        //tymczasowo konsola
        qDebug() << "Os X: " << wartosci.first << " Os Y: " << wartosci.second << "\n";
    }
    void setInterwal(int time_in_ms){
        stoper->setInterval(time_in_ms);
    }
};
