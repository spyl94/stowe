#ifndef VIEWEMPLOI_H
#define VIEWEMPLOI_H

#include <QDialog>
#include <stowe.h>
namespace Ui {
    class viewEmploi;
}

class viewEmploi : public QDialog
{
    Q_OBJECT

public:
    explicit viewEmploi(QWidget *parent = 0);
    ~viewEmploi();
    void loadEmploi(Stowe*, QString, QDate, int, QString);
    int findPos(Stowe*, QString, int);

private:
    Ui::viewEmploi *ui;
};

#endif // VIEWEMPLOI_H
