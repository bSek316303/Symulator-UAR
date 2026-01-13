#include "mainwindow.h"
#include "arx_dialog.h"
#include "ui_mainwindow.h"
#include "fabryka_wykresow.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QPainter>

void MainWindow::set_wartosci_domyslne(){
    ui->spnbx_wzmocnienie->setValue(POCZ_KP);
    ui->spnbx_stal_calkowania->setValue(POCZ_TI);
    ui->spnbx_stala_rozniczkowania->setValue(POCZ_TD);
    ui->spnbx_amplituda->setValue(POCZ_AMP);
    ui->spnbx_amplituda->setMinimum(0.0);
    ui->spnbx_wypelnienie->setValue(POCZ_P);
    ui->spnbx_stala_skladowa->setValue(POCZ_S);
    if(POCZ_LICZ_CALKE) ui->rdio_w_calce->setChecked(true);
    else ui->rdio_poza_calka->setChecked(true);
    ui->spnbx_czas_wykresu->setValue(POCZ_ZAKRES_X);
    ui->spnbx_czas_wykresu->setRange(5, 500);
    ui->spnbx_okres->setValue(POCZ_OKRES);
    ui->spnbx_okres->setMinimum(0.0);
    ui->spnbx_taktowanie->setValue(POCZ_TAKTOWANIE);
    ui->spnbx_taktowanie->setRange(10, 1000);
}
MainWindow::MainWindow(PIDConfig* pidcfg, ARXConfig* arxcfg, GENConfig* gencfg, class sim_handler* simhandler, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Asocjacja abstrakcji.
    pidconfig = pidcfg;
    arxconfig = arxcfg;
    genconfig = gencfg;
    sim_handler = simhandler;

    // Typ sygnalu generatora.
    ui->comboBox_typ_sygnalu->blockSignals(true);
    ui->comboBox_typ_sygnalu->addItem("Sinusoidalny");
    ui->comboBox_typ_sygnalu->addItem("Prostokątny");
    ui->comboBox_typ_sygnalu->setCurrentIndex(POCZ_SYGNAL);
    ui->comboBox_typ_sygnalu->blockSignals(false);

    // Tworzenie wykresów.
    konfiguracjaWykresu uar_cfg;
    uar_cfg.tytul = "wykres generatora i UAR";
    uar_cfg.serie = { "Generator", "UAR" };
    auto paczka = fabryka_wykresow::stworz_wykres(uar_cfg);
    for(auto* x: std::get<1>(paczka)){
        sim_handler->dodaj_serie(x);
    }
    QChart* wykres_uar = std::get<0>(paczka);
    sim_handler->dodaj_wykres(wykres_uar);
    sim_handler->dodaj_os_x(std::get<2>(paczka));
    sim_handler->dodaj_os_y(std::get<3>(paczka));

    konfiguracjaWykresu uchyb_cfg;
    uchyb_cfg.tytul = "wykres uchybu";
    uchyb_cfg.serie.append("Uchyb");
    paczka = fabryka_wykresow::stworz_wykres(uchyb_cfg);
    for(auto* x: std::get<1>(paczka)){
        sim_handler->dodaj_serie(x);
    }
    QChart* wykres_uchyb = std::get<0>(paczka);
    sim_handler->dodaj_wykres(wykres_uchyb);
    sim_handler->dodaj_os_x(std::get<2>(paczka));
    sim_handler->dodaj_os_y(std::get<3>(paczka));

    konfiguracjaWykresu ster_cfg;
    ster_cfg.tytul = "wykres wartosci sterujacej";
    ster_cfg.serie.append("serie");
    paczka = fabryka_wykresow::stworz_wykres(ster_cfg);
    for(auto* x: std::get<1>(paczka)){
        sim_handler->dodaj_serie(x);
    }
    QChart* wykres_ster = std::get<0>(paczka);
    sim_handler->dodaj_wykres(wykres_ster);
    sim_handler->dodaj_os_x(std::get<2>(paczka));
    sim_handler->dodaj_os_y(std::get<3>(paczka));

    konfiguracjaWykresu pid_cfg;
    pid_cfg.tytul = "wykres PID";
    pid_cfg.serie = { "P", "I", "D" };
    paczka = fabryka_wykresow::stworz_wykres(pid_cfg);
    for(auto* x: std::get<1>(paczka)){
        sim_handler->dodaj_serie(x);
    }
    QChart* wykres_pid = std::get<0>(paczka);
    sim_handler->dodaj_wykres(wykres_pid);
    sim_handler->dodaj_os_x(std::get<2>(paczka));
    sim_handler->dodaj_os_y(std::get<3>(paczka));

    // Widoki wykresów.
    QChartView* widok_uar = new QChartView(wykres_uar);
    QChartView* widok_uchyb = new QChartView(wykres_uchyb);
    QChartView* widok_ster = new QChartView(wykres_ster);
    QChartView* widok_pid = new QChartView(wykres_pid);

    widok_uar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_uchyb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_ster->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_pid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    widok_uar->setRenderHint(QPainter::Antialiasing);
    widok_uchyb->setRenderHint(QPainter::Antialiasing);
    widok_ster->setRenderHint(QPainter::Antialiasing);
    widok_pid->setRenderHint(QPainter::Antialiasing);

    ui->chart_layout->addWidget(widok_uar,4);
    ui->chart_layout->addWidget(widok_uchyb,3);
    ui->chart_layout->addWidget(widok_ster,3);
    ui->chart_layout->addWidget(widok_pid,3);

    // Wartości MIN/MAX
    ui->spnbx_taktowanie->setMinimum(50);
    ui->spnbx_taktowanie->setMaximum(1000);
}

