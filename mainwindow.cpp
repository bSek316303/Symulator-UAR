#include "mainwindow.h"
#include "arx_dialog.h"
#include "ui_mainwindow.h"
#include "menedzer.h"
#include "fabryka_wykresow.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QPainter>
#include <QDebug>

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
    ui->spnbx_czas_wykresu->setRange(5, 50);
    ui->spnbx_okres->setValue(POCZ_OKRES);
    ui->spnbx_okres->setMinimum(1.0);
    ui->spnbx_taktowanie->setRange(10, 1000);
    ui->spnbx_taktowanie->setValue(POCZ_TAKTOWANIE);
}

void MainWindow::append(dane_do_wykresow dane, double czas){
    skalowanie.skaluj_z_zakresu_x(czas-zakres_osi_x, czas);
    tab_serii[0]->append(czas, dane.uar);
    tab_serii[1]->append(czas, dane.gen);
    tab_serii[2]->append(czas, dane.uchyb);
    tab_serii[3]->append(czas, dane.ster);
    tab_serii[4]->append(czas, dane.p);
    tab_serii[5]->append(czas, dane.i);
    tab_serii[6]->append(czas, dane.d);
    if(czas >= zakres_osi_x) zwieksz_zakres_osi_x(czas);
}

MainWindow::MainWindow(class menedzer* menedzer_p, QWidget *parent)
    : QMainWindow(parent)
    , skalowanie(), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Symulator UAR");
    ui->centralwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    menedzer = menedzer_p;
    menedzer->set_wyjscie_kroku(std::bind(&MainWindow::append, this, std::placeholders::_1, std::placeholders::_2));

    // SYMULACJA.
    zakres_osi_x = POCZ_ZAKRES_X;
    skalowanie.setup(&tab_serii, &tab_wykresow, &tab_osi_x, &tab_osi_y, &tab_max, &tab_min);

    // QMenu.
    QMenu *menu_plik = menuBar()->addMenu("Plik");
    QAction *akcja_wczytaj = menu_plik->addAction("Wczytaj konfiguracje");
    QAction *akcja_zapisz = menu_plik->addAction("Zapisz konfiguracje");
    connect(akcja_wczytaj, &QAction::triggered, menedzer, &menedzer::zastosuj_konfiguracje);
    connect(akcja_zapisz, &QAction::triggered, menedzer, &menedzer::zapisz_konfiguracje);

    // Typ sygnalu generatora.
    ui->comboBox_typ_sygnalu->blockSignals(true);
    ui->comboBox_typ_sygnalu->addItem("Sinusoidalny");
    ui->comboBox_typ_sygnalu->addItem("Prostokątny");
    ui->comboBox_typ_sygnalu->setCurrentIndex(POCZ_SYGNAL);
    ui->comboBox_typ_sygnalu->blockSignals(false);

    // Tworzenie wykresów.
    konfiguracjaWykresu uar_cfg;
    uar_cfg.tytul = "wykres generatora i UAR";
    uar_cfg.serie = { "UAR  ", "GEN  " };
    auto paczka = fabryka_wykresow::stworz_wykres(uar_cfg);
    for(auto* x: std::get<1>(paczka)){
        x->useOpenGL();
        dodaj_serie(x);
    }
    QChart* wykres_uar = std::get<0>(paczka);
    dodaj_wykres(wykres_uar);
    dodaj_os_x(std::get<2>(paczka));
    dodaj_os_y(std::get<3>(paczka));

    konfiguracjaWykresu uchyb_cfg;
    uchyb_cfg.tytul = "wykres uchybu";
    uchyb_cfg.serie.append("Uchyb");
    paczka = fabryka_wykresow::stworz_wykres(uchyb_cfg);
    for(auto* x: std::get<1>(paczka)){
        x->useOpenGL();
        dodaj_serie(x);
    }
    QChart* wykres_uchyb = std::get<0>(paczka);
    dodaj_wykres(wykres_uchyb);
    dodaj_os_x(std::get<2>(paczka));
    dodaj_os_y(std::get<3>(paczka));

    konfiguracjaWykresu ster_cfg;
    ster_cfg.tytul = "wykres wartosci sterujacej";
    ster_cfg.serie.append("Ster.  ");
    paczka = fabryka_wykresow::stworz_wykres(ster_cfg);
    for(auto* x: std::get<1>(paczka)){
        x->useOpenGL();
        dodaj_serie(x);
    }
    QChart* wykres_ster = std::get<0>(paczka);
    dodaj_wykres(wykres_ster);
    dodaj_os_x(std::get<2>(paczka));
    dodaj_os_y(std::get<3>(paczka));

    konfiguracjaWykresu pid_cfg;
    pid_cfg.tytul = "wykres PID";
    pid_cfg.serie = { "P    ", "I    ", "D    " };
    paczka = fabryka_wykresow::stworz_wykres(pid_cfg);
    for(auto* x: std::get<1>(paczka)){
        x->useOpenGL();
        dodaj_serie(x);
    }
    QChart* wykres_pid = std::get<0>(paczka);
    dodaj_wykres(wykres_pid);
    dodaj_os_x(std::get<2>(paczka));
    dodaj_os_y(std::get<3>(paczka));

    // Widoki wykresów.
    QChartView* widok_uar = new QChartView(wykres_uar);
    QChartView* widok_uchyb = new QChartView(wykres_uchyb);
    QChartView* widok_ster = new QChartView(wykres_ster);
    QChartView* widok_pid = new QChartView(wykres_pid);

    widok_uar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_uar->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    widok_uar->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontSavePainterState);
    widok_uar->setOptimizationFlags(QGraphicsView::OptimizationFlag::IndirectPainting);
    widok_uchyb->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_uchyb->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    widok_uchyb->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontSavePainterState);
    widok_uchyb->setOptimizationFlags(QGraphicsView::OptimizationFlag::IndirectPainting);
    widok_ster->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_ster->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    widok_ster->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontSavePainterState);
    widok_ster->setOptimizationFlags(QGraphicsView::OptimizationFlag::IndirectPainting);
    widok_pid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    widok_pid->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontAdjustForAntialiasing);
    widok_pid->setOptimizationFlags(QGraphicsView::OptimizationFlag::DontSavePainterState);
    widok_pid->setOptimizationFlags(QGraphicsView::OptimizationFlag::IndirectPainting);

    widok_uar->setRenderHint(QPainter::Antialiasing);
    widok_uchyb->setRenderHint(QPainter::Antialiasing);
    widok_ster->setRenderHint(QPainter::Antialiasing);
    widok_pid->setRenderHint(QPainter::Antialiasing);

    ui->chart_layout->addWidget(widok_uar,4);
    ui->chart_layout->addWidget(widok_uchyb,3);
    ui->chart_layout->addWidget(widok_ster,3);
    ui->chart_layout->addWidget(widok_pid,3);

    set_wartosci_domyslne();
}

