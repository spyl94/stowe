#include "addsalle.h"
#include "ui_addsalle.h"

addsalle::addsalle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addsalle)
{
    ui->setupUi(this);
}

QString addsalle::getLine1()
{
    return ui->lineEdit->text();
}

QString addsalle::getLine2()
{
    return ui->comboBox->currentText();
}

QString addsalle::getLine3()
{
    return ui->lineEdit_3->text();
}

void addsalle::on_pushButton_clicked()
{
    close();

}

void addsalle::clean()
{
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
}

addsalle::~addsalle()
{
    delete ui;
}
