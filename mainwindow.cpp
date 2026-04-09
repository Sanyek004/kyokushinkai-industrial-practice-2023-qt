#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connect.h"
#include "search_student.h"
#include "search_coach.h"
#include "search_table.h"
#include "mixed.h"
#include "single.h"
#include "coach.h"
#include <QSqlRelationalTableModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!db::connect()) // Если программа не соединится с БД появится следующее сообщение
    {
        QMessageBox::critical(0, "Ошибка", "Ошибка подключения к БД!");
    }

    model_coach = new QSqlRelationalTableModel;
    model_student = new QSqlRelationalTableModel;
    model_table = new QSqlRelationalTableModel;
    model_group = new QSqlRelationalTableModel;
    model_place_coaches = new QSqlRelationalTableModel;

    init(); // загружаем все модели таблицы

    ui->dateEdit->setDate(QDate::currentDate());

    connect(ui->tableView->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(init_group()));

    connect(ui->tableView_4->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(init_table()));

    connect(ui->tableView_2->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(init_group()));

    connect(ui->tableView_2->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(init_table()));

    connect(ui->tableView_5->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(init_table()));

    connect(ui->tableView_5->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this, SLOT(init_student()));




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()// Здесь будем загружать/обновлять таблицы в qt
{
    init_coach();
    init_group();
    init_student();
    init_place_coaches();
    init_table();
}

void MainWindow::init_coach()
{

    model_coach->setTable("coaches"); // таблица
    model_coach->setSort(0, Qt::AscendingOrder); // сортировка по 0-му столбцу
    model_coach->select(); // загрузить таблицу
    model_coach->setHeaderData(0, Qt::Horizontal, "ID"); // переименовать заголовки
    model_coach->setHeaderData(1, Qt::Horizontal, "ФИО");
    model_coach->setHeaderData(2, Qt::Horizontal, "Телефон");
    model_coach->setHeaderData(3, Qt::Horizontal, "Квалификация");
    model_coach->setEditStrategy(QSqlTableModel::OnFieldChange);  // автосохранение
    ui->tableView->setModel(model_coach); // установить модель в tableview
    ui->tableView->resizeColumnsToContents(); // автосжатие столбцов и строк
    ui->tableView->resizeRowsToContents();
    ui->tableView->verticalHeader()->setVisible(false); // скрыть заголовки строк
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // выделение только одного элемента


}

void MainWindow::init_student()
{


    model_student->setTable("student"); // таблица
    model_student->setSort(0, Qt::AscendingOrder); // сортировка по 0-му столбцу

    // автозамена
    model_student->setRelation(3, QSqlRelation ( "groupp", "id_g", "name"));

    model_student->select(); // загрузить таблицу
    model_student->setHeaderData(0, Qt::Horizontal, "ID"); // переименовать заголовки
    model_student->setHeaderData(1, Qt::Horizontal, "ФИО");
    model_student->setHeaderData(2, Qt::Horizontal, "Возраст");
    model_student->setHeaderData(3, Qt::Horizontal, "Группа");
    model_student->setEditStrategy(QSqlTableModel::OnFieldChange); // автосохранение

    ui->tableView_2->setModel(model_student); // установить модель в tableview
    // подключаем делегаты для автозамены
    ui->tableView_2->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_2));
    ui->tableView_2->resizeColumnsToContents(); // автосжатие столбцов и строк
    ui->tableView_2->resizeRowsToContents();
    ui->tableView_2->verticalHeader()->setVisible(false); // скрыть заголовки строк
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection); // выделение только одного элемента


    // используя sql-запрос, формируем элементы comboBox'ов из таблиц
    QSqlQueryModel* list_patient = new QSqlQueryModel;
    list_patient->setQuery( " select CONCAT ( '[', p.id_g , '] ', p.name) "
                            " from groupp as p " );
    ui->comboBox_3->setModel(list_patient);
    ui->comboBox_3->setModelColumn(0);




}

void MainWindow::init_place_coaches()
{


    model_place_coaches->setTable("place_coaches"); // таблица
    model_place_coaches->setSort(0, Qt::AscendingOrder); // сортировка по 0-му столбцу

    model_place_coaches->select(); // загрузить таблицу
    model_place_coaches->setHeaderData(0, Qt::Horizontal, "ID"); // переименовать заголовки
    model_place_coaches->setHeaderData(1, Qt::Horizontal, "Название");
    model_place_coaches->setHeaderData(2, Qt::Horizontal, "Адрес");
    model_place_coaches->setEditStrategy(QSqlTableModel::OnFieldChange); // автосохранение

    ui->tableView_4->setModel(model_place_coaches); // установить модель в tableview
    // подключаем делегаты для автозамены
    ui->tableView_4->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_4));
    ui->tableView_4->resizeColumnsToContents(); // автосжатие столбцов и строк
    ui->tableView_4->resizeRowsToContents();
    ui->tableView_4->verticalHeader()->setVisible(false); // скрыть заголовки строк
    ui->tableView_4->setSelectionMode(QAbstractItemView::SingleSelection); // выделение только одного элемента

}

