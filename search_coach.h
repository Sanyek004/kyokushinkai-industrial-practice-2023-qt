#ifndef SEARCH_COACH_H
#define SEARCH_COACH_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

namespace Ui {
class Search_coach;
}

class Search_coach : public QWidget
{
    Q_OBJECT

public:
    QSqlQueryModel* model_find2;
    explicit Search_coach(QWidget *parent = 0);
    ~Search_coach();

private slots:
    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::Search_coach *ui;
};

#endif // SEARCH_COACH_H
