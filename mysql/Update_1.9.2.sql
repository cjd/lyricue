CREATE DATABASE mediaDb;

use mediaDb;

CREATE TABLE media (
  id int(10) unsigned NOT NULL auto_increment,
  category varchar(100) NOT NULL default '',
  subcategory varchar(100) NOT NULL default '',
  type varchar(10) NOT NULL default '',
  format varchar(10) NOT NULL default '',
  insertedby varchar(100) NOT NULL default '',
  insertdate datetime NOT NULL default '0000-00-00 00:00:00',
  description varchar(100) default '',
  data mediumblob,
  PRIMARY KEY  (id),
  UNIQUE KEY data (data(100),description,category,subcategory,type,format)
) TYPE=MyISAM;

