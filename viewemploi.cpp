#include "viewemploi.h"
#include "ui_viewemploi.h"
#include <QColor>

viewEmploi::viewEmploi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewEmploi)
{
    ui->setupUi(this);
}

int viewEmploi::findPos(Stowe *admin, QString grp, int prom)
{
    for(int i = 0; i < admin->getPromos().at(prom)->get().size(); ++i)
    {
        if(admin->getPromos().at(prom)->get().at(i)->getName() == grp) return i+1;
        if(admin->getPromos().at(prom)->getName() == grp) return -1;
    }
    return -2;
}

void viewEmploi::loadEmploi(Stowe *admin, QString _promo, QDate _day, int _view, QString _prof)
{
    ui->affEmploi->clearContents();
    int prom, col, ligne;
    int cpt = 0;
    QDate day = _day;

    QTime sample(8,0);
    QColor gray("lightGray");
    QBrush color(gray);

    //Affichage eleve
    if(_view == 0)
    {
        for(int i = 0; i < admin->getPromos().size(); ++i)
        {
            if (admin->getPromos().at(i)->getName() == _promo) prom = i;
        }

        for(int i = 0; i < (7*(admin->getPromos().at(prom)->get().size())); i++)
        {
            if (i%admin->getPromos().at(prom)->get().size() == 0)
            {
                ui->affEmploi->insertColumn(i);
                QTableWidgetItem *item = new QTableWidgetItem(day.toString("dddd dd/MM/yy"));
                ui->affEmploi->setHorizontalHeaderItem(i, item);
                day = day.addDays(1);
            }
            else
            {
                ui->affEmploi->insertColumn(i);
                QTableWidgetItem *item = new QTableWidgetItem("");
                ui->affEmploi->setHorizontalHeaderItem(i, item);
            }
        }

        for(int j = 0; j < 7; ++j)
        {
            for(int i = 0; i < admin->getPromos().at(prom)->get().size(); ++i)
            {
                QTableWidgetItem *item = new QTableWidgetItem(admin->getPromos().at(prom)->get().at(i)->getName());
                ui->affEmploi->setItem(0, cpt, item);
                cpt++;
            }
        }

        for(int tim = 0; tim < admin->getTimeList().size(); ++tim)
        {

            if ((admin->getTimeList().at(tim)->getDebut().date().daysTo(_day) <= 0) && (admin->getTimeList().at(tim)->getDebut().date().daysTo(_day) > -7 ))
            {


                    if (findPos(admin, admin->getTimeList().at(tim)->getPeople()->getName(), prom) > -2)
                    {

                        col = admin->getTimeList().at(tim)->getDebut().date().daysTo(_day) * admin->getPromos().at(prom)->get().size() * (-1) + findPos(admin, admin->getTimeList().at(tim)->getPeople()->getName(), prom);
                        if (findPos(admin, admin->getTimeList().at(tim)->getPeople()->getName(), prom) == -1)
                        {
                            col++;
                            for(int i = col; i < col + admin->getPromos().at(prom)->get().size(); ++i)
                            {
                                for (int k = (-admin->getTimeList().at(tim)->getDebut().time().secsTo(sample))/900 +1; k <= (-admin->getTimeList().at(tim)->getFin().time().secsTo(sample))/900 ; k++)
                                {
                                    QTableWidgetItem *item = new QTableWidgetItem("");
                                    item->setBackground(color);
                                    ui->affEmploi->setItem(k, i, item);
                                }
                                ligne = (-admin->getTimeList().at(tim)->getDebut().time().secsTo(sample))/900;
                                QTableWidgetItem *item1 = new QTableWidgetItem(admin->getTimeList().at(tim)->getLesson()->getName());
                                item1->setBackground(color);
                                ui->affEmploi->setItem(ligne+1, i, item1);
                                ligne = (-admin->getTimeList().at(tim)->getFin().time().secsTo(sample))/900;
                                QTableWidgetItem *item2 = new QTableWidgetItem(admin->getTimeList().at(tim)->getRoom()->getName());
                                item2->setBackground(color);
                                ui->affEmploi->setItem(ligne, i, item2);
                            }
                        }
                        else
                        {
                            for (int k = (-admin->getTimeList().at(tim)->getDebut().time().secsTo(sample))/900 +1; k <= (-admin->getTimeList().at(tim)->getFin().time().secsTo(sample))/900 ; k++)
                            {
                                QTableWidgetItem *item = new QTableWidgetItem("");
                                item->setBackground(color);
                                ui->affEmploi->setItem(k, col-1, item);
                            }
                            ligne = (-admin->getTimeList().at(tim)->getDebut().time().secsTo(sample))/900;
                            QTableWidgetItem *item1 = new QTableWidgetItem(admin->getTimeList().at(tim)->getLesson()->getName());
                            item1->setBackground(color);
                            ui->affEmploi->setItem(ligne+1, col-1, item1);
                            ligne = (-admin->getTimeList().at(tim)->getFin().time().secsTo(sample))/900;
                            QTableWidgetItem *item2 = new QTableWidgetItem(admin->getTimeList().at(tim)->getRoom()->getName());
                            item2->setBackground(color);
                            ui->affEmploi->setItem(ligne, col-1, item2);
                        }
                    }

            }
        }
    }

    else
    {
        setWindowTitle(_prof);
        for(int i = 0; i<7; i++)
        {
            ui->affEmploi->insertColumn(i);
            QTableWidgetItem *item = new QTableWidgetItem(day.toString("dddd dd/MM/yy"));
            ui->affEmploi->setHorizontalHeaderItem(i, item);
            day = day.addDays(1);
        }
        for(int tim = 0; tim < admin->getTimeList().size(); ++tim)
        {
            if ((admin->getTimeList().at(tim)->getDebut().date().daysTo(_day) <= 0) && (admin->getTimeList().at(tim)->getDebut().date().daysTo(_day) > -7 ))
            {
                if(admin->getTimeList().at(tim)->getProf()->getName() == _prof)
                {

                    col = -admin->getTimeList().at(tim)->getDebut().date().daysTo(_day);

                    for (int k = (-admin->getTimeList().at(tim)->getDebut().time().secsTo(sample))/900 +1; k <= (-admin->getTimeList().at(tim)->getFin().time().secsTo(sample))/900 ; k++)
                    {
                        QTableWidgetItem *item = new QTableWidgetItem("");
                        item->setBackground(color);
                        ui->affEmploi->setItem(k, col, item);
                    }
                    ligne = (-admin->getTimeList().at(tim)->getDebut().time().secsTo(sample))/900;
                    QTableWidgetItem *item1 = new QTableWidgetItem(admin->getTimeList().at(tim)->getLesson()->getName());
                    item1->setBackground(color);
                    ui->affEmploi->setItem(ligne+1, col, item1);
                    ligne = (-admin->getTimeList().at(tim)->getFin().time().secsTo(sample))/900;
                    QTableWidgetItem *item2 = new QTableWidgetItem(admin->getTimeList().at(tim)->getRoom()->getName());
                    item2->setBackground(color);
                    ui->affEmploi->setItem(ligne, col, item2);
                }
            }
        }
    }

}

viewEmploi::~viewEmploi()
{
    delete ui;
}
