CREATE DATABASE mediaDb;

USE mediaDb;

--
-- Table structure for table `media`
--

CREATE TABLE media (
  id INTEGER unsigned NOT NULL auto_increment,
  category varchar(100) NOT NULL default '',
  subcategory varchar(100) NOT NULL default '',
  type varchar(10) NOT NULL default '',
  format varchar(10) NOT NULL default '',
  insertedby varchar(100) NOT NULL default '',
  insertdate datetime NOT NULL default '0000-00-00 00:00:00',
  description varchar(100) default '',
  textcolour varchar(10) DEFAULT 'NULL',
  shadowcolour varchar(10) DEFAULT 'NULL',
  data mediumblob,
  PRIMARY KEY  (id),
  UNIQUE KEY data (data(100),description,category,subcategory,type,format)
) TYPE=MyISAM;

--
-- Dumping data for table `media`
--

INSERT INTO media VALUES (1,'Solid','','bg','bg','cjd','2004-08-01 17:03:47','black','');
INSERT INTO media VALUES (2,'Main','','img','bg','cjd','2004-08-01 17:02:25','black','');
INSERT INTO media VALUES (5,'Solid','','bg','bg','cjd','2004-08-01 17:03:47','orange','');
INSERT INTO media VALUES (6,'Solid','','bg','bg','cjd','2004-08-01 17:03:47','gray','');
INSERT INTO media VALUES (7,'Solid','','bg','bg','cjd','2004-08-01 17:03:47','red','');
INSERT INTO media VALUES (8,'Solid','','bg','bg','cjd','2004-08-01 17:03:47','green','');
INSERT INTO media VALUES (9,'Solid','','bg','bg','cjd','2004-08-01 17:03:47','blue','');
INSERT INTO media VALUES (10,'Solid','','bg','bg','cjd','2004-08-01 17:03:47','yellow','');
INSERT INTO media VALUES (11,'Solid','','bg','bg','cjd','2004-08-01 17:03:47','white','');
