#include "arx_dialog.h"
#include "modelARX.h"
#include "ui_arx_dialog.h"

arx_dialog::arx_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::arx_dialog)
{
    ui->setupUi(this);
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
    opoznienie = ui->opoznienie_input->value();
    zaklocenia = ui->zaklocenie_input->value();
    ModelARX arx;
    arx.set_A(wsp_a);
    arx.set_B(wsp_b);
    arx.set_opoznienie(int(get_opoznienie()));
    arx.set_szum(get_zaklocenie());
}

