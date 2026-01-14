#include "arx_dialog.h"
#include "modelARX.h"
#include "ui_arx_dialog.h"

arx_dialog::arx_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::arx_dialog)
{
    ui->setupUi(this);
    ui->gorna_sterowanie->setEnabled(false);
    ui->dolna_sterowanie->setEnabled(false);
    ui->gorna_wyjscie->setEnabled(false);
    ui->dolna_wyjscie->setEnabled(false);
}

arx_dialog::~arx_dialog()
{
    delete ui;
}


void arx_dialog::on_a_confirm_clicked()
{
    double wsp = ui->a_input->value();
    QString pom_value = QString::number(wsp) + ", ";
    ui->widok_a->insertPlainText(pom_value);
    wsp_a.push_back(wsp);
}

void arx_dialog::on_b_confirm_clicked()
{
    double wsp = ui->b_input->value();
    QString pom_value = QString::number(wsp) + ", ";
    ui->widok_b->insertPlainText(pom_value);
    wsp_b.push_back(wsp);
}

void arx_dialog::on_remove_a_clicked()
{
    if (!wsp_a.empty())
    {
        wsp_a.pop_back();
        ui->widok_a->clear();
        for (double wartosc : wsp_a) {
            ui->widok_a->insertPlainText(QString::number(wartosc) + ", ");
        }
    }
}

void arx_dialog::on_remove_b_clicked()
{
    if (!wsp_b.empty())
    {
        wsp_b.pop_back();
        ui->widok_b->clear();
        for (double wartosc : wsp_b) {
            ui->widok_b->insertPlainText(QString::number(wartosc) + ", ");
        }
    }
}

std::vector<double> arx_dialog::get_wsp_a()
{
    return wsp_a;
}

std::vector<double> arx_dialog::get_wsp_b()
{
    return wsp_b;
}

double arx_dialog::get_opoznienie()
{
    return opoznienie;
}

double arx_dialog::get_zaklocenie()
{
    return zaklocenia;
}

void arx_dialog::on_ok_arx_clicked()
{
    this->accept();
}

void arx_dialog::on_opoznienie_input_valueChanged(double arg1)
{
    opoznienie = arg1;
}

void arx_dialog::on_zaklocenie_input_valueChanged(double arg1)
{
    zaklocenia = arg1;
}

void arx_dialog::on_ograniczenia_sterowania_checked_stateChanged(int arg1)
{
    ograniczenie_sterowania = (arg1 == Qt::Checked);
    if(arg1 == 0)
    {
        ui->gorna_sterowanie->setEnabled(false);
        ui->dolna_sterowanie->setEnabled(false);
    }
    if(arg1 == 2)
    {
        ui->gorna_sterowanie->setEnabled(true);
        ui->dolna_sterowanie->setEnabled(true);
    }
}

void arx_dialog::on_ograniczenia_wyjscia_checked_stateChanged(int arg1)
{
    ograniczenie_wyjscia = (arg1 == Qt::Checked);
    if(arg1 == 0)
    {
        ui->gorna_wyjscie->setEnabled(false);
        ui->dolna_wyjscie->setEnabled(false);
    }
    if(arg1 == 2)
    {
        ui->gorna_wyjscie->setEnabled(true);
        ui->dolna_wyjscie->setEnabled(true);
    }
}


void arx_dialog::on_gorna_sterowanie_valueChanged(double arg1)
{
    ograniczenie_sterowania_gora = arg1;
}


void arx_dialog::on_dolna_sterowanie_valueChanged(double arg1)
{
    ograniczenie_sterowania_dol = arg1;
}


void arx_dialog::on_gorna_wyjscie_valueChanged(double arg1)
{
    ograniczenie_wyjscia_gora = arg1;
}


void arx_dialog::on_dolna_wyjscie_valueChanged(double arg1)
{
    ograniczenie_wyjscia_dol = arg1;
}

