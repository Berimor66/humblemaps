/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 60006
Source Host           : localhost:3306
Source Database       : hm

Target Server Type    : MYSQL
Target Server Version : 60006
File Encoding         : 65001

Date: 2011-12-29 11:35:51
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
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_edge
-- ----------------------------

-- ----------------------------
-- Table structure for `hm_node`
-- ----------------------------
DROP TABLE IF EXISTS `hm_node`;
CREATE TABLE `hm_node` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `x` int(11) DEFAULT NULL,
  `y` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
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
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_streets
-- ----------------------------
INSERT INTO `hm_streets` VALUES ('1', '123');
INSERT INTO `hm_streets` VALUES ('2', 'ул. Революционная');
INSERT INTO `hm_streets` VALUES ('4', 'ул. Новосадовая');
INSERT INTO `hm_streets` VALUES ('5', 'ул. Потапова');

-- ----------------------------
-- Table structure for `hm_surface`
-- ----------------------------
DROP TABLE IF EXISTS `hm_surface`;
CREATE TABLE `hm_surface` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) NOT NULL,
  `coef` double NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of hm_surface
-- ----------------------------
