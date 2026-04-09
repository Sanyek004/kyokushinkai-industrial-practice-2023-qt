#ifndef SINGLE_H
#define SINGLE_H

#include <QWidget>

#include <QtWidgets>
#include <QtSql>
#include <QtPrintSupport>

namespace Ui {
class Single;
}

class Single : public QWidget
{
    Q_OBJECT

public:
    explicit Single(QWidget *parent = 0);
    QString html="";
    ~Single();

private:
    Ui::Single *ui;

public slots:
void printDocument(QPrinter* pr);
void exportDocument(QString fileName, QPrinter *pr);
void on_pushButton_clicked();
void on_pushButton_2_clicked();
void on_pushButton_3_clicked();
void on_comboBox_currentIndexChanged(const QString &arg1);

};

#endif // SINGLE_H
