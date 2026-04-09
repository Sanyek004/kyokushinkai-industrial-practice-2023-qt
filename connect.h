#ifndef CONNECT_H
#define CONNECT_H

#include <QSqlDatabase>
#include <QTextCodec>
#include <QSqlError>
#include <QDebug>

namespace db
{
bool connect();
}

inline bool db::connect() // добавлено inline, чтобы избежать ошибок линковки при включении в несколько файлов
{
    // Создаем и выбираем тип БД MYSQL (подходит и для MariaDB)
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    // указываем кодировку для отображения данных из БД (в новых версиях Qt это часто не нужно, но оставим)
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

    db.setHostName("127.0.0.1"); // или "127.0.0.1"
    db.setPort(3306);            // Стандартный порт MariaDB

    db.setUserName("qtuser");    // Наш новый пользователь
    db.setPassword("12345");     // Пароль нового пользователя

    // указываем название БД, к которой подключаемся
    db.setDatabaseName("mydb");

    // Открываем подключение
    if (!db.open()) {
        qDebug() << "Ошибка подключения к БД:" << db.lastError().text();
        return false;
    }

    qDebug() << "Успешное подключение к БД mydb!";
    return true;
}

#endif // CONNECT_H
