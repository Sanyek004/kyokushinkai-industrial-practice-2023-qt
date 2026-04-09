#include "single.h"
#include "ui_single.h"

Single::Single(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Single)
{
    ui->setupUi(this);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    // указываем кодировку для отображения данных

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    // указываем кодировку для отображения данных

    // с помощью QSqlQueryModel получаем в comboBox список id_patient
    QSqlQueryModel* listid = new QSqlQueryModel;
    listid->setQuery(" select p.id_stud , p.fio, p.age, p.id_group "
                     " from student as p"
                     " order by p.id_stud");

    ui->comboBox->setModel(listid);
    ui->comboBox->setModelColumn(0);

    ui->comboBox_2->setModel(listid);
    ui->comboBox_2->setModelColumn(1);

    on_comboBox_currentIndexChanged(ui->comboBox->currentText()); //выполняем слот при запуске окна

}

Single::~Single()
{
    delete ui;
}

void Single::on_pushButton_clicked()
{
    // Создаем QPrinter для предпросмотра
    QPrinter * printer = new QPrinter(QPrinter::HighResolution); // хорошее качество
    printer->setOrientation(QPrinter::Landscape);   // альбомный лист
    printer->setPageSize(QPrinter::A6); // можно установить от A0 до A10. Чем меньше A тем больше вместимость листа

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

void Single::printDocument(QPrinter* pr) // ДЛЯ ПРЕДПРОСМОТРА И ПЕЧАТИ
{
    ui->textBrowser->document()->print(pr); // вывести на устройство (предпросмотр и печать)
}

void Single::on_pushButton_2_clicked()
{
    // Создаем QPrinter для печати
    QPrinter * printer = new QPrinter(QPrinter::HighResolution); // хорошее качество
    printer->setOrientation(QPrinter::Landscape);   // альбомный лист
    printer->setPageSize(QPrinter::A6); // можно установить от A0 до A10. Чем меньше A тем больше вместимость листа

    // вызываем диалог печати
    QPrintDialog *dialog = new QPrintDialog (printer, this);

    // запускаем QPrintDialog
    if (dialog->exec())
    printDocument(printer); // передаем документ на печать из printer
    delete dialog;
    delete printer;

}

void Single::exportDocument(QString fileName, QPrinter* pr) //
{
    pr->setOutputFileName(fileName); // указать файл
    ui->textBrowser->document()->print(pr); // вывести на устройство pdf textBrowser
}




void Single::on_pushButton_3_clicked()
{
    // Создаем QPrinter для PDF
    QPrinter* printer2 = new QPrinter(QPrinter::HighResolution);
    printer2->setOrientation(QPrinter::Landscape);
    printer2->setPageSize(QPrinter::A6);
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

void Single::on_comboBox_currentIndexChanged(const QString &arg1)
{

    // ФОРМИРУЕМ СТРОКУ С HTML-КОДОМ ДЛЯ СТРАНИЦЫ НА ПЕЧАТЬ

    html = "";
    QTextStream out(&html);

    // ЗАГОЛОВОК
    out << "<h2>" << tr ("Личное дело ученика № ") << arg1 << "</h2> ";

    // ПОЛУЧАЕМ ОБЩИЕ ДАННЫЕ ПАЦИЕНТА И ВЫВОДИМ ПОСТРОЧНО
    QComboBox * combo = new QComboBox;     // создаем QComboBox
    QSqlQueryModel* Cquery = new QSqlQueryModel; // Создаем модель-запроса

    // формиурем таблицу по sql-коду запроса
    Cquery->setQuery( " select p.fio, p.age, p.id_group "
                      " from student as p"
                      " where  p.id_stud = " + arg1 ); // указываем запрос


    combo->setModel(Cquery);
    combo->setModelColumn(0); // выбираем столбец из запроса
    QString p_fio = combo->currentText();

    combo->setModel(Cquery);
    combo->setModelColumn(1); // выбираем столбец из запроса
    QString p_age = combo->currentText();

    combo->setModel(Cquery);
    combo->setModelColumn(2); // выбираем столбец из запроса
    QString p_group = combo->currentText();

    out << "<p><b>ФИО: </b>"+p_fio+"</p>"
    "<p><b>Возраст: </b>"+p_age+"</p>"
    "<p><b>Группа: </b>" +p_group+ "</p>"
    "<p>&nbsp;</p>";

    ui->textBrowser->document()->setHtml(html); // устанавливаем html в textBrowser
    // Содержание textBrowser пойдет на ВЫВОД QPrinter
}

