#ifndef SEARCH_STUDENT_H
#define SEARCH_STUDENT_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

namespace Ui {
class Search_Student;
}

class Search_Student : public QWidget
{
    Q_OBJECT

public:
    QSqlQueryModel* model_find;
    explicit Search_Student(QWidget *parent = 0);
    ~Search_Student();

private slots:
    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::Search_Student *ui;
};

#endif // SEARCH_STUDENT_H
