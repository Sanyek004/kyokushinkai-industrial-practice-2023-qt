-- --------------------------------------------------------
-- Хост:                         127.0.0.1
-- База данных:                  mydb
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Дамп структуры для таблицы mydb.coaches
DROP TABLE IF EXISTS `coaches`;
CREATE TABLE IF NOT EXISTS `coaches` (
  `id_coaches` int(10) NOT NULL AUTO_INCREMENT,
  `fio` varchar(200) NOT NULL,
  `phone` varchar(15) NOT NULL,
  `qualification` enum('Первая квалификационная категория','Вторая квалификационная категория','Высшая квалификационная категория') NOT NULL,
  PRIMARY KEY (`id_coaches`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- Дамп данных таблицы mydb.coaches
INSERT INTO `coaches` (`id_coaches`, `fio`, `phone`, `qualification`) VALUES
	(1, 'Сергеев Михаил Джекович', '+79005553535', 'Первая квалификационная категория'),
	(2, 'Зубков Дмитрий Васильевич', '+88002172122', 'Вторая квалификационная категория'),
	(3, 'Фонети Максим Карлович', '+30012323329', 'Высшая квалификационная категория');

-- Дамп структуры для таблицы mydb.groupp
DROP TABLE IF EXISTS `groupp`;
CREATE TABLE IF NOT EXISTS `groupp` (
  `id_g` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `category` enum('Дошкольный','Школьный','Подростковый','Взрослый') NOT NULL,
  `id_coach` int(10) DEFAULT NULL,
  PRIMARY KEY (`id_g`),
  KEY `FK_groupp_coaches` (`id_coach`),
  CONSTRAINT `FK_groupp_coaches` FOREIGN KEY (`id_coach`) REFERENCES `coaches` (`id_coaches`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- Дамп данных таблицы mydb.groupp
INSERT INTO `groupp` (`id_g`, `name`, `category`, `id_coach`) VALUES
	(1, 'Дошкольный 1', 'Дошкольный', 2),
	(2, 'Дошкольный 2', 'Дошкольный', 1),
	(3, 'Подростковый 1', 'Подростковый', 3);

-- Дамп структуры для таблицы mydb.place_coaches
DROP TABLE IF EXISTS `place_coaches`;
CREATE TABLE IF NOT EXISTS `place_coaches` (
  `id_place` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(150) NOT NULL,
  `address` varchar(150) NOT NULL,
  PRIMARY KEY (`id_place`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- Дамп данных таблицы mydb.place_coaches
INSERT INTO `place_coaches` (`id_place`, `name`, `address`) VALUES
	(1, 'Спорткомплекс Дэвис', 'ул. Дэвиса, д. 2'),
	(2, 'Арена Мишн Роу', 'ул. Мишн Роу, д. 1'),
	(3, 'Зал Ла Меса', 'ул. им. ДПСА, д. 3');

-- Дамп структуры для таблицы mydb.student
DROP TABLE IF EXISTS `student`;
CREATE TABLE IF NOT EXISTS `student` (
  `id_stud` int(10) NOT NULL AUTO_INCREMENT,
  `fio` varchar(200) NOT NULL,
  `age` varchar(2) NOT NULL,
  `id_group` int(10) DEFAULT NULL,
  PRIMARY KEY (`id_stud`),
  KEY `FK_student_groupp` (`id_group`),
  CONSTRAINT `FK_student_groupp` FOREIGN KEY (`id_group`) REFERENCES `groupp` (`id_g`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- Дамп данных таблицы mydb.student
INSERT INTO `student` (`id_stud`, `fio`, `age`, `id_group`) VALUES
	(1, 'Иванов Иван Иванович', '7', 1),
	(2, 'Смирнов Сергей Сергеевич', '9', 2),
	(3, 'Дрифтмарк Оливер Раймонович', '14', 3);

-- Дамп структуры для таблицы mydb.tableses (Расписание)
DROP TABLE IF EXISTS `tableses`;
CREATE TABLE IF NOT EXISTS `tableses` (
  `id_table` int(10) NOT NULL AUTO_INCREMENT,
  `id_grouppp` int(10) NOT NULL,
  `id_place` int(10) NOT NULL,
  `datee` date NOT NULL,
  `timee` enum('15:00','16:00','17:00','18:00','19:00','20:00') NOT NULL,
  `weekdays` enum('Понедельник','Вторник','Среда','Четверг','Пятница','Суббота','Воскресенье') NOT NULL,
  PRIMARY KEY (`id_table`),
  KEY `FK_tableses_groupp` (`id_grouppp`),
  KEY `FK_tableses_place` (`id_place`),
  CONSTRAINT `FK_tableses_place` FOREIGN KEY (`id_place`) REFERENCES `place_coaches` (`id_place`),
  CONSTRAINT `FK_tableses_groupp` FOREIGN KEY (`id_grouppp`) REFERENCES `groupp` (`id_g`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

-- Дамп данных таблицы mydb.tableses
INSERT INTO `tableses` (`id_table`, `id_grouppp`, `id_place`, `datee`, `timee`, `weekdays`) VALUES
	(1, 1, 2, '2023-05-10', '15:00', 'Среда'),
	(2, 2, 1, '2023-05-10', '17:00', 'Среда');

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
