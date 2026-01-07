#include "arx_dialog.h"
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

void arx_dialog::dodaj_do_listy(QTextBrowser lista_wspolczynnikow, QDoubleSpinBox wsp)
{
    QString pom_value = QString::number(wsp.value()) + ", ";
    lista_wspolczynnikow.append(pom_value);
}
