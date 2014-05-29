CREATE DATABASE lyricDb CHARSET=utf8;
USE lyricDb;

-- Table structure for table `associations`
CREATE TABLE `associations` (
  `id` int(11) NOT NULL auto_increment,
  `playlist` int(11) NOT NULL default '0',
  `imagename` varchar(255) NOT NULL default '',
  `absoluteparent` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) DEFAULT CHARSET=utf8; 

-- Table structure for table `audit`
CREATE TABLE `audit` (
  `id` int(11) NOT NULL auto_increment,
  `songid` int(11) NOT NULL default '0',
  `playdate` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`id`)
) DEFAULT CHARSET=utf8;

-- Table structure for table `lyricMain`
CREATE TABLE `lyricMain` (
  `id` int(11) NOT NULL auto_increment,
  `title` varchar(100) NOT NULL default '',
  `songnum` int(11) default '0',
  `book` varchar(100) default '',
  `artist` varchar(100) default '',
  `written` timestamp NOT NULL default '0000-00-00 00:00:00',
  `keywords` text,
  `entered` timestamp NOT NULL default '0000-00-00 00:00:00',
  `copyright` varchar(100) default '',
  PRIMARY KEY  (`id`)
) DEFAULT CHARSET=utf8;

-- Table structure for table `page`
CREATE TABLE `page` (
  `pageid` int(11) NOT NULL auto_increment,
  `songid` int(11) NOT NULL default '0',
  `pagenum` int(11) NOT NULL default '0',
  `pagetitle` varchar(100) default '',
  `lyrics` text,
  PRIMARY KEY  (`pageid`)
) DEFAULT CHARSET=utf8;

-- Table structure for table `playlist`
CREATE TABLE `playlist` (
  `playorder` int(11) NOT NULL default '0',
  `playlist` int(11) NOT NULL default '1',
  `data` varchar(256) default NULL,
  `type` varchar(4) default 'song',
  `transition` int(11) default '0',
  `snapshot` mediumblob,
  PRIMARY KEY  (`playorder`)
) DEFAULT CHARSET=utf8;

-- Table structure for table `playlists`
CREATE TABLE `playlists` (
  `id` int(11) NOT NULL default '1',
  `title` varchar(50) NOT NULL default '',
  `ref` varchar(50) NOT NULL default '',
  `profile` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`id`)
) DEFAULT CHARSET=utf8;

-- Table structure for table `config`
CREATE TABLE `config` (
  `id` int(11) NOT NULL auto_increment,
  `profile` varchar(50) NOT NULL default '',
  `config_key` varchar(50) NOT NULL default '',
  `config_value` varchar(250) default '',
  PRIMARY KEY  (`id`)
) DEFAULT CHARSET=utf8;

-- Table structure for table `config_old`
CREATE TABLE `config_old` (
  `id` int(11) NOT NULL auto_increment,
  `profile` varchar(50) NOT NULL default '',
  `config_key` varchar(50) NOT NULL default '',
  `config_value` varchar(250) default '',
  PRIMARY KEY  (`id`)
) DEFAULT CHARSET=utf8;

-- Table structure for table `status`
CREATE TABLE `status` (
  `host` varchar(50) NOT NULL default '',
  `title` varchar(50) NOT NULL default '',
  `lastupdate` timestamp NOT NULL default '0000-00-00 00:00:00',
  `profile` varchar(50) NOT NULL default '',
  `type` varchar(50) NOT NULL default 'normal',
  `ip` varchar(16) NOT NULL default '',
  `ref` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`host`)
) DEFAULT CHARSET=utf8;


-- Table structure for table `profiles`
CREATE TABLE `profiles` (
  `host` varchar(50) NOT NULL default '',
  `profile` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`host`)
) DEFAULT CHARSET=utf8;


