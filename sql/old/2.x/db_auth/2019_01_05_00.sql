-- DB update 2018_09_17_00 -> 2019_01_05_00
DROP PROCEDURE IF EXISTS `updateDb`;
DELIMITER //
CREATE PROCEDURE updateDb ()
proc:BEGIN DECLARE OK VARCHAR(100) DEFAULT 'FALSE';
SELECT COUNT(*) INTO @COLEXISTS
FROM information_schema.COLUMNS
WHERE TABLE_SCHEMA = DATABASE() AND TABLE_NAME = 'version_db_auth' AND COLUMN_NAME = '2018_09_17_00';
IF @COLEXISTS = 0 THEN LEAVE proc; END IF;
START TRANSACTION;
ALTER TABLE version_db_auth CHANGE COLUMN 2018_09_17_00 2019_01_05_00 bit;
SELECT sql_rev INTO OK FROM version_db_auth WHERE sql_rev = '1546540718864817294'; IF OK <> 'FALSE' THEN LEAVE proc; END IF;
--
-- START UPDATING QUERIES
--

INSERT INTO version_db_auth (`sql_rev`) VALUES ('1546540718864817294');

ALTER TABLE `account` CHANGE `last_login` `last_login` TIMESTAMP NULL DEFAULT NULL;
ALTER TABLE `account` CHANGE `email` `email` VARCHAR(255) NOT NULL DEFAULT '';

UPDATE IGNORE `account` SET `last_login`=NULL WHERE `last_login`='0000-00-00 00:00:00';

--
-- END UPDATING QUERIES
--
COMMIT;
END //
DELIMITER ;
CALL updateDb();
DROP PROCEDURE IF EXISTS `updateDb`;
