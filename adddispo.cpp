#include "adddispo.h"
#include "ui_adddispo.h"

adddispo::adddispo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adddispo)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit_2->setDate(QDate::currentDate());
}

void adddispo::loadProf(QVector<Prof*> _profs)
{
    profs = _profs;

    for (int i = 0; i < _profs.size(); ++i)
        ui->comboProf->addItem(_profs.at(i)->getName());
}

QString adddispo::getLine1()
{
    return ui->comboProf->currentText();
}

QDateTime adddispo::getLine2()
{
    return ui->dateTimeEdit->dateTime();
}

QDateTime adddispo::getLine3()
{
    return ui->dateTimeEdit_2->dateTime();
}

void adddispo::clean()
{
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit_2->setDate(QDate::currentDate());
}

void adddispo::on_pushButton_clicked()
{
    close();

}

adddispo::~adddispo()
{
    delete ui;
}