MainWindow::~MainWindow() { delete ui; }

// Przycisk ARX.
void MainWindow::on_btn_nastawy_arx_clicked()//DZIALA XD
{
    arx_dialog *okno = new arx_dialog(this);
    okno->setAttribute(Qt::WA_DeleteOnClose);
    connect(okno, &arx_dialog::accepted, this, [this, okno]() {
        menedzer->set_parametry_arx(okno->get_wsp_a(), okno->get_wsp_b());
        menedzer->set_opoznienie_ARX(okno->get_opoznienie());
        menedzer->set_szum(okno->get_zaklocenie(), true);
        if(okno->get_ograniczenie_sterowania()){
            menedzer->set_ograniczenia_sterowania_ARX(okno->get_ograniczenie_sterowania(), okno->get_ograniczenie_sterowania_dol(), okno->get_ograniczenie_sterowania_gora());
        }
        else{
            menedzer->set_ograniczenia_ster_ARX(okno->get_ograniczenie_sterowania());
        }
        if(okno->get_ograniczenie_wyjscia()){
            menedzer->set_ograniaczenia_wyjscia_ARX(okno->get_ograniczenie_wyjscia(), okno->get_ograniczenie_wyjscia_dol(), okno->get_ograniczenie_wyjscia_gora());
        }
        else{
            menedzer->set_ograniczenia_wyj_ARX(okno->get_ograniczenie_wyjscia());
        }
        // std::cout<< okno->get_ograniczenie_sterowania()<< okno->get_ograniczenie_sterowania_dol() <<okno->get_ograniczenie_sterowania_gora() << std::endl;
        // std::cout<< okno->get_ograniczenie_wyjscia()<< okno->get_ograniczenie_wyjscia_dol() <<okno->get_ograniczenie_wyjscia_gora() << std::endl;
        std::cout<< okno->get_opoznienie()<<std::endl;
    });
    connect(menedzer, &menedzer::wyslij_dane_do_arx_dialog ,okno, &arx_dialog::ustaw_dane);

    menedzer->wyslij_arx();
    okno->show();

}

void MainWindow::on_btn_resetuj_pamiec_calki_clicked() { menedzer->resetuj_pamiec_calki(); }
void MainWindow::on_btn_reset_pamieci_rozniczki_clicked() { menedzer->resetuj_pamiec_rozniczki(); }
void MainWindow::on_rdio_w_calce_toggled(bool checked) { if(checked) menedzer->set_pid_tryb(1); }
void MainWindow::on_rdio_poza_calka_toggled(bool checked){ if(checked) menedzer->set_pid_tryb(0); }

void MainWindow::on_comboBox_typ_sygnalu_currentIndexChanged(int index) { menedzer->set_sygnal(index); }

