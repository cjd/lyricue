use lyricDb;

CREATE TABLE associations (
   id int(11) NOT NULL auto_increment,
   playlist int(11) NOT NULL,
   imagename varchar(255) NOT NULL,
   absoluteparent int(11) NOT NULL,
   PRIMARY KEY (id)
);

CREATE TABLE audit (
  id int(24) NOT NULL auto_increment,
  songid int(11) NOT NULL,
  playdate datetime NOT NULL,
  PRIMARY KEY (id)
); 

ALTER TABLE lyricMain ADD copyright varchar(100) default '';

DROP TABLE playlist;

CREATE TABLE playlist (
  playorder int(11) NOT NULL default '0',
  playlist int(11) NOT NULL default '1',
  data varchar(50) NOT NULL default '',
  type varchar(4) default 'song',
  PRIMARY KEY  (playorder)
);

CREATE TABLE playlists (
  id int(11) NOT NULL default '1',
  title varchar(50) NOT NULL default '',
  ref varchar(50) NOT NULL default '',
  PRIMARY KEY (id)
);

INSERT INTO playlists SET id=1, title="Main Playlist", ref='';
