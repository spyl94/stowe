#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //On alloue les affichages
    uiprof = new addProf(this);
    uidispo = new adddispo(this);
    uisalle = new addsalle(this);
    uisyllabus = new addsyllabus(this);
    uiemploi = new viewEmploi(this);
    uihelp = new help(this);
    ui->setupUi(this);
    admin = new Stowe();
    admin->dump();
    admin->dumpTimeList();
    ui->dateEdit->setDate(QDate::currentDate());
    profs = admin->getProfs();
    rooms = admin->getRooms();
    promos = admin->getPromos();
    syllabus = admin->getSyllabus();




    //On affiche la liste des profs
    for (int i = 0; i < profs.size(); ++i)
        ui->listProf->addItem(profs.at(i)->dump());
    //On affiche la liste des matières
        QMapIterator<QString, Syllabus*> i(syllabus);
        while (i.hasNext()){
        i.next();
        ui->listSyllabus->addItem(i.value()->getName());
        }
    //On affiche les indispos

    //On affiche la liste des rooms
    for (int i = 0; i < rooms.size(); ++i)
        ui->listRoom->addItem(rooms.at(i)->dump());
    //On met les promos dans la box
    for(int i = 0; i < promos.size(); ++i)
        ui->boxPromo->addItem(promos.at(i)->getName());
    //vueCombo
    for(int i = 0; i < profs.size(); ++i)
        ui->vueCombo->addItem(admin->getProfs().at(i)->getName());

}

void MainWindow::on_actionAide_triggered()
{
    uihelp->exec();
}

void MainWindow::on_ajProf_clicked()
{
    uiprof->load(admin->getSyllabus());
    uiprof->exec();
    QString line1 = uiprof->getLine1();
    QString line2 = uiprof->getLine2();
    if(line1 != "")
    {
        admin->addProf(line1, line2.split(","));
        ui->listProf->clear();
        uiprof->clean();
        for (int i = 0; i < admin->getProfs().size(); ++i)
            ui->listProf->addItem(admin->getProfs().at(i)->dump());
    }
}

void MainWindow::on_suProf_clicked()
{
    admin->delProf(ui->listProf->currentRow());
    ui->listProf->clear();
    for (int i = 0; i < admin->getProfs().size(); ++i)
        ui->listProf->addItem(admin->getProfs().at(i)->dump());
}

void MainWindow::on_ajSalle_clicked()
{
    uisalle->exec();
    QString line1 = uisalle->getLine1();
    QString line2 = uisalle->getLine2();
    if(line1 != "");
    {
        RoomType type;
        if(line2=="Amphi") type = AMPHI;
        if(line2=="Td") type = TD;
        if(line2=="Tp") type = TP;
        QString line3 = uisalle->getLine3();
        admin->addRoom(line1, type, line3.toInt());
        ui->listRoom->clear();
        uisalle->clean();
        for (int i = 0; i < admin->getRooms().size(); ++i)
            ui->listRoom->addItem(admin->getRooms().at(i)->dump());
    }
}

void MainWindow::on_suSalle_clicked()
{
    admin->delRoom(ui->listRoom->currentRow());
    ui->listRoom->clear();
    for (int i = 0; i < admin->getRooms().size(); ++i)
        ui->listRoom->addItem(admin->getRooms().at(i)->dump());
}

void MainWindow::on_ajDispo_clicked()
{
    uidispo->loadProf(profs);
    uidispo->exec();
    QString line1 = uidispo->getLine1();
    QDateTime line2 = uidispo->getLine2();
    QDateTime line3 = uidispo->getLine3();
    admin->addIndispo(line1, line2, line3);
    uidispo->clean();
    //Manque l'affichage
}


void MainWindow::on_ajSyllabus_clicked()
{
    uisyllabus->exec();
    QString line1 = uisyllabus->getLine1();
    int cm = uisyllabus->getLine2().toInt();
    int tp = uisyllabus->getLine3().toInt();
    int td = uisyllabus->getLine4().toInt();
    if(line1 != "")
    {
        admin->addSyllabus(line1,cm,tp,td);
        ui->listSyllabus->clear();
        uisyllabus->clean();
        QMapIterator<QString, Syllabus*> i(admin->getSyllabus());
        while (i.hasNext()){
        i.next();
        ui->listSyllabus->addItem(i.value()->getName());
    }
    }
}

void MainWindow::on_suSyllabus_clicked()
{
        admin->delSyllabus(ui->listSyllabus->currentItem()->text());
        ui->listSyllabus->clear();
        QMapIterator<QString, Syllabus*> i(admin->getSyllabus());
        while (i.hasNext()){
        i.next();
        ui->listSyllabus->addItem(i.value()->getName());
        }
}

int MainWindow::choixVue()
{
    if(ui->vueCombo->currentText() == "Elève") return 0;
    return 1;
}

void MainWindow::on_generateBut_clicked()
{
    admin->generate();
}

void MainWindow::on_viewEmploi_clicked()
{

    uiemploi->loadEmploi(admin ,ui->boxPromo->currentText(),ui->dateEdit->date(), choixVue(), ui->vueCombo->currentText());
    uiemploi->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
