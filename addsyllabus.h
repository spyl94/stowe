#ifndef ADDSYLLABUS_H
#define ADDSYLLABUS_H

#include <QDialog>

namespace Ui {
    class addsyllabus;
}

class addsyllabus : public QDialog
{
    Q_OBJECT

public:
    explicit addsyllabus(QWidget *parent = 0);
    ~addsyllabus();
    QString getLine1();
    QString getLine2();
    QString getLine3();
    QString getLine4();
    void clean();

private:
    Ui::addsyllabus *ui;
private slots:
    void on_pushButton_clicked();
};

#endif // ADDSYLLABUS_H
