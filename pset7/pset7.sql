-- MySQL dump 10.13  Distrib 5.5.46, for debian-linux-gnu (x86_64)
--
-- Host: 0.0.0.0    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.46-0ubuntu0.14.04.2

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `transaction` char(4) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `symbol` varchar(7) NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  `price` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (1,13,'BUY','2016-05-25 11:24:52','AAPL',1,97.9000),(3,13,'SELL','2016-05-25 11:26:04','FB',4,117.7000),(4,13,'SELL','2016-05-25 11:28:30','GOOG',2,720.0900),(5,13,'SELL','2016-05-25 11:54:35','AAPL',1,97.9000),(6,13,'BUY','2016-05-25 11:55:22','NKE',1,56.5900),(7,13,'SELL','2016-05-25 12:54:59','NKE',1,56.5900),(8,13,'BUY','2016-05-25 12:57:58','AAPL',18,97.9000),(9,13,'SELL','2016-05-25 12:58:19','AAPL',1,97.9000),(11,9,'SELL','2016-05-25 12:59:49','AAPL',1,97.9000),(12,13,'BUY','2016-05-25 15:55:28','AAPL',1,98.7800),(13,13,'SELL','2016-05-25 15:55:48','FB',1,118.0000),(14,13,'BUY','2016-05-25 19:39:05','GOOG',1,725.2900),(15,13,'BUY','2016-05-25 19:47:11','AAPL',1,99.5650),(16,13,'BUY','2016-05-25 19:47:42','AAPL',1,99.6101),(17,13,'BUY','2016-05-25 19:48:53','NKE',2,56.0900),(18,13,'BUY','2016-05-25 19:51:52','AAPL',3,99.5900),(19,18,'BUY','2016-05-25 19:55:26','GOOG',5,724.9500),(20,18,'BUY','2016-05-25 19:56:23','CMG',10,458.7500),(21,18,'BUY','2016-05-25 19:57:14','FB',1,117.8200),(22,18,'BUY','2016-05-25 19:59:00','WFM',50,32.1700),(23,18,'BUY','2016-05-25 20:00:22','SCHL',1,38.6800),(24,13,'BUY','2016-05-25 20:00:55','AAPL',4,99.6000),(25,9,'SELL','2016-05-25 20:04:13','AAPL',19,99.5799),(26,9,'SELL','2016-05-25 20:04:20','GOOG',1,724.3969),(27,9,'BUY','2016-05-25 20:04:29','AAPL',12,99.5700),(28,9,'BUY','2016-05-25 20:06:53','GOOG',1,724.7900);
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolios`
--

DROP TABLE IF EXISTS `portfolios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolios` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `symbol` varchar(7) NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_id` (`user_id`,`symbol`)
) ENGINE=InnoDB AUTO_INCREMENT=41 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolios`
--

LOCK TABLES `portfolios` WRITE;
/*!40000 ALTER TABLE `portfolios` DISABLE KEYS */;
INSERT INTO `portfolios` VALUES (3,10,'MSFT',5),(4,8,'NKE',1),(12,13,'AAPL',34),(13,13,'FB',10),(20,13,'PBPB',4),(28,13,'GOOG',1),(31,13,'NKE',2),(33,18,'GOOG',5),(34,18,'CMG',10),(35,18,'FB',1),(36,18,'WFM',50),(37,18,'SCHL',1),(39,9,'AAPL',12),(40,9,'GOOG',1);
/*!40000 ALTER TABLE `portfolios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL,
  `hash` varchar(255) NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'andi','$2y$10$c.e4DK7pVyLT.stmHxgAleWq4yViMmkwKz3x8XCo4b/u3r8g5OTnS',10000.0000),(2,'caesar','$2y$10$0p2dlmu6HnhzEMf9UaUIfuaQP7tFVDMxgFcVs0irhGqhOxt6hJFaa',10000.0000),(3,'eli','$2y$10$COO6EnTVrCPCEddZyWeEJeH9qPCwPkCS0jJpusNiru.XpRN6Jf7HW',10000.0000),(4,'hdan','$2y$10$o9a4ZoHqVkVHSno6j.k34.wC.qzgeQTBHiwa3rpnLq7j2PlPJHo1G',10000.0000),(5,'jason','$2y$10$ci2zwcWLJmSSqyhCnHKUF.AjoysFMvlIb1w4zfmCS7/WaOrmBnLNe',10000.0000),(6,'john','$2y$10$dy.LVhWgoxIQHAgfCStWietGdJCPjnNrxKNRs5twGcMrQvAPPIxSy',10000.0000),(7,'levatich','$2y$10$fBfk7L/QFiplffZdo6etM.096pt4Oyz2imLSp5s8HUAykdLXaz6MK',10000.0000),(8,'rob','$2y$10$3pRWcBbGdAdzdDiVVybKSeFq6C50g80zyPRAxcsh2t5UnwAkG.I.2',10000.0000),(9,'skroob','$2y$10$AxIyTyhL7/y.QfstmY2vc.CLI/tNi37mZgove3oopCoT5d.ni84Ei',8152.5950),(10,'zamyla','$2y$10$UOaRF0LGOaeHG4oaEkfO4O7vfI34B1W23WqHr9zCpXL68hfQsS3/e',10000.0000),(13,'machajew','$2y$10$UvEsRC1oApc5tzH2UURZw.KYxHhfkTeIpoFwnNPlg9ExbGQB44XYW',9181.2049),(15,'isaac','$2y$10$V/PrNaZtEMmnmjhpq.tgzeBKsmqWz6.RH9shUMkNiQgYhkQyMugAS',70000.0000),(16,'david2','$2y$10$2CNjnV/yE2Y.I4UbHud8VuxJGQMGevkDztN1OT09a3NBciFIPtDKG',5000.0000),(17,'newuser','$2y$10$O0PUqQ44hDPlMMJieeY8TOrYgGhs8U1nQge/uQ5Wad9tLkBAiKrCy',5000.0000),(18,'sarahm24','$2y$10$BikHP3TqcQ01MzsONHz89OAV3HJ2/FNXyL.susUSPgsp6cJqm9dza',55022.7500);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2016-05-25 20:09:56
