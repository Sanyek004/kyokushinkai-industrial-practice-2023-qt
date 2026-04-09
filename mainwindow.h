#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlRelationalTableModel * model_coach;
    QSqlRelationalTableModel * model_student;
    QSqlRelationalTableModel * model_table;
    QSqlRelationalTableModel * model_group;
    QSqlRelationalTableModel * model_place_coaches;
//    QSqlQueryModel* list_coach;
//    QSqlQueryModel* list_group1;
//    QSqlQueryModel* list_group2;
//    QSqlQueryModel* list_place;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void init();
    void init_coach();
    void init_student();
    void init_table();
    void init_group();
    void init_place_coaches();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();
    void on_action_5_triggered();
    void on_action_6_triggered();
};

#endif // MAINWINDOW_H
