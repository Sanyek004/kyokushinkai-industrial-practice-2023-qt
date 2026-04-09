<div align="center">
  <a href="#english">🇬🇧 English</a> | <a href="#русский">🇷🇺 Русский</a>
</div>

---

<h1 id="english">🥋 Kyokushinkai Academy Management System</h1>

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Qt](https://img.shields.io/badge/Qt5-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![MySQL](https://img.shields.io/badge/MySQL-00000F?style=for-the-badge&logo=mysql&logoColor=white)

A desktop application designed to automate the management of a sports organization (coaches, students, and training schedules). This project was developed as part of a college production practice in 2023.

## 📌 Key Features
1. **Personnel Management:** Add, edit, and delete coach profiles including their qualification levels.
2. **Student Tracking:** Manage a database of students linked to specific age groups.
3. **Scheduling:** Create and manage training schedules (date, time, weekday) with designated training locations.
4. **PDF Reports & Printing:** Generate personal files for students/coaches and export schedules directly to **PDF** or send them to a printer.
5. **Search & Filtering:** Fast database search using various criteria (Name, age, group, address, etc.).

## 🚀 How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/Sanyek004/kyokushinkai-industrial-practice-2023.git
   ```
2. Import the `database.sql` dump into your MySQL / MariaDB server.
3. Create a database user `qtuser` with the password `12345` and grant privileges to the `mydb` database (or edit the connection parameters inside `connect.h`).
4. Open the `.pro` file in **Qt Creator** (Qt 5 is required).
5. Build and run the project.

## 📸 Screenshots
*Coming Soon...*

---
---

<h1 id="русский">🥋 Система автоматизации «Академия Киокусинкай»</h1>

Десктопное приложение для автоматизации работы спортивной организации (учет тренеров, учеников и составление расписания тренировок). Проект разработан в рамках производственной практики в колледже (2023 год).

## 📌 Основной функционал
1. **Управление персоналом (Тренеры):** Добавление, редактирование, удаление тренеров и их квалификации.
2. **Учет учеников:** Ведение базы учеников с привязкой к возрастным группам.
3. **Расписание и группы:** Формирование расписания (дата, время, день недели) с указанием места проведения тренировки.
4. **Генерация отчетов:** Вывод на печать личных дел учеников/тренеров и расписания с возможностью экспорта в **PDF**.
5. **Поиск и фильтрация:** Поиск по различным критериям в таблицах (ФИО, возраст, группа, адрес и т.д.).

## 🚀 Как запустить проект
1. Склонируйте репозиторий:
   ```bash
   git clone https://github.com/Sanyek004/kyokushinkai-industrial-practice-2023.git
   ```
2. Импортируйте дамп базы данных `database.sql` в вашу СУБД (MySQL или MariaDB).
3. Создайте пользователя `qtuser` с паролем `12345` и дайте ему права на базу `mydb` (либо измените настройки подключения в файле `connect.h`).
4. Откройте файл `.pro` в **Qt Creator** (требуется версия Qt 5).
5. Соберите и запустите проект.

## 📸 Скриншоты
*Скоро появятся...*
