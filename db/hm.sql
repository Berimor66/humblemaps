/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 60006
Source Host           : localhost:3306
Source Database       : hm

Target Server Type    : MYSQL
Target Server Version : 60006
File Encoding         : 65001

Date: 2011-12-29 18:11:01
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `hm_car`
-- ----------------------------
DROP TABLE IF EXISTS `hm_car`;
CREATE TABLE `hm_car` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET cp1251 NOT NULL DEFAULT '',
  `fuel_id` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_car
-- ----------------------------

-- ----------------------------
-- Table structure for `hm_driver`
-- ----------------------------
DROP TABLE IF EXISTS `hm_driver`;
CREATE TABLE `hm_driver` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) CHARACTER SET cp1251 DEFAULT '',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_driver
-- ----------------------------

-- ----------------------------
-- Table structure for `hm_edge`
-- ----------------------------
DROP TABLE IF EXISTS `hm_edge`;
CREATE TABLE `hm_edge` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `street_id` int(11) NOT NULL,
  `start_id` int(11) NOT NULL,
  `end_id` int(11) NOT NULL,
  `surface_id` int(11) NOT NULL,
  `policeman` binary(255) NOT NULL,
  `map_id` int(11) NOT NULL,
  PRIMARY KEY (`id`,`map_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_edge
-- ----------------------------

-- ----------------------------
-- Table structure for `hm_fuel`
-- ----------------------------
DROP TABLE IF EXISTS `hm_fuel`;
CREATE TABLE `hm_fuel` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL DEFAULT '',
  `price` double NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_fuel
-- ----------------------------
INSERT INTO `hm_fuel` VALUES ('1', 'бензин АИ-92', '10');
INSERT INTO `hm_fuel` VALUES ('3', 'бензин АИ-98', '30');
INSERT INTO `hm_fuel` VALUES ('4', 'бензин АИ-95', '20.1');
INSERT INTO `hm_fuel` VALUES ('5', 'бензин АИ-99', '100.502');

-- ----------------------------
-- Table structure for `hm_maps`
-- ----------------------------
DROP TABLE IF EXISTS `hm_maps`;
CREATE TABLE `hm_maps` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_maps
-- ----------------------------

-- ----------------------------
-- Table structure for `hm_node`
-- ----------------------------
DROP TABLE IF EXISTS `hm_node`;
CREATE TABLE `hm_node` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `map_id` int(11) NOT NULL,
  PRIMARY KEY (`id`,`map_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_node
-- ----------------------------

-- ----------------------------
-- Table structure for `hm_streets`
-- ----------------------------
DROP TABLE IF EXISTS `hm_streets`;
CREATE TABLE `hm_streets` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_streets
-- ----------------------------
INSERT INTO `hm_streets` VALUES ('1', 'ул. Маломосковская');
INSERT INTO `hm_streets` VALUES ('2', 'ул. Гагарина');
INSERT INTO `hm_streets` VALUES ('4', 'ул. Новосадовая');
INSERT INTO `hm_streets` VALUES ('5', 'ул. Потапова');
INSERT INTO `hm_streets` VALUES ('6', 'ул. Полевая');
INSERT INTO `hm_streets` VALUES ('7', 'ул. Новополевая');

-- ----------------------------
-- Table structure for `hm_surface`
-- ----------------------------
DROP TABLE IF EXISTS `hm_surface`;
CREATE TABLE `hm_surface` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `coef` double NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_surface
-- ----------------------------
INSERT INTO `hm_surface` VALUES ('1', 'Асфальт', '600');
INSERT INTO `hm_surface` VALUES ('2', 'Грунтовка', '20');
INSERT INTO `hm_surface` VALUES ('3', 'Пористый асфальт', '40');
INSERT INTO `hm_surface` VALUES ('4', 'Мнгновенный пористый асфальт', '40');
