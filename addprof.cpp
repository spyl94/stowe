#include "addprof.h"
#include "ui_addprof.h"

addProf::addProf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addProf)
{
    ui->setupUi(this);
    ui->comboBox_2->addItem((""));
    ui->comboBox_3->addItem((""));
}

QString addProf::getLine1()
{
    return ui->lineEdit->text();
}

QString addProf::getLine2()
{
        if(ui->comboBox_2->currentText() == "")
        {
            if(ui->comboBox_3->currentText() == "")
            {
                return ui->comboBox->currentText();
            }

            else
            {
                return ui->comboBox->currentText()+","+ui->comboBox_3->currentText();
            }
        }

        if(ui->comboBox_3->currentText() == "")
        {
            return ui->comboBox->currentText()+","+ui->comboBox_2->currentText();

        }

    return ui->comboBox->currentText()+"," + ui->comboBox_2->currentText()+"," + ui->comboBox_3->currentText();
}

void addProf::load(QMap<QString, Syllabus*> syl)
{
    QMapIterator<QString, Syllabus*> i(syl);
    while (i.hasNext()){
    i.next();
    ui->comboBox->addItem(i.value()->getName());
    ui->comboBox_2->addItem(i.value()->getName());
    ui->comboBox_3->addItem(i.value()->getName());
    }

}

void addProf::clean()
{
    ui->lineEdit->clear();
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();

}

void addProf::on_pushButton_clicked()
{
    close();
}

addProf::~addProf()
{
    delete ui;
}
