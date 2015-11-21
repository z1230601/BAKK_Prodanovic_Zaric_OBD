-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Erstellungszeit: 10. Nov 2015 um 19:33
-- Server Version: 5.5.46-0ubuntu0.14.04.2
-- PHP-Version: 5.5.9-1ubuntu4.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Datenbank: `testdb`
--
CREATE DATABASE IF NOT EXISTS testdb;
USE testdb;
-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `testdata`
--

CREATE TABLE IF NOT EXISTS `testdata` (
  `ID` int(10) unsigned NOT NULL,
  `Name` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `testdata`
--
DELETE FROM testdata;
INSERT INTO `testdata` (`ID`, `Name`) VALUES
(1, 'Adolf'),
(2, 'Borat'),
(3, 'Caesar');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
