#ifndef MIXED_H
#define MIXED_H

#include <QWidget>

#include <QtWidgets>
#include <QtSql>
#include <QtPrintSupport>
#include <QPrinter>

namespace Ui {
class Mixed;
}

class Mixed : public QWidget
{
    Q_OBJECT

public:
    explicit Mixed(QWidget *parent = 0);
    QString html="";
    ~Mixed();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

     void on_comboBox_currentIndexChanged(const QString &arg1);

     void printDocument(QPrinter* pr);

     void exportDocument(QString fileName, QPrinter* pr);

private:
    Ui::Mixed *ui;


};

#endif // MIXED_H
