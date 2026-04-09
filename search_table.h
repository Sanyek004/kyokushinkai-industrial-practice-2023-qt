#ifndef SEARCH_TABLE_H
#define SEARCH_TABLE_H

#include <QWidget>
#include <QtWidgets>
#include <QtSql>

namespace Ui {
class Search_table;
}

class Search_table : public QWidget
{
    Q_OBJECT

public:
    QSqlQueryModel* model_find3;
    explicit Search_table(QWidget *parent = 0);
    ~Search_table();

private slots:
    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::Search_table *ui;
};

#endif // SEARCH_TABLE_H
