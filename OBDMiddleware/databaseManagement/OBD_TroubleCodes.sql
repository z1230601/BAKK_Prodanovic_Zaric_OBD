-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Erstellungszeit: 07. Nov 2015 um 19:34
-- Server Version: 5.5.46-0ubuntu0.14.04.2
-- PHP-Version: 5.5.9-1ubuntu4.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Datenbank: `OBD_TroubleCodes`
--

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Body`
--

CREATE TABLE IF NOT EXISTS `Body` (
  `ID` int(10) unsigned NOT NULL,
  `ID_CodeClass` int(10) unsigned NOT NULL,
  `ID_Source` int(10) unsigned NOT NULL,
  `ShortDescription` text,
  `Diagnosis` text,
  PRIMARY KEY (`ID`),
  KEY `fk_cc` (`ID_CodeClass`),
  KEY `fk_src` (`ID_Source`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Chassis`
--

CREATE TABLE IF NOT EXISTS `Chassis` (
  `ID` int(10) unsigned NOT NULL,
  `ID_CodeClass` int(10) unsigned NOT NULL,
  `ID_Source` int(10) unsigned NOT NULL,
  `ShortDescription` text,
  `Diagnosis` text,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `fk_cc` (`ID_CodeClass`),
  KEY `fk_src` (`ID_Source`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `CodeClass`
--

CREATE TABLE IF NOT EXISTS `CodeClass` (
  `ID` int(10) unsigned NOT NULL,
  `Property` text,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `CodeClass`
--

INSERT INTO `CodeClass` (`ID`, `Property`) VALUES
(0, 'Generic'),
(1, 'Manufacturer specific'),
(2, 'Generic'),
(3, 'Generic');

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Network`
--

CREATE TABLE IF NOT EXISTS `Network` (
  `ID` int(10) unsigned NOT NULL,
  `ID_CodeClass` int(10) unsigned NOT NULL,
  `ID_Source` int(10) unsigned NOT NULL,
  `ShortDescription` text,
  `Diagnosis` text,
  PRIMARY KEY (`ID`),
  UNIQUE KEY `fk_src` (`ID_Source`),
  KEY `fk_cc` (`ID_CodeClass`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Powertrain`
--

CREATE TABLE IF NOT EXISTS `Powertrain` (
  `ID` int(10) unsigned NOT NULL,
  `ID_CodeClass` int(10) unsigned NOT NULL,
  `ID_Source` int(10) unsigned NOT NULL,
  `ShortDescription` text,
  `Diagnosis` text,
  PRIMARY KEY (`ID`),
  KEY `fk_cc` (`ID_CodeClass`),
  KEY `fk_src` (`ID_Source`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Tabellenstruktur für Tabelle `Source`
--

CREATE TABLE IF NOT EXISTS `Source` (
  `ID` int(10) unsigned NOT NULL,
  `Name` text,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Daten für Tabelle `Source`
--

INSERT INTO `Source` (`ID`, `Name`) VALUES
(1, 'Fuel & Air Metering'),
(2, 'Fuel & Air Metering (Injector Circuit)'),
(3, 'Ignition System or Misfire'),
(4, 'Auxilliary Emission Controls'),
(5, 'Vehicle Speed Control & Idle Control System'),
(6, 'Computer Output Circuit'),
(7, 'Transmission'),
(8, 'Transmission');

--
-- Constraints der exportierten Tabellen
--

--
-- Constraints der Tabelle `Body`
--
ALTER TABLE `Body`
  ADD CONSTRAINT `Body_ibfk_2` FOREIGN KEY (`ID_Source`) REFERENCES `Source` (`ID`),
  ADD CONSTRAINT `Body_ibfk_1` FOREIGN KEY (`ID_CodeClass`) REFERENCES `CodeClass` (`ID`);

--
-- Constraints der Tabelle `Chassis`
--
ALTER TABLE `Chassis`
  ADD CONSTRAINT `Chassis_ibfk_2` FOREIGN KEY (`ID_Source`) REFERENCES `Source` (`ID`),
  ADD CONSTRAINT `Chassis_ibfk_1` FOREIGN KEY (`ID_CodeClass`) REFERENCES `CodeClass` (`ID`);

--
-- Constraints der Tabelle `Network`
--
ALTER TABLE `Network`
  ADD CONSTRAINT `Network_ibfk_2` FOREIGN KEY (`ID_Source`) REFERENCES `Source` (`ID`),
  ADD CONSTRAINT `Network_ibfk_1` FOREIGN KEY (`ID_CodeClass`) REFERENCES `CodeClass` (`ID`);

--
-- Constraints der Tabelle `Powertrain`
--
ALTER TABLE `Powertrain`
  ADD CONSTRAINT `Powertrain_ibfk_2` FOREIGN KEY (`ID_Source`) REFERENCES `Source` (`ID`),
  ADD CONSTRAINT `Powertrain_ibfk_1` FOREIGN KEY (`ID_CodeClass`) REFERENCES `CodeClass` (`ID`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
