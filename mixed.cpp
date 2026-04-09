#include "mixed.h"
#include "ui_mixed.h"

Mixed::Mixed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mixed)
{
    ui->setupUi(this);

    setWindowTitle("Mixed");

    // с помощью QSqlQueryModel получаем в comboBox список id_student
    QSqlQueryModel* listid = new QSqlQueryModel;
    listid->setQuery(" select p.id_table , p.id_grouppp, p.id_place, p.datee, p.timee, p.weekdays"
                     " from tableses as p"
                     " order by p.id_table");

    ui->comboBox->setModel(listid); // идентификатор записи
    ui->comboBox->setModelColumn(0);

    ui->comboBox_2->setModel(listid);
    ui->comboBox_2->setModelColumn(1);

    on_comboBox_currentIndexChanged(ui->comboBox->currentText()); //выполняем слот при запуске окна


}

Mixed::~Mixed()
{
    delete ui;
}


void Mixed::on_comboBox_currentIndexChanged(const QString &arg1)
{
    // ФОРМИРУЕМ СТРОКУ С HTML-КОДОМ ДЛЯ СТРАНИЦЫ НА ПЕЧАТЬ

    html = "";
    QTextStream out(&html);

    // ЗАГОЛОВОК
    out << "<h2>" << tr ("Расписание № ") << arg1 << "</h2> ";

    // ПОЛУЧАЕМ ОБЩИЕ ДАННЫЕ ПАЦИЕНТА И ВЫВОДИМ ПОСТРОЧНО
    QComboBox * combo = new QComboBox;     // создаем QComboBox
    QSqlQueryModel* Cquery = new QSqlQueryModel; // Создаем модель-запроса

    // формиурем таблицу по sql-коду запроса
    Cquery->setQuery( " SELECT p.id_grouppp, p.id_place, p.datee, p.timee, p.weekdays"
                      " from tableses as p"
                      " where p.id_table = " + arg1 ); // указываем запрос


    combo->setModel(Cquery);
    combo->setModelColumn(0); // выбираем столбец из запроса
    QString p_id_grouppp = combo->currentText();

    combo->setModel(Cquery);
    combo->setModelColumn(1); // выбираем столбец из запроса
    QString p_id_place = combo->currentText();

    combo->setModel(Cquery);
    combo->setModelColumn(2); // выбираем столбец из запроса
    QString p_datee = combo->currentText();

    combo->setModel(Cquery);
    combo->setModelColumn(3); // выбираем столбец из запроса
    QString p_timee = combo->currentText();

    combo->setModel(Cquery);
    combo->setModelColumn(4); // выбираем столбец из запроса
    QString p_weekdays = combo->currentText();

    out << "<p><b>Группа: </b>"+p_id_grouppp+"</p>"
    "<p><b>Место проведения тренировки: </b>"+p_id_place+"</p>"
    "<p><b>Дата: </b>" +p_datee+ "</p>"
    "<p><b>Назначенное время: </b>" +p_timee+ "</p>"
    "<p><b>День недели: </b>" +p_weekdays+ "</p>"
    "<p>&nbsp;</p>";

    ui->textBrowser->document()->setHtml(html); // устанавливаем html в textBrowser
    // Содержание textBrowser пойдет на ВЫВОД QPrinter
}


void Mixed::on_pushButton_clicked()
{
    // Создаем QPrinter для предпросмотра
        QPrinter * printer = new QPrinter(QPrinter::HighResolution); // хорошее качество
        printer->setOrientation(QPrinter::Landscape);   // альбомный лист
        printer->setPageSize(QPrinter::A4); // можно установить от A0 до A10. Чем меньше A тем больше вместимость листа

        //Создаем QPrintPreviewDialog
        QPrintPreviewDialog  * printPreviewDialog = new QPrintPreviewDialog(printer, this);

        // получаем текущие размеры экрана и устанавливаем их для QPrintPreviewDialog
        QSize size = qApp->desktop()->availableGeometry().size();
        printPreviewDialog->resize(size);

        // соединияем сигнал paintRequested в QPrintPreviewDialog со слотом printDocument
        connect(printPreviewDialog, SIGNAL(paintRequested(QPrinter*)),
                this, SLOT(printDocument(QPrinter*)));
        // запускаем QPrintPreviewDialog
        printPreviewDialog->exec();

        // удаляем QPrintPreviewDialog после закрытия
        delete printPreviewDialog;
        delete printer;
}

void Mixed::printDocument(QPrinter* pr) // ДЛЯ ПРЕДПРОСМОТРА И ПЕЧАТИ
{
    ui->textBrowser->document()->print(pr); // вывести на устройство (предпросмотр и печать)
}


void Mixed::on_pushButton_2_clicked()
{
    // Создаем QPrinter для печати
        QPrinter * printer = new QPrinter(QPrinter::HighResolution); // хорошее качество
        printer->setOrientation(QPrinter::Landscape);   // альбомный лист
        printer->setPageSize(QPrinter::A4); // можно установить от A0 до A10. Чем меньше A тем больше вместимость листа

        // вызываем диалог печати
        QPrintDialog *dialog = new QPrintDialog (printer, this);

        // запускаем QPrintDialog
        if (dialog->exec())
            printDocument(printer); // передаем документ на печать из printer
        delete dialog;
        delete printer;
}

void Mixed::exportDocument(QString fileName, QPrinter* pr) //
{
    pr->setOutputFileName(fileName); // указать файл
    ui->textBrowser->document()->print(pr); // вывести на устройство pdf textBrowser
}

void Mixed::on_pushButton_3_clicked()
{
    // Создаем QPrinter для PDF
    QPrinter* printer2 = new QPrinter(QPrinter::HighResolution);
    printer2->setOrientation(QPrinter::Landscape);
    printer2->setPageSize(QPrinter::A4);
    printer2->setOutputFormat(QPrinter::PdfFormat);


    // получаем в fileName путь сохранения после QFileDialog
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Сохранить как..."),
                                                    "new.pdf",
                                                    tr("PDF (*.pdf)"));

    // Если путь не пустой то сохраняем document в pdf
    if(!fileName.isEmpty())
    {
        exportDocument(fileName,printer2);
    }
    delete printer2;

}
