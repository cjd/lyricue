CREATE DATABASE lyricDb;
USE lyricDb;

-- Table structure for table `associations`
CREATE TABLE `associations` (
  `id` int(11) NOT NULL auto_increment,
  `playlist` int(11) NOT NULL default '0',
  `imagename` varchar(255) NOT NULL default '',
  `absoluteparent` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
); 

-- Table structure for table `audit`
CREATE TABLE `audit` (
  `id` int(11) NOT NULL auto_increment,
  `songid` int(11) NOT NULL default '0',
  `playdate` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`id`)
);

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
);

-- Table structure for table `page`
CREATE TABLE `page` (
  `pageid` int(11) NOT NULL auto_increment,
  `songid` int(11) NOT NULL default '0',
  `pagenum` int(11) NOT NULL default '0',
  `lyrics` text,
  PRIMARY KEY  (`pageid`)
);

-- Table structure for table `playlist`
CREATE TABLE `playlist` (
  `playorder` int(11) NOT NULL default '0',
  `playlist` int(11) NOT NULL default '1',
  `data` varchar(256) default NULL,
  `type` varchar(4) default 'song',
  `transition` int(11) default '0',
  PRIMARY KEY  (`playorder`)
);

-- Table structure for table `playlists`
CREATE TABLE `playlists` (
  `id` int(11) NOT NULL default '1',
  `title` varchar(50) NOT NULL default '',
  `ref` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`id`)
);


-- Baseline Data
INSERT INTO lyricMain VALUES (1,'Today\'s Announcements',0,'Not Songs','',20040307192037 ,'',00000000000000,'');
INSERT INTO page VALUES (1,1,1,'Here are todays announcements');
INSERT INTO lyricMain VALUES (2,'Sample Song',0,'Sample Songbook','',20040307192037 ,'',00000000000000,'');
INSERT INTO page VALUES (2,2,1,'This is a sample song');
INSERT INTO page VALUES (3,2,2,'This is the second page of the a sample song');
INSERT INTO playlists VALUES (1,'Main Playlist','');

