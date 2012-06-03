#ifndef ADDSALLE_H
#define ADDSALLE_H

#include <QDialog>

namespace Ui {
    class addsalle;
}

class addsalle : public QDialog
{
    Q_OBJECT

public:
    explicit addsalle(QWidget *parent = 0);
    ~addsalle();
    QString getLine1();
    QString getLine2();
    QString getLine3();
    void clean();
private:
    Ui::addsalle *ui;

private slots:
    void on_pushButton_clicked();
};

#endif // ADDSALLE_H