void MainWindow::on_btn_stop_clicked() { menedzer->zakoncz_symulacje(); }
void MainWindow::on_btn_start_clicked() { menedzer->zacznij_symulacje(); }
void MainWindow::on_btn_reset_clicked() {
    menedzer->resetuj_symulacje();
    for(auto &wykres: tab_wykresow) {
        for (QAbstractSeries *abstractSeries : wykres->series()) {
            QLineSeries *seria = qobject_cast<QLineSeries*>(abstractSeries);
            if (!seria) continue;
            seria->clear();
        }
    }
    for(auto& x: tab_osi_x){ x->setRange(0, zakres_osi_x); }
}
/*
void MainWindow::on_wczytaj_konfiguracje_clicked(){ //menedzer->wczytajKonfiguracje();
}
void MainWindow::on_zapisz_konfiguracje_clicked(){ //menedzer->zapisz_konfiguracje();
}
*/

// LOGIKA WYKRESOW

void MainWindow::dodaj_serie(QLineSeries* seria){ tab_serii.push_back(seria); }
void MainWindow::dodaj_wykres(QChart* wykres) {
    tab_wykresow.push_back(wykres);
    tab_max.push_back(std::numeric_limits<double>::min());
    tab_min.push_back(std::numeric_limits<double>::max());
}
void MainWindow::dodaj_os_x(QValueAxis* os) {
    tab_osi_x.push_back(os);
    os->setRange(0, zakres_osi_x);
}
void MainWindow::dodaj_os_y(QValueAxis* os) {
    tab_osi_y.push_back(os);
    os->setRange(-10, 10);
}

void MainWindow::zwieksz_zakres_osi_x(double czas){
    int interwal = menedzer->get_interwal();
    for(auto& x: tab_osi_x){ x->setRange(czas - zakres_osi_x,czas); }
    //skalowanie.skaluj_wykresy_przy_resizie(czas - zakres_osi_x / 2, czas + zakres_osi_x / 2);
}
void MainWindow::set_czas_wykresu(double nowy_czas){
    if(nowy_czas < menedzer->get_czas()) for(auto& x : tab_osi_x) x->setRange(x->max() - nowy_czas, x->max());
    else for(auto& x : tab_osi_x) x->setRange(0, nowy_czas);
}

// PRZYCISKI

// Przyciski PID
void MainWindow::on_spnbx_wzmocnienie_editingFinished()
{
    menedzer->set_parametry_pid(ui->spnbx_wzmocnienie->value(), ui->spnbx_stal_calkowania->value(), ui->spnbx_stala_rozniczkowania->value());
}


void MainWindow::on_spnbx_stal_calkowania_editingFinished()
{
    menedzer->set_parametry_pid(ui->spnbx_wzmocnienie->value(), ui->spnbx_stal_calkowania->value(), ui->spnbx_stala_rozniczkowania->value());
}


void MainWindow::on_spnbx_stala_rozniczkowania_editingFinished()
{
    menedzer->set_parametry_pid(ui->spnbx_wzmocnienie->value(), ui->spnbx_stal_calkowania->value(), ui->spnbx_stala_rozniczkowania->value());
}

// Przyciski do ustawień symulacji
void MainWindow::on_spnbx_czas_wykresu_editingFinished()
{
    set_czas_wykresu(ui->spnbx_czas_wykresu->value());
}

void MainWindow::on_spnbx_taktowanie_editingFinished()
{
    int arg1 = ui->spnbx_taktowanie->value();
    if (arg1 > 1000) arg1 = 1000;
    else if (arg1 < 10) arg1 = 10;
    menedzer->set_interwal(arg1);
}


// Przyciski Generator
//double amplituda, double stala_skladowa, double okres, double wypelnienie
void MainWindow::on_spnbx_amplituda_editingFinished()
{
    menedzer->set_parametry_generator(ui->spnbx_amplituda->value(), ui->spnbx_stala_skladowa->value(), ui->spnbx_okres->value(), ui->spnbx_wypelnienie->value());
}


void MainWindow::on_spnbx_stala_skladowa_editingFinished()
{
    menedzer->set_parametry_generator(ui->spnbx_amplituda->value(), ui->spnbx_stala_skladowa->value(), ui->spnbx_okres->value(), ui->spnbx_wypelnienie->value());
}


void MainWindow::on_spnbx_wypelnienie_editingFinished()
{
    menedzer->set_parametry_generator(ui->spnbx_amplituda->value(), ui->spnbx_stala_skladowa->value(), ui->spnbx_okres->value(), ui->spnbx_wypelnienie->value());
}

void MainWindow::on_spnbx_okres_editingFinished()
{
    menedzer->set_parametry_generator(ui->spnbx_amplituda->value(), ui->spnbx_stala_skladowa->value(), ui->spnbx_okres->value(), ui->spnbx_wypelnienie->value());
}