void MainWindow::init_group()
{


    model_group->setTable("groupp"); // таблица
    model_group->setSort(0, Qt::AscendingOrder); // сортировка по 0-му столбцу

    // автозамена
    model_group->setRelation(3, QSqlRelation ( "coaches", "id_coaches", "fio"));

    model_group->select(); // загрузить таблицу
    model_group->setHeaderData(0, Qt::Horizontal, "ID"); // переименовать заголовки
    model_group->setHeaderData(1, Qt::Horizontal, "Название");
    model_group->setHeaderData(2, Qt::Horizontal, "Возрастная категория");
    model_group->setHeaderData(3, Qt::Horizontal, "Назначенный тренер");
    model_group->setEditStrategy(QSqlTableModel::OnFieldChange); // автосохранение

    ui->tableView_5->setModel(model_group); // установить модель в tableview
    // подключаем делегаты для автозамены
    ui->tableView_5->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_5));
    ui->tableView_5->resizeColumnsToContents(); // автосжатие столбцов и строк
    ui->tableView_5->resizeRowsToContents();
    ui->tableView_5->verticalHeader()->setVisible(false); // скрыть заголовки строк
    ui->tableView_5->setSelectionMode(QAbstractItemView::SingleSelection); // выделение только одного элемента


    QSqlQueryModel* list_coach = new QSqlQueryModel;
    list_coach->setQuery( " select CONCAT ( '[', d.id_coaches , '] ', d.fio) "
                          " from coaches as d " );
    ui->comboBox_7->setModel(list_coach);
    ui->comboBox_7->setModelColumn(0);


}

void MainWindow::init_table()
{
    // будет загрузка таблицы «Записи»
    model_table->setTable("tableses"); // таблица
    model_table->setSort(0, Qt::AscendingOrder); // сортировка по 0-му столбцу

    // автозамена
    model_table->setRelation(1, QSqlRelation ( "groupp", "id_g", "name"));
    model_table->setRelation(2, QSqlRelation ( "place_coaches", "id_place", "name"));

    model_table->select(); // загрузить таблицу
    model_table->setHeaderData(0, Qt::Horizontal, "ID"); // переименовать заголовки
    model_table->setHeaderData(1, Qt::Horizontal, "Группа");
    model_table->setHeaderData(2, Qt::Horizontal, "Место проведение тренировки");
    model_table->setHeaderData(3, Qt::Horizontal, "Дата");
    model_table->setHeaderData(4, Qt::Horizontal, "Время");
    model_table->setHeaderData(5, Qt::Horizontal, "День недели");
    model_table->setEditStrategy(QSqlTableModel::OnFieldChange); // автосохранение

    ui->tableView_3->setModel(model_table); // установить модель в tableview
    // подключаем делегаты для автозамены
    ui->tableView_3->setItemDelegate(new QSqlRelationalDelegate(ui->tableView_3));
    ui->tableView_3->resizeColumnsToContents(); // автосжатие столбцов и строк
    ui->tableView_3->resizeRowsToContents();
    ui->tableView_3->verticalHeader()->setVisible(false); // скрыть заголовки строк
    ui->tableView_3->setSelectionMode(QAbstractItemView::SingleSelection); // выделение только одного элемента


    // используя sql-запрос, формируем элементы comboBox'ов из таблиц
    QSqlQueryModel* list_group2 = new QSqlQueryModel;
    list_group2->setQuery( " select CONCAT ( '[', p.id_g , '] ', p.name) "
                           " from groupp as p " );
    ui->comboBox_4->setModel(list_group2);
    ui->comboBox_4->setModelColumn(0);



    QSqlQueryModel* list_place = new QSqlQueryModel;
    list_place->setQuery( " select CONCAT ( '[', d.id_place , '] ', d.name) "
                          " from place_coaches as d " );
    ui->comboBox_5->setModel(list_place);
    ui->comboBox_5->setModelColumn(0);

}

