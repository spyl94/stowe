#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stowe.h"
#include "addprof.h"
#include "addsalle.h"
#include "addsyllabus.h"
#include "adddispo.h"
#include "viewemploi.h"
#include <QStringListModel>
#include "help.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    addProf *uiprof;
    addsalle *uisalle;
    adddispo *uidispo;
    addsyllabus *uisyllabus;
    help *uihelp;
    viewEmploi *uiemploi;
    QVector<Prof*> profs;
    QVector<Room*> rooms;
    QVector<Promo*> promos;
    QMap<QString, Syllabus*> syllabus;
    int choixVue();

private:
    Ui::MainWindow *ui;
    Stowe* admin;

private slots:
    void on_ajProf_clicked();
    void on_suProf_clicked();
    void on_ajSalle_clicked();
    void on_suSalle_clicked();
    void on_ajDispo_clicked();
    //void on_suDispo_clicked();
    void on_ajSyllabus_clicked();
    void on_suSyllabus_clicked();
    void on_viewEmploi_clicked();
    void on_generateBut_clicked();
    void on_actionAide_triggered();
};

#endif // MAINWINDOW_H
