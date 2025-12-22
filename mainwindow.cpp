#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fabryka_wykresow.h"
#include <QtCharts/QtCharts>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QPainter>

void MainWindow::set_wartosci_domyslne(){
    ui->spnbx_wzmocnienie->setValue(POCZ_KP);
    ui->spnbx_stal_calkowania->setValue(POCZ_TI);
    ui->spnbx_stala_rozniczkowania->setValue(POCZ_TD);
    ui->spnbx_amplituda->setValue(POCZ_AMP);
    ui->spnbx_wypelnienie->setValue(POCZ_P);
    ui->spnbx_stala_skladowa->setValue(POCZ_S);
    if(POCZ_LICZ_CALKE) ui->rdio_w_calce->setChecked(true);
    else ui->rdio_poza_calka->setChecked(true);
    if(POCZ_SYGNAL) ui->rdiobtn_square->setChecked(true);
    else ui->rdiobtn_sin->setChecked(true);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Wykresy.
    konfiguracjaWykresu uar_cfg;
    uar_cfg.tytul = "wykres generatora i UAR";
    uar_cfg.serie = { "Generator", "UAR" };

    QChart* wykres_uar = fabryka_wykresow::stworz_wykres(uar_cfg);

    konfiguracjaWykresu uchyb_cfg;
    uchyb_cfg.tytul = "wykres uchybu";
    uchyb_cfg.serie.append("Uchyb");

    QChart* wykres_uchyb = fabryka_wykresow::stworz_wykres(uchyb_cfg);

    konfiguracjaWykresu ster_cfg;
    ster_cfg.tytul = "wykres wartosci sterujacej";
    ster_cfg.serie.append("serie");

    QChart* wykres_ster = fabryka_wykresow::stworz_wykres(ster_cfg);

    konfiguracjaWykresu pid_cfg;
    pid_cfg.tytul = "wykres PID";
    pid_cfg.serie = { "P", "I", "D" };

    QChart* wykres_pid = fabryka_wykresow::stworz_wykres(pid_cfg);

    // Widoki wykresów.
    QChartView* widok_uar = new QChartView(wykres_uar);
    QChartView* widok_uchyb = new QChartView(wykres_uchyb);
    QChartView* widok_ster = new QChartView(wykres_ster);
    QChartView* widok_pid = new QChartView(wykres_pid);

    widok_uar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_uchyb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_ster->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_pid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->chart_layout->addWidget(widok_uar,2);
    ui->chart_layout->addWidget(widok_uchyb,1);
    ui->chart_layout->addWidget(widok_ster,1);
    ui->chart_layout->addWidget(widok_pid,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Przycisk ARX.
void MainWindow::on_btn_nastawy_arx_clicked()
{

}

// Przyciski PID.
void MainWindow::on_spnbx_wzmocnienie_valueChanged(double arg1) { pidconfig.set_kp(arg1); }
void MainWindow::on_spnbx_stal_calkowania_valueChanged(double arg1) { pidconfig.set_ti(arg1); }
void MainWindow::on_spnbx_stala_rozniczkowania_valueChanged(double arg1){ pidconfig.set_td(arg1); }
void MainWindow::on_btn_resetuj_pamiec_calki_clicked() { pidconfig.powiadom_o_resecie_pamieci_calki(); }
void MainWindow::on_btn_reset_pamieci_rozniczki_clicked() { pidconfig.powiadom_o_resecie_pamieci_rozniczki(); }
void MainWindow::on_rdio_w_calce_toggled(bool checked) { if(checked) pidconfig.set_licz_calke(1); }
void MainWindow::on_rdio_poza_calka_toggled(bool checked){ if(checked) pidconfig.set_licz_calke(0); }

// Przyciski Generator.
void MainWindow::on_spnbx_amplituda_valueChanged(double arg1) { genconfig.set_a(arg1); }
void MainWindow::on_spnbx_stala_skladowa_valueChanged(double arg1) { genconfig.set_s(arg1); }
void MainWindow::on_spnbx_wypelnienie_valueChanged(double arg1) { genconfig.set_p(arg1); }
void MainWindow::on_rdiobtn_square_toggled(bool checked) { if(checked) genconfig.set_syg(1); }
void MainWindow::on_rdiobtn_sin_toggled(bool checked) { if(checked) genconfig.set_syg(0); }

