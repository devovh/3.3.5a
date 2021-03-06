/*WorldStates Characters DB*/
DELETE FROM worldstates WHERE entry IN (31001,31002,31003,31004);
INSERT INTO `worldstates` VALUES ('31001', '0', 'WG war status');
INSERT INTO `worldstates` VALUES ('31002', '0', 'WG clock');
INSERT INTO `worldstates` VALUES ('31003', '0', 'WG Fortress Defender');
INSERT INTO `worldstates` VALUES ('31004', '0', 'WG TEMP Battle Control Faction');

DROP TABLE IF EXISTS `players_reports_status`;
CREATE TABLE `players_reports_status` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `creation_time` int(10) unsigned NOT NULL DEFAULT '0',
  `average` float NOT NULL DEFAULT '0',
  `total_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `speed_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `fly_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `jump_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `waterwalk_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `teleportplane_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `climb_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='';

DROP TABLE IF EXISTS `daily_players_reports`;
CREATE TABLE `daily_players_reports` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0',
  `creation_time` int(10) unsigned NOT NULL DEFAULT '0',
  `average` float NOT NULL DEFAULT '0',
  `total_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `speed_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `fly_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `jump_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `waterwalk_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `teleportplane_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  `climb_reports` bigint(20) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='';

DROP TABLE IF EXISTS `mail_external`;
CREATE TABLE `mail_external` (
  `id` bigint(20) unsigned NOT NULL auto_increment,
  `receiver` bigint(20) unsigned NOT NULL,
  `subject` varchar(200) default 'Support Message',
  `message` varchar(500) default 'Support Message',
  `money` bigint(20) unsigned NOT NULL default '0',
  `item` bigint(20) unsigned NOT NULL default '0',
  `item_count` bigint(20) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=7525 DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `auctionhousebot`;
CREATE TABLE `auctionhousebot` (
    `auctionhouse` INT(11) NOT NULL DEFAULT '0' COMMENT 'mapID of the auctionhouse.',
    `name` CHAR(25) NULL DEFAULT NULL COMMENT 'Text name of the auctionhouse.',
    `minitems` INT(11) NULL DEFAULT '0' COMMENT 'This is the minimum number of items you want to keep in the auction house. a 0 here will make it the same as the maximum.',
    `maxitems` INT(11) NULL DEFAULT '0' COMMENT 'This is the number of items you want to keep in the auction house.',
    `percentgreytradegoods` INT(11) NULL DEFAULT '0' COMMENT 'Sets the percentage of the Grey Trade Goods auction items',
    `percentwhitetradegoods` INT(11) NULL DEFAULT '27' COMMENT 'Sets the percentage of the White Trade Goods auction items',
    `percentgreentradegoods` INT(11) NULL DEFAULT '12' COMMENT 'Sets the percentage of the Green Trade Goods auction items',
    `percentbluetradegoods` INT(11) NULL DEFAULT '10' COMMENT 'Sets the percentage of the Blue Trade Goods auction items',
    `percentpurpletradegoods` INT(11) NULL DEFAULT '1' COMMENT 'Sets the percentage of the Purple Trade Goods auction items',
    `percentorangetradegoods` INT(11) NULL DEFAULT '0' COMMENT 'Sets the percentage of the Orange Trade Goods auction items',
    `percentyellowtradegoods` INT(11) NULL DEFAULT '0' COMMENT 'Sets the percentage of the Yellow Trade Goods auction items',
    `percentgreyitems` INT(11) NULL DEFAULT '0' COMMENT 'Sets the percentage of the non trade Grey auction items',
    `percentwhiteitems` INT(11) NULL DEFAULT '10' COMMENT 'Sets the percentage of the non trade White auction items',
    `percentgreenitems` INT(11) NULL DEFAULT '30' COMMENT 'Sets the percentage of the non trade Green auction items',
    `percentblueitems` INT(11) NULL DEFAULT '8' COMMENT 'Sets the percentage of the non trade Blue auction items',
    `percentpurpleitems` INT(11) NULL DEFAULT '2' COMMENT 'Sets the percentage of the non trade Purple auction items',
    `percentorangeitems` INT(11) NULL DEFAULT '0' COMMENT 'Sets the percentage of the non trade Orange auction items',
    `percentyellowitems` INT(11) NULL DEFAULT '0' COMMENT 'Sets the percentage of the non trade Yellow auction items',
    `minpricegrey` INT(11) NULL DEFAULT '100' COMMENT 'Minimum price of Grey items (percentage).',
    `maxpricegrey` INT(11) NULL DEFAULT '150' COMMENT 'Maximum price of Grey items (percentage).',
    `minpricewhite` INT(11) NULL DEFAULT '150' COMMENT 'Minimum price of White items (percentage).',
    `maxpricewhite` INT(11) NULL DEFAULT '250' COMMENT 'Maximum price of White items (percentage).',
    `minpricegreen` INT(11) NULL DEFAULT '800' COMMENT 'Minimum price of Green items (percentage).',
    `maxpricegreen` INT(11) NULL DEFAULT '1400' COMMENT 'Maximum price of Green items (percentage).',
    `minpriceblue` INT(11) NULL DEFAULT '1250' COMMENT 'Minimum price of Blue items (percentage).',
    `maxpriceblue` INT(11) NULL DEFAULT '1750' COMMENT 'Maximum price of Blue items (percentage).',
    `minpricepurple` INT(11) NULL DEFAULT '2250' COMMENT 'Minimum price of Purple items (percentage).',
    `maxpricepurple` INT(11) NULL DEFAULT '4550' COMMENT 'Maximum price of Purple items (percentage).',
    `minpriceorange` INT(11) NULL DEFAULT '3250' COMMENT 'Minimum price of Orange items (percentage).',
    `maxpriceorange` INT(11) NULL DEFAULT '5550' COMMENT 'Maximum price of Orange items (percentage).',
    `minpriceyellow` INT(11) NULL DEFAULT '5250' COMMENT 'Minimum price of Yellow items (percentage).',
    `maxpriceyellow` INT(11) NULL DEFAULT '6550' COMMENT 'Maximum price of Yellow items (percentage).',
    `minbidpricegrey` INT(11) NULL DEFAULT '70' COMMENT 'Starting bid price of Grey items as a percentage of the randomly chosen buyout price. Default: 70',
    `maxbidpricegrey` INT(11) NULL DEFAULT '100' COMMENT 'Starting bid price of Grey items as a percentage of the randomly chosen buyout price. Default: 100',
    `minbidpricewhite` INT(11) NULL DEFAULT '70' COMMENT 'Starting bid price of White items as a percentage of the randomly chosen buyout price. Default: 70',
    `maxbidpricewhite` INT(11) NULL DEFAULT '100' COMMENT 'Starting bid price of White items as a percentage of the randomly chosen buyout price. Default: 100',
    `minbidpricegreen` INT(11) NULL DEFAULT '80' COMMENT 'Starting bid price of Green items as a percentage of the randomly chosen buyout price. Default: 80',
    `maxbidpricegreen` INT(11) NULL DEFAULT '100' COMMENT 'Starting bid price of Green items as a percentage of the randomly chosen buyout price. Default: 100',
    `minbidpriceblue` INT(11) NULL DEFAULT '75' COMMENT 'Starting bid price of Blue items as a percentage of the randomly chosen buyout price. Default: 75',
    `maxbidpriceblue` INT(11) NULL DEFAULT '100' COMMENT 'Starting bid price of Blue items as a percentage of the randomly chosen buyout price. Default: 100',
    `minbidpricepurple` INT(11) NULL DEFAULT '80' COMMENT 'Starting bid price of Purple items as a percentage of the randomly chosen buyout price. Default: 80',
    `maxbidpricepurple` INT(11) NULL DEFAULT '100' COMMENT 'Starting bid price of Purple items as a percentage of the randomly chosen buyout price. Default: 100',
    `minbidpriceorange` INT(11) NULL DEFAULT '80' COMMENT 'Starting bid price of Orange items as a percentage of the randomly chosen buyout price. Default: 80',
    `maxbidpriceorange` INT(11) NULL DEFAULT '100' COMMENT 'Starting bid price of Orange items as a percentage of the randomly chosen buyout price. Default: 100',
    `minbidpriceyellow` INT(11) NULL DEFAULT '80' COMMENT 'Starting bid price of Yellow items as a percentage of the randomly chosen buyout price. Default: 80',
    `maxbidpriceyellow` INT(11) NULL DEFAULT '100' COMMENT 'Starting bid price of Yellow items as a percentage of the randomly chosen buyout price. Default: 100',
    `maxstackgrey` INT(11) NULL DEFAULT '0' COMMENT 'Stack size limits for item qualities - a value of 0 will disable a maximum stack size for that quality, which will allow the bot to create items in stack as large as the item allows.',
    `maxstackwhite` INT(11) NULL DEFAULT '0' COMMENT 'Stack size limits for item qualities - a value of 0 will disable a maximum stack size for that quality, which will allow the bot to create items in stack as large as the item allows.',
    `maxstackgreen` INT(11) NULL DEFAULT '0' COMMENT 'Stack size limits for item qualities - a value of 0 will disable a maximum stack size for that quality, which will allow the bot to create items in stack as large as the item allows.',
    `maxstackblue` INT(11) NULL DEFAULT '0' COMMENT 'Stack size limits for item qualities - a value of 0 will disable a maximum stack size for that quality, which will allow the bot to create items in stack as large as the item allows.',
    `maxstackpurple` INT(11) NULL DEFAULT '0' COMMENT 'Stack size limits for item qualities - a value of 0 will disable a maximum stack size for that quality, which will allow the bot to create items in stack as large as the item allows.',
    `maxstackorange` INT(11) NULL DEFAULT '0' COMMENT 'Stack size limits for item qualities - a value of 0 will disable a maximum stack size for that quality, which will allow the bot to create items in stack as large as the item allows.',
    `maxstackyellow` INT(11) NULL DEFAULT '0' COMMENT 'Stack size limits for item qualities - a value of 0 will disable a maximum stack size for that quality, which will allow the bot to create items in stack as large as the item allows.',
    `buyerpricegrey` INT(11) NULL DEFAULT '1' COMMENT 'Multiplier to vendorprice when buying grey items from auctionhouse',
    `buyerpricewhite` INT(11) NULL DEFAULT '3' COMMENT 'Multiplier to vendorprice when buying white items from auctionhouse',
    `buyerpricegreen` INT(11) NULL DEFAULT '5' COMMENT 'Multiplier to vendorprice when buying green items from auctionhouse',
    `buyerpriceblue` INT(11) NULL DEFAULT '12' COMMENT 'Multiplier to vendorprice when buying blue items from auctionhouse',
    `buyerpricepurple` INT(11) NULL DEFAULT '15' COMMENT 'Multiplier to vendorprice when buying purple items from auctionhouse',
    `buyerpriceorange` INT(11) NULL DEFAULT '20' COMMENT 'Multiplier to vendorprice when buying orange items from auctionhouse',
    `buyerpriceyellow` INT(11) NULL DEFAULT '22' COMMENT 'Multiplier to vendorprice when buying yellow items from auctionhouse',
    `buyerbiddinginterval` INT(11) NULL DEFAULT '1' COMMENT 'Interval how frequently AHB bids on each AH. Time in minutes',
    `buyerbidsperinterval` INT(11) NULL DEFAULT '1' COMMENT 'number of bids to put in per bidding interval',
    PRIMARY KEY (`auctionhouse`)
)
ENGINE=InnoDB
ROW_FORMAT=DEFAULT;

INSERT INTO `auctionhousebot`(`auctionhouse`,`name`,`minitems`,`maxitems`,`percentgreytradegoods`,`percentwhitetradegoods`,`percentgreentradegoods`,`percentbluetradegoods`,`percentpurpletradegoods`,`percentorangetradegoods`,`percentyellowtradegoods`,`percentgreyitems`,`percentwhiteitems`,`percentgreenitems`,`percentblueitems`,`percentpurpleitems`,`percentorangeitems`,`percentyellowitems`,`minpricegrey`,`maxpricegrey`,`minpricewhite`,`maxpricewhite`,`minpricegreen`,`maxpricegreen`,`minpriceblue`,`maxpriceblue`,`minpricepurple`,`maxpricepurple`,`minpriceorange`,`maxpriceorange`,`minpriceyellow`,`maxpriceyellow`,`minbidpricegrey`,`maxbidpricegrey`,`minbidpricewhite`,`maxbidpricewhite`,`minbidpricegreen`,`maxbidpricegreen`,`minbidpriceblue`,`maxbidpriceblue`,`minbidpricepurple`,`maxbidpricepurple`,`minbidpriceorange`,`maxbidpriceorange`,`minbidpriceyellow`,`maxbidpriceyellow`,`maxstackgrey`,`maxstackwhite`,`maxstackgreen`,`maxstackblue`,`maxstackpurple`,`maxstackorange`,`maxstackyellow`,`buyerpricegrey`,`buyerpricewhite`,`buyerpricegreen`,`buyerpriceblue`,`buyerpricepurple`,`buyerpriceorange`,`buyerpriceyellow`,`buyerbiddinginterval`,`buyerbidsperinterval`) VALUES
(2,'Alliance',250,250,0,27,12,10,1,0,0,0,10,30,8,2,0,0,100,150,150,250,800,1400,1250,1750,2250,4550,3250,5550,5250,6550,70,100,70,100,80,100,75,100,80,100,80,100,80,100,0,0,3,2,1,1,1,1,3,5,12,15,20,22,1,1),
(6,'Horde',250,250,0,27,12,10,1,0,0,0,10,30,8,2,0,0,100,150,150,250,800,1400,1250,1750,2250,4550,3250,5550,5250,6550,70,100,70,100,80,100,75,100,80,100,80,100,80,100,0,0,3,2,1,1,1,1,3,5,12,15,20,22,1,1),
(7,'Neutral',250,250,0,27,12,10,1,0,0,0,10,30,8,2,0,0,100,150,150,250,800,1400,1250,1750,2250,4550,3250,5550,5250,6550,70,100,70,100,80,100,75,100,80,100,80,100,80,100,0,0,3,2,1,1,1,1,3,5,12,15,20,22,1,1);

-- ----------------------------
-- Table structure for `character_boss_kill_history`
-- ----------------------------
DROP TABLE IF EXISTS `character_boss_kill_history`;
CREATE TABLE `character_boss_kill_history` (
  `Guid` bigint(20) NOT NULL AUTO_INCREMENT,
  `GuildId` int(10) NOT NULL,
  `CreatureEntry` int(10) NOT NULL,
  `CreatureName` varchar(255) NOT NULL,
  `KillerCount` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `KillTime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `KillData` longtext NOT NULL,
  `MapRaid` tinyint(1) unsigned NOT NULL DEFAULT '0',
  `MapId` smallint(6) unsigned NOT NULL DEFAULT '0',
  `MapName` varchar(255) NOT NULL,
  `MapSpawnMode` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`Guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

REPLACE INTO `reserved_name` (`name`) VALUES
('??????????????????????'),
('????'),
('Gm'),
('??????????'),
('??????????????'),
('Admin'),
('Gamemaster'),
('????????????????????'),
('????????????'),
('Developer'),
('??????????????????'),
('Moderator'),
('Moder'),
('??????????');

DROP TABLE IF EXISTS `fake_items`;
CREATE TABLE `fake_items` (
  `guid` int(11) NOT NULL,
  `fakeEntry` int(11) NOT NULL,
  PRIMARY KEY (`guid`)
);