void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text().length() == 0) return; // проверка на пустоту

    int row = model_coach->rowCount(); // создаем строку
    model_coach->insertRow(row);

    QModelIndex col1 = model_coach->index(row, 1); // вставляем данные
    model_coach->setData(col1, ui->lineEdit->text());

    QModelIndex col2 = model_coach->index(row, 2); // вставляем данные
    model_coach->setData(col2, ui->lineEdit_2->text());

    QModelIndex col3 = model_coach->index(row, 3);
    model_coach->setData(col3, ui->comboBox->currentText());

    model_coach->submitAll(); // сохранить

    ui->lineEdit->setText(""); // очистить поле

    //qDebug() << ui->lineEdit->text() << ui->lineEdit_2->text() << ui->comboBox->currentText();

    init(); // обновляем все модели
}

void MainWindow::on_pushButton_2_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    if (index.isValid())
    {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Подтвердите",
                                          "Вы уверены?",QMessageBox::Yes|QMessageBox::No);

        mb->setButtonText(QMessageBox::Yes,"Да");
        mb->setButtonText(QMessageBox::No,"Нет");

        if (mb->exec()==QMessageBox::Yes) {

            bool status = model_coach->removeRow(index.row());
            if (status == 0)
                QMessageBox::warning(0,"Ошибка",
                                     "Удалить запись невозможно. Убедитесь что она находится в других таблицах",0,0);

            model_coach->select();
        }
    }

    init(); // обновляем все модели
}



void MainWindow::on_pushButton_3_clicked()
{
    if (ui->lineEdit_7->text().length() == 0) return; // проверка на пустоту

    int row = model_student->rowCount(); // создаем строку
    model_student->insertRow(row);

    QModelIndex col1 = model_student->index(row, 1); // вставляем данные
    model_student->setData(col1, ui->lineEdit_7->text());

    QModelIndex col2 = model_student->index(row, 2); // вставляем данные
    model_student->setData(col2, ui->spinBox->text());

    QModelIndex col3 = model_student->index(row, 3); // вставляем данные
    model_student->setData(col3, model_student->index(ui->comboBox_3->currentIndex(),0).data());

    //qDebug() << ui->lineEdit_7->text() << ui->spinBox->text() << ui->comboBox_3->currentText();


    model_student->submitAll(); // сохранить
    ui->lineEdit_7->setText(""); // очистить поле

    init(); // обновляем все модели
}

void MainWindow::on_pushButton_4_clicked()
{
    QModelIndex index = ui->tableView_2->currentIndex();

    if (index.isValid())
    {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Подтвердите",
                                          "Вы уверены?",QMessageBox::Yes|QMessageBox::No);

        mb->setButtonText(QMessageBox::Yes,"Да");
        mb->setButtonText(QMessageBox::No,"Нет");

        if (mb->exec()==QMessageBox::Yes) {

            bool status = model_student->removeRow(index.row());
            if (status == 0)
                QMessageBox::warning(0,"Ошибка",
                                     "Удалить запись невозможно. Убедитесь что она находится в других таблицах",0,0);

            model_student->select();
        }
    }

    init(); // обновляем все модели
}


void MainWindow::on_pushButton_5_clicked()
{
    if (ui->lineEdit_8->text().length() == 0) return; // проверка на пустоту
    if (ui->lineEdit_9->text().length() == 0) return; // проверка на пустоту

    int row = model_place_coaches->rowCount(); // создаем строку
    model_place_coaches->insertRow(row);

    QModelIndex col1 = model_place_coaches->index(row, 1); // вставляем данные
    model_place_coaches->setData(col1, ui->lineEdit_8->text());

    QModelIndex col2 = model_place_coaches->index(row, 2); // вставляем данные
    model_place_coaches->setData(col2, ui->lineEdit_9->text());


    model_place_coaches->submitAll(); // сохранить
    ui->lineEdit_8->setText(""); // очистить поле
    ui->lineEdit_9->setText(""); // очистить поле

    init(); // обновляем все модели
}

void MainWindow::on_pushButton_6_clicked()
{
    QModelIndex index = ui->tableView_4->currentIndex();

    if (index.isValid())
    {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Подтвердите",
                                          "Вы уверены?",QMessageBox::Yes|QMessageBox::No);

        mb->setButtonText(QMessageBox::Yes,"Да");
        mb->setButtonText(QMessageBox::No,"Нет");

        if (mb->exec()==QMessageBox::Yes) {

            bool status = model_place_coaches->removeRow(index.row());
            if (status == 0)
                QMessageBox::warning(0,"Ошибка",
                                     "Удалить запись невозможно. Убедитесь что она находится в других таблицах",0,0);

            model_place_coaches->select();
        }
    }

    init(); // обновляем все модели
}



