CREATE DATABASE lyricDb;

USE lyricDb;

--
-- Table structure for table 'audit'
--

CREATE TABLE associations (
   id int(11) NOT NULL auto_increment,
   playlist int(11) NOT NULL,
   imagename varchar(255) NOT NULL,
   absoluteparent int(11) NOT NULL,
   PRIMARY KEY (id)
);

--
-- Table structure for table 'audit'
--

CREATE TABLE audit (
  id int(24) NOT NULL auto_increment,
  songid int(11) NOT NULL,
  playdate datetime NOT NULL,
  PRIMARY KEY (id)
); 

--
-- Table structure for table 'lyricMain'
--

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
) TYPE=MyISAM;

--
-- Dumping data for table 'lyricMain'
--


INSERT INTO lyricMain VALUES (1,'test line',0,'','teest artist',20020925112202,'',00000000000000,'');
INSERT INTO lyricMain VALUES (3,'Amazing Grace',0,'','',20011111180040,'',00000000000000,'');
INSERT INTO lyricMain VALUES (9,'Joyful, Joyful we adore thee',1,'Hymnal','Henry Van Dyke',20011118102650,'joyful adore the god glory lord love we thee',00000000000000,'');
INSERT INTO lyricMain VALUES (8,'Rejoice! Rejoice!',614,'','',20011111183604,'rejoice christ in you',00000000000000,'');
INSERT INTO lyricMain VALUES (10,'The Solid Rock',0,'','',20011118103223,'',00000000000000,'');
INSERT INTO lyricMain VALUES (11,'He has made me glad',0,'','',20011118103359,'',00000000000000,'');
INSERT INTO lyricMain VALUES (13,'Beautiful',5,'Elevate','Lucas Parry',20011118191716,'',00000000000000,'');
INSERT INTO lyricMain VALUES (14,'Adore',6,'Elevate','Sebastian Buffa',20011118191732,'',00000000000000,'');
INSERT INTO lyricMain VALUES (18,'God is in the house',0,'Hillsongs','Russel Fragar and Darlene Zschech',20011118191603,'',00000000000000,'');
INSERT INTO lyricMain VALUES (20,'I Give You My Heart',0,'Hillsongs','Reuben Morgan',20011118191640,'',00000000000000,'');
INSERT INTO lyricMain VALUES (78,'Glory',14,'Hillsongs: the music','Geoff Bullock\n',20020113091813,'',00000000000000,'');
INSERT INTO lyricMain VALUES (23,'The stone\'s been rolled away',0,'','',20021009120618,'',00000000000000,'Preset:1');
INSERT INTO lyricMain VALUES (22,'My Redeemer Lives',0,'','',20011123153659,'',00000000000000,'');
INSERT INTO lyricMain VALUES (25,'You give me shelter',0,'','',20011123182414,'',00000000000000,'');
INSERT INTO lyricMain VALUES (27,'I Believe',0,'','',20011209191538,'',00000000000000,'');
INSERT INTO lyricMain VALUES (28,'Put on the garment of praise',0,'','',20011125093751,'',00000000000000,'');
INSERT INTO lyricMain VALUES (32,'Because He Lives',0,'','',20011125100113,'',00000000000000,'');
INSERT INTO lyricMain VALUES (31,'Give Thanks',0,'','',20011125095532,'',00000000000000,'');
INSERT INTO lyricMain VALUES (33,'The Servant King',0,'','',20011125101127,'',00000000000000,'');
INSERT INTO lyricMain VALUES (34,'Hallelujah! Our God reigns',102,'S in S','Dale Garratt',20011202173436,'',00000000000000,'');
INSERT INTO lyricMain VALUES (35,'He is exalted',518,'S in S','Twila Paris',20011202174211,'',00000000000000,'');
INSERT INTO lyricMain VALUES (36,'Ascribe greatness',461,'S in S','',20011202174456,'',00000000000000,'');
INSERT INTO lyricMain VALUES (37,'The Lord reigns',342,'S in S','',20011202175646,'',00000000000000,'');
INSERT INTO lyricMain VALUES (38,'Blessed be the lord god almighty',472,'S in S','',20020113103402,'',00000000000000,'');
INSERT INTO lyricMain VALUES (39,'Doxology',343,'S in S','',20020113103411,'',00000000000000,'');
INSERT INTO lyricMain VALUES (46,'Excelsis Deo',0,'','',20011216181237,'',00000000000000,'');
INSERT INTO lyricMain VALUES (41,'Great are your works',0,'','Andy Park',20011202181554,'',00000000000000,'');
INSERT INTO lyricMain VALUES (54,'Silent Night',0,'','',20011223165720,'',00000000000000,'');
INSERT INTO lyricMain VALUES (43,'Make Me Your Servant',0,'Hillsongs','Russell Fragar',20011209174759,'servant',00000000000000,'');
INSERT INTO lyricMain VALUES (44,'Jesus Lover of my Soul',0,'Hillsongs','Daniel Grul & John Ezzy',20011209175018,'',00000000000000,'');
INSERT INTO lyricMain VALUES (47,'Angels we have heard on high (In excelsis deo)',0,'','',20011223173537,'',00000000000000,'');
INSERT INTO lyricMain VALUES (49,'Come and join the celebration',0,'','',20011216185327,'',00000000000000,'');
INSERT INTO lyricMain VALUES (48,'Hark! the herald angels sing',0,'','',20011216183648,'',00000000000000,'');
INSERT INTO lyricMain VALUES (50,'O Come all ye faithful',0,'','',20011216191028,'',00000000000000,'');
INSERT INTO lyricMain VALUES (51,'He is the king of kings',0,'','',20011216191145,'',00000000000000,'');
INSERT INTO lyricMain VALUES (52,'The heavens shall declare',0,'','',20011216192130,'',00000000000000,'');
INSERT INTO lyricMain VALUES (53,'The First Noel',124,'Hymnal','',20020113103321,'noel',00000000000000,'');
INSERT INTO lyricMain VALUES (56,'Merry Christmas',0,'','',20011223182107,'',00000000000000,'');
INSERT INTO lyricMain VALUES (55,'It came upon the midnight clear',0,'','',20011223174450,'',00000000000000,'');
INSERT INTO lyricMain VALUES (57,'While Shepherds Watched',0,'','',20011223183109,'',00000000000000,'');
INSERT INTO lyricMain VALUES (58,'As with Gladness Men of Old',0,'','',20011223183137,'',00000000000000,'');
INSERT INTO lyricMain VALUES (59,'Jesus stand Among us',0,'','',20011230093046,'',00000000000000,'');
INSERT INTO lyricMain VALUES (114,'Everybody ought to know',0,'','R. J. Hughes',20020127093034,'',00000000000000,'');
INSERT INTO lyricMain VALUES (60,'I will sing of the mercies of the lord',0,'','',20011230093325,'',00000000000000,'');
INSERT INTO lyricMain VALUES (61,'Behold what manner of love',316,'S in S','',20020113103355,'behold manner love sons god',00000000000000,'');
INSERT INTO lyricMain VALUES (62,'Now unto him',0,'','',20011230101843,'',00000000000000,'');
INSERT INTO lyricMain VALUES (63,'He is Lord',0,'','',20011230102031,'',00000000000000,'');
INSERT INTO lyricMain VALUES (64,'Blessing, Honour',0,'','',20011230103025,'',00000000000000,'');
INSERT INTO lyricMain VALUES (65,'The Lord thy God in the midst',103,'S in S','Tapu Moala',20011230174534,'',00000000000000,'');
INSERT INTO lyricMain VALUES (67,'The Lord Liveth',635,'S in S','Michael O\'Shields',20011230175725,'',00000000000000,'');
INSERT INTO lyricMain VALUES (66,'Make Way',587,'S in S','Graham Kendrick',20011230174918,'',00000000000000,'');
INSERT INTO lyricMain VALUES (68,'For I\'m Building a People of Power',262,'S in S','Dave Richards',20011230175955,'',00000000000000,'');
INSERT INTO lyricMain VALUES (69,'I will rejoice',556,'S in S','Brent Chambers',20011230180403,'',00000000000000,'');
INSERT INTO lyricMain VALUES (70,'Lord, for the years',0,'','Timothy Dudley-Smith',20011230183809,'',00000000000000,'');
INSERT INTO lyricMain VALUES (71,'Blessed Assurance',687,'Hymnal','',20020106092156,'',00000000000000,'');
INSERT INTO lyricMain VALUES (72,'All for Jesus',0,'','',20020106092327,'',00000000000000,'');
INSERT INTO lyricMain VALUES (105,'My Lord knows the way',10,'','Sidney E. Cox',20020120101759,'',00000000000000,'');
INSERT INTO lyricMain VALUES (75,'Love the Lord your God',0,'S in S','',20020113103336,'',00000000000000,'');
INSERT INTO lyricMain VALUES (74,'Ancient of days',0,'S in S','Gary Sadler and Jamie Harvill',20020113103347,'every ancient',00000000000000,'');
INSERT INTO lyricMain VALUES (76,'Lord I lift your name on high',0,'','',20020106181407,'',00000000000000,'');
INSERT INTO lyricMain VALUES (113,'The Price is paid',640,'','Graham Kendrick',20020127092637,'',00000000000000,'');
INSERT INTO lyricMain VALUES (77,'Lord of the Heavens',13,'God is in the house','',20020113091535,'',00000000000000,'');
INSERT INTO lyricMain VALUES (79,'Thou are the everlasting word',242,'Hymnal','',20020113100544,'',00000000000000,'');
INSERT INTO lyricMain VALUES (80,'To God be the glory',741,'Hymnal','William H. Doane, Fanny J. Crosby',20020113092241,'',00000000000000,'');
INSERT INTO lyricMain VALUES (82,'I will sing, I will sing',254,'S in S','Max Dyer',20020113092728,'',00000000000000,'');
INSERT INTO lyricMain VALUES (83,'Glory to the king',0,'S in S','Darlene Zschech',20020113093240,'',00000000000000,'');
INSERT INTO lyricMain VALUES (84,'Thank You, Lord',378,'S in S','Diane Davis Andrew',20020113094242,'',00000000000000,'');
INSERT INTO lyricMain VALUES (85,'Turn your eyes upon Jesus',48,'','H. H. Lemmel',20020113100103,'',00000000000000,'');
INSERT INTO lyricMain VALUES (86,'I know a fount',15,'','O. Cooke Lewisham',20020113100411,'',00000000000000,'');
INSERT INTO lyricMain VALUES (87,'Oh, how I love Him',16,'','Carl Blackmore',20020113101215,'',00000000000000,'');
INSERT INTO lyricMain VALUES (91,'I will run to You',15,'God Is In The House','Darlene Zschech',20020113174839,'',00000000000000,'');
INSERT INTO lyricMain VALUES (88,'I will sing, I will sing',254,'S in S','Max Dyer',20020113174204,'',00000000000000,'');
INSERT INTO lyricMain VALUES (89,'Glory Jesus Glory',251,'S in S','Susie Wilson',20020113174329,'',00000000000000,'');
INSERT INTO lyricMain VALUES (90,'Your hand O God has Guided',0,'','',20020113174428,'',00000000000000,'');
INSERT INTO lyricMain VALUES (92,'Your People Sing Praises',10,'God Is In The House','Russel Fragar',20020113175026,'',00000000000000,'');
INSERT INTO lyricMain VALUES (93,'Let the peace of God reign',7,'God Is In The House','Dalene Zschech\n',20020113175234,'',00000000000000,'');
INSERT INTO lyricMain VALUES (94,'Jesus, what a beautiful name',6,'God Is In The House','Tanya Riches\n',20020113175334,'',00000000000000,'');
INSERT INTO lyricMain VALUES (95,'And that my soul knows very well',5,'God Is In The House','Darlene Zschech and Russel Fragar',20020113175435,'',00000000000000,'');
INSERT INTO lyricMain VALUES (96,'My heart Sings Praises',4,'God Is In The House','Russell Fragar',20020113175547,'',00000000000000,'');
INSERT INTO lyricMain VALUES (97,'Steppin\' out',3,'God Is In The House','Steve McPherson',20020113175634,'',00000000000000,'');
INSERT INTO lyricMain VALUES (98,'Joy in the Holy Ghost',2,'God Is In The House','Russel Fragar\n',20020113175741,'',00000000000000,'');
INSERT INTO lyricMain VALUES (99,'Amazing Love',0,'','',20020120090535,'',00000000000000,'');
INSERT INTO lyricMain VALUES (100,'Beauty for Ashes',144,'','',20020120090905,'',00000000000000,'');
INSERT INTO lyricMain VALUES (101,'Praise my soul',17,'Hymnal','John Goss and Henry F. Lyte',20020120092213,'',00000000000000,'');
INSERT INTO lyricMain VALUES (102,'Take my life, And let it be',510,'Hymnal','Frances Ridley Havergal',20020120092449,'',00000000000000,'');
INSERT INTO lyricMain VALUES (103,'Guide me, O thou great Jehovah,',540,'Hymnal','Wiliam Wiliams, John Hughes',20020120092558,'',00000000000000,'');
INSERT INTO lyricMain VALUES (104,'The Son of God goes forth to war,',525,'Hymnal','Reginald Heber, Henry S. Cutler',20020120092704,'',00000000000000,'');
INSERT INTO lyricMain VALUES (106,'I\'n in the Lord\'s Army',31,'','Anonymous. Copyright held by Zondervan Music Publishers',20020120102247,'',00000000000000,'');
INSERT INTO lyricMain VALUES (107,'Every day with Jesus',71,'','Wendell P. Loveless',20020120102623,'',00000000000000,'');
INSERT INTO lyricMain VALUES (108,'I shall not be moved',6,'Singing Joy','John T. Benson and Mrs. Jas. A. Pate',20020120103238,'',00000000000000,'');
INSERT INTO lyricMain VALUES (109,'Have faith in God',0,'','',20020120103943,'',00000000000000,'');
INSERT INTO lyricMain VALUES (110,'Blessed be the rock',473,'S in S','Dan Gardner',20020120174515,'blessed rock',00000000000000,'');
INSERT INTO lyricMain VALUES (111,'Don\'t you know that I formed you',496,'S in S','David Garratt and Wayne Drain',20020120174804,'',00000000000000,'');
INSERT INTO lyricMain VALUES (112,'Question',0,'','',20020120185147,'',00000000000000,'');
INSERT INTO lyricMain VALUES (118,'One Day\n',1,'For This Cause\n','Reuben Morgan\n',20020202162937,'blessed enough\n',00000000000000,'');
INSERT INTO lyricMain VALUES (116,'All the Earth shall Worship',457,'S in S','Carl Tuttle',20020127180611,'worship',00000000000000,'');
INSERT INTO lyricMain VALUES (115,'Jesus put this song into our hearts',569,'S in S','',20020127102303,'',00000000000000,'');
INSERT INTO lyricMain VALUES (117,'I will lift my voice',0,'Geoff Bullock 2','Geoff Bullock',20020127181625,'lift voice king lord worship',00000000000000,'');
INSERT INTO lyricMain VALUES (123,'Surrender',0,'','Marc James',20020202170248,'',00000000000000,'');
INSERT INTO lyricMain VALUES (119,'Faith\n',2,'For This Cause\n','Reuben Morgan\n',20020202163022,'Faith standing greater world\n',00000000000000,'');
INSERT INTO lyricMain VALUES (121,'It makes me wanna sing',0,'','Jay VanDer Noord',20020202165057,'',00000000000000,'');
INSERT INTO lyricMain VALUES (133,'Here is bread',0,'','Graham Kendrick',20020203093143,'',00000000000000,'');
INSERT INTO lyricMain VALUES (122,'Stronger than',0,'','',20020202165635,'',00000000000000,'');
INSERT INTO lyricMain VALUES (124,'Your love oh Lord',0,'','',20020202170556,'',00000000000000,'');
INSERT INTO lyricMain VALUES (125,'You are my world',0,'','',20020202171200,'',00000000000000,'');
INSERT INTO lyricMain VALUES (126,'One80 café MENU',0,'','',20020202184655,'',00000000000000,'');
INSERT INTO lyricMain VALUES (135,'Shout to the Lord',0,'People Just Like Us','Darlene Zschesh',20020203175959,'',00000000000000,'');
INSERT INTO lyricMain VALUES (156,'Your grace and your mercy',0,'Geoff Bullock 2','Geoff Bullock',20020210180644,'',00000000000000,'');
INSERT INTO lyricMain VALUES (134,'Father of Lights',0,'People Just Like Us','Russell Fragar',20020203175557,'',00000000000000,'');
INSERT INTO lyricMain VALUES (129,'Awesome in this place',3,'For This Cause\n','',20020209174940,'',00000000000000,'');
INSERT INTO lyricMain VALUES (130,'Dwell in Your House\n',4,'For This Cause\n','Paul Ewing\n',20020203091950,'\n',00000000000000,'');
INSERT INTO lyricMain VALUES (131,'As the Deer',0,'The Hymnal\n','\n',20020203095735,'\n',00000000000000,'');
INSERT INTO lyricMain VALUES (132,'At the Name of Jesus',0,'The Hymnal\n','\n',20020203095755,'\n',00000000000000,'');
INSERT INTO lyricMain VALUES (136,'Your love keeps following me',0,'People Just Like Us','Russell Fragar',20020203181453,'',00000000000000,'');
INSERT INTO lyricMain VALUES (137,'Just let me say',0,'People Just Like Us','Geoff Bullock',20020203182118,'',00000000000000,'');
INSERT INTO lyricMain VALUES (138,'Power and the Glory',0,'People Just Like Us','Geoff Bullock',20020203182537,'',00000000000000,'');
INSERT INTO lyricMain VALUES (142,'God is great',0,'','Marty Sampson',20020209170817,'',00000000000000,'');
INSERT INTO lyricMain VALUES (141,'Holy Moment',0,'','Mat Redmond',20020209165408,'',00000000000000,'');
INSERT INTO lyricMain VALUES (139,'Psalm 119',0,'','',20020209162831,'',00000000000000,'');
INSERT INTO lyricMain VALUES (143,'For This Cause',0,'For This Cause','',20020209172410,'',00000000000000,'');
INSERT INTO lyricMain VALUES (144,'Lord You have my heart',0,'','',20020209172636,'',00000000000000,'');
INSERT INTO lyricMain VALUES (145,'Deeply In love',0,'','',20020209173153,'',00000000000000,'');
INSERT INTO lyricMain VALUES (146,'Psalm 119',0,'','',20020209173654,'',00000000000000,'');
INSERT INTO lyricMain VALUES (147,'The Celebration Song',361,'S in S','Brent Chambers',20020210091555,'',00000000000000,'');
INSERT INTO lyricMain VALUES (148,'Jesus is Lord',360,'S in S','David J. Mansell',20020210091914,'',00000000000000,'');
INSERT INTO lyricMain VALUES (155,'We are a people of power',652,'S in S','Trevor King',20020217173716,'',00000000000000,'');
INSERT INTO lyricMain VALUES (149,'Holy, Holy, Holy, Holy',94,'SIS\n','\n',20020210092628,'\n',00000000000000,'');
INSERT INTO lyricMain VALUES (150,'Holy, Holy, Holy',60,'Hymnal','John B. Dykes',20020210093506,'',00000000000000,'');
INSERT INTO lyricMain VALUES (152,'Sermon 10-2-2002 Morning',0,'','',20020210103312,'',00000000000000,'');
INSERT INTO lyricMain VALUES (153,'Master speak, thy servant heareth',441,'Hymnal','Lowell Mason',20020210100201,'',00000000000000,'');
INSERT INTO lyricMain VALUES (154,'This kingdom',0,'','Geoff Bullock',20020210175225,'',00000000000000,'');
INSERT INTO lyricMain VALUES (158,'What a Friend I\'ve found',0,'','',20020216183547,'',00000000000000,'');
INSERT INTO lyricMain VALUES (157,'Steve\'s quotes of the day',0,'','',20020210192313,'',00000000000000,'');
INSERT INTO lyricMain VALUES (159,'Forever',0,'','',20020216183702,'',00000000000000,'');
INSERT INTO lyricMain VALUES (162,'Father, I thank you',269,'S in S\n','Steve Stewart\n',20020217092047,'',00000000000000,'');
INSERT INTO lyricMain VALUES (160,'All of creation',0,'','',20020216184718,'',00000000000000,'');
INSERT INTO lyricMain VALUES (161,'All I need is You',0,'','',20020216185639,'',00000000000000,'');
INSERT INTO lyricMain VALUES (163,'Love divine, all loves excelling',496,'Hymnal\n','Charles Wesley and John Zundel',20020217092012,'',00000000000000,'');
INSERT INTO lyricMain VALUES (164,'Standing on the promises',690,'Hymnal\n','R. Kelso Carter\n',20020217092116,'',00000000000000,'');
INSERT INTO lyricMain VALUES (165,'There is a redeemer',644,'S in S\n','Melody Green\n',20020217092133,'',00000000000000,'');
INSERT INTO lyricMain VALUES (166,'Will your anchor hold?\n',714,'Hymnal\n','Priscilla J. Owens and William J. Kirkpatrick\n',20020217091954,'',00000000000000,'');
INSERT INTO lyricMain VALUES (167,'Trust and Obey',711,'Hymnal','John H. Sammis and Daniel B. Towner',20020217103540,'',00000000000000,'');
INSERT INTO lyricMain VALUES (168,'The Lords Prayer',0,'','',20020217104243,'',00000000000000,'');
INSERT INTO lyricMain VALUES (169,'Hosanna',538,'S in S','Carl Tuttle',20020217180104,'',00000000000000,'');
INSERT INTO lyricMain VALUES (170,'We believe',654,'S in S','Graham Kendrick',20020217180455,'',00000000000000,'');
INSERT INTO lyricMain VALUES (171,'Today\'s Announcements',0,'','',20020925183516,'',00000000000000,'');

