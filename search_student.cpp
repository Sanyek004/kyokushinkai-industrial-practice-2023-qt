#include "search_student.h"
#include "ui_search_student.h"
#include <QSqlRelationalTableModel>

Search_Student::Search_Student(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_Student)
{
    ui->setupUi(this);

    model_find = new QSqlQueryModel; // создаем модель поиска пациента
    on_pushButton_9_clicked(); // нажимаем кнопку
    // тем самым формируем запрос со всеми данными поиска при запуске программы
}

Search_Student::~Search_Student()
{
    delete ui;
}

void Search_Student::on_pushButton_9_clicked()
{
    QString findtext = ui->lineEdit_7->text(); // получаем данные из поля поиска
    QString search; // критерий поиска

    // в зависимости от пункта comboBox будет разный критерий
    if (ui->comboBox_4->currentIndex() == 0) search = "p.fio";
    else if (ui->comboBox_4->currentIndex() == 1) search = "p.age";
    else if (ui->comboBox_4->currentIndex() == 2) search = "p.name";

    QString sql = " select p.id_stud as 'id', p.fio as 'ФИО', p.age as 'Возраст', p.name as 'Группа' "
                  " from student as p "
                  " WHERE "+search+" LIKE '%"+findtext+"%' "
                  " order by p.id_stud ";


    model_find->setQuery(sql);

    // Устанавливаем модель model_find в представление tableView
    ui->tableView_5->setModel(model_find);

    //Заставляем столбцы и строки принять минимальный размер
    ui->tableView_5->resizeColumnsToContents();
    ui->tableView_5->resizeRowsToContents();
    // Скрываем заголовки строк
    ui->tableView_5->verticalHeader()->setVisible(false);
}

void Search_Student::on_pushButton_10_clicked()
{
    QString sql = " select p.id_stud as 'id', p.fio as 'ФИО', p.age as 'Возраст', p.name as 'Группа' "
                  " from student as p "
                  " order by p.id_stud ";

    model_find->setQuery(sql);
    ui->tableView_5->setModel(model_find);
    ui->tableView_5->resizeColumnsToContents();
    ui->tableView_5->resizeRowsToContents();
    ui->tableView_5->verticalHeader()->setVisible(false);
}
