#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


/*

select p.id_table as 'id', g.name as 'Группа', pc.name as 'Место проведение тренировки', p.datee as 'Дата', p.timee as ' Время ', p.weekdays as ' День недели '
from tableses as p, groupp as g, place_coaches as pc
where p.id_grouppp = g.id_g and p.id_place = pc.id_place
order by p.id_table


*/


/*

select *
from student as s, groupp as g, coaches as c
where s.id_group = g.id_g and g.id_coach = c.id_coaches
and s.id_stud = 1

*/
