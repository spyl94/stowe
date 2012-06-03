#ifndef ADDDISPO_H
#define ADDDISPO_H

#include <QDialog>
#include <Stowe.h>

namespace Ui {
    class adddispo;
}

class adddispo : public QDialog
{
    Q_OBJECT

public:
    explicit adddispo(QWidget *parent = 0);
    ~adddispo();
    QVector<Prof*> profs;
    void loadProf(QVector<Prof*>);
    QString getLine1();
    QDateTime getLine2();
    QDateTime getLine3();
    void clean();

private:
    Ui::adddispo *ui;
private slots:
    void on_pushButton_clicked();
};

#endif // ADDDISPO_H
