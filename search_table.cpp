#include "search_table.h"
#include "ui_search_table.h"
#include <QSqlRelationalTableModel>

Search_table::Search_table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_table)
{
    ui->setupUi(this);

    model_find3 = new QSqlQueryModel; // создаем модель поиска пациента
    on_pushButton_9_clicked(); // нажимаем кнопку
    // тем самым формируем запрос со всеми данными поиска при запуске программы
}

Search_table::~Search_table()
{
    delete ui;
}

void Search_table::on_pushButton_10_clicked()
{
    QString sql = " select p.id_table as 'id', g.name as 'Группа', pc.name as 'Место проведение тренировки', p.datee as 'Дата', p.timee as ' Время ', p.weekdays as ' День недели ' "
            " from tableses as p, groupp as g, place_coaches as pc "
            " where p.id_grouppp = g.id_g and p.id_place = pc.id_place "
            " order by p.id_table ";

    model_find3->setQuery(sql);
    ui->tableView_5->setModel(model_find3);
    ui->tableView_5->resizeColumnsToContents();
    ui->tableView_5->resizeRowsToContents();
    ui->tableView_5->verticalHeader()->setVisible(false);
}

void Search_table::on_pushButton_9_clicked()
{
    QString findtext = ui->lineEdit_7->text(); // получаем данные из поля поиска
    QString search; // критерий поиска

    // в зависимости от пункта comboBox будет разный критерий
    if (ui->comboBox_4->currentIndex() == 0) search = "g.name";
    else if (ui->comboBox_4->currentIndex() == 1) search = "pc.name";
    else if (ui->comboBox_4->currentIndex() == 2) search = "p.date";
    else if (ui->comboBox_4->currentIndex() == 3) search = "p.time";
    else if (ui->comboBox_4->currentIndex() == 4) search = "p.weekday";

    QString sql = " select p.id_table as 'id', g.name as 'Группа', pc.name as 'Место проведение тренировки', p.datee as 'Дата', p.timee as ' Время ', p.weekdays as ' День недели ' "
            " from tableses as p, groupp as g, place_coaches as pc "
            " where p.id_grouppp = g.id_g and p.id_place = pc.id_place "
              " and "+search+" LIKE '%"+findtext+"%' "
                  " order by p.id_table ";


    model_find3->setQuery(sql);

    // Устанавливаем модель model_find в представление tableView
    ui->tableView_5->setModel(model_find3);

    //Заставляем столбцы и строки принять минимальный размер
    ui->tableView_5->resizeColumnsToContents();
    ui->tableView_5->resizeRowsToContents();
    // Скрываем заголовки строк
    ui->tableView_5->verticalHeader()->setVisible(false);
}
