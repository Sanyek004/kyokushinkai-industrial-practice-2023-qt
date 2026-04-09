#ifndef COACH_H
#define COACH_H

#include <QWidget>

#include <QtWidgets>
#include <QtSql>
#include <QtPrintSupport>

namespace Ui {
class Coach;
}

class Coach : public QWidget
{
    Q_OBJECT

public:
    explicit Coach(QWidget *parent = 0);
    QString html="";
    ~Coach();

private:
    Ui::Coach *ui;

public slots:
void printDocument(QPrinter* pr);
void exportDocument(QString fileName, QPrinter *pr);
void on_pushButton_clicked();
void on_pushButton_2_clicked();
void on_pushButton_3_clicked();
void on_comboBox_currentIndexChanged(const QString &arg1);
};

#endif // COACH_H
