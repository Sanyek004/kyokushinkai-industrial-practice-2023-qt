<div align="center">
  <strong>🇬🇧 English</strong> | <a href="README.ru.md">🇷🇺 Русский</a>
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
