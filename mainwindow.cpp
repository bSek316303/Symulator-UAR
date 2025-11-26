#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ProstyUAR.h"
#include "Generator.h"
#include <QtCharts/QtCharts>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RegulatorPID testPID(1.0, 2.0, 0.2);
    ModelARX testARX({ -0.4 }, { 0.6 }, 1);
    ProstyUAR instancjaTestowa(testARX, testPID);
    Generator gen(3,3,3);

    QWidget* glownyWidget = new QWidget(this);
    QHBoxLayout* glownyLayout = new QHBoxLayout(glownyWidget);

    QChartView* chart_widget = new QChartView();
    QWidget* control_widget = new QWidget();
    ui->chart_layout->addWidget(chart_widget);
    ui->control_layout->addWidget(control_widget);

    glownyLayout->addLayout(ui->chart_layout, 4);
    glownyLayout->addLayout(ui->control_layout,1);
    ui->centralwidget->setLayout(glownyLayout);

    chart_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    control_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //charts
    QChart* chart_uar = new QChart();
    chart_uar->setTitle("Wykres wyjscia UAR i generatora");
    chart_uar->legend()->setVisible(false);
    chart_uar->legend()->setAlignment(Qt::AlignBottom);
    chart_uar->setMargins(QMargins(10, 10, 10, 10));
    chart_uar->setBackgroundRoundness(1);

    QValueAxis* osX_uar = new QValueAxis();
    osX_uar->setTitleText("czas [s]");
    osX_uar->setRange(-20, 20);
    chart_uar->addAxis(osX_uar, Qt::AlignBottom);

    QValueAxis* osY_uar = new QValueAxis();
    osY_uar->setTitleText("wartości");
    osY_uar->setRange(0, 10);
    chart_uar->addAxis(osY_uar, Qt::AlignLeft);

    QLineSeries* series_out = new QLineSeries();
    series_out->attachAxis(osX_uar);
    series_out->attachAxis(osY_uar);

    QLineSeries* series_gen = new QLineSeries();
    series_gen->attachAxis(osX_uar);
    series_gen->attachAxis(osY_uar);

    chart_uar->addSeries(series_out);
    chart_uar->addSeries(series_gen);

    QChart* chart_uchyb = new QChart();

    QLineSeries* series_uchyb = new QLineSeries();
    chart_uar->addSeries(series_uchyb);

    QChart* chart_ster = new QChart();

    QLineSeries* series_ster = new QLineSeries();
    chart_ster->addSeries(series_ster);  

    QChart* chart_pid = new QChart();

    QLineSeries* seriesP = new QLineSeries();
    QLineSeries* seriesI = new QLineSeries();
    QLineSeries* seriesD = new QLineSeries();

    chart_pid->addSeries(seriesP);
    chart_pid->addSeries(seriesI);
    chart_pid->addSeries(seriesD);

    QChartView* widok_uar = new QChartView(chart_uar);
    QChartView* widok_uchyb = new QChartView(chart_uchyb);
    QChartView* widok_ster = new QChartView(chart_ster);
    QChartView* widok_pid = new QChartView(chart_pid);

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