--
-- Table structure for table 'page'
--

CREATE TABLE page (
  pageid int(11) NOT NULL auto_increment,
  songid int(11) NOT NULL default '0',
  pagenum int(11) NOT NULL default '0',
  lyrics text,
  PRIMARY KEY  (pageid)
) TYPE=MyISAM;

--
-- Dumping data for table 'page'
--


INSERT INTO page VALUES (640,9,8,'Ever singing march we onwards,\nvictors in the midst of strife;\nJoyful music leads us sunward\nin the triumph song of life.');
INSERT INTO page VALUES (696,41,2,'Great are Your works Lord,\nGreat are your deeds,\nAwesome in power,\nSo awesome to me.');
INSERT INTO page VALUES (697,41,3,'You will reign, You will reign\nForever, forever\nIn power, in power\nYou will reign.\n(repeat)');
INSERT INTO page VALUES (698,41,4,'Great are Your works Lord,\nGreat are your deeds,\nAwesome in power,\nSo awesome to me.');
INSERT INTO page VALUES (699,41,5,'Because of, because of,\nYour greatness, your greatness,\nAll the earth, all the earth,\nWill sing.\n(repeat)');
INSERT INTO page VALUES (2820,45,6,'Remember to arrive Before 7 next \nweek and bring along\na friend.');
INSERT INTO page VALUES (1621,113,8,'The price is paid, Alleluia\nAmazing grace so strong and sure\nAnd so with all my heart\nMy life in every part\nI live to thank you for the price you paid.');
INSERT INTO page VALUES (1639,115,3,'Jesus taught us how to be a family\nJesus taught us how to be a family\nLoving one another with the love that\nHe gives\nJesus taught us how to be a family.');
INSERT INTO page VALUES (1638,115,2,'Jesus taught us how to live in harmony\nJesus taught us how to live in harmony\nDifferent faces, different races,\nHe made us one\nJesus taught us how to live in harmony.');
INSERT INTO page VALUES (1619,113,6,'The price is paid, Alleluia\nAmazing grace so strong and sure\nAnd so with all my heart\nMy life in every part\nI live to thank you for the price you paid.');
INSERT INTO page VALUES (1620,113,7,'The price is paid worthy the Lamb we cry\nEternity shall never cease his praise\nThe church of Christ shall rule upon the Earth\nIn Jesus name we have authority.');
INSERT INTO page VALUES (1616,113,3,'The Price is paid see Satan flee away\nFor Jesus crucified destroys his power\nNo more to pay let accusation cease\nIn Christ there is no condemnation now.');
INSERT INTO page VALUES (1617,113,4,'The price is paid, Alleluia\nAmazing grace so strong and sure\nAnd so with all my heart\nMy life in every part\nI live to thank you for the price you paid.');
INSERT INTO page VALUES (1618,113,5,'The price is paid and by that\nscourging cruel\nHe took our sicknesses as if his own\nAnd by his wounds his body broken there\nHis healing touch may now by faith be known.');
INSERT INTO page VALUES (1614,113,1,'The price is paid come let us enter in\nTo all that Jesus died to make our own\nFor every sin.\nMore than enough he gave\nAnd bought our freedom from \neach guilty stain.');
INSERT INTO page VALUES (1615,113,2,'The price is paid, Alleluia\nAmazing grace so strong and sure\nAnd so with all my heart\nMy life in every part\nI live to thank you for the price you paid.');
INSERT INTO page VALUES (1637,115,1,'Jesus put this song into our hearts,\nJesus put this song into our hearts,\nIt\'s a song of joy no one can take away,\nJesus put this song into our hearts.');
INSERT INTO page VALUES (2658,158,2,'Jesus, Jesus\nJesus, friend for ever.');
INSERT INTO page VALUES (638,9,4,'Field and forest, vale and mountain\nFlowery meadow, flashing stream;\nChanting bird and flowing fountain,\nCall us to rejoice in thee');
INSERT INTO page VALUES (639,9,6,'Thou our Father, Christ our brother,\nAll who live in love are thine;\nTeach us how to love each other,\nLift us to the joy divine.');
INSERT INTO page VALUES (637,9,2,'Melt the clouds of Sin and sadness\nDrive the dark of doubt away\nGiver of immortal gladness\nFill us with the light of day');
INSERT INTO page VALUES (635,9,5,'Thou art giving and forgiving,\never blessing, ever blest,\nWell-spring of the joy of living,\nOcean depth of happy rest!\n');
INSERT INTO page VALUES (636,9,7,'Mortals join the happy chorus,\nwhich the morning stars began;\nFather love is reigning o\'er us,\nBrother love binds man to man.\n');
INSERT INTO page VALUES (633,9,1,'Joyful, Joyful we adore thee\nGod of glory, Lord of love;\nHearts unfold like flowers before thee\nOpening to the sun above.');
INSERT INTO page VALUES (634,9,3,'All thy works with joy surround thee\nEarth and heav\'n reflect thy rays\nStars and angels sing around thee\ncentre of unbroken praise\n');
INSERT INTO page VALUES (167,10,6,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (165,10,5,'Now is the time for us to \nmarch upon the land \nInto our hands he will \ngive the ground we claim \nHe rides in majesty \nto lead us into victory \nThe world shall see \nthat Christ is Lord.\n');
INSERT INTO page VALUES (166,10,20,'\'Twas grace that taught my heart to fear, and grace my fears relieved;\nHow precious did that grace appear the hour I first believed!\n');
INSERT INTO page VALUES (164,10,25,'Mortals join the happy chorus,\nwhich the morning stars began;\nFather love is reigning o\'er us,\nBrother love binds man to man.\n\nEver singing march we onwards,\nvictors in the midst of strife;\nJoyful music leads us sunward\nin the triumph song of life.');
INSERT INTO page VALUES (163,10,19,'When we\'ve been there ten thousand years, \nbright shining as the sun,\nWe\'ve no less days to sing God\'s praise \nthan when we first begun.');
INSERT INTO page VALUES (162,10,24,'Thou art giving and forgiving,\never blessing, ever blest,\nWell-spring of the joy of living,\nOcean depth of happy rest!\n\nThou our Father, Christ our brother,\nAll who live in love are thine;\nTeach us how to love each other,\nLift us to the joy divine.');
INSERT INTO page VALUES (161,10,23,'All thy works with joy surround thee\nEarth and heav\'n reflect thy rays\nStars and angels sing around thee\ncentre of unbroken praise\n\nField and forest, vale and mountain\nFlowery meadow, flashing stream;\nChanting bird and flowing fountain,\nCall us to rejoice in thee');
INSERT INTO page VALUES (160,10,1,'My hope is built on nothing less \nthan Jesus\' blood and righteousness.\nI dare not trust the sweetest frame \nbut wholly lean on Jesus\' name.\n\nOn Christ, the solid Rock, I stand; \nall other ground is sinking sand.\nAll other ground is sinking sand.');
INSERT INTO page VALUES (1365,39,2,'Praise him above ye \nheavenly host\nPraise Father, Son \nand Holy Ghost!');
INSERT INTO page VALUES (1364,39,1,'Praise God from whom \nall blessings flow\nPraise him all \ncreatures here below\n');
INSERT INTO page VALUES (1362,38,1,'Father in heaven, how we love you\nWe lift your name in all the Earth\nMay your kingdom be \nestablished in our praises\nAs your people declare \nyour mighty works!');
INSERT INTO page VALUES (1363,38,2,'Blessed be the Lord God Almighty\nWho was and is and is to come\nBlessed be the Lord God Almighty\nWho reigns for evermore');
INSERT INTO page VALUES (687,37,3,'The Lord reigns, The Lord reigns,\nThe Lord reigns, let the earth rejoice\nLet the earth rejoice, \nLet the earth rejoice,\nLet the people be glad\nThat our God reigns!');
INSERT INTO page VALUES (685,37,1,'The Lord reigns, The Lord reigns,\nThe Lord reigns, let the earth rejoice\nLet the earth rejoice, \nLet the earth rejoice,\nLet the people be glad\nThat our God reigns!');
INSERT INTO page VALUES (686,37,2,'A fire goes before him\nAnd burns up all his enemies\nThe hills melt like wax\nAt the presence of the lord\nAt the presence of the lord\nof the whole earth');
INSERT INTO page VALUES (1464,35,2,'He is the Lord\nFor ever his truth shall reign:\nHeaven and earth\nRejoice in his holy name\nHe is exalted\nThe King is exalted on high.');
INSERT INTO page VALUES (706,36,2,'Ascribe greatness to our God,\nthe rock.\nHis work is perfect,\nand all his ways are just.');
INSERT INTO page VALUES (705,36,4,'A God of faithfulness\nand without injustice\nGood and upright is he\n(repeat)');
INSERT INTO page VALUES (703,36,1,'Ascribe greatness');
INSERT INTO page VALUES (704,36,3,'Ascribe greatness to our God,\nthe rock\nHis work is perfect,\nand all his ways are just.');
INSERT INTO page VALUES (2879,23,10,'Singing Glory\nSinging Glory\nSinging Glory\nRestored and Sanctified\nThe stone\'s been rolled away');
INSERT INTO page VALUES (2880,23,5,'Singing Glory\nSinging Glory\nSinging Glory\nRestored and Sanctified\nThe stone\'s been rolled away');
INSERT INTO page VALUES (2878,23,4,'I\'ve been released\nThe stone\'s been rolled away\nI\'ve been released\nThe stone\'s been rolled away');
INSERT INTO page VALUES (2877,23,1,'I\'ve been forgiven\nI\'ve been set free\nRestored and sanctified\nIn Christ I\'ve been set free');
INSERT INTO page VALUES (2876,23,8,'And I am free\nThe stone\'s been rolled away\nAnd I am free\nThe stone\'s been rolled away');
INSERT INTO page VALUES (2875,23,2,'And I am free\nThe stone\'s been rolled away\nAnd I am free\nThe stone\'s been rolled away');
INSERT INTO page VALUES (441,13,3,'Let us see on earth\nThe glory of your Son\nMay I be the one\nThat you\'d use in your plan');
INSERT INTO page VALUES (442,13,4,'Bring the nations to your side\nLet the kingdoms join\nIn shouts of praise\nLet me be the one who brings\nThe one who brings your love');
INSERT INTO page VALUES (447,20,2,'Lord I give You my heart\nI give You my soul\nI live for You alone\nEvery breath that I take\nEvery moment I\'m awake\nLord have Your way in me');
INSERT INTO page VALUES (446,20,1,'This is my desire\nTo honour You\nLord with all my heart\nI worship You\nAll I have within me\nI give You praise\nAll that I adore\nIs in You');
INSERT INTO page VALUES (1240,78,4,'Glory to the King of Kings\nMajesty power and strength,\nTo the Lord of Lords.');
INSERT INTO page VALUES (1239,78,3,'Glory to the King of Kings.\nMakesty, power and strength\nto the Lord of Lords');
INSERT INTO page VALUES (440,13,2,'I stand before you\nMy heart adores you\nIn your hands I place my life\nI pray, let your will be done');
INSERT INTO page VALUES (439,13,1,'All I am I give to you\nWith every breath I worship you\nI pray, let your will be done');
INSERT INTO page VALUES (700,41,6,'Great are Your works Lord,\nGreat are your deeds,\nAwesome in power,\nSo awesome to me.');
INSERT INTO page VALUES (836,50,4,'O come, let us adore Him,\nO come, let us adore Him,\nO come, let us adore Him,\nChrist the Lord.');
INSERT INTO page VALUES (827,51,1,'He is the King of Kings\nHe is the Lord of Lord\nHis name is Jesus, \nJesus, Jesus, Jesus\nO, He is King');
INSERT INTO page VALUES (711,43,1,'I want to be your hands\nAnd be your feet\nLord make me your servant\nI want to tell your love\nTo everyone I meet\nLord make me your servant');
INSERT INTO page VALUES (632,3,4,'When we\'ve been there ten thousand years,\nbright shining as the sun,\nWe\'ve no less days to sing God\'s praise \nthen when we first began.');
INSERT INTO page VALUES (630,3,2,'\'Twas grace that taught my heart to fear,\n and grace my fears relieved;\nHow precious did that grace \nappear the hour I first believed!\n');
INSERT INTO page VALUES (631,3,3,'Through many dangers, \ntoils and snares I have already come;\n\'Tis grace hath brought me safe thus far, \nand grace will lead me home.\n');
INSERT INTO page VALUES (629,3,1,'Amazing grace! how sweet the sound\nthat saved a wretch like me!\nI once was lost but now am found, \nWas blind but now I see');
INSERT INTO page VALUES (1640,115,4,'Jesus turned our sorrow into dancing\nJesus turned our sorrow into dancing\nChanged our tears of sadness into rivers\nof joy\nJesus turned our sorrow into a dance.');
INSERT INTO page VALUES (1705,117,3,'I will lift my hands\nto the Lord of lords\nAs an offering to Him\nI will lift my life\nto the Lord of lords\nAs an offering to Him\n');
INSERT INTO page VALUES (1625,114,1,'Everybody ought to know\nEverybody ought to know\nEverybody ought to know\nwho Jesus is. (repeat)\nHe\'s the Lily of the Valley\nHe\'s the Bright and Morning Star\nHe\'s the fairest of Ten Thousand\nEverybody ought to know\n');
INSERT INTO page VALUES (1584,8,7,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (1583,8,6,'Though we are weak, \nhis grace is everything we need\nWe\'re made of clay. \nBut this treasure is within. \nHe turns our weaknesses \ninto his oppurtunities\nSo that the glory goes to him.');
INSERT INTO page VALUES (1582,8,5,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (1581,8,4,'God is at work in us his purpose to perform\nBuilding a kingdom of power not of words\nWhere things impossible, \nby faith shall be made possible\nLet\'s give the glory to him now.');
INSERT INTO page VALUES (1580,8,3,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (1579,8,2,'Now is the time for us to \nmarch upon the land \nInto our hands he will \ngive the ground we claim \nHe rides in majesty \nto lead us into victory \nThe world shall see \nthat Christ is Lord.\n');
INSERT INTO page VALUES (1578,8,1,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (168,10,21,'Through many dangers, toils and snares I have already come;\n\'Tis grace hath brought me safe thus far, and grace will lead me home.\n');
INSERT INTO page VALUES (169,10,14,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (170,10,7,'God is at work in us his purpose to perform\nBuilding a kingdom of power not of words\nWhere things impossible, \nby faith shall be made possible\nLet\'s give the glory to him now.');
INSERT INTO page VALUES (171,10,22,'When we\'ve been there ten thousand years, bright shining as the sun,\nWe\'ve no less days to sing God\'s praise than when we first begun.');
INSERT INTO page VALUES (172,10,15,'Though we are weak, his grace is everything we need\nWe\'re made of clay. But this treasure is within. \nHe turns our weaknesses into his oppurtunities\nSo that the glory goes to him.');
INSERT INTO page VALUES (173,10,8,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (174,10,17,'\'Twas grace that taught my heart to fear,\n and grace my fears relieved;\nHow precious did that grace \nappear the hour I first believed!\n');
INSERT INTO page VALUES (175,10,16,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (176,10,2,'When darkness seems to hide His face, \nI rest on His unchanging grace.\nIn every high and stormy gale, \nmy anchor holds within the vale.\n\nOn Christ, the solid Rock, I stand; \nall other ground is sinking sand.\nAll other ground is sinking sand.');
INSERT INTO page VALUES (177,10,18,'Through many dangers, \ntoils and snares I have already come;\n\'Tis grace hath brought me safe thus far, \nand grace will lead me home.\n');
INSERT INTO page VALUES (178,10,9,'Though we are weak, \nhis grace is everything we need\nWe\'re made of clay. \nBut this treasure is within. \nHe turns our weaknesses \ninto his oppurtunities\nSo that the glory goes to him.');
INSERT INTO page VALUES (179,10,3,'His oath, His covenant, \nHis blood support me in the whelming flood.\nWhen all around my soul gives way, \nHe then is all my Hope and Stay.\n\nOn Christ, the solid Rock, I stand; \nall other ground is sinking sand.\nAll other ground is sinking sand.');
INSERT INTO page VALUES (180,10,10,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (181,10,4,'When He shall come with trumpet sound, \noh, may I then in Him be found;\nDressed in His righteousness alone, \nfaultless to stand before the throne.\n\nOn Christ, the solid Rock, I stand; \nall other ground is sinking sand.\nAll other ground is sinking sand.');
INSERT INTO page VALUES (182,10,11,'Now is the time for us to march upon the land \nInto our hands he will give the ground we claim \nHe rids in mahesrt to lead us into victory \nThe world shall see that Christ is Lord.\n');
INSERT INTO page VALUES (183,10,12,'Rejoice Rejoice! Christ is in you\nThe hope of glory in our hearts\nHe lives! He lives! His breath is in you\nArise a mighty army, we arise!');
INSERT INTO page VALUES (184,10,13,'God is at work in us his purpose to perform\nBuilding a kingdom of power not of words\nWhere things impossible, \nby faith shall be made possible\nLet\'s give the glory to him now.');
INSERT INTO page VALUES (695,41,1,'Your works Lord, Your works Lord\nAre awesome, are awesome\nYour power, your power\nIs great \n(repeat)');
INSERT INTO page VALUES (1463,35,1,'He is exalted, \nthe King is exalted on high:\nI will praise him.\nHe is exalted, forever exalted\nAnd I will praise his name');
INSERT INTO page VALUES (670,34,2,'Let us rejoice and be glad\nAnd give the glory unto him\nHallelujah! for the lord our God \nthe Almighty reigns.');
INSERT INTO page VALUES (669,34,1,'Hallelujah! For the Lord our God\nthe almighty reigns\nHallelujah! For the Lord our God\nthe almighty reigns');
INSERT INTO page VALUES (658,31,3,'And now,\nlet the weak say I am strong,\nlet the poor say I am rich,\nBecause of what the Lord\nhas done for us\n\nGive thanks.\n');
INSERT INTO page VALUES (657,31,2,'Give thanks with a grateful heart\nGive thanks to the Holy One\nGive thanks because he\'s given\nJesus Christ his Son');
INSERT INTO page VALUES (656,31,1,'Give thanks with a grateful heart\nGive thanks to the Holy One\nGive thanks because he\'s given\nJesus Christ his Son');
INSERT INTO page VALUES (664,33,2,'This is our God,\nthe servant King\nHe calls us now\nto worship Him;\nTo bring our lives\nas a daily offering\nOf worship to\nthe Servant King.');
INSERT INTO page VALUES (659,32,1,'Because He Lives\nI can face tomorrow\nBecause He Lives\nAll fear is gone');
INSERT INTO page VALUES (660,32,2,'Because He Lives\nHe holds the future\nAnd life is worth the living,\nJust because He lives.');
INSERT INTO page VALUES (661,32,3,'Because He Lives\nI can face tomorrow\nBecause He Lives\nAll fear is gone');
INSERT INTO page VALUES (662,32,4,'Because He Lives\nHe holds the future\nAnd life is worth the living,\nJust because He lives.');
INSERT INTO page VALUES (663,33,1,'From heaven You came,\nhelpless Babe,\nEnteter our world\nYour glory veiled;\nNot to be served,\nbut to serve,\nAnd give Your life\nthat we might live.');
INSERT INTO page VALUES (665,33,3,'There in the garden of tears');
INSERT INTO page VALUES (649,28,6,'Sing to Yahweh, a;;eluia\nWorship and praise our God\nPraise and adore Him,\nbow down before Him\nO, magnify the Lord...');
INSERT INTO page VALUES (647,28,4,'Lift up the hands that hang down\nLift up the voice now still\nGive unto God continuous praise\nSing forth from Zion\'s hill...\n ');
INSERT INTO page VALUES (648,28,5,'Put on the garment of praise\nfor the spirit of heaviness\nLift up your voice to God!\n\nPraise with the spirit\nAnd with understanding\nO, magnify the Lord.');
INSERT INTO page VALUES (645,28,2,'All you that mourn in Zion\nI have authority\nTo appoint unto you in Zion\nOil of joy that will set you free...');
INSERT INTO page VALUES (646,28,3,'Put on the garment of praise\nfor the spirit of heaviness\nLift up your voice to God!\n\nPraise with the spirit\nAnd with understanding\nO, magnify the Lord.');
INSERT INTO page VALUES (644,28,1,'Put on the garment of praise\nfor the spirit of heaviness\nLift up your voice to God!\n\nPraise with the spirit\nAnd with understanding\nO, magnify the Lord.');
INSERT INTO page VALUES (643,28,7,'Put on the garment of praise\nfor the spirit of heaviness\nLift up your voice to God!\n\nPraise with the spirit\nAnd with understanding\nO, magnify the Lord.');
INSERT INTO page VALUES (641,11,1,'I will enter his gates with thanksgiving in my heart\nI will enter his courts with praise\nI will say this is the day that the Lord has made\nI will rejoice for he has made me glad');
INSERT INTO page VALUES (642,11,2,'He has made me glad,\nHe has made me glad\nI will rejoice for he has made me glad\nHe has made me glad,\nHe has made me glad\nI will rejoice for he has made me glad');
INSERT INTO page VALUES (818,49,5,'Come and join the celebration,\nIt\'s a very special day;\nCome and share our jubilation,\nThere\'s a new King born today!');
INSERT INTO page VALUES (835,50,3,'Sing, choirs of angels,\nsing in exaltation,\nSing, all ye citizens of\nheaven above;\nGlory to God,\nglory in the highest!');
INSERT INTO page VALUES (791,48,9,'Hark! the herald angels sing,\nGlory to the newborn King!');
INSERT INTO page VALUES (790,48,8,'Mild, He lays His glory by,\nBorn that man no more may die;\nBorn to raise the sons of earth,\nBorn to give them second birth!');
INSERT INTO page VALUES (789,48,7,'Hail the heaven born Prince of Peace!\nHail the Son the Righteousness!\nLight of life to all he brings,\nRisen with healing in his wings.');
INSERT INTO page VALUES (787,48,5,'Veiled in flesh the Godhead see,\nHail, the incarnate Deity!\nPleased as man with men to dwell,\nJesus our Immanuel!');
INSERT INTO page VALUES (788,48,6,'Hark! the herald angels sing,\nGlory to the newborn King!');
INSERT INTO page VALUES (785,48,3,'Hark! the herald angels sing,\nGlory to the newborn King!');
INSERT INTO page VALUES (786,48,4,'Christ, by highest heaven adored,\nChrist, the everlasting Lord;\nLate in time behold him come,\nOffspring of a virgin\'s womb.');
INSERT INTO page VALUES (783,48,1,'Hark the herald angels sing,\nGlory to the newborn King;\nPeace on earth and mercy mild,\nGod and sinners reconciled.');
INSERT INTO page VALUES (998,55,4,'For lo! the days are hastening on,\nBy prophet-bards foretold,\nWhen with the ever-circling years\nComes round the age of gold;\nWhen peace shall over all the Earth\nIts ancient splendors fling,\nAnd the whole world give back the song\nWhich now the angels sing.');
INSERT INTO page VALUES (770,46,2,'Come to bethlehem and see,\nHim whose birth the angels sing;\nCome, adore on bended knee,\nChrist the Lord, the newborn King;\n\n\nGloria in excelsis Deo,\nGloria in excelsis Deo!');
INSERT INTO page VALUES (757,44,1,'Jesus, lover of my soul\nJesus, I will never let you go\nYou\'ve taken me, from the mirey clay\nSet my feet upon the rock\nAnd now I know');
INSERT INTO page VALUES (758,44,2,'I love you, I need you\nThough my world may fall\nI\'ll never let you go\nMy saviour, my closest friend\nI will worship you until the very end');
INSERT INTO page VALUES (712,43,2,'And when you call me servant\nYou really call me friend\nYour love has made me love you\nAnd want to serve you\nMake me the one you send');
INSERT INTO page VALUES (744,27,9,'I believe, I\'m righteous and reformed\nI believe\nI believe, oh yes my God\nI believe');
INSERT INTO page VALUES (743,27,8,'I believe, I\'m sanctified, restored\nI believe\nI believe, forgiven and transformed\nI believe');
INSERT INTO page VALUES (742,27,7,'I\'m reaching out\n\'Cause I know there\'s\na better way\nI walk by faith\nI beleive in a better day\nI\'m holding on to you');
INSERT INTO page VALUES (769,46,1,'Angels we have heard on high,\nSweetly singing o\'er the plains,\nAnd the mountains in reply,\nEcho back their joyous strains,\n\nGloria in excelsis Deo,\nGloria in excelsis Deo!\n');
INSERT INTO page VALUES (740,27,12,'I believe, I\'m righteous and reformed\nI believe\nI believe, oh yes my God\nI believe');
INSERT INTO page VALUES (741,27,6,'I believe, I\'m righteous and reformed\nI believe\nI believe, oh yes my God\nI believe');
INSERT INTO page VALUES (733,27,1,'I\'m reaching out\n\'Cause I know there\'s\na better way\nI walk by faith\nI beleive in a better day\nI\'m holding on to you');
INSERT INTO page VALUES (734,27,2,'I believe, I\'m sanctified, restored\nI believe\nI believe, forgiven and transformed\nI believe');
INSERT INTO page VALUES (735,27,3,'I believe, I\'m righteous and reformed\nI believe\nI believe, oh yes my God\nI believe');
INSERT INTO page VALUES (736,27,10,'I\'m singing out\n\'Cause I\'ve heard all the angels say\nI can\'t hold back\n\'Cause I know You will come one day\nI\'m holding on\nHolding on to you');
INSERT INTO page VALUES (737,27,4,'I\'m singing out\n\'Cause I\'ve heard all the angels say\nI can\'t hold back\n\'Cause I know You will come one day\nI\'m holding on\nHolding on to you');
INSERT INTO page VALUES (738,27,11,'I believe, I\'m sanctified, restored\nI believe\nI believe, forgiven and transformed\nI believe');
INSERT INTO page VALUES (739,27,5,'I believe, I\'m sanctified, restored\nI believe\nI believe, forgiven and transformed\nI believe');
INSERT INTO page VALUES (1695,116,6,'All the earth shall worship\nAt the throne of the king\nOf his great and awesome power we shall sing.\nAll the earth shall worship\nAt the throne of the king\nOf his great and awesome power we shall sing.\n');
INSERT INTO page VALUES (1703,117,1,'I will lift my voice\nto the King of kings\nAs an offering to Him\nI will lift my heart\nto the King of kings\nAs an offering to Him');
INSERT INTO page VALUES (1706,117,4,'Jesus how I love you,\nI will worship, You alone\nJesus precious Jesus,\nI will serve You, You alone');
INSERT INTO page VALUES (2622,112,1,'What do you think in our\nculture (as in NSW area)\nstops the contemporary\nchurch doing the kind of\ngood seen in Titus 3?');
INSERT INTO page VALUES (1686,25,1,'You give me shelter\nYou give me peace\nYou give me comfort\nhealing, release\n\nThe peace and comfort\nof the knowledge of\nGod in my heart\n\n');
INSERT INTO page VALUES (1687,25,2,'You healed my body\nReleased my mind\nYou set me free\nto leave the past behind\n\nThe peace and comfort\nof the knowledge of\nGod in my heart');
INSERT INTO page VALUES (1688,25,3,'And no matter what \nlife can bring\nThis peace in my heart \njust makes me sing\n');
INSERT INTO page VALUES (1704,117,2,'Jesus how I love you,\nI will worship, You alone\nJesus precious Jesus,\nI will serve You, You alone');
INSERT INTO page VALUES (1689,25,4,'You\'re My God, Saviour Lord\nYou\'re my God, King of Kings\nYou\'re my God, Prince of peace\n\nAnd all the Earth \nis going to see the \nglory of my God');
INSERT INTO page VALUES (2874,23,9,'And I am free\nThe stone\'s been rolled away\nAnd I am free\nThe stone\'s been rolled away');
INSERT INTO page VALUES (2873,23,7,'And I am free\nThe stone\'s been rolled away\nAnd I am free\nThe stone\'s been rolled away');
INSERT INTO page VALUES (2872,23,3,'I\'ve been delivered\nI\'ve been released\nBeen washed and purified\nMy God has set me free');
INSERT INTO page VALUES (1237,78,1,'Glory to the King of Kings\nMajesty power and strength,\nTo the Lord of Lords.');
INSERT INTO page VALUES (1238,78,2,'Holy one, all creation\ncrowns you King of Kings\nHoly one, King of Kings,\nLord of Lords, Holy one.');
INSERT INTO page VALUES (899,47,1,'Angels we have heard on high,\nSweetly singing o\'er the plains,\nAnd the mountains in reply,\nEcho back their joyous strains,\n\nGloria in excelsis Deo,\nGloria in excelsis Deo!');
INSERT INTO page VALUES (1193,14,3,'Heaven\'s praise surrounds us\n  in this place\nAs we offer up our songs\n  of praise to you\nNations turn and see\n  your holy face\n\nHow I adore you\nHow I adore you');
INSERT INTO page VALUES (1191,14,1,'Before the heavens we stand\nIn awe of the one we love\nBefore the nations we stand\nTo sing of the Son of God');
INSERT INTO page VALUES (1192,14,2,'How I adore you\nHow I adore, I adore you\nHow I adore you\nHow I adore, I adore you');
INSERT INTO page VALUES (784,48,2,'Joyful, all ye nations, rise,\nJoin the triumph of the skies;\nWith angelic hosts proclaim,\nChrist is born in Bethlehem!');
INSERT INTO page VALUES (2871,23,11,'Restored and Sanctified\nThe stone\'s been rolled away');
INSERT INTO page VALUES (2714,22,8,'My redeemer lives!');
INSERT INTO page VALUES (2713,22,7,'You lift my burdens\nI\'ll rise with you\nI\'m dancing on this mountain top\nto see your kingdom come!');
INSERT INTO page VALUES (2712,22,6,'My redeemer lives!\nMy redeemer lives!\nMy redeemer lives!\nMy redeemer lives!\n');
INSERT INTO page VALUES (2709,22,3,'My redeemer lives!\nMy redeemer lives!\nMy redeemer lives!\nMy redeemer lives!');
INSERT INTO page VALUES (2710,22,4,'I know He rescued my soul\nHis blood has covered my sins\nI Believe, I Believe.\n\nMy shame He\'s taken away,\nmy pain is healed in His name.\nI Believe, I Believe.\n\n');
INSERT INTO page VALUES (2711,22,5,'I\'ll raise the banner\n\'cause my lord has \nconquered the grave\n\n');
INSERT INTO page VALUES (2708,22,2,'I\'ll raise the banner\n\'cause my lord has \nconquered the grave\n');
INSERT INTO page VALUES (2707,22,1,'I know He rescued my soul\nHis blood has covered my sins\nI Believe, I Believe.\n\nMy shame He\'s taken away,\nmy pain is healed in His name.\nI Believe, I Believe.');
INSERT INTO page VALUES (431,18,1,'As for me, God came and found me\nAs for me, He took me home\nAs for me, He gave me a family\nAnd I\'ll never walk alone\nIn my life\nI\'m soaked in blessing\nAnd in heaven there\'s a great reward\nAs for me and my house\nWe\'re gonna serve the Lord');
INSERT INTO page VALUES (433,18,3,'God is in the house\nCan\'t keep Him out\nAs for you (As for you)\nAs for me (As for me)\nWe\'re gonna serve the Lord');
INSERT INTO page VALUES (900,47,2,'Come to Bethlehem and see,\nHim whose birth the angels sing;\nCome, adore on bended knee,\nChrist the Lord, the newborn King;\n\nGloria in excelsis Deo,\nGloria in excelsis Deo!');
INSERT INTO page VALUES (432,18,2,'I\'ve got Jesus, Jesus\nHe calls me for His own\nAnd He lifts me, lifts me\nAbove the world I know\nGod is in the house\nThere is no doubt\n');
INSERT INTO page VALUES (817,49,4,'Wise men journey,\nled to worship by a star,\n\nKneel in homage,\nbringing precious gifts from \nlands afar, So...');
INSERT INTO page VALUES (816,49,3,'Come and join the celebration,\nIt\'s a very special day;\nCome and share our jubilation,\nThere\'s a new King born today!');
INSERT INTO page VALUES (814,49,1,'Come and join the celebration,\nIt\'s a very special day;\nCome and share our jubilation,\nThere\'s a new King born today!');
INSERT INTO page VALUES (815,49,2,'See the shepherds hurry \ndown to Bethlehem\n\nGaze in wonder at the Son\nof God who lay before them');
INSERT INTO page VALUES (813,49,7,'Come and join the celebration,\nIt\'s a very special day;\nCome and share our jubilation,\nThere\'s a new King born today!');
INSERT INTO page VALUES (819,49,6,'God is with us,\nround the world the message bring,\nHe is with us,\nWelcome,\nall the bells on earth are peeling');
INSERT INTO page VALUES (849,52,5,'Every eye shall see,\nEvery heart will know,\nEvery knee shall bow,\nEvery tongue confees;');
INSERT INTO page VALUES (848,52,4,'The heavens shall declare\nthe glory of His name,\nAll creation bow\nat the coming of the King');
INSERT INTO page VALUES (834,50,2,'O come, let us adore Him,\nO come, let us adore Him,\nO come, let us adore Him,\nChrist the Lord.');
INSERT INTO page VALUES (833,50,1,'O come, all ye faithful, \njoyful and triumphant,\nO come, O come ye,\nto Bethlehem,\nCome and behold him,\nBorn the king of angels;');
INSERT INTO page VALUES (837,50,5,'Yea, Lord, we greet thee,\nborn this happy morning,\nJesus to Thee be glory given!\nWord of the father \nnow in flesh appearing;');
INSERT INTO page VALUES (838,50,6,'O come, let us adore Him,\nO come, let us adore Him,\nO come, let us adore Him,\nChrist the Lord.');
INSERT INTO page VALUES (847,52,3,'Holy, Holy, Holy is the Lord,\nSee the coming of the Lord,\nHoly is the Lord.');
INSERT INTO page VALUES (846,52,2,'Every eye shall see,\nEvery heart will know,\nEvery knee shall bow,\nEvery tongue confees;');
INSERT INTO page VALUES (845,52,1,'The heavens shall declare\nthe glory of His name,\nAll creation bow\nat the coming of the King');
INSERT INTO page VALUES (850,52,6,'Holy, Holy, Holy is the Lord,\nSee the coming of the Lord,\nHoly is the Lord.');
INSERT INTO page VALUES (1350,53,7,'Then let us all with one accord,\nSing praises to our heavenly lord;\nWho hath made heaven,\nand Earth of nought\nAnd with His blood,\nmankind hath bought');
INSERT INTO page VALUES (1351,53,8,'Noel, Noel, Noel, Noel\nBorn is the King of Israel,');
INSERT INTO page VALUES (1348,53,5,'And by the light of that same star,\nThree wise men came from country far;\nTo seek for a King that was their intent,\nAnd to follow the star wherever it went,');
INSERT INTO page VALUES (1349,53,6,'Noel, Noel, Noel, Noel\nBorn is the King of Israel,');
INSERT INTO page VALUES (1346,53,3,'They looked up and saw a star,\nShining in the east,\nBeyond them far;\nAnd to the earth it gave great light,\nAnd so it continued both day and night');
INSERT INTO page VALUES (1344,53,1,'The First Noel the angel did say,\nWas to certain poor shepherds,\nin fields as they lay;\nIn fields where they lay,\nkeeping their sheep,\nOn a cold winter\'s night that was so deep');
INSERT INTO page VALUES (1345,53,2,'Noel, Noel, Noel, Noel\nBorn is the King of Israel,');
INSERT INTO page VALUES (1005,59,1,'Jesus, Stand among us\nAt the meeting of our lives.\nBe our sweet agreement,\nAt the meeting of our eyes.');
INSERT INTO page VALUES (994,54,3,'Silent night, holy night\nSon of God, love\'s pure light \nRadiant beams from Thy holy face \nWith the dawn of redeeming grace\nJesus, Lord at Thy birth.\nJesus, Lord at Thy birth.');
INSERT INTO page VALUES (1347,53,4,'Noel, Noel, Noel, Noel\nBorn is the King of Israel,');
INSERT INTO page VALUES (993,54,2,'Silent night, holy night \nShepherds quake at the sight \nGlories stream from Heaven afar \nHeavenly hosts sing Hallelujah \nChrist the Saviour is born \nChrist the Saviour is born.');
INSERT INTO page VALUES (992,54,1,'Silent night, holy night\nAll is calm, all is bright\nRound yon Virgin\nMother and Child\nHoly infant, so tender and mild\nSleep in heavenly peace\nSleep in heavenly peace.');
INSERT INTO page VALUES (997,55,3,'And ye, beneath life\'s crushing load,\nWhose forms are bending low,\nWho toil along the climbing way\nWith painful steps and slow,\nLook now! for glad and golden hours\nCome swiftly on the wing:\nO rest beside the weary road,\nAnd hear the angels sing!');
INSERT INTO page VALUES (996,55,2,'Still thro\' the cloven skies they come,\nWith peaceful wings unfurled,\nAnd still their heavenly music floats\nO\'er all the weary world:\nAbove its sad and lowly plains\nThey bend on hovering wing,\nAnd ever o\'er its Babel sounds\nThe blessed angels sing.');
INSERT INTO page VALUES (995,55,1,'It came upon the midnight clear,\nThat glorious song of old,\nFrom angels bending near the Earth,\nTo touch their harps of gold:\nPeace on Earth, good will to men,\nFrom heaven\'s all gracious King.\nThe world in solemn stillness lay,\nTo hear the angels sing.');
INSERT INTO page VALUES (1800,118,3,'Lord You\'re more than enough for me\n\n');
INSERT INTO page VALUES (1007,59,3,'So to you we\'re gathering\nOut of each and every land\nChrist the love between us\nAt the joining of our hands');
INSERT INTO page VALUES (978,56,3,'Golden day, When we say,\nMerry, merry christmas.\nIn the street, Where we meet,\nMerry, merry, merry christmas.\nAnd with pride, far and wide,\nAll our homes adorning,\nEarth and sky, Sound the cry,');
INSERT INTO page VALUES (977,56,2,'So with joy, Man and boy,\nSing with us together; On this morn,\nChrist was born,\nMerry, Merry, Merry Christmas.\nRaise the song, Loud and strong,\nIn the shining weather, Joy bells ring,\nChrist is King, Merry, merry, merry Christmas.');
INSERT INTO page VALUES (976,56,1,'Sun gleams bright, Hearts are light,\nMerry, merry Christmas.\nBells ring out, Children shout,\nMerry, Merry, Merry Christmas.\nSheep in fold, Shine like gold, As the day is\ndawning, Riding by Stocking men cry,\nWelcome Christmas morning\n');
INSERT INTO page VALUES (962,57,3,'To you, in Davids town this day\nIs born of Davids line,\nThe Saviour who is Christ the Lord\nAnd this shall be the sign');
INSERT INTO page VALUES (961,57,2,'Fear Not, said he for mighty dread\nHad seized their troubled mind\nGlad tidings of great joy I bring\nTo you and all mankind');
INSERT INTO page VALUES (960,57,1,'While shepherds watched their flocks by night\nAll seated on the ground\nThe angel of the Lord came down\nAnd glory shone around');
INSERT INTO page VALUES (963,57,4,'The heavenly Babe you there shall find\nTo human view displayed\nAll meanly wrapped in swathing bands\nAnd in a manger laid');
INSERT INTO page VALUES (964,57,5,'Thus spoke the seraph; and forth-with\nAppeared a shining throng\nOf angels praising God on high\nWho thus addressed song');
INSERT INTO page VALUES (965,57,6,'All glory be to God on high\nAnd to the earth be peace\nGood will henceforth from heaven to men\nBegin and never cease!');
INSERT INTO page VALUES (1001,58,3,'As they offered gifts most rare\nAt the manger rude and bare\nSo may we with holy joy,\nPure and free from sin\'s alloy\nAll our costliest treasures bring\nChrist, to Thee, our heavenly King.');
INSERT INTO page VALUES (1006,59,2,'O Jesus, we love you\nSo we gather here\nJoin our hearts in unity\nand take away our fear.');
INSERT INTO page VALUES (1002,58,4,'Holy Jesus, every day\nKeep us in the narrow way;\nAnd when earthly things are past,\nBring our ransomed souls at last\nWhere they need no star to guide,\nWhere no clouds Thy glory hide.');
INSERT INTO page VALUES (1000,58,2,'As with joyous steps they sped\nTo that lowly manger bed,\nThere to bend the knee before\nHim whom heaven and earth adore\nSo may we with willing feet\nEver seek Thy mercy seat');
INSERT INTO page VALUES (999,58,1,'As with gladness men of old\nDid the guiding star behold\nAs with joy they hailed its light\nLeading onward, beaming bright\nSo, most gracious Lord,\nmay we Evermore be led to thee');
INSERT INTO page VALUES (1008,59,4,'O Jesus, we love you\nSo we gather here\nJoin our hearts in unity\nAnd take away our fear');
INSERT INTO page VALUES (1017,60,1,'I will sing of the mercies of the Lord forever\nI will sing, I will sing\nI will sing of the mercies of the Lord forever\nI will sing of the mercies of the Lord\nWith my mouth will I make known\nThy faithfulness, thy faithfulness\nWith my mouth will I make known\nThy faithfulness to all generations.');
INSERT INTO page VALUES (1361,61,1,'Behold what manner of love\nthe father has given unto us\nBehold what manner of love\nthe father has given unto us\n\nThat we should be called the\nSons of God\nThat we should be called the\nSons of God');
INSERT INTO page VALUES (1026,65,1,'The Lord thy God in the midst of thee\nIs mighty, is mighty\nHe will save, he will rejoice over thee\nWith joy, with joy\nHe will rest in his love\nHe will joy over thee with singing\nThe Lord thy God in the midst of thee\nIs mighty, is mighty, is mighty');
INSERT INTO page VALUES (1019,62,1,'Now unto him who is able to keep,\nable to keep you from falling.\nAnd present you faultless,\nbefore the presence of his glory,\nwith exceeding joy!');
INSERT INTO page VALUES (1020,62,2,'To the only wise God, \nour Saviour,\nBe glory and Majesty!\nDominion and Power, \nboth now and forever, \nAmen.');
INSERT INTO page VALUES (1075,63,1,'He is Lord, He is Lord,\nHe is risen from the dead\nand He is Lord!\nevery knee shall bow,\nevery tongue confess,\nthat Jesus Christ is Lord.');
INSERT INTO page VALUES (1022,64,1,'Blessing, Honour,\nGlory to the Lamb.\nBlessing, Honour,\nWorthy is the Lamb.\n(repeat)\n\nDeath could not hold him down,\nfor He is risen!\nSeated upon the throne,\nHe is the Son of God!');
INSERT INTO page VALUES (1507,66,7,'We call you now to worship him\nAs Lord of all\nTo have no gods before him\nTheir thrones must fall');
INSERT INTO page VALUES (1508,66,8,'Make way (echo)\nMake way (echo)\nFor the King of kings (echo)\nMake way (echo)\nMake way (echo)\nAnd let his Kingdom in');
INSERT INTO page VALUES (1700,77,1,'Lord of the Heavens and the Earth,\nMy Saviour Redeemer, Risen Lord.\nAll honour and glory, power and strength,\nTo Him upon the Throne.\n(repeat first time)');
INSERT INTO page VALUES (1506,66,6,'Make way (echo)\nMake way (echo)\nFor the King of kings (echo)\nMake way (echo)\nMake way (echo)\nAnd let his Kingdom in');
INSERT INTO page VALUES (1505,66,5,'And those who mourn with heavy hearts\nWho weep and sigh\nWith laughter joy and royal crown\nHe\'ll beautify');
INSERT INTO page VALUES (1503,66,3,'He comes the broken hearts to heal\nThe prisoners to free\nThe deaf shall hear, the lame shall dance\nThe blind shall see');
INSERT INTO page VALUES (1504,66,4,'Make way (echo)\nMake way (echo)\nFor the King of kings (echo)\nMake way (echo)\nMake way (echo)\nAnd let his Kingdom in');
INSERT INTO page VALUES (1502,66,2,'Make way (echo)\nMake way (echo)\nFor the King of kings (echo)\nMake way (echo)\nMake way (echo)\nAnd let his Kingdom in');
INSERT INTO page VALUES (1501,66,1,'Make way, make way for Christ the King\nIn splendour arrives\nFling wide the gates and welcome him\nInto your lives');
INSERT INTO page VALUES (1052,67,1,'I will call upon the Lord (echo)\nWho is worthy to be praised (echo)\nSo shall I be saved from my enemies (echo)');
INSERT INTO page VALUES (1053,67,2,'The Lord liveth\nAnd blessed be my rock\nAnd let the God of my salvation be exalted\nThe Lord liveth\nAnd blessed be my rock\nAnd let the God of my salvation be exalted');
INSERT INTO page VALUES (1054,68,1,'For I\'m building a people of power\nAnd I\'m making a people of praise\nThat will move through this land by my Spirit\nAnd will glorify my precious name');
INSERT INTO page VALUES (1055,68,2,'Build your church, Lord\nMake us strong, Lord\nJoin our hearts, Lord\nThrough your Son\nMake us one, Lord\nIn your Body\nIn the kingdom of your Son');
INSERT INTO page VALUES (2635,69,3,'I will rejoice (do do do do do),\nI will rejoice (do do do do do),\nI will rejoice,\nfor I\'ve made my choice\nTo rejoice in the Lord\n(Repeat)');
INSERT INTO page VALUES (2636,69,4,'It doesn\'t depend on the circumstance,\nThe strength of my arm or my voice.\nIt doesn\'t depend on the way I feel.\nI\'ve made up my mind\nAnd I\'m gonna rejoice!');
INSERT INTO page VALUES (2634,69,2,'The enemy whispered into my mind,\nDetermined to wear me down.\nAlert in the Spirit, I am not blind\nMy confession of faith\nHas that enemy bound');
INSERT INTO page VALUES (2633,69,1,'I will rejoice (do do do do do),\nI will rejoice (do do do do do),\nI will rejoice,\nfor I\'ve made my choice\nTo rejoice in the Lord\n(Repeat)');
INSERT INTO page VALUES (1070,70,1,'Lord, for the years your love has kept and guided\nurged and inspired us, cheered us on our way,\nsought us and saved us, pardoned and provided:\nLord of the years, we bring our thanks today.');
INSERT INTO page VALUES (1071,70,2,'Lord, for that word, the word of life which fires us,\nspeaks to our hearts and sets our souls ablaze,\nteaches and trains, rebukes us and inspires us:\nLord of the word, receive your people\'s praise.');
INSERT INTO page VALUES (1072,70,3,'Lord, for our land, in this our generation,\nspirits opressed by pleasure, wealth and care:\nfor young and old, for commonwealth and nation,\nLord of our land, be pleased to hear our prayer.');
INSERT INTO page VALUES (1073,70,4,'Lord, for ourselves, in living power remake us -\nself on the cross and Christ upon the throne,\npast put behind us, for the future take us:\nLord of our lives, to live for Christ alone.');
INSERT INTO page VALUES (1105,71,5,'Perfect submission,\nall is at rest,\nI in my Saviour\nam happy and blest:\nWatching and waiting,\nlooking above,\nFill\'d with His goodnes,\nlost in His love');
INSERT INTO page VALUES (1106,71,6,'This is my story,\nthis is my song\nPraising my Saviour\nall the day long\n(repeat)');
INSERT INTO page VALUES (1104,71,4,'This is my story,\nthis is my song\nPraising my Saviour\nall the day long\n(repeat)');
INSERT INTO page VALUES (1102,71,2,'This is my story,\nthis is my song\nPraising my Saviour\nall the day long\n(repeat)');
INSERT INTO page VALUES (1103,71,3,'Perfect Submision,\nperfect delight,\nVisions of rapture\nnow burst on my sight:\nAngels descending\nbring from above\nEchoes of mercy,\nwhispers of love.');
INSERT INTO page VALUES (1082,72,1,'All for Jesus, all for Jesus!\nThis our song shall ever be:\nYou our only hope, our Saviour,\nYours the love that sets us free!');
INSERT INTO page VALUES (1083,72,2,'All for Jesus: you will give us\nStrength to serve you hour by hour:\nNone can move us from your presence\nWhile we trust your grace and power.');
INSERT INTO page VALUES (1084,72,3,'All for Jesus you have loved us,\nAll for Jesus you have died,\nAll for Jesus you are with us;\nAll for Jesus crucified.\n');
INSERT INTO page VALUES (1085,72,4,'All for Jesus, all for Jesus,\nAll our talents and our powers,\nAll our thoughts and words and actions,\nAll our passing days and hours.');
INSERT INTO page VALUES (1086,72,5,'All for Jesus, all for Jesus!\nThis our Churchs song shall be\nTill at last her children gather,\nOne in Him eternally.');
INSERT INTO page VALUES (1514,107,1,'Ev\'ry day with Jesus\nIs sweeter than the day before,\nEv\'ry day with Jesus\nI love Him more and more;\nJesus saves and keeps me,\nAnd He\'s the One I\'m waiting for;\nEv\'ry day with Jesus\nIs sweeter than the day before,');
INSERT INTO page VALUES (1626,105,1,'My Lord knows the way thro\' the wilderness,\nall I have to do is follow.\nMy Lord knows the way thro\' the wilderness,\nall I have to do is follow.\n\nStrength for today is mine all the way,\nand all I need for tomorrow.\nMy Lord knows the way thro\' the wilderness,\nall I have to do is follow.');
INSERT INTO page VALUES (1513,106,1,'I may never march in the infantry,\nRide in the Calvary,\nShoot in the artillery;\nI may never fly o\'er the enemy,\nBut I\'m in the Lord\'s army.\nI\'m in the Lord\'s army,\nI\'m in the Lord\'s army!');
INSERT INTO page VALUES (1813,124,1,'Your love oh Lord\nReaches to the Heavens\nYour faithfullnes\nStretches to the sky\nYour Righteousness\nIs like the mighty mountains\nYour Justice flows\nLike the ocean\'s tide');
INSERT INTO page VALUES (1101,71,1,'Blessed assurance,\nJesus is mine!\nOh What a foretaste\nof glory divine!\nHeir of salvation,\npurchase of God,\nBorn of His spirit,\nwash\'d in His Blood.');
INSERT INTO page VALUES (1798,118,1,'More than I could\nHope or Dream of\nYou have poured\nYour favour on me\nOne day in the\nHouse of God is\nBetter than a thousand\nDays in the world\n');
INSERT INTO page VALUES (1360,74,6,'Every toungue in heaven and \nEarth shall declare your glory,\nEvery knee shall bow at your \nthrone in worship\nYou will be exalted oh God,\nand your kingdom shall not \npass away,\nO Ancient of Days!');
INSERT INTO page VALUES (1357,74,3,'Blessing and honour, glory and power,\nBe unto the Ancient of Days\nFrom every nation, all of creation,\nBow before the Ancient of Days');
INSERT INTO page VALUES (1358,74,4,'Every toungue in heaven and \nEarth shall declare your glory,\nEvery knee shall bow at your \nthrone in worship\nYou will be exalted oh God,\nand your kingdom shall not \npass away,\nO Ancient of Days');
INSERT INTO page VALUES (1359,74,5,'Your kingdom shall reign over all the earth\nSing unto the ancient of days\nFor none can compare to your matchless worth\nSing unto the ancient of days');
INSERT INTO page VALUES (1540,111,1,'Don\'t you know that I formed you?\nBefore you were born I knew you.\nCan\'t you see that my plans for you are good?\n(Repeat)');
INSERT INTO page VALUES (1352,75,1,'Love the Lord your God,\nwith all your heart and \nall your soul and all your mind,\nand love for all mankind as you would\nlove yourself and..');
INSERT INTO page VALUES (1353,75,2,'Love the Lord your God\nwith all your heart and \nall your soul and mind\nand love for mankind.');
INSERT INTO page VALUES (1354,75,3,'We\'ve got Christian lives to live\nWe\'ve got Jesus\' love to give\nWe\'ve got nothing to hide\nbecause in him we abide Love.');
INSERT INTO page VALUES (2476,76,3,'Lord, I lift your name on high;\nLord, I love to sing your praises.\nI\'m so glad You\'re in my life;\nI\'m so glad You came to save us.');
INSERT INTO page VALUES (2475,76,2,'You came from heaven to Earth\nTo show the way;\nFrom the Earth to the cross,\nMy debt to pay.\nFrom the cross to the grave,\nFrom the grave to the sky;\nLord, I lift your name on high\n');
INSERT INTO page VALUES (2474,76,1,'Lord, I lift your name on high;\nLord, I love to sing your praises.\nI\'m so glad You\'re in my life;\nI\'m so glad You came to save us.');
INSERT INTO page VALUES (1355,74,1,'Blessing and honour, glory and power,\nBe unto the Ancient of Days\nFrom every nation, all of creation,\nBow before the Ancient of Days');
INSERT INTO page VALUES (1356,74,2,'Every toungue in heaven and \nEarth shall declare your glory,\nEvery knee shall bow at your \nthrone in worship\nYou will be exalted oh God,\nand your kingdom shall not \npass away,\nO Ancient of Days');
INSERT INTO page VALUES (2477,76,4,'You came from heaven to Earth\nTo show the way;\nFrom the Earth to the cross,\nMy debt to pay.\nFrom the cross to the grave,\nFrom the grave to the sky;\nLord, I lift your name on high\n');
INSERT INTO page VALUES (1701,77,2,'Holy, holy, You are worthy,\nPraises to you the Son of God,\nJesus You alone are worthy,\nCrowned in righteousness and peace.');
INSERT INTO page VALUES (1702,77,3,'Glory, glory, hallelujah,\nPraises to the Great I Am.\nHosanna, join with angels singing,\nworthy is the Lamb of God.');
INSERT INTO page VALUES (1799,118,2,'So blessed I can\'t contain it\nSo much I\'ve got to give it away\nYour love has tought\nme to live now\nYou are more than enough for me\n');
INSERT INTO page VALUES (1241,78,5,'Jesus, Lord with eyes unveiled\n we see your throne.\nJesus, Prince of Peace,\nSon of God, Emmanuel.');
INSERT INTO page VALUES (1242,78,6,'Glory to the King of Kings.\nMakesty, power and strength\nto the Lord of Lords');
INSERT INTO page VALUES (1333,79,5,'True image of the Infinite,\nwhose essence is concealed;\nBrightness of uncreated light;\nThe heart of God revealed:\n');
INSERT INTO page VALUES (1336,79,8,'Worthy, O Lamb of God, art Thou \nThat ev\'ry knee to Thee should bow');
INSERT INTO page VALUES (1337,79,9,'Throughout the universe of bliss,\nThe centre Thou and sun;\nTh\'eternal theme of praise in this,\nTo heav\'n\'s beloved One:\n');
INSERT INTO page VALUES (1335,79,7,'But the high myst\'ries of thy name\nAn angel\'s grasp trancent;\nThe Father only, glorious, claim.\nThe Son can comprehend:');
INSERT INTO page VALUES (1334,79,6,'Worthy, O Lamb of God, art Thou \nThat ev\'ry knee to Thee should bow');
INSERT INTO page VALUES (1332,79,4,'Worthy, O Lamb of God, art Thou \nThat ev\'ry knee to Thee should bow');
INSERT INTO page VALUES (1331,79,10,'Worthy, O Lamb of God, art Thou \nThat ev\'ry knee to Thee should bow');
INSERT INTO page VALUES (1330,79,3,'In The most perfectly expressed\nThe Father\'s glories shine;\nOf the full Deity possessed,\nEternally Divine:');
INSERT INTO page VALUES (1329,79,2,'Worthy, O Lamb of God, art Thou \nThat ev\'ry knee to Thee should bow');
INSERT INTO page VALUES (1343,80,6,'Praise the Lord, Praise the Lord,\nLet the Earth hear His voice!\nPraise the Lord, Praise the Lord,\nLet the people rejoice!\nO come to the Father,\nthro\' Jesus the Son,\nAnd give Him the Glory,\nGreat things He has done.');
INSERT INTO page VALUES (1342,80,5,'Great things He has taught us, \ngreat things He has done, \nAnd great our rejoicing thro\' Jesus the Son; \nBut purer, and higher, and greater will be\nOur wonder our transport, when Jesus we see.\n');
INSERT INTO page VALUES (1341,80,4,'Praise the Lord, Praise the Lord,\nLet the Earth hear His voice!\nPraise the Lord, Praise the Lord,\nLet the people rejoice!\nO come to the Father,\nthro\' Jesus the Son,\nAnd give Him the Glory,\nGreat things He has done.');
INSERT INTO page VALUES (1340,80,3,'O perfect redemption, the purchase of blood,\nTo ev\'ry believer the promise of God;\nThe vilest offender who truly believes,\nThat moment from Jesus a pardon receives.');
INSERT INTO page VALUES (1339,80,2,'Praise the Lord, Praise the Lord,\nLet the Earth hear His voice!\nPraise the Lord, Praise the Lord,\nLet the people rejoice!\nO come to the Father,\nthro\' Jesus the Son,\nAnd give Him the Glory,\nGreat things He has done.');
INSERT INTO page VALUES (1338,80,1,'To God be the glory, great things He has done;\nSo loved He the world that He gave us His Son;\nWho yeilded his life and atonement for sin,\nAnd opened the life gate that all may go in.');
INSERT INTO page VALUES (1263,82,2,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1262,82,1,'I will sing, I will sing a song unto the Lord. \nI will sing, I will sing a song unto the Lord.\nI will sing, I will sing a song unto the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1264,82,3,'We will come, we will come as one before the Lord.\nWe will come, we will come as one before the Lord.\nWe will come, we will come as one before the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1265,82,10,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1266,82,4,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1267,82,11,'In his name, In his name we have the victory.\nIn his name, In his name we have the victory.\nIn his name, In his name we have the victory.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1268,82,5,'If the Son, if the Son shall make you free\nIf the Son, if the Son shall make you free\nIf the Son, if the Son shall make you free\nYou shall be free indeed.');
INSERT INTO page VALUES (1269,82,12,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1270,82,6,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1271,82,7,'They that sow in tears shall reap in joy.\nThey that sow in tears shall reap in joy.\nThey that sow in tears shall reap in joy.\nAleluia, Glory to the Lord.\n');
INSERT INTO page VALUES (1272,82,8,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1273,82,9,'Every knee shall bow and ev\'ry tounge confess,\nEvery knee shall bow and ev\'ry tounge confess,\nEvery knee shall bow and ev\'ry tounge confess,\nThat Jesus Christ is Lord.');
INSERT INTO page VALUES (1289,83,6,'You\'re a father to the fatherless\nThe answer to my dreams\nI see you crowned in righteousness\nWe cry glory to the King\nComforter to the lonely\nThe lifter of my head\nI see you veiled in majesty\nWe cry glory, glory\nWe cry glory to the king');
INSERT INTO page VALUES (1288,83,5,'Open my ears\nLet me hear your voice\nTo know that sweet sound\nOh my soul rejoice\nGlory, glory\nI hear the angels sing');
INSERT INTO page VALUES (1287,83,4,'Lord my heart cries out\nGlory to the King\nMy greatest love in life\nI hand you everything\nGlory, glory\nI hear the angels sing');
INSERT INTO page VALUES (1286,83,3,'You\'re a father to the fatherless\nThe answer to my dreams\nI see you crowned in righteousness\nWe cry glory to the King\nComforter to the lonely\nThe lifter of my head\nI see you veiled in majesty\nWe cry glory, glory\nWe cry glory to the king');
INSERT INTO page VALUES (1284,83,1,'Lord my heart cries out\nGlory to the King\nMy greatest love in life\nI hand you everything\nGlory, glory\nI hear the angels sing');
INSERT INTO page VALUES (1285,83,2,'Open my ears\nLet me hear your voice\nTo know that sweet sound\nOh my soul rejoice\nGlory, glory\nI hear the angels sing');
INSERT INTO page VALUES (1306,84,3,'Thank you Lord for loving us.\nThank you Lord for loving us.\nThank you Lord for loving us,\nright where we are.');
INSERT INTO page VALUES (1305,84,2,'Alleluia, praise the Lord.\nAlleluia, praise the Lord.\nAlleluia, praise the Lord,\nright where we are.');
INSERT INTO page VALUES (1304,84,1,'Thank you, Lord, for this fine day.\nThank you, Lord, for this fine day.\nThank you, Lord, for this fine day.\nright where we are.');
INSERT INTO page VALUES (1291,85,1,'Turn your eyes upon Jesus\nLook full in His wonderful face;\nAnd the things of Earth will grow\nstrangely dim,\nIn the light of His glory and grace.');
INSERT INTO page VALUES (1292,86,1,'I know a fount where sins are washed away,\nI know a place where night is turned to day;\nBurdens are lifted, blind eyes made to see;\nTheres a wonder working power in the\nblood of Calvary.');
INSERT INTO page VALUES (1328,79,1,'Thou art the Everlasting word,\nThe Father\'s only Son;\nGod manifestly seen and heard,\nAnd Heaven\'s beloved One:');
INSERT INTO page VALUES (1303,87,1,'Oh, how I love Him, this man of Gallilee;\nOh, how I love Him, He died on Calvary;\nOh, how I love Him, He\'s done so much for me;\nOh, how I love Him, and He loves me.\n');
INSERT INTO page VALUES (1307,84,4,'Thank you Lord for giving us peace,\nThank you Lord for giving us peace,\nThank you Lord for giving us peace,\nright where we are.');
INSERT INTO page VALUES (1367,88,1,' will sing, I will sing a song unto the Lord. \nI will sing, I will sing a song unto the Lord.\nI will sing, I will sing a song unto the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1368,88,2,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1369,88,3,'We will come, we will come as one before the Lord.\nWe will come, we will come as one before the Lord.\nWe will come, we will come as one before the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1370,88,10,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1371,88,4,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1372,88,11,'In his name, In his name we have the victory.\nIn his name, In his name we have the victory.\nIn his name, In his name we have the victory.\nAleluia, Glory to the Lord.\n');
INSERT INTO page VALUES (1373,88,5,'If the Son, if the Son shall make you free\nIf the Son, if the Son shall make you free\nIf the Son, if the Son shall make you free\nYou shall be free indeed.');
INSERT INTO page VALUES (1374,88,12,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1375,88,6,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1376,88,7,'They that sow in tears shall reap in joy.\nThey that sow in tears shall reap in joy.\nThey that sow in tears shall reap in joy.\nAleluia, Glory to the Lord.\n');
INSERT INTO page VALUES (1377,88,8,'Alelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAlelu, aleluia, Glory to the Lord.\nAleluia, Glory to the Lord.');
INSERT INTO page VALUES (1378,88,9,'Every knee shall bow and ev\'ry tounge confess,\nEvery knee shall bow and ev\'ry tounge confess,\nEvery knee shall bow and ev\'ry tounge confess,\nThat Jesus Christ is Lord.\n');
INSERT INTO page VALUES (1379,89,1,'Glory, Jesus, glory,\nYou do the fighting for me.\nPraise you Jesus, praise you,\nWith you there\'s always victory.\nYou are of God, little children,\nand have over come them,\nFor greater is He that is in you,\nthan he that is in the world.');
INSERT INTO page VALUES (1380,90,1,'Your hand O god has guided\nYour flock from age to age;\nThe wondrous tale is written,\nFull clear on every page.\nOur fathers owned your goodness,\nAnd we their deeds record,\nAnd both of these bear witness,\nOne Church, one Faith, one Lord.');
INSERT INTO page VALUES (1381,90,2,'Through many a day of darkness,\nThrough many a scene of strife,\nThe faithful few fought bravely\nTo guard the nation?s life.\nTheir Gospel of redemption,\nSin pardoned, man restored.\nWas all in this enfolded,\nOne Church, one Faith, one Lord.\n');
INSERT INTO page VALUES (1382,90,3,'Your mercy will not fail us,\nNor leave your work undone;\nWith your right hand to help us,\nYour victory will be won.\nAnd then, by men and angels,\nYour name shall be adored,\nAnd this shall be their anthem,\nOne Church, one Faith, one Lord.');
INSERT INTO page VALUES (1431,91,3,'And I will run to You\nTo Your words of truth\nNot by might, not by power\nBut by the Spirit of God\nYes I will run the race\n\'Til I see Your face\nOh let me live in the \nglory of Your grace.');
INSERT INTO page VALUES (1430,91,2,'You call me to Your purpose\nAs angels understand\nFor Your glory\nMay You draw all men\nAs Your love and grace demands');
INSERT INTO page VALUES (1429,91,1,'Your Eye is on the sparrow\nAnd Your Hand, It comforts me\nFrom the ends of the earth\nTo the depths of my heart\nLet Your mercy and strength be seen');
INSERT INTO page VALUES (1437,92,6,'We Praise the Lord with our voices\nWe Praise the Lord with our hearts\nWe Praise the Lord with all our strength\nAnd everything else that we\'ve got\nWe praise His name with dancing\nWe praise His name with the drums\nCome on and lift up Jesus\' name\n\'Til the day He comes!');
INSERT INTO page VALUES (1436,92,5,'Your People sing praises,\nLet laughter fill the world.\nYour People sing praises,\nLet love and faith be heard.\nJesus came to the Rescue,\nAnd we\'re the reason He came.\nSo come on lift up a mighty voice,\n\'Til Jesus comes again.');
INSERT INTO page VALUES (1435,92,4,'Your People sing praises,\nLet laughter fill the world.\nYour People sing praises,\nLet love and faith be heard.\nThe power of death has been shattered,\nAnd Jesus ever will reign.\nSo come on lift up a mighty voice,\n\'Til Jesus comes again.');
INSERT INTO page VALUES (1434,92,3,'We Praise the Lord with our voices\nWe Praise the Lord with our hearts\nWe Praise the Lord with all our strength\nAnd everything else that we\'ve got\nWe praise His name with the drums\nCome on and lift up Jesus\' name\n\'Til the day He comes!');
INSERT INTO page VALUES (1433,92,2,'Your People sing praises,\nLet laughter fill the world.\nYour People sing praises,\nLet love and faith be heard.\nJesus came to the Rescue,\nAnd we\'re the reason He came.\nSo come on lift up a mighty voice,\n\'Til Jesus comes again.');
INSERT INTO page VALUES (1432,92,1,'Your People sing praises,\nLet laughter fill the world.\nYour People sing praises,\nLet love and faith be heard.\nThe power of death has been shattered,\nAnd Jesus ever will reign.\nSo come on lift up a mighty voice,\n\'Til Jesus comes again.');
INSERT INTO page VALUES (1393,93,1,'Father of life\nDraw me closer\nLord my heart is set on You\nLet me run the race of time\nWith Your life enfolding mine\nAnd let the peace of God\nLet it reign');
INSERT INTO page VALUES (1394,93,3,'Oh Holy Spirit\nLord, my comfort\nStrenghten me, hold my head up high\nAnd I stand upon Your Truth\nBringing glory unto You\nAnd let the peace of God\nLet it reign');
INSERT INTO page VALUES (1395,93,2,'Oh Lord I hunger\nFor more of You\nRise up within me\nLet me know Your Truth');
INSERT INTO page VALUES (1396,93,4,'Oh Lord I hunger\nFor more of You\nRise up within me\nLet me know Your Truth');
INSERT INTO page VALUES (1397,93,5,'Oh Holy spirit, saturate my soul\nAnd let the life of God\nFill me now\nLet Your healing power\nBreathe life and make me whole\nAnd let the peace of God\nLet it reign.');
INSERT INTO page VALUES (1398,93,6,'Oh Lord I hunger\nFor more of You\nRise up within me\nLet me know Your Truth');
INSERT INTO page VALUES (1499,94,4,'Jesus, what a beautiful name\nRescued my soul, my stronghold\nLifts me from shame\nForgiveness, security, power and love\nGrace that blows all fear away\nJesus what a beautiful name');
INSERT INTO page VALUES (1498,94,3,'Jesus, what a beautiful name\nTruth revealed, my future sealed\nHealed my pain\nLove and freedom, life and warmth\nGrace that blows all fear away\nJesus, what a beautiful name');
INSERT INTO page VALUES (1497,94,2,'Jesus, what a beautiful name\nRescued my soul, my stronghold\nLifts me from shame\nForgiveness, security, power and love\nGrace that blows all fear away\nJesusm what a beautiful name');
INSERT INTO page VALUES (1496,94,1,'Jesus, what a beautifiul name\nSon of God, Son of Man\nLamb that was slain\nJoy and peace, strength and hope,\nGrace that blows all fear away\nJesus, what a beautiful name');
INSERT INTO page VALUES (1403,95,1,'You make Your face to shine on me\nAnd that my soul knows very well\nYou lift me up, I\'m cleansed and free\nAnd that my soul knows very well.');
INSERT INTO page VALUES (1404,95,2,'When Mountains fall I\'ll stand\nBy the power of Your hand\nAnd in Your heart of hearts I\'ll dwell\nAnd that my soul knows very well.');
INSERT INTO page VALUES (1405,95,3,'Joy and strength each day I\'ll find\nAnd that my soul knows very well\nForgiveness, hope, I know is mine\nAnd that my soul knows very well.');
INSERT INTO page VALUES (1406,95,4,'When Mountains fall I\'ll stand\nBy the power of Your hand\nAnd in Your heart of hearts I\'ll dwell\nAnd that my soul knows very well.');
INSERT INTO page VALUES (1407,96,1,'My heart sings praises\nEach time I say Your name\nThis love is deeper\nThan simple words can say\nYou go before me\nYou make a perfect way\nMy one desire\nIs to give You perfect praise');
INSERT INTO page VALUES (1408,96,2,'In my heart\nYou are the power\nIn my night\nNever failing light\nWith every\nbreath that I take\nI\'ll declare the\nthings You\'ve done');
INSERT INTO page VALUES (1409,96,3,'In my mind\nMighty overcomer\nIn my soul\nThe reason why\nIn my life\nYou are the fire\nthat calls me on');
INSERT INTO page VALUES (1410,96,4,'And in my mind\nMighty overcomer\nIn my soul\nThe reason why\nIn my life\nYou are the fire\nthat calls me on');
INSERT INTO page VALUES (1411,97,1,'We\'re a generation\nSaved by grace and set apart\nTo change this land\n\nWe\'re standing strong and pressing on\nWe know in Jesus Christ we can\n\nThe Church of God is growing everyday\nWe\'re taking ground');
INSERT INTO page VALUES (1412,97,2,'And we are steppin\' out\n(Change our generation)\nWe\'re steppin\' out\n(Reaching every nation)\nWith the favour of God on us\nDay by Day, we\'re moving on in every way\nWe\'re steppin out');
INSERT INTO page VALUES (1413,97,3,'We\'re the chosen few\nWho speak His Word\nAnd manifest it in our lives\n\nWe\'re not moved by what the world says\nGod Jesus on our side\n\nWe\'re not dismayed\nby what we\nsee with our eyes\nWe walk by faith');
INSERT INTO page VALUES (1449,98,3,'(We\'ve got peace)\nIt\'s like a river\nAnd you\'ll never run it dry\nWe\'ve got power over fear and death\nAnd hearts filled up with joy');
INSERT INTO page VALUES (1450,98,4,'The Holy Spirit fills me up\nAnd I need him every day\nFor fire, faith and confidence\nAnd knowing what to say\nI gave my heart and all that I am\nTo the one who loves me most\nWe\'ve got love, grace, peace and power\nAnd joy in the Holy Ghost');
INSERT INTO page VALUES (1447,98,1,'I\'ve found a friend O such a friend\nHe made my heart His home\nGod Himself is with me\nAnd I know I\'m never alone\nI know all my tomorrows will be\nbetter than all my hopes\nWe\'ve got love, grace, peace and power\nAnd joy in the Holy Ghost');
INSERT INTO page VALUES (1448,98,2,'(We\'ve got love)\nMy God is never wrong\nAnd He makes time for me\n(We\'ve got grace)\nIt blew apart my chains\nAnd set this sinner free\n');
INSERT INTO page VALUES (1489,102,6,'Take my love; my Lord, I pour\nAt Thy feet its treasure store:\nTake myself, and I will be\nEver, only, all, for Thee.');
INSERT INTO page VALUES (1460,99,4,'Amazing Love, O what sacrifice,\nThe Son of God giv\'n for me.\nMy debt he pays and my death\nhe dies.\nThat I might live, that I might live');
INSERT INTO page VALUES (1459,99,3,'And so they watched Him die,\ndespised, rejected\nBut oh the blood He shed flowed\nfor me!');
INSERT INTO page VALUES (1457,99,1,'My Lord, what love is this\nThat pays so dearly that I,\nthe guilty one, may go free!');
INSERT INTO page VALUES (1458,99,2,'Amazing Love, O what sacrifice,\nThe Son of God giv\'n for me.\nMy debt he pays and my death\nhe dies.\nThat I might live, that I might live');
INSERT INTO page VALUES (1461,99,5,'And now this love of Christ\nShall flow like rivers\nCome wash your guilt away,\nlive again!');
INSERT INTO page VALUES (1462,99,6,'Amazing Love, O what sacrifice,\nThe Son of God giv\'n for me.\nMy debt he pays and my death\nhe dies.\nThat I might live, that I might live');
INSERT INTO page VALUES (1500,100,1,'He gave me beauty for ashes\nThe oil of joy for mourning\nThe garment of praise for the\nspirit of heaviness\nThe we might be trees of \nrighteousness\nThe planting of the Lord\nThat he might be glorified');
INSERT INTO page VALUES (1477,101,4,'Angels, help us to adore him;\nYe behold him face to face;\nSun and moon, bow down before him,\nDwellers all in time and space,\n\nPraise him, praise him,\nPraise him, Praise him,\nPraise with us the God of grace.');
INSERT INTO page VALUES (1476,101,3,'Fatherlike, he tends and spares us;\nWell our feeble frame he knows;\nIn his hands he gently bears us,\nRescues us from all our foes;\n\nPraise him, praise Him,\nPraise him, praise him,\nWidely as his mercy flows.');
INSERT INTO page VALUES (1475,101,2,'Praise him for his grace and favour\nTo our fathers in distress;\nPraise him, still the same for ever,\nSlow to chide, and swift to bless;\n\nPraise him, praise him,\nPraise him, praise him,\nGlorious in his faithfullness.');
INSERT INTO page VALUES (1474,101,1,'Praise, my soul, the King of heaven,\nTo his Feet thy tribute bring;\nRansomed, healed, restored, forgiven,\nWho like thee, his praise should sing?\n\nPraise him, praise him,\nPraise him, praise him,\nPraise the everlasting King.');
INSERT INTO page VALUES (1488,102,5,'Take my will, and make it Thine;\nIt shall no be longer mine:\nTake my heart, it is Thine own;\nIt shall be Thy royal throne.');
INSERT INTO page VALUES (1487,102,4,'Take my silver, and my gold,\nNot a mite would I with-hold;\nTake my intelect, and use\nEv\'ry pow\'r as Thou shalt choose.');
INSERT INTO page VALUES (1486,102,3,'Take my voice, and let me sing\nAlways, only, for my King;\nTake my lips, and let them be\nFilled with messages from Thee.');
INSERT INTO page VALUES (1485,102,2,'Take my hands, and let them move\nAt the impulse of Thy love;\nTake my feet, and let them be\nSwift and beautiful for Thee.');
INSERT INTO page VALUES (1484,102,1,'Take my life, And let it be \nConsecrated, Lord, to Thee;\nTake my moments and my days,\nLet them flow in cease-less praise.');
INSERT INTO page VALUES (1511,103,3,'When I tread on the verge of Jordan,\nBid my anxious fears subside;\nDeath of death, and hell\'s destruction,\nLand me safe on Canaan\'s side;\nSongs of praises, songs of praises,\nI will ever give to Thee (give to Thee)\nI will ever give to Thee.');
INSERT INTO page VALUES (1510,103,2,'Open now the crystal fountain,\nWhence the healing stream doth flow;\nLet the fire and cloudy pilar\nLead me all my journey through;\nStrong Deliverer, strong Deliverer,\nBe Thou still my strength and\nshield (strength and shield)\nBe Thou still my strength and shield.');
INSERT INTO page VALUES (1509,103,1,'Guide me, O thou great Jehovah,\nPilgrim through this barren land;\nI am weak, but Thou art mighty;\nHold me with Thy powerful hand;\nBread of heaven, Bread of heaven,\nFeed me till I want no\nmore (want no more)\nFeed me till I want no more.');
INSERT INTO page VALUES (1525,104,3,'A glorious band, the chosen few\nOn whom the spirit came,\nTwelve valient saints, their hope they knew,\nAnd mocked the cross and flame;\nThey climbed the steep ascent of heaven\nThrough peril, toil, and pain:\nO God, to us may grace be given\nTo follow in their train!');
INSERT INTO page VALUES (1524,104,2,'The martyr first, whose eagle eye\nCould pierce behind the grave,\nWho saw his master in the sky,\nAnd called on him to save:\nLike him, with pardon on his tongue,\nIn midst of mortal pain,\nHe prayed for them that did the wrong:\nWho follows in his train?');
INSERT INTO page VALUES (1523,104,1,'The Son of God goes forth to war,\nA kingly crown to gain;\nHis blood-red banner, streams afar;\nWho follows in his train?\nWho can drink his cup of woe,\nTriumphant over pain,\nWho patient bears his cross below,\nHe follows in his train.');
INSERT INTO page VALUES (1630,108,4,'On His word I\'m feeding, I shall not be moved;\nHe\'s the One that\'s leading, I shall not be moved,\nJust like a tree that planted by the waters, Lord,\nI shall not be moved, I shall not be, \nI shall not be moved;\nI shall not be, I shall not be moved;\nJust like a tree that planted by the waters, Lord,\nI shall not be moved (be moved).');
INSERT INTO page VALUES (1629,108,3,'If I trust Him ever, I shall not be moved;\nHe will fail me never, I shall not be moved,\nJust like a tree that planted by the waters, Lord,\nI shall not be moved, I shall not be, \nI shall not be moved;\nI shall not be, I shall not be moved;\nJust like a tree that planted by the waters, Lord,\nI shall not be moved (be moved).');
INSERT INTO page VALUES (1628,108,2,'In my Christ abiding, I shall not be moved;\nIn His love I\'m hiding, I shall not be moved,\nJust like a tree that planted by the waters, Lord,\nI shall not be moved, I shall not be, \nI shall not be moved;\nI shall not be, I shall not be moved;\nJust like a tree that planted by the waters, Lord,\nI shall not be moved (be moved).');
INSERT INTO page VALUES (1627,108,1,'Jesus is my Saviour, I shall not be moved;\nIn His love and favour, I shall not be moved,\nJust like a tree that planted by the waters, Lord,\nI shall not be moved, I shall not be, \nI shall not be moved;\nI shall not be, I shall not be moved;\nJust like a tree that planted by the waters, Lord,\nI shall not be moved (be moved).\n');
INSERT INTO page VALUES (1519,109,1,'Oh, Lord you lead me\nby the still waters\nQuietly restoring my soul\nYou speak words of wisdom\nThe promoise of glory\nThe power of the presence of God');
INSERT INTO page VALUES (1520,109,2,'Have faith in God\nLet your faith rest on the\nfaith he has placed in your heart\nNever give up, Never let go of\nthe faith he has placed in your heart');
INSERT INTO page VALUES (1521,109,3,'O, Lord you guide me\nThrough all the darkness\nTurning my night into day\nYou\'ll never leave me\nNever forsake me\nThe power of the presence of God');
INSERT INTO page VALUES (1522,109,4,'Have faith in God\nLet your faith rest on the\nfaith he has placed in your heart\nNever give up, Never let go of\nthe faith he has placed in your heart');
INSERT INTO page VALUES (1534,110,1,'Blessed be the rock of my salvation\nBlessed be the rock of my salvation\nFor the Lord is on my side\nAnd he\'s made his victory mine\nBlessed be the rock of my salvation\n(repeat)');
INSERT INTO page VALUES (1535,110,2,'Blessed be the rock!\nBlessed be the rock!\nBlessed be the rock!\nBlessed be the rock!\nBlessed be the rock of my salvation!');
INSERT INTO page VALUES (1541,111,2,'Look and see I\'ve engraved you\nOn the palms of my hands\nLook and see I\'ve engraved you\nOn my hands\n(Repeat)');
INSERT INTO page VALUES (1694,116,5,'Spirit we need you\nTo lift us from this mire\nConsume and empower us\nWith your holy fire.');
INSERT INTO page VALUES (1693,116,4,'All the earth shall worship\nAt the throne of the king\nOf his great and awesome power we shall sing.\nAll the earth shall worship\nAt the throne of the king\nOf his great and awesome power we shall sing.\n');
INSERT INTO page VALUES (1692,116,3,'Jesus we love you\nBecause you first loved us\nYou reached out and healed us\nWith your mighty touch');
INSERT INTO page VALUES (1690,116,1,'Father we adore you\nYou\'ve drawn us to this place.\nWe bow down before you\nHumbly on our face');
INSERT INTO page VALUES (1691,116,2,'All the earth shall worship\nAt the throne of the king\nOf his great and awesome power we shall sing.\nAll the earth shall worship\nAt the throne of the king\nOf his great and awesome power we shall sing.\n');
INSERT INTO page VALUES (1814,124,2,'I will lift my voice\nto worship you my King\nI will find my strength\nin the shadow of your wings');
INSERT INTO page VALUES (1717,119,1,'I\'m reaching for the prize\nI\'m giving everything\nI give my life for this\nIt\'s what I live for\nNothing will keep me from\nAll that You have for me\nYou hold my head up high\nI live for You\n');
INSERT INTO page VALUES (1718,119,2,'Greater is He that\'s living in me\nThan he that is in the world\n');
INSERT INTO page VALUES (1719,119,3,'              Faith\nI can move the mountain\n  I can do all the things\n  through Christ I know\n              Faith\n Standing and beleiving\n  Through Christ who\n     strengthens me');
INSERT INTO page VALUES (2097,136,1,'You loved me as you found me\nYour love keeps following me\nYou wrapped your arms around me\nYour love keeps following me\nBy grace I\'m what I should be me\nYour love keeps following me\nYou saw me as I could be\nYour love keeps following me');
INSERT INTO page VALUES (2099,136,3,'Your love keeps following me\n(repeat a couple of times)');
INSERT INTO page VALUES (1723,121,1,'I love Jesus\nYes I do\nI love Jesus\nHow \'bout you\n(repeat x4)');
INSERT INTO page VALUES (1724,121,2,'And It makes me wana sing\nJesus Lives\nIt makes me wana sing\nHe lives in me\nIt makes me wana sing\nNow I live\nIt makes me wana sing\nIn victory');
INSERT INTO page VALUES (1725,121,3,'Jesus lives\nHe lives in me\nNow I live\nIn victory\n\n');
INSERT INTO page VALUES (1977,133,1,'Here is bread, here is wine\nChrist is with us, He is with us.\nBreak the bread, drink the wine,\nChrist is with us here.');
INSERT INTO page VALUES (1806,122,3,'Your love is stronger than\nThe sound of Heaven\'s praises\nHigher than the lofty mountain peaks\nDeeper than the deepest ocean valleys\nStrong enough for me');
INSERT INTO page VALUES (1805,122,2,'You wash away my tears\nGave my joy and freedom\nLifting me through the years');
INSERT INTO page VALUES (1804,122,1,'Oh Lord You have shown Your favour\nYour every word stands true\nAnd I\'m found safe within Your harbour\nAnchored deep in You');
INSERT INTO page VALUES (2817,45,3,'This Term:\n02/03 - Special secret guest speaker\n16/03 - PULSE are coming back to\n          play their awesome brand of\n          praise/worship and rock for us\n23/03 - COAST UNITED combined\n          at TLC (old Mingara - Tumbi Umbi)');
INSERT INTO page VALUES (1918,123,6,'And I surrender\nAll to you\nAll to you\n(repeat)');
INSERT INTO page VALUES (1916,123,4,'And I surrender\nAll to you\nAll to you\n(repeat x4)');
INSERT INTO page VALUES (2722,125,8,'And angels come and adore You\nAnd we your children worship You');
INSERT INTO page VALUES (2723,125,9,'You are my world, You are my God\nAnd I lay down my life for you\nYou are my Lord the one that I love\nNo one could ever take your place\n(repeat)');
INSERT INTO page VALUES (2720,125,6,'You are my world, You are my God\nAnd I lay down my life for you\nYou are my Lord the one that I love\nNo one could ever take your place\n(repeat)');
INSERT INTO page VALUES (2818,45,4,'Setup and Pulldown team:\nWe are currently looking\nfor people to volunteer to\nhelp out before and after\nONE80 on a setup and\npulldown roster. If you are\navailable and willing please\nsee Mal tonite');
INSERT INTO page VALUES (1807,122,4,'Oh Lord You have shown Your favour\nYour every word stands true\nAnd I\'m found safe within Your harbour\nAnchored deep in You');
INSERT INTO page VALUES (1808,122,5,'You wash away my tears\nGave my joy and freedom\nLifting me through the years');
INSERT INTO page VALUES (1809,122,6,'Your love is stronger than\nThe sound of Heaven\'s praises\nHigher than the lofty mountain peaks\nDeeper than the deepest ocean valleys\nStrong enough for me');
INSERT INTO page VALUES (1810,122,7,'');
INSERT INTO page VALUES (1811,122,8,'You wash away my tears\nGave my joy and freedom\nLifting me through the years');
INSERT INTO page VALUES (1812,122,9,'Your love is stronger than\nThe sound of Heaven\'s praises\nHigher than the lofty mountain peaks\nDeeper than the deepest ocean valleys\nStrong enough for me');
INSERT INTO page VALUES (1815,124,3,'Your love oh Lord\nReaches to the Heavens\nYour faithfullnes\nStretches to the sky');
INSERT INTO page VALUES (1917,123,5,'I\'m singing You this song\nI\'m waiting at the cross\nAnd all the world holds dear\nI count it all as loss\nFor the sake of knowing You\nThe glory of your name\nTo know the everlasting joy\nEven sharig in your pain');
INSERT INTO page VALUES (1915,123,3,'I\'m singing You this song\nI\'m waiting at the cross\nAnd all the world holds dear\nI count it all as loss\nFor the sake of knowing You\nThe glory of your name\nTo know the everlasting joy\nEven sharig in your pain');
INSERT INTO page VALUES (1914,123,2,'And I surrender\nAll to you\nAll to you\n(repeat x2)');
INSERT INTO page VALUES (1913,123,1,'I\'m giving you my heart and all that is within\nI lay it down for the sake of  you my king\nIm giving you my dreams\nI\'m laying down my rights\nI\'m giving up my pride\nFor the Promise of new life');
INSERT INTO page VALUES (2014,134,1,'I\'m changed I\'m not the same\nThe Father called me by my name\nHe called me through His Son\nThe Father\'s holy righteous One \n(repeat)\n\nWe are the first fruits\nThe Children of the King');
INSERT INTO page VALUES (1892,126,1,'Melts	(available from 6.30pm)	           $2.00\n- options: cheese, tomato, ham, pineapple\nChicken Burgers					        $2.50\nstandard: lettuce, tomato, cheese & mayo\nExtra: sweet chili sauce, sour cream        20c\nMeat Pies							$1.50\nSausage Rolls						$1.00\nsauce								 	  .10\n');
INSERT INTO page VALUES (2421,141,4,'Let this be a holy moment now\n            (repeat)');
INSERT INTO page VALUES (2419,141,2,'Come, come, come,\nlet us worship God,\nWith Our hands held high,\nand our hearts bowed down\nWe will run, run, run,\nthrough your gates, oh God\nWith a shout of love,\nWith a shout of love.');
INSERT INTO page VALUES (2721,125,7,'And everything I have I give\nto You my Lord the one I live for\nI live for You\nAnd all my days are gifts from You\nI pray I use them as you want me to\nuse them for You.');
INSERT INTO page VALUES (2719,125,5,'And angels come and adore You\nAnd we your children worship You');
INSERT INTO page VALUES (2718,125,4,'And everything I have I give\nto You my Lord the one I live for\nI live for You\nAnd all my days are gifts from You\nI pray I use them as you want me to\nuse them for You.');
INSERT INTO page VALUES (2716,125,2,'And angels come and adore You\nAnd we your children worship You');
INSERT INTO page VALUES (2717,125,3,'You are my world, You are my God\nAnd I lay down my life for you\nYou are my Lord the one that I love\nNo one could ever take your place');
INSERT INTO page VALUES (1893,126,2,'Sundaes								$2.00\noptions: choc, strawberry, caramel sauce, nuts, wafers	\nCoffee-								   50c\nTea-								   50c\nMilo-  with marshmallows			$1.20\nSpiders - coke, orange, raspberry	$1.50\nCans-								$1.20\nChips-								$1.20\nLollies-	 			big			$1.20\n						Small	  	70c		');
INSERT INTO page VALUES (2015,134,2,'Praise to the Father of Lights\nIn Him there\'s day there is no night\nEvery good gift comes from above\nA certain sign of the Father\'s love\n(repeat)');
INSERT INTO page VALUES (2107,137,3,'So let me say how much I love You\nWith all my heart I long for You\nFor I am caught in this passion of knowing\nThis endless love I\'ve found in You\n\nAnd the depth of grace, the forgiveness found\nTo be called a child of God\nJust makes me say how much I love You\nO my Saviour, my Lord and friend');
INSERT INTO page VALUES (2715,125,1,'My Father I adore You more\nThan anything my heart could wish for\nI just want You\nAnd Jesus my beloved Savior,\nEverything I have I owe to You\nI owe it all to You');
INSERT INTO page VALUES (2819,45,5,'Lyric display System Written by\nChris Debanham\nhttp://lds.sourceforge.net');
INSERT INTO page VALUES (2030,135,4,'I sing for joy\nAt the work of Your hands\nForever I\'ll love You\nForever I\'ll stand\nNothing compares to the promise\nI have in You');
INSERT INTO page VALUES (2029,135,3,'Shout to the Lord\nAll the earth let us sing\nPower and majesty\nPraise to the King\nMountains bow down\nAnd the seas will roar\nAt the sound of Your name');
INSERT INTO page VALUES (2027,135,1,'My Jesus, my Saviour\nLord there is none like you\nAll of my days, I want to praise\nThe wonders of your mighty love');
INSERT INTO page VALUES (2028,135,2,'My comfort, my shelter\nTower of refuge and strength\nlet every breath, all that I am\nNever cease to worship you');
INSERT INTO page VALUES (2016,134,3,'He made me in his image\nAnd I\'m wonderfully made\nHe saved me through His only Son\nAnd I\'m wonderfully saved');
INSERT INTO page VALUES (2098,136,2,'And it\'s higher\n(reaches from heaven to man)\nIt\'s wider\n(anyone can come in)\nIt\'s deeper\n(it covers any sin)\nAnd I know one thing\nWhere I go\nI know...');
INSERT INTO page VALUES (2428,145,2,'You have stolen my heart\nI\'m captivated by you\nNever will you and I part\nI\'m falling deeply in love with you');
INSERT INTO page VALUES (2373,129,5,'I\'ve found where I belong\nI\'m a living stone\nIn this house I will grow');
INSERT INTO page VALUES (2370,129,2,'God is awesome in this place\nWe sense His presence\nAs we sing His praise\n');
INSERT INTO page VALUES (2371,129,3,'There is Power here for miracles\nTo set the captives free\nAnd make the Broken Whole\n');
INSERT INTO page VALUES (1962,130,1,'You set me apart\nGave me a new heart\nFiled me with compassion\nTo share Your great love\nShow me your way\nI want to know You\nGuide me in truth\nMy hope is in You\n');
INSERT INTO page VALUES (1963,130,2,'That I may\nDwell in Your house forever\nLifting up Your name\nDwell In Your house forever more\n');
INSERT INTO page VALUES (1964,130,3,'I\'ll hold on to You\nMy strength an my refuge\nWhom shal I fear\nI know You are near\nAll of my days\nI live for You Lord\nEstablish my path\nThere\'s one thing I ask\n');
INSERT INTO page VALUES (1965,130,4,'Holy Spirit have your way\nSweet anointing teach our hearts,\nour lives we pray');
INSERT INTO page VALUES (1993,131,5,'You\'re my friend and you are my brother,\nEven though you are a King,\nI love you more than any other,\nSo much more than anything');
INSERT INTO page VALUES (1992,131,4,'You alone are my strength, my shield,\nTo you alone may my spirit yield, \nYou alone are my hearts desire,\nAnd I long to worship you.');
INSERT INTO page VALUES (1990,131,2,'You alone are my strength, my shield,\nTo you alone may my spirit yield, \nYou alone are my hearts desire,\nAnd I long to worship you.');
INSERT INTO page VALUES (1991,131,3,'I want you more than gold or silver,\nOnly you can satisfy,\nYou alone are the real joy giver,\nAnd the apple of my eye.');
INSERT INTO page VALUES (1989,131,1,'As the deer pants for the water,\nSo my soul longs after you,\nYou alone are my hearts desire, \nAnd I long to worship you.');
INSERT INTO page VALUES (1998,132,4,'Brothers this Lord Jesus\nShall return again,\nWith His Fathers glory,\nWith His angel train,\nFor all wreaths of empire,\nMeet upon His brow,\nAnd our hearts confess Him,\nKing of glory now.');
INSERT INTO page VALUES (1997,132,3,'In our hearts enthrone Him,\nThere let Him subdue,\nAll that is not Holy,\nAll that is not true,\nCrown Him as your captain,\nIn temptations hour,\nLet His will enfold you,\nIn its light and power.\n');
INSERT INTO page VALUES (1996,132,2,'Humbled for a season,\nTo receive a name,\nFrom the lips of sinners,\nUnto whom He came,\nFaithfully He bore it,\nSpotless to the last,\nBrought it back victorious,\nWhen from death He passed.\n');
INSERT INTO page VALUES (1995,132,1,'At the name of Jesus,\nEvery knee shall bow,\nEvery tongue confess him,\nKing of glory now.\nIt\'s the father pleasure,\nWe should call Him Lord,\nWho from the beginning,\nWas the mighty Word.\n');
INSERT INTO page VALUES (1978,133,2,'In this bread there is healing\nIn this cup there\'s life for ever.\nIn this moment, by the Spirit\nChrist is with us here.');
INSERT INTO page VALUES (1979,133,3,'Here is grace, here is peace,\nChrist is with us, He is with us.\nKnow His grace, find His peace,\nFeast on Jesus here.');
INSERT INTO page VALUES (1980,133,4,'In this bread there is healing\nIn this cup there\'s life for ever.\nIn this moment, by the Spirit\nChrist is with us here.');
INSERT INTO page VALUES (1981,133,5,'Here we are, joined in One,\nChrist is with us, He is with us.\nWe\'ll proclaim \'til He comes\nJesus crucified.');
INSERT INTO page VALUES (1982,133,6,'In this bread there is healing\nIn this cup there\'s life for ever.\nIn this moment, by the Spirit\nChrist is with us here.');
INSERT INTO page VALUES (1994,131,6,'You alone are my strength, my shield,\nTo you alone may my spirit yield, \nYou alone are my hearts desire,\nAnd I long to worship you.');
INSERT INTO page VALUES (2420,141,3,'Lord with confidence we come \nbefore your throne of grace\nNot that we deserve to come\nbut you have paid the way\nYou are the Holy King of all,\nHeaven and Earth are in your hands,\nAll of the angels sing your song,\nwe join them now.');
INSERT INTO page VALUES (2815,45,1,'Tonights service at 6:30:\nWe will start showing the\nAlpha video series.');
INSERT INTO page VALUES (2816,45,2,'Please take a moment now\nto turn off or silence\nyour mobile phones or\npersonal electronic devices!');
INSERT INTO page VALUES (2473,147,2,'And your steadfast love\nMay your name be exalted\nHere on earth\nAnd in heav\'n above\nLai, lai, lai...');
INSERT INTO page VALUES (2322,142,1,'All creation cries to you\nWorshipping in spirit and in truth\nGlory to the faithfull one\nJesus Christ God\'s son');
INSERT INTO page VALUES (2372,129,4,'God is awesome\nHe\'s so awesome\nGod is awesome in this place\n');
INSERT INTO page VALUES (2106,137,2,'Just let me hear Your finest whispers\nAs you gently call my name\nAnd let me see Your power and Your glory\nLet me feel Your Spirit\'s flame\n\nLet me find You in the desert\n\'til this sand is holy ground\nAnd I am found completely surrendered\nTo You, my Lord and friend');
INSERT INTO page VALUES (2105,137,1,'Just let me say how much I love You\nLet me speak of Your mercy and grace\nJust let me live in the shadow of Your beauty\nLet me see you face to face\n\nAnd the earth will shake as Your Word goes forth\nThe heavens can tremble and fall\nBut let me say how much I love You\nO my Saviour, my Lord and friend');
INSERT INTO page VALUES (2082,138,5,'The power and the glory of Your name\nThe power and the glory of Your name\nThe power and the glory of Your name\nThe name of the Lord\nThe Son of God');
INSERT INTO page VALUES (2081,138,4,'This life is mine\nSo perfect and so pure, this God in me\nThis glorious hope\nFrom earth to heaven, death to life\nThis future assured and secured\nBy this love in my heart');
INSERT INTO page VALUES (2080,138,3,'The power and the glory of Your name\nThe power and the glory of Your name\nThe power and the glory of Your name\nThe name of the Lord\nThe Son of God');
INSERT INTO page VALUES (2079,138,2,'This love is mine\nSo undeserved this glorious name\nThis Son, this God\nThis life, this death, this victory won\nForgiveness has flowed as this grace\nThat is mine fills my heart');
INSERT INTO page VALUES (2078,138,1,'This grace is mine\nThis glory earthbound, heaven sent\nThis plan divine\nThis life, this light that breaks my night\nThe Spirit of God, heaven falls like a dove\nTo my heart');
INSERT INTO page VALUES (2424,143,3,'I\'m living for this cause\nI lay down my life \nInto Your hands');
INSERT INTO page VALUES (2425,143,4,'I\'m living for the truth\nThe hope of the world\nIn You I\'ll stand\nCause all I want is You');
INSERT INTO page VALUES (2324,142,3,'All creation gives praise to you\nYou alone are truly great\nYou alone are God who reigns\nFor eternity');
INSERT INTO page VALUES (2326,142,5,'Holy is the Lord the whole Earth sings\nThe whole Earth sings');
INSERT INTO page VALUES (2325,142,4,'All to you O God we bring\nJesus teach us how live\nLet your fire burn in us\nthat all may hear\nAnd all may see');
INSERT INTO page VALUES (2369,129,1,'Here in this house\nof the Great King\nWe\'ve come together\nnow to worship Him\nThis house is built\non Christ our Rock\nCan not be shaken,\nCan not be shaken.');
INSERT INTO page VALUES (2562,154,2,'And this kingdom will know no end\nAnd it\'s glory shall know no bounds\nFor the majesty and power\nOf this kingdom\'s King has come\nAnd this kingdom\'s reign\nAnd this kingdom\'s rule\nAnd this kingdom\'s power and authority\nJesus, God\'s righteousness revealed');
INSERT INTO page VALUES (2418,141,1,'   As we come today, we remind ourselves\n                 Of what we do\n That these songs are not just songs but signs\n                 of love for You\n          This is a holy moment now,\n      Something of heaven touches earth,\nVoices of angels all resound, we join their song');
INSERT INTO page VALUES (2323,142,2,'God is great and his praise\nfills the earth, Fills the Heavens\nAnd Your name will be praised\nthrough all the Earth\nGod is great sing his praise\nAll the Earth, All the Heavens\n\'Cause we\'re living for \nthe glory of your name');
INSERT INTO page VALUES (2446,148,1,'Jesus is Lord!\nCreation\'s voice proclaims it\nFor by his power, each tree and flower\nWas planned and made\nJesus is Lord!\nThe universe declares it\nSun, moon and stars in heaven\nCry Jesus is Lord!...');
INSERT INTO page VALUES (2824,155,4,'Jesus has risen\nHe\'s conquered the grave! \n[repeat]\n\nHey!');
INSERT INTO page VALUES (2426,143,5,'All I want is\nAll I want is You.....Jesus');
INSERT INTO page VALUES (2423,143,2,'Let Your presence fall upon us\nI want to see You face to face\nLet me live forever lost in Your love\n\'Cause all I want is more of You\nAll I want is more of You');
INSERT INTO page VALUES (2422,143,1,'Hope has found its home within me\nNow that i\'ve been found in you\nLet all i am be all You want me to be\n\'Cause all i want is more of You\n\n');
INSERT INTO page VALUES (2332,144,1,'Lord You have my heart\nAnd I will search for yours\nJesus take my life\nAnd lead me on');
INSERT INTO page VALUES (2333,144,2,'Lord You have my heart\nAnd I will search for yours\nAnd let me be Your sacrifice');
INSERT INTO page VALUES (2334,144,3,'And I will praise You Lord\nAnd I will sing of love come down\nAs You show me your face\nWe\'ll see your glory here');
INSERT INTO page VALUES (2429,145,3,'You and I together forever\nNothing can stand in the way\nMy love for you\nGrows stronger each new day\nI\'m falling deeply in love with you');
INSERT INTO page VALUES (2427,145,1,'In my life\nYou\'ve heard me say\nI love you\nHow do I show it\'s true\nHear my heart\nIt longs for more more of you\nI\'m falling deeply in love with you');
INSERT INTO page VALUES (2409,146,3,'\n\n\n\n\n\n\nTrust in the Lord with all your heart\nand learn not on your own understanding;\nIn all your ways acknowledge him,\nand he will make your paths straight.\n');
INSERT INTO page VALUES (2407,146,1,'\n\n\n\n\nYou\'re blessed when you stay on the course,\nwalking steadily on the road revealed by God.\nYou\'re blessed when you follow His directions, \ndoing your best to find Him.\nThat\'s right, you do not go off on your own\nYou walk straight along the road he set.');
INSERT INTO page VALUES (2408,146,2,'\n\n\n\n\nGod teach me lessons for living\nso I can stay on the course\nGive me insight so I can do what You tell me\nMy whole life one long obedient response\nGuide me down the road of your commandments\nI love traveling this freeway!');
INSERT INTO page VALUES (2472,147,1,'In the presence of your people\nI will praise your name\nFor alone you are holy\nEnthroned on the praises of Israel\nLet us celebrate your goodness\n');
INSERT INTO page VALUES (2447,148,3,'Jesus is Lord!\nYet from his throne eternal\nIn flesh he came,\nto die in pain\nOn Calv\'ry\'s tree\nJesus is Lord!\nFrom him all life proceeding\nYet gave his life a ransom\nThus setting us free...');
INSERT INTO page VALUES (2448,148,5,'Jesus is Lord!\nO\'er sin the mighty conqueror\nFrom death he rose and all his foes\nShall own his name\nJesus is Lord!\nGod sent his Holy Spirit\nTo show by works of power \nThat Jesus is Lord...');
INSERT INTO page VALUES (2449,148,2,'Jesus is Lord! Jesus is Lord!\nPraise him with hallelujahs\nFor Jesus is Lord!\n');
INSERT INTO page VALUES (2450,148,4,'Jesus is Lord! Jesus is Lord!\nPraise him with hallelujahs\nFor Jesus is Lord!\n');
INSERT INTO page VALUES (2451,148,6,'Jesus is Lord! Jesus is Lord!\nPraise him with hallelujahs\nFor Jesus is Lord!');
INSERT INTO page VALUES (2560,149,5,'Hallelujah Hallelujah, \nHallelujah Hallelujah, \nAnd we lift our hearts before you \nAs a token of our love,\nHallelujah Hallelujah.');
INSERT INTO page VALUES (2559,149,4,'Holy Spirit, Holy Spirit,\nCome and fill our hearts anew Holy Spirit,\nAnd we lift our voice before you \nAs a token of our love,\nHoly Spirit, Holy Spirit.\n');
INSERT INTO page VALUES (2556,149,1,'Holy, Holy, Holy, Holy, \nHoly, Holy, Lord God Almighty,\nAnd we lift our hearts before you\nAs a token of our love,\nHoly, Holy, Holy, Holy.\n');
INSERT INTO page VALUES (2557,149,2,'Gracious Father, Gracious Father,\nWe\'re so blest to be your children \nGracious Father,\nAnd we lift our heads before you \nAs a token of our love,\nGracious Father, Gracious Father.\n');
INSERT INTO page VALUES (2558,149,3,'Precious Jesus, Precious Jesus,\nWe\'re so glad that you\'ve redeemed us,\nprecious Jesus,\nAnd we lift our hands before you \nAs a token of our love,\nPrecious Jesus, Precious Jesus.\n');
INSERT INTO page VALUES (2471,150,4,'Holy, Holy, Holy, Lord God almighty\nAll thy works shall praise thy Name,\nin earth and sky and sea;\nHoly, Holy, Holy, Merciful and Mighty\nGod in three Persons blessed Trinity\nAmen.');
INSERT INTO page VALUES (2470,150,3,'Holy, Holy, Holy, Though the darkness hide thee,\nThou the eye of sinful man thy glory may not see;\nOnly thou art holy; there is none beside thee\nPerfect in pow\'r, in love and purity.\n');
INSERT INTO page VALUES (2469,150,2,'Holy, Holy, Holy, All the saints adore thee\nCasting dow their golden crowns around the glasy sea;\nCherubim and Seraphim falling down before thee\nWho wert, and art, and evermore shalt be.');
INSERT INTO page VALUES (2468,150,1,'Holy, Holy, Holy, Lord God almighty\nEarly in the morning our song shall rise to thee;\nHoly, Holy, Holy, Merciful and Mighty\nGod in three Persons blessed Trinity');
INSERT INTO page VALUES (2823,155,3,'We are a people of power\nWe are a people of praise!\nWe are a people of promise\nJesus has risen\nHe\'s conquered the grave!');
INSERT INTO page VALUES (2549,152,5,'CHRISTIANS:\n1. Yes, we believe in God - Creator \nof heaven and Earth and of all there is!\n\n2. We believe God as revealed Himself in \nmany ways:- Creation, History, Providence, \nProphets and that God\'s final and \nfull Revelation of Himself is in \nJesus Christ our Lord!');
INSERT INTO page VALUES (2550,152,6,'3. God\'s final and full Revelation is \nthrough the Life, Teaching, Ministry, \nDeath and Glorious Resurrection \nor our Lord Jesus Christ.\n\n4. To see Jesus is to see God.\nTo hear Jesus is to hear God.\nTo know Jesus is to know God.');
INSERT INTO page VALUES (2548,152,4,'AGNOSTICS:\n1. Gnostic meaning knowledge\n\n2. The A being the prefic for anti = \nNO KNOWLEDGE!\n\n3. We do not know whether there is or \nisn\'t a God - we have no way of knowing.');
INSERT INTO page VALUES (2544,152,7,'This is life to know the only true God \nand Jesus Christ whom God has sent.\nJohn 17:3\n');
INSERT INTO page VALUES (2545,152,1,'What are we?\n\nIsaiah 44:11-20\nRomans 1:18-25\nJohn 14:1-11');
INSERT INTO page VALUES (2546,152,2,'THEISTS:\n1. From the Greek word Theos = God\n2. Belief in a Supreme Being - Creator and Ruler\n3. But not Personal.\n4. We are not merely Theists - \nmany others believe in God.');
INSERT INTO page VALUES (2547,152,3,'ATHEISTS:\n1. The prefix A for anti - NO GOD!\n\n2. Most Aussies who profess faith \nin God are for all practical purposes \nAtheists - God is not central to their lives!');
INSERT INTO page VALUES (2485,153,1,'Master, speak! Thy servant heareth,\nWaiting for Thy gracious word,\nLonging for Thy voice that cheereth;\nMaster let it now be heard.\nI am listening Lord, for Thee!\nWhat hast Thou to say to me?');
INSERT INTO page VALUES (2486,153,2,'Speak to me by name, O Master,\nLet me know it is to me;\nSpeak that I may follow faster,\nWith a step more firm and free,\nWhere the Shepherd leads the flock,\nin the shadow of the rock.');
INSERT INTO page VALUES (2487,153,3,'Master, speak! though least and lowest\nLet me not unheard depart;\nMater speak: for Oh, Thou knowest\nAll the yearning of my heart;\nKnowest all its truest need;\nSpeak and make me blest indeed.');
INSERT INTO page VALUES (2488,153,4,'Master, speak! and make me ready,\nWhen Thy voice is truly heard,\nWith obedience glad and steady\nStill to follow ev\'ry word.\nI am listening, Lord, for Thee,\nMaster, speak, O speak to me!');
INSERT INTO page VALUES (2561,154,1,'Jesus, God\'s righteousness revealed\nThe son of man, the son of God\nHis Kingdom comes\nJesus redemption\'s sacrifice\nnow glorified, now justified\nHis Kingdom comes');
INSERT INTO page VALUES (2640,157,3,'\'...honouring and taking the small step,\ntrusting God is always bigger than\nour imaginations\'\n\n\'Care is the only thing the \nsystem cannot produce\'');
INSERT INTO page VALUES (2563,154,3,'Jesus, the expression of God\'s love\nThe grace of God, the word of God\nRevealed to us\nJesus, God\'s holiness displayed\nnow glorified, now justified\nHis kingdom comes');
INSERT INTO page VALUES (2564,154,4,'And this kingdom will know no end\nAnd it\'s glory shall know no bounds\nFor the majesty and power\nOf this kingdom\'s King has come\nAnd this kingdom\'s reign\nAnd this kingdom\'s rule\nAnd this kingdom\'s power and authority\nJesus, God\'s righteousness revealed');
INSERT INTO page VALUES (2822,155,2,'Risen, yes, born again!\nWe walk in the power of his name!\nPower to be the sons of God,\nSons of God!\nSons of God!\nWe are the sons,\nHey!\nSons of God!\nHey! Hey! Hey!');
INSERT INTO page VALUES (2656,156,5,'Your grace and Your mercy is all I need,\nYour loving kindness,\nYour hope and Your peace.\nReaching for Your love my soul finds release,\nYour grace and Your mercy is all I need.');
INSERT INTO page VALUES (2655,156,4,'You lift my eyes to see\nthe hope I have in You.\nYou gently heal my heart,\nYour love and life burst through\nThe darkness of my soul,\nThe troubles and the pain,\nYour grace and Your mercy \nIs all I need.');
INSERT INTO page VALUES (2654,156,3,'Your grace and Your mercy is all I need,\nYour loving kindness,\nYour hope and Your peace.\nReaching for Your love my soul finds release,\nYour grace and Your mercy is all I need.');
INSERT INTO page VALUES (2652,156,1,'Your grace and Your mercy is all I need,\nYour loving kindness,\nYour hope and Your peace.\nReaching for Your love my soul finds release,\nYour grace and Your mercy is all I need.\n(repeat)');
INSERT INTO page VALUES (2653,156,2,'I open my heart\nto the One who knows me best.\nYour grace and righteousness,\nPeace and perfect rest.\nMy heavy heart released,\nMy soul is now restored,\nYour grace and Your mercy \nIs all I need.');
INSERT INTO page VALUES (2657,158,1,'What a friend I\'ve found,\nCloser than a brother.\nI have felt Your touch,\nMore intimate than lovers.');
INSERT INTO page VALUES (2704,159,1,'I\'ll worship at your throne,\nwhisper my own love song.\nWith al my heart I\'ll sing,\nfor You my dad and King.\nI\'ll live for all my days,\nto put a smile on your face.\nAnd when we finally meet\nit\'ll be for etertity');
INSERT INTO page VALUES (2639,157,2,'\'... recognize that we are inescapably \ncommunal creatures\'\n\n\'... recognizing the power of the church\'s\nregular gathering and worship\'\n\n\'...reclaiming and giving more deliberate \nattention to Christian language\'');
INSERT INTO page VALUES (2638,157,1,'Professionalized, specialized,\nfederalized and capitalized,\nthe modern world system \'simply \ncannot register the wisdom inherent \nin any indigenous culture\'');
INSERT INTO page VALUES (2821,155,1,'We are a people of power\nWe are a people of praise!\nWe are a people of promise\nJesus has risen\nHe\'s conquered the grave!');
INSERT INTO page VALUES (2637,69,5,'I will rejoice (do do do do do),\nI will rejoice (do do do do do),\nI will rejoice,\nfor I\'ve made my choice\nTo rejoice in the Lord\n(Repeat)');
INSERT INTO page VALUES (2728,160,1,'Jesus, You are the Beginning and the End,\nCreator, God and King.\nGiver of life, Savior of man,\nLord of everything.\n');
INSERT INTO page VALUES (2659,158,3,'What a hpe I\'ve found,\nMore faithfull than a mother.\nIt would break my heart,\nTo ever loose each other.');
INSERT INTO page VALUES (2705,159,2,'And oh, how wide You\nopen up your arms\nWhen I need your love,\nhow far you would come\nIf i ever was lost,\nand you said that all you feel for me\nIs undying love,\nthat you showed me through the cross');
INSERT INTO page VALUES (2731,160,4,'Jesus, Your name is faithfull and true,\nRedeemer, lord and friend,\nHere in Your hands, my life is secure,\nYour love will never end.');
INSERT INTO page VALUES (2730,160,3,'All of creation sings out Your Praise,\nThe heavens declare you God,\nJesus You\'re worthy to be glorified,\nLet all of creation bow down,\nGlory and honour to the Lamb on the throne,\nLord we exalt you on high\nJesus You\'re worthy to be glorified,\nLet al of creation bow down!');
INSERT INTO page VALUES (2706,159,3,'I\'ll worship you my God\nI\'ll worship you my God\nI love you, I love you\nForever I will sing\nForever I will be with you\nBe with you');
INSERT INTO page VALUES (2729,160,2,'Blessing and favour fall like rain,\nReviving the hearts of Your children again\nJustice and mercy flow from Your throne\nRivers of love from Your heart.');
INSERT INTO page VALUES (2694,161,1,'My heart is longing for a fresh touch\nI\'ve got a burning desire for my frist love\nI know you\'re there\nand I know you\'re true\nNow all I need is You');
INSERT INTO page VALUES (2695,161,2,'All I need is You\nAll I need is You\nAll i need, All I need,\nAll I need is You');
INSERT INTO page VALUES (2696,161,3,'So won\'t you find me\nIn that place where\nYou know I should be\nWon\'t you take me to\nThat place where You\nknow I could be');
INSERT INTO page VALUES (2697,161,4,'My heart is open for You to move\nI lift up my voice and my arms too\nI know You\'re there\nand I know You\'re true\nNow All I need is You.');
INSERT INTO page VALUES (2760,162,3,'Jesus I need you\nAs Lord of my life\nI give all I have unto you\nLord I want to come under\nYour heavenly hand\nAnd to praise you\nIn all that I do');
INSERT INTO page VALUES (2759,162,2,'Spirit of life\nYou are God\'s holy fire\nYou\'ve kindled my heart with your blaze\nAnd I know you\'re refining me\nChanging my life\nAnd by faith\nYou\'re revealing your ways\n');
INSERT INTO page VALUES (2758,162,1,'Father, I thank you\nFor all that you\'ve done\nYou gave your Son freely for me\nAnd I praise you for calling me\nDrawing me near\nOut of blindness\nYou caused me to see\n');
INSERT INTO page VALUES (2757,163,4,'Finish, then, Thy new creation;\nPure and spotless let us be;\nLet us see Thy great salvation\nPerfectly restored in Thee:\nChanged from glory into glory,\nTill in heaven we take our place,\nTill we cast our crowns before Thee,\nLost in wonder, love, and praise.');
INSERT INTO page VALUES (2756,163,3,'Come, Almighty to deliver,\nLet us all Thy grace receive;\nSuddenly return, and never,\nNever more Thy temples leave.\nThee we would be always blessing,\nServe Thee as Thy hosts above,\nPray, and praise Thee without ceasing,\nGlory in Thy perfect love.\n');
INSERT INTO page VALUES (2755,163,2,'Breathe, O breathe Thy loving Spirit\nInto every troubled breast!\nLet us all in Thee inherit,\nLet us find the promised rest;\nTake away our bent to sinning;\nAlpha and Omega be;\nEnd of faith, as its beginning,\nSet our hearts at liberty.\n');
INSERT INTO page VALUES (2754,163,1,'Love divine, all loves excelling,\nJoy of heaven, to earth come down;\nFix in us Thy humble dwelling;\nAll Thy faithful mercies crown.\nJesus, Thou art all compassion,\nPure, unbounded love Thou art;\nVisit us with Thy salvation; \nEnter every trembling heart.\n');
INSERT INTO page VALUES (2788,164,7,'Standing on the promises I can-not fall,\nListening every moment to the Sprit\'s call,\nResting in my Saviour as my all in all,\nStanding on the promises of God.');
INSERT INTO page VALUES (2789,164,2,'Standing, standing,\nStanding on the promises of God my Saviour;\nStanding, standing,\nI\'m standing on the promises of God.');
INSERT INTO page VALUES (2790,164,4,'Standing, standing,\nStanding on the promises of God my Saviour;\nStanding, standing,\nI\'m standing on the promises of God.');
INSERT INTO page VALUES (2791,164,6,'Standing, standing,\nStanding on the promises of God my Saviour;\nStanding, standing,\nI\'m standing on the promises of God.');
INSERT INTO page VALUES (2785,164,1,'Standing on the promises of Christ my King,\nThro\' eternal ages let His praises ring;\nGlory in the highest, I will shout and sing,\nStanding on the promises of God.');
INSERT INTO page VALUES (2786,164,3,'Standing on the promises that can-not fail,\nWhen the howling storms of doubt and fear asail,\nBy the living word of God I shall prevail,\nStanding on the promises of God.');
INSERT INTO page VALUES (2787,164,5,'Stannding on the promises of Christ the Lord,\nBound to Him eternally by love\'s strong cord,\nOvercoming daily with with the Spirit\'s Sword,\nStanding on the promises of God.');
INSERT INTO page VALUES (2769,165,5,'When I stand in glory\nI will see his face\nAnd there I\'ll serve my King forever,\nIn that Holy Place\n');
INSERT INTO page VALUES (2768,165,4,'Thank you O our Father\nFor giving us your Son\nAnd leaving your Spirit\nTill your work on Earth is done.\n');
INSERT INTO page VALUES (2767,165,3,'Jesus my Redeemer,\nName above all names,\nPrecious Lamb of God, Messiah\nHoly One.\n');
INSERT INTO page VALUES (2766,165,2,'Thank you O our Father\nFor giving us your Son\nAnd leaving your Spirit\nTill your work on Earth is done.\n');
INSERT INTO page VALUES (2765,165,1,'There is a redeemer\nJesus, God\'s own Son\nPrecious Lamb of God, Messiah\nHoly One.\n');
INSERT INTO page VALUES (2749,166,1,'Will your anchor hold in the storm of life,\nWhen the clouds unfold their wings of strife?\nWhen the strong tides lift, and the cables strain,\nWill your anchor drift or firm remain?\n\nWe have an anchor that keeps the soul\nSteadfast and sure while the billows roll;\nFastened to the Rock which cannot move,\nGrounded firm and deep in the Saviour\'s love.\n');
INSERT INTO page VALUES (2750,166,2,'If \'tis safely moored, \'twill the storm withstand,\nFor \'tis well secured by the Saviour\'s hand;\nAnd the cables, passed from His heart to thine,\nCan defy the blast, through strength divine.\n\nWe have an anchor that keeps the soul\nSteadfast and sure while the billows roll;\nFastened to the Rock which cannot move,\nGrounded firm and deep in the Saviour\'s love.\n');
INSERT INTO page VALUES (2751,166,3,'It will firmly hold in the straits of Fear,\nWhen the breakers tell that the reef is near;\nThough the tempest rave and the wild winds blow,\nNot an angry wave shall our bark o\'erflow.\n\nWe have an anchor that keeps the soul\nSteadfast and sure while the billows roll;\nFastened to the Rock which cannot move,\nGrounded firm and deep in the Saviour\'s love.\n');
INSERT INTO page VALUES (2752,166,4,'It will surely hold in the floods of death,\nWhen the waters cold chill our latest breath;\nOn the rising tide it can never fail,\nWhile our hopes abide within the veil.\n\nWe have an anchor that keeps the soul\nSteadfast and sure while the billows roll;\nFastened to the Rock which cannot move,\nGrounded firm and deep in the Saviour\'s love.\n');
INSERT INTO page VALUES (2753,166,5,'When our eyes behold, in the dawning light,\nShining gates of pearl, our harbor bright,\nWe shall anchor fast to the heavenly shore,\nWith the storms all past for ever more.\n\nWe have an anchor that keeps the soul\nSteadfast and sure while the billows roll;\nFastened to the Rock which cannot move,\nGrounded firm and deep in the Saviour\'s love.');
INSERT INTO page VALUES (2792,164,8,'Standing, standing,\nStanding on the promises of God my Saviour;\nStanding, standing,\nI\'m standing on the promises of God.');
INSERT INTO page VALUES (2770,165,6,'Thank you O our Father\nFor giving us your Son\nAnd leaving your Spirit\nTill your work on Earth is done.');
INSERT INTO page VALUES (2793,167,1,'When we walk with the Lord\nIn the light of His Word\nWhat a glory He sheds on our way!\nWhile we do His good will,\nHe abides with us still,\nAnd with all who will trust and obey.\n');
INSERT INTO page VALUES (2794,167,2,'Trust and obey,\nfor theres no other way\nto be happy in Jesus,\nBut to trust and obey.\n');
INSERT INTO page VALUES (2795,167,3,'Not a burden we bear,\nNot a sorrow we share,\nBut our toil He doth richly repay;\nNot a grief or a loss,\nNot a frown or a cross,\nBut is blest if we trust and obey.\n');
INSERT INTO page VALUES (2796,167,4,'Trust and obey,\nfor theres no other way\nto be happy in Jesus,\nBut to trust and obey.\n');
INSERT INTO page VALUES (2797,167,5,'But we never can prove\nThe delights of His love\nUntil all on the altar we lay;\nFor the favor He shows\nAnd the joy He bestows\nAre for them who will trust and obey.\n');
INSERT INTO page VALUES (2798,167,6,'Trust and obey,\nfor theres no other way\nto be happy in Jesus,\nBut to trust and obey.\n');
INSERT INTO page VALUES (2799,167,7,'Then in fellowship sweet\nWe will sit at His feet\nOr well walk by His side in the way;\nWhat He says we will do,\nWhere He sends we will go;\nNever fear, only trust and obey.\n');
INSERT INTO page VALUES (2800,167,8,'Trust and obey,\nfor theres no other way\nto be happy in Jesus,\nBut to trust and obey.');
INSERT INTO page VALUES (2801,168,1,'Our Father, who art in heaven,\nHallowed be thy name.\nThy kingdom come, thy will be done.\nGive us this day our daily bread,\nand forgive us our trespasses,\nas we forgive those who trespass against us.\nAnd lead us not into temptation,\nbut deliver us from evil.\nFor thine is the kingdom, the power and the\nglory, forever and ever, Amen. ');
INSERT INTO page VALUES (2802,168,2,'Our Father who is in heaven,\nHallowed be your name,\nYour kingdom come, your will be done,\nOn Earth as it is in heaven.\nForgive our sins as we forgive those who\nsin against us.\nAnd lead us not into temptation but deliver\nus from evil.\nFor yours is the kingdom, the power and the glory,\nFor now and for ever, Amen.');
INSERT INTO page VALUES (2825,169,1,'Hosanna, hosanna, hosanna in the highest!\nHosanna, hosanna, hosanna in the highest!\nLord, we lift up your name,\nWith hearts full of praise.\nBe exalted, O Lord my God.\nHosanna in the highest!');
INSERT INTO page VALUES (2826,169,2,'Glory, glory, glory to the King of kings!\nGlory, glory, glory to the King of kings!\nLord we lift up your name,\nWith hearts full of praise.\nBe exalted O Lord my God.\nGlory to the King of king!');
INSERT INTO page VALUES (2831,170,1,'We believe in God the Father\nMaker of the universe\nAnd in Christ his son our saviour\nCome to us by virgin birth\nWe believe he died to save us\nBore our sins, was crucified\nThen from death he rose victorious\nAscended to the Father\'s side');
INSERT INTO page VALUES (2832,170,2,'Jesus Lord of all, Lord of all (x4)\nName above all names,\nName above all names.');
INSERT INTO page VALUES (2833,170,3,'We believe he sends his Spirit\nOn his church with gifts of power\nGod his word of truth affirming\nSends us to the nations now.\nHe will come again in glory\nJudge the living and the dead\nEvery knee shall bow before him\nThe must every tongue confess');
INSERT INTO page VALUES (2857,1,1,'asdjh lkjhg \ndsg sdf g\nsdfg s\ndg sd\nfgsd \ndsfg sd\ng sdg sd fgsd\nfgs dfgsd \ndsg sdfg sd\ng sdfgsdfg \nsdfg sdfg sdf\nsdg s sdfhg \ndsg sdf g\nsdfg s\ndg sd\nfgsd \ndsfg sd\ng sdg sd fgsd\nfgs dfgsd \ndsg sdfg sd\ng sdfgsdfg \nsdfg sdfg sdf\nsdg s sdf\nsd fgsd\nj\nj\nj\n');
INSERT INTO page VALUES (2858,171,1,'Nothing much today');
INSERT INTO page VALUES (2870,23,6,'I\'ve been forgiven\nI\'ve been set free\nRestored and sanctified\nIn Christ I\'ve been set free');

--
-- Table structure for table 'playlist'
--

CREATE TABLE playlist (
  playorder int(11) NOT NULL default '0',
  playlist int(11) NOT NULL default '1',
  data varchar(50) NOT NULL default '',
  type varchar(4) default 'song',
  PRIMARY KEY  (playorder)
) TYPE=MyISAM;

--
-- Table structure for table 'playlists'
--

CREATE TABLE playlists (
  id int(11) NOT NULL default '0',
  title varchar(50) NOT NULL default '',
  ref varchar(50) NOT NULL default '',
  PRIMARY KEY  (id)
) TYPE=MyISAM;

--
-- Dumping data for table 'playlists'
--


INSERT INTO playlists VALUES (1,'Main Playlist','');