void MainWindow::on_pushButton_7_clicked()
{
    if (ui->lineEdit_4->text().length() == 0) return; // проверка на пустоту

    int row = model_group->rowCount(); // создаем строку
    model_group->insertRow(row);

    QModelIndex col1 = model_group->index(row, 1); // вставляем данные
    model_group->setData(col1, ui->lineEdit_4->text());

    QModelIndex col2 = model_group->index(row, 2); // вставляем данные
    model_group->setData(col2, model_group->index(ui->comboBox_2->currentIndex(),0).data());

    QModelIndex col3 = model_group->index(row, 3); // вставляем данные
    model_group->setData(col3, model_group->index(ui->comboBox_7->currentIndex(),0).data());


    model_group->submitAll(); // сохранить
    ui->lineEdit_4->setText(""); // очистить поле

    init(); // обновляем все модели
}

void MainWindow::on_pushButton_8_clicked()
{
    QModelIndex index = ui->tableView_5->currentIndex();

    if (index.isValid())
    {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Подтвердите",
                                          "Вы уверены?",QMessageBox::Yes|QMessageBox::No);

        mb->setButtonText(QMessageBox::Yes,"Да");
        mb->setButtonText(QMessageBox::No,"Нет");

        if (mb->exec()==QMessageBox::Yes) {

            bool status = model_group->removeRow(index.row());
            if (status == 0)
                QMessageBox::warning(0,"Ошибка",
                                     "Удалить запись невозможно. Убедитесь что она находится в других таблицах",0,0);

            model_group->select();
        }
    }

    init(); // обновляем все модели
}



void MainWindow::on_pushButton_9_clicked()
{

    int row = model_table->rowCount(); // создаем строку
    model_table->insertRow(row);

    QModelIndex col1 = model_table->index(row, 1); // вставляем данные
    model_table->setData(col1, model_group->index(ui->comboBox_4->currentIndex(),0).data());

    QModelIndex col2 = model_table->index(row, 2); // вставляем данные
    model_table->setData(col2, model_place_coaches->index(ui->comboBox_5->currentIndex(),0).data());

    QModelIndex col3 = model_table->index(row, 3); // вставляем данные
    model_table->setData(col3, ui->dateEdit->date());

    QModelIndex col4 = model_table->index(row, 4); // вставляем данные
    model_table->setData(col4, model_table->index(ui->comboBox_8->currentIndex(),0).data());

    QModelIndex col5 = model_table->index(row, 5); // вставляем данные
    model_table->setData(col5, model_table->index(ui->comboBox_6->currentIndex(),0).data());


    //qDebug() << ui->comboBox_4->currentText() << ui->comboBox_5->currentText() << ui->dateEdit->date() << ui->comboBox_8->currentText() << ui->comboBox_6->currentText();


    model_table->submitAll(); // сохранить

    init(); // обновляем все модели
}

void MainWindow::on_pushButton_10_clicked()
{
    QModelIndex index = ui->tableView_3->currentIndex();

    if (index.isValid())
    {
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning,"Подтвердите",
                                          "Вы уверены?",QMessageBox::Yes|QMessageBox::No);

        mb->setButtonText(QMessageBox::Yes,"Да");
        mb->setButtonText(QMessageBox::No,"Нет");

        if (mb->exec()==QMessageBox::Yes) {

            bool status = model_table->removeRow(index.row());
            if (status == 0)
                QMessageBox::warning(0,"Ошибка",
                                     "Удалить запись невозможно. Убедитесь что она находится в других таблицах",0,0);

            model_table->select();
        }
    }

    init(); // обновляем все модели
}

void MainWindow::on_action_triggered()
{
    Search_Student *dlg = new Search_Student; // Создаем диалоговое окно
    dlg->show();
}

void MainWindow::on_action_2_triggered()
{
    Search_coach *dlg2 = new Search_coach; // Создаем диалоговое окно
    dlg2->show();
}

void MainWindow::on_action_3_triggered()
{
    Search_table *dlg3 = new Search_table; // Создаем диалоговое окно
    dlg3->show();
}

void MainWindow::on_action_4_triggered()
{
    Mixed *dlg = new Mixed; // Создаем диалоговое окно
    dlg->show();
}

void MainWindow::on_action_5_triggered()
{
    Single *dlg = new Single; // Создаем диалоговое окно
    dlg->show();
}

void MainWindow::on_action_6_triggered()
{
    Coach *dlg = new Coach; // Создаем диалоговое окно
    dlg->show();
}
