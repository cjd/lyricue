CREATE TABLE associations (
  id int(11) NOT NULL auto_increment,
  playlist int(11) NOT NULL default '0',
  imagename varchar(255) NOT NULL default '',
  absoluteparent int(11) NOT NULL default '0',
  PRIMARY KEY  (id)
);

CREATE TABLE audit (
  id int(24) NOT NULL auto_increment,
  songid int(11) NOT NULL default '0',
  playdate datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (id)
);

CREATE TABLE lyricMain (
  id int(11) NOT NULL auto_increment,
  title varchar(100) NOT NULL default '',
  songnum int(11) default '0',
  book varchar(100) default '',
  artist varchar(100) default '',
  written timestamp(14) NOT NULL,
  keywords text,
  entered timestamp(14) NOT NULL,
  copyright varchar(100) default '',
  PRIMARY KEY  (id)
);

CREATE TABLE page (
  pageid int(11) NOT NULL auto_increment,
  songid int(11) NOT NULL default '0',
  pagenum int(11) NOT NULL default '0',
  lyrics text,
  PRIMARY KEY  (pageid)
);

CREATE TABLE playlist (
  playorder int(11) NOT NULL default '0',
  playlist int(11) NOT NULL default '1',
  data varchar(50) NOT NULL default '',
  type varchar(4) default 'song',
  transition int(11) default '0',
  PRIMARY KEY  (playorder)
);

CREATE TABLE playlists (
  id int(11) NOT NULL default '0',
  title varchar(50) NOT NULL default '',
  ref varchar(50) NOT NULL default '',
  PRIMARY KEY  (id)
);
