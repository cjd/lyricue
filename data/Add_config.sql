use lyricDb;

-- Table structure for table `config`
CREATE TABLE config (
  id int(11) NOT NULL auto_increment,
  config_key varchar(50) NOT NULL default '',
  config_value varchar(250) default '',
  PRIMARY KEY  (id)
) DEFAULT CHARSET=utf8;

-- Table structure for table `config_old`
CREATE TABLE config_old (
  id int(11) NOT NULL auto_increment,
  config_key varchar(50) NOT NULL default '',
  config_value varchar(250) default '',
  PRIMARY KEY  (id)
) DEFAULT CHARSET=utf8;

