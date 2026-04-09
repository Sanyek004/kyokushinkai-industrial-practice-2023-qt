#include "search_coach.h"
#include "ui_search_coach.h"
#include <QSqlRelationalTableModel>

Search_coach::Search_coach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_coach)
{
    ui->setupUi(this);
     model_find2 = new QSqlQueryModel; // создаем модель поиска пациента
    on_pushButton_9_clicked(); // нажимаем кнопку
    // тем самым формируем запрос со всеми данными поиска при запуске программы
}

Search_coach::~Search_coach()
{
    delete ui;
}

void Search_coach::on_pushButton_9_clicked()
{
    QString findtext = ui->lineEdit_7->text(); // получаем данные из поля поиска
    QString search; // критерий поиска

    // в зависимости от пункта comboBox будет разный критерий
    if (ui->comboBox_4->currentIndex() == 0) search = "p.fio";
    else if (ui->comboBox_4->currentIndex() == 1) search = "p.phone";
    else if (ui->comboBox_4->currentIndex() == 2) search = "p.qualification";

    QString sql = " select p.id_coaches as 'id', p.fio as 'ФИО', p.phone as 'Телефон', p.qualification as 'Квалификация' "
                  " from coaches as p "
                  " WHERE "+search+" LIKE '%"+findtext+"%' "
                  " order by p.id_coaches ";


    model_find2->setQuery(sql);

    // Устанавливаем модель model_find в представление tableView
    ui->tableView_5->setModel(model_find2);

    //Заставляем столбцы и строки принять минимальный размер
    ui->tableView_5->resizeColumnsToContents();
    ui->tableView_5->resizeRowsToContents();
    // Скрываем заголовки строк
    ui->tableView_5->verticalHeader()->setVisible(false);
}

void Search_coach::on_pushButton_10_clicked()
{
    QString sql = " select p.id_coaches as 'id', p.fio as 'ФИО', p.phone as 'Телефон', p.qualification as 'Квалификация' "
                  " from coaches as p "
                  " order by p.id_coaches ";

    model_find2->setQuery(sql);
    ui->tableView_5->setModel(model_find2);
    ui->tableView_5->resizeColumnsToContents();
    ui->tableView_5->resizeRowsToContents();
    ui->tableView_5->verticalHeader()->setVisible(false);
}