MainWindow::~MainWindow() { delete ui; }

// Przycisk ARX.
void MainWindow::on_btn_nastawy_arx_clicked()
{
    arx_dialog *okno = new arx_dialog(this);
    okno->setAttribute(Qt::WA_DeleteOnClose);
    connect(okno, &arx_dialog::accepted, this, [this, okno]() {
        arxconfig->set_a(okno->get_wsp_a());
        arxconfig->set_b(okno->get_wsp_b());
        arxconfig->set_opoznienie(okno->get_opoznienie());
        arxconfig->set_zaklocenie(okno->get_zaklocenie());
    });
    okno->show();
}
// Przyciski PID.
void MainWindow::on_spnbx_wzmocnienie_valueChanged(double arg1) { pidconfig->set_kp(arg1); }
void MainWindow::on_spnbx_stal_calkowania_valueChanged(double arg1) { pidconfig->set_ti(arg1); }
void MainWindow::on_spnbx_stala_rozniczkowania_valueChanged(double arg1){ pidconfig->set_td(arg1); }
void MainWindow::on_btn_resetuj_pamiec_calki_clicked() { pidconfig->powiadom_o_resecie_pamieci_calki(); }
void MainWindow::on_btn_reset_pamieci_rozniczki_clicked() { pidconfig->powiadom_o_resecie_pamieci_rozniczki(); }
void MainWindow::on_rdio_w_calce_toggled(bool checked) { if(checked) pidconfig->set_licz_calke(1); }
void MainWindow::on_rdio_poza_calka_toggled(bool checked){ if(checked) pidconfig->set_licz_calke(0); }

// Przyciski Generator.
void MainWindow::on_spnbx_amplituda_valueChanged(double arg1) { genconfig->set_a(arg1); }
void MainWindow::on_spnbx_stala_skladowa_valueChanged(double arg1) { genconfig->set_s(arg1); }
void MainWindow::on_spnbx_wypelnienie_valueChanged(double arg1) { genconfig->set_p(arg1); }
void MainWindow::on_spnbx_okres_valueChanged(double arg1) { genconfig->set_okres(arg1); }
void MainWindow::on_spnbx_taktowanie_valueChanged(int arg1){
    if (arg1 > 1000) arg1 = 1000;
    else if (arg1 < 10) arg1 = 10;
    sim_handler->set_interwal(arg1);
}

void MainWindow::on_btn_stop_clicked() { sim_handler->zakoncz_symulacje(); }
void MainWindow::on_btn_start_clicked() { sim_handler->zacznij_symulacje(); }
void MainWindow::on_btn_reset_clicked() { sim_handler->resetuj_symulacje(); }
void MainWindow::on_spnbx_czas_wykresu_valueChanged(int arg1) { sim_handler->set_czas_wykresu(arg1); }
void MainWindow::on_comboBox_typ_sygnalu_currentIndexChanged(int index) { genconfig->set_syg(index); }

