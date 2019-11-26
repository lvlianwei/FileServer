/*
Navicat MySQL Data Transfer

Source Server         : 192.168.195.60
Source Server Version : 50727
Source Host           : 192.168.195.60:3306
Source Database       : SECMNG

Target Server Type    : MYSQL
Target Server Version : 50727
File Encoding         : 65001

Date: 2019-11-05 17:19:28
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for SECNODE
-- ----------------------------
DROP TABLE IF EXISTS `SECNODE`;
CREATE TABLE `SECNODE` (
  `id` char(4) NOT NULL,
  `name` varchar(128) NOT NULL,
  `nodedesc` varchar(512) DEFAULT NULL,
  `createtime` datetime DEFAULT NULL,
  `authcode` double(12,0) DEFAULT NULL,
  `state` int(4) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of SECNODE
-- ----------------------------
