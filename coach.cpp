#include "coach.h"
#include "ui_coach.h"

Coach::Coach(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Coach)
{
    ui->setupUi(this);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    // указываем кодировку для отображения данных

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    // указываем кодировку для отображения данных

    // с помощью QSqlQueryModel получаем в comboBox список id_patient
    QSqlQueryModel* listid = new QSqlQueryModel;
    listid->setQuery(" select p.id_coaches , p.fio, p.phone, p.qualification "
                     " from coaches as p"
                     " order by p.id_coaches");

    ui->comboBox->setModel(listid);
    ui->comboBox->setModelColumn(0);

    ui->comboBox_2->setModel(listid);
    ui->comboBox_2->setModelColumn(1);

    on_comboBox_currentIndexChanged(ui->comboBox->currentText()); //выполняем слот при запуске окна
}

Coach::~Coach()
{
    delete ui;
}

void Coach::on_comboBox_currentIndexChanged(const QString &arg1)
{

    // ФОРМИРУЕМ СТРОКУ С HTML-КОДОМ ДЛЯ СТРАНИЦЫ НА ПЕЧАТЬ

    html = "";
    QTextStream out(&html);

    // ЗАГОЛОВОК
    out << "<h2>" << tr ("Личное дело тренера № ") << arg1 << "</h2> ";

    // ПОЛУЧАЕМ ОБЩИЕ ДАННЫЕ ПАЦИЕНТА И ВЫВОДИМ ПОСТРОЧНО
    QComboBox * combo = new QComboBox;     // создаем QComboBox
    QSqlQueryModel* Cquery = new QSqlQueryModel; // Создаем модель-запроса

    // формиурем таблицу по sql-коду запроса
    Cquery->setQuery( " select p.fio, p.phone, p.qualification "
                      " from coaches as p"
                      " where p.id_coaches = " + arg1 ); // указываем запрос


    combo->setModel(Cquery);
    combo->setModelColumn(0); // выбираем столбец из запроса
    QString p_fio = combo->currentText();

    combo->setModel(Cquery);
    combo->setModelColumn(1); // выбираем столбец из запроса
    QString p_phone = combo->currentText();

    combo->setModel(Cquery);
    combo->setModelColumn(2); // выбираем столбец из запроса
    QString p_qualification = combo->currentText();

    out << "<p><b>ФИО: </b>"+p_fio+"</p>"
    "<p><b>Телефон: </b>"+p_phone+"</p>"
    "<p><b>Квалификация: </b>" +p_qualification+ "</p>"
    "<p>&nbsp;</p>";

    ui->textBrowser->document()->setHtml(html); // устанавливаем html в textBrowser
    // Содержание textBrowser пойдет на ВЫВОД QPrinter
}

void Coach::on_pushButton_clicked()
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

void Coach::on_pushButton_2_clicked()
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

void Coach::on_pushButton_3_clicked()
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

void Coach::printDocument(QPrinter* pr) // ДЛЯ ПРЕДПРОСМОТРА И ПЕЧАТИ
{
    ui->textBrowser->document()->print(pr); // вывести на устройство (предпросмотр и печать)
}

void Coach::exportDocument(QString fileName, QPrinter* pr) //
{
    pr->setOutputFileName(fileName); // указать файл
    ui->textBrowser->document()->print(pr); // вывести на устройство pdf textBrowser
}
