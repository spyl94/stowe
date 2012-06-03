#include "addsyllabus.h"
#include "ui_addsyllabus.h"

addsyllabus::addsyllabus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addsyllabus)
{
    ui->setupUi(this);
}

QString addsyllabus::getLine1()
{
    return ui->lineEdit->text();
}

QString addsyllabus::getLine2()
{
    return ui->spinBox->text();
}

QString addsyllabus::getLine3()
{
    return ui->spinBox_2->text();
}
QString addsyllabus::getLine4()
{
    return ui->spinBox_3->text();
}

void addsyllabus::clean()
{
    ui->lineEdit->clear();
    ui->spinBox->clear();
    ui->spinBox_2->clear();
    ui->spinBox_3->clear();
}

void addsyllabus::on_pushButton_clicked()
{
    close();
}

addsyllabus::~addsyllabus()
{
    delete ui;
}
