CREATE DATABASE mediaDb;

use mediaDb;

CREATE TABLE media (
  id int(10) unsigned NOT NULL auto_increment,
  category varchar(100) NOT NULL default '',
  subcategory varchar(100) NOT NULL default '',
  type varchar(10) NOT NULL default '',
  description varchar(100) NOT NULL default '',
  data blob,
  PRIMARY KEY  (id)
) TYPE=MyISAM;