-- Baseline Data
INSERT INTO lyricMain VALUES (1,'Today\'s Announcements',0,'Not Songs','',20040307192037 ,'',00000000000000,'');
INSERT INTO page VALUES (1,1,1,'', 'Here are todays announcements');
INSERT INTO lyricMain VALUES (2,'Sample Song',0,'Sample Songbook','',20040307192037 ,'',00000000000000,'');
INSERT INTO page VALUES (2,2,1,'Verse 1', 'This is a sample song');
INSERT INTO page VALUES (3,2,2,'Chorus', 'This is the second page of the a sample song');
INSERT INTO playlists VALUES (1,'Main Playlist','','Default');
INSERT INTO `config` VALUES (1,'','Audit','1');
INSERT INTO `config` VALUES (2,'','BGDirectory','');
INSERT INTO `config` VALUES (3,'','BGImage','db;1');
INSERT INTO `config` VALUES (4,'','CentreX','0');
INSERT INTO `config` VALUES (5,'','CentreY','1');
INSERT INTO `config` VALUES (6,'','Colour','#ffffff');
INSERT INTO `config` VALUES (7,'','DatabaseType','mysql');
INSERT INTO `config` VALUES (8,'','DBHost','localhost');
INSERT INTO `config` VALUES (9,'','DefaultTransition','Fade');
INSERT INTO `config` VALUES (10,'','DefBible','');
INSERT INTO `config` VALUES (11,'','DynamicPreview','1');
INSERT INTO `config` VALUES (12,'','ExpandNew','0');
INSERT INTO `config` VALUES (13,'','Footer','Sans 20');
INSERT INTO `config` VALUES (14,'','FrameLeft','327');
INSERT INTO `config` VALUES (15,'','FrameRight','259');
INSERT INTO `config` VALUES (16,'','GeometryOverride','');
INSERT INTO `config` VALUES (17,'','Header','Sans 20');
INSERT INTO `config` VALUES (18,'','Height','768');
INSERT INTO `config` VALUES (19,'','HighlightColour','yellow');
INSERT INTO `config` VALUES (20,'','HorizontalLocation','Centre');
INSERT INTO `config` VALUES (21,'','IgnoreMouse','0');
INSERT INTO `config` VALUES (22,'','ImageDirectory','');
INSERT INTO `config` VALUES (23,'','Justification','Left');
INSERT INTO `config` VALUES (24,'','Loop','1');
INSERT INTO `config` VALUES (25,'','Main','Sans 40');
INSERT INTO `config` VALUES (26,'','Miniview','0');
INSERT INTO `config` VALUES (27,'','OSD','Sans 30');
INSERT INTO `config` VALUES (28,'','OverscanH','0');
INSERT INTO `config` VALUES (29,'','OverscanV','0');
INSERT INTO `config` VALUES (30,'','Preset1','Used with permission CCLI 23232');
INSERT INTO `config` VALUES (31,'','Preset2','Used without permission');
INSERT INTO `config` VALUES (32,'','ProjectorHost','localhost');
INSERT INTO `config` VALUES (33,'','ShadowColour','#000000');
INSERT INTO `config` VALUES (34,'','ShadowSize','1');
INSERT INTO `config` VALUES (35,'','SpecialBack','Solid');
INSERT INTO `config` VALUES (36,'','SpecialImage','Solid');
INSERT INTO `config` VALUES (37,'','SpecialSong','Today\'s Announcements');
INSERT INTO `config` VALUES (38,'','TrayIcons','1');
INSERT INTO `config` VALUES (39,'','VerticalLocation','Centre');
INSERT INTO `config` VALUES (40,'','Width','1024');
INSERT INTO `config` VALUES (41,'','Xinerama','1');
INSERT INTO `config` VALUES (42,'','App','Load Lyricue Display;lyricue_display');
INSERT INTO `config` VALUES (43,'','App','Close Lyricue Display;lyricue_remote close');
INSERT INTO `config` VALUES (44,'','App','OpenOffice Impress;ooimpress');
INSERT INTO `config` VALUES (45,'','App','Movie Player;totem');
