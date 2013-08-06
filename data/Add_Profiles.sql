use lyricDb;
CREATE TABLE `status` (
  `host` varchar(50) NOT NULL default '',
  `title` varchar(50) NOT NULL default '',
  `lastupdate` timestamp NOT NULL default '0000-00-00 00:00:00',
  `profile` varchar(50) NOT NULL default '',
  `type` varchar(50) NOT NULL default 'normal',
  `ref` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`host`)
) DEFAULT CHARSET=utf8;

CREATE TABLE `profiles` (
  `host` varchar(50) NOT NULL default '',
  `profile` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`host`)
) DEFAULT CHARSET=utf8;

ALTER TABLE config ADD profile varchar(50) default '';
ALTER TABLE config_old ADD profile varchar(50) default '';
ALTER TABLE playlists ADD profile varchar(50) default 'Default';
