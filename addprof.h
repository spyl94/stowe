#ifndef ADDPROF_H
#define ADDPROF_H

#include <QDialog>
#include "stowe.h"

namespace Ui {
    class addProf;
}

class addProf : public QDialog
{
    Q_OBJECT

public:
    explicit addProf(QWidget *parent = 0);
    ~addProf();
    QString getLine1();
    QString getLine2();
    void clean();
    void load(QMap<QString, Syllabus*>);

private:
    Ui::addProf *ui;

private slots:
    void on_pushButton_clicked();

};

#endif // ADDPROF_H
