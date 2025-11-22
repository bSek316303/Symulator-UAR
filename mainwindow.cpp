#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ProstyUAR.h"
#include "Generator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RegulatorPID testPID(1.0, 2.0, 0.2);
    ModelARX testARX({ -0.4 }, { 0.6 }, 1);
    ProstyUAR instancjaTestowa(testARX, testPID);
    Generator gen(3,3,3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_test_clicked()
{

}

