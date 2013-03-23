-- Nagrand
-- Quest: Blessing of Incineratus, http://old.wowhead.com/quest=9805
UPDATE `item_template` SET `ScriptName` = "item_living_fire" WHERE `entry` = 24467;

-- Quest: HELP!, http://old.wowhead.com/quest=9923
UPDATE `gameobject` SET `state`='1' WHERE `guid`='21657';
UPDATE `gameobject_template` SET `data2`='0' WHERE `entry`='182349';

-- Dragonblight
-- Quest: Blighted Last Rites, http://old.wowhead.com/quest=12206
UPDATE `item_template` SET `ScriptName` = "flask_of_blight" WHERE `entry` = 37129;

-- Quest: Fire Upon the Waters, http://old.wowhead.com/quest=12243
SET @GUID =42887;
DELETE FROM `creature` WHERE `id`=28013;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(@GUID+0,28013,571,1,1,0,0,2488.86,-400.017,19.0803,2.99498,300,0,0,42,0,0,0,33554432,0),
(@GUID+1,28013,571,1,1,0,0,2458.96,-401.066,20.7778,0.108631,300,0,0,42,0,0,0,33554432,0);
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 28013;
DELETE FROM `smart_scripts` WHERE `entryorguid`=28013 AND `source_type`=0;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES 
(28013,0,0,0,8,0,100,0,48455,0,0,0,33,28013,0,0,0,0,0,7,0,0,0,0,0,0,0,"Fire Upon the Waters Kill Credit Bunny - On SpellHit Apothecary's Burning Water - Call KilledMonster Fire Upon the Waters Kill Credit Bunny");
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=48455;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,1,48455,0,0,31,0,3,28013,0,0,0,'',"Fire Upon the Waters - spell to Fire Upon the Waters Kill Credit Bunny");
DELETE FROM conditions WHERE `SourceGroup` = 27232 AND `SourceEntry` = 39152;
DELETE FROM `creature_loot_template` WHERE `entry`=27232;
INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
(27232,37305,-100,1,0,1,1),
(27232,43851,25,1,0,1,1),
(27232,33470,10,1,0,1,3),
(27232,33443,5,1,0,1,1),
(27232,33444,2,1,0,1,1),
(27232,22829,1,1,0,1,1),
(27232,45912,0.05,1,0,1,1);

-- The Storm Peaks
-- Quest: You'll Need a Bear, http://old.wowhead.com/quest=12972
UPDATE `creature_template` SET `faction_A`='35',`faction_H`='35' WHERE `entry`='29592';
UPDATE `creature_template` SET `gossip_menu_id`='0' WHERE `entry`='29592';
UPDATE `quest_template` SET `Method`='0' WHERE `Id`='12972';

-- Quest: The Best of Intentions, http://old.wowhead.com/quest=12263
SET @NPC=26593;
SET @QUEST=12263;
SET @GOSSIP=9537;
UPDATE `creature_template` SET `AIName`='SmartAI' WHERE `entry`=@NPC;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@NPC;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(@NPC, 0, 0, 0, 19, 0, 100, 0, @QUEST, 0, 0, 0, 11, 48750, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Serinar - on quest accept - cast Burning Depths Necrolyte Image'),
(@NPC, 0, 1, 0, 62, 0, 100, 0, @GOSSIP, 1, 0, 0, 11, 48750, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Serinar - on gossip option select - cast Burning Depths Necrolyte Image');
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=15 AND `SourceGroup`=@GOSSIP AND `SourceEntry`=1;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(15, @GOSSIP, 1, 0, 0, 9, 0, @QUEST, 0, 0, 0, 0, '', 'Show gossip option if player has quest The Best of Intentions');
UPDATE `gossip_menu_option` SET `action_menu_id`=9538 WHERE `menu_id`=9537;
DELETE FROM `gossip_menu` WHERE `entry`=9538;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES
(9538,12851);

-- Crystalsong Forest
-- Quest: There's Something About the Squire, http://old.wowhead.com/quest=13654
UPDATE `npc_spellclick_spells` SET `cast_flags`=3 WHERE `npc_entry`=33498 AND `spell_id`=63126;

-- Blade's Edge Mountains
-- Quest: The Thunderspike, http://old.wowhead.com/quest=10526
SET @ENTRY := 184729;
UPDATE `gameobject_template` SET `ScriptName` = '', `data2`=13685, `data3`=3000 WHERE `entry` = @ENTRY;
DELETE FROM `event_scripts` WHERE `id`=13685;
INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES
('13685','1','10','21319','900000','0','1326.51','6691.53','-20.3344','3.29793');
UPDATE `gameobject_template` SET `AIName`='SmartGameObjectAI' WHERE `entry`=@ENTRY;
DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,1,0,0,64,0,100,1,0,0,0,0,12,21319,1,900000,0,0,0,8,0,0,0,1326.51,6691.53,-20.3344,3.29793,"The Thunderspike - Summon Gor Grimgut");

-- Borean Tundra
-- Quest: The Power of the Elements, http://old.wowhead.com/quest=11893
UPDATE `creature_template` SET `ScriptName`='npc_steam_rager' WHERE `entry`='24601';

-- Quest: Death from Above, http://old.wowhead.com/quest=11889
UPDATE creature_template Set `InhabitType` = 4 WHERE entry = 25582;
UPDATE item_template SET `ScriptName` = "item_reinforced_net" WHERE entry = 35278;

-- Quest: Kaw the Mammoth Destroyer, http://old.wowhead.com/quest=11879
DELETE FROM `vehicle_template_accessory` WHERE entry=25881 AND seat_id=0;
INSERT INTO `vehicle_template_accessory` VALUES (25881, 25802, 0, 0, 'Kaw the Mammoth Destroyer mounted on Moria', 5, 0);
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry` = '25881' AND `spell_id`='46260';
INSERT INTO `npc_spellclick_spells` VALUES (25881, 46260, 0, 0);
DELETE FROM `creature` WHERE `id`=25802;
UPDATE `creature_template` SET unit_flags = 0 WHERE entry IN (25802, 25881);

-- Quest: Oh Noes, the Tadpoles!, http://old.wowhead.com/quest=11560
DELETE FROM `creature` WHERE `id` = 25201;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
('97437','25201','571','1','1','22987','0','3956.85','6367.35','11.4804','3.21141','300','0','0','48','0','0','0','0','0'),
('97438','25201','571','1','1','22986','0','3932.95','6394.11','11.5035','2.79253','300','0','0','48','0','0','0','0','0'),
('97439','25201','571','1','1','22987','0','3831.18','6424.5','22.1346','0.802851','300','0','0','48','0','0','0','0','0'),
('97441','25201','571','1','1','22986','0','3986.81','6480.68','22.1035','1.46608','300','0','0','48','0','0','0','0','0'),
('97442','25201','571','1','1','15984','0','4037.85','6468.75','22.4485','2.65259','300','5','0','48','0','1','0','0','0'),
('97443','25201','571','1','1','22986','0','3973.07','6313.26','8.16543','5.13127','300','0','0','48','0','0','0','0','0'),
('97444','25201','571','1','1','15369','0','3984.86','6342.51','8.10709','1.85005','300','0','0','48','0','0','0','0','0'),
('97446','25201','571','1','1','15984','0','3998.29','6282.32','8.16543','2.02458','300','0','0','48','0','0','0','0','0'),
('97447','25201','571','1','1','15984','0','4031.71','6332.46','9.15257','5.35816','300','0','0','48','0','0','0','0','0'),
('97448','25201','571','1','1','22987','0','4051.43','6298.06','2.8178','3.28122','300','0','0','48','0','0','0','0','0'),
('97451','25201','571','1','1','15369','0','4297.36','6206.13','0.721473','0.645772','300','0','0','48','0','0','0','0','0'),
('97452','25201','571','1','1','22986','0','4283.54','6298.31','0.648284','3.92699','300','0','0','48','0','0','0','0','0'),
('97454','25201','571','1','1','15984','0','4231.16','6183.2','1.30836','0.628319','300','0','0','48','0','0','0','0','0'),
('97455','25201','571','1','1','15984','0','4297.16','6250.19','0.395812','0.017453','300','0','0','48','0','0','0','0','0'),
('97456','25201','571','1','1','15984','0','4225.96','6230.02','1.31987','0.349066','300','0','0','48','0','0','0','0','0'),
('97457','25201','571','1','1','15369','0','4176.29','6243.69','8.42978','0.314159','300','0','0','48','0','0','0','0','0'),
('97458','25201','571','1','1','22986','0','4161.3','6188.54','9.33637','0.959931','300','0','0','48','0','0','0','0','0');
DELETE FROM `gameobject` WHERE `id` = 187373;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('46894','187373','571','1','1','3956.9','6367.73','11.2895','0.767944','0','0','0','1','300','100','1'),
('46895','187373','571','1','1','4176.06','6243.41','8.2004','-1.29154','0','0','0','1','300','100','1'),
('46896','187373','571','1','1','4298.07','6206.28','0.487122','-2.28638','0','0','0','1','300','100','1'),
('47512','187373','571','1','1','3932.65','6394.14','11.2002','-1.309','0','0','0','1','300','100','1'),
('47513','187373','571','1','1','4031.3','6332.22','8.90955','1.72787','0','0','0','1','300','100','1'),
('47514','187373','571','1','1','4283.26','6297.99','0.404293','-0.122173','0','0','0','1','300','100','1'),
('47515','187373','571','1','1','4231.63','6183.1','1.05165','1.83259','0','0','0','1','300','100','1'),
('47516','187373','571','1','1','4161.53','6188.07','9.17654','-1.58825','0','0','0','1','300','100','1'),
('47517','187373','571','1','1','4061.56','6254.12','21.8839','0.366518','0','0','0','1','300','100','1'),
('47518','187373','571','1','1','4296.52','6250.31','0.182616','1.0472','0','0','0','1','300','100','1'),
('47519','187373','571','1','1','3984.93','6343.08','7.85525','-1.22173','0','0','0','1','300','100','1'),
('47520','187373','571','1','1','3986.92','6481.15','21.8128','-2.84488','0','0','0','1','300','100','1'),
('47521','187373','571','1','1','4180.65','6308.74','13.0965','-2.1293','0','0','0','1','300','100','1'),
('47522','187373','571','1','1','4225.75','6230.07','0.987369','-2.87979','0','0','0','1','300','100','1'),
('53090','187373','571','1','1','3997.79','6282.02','7.97459','-0.663223','0','0','0','1','300','100','1'),
('53091','187373','571','1','1','4104.5','6300.65','23.2685','2.47837','0','0','0','1','300','100','1'),
('53092','187373','571','1','1','4051.67','6298.44','2.58589','1.76278','0','0','0','1','300','100','1'),
('53093','187373','571','1','1','3830.89','6424.93','21.8597','-2.11185','0','0','0','1','300','100','1'),
('53095','187373','571','1','1','4038.38','6468.67','22.2306','1.5708','0','0','0','1','300','100','1'),
('53096','187373','571','1','1','3973.45','6313.41','7.9676','-1.6057','0','0','0','1','300','100','1'),
('53097','187373','571','1','1','4270.82','6400.72','0.4071','-2.35619','0','0','0','1','300','100','1');

-- Quest: Blending In, http://old.wowhead.com/quest=11633
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (25471,25472,25473);
DELETE FROM `creature` WHERE `id` IN (25471,25472,25473);
DELETE FROM `spell_area` WHERE `spell` IN (45627,45628,45629);
INSERT INTO `spell_area` (`spell`, `area`, `quest_start`, `quest_start_active`, `quest_end`, `aura_spell`, `racemask`, `gender`, `autocast`) VALUES
(45627,4136,11633,1,11633,45614,0,2,1),
(45628,4135,11633,1,11633,45614,0,2,1),
(45629,4137,11633,1,11633,45614,0,2,1);

-- Quest: Drake Hunt, http://old.wowhead.com/quest=11919
DELETE FROM `areatrigger_scripts` WHERE `entry` = 4914;
INSERT INTO `areatrigger_scripts` VALUES (4914, 'at_drake_hunt');

-- Quest: The Honored Dead, http://old.wowhead.com/quest=11593
SET @SPELL := 45474;
SET @GUARD := 25342;
SET @WORKER := 25343;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=@SPELL AND `ConditionTypeOrReference`=36;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid` IN (@GUARD,@WORKER) AND `id` IN (2,3);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@GUARD,0,2,3,8,0,100,0,@SPELL,0,0,0,33,@GUARD,0,0,0,0,0,7,0,0,0,0,0,0,0,'Dead Caravan Guard - On Spellhit - Give Quest Credit'),
(@GUARD,0,3,0,61,0,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0,0,0,0,'Dead Caravan Guard - On Spellhit - Despawn'),
(@WORKER,0,2,3,8,0,100,0,@SPELL,0,0,0,33,@GUARD,0,0,0,0,0,7,0,0,0,0,0,0,0,'Dead Caravan Worker - On Spellhit - Give Quest Credit'),
(@WORKER,0,3,0,61,0,100,0,0,0,0,0,41,500,0,0,0,0,0,1,0,0,0,0,0,0,0,'Dead Caravan Worker - On Spellhit - Despawn');

-- Goldshire
-- Quest: Report to Goldshire, http://old.wowhead.com/quest=54
DELETE FROM `quest_start_scripts` WHERE `id` = 54;
DELETE FROM `db_script_string` WHERE `entry`=2000000059;
UPDATE `quest_template` SET `StartScript`='54', `SpecialFlags`='0' WHERE `Id`='54';
INSERT INTO `quest_start_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES
('54','1','15','6245','0','0','0','0','0','0'),
('54','2','1','113','0','0','0','0','0','0'),
('54','2','0','0','0','2000000059','0','0','0','0');
INSERT INTO `db_script_string` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`) VALUES
('2000000059','You are Dismissed, $N',NULL,NULL,NULL,NULL,NULL,NULL,NULL,'Ты уволен, $N');

-- Scarlet Unclave
-- Death Comes from high
UPDATE `creature_template` SET `ScriptName` = 'npc_eye_of_acherus' WHERE `entry` = '28511';
DELETE FROM `creature_text` WHERE `entry`=28511;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(28511,1,0, 'The eye of Acherus moves toward it\s target.',14,0,100,0,0,0, 'Q12641 - EMOTE_EYE_OF_ACHERUS_START'),
(28511,2,0, 'The eye of Acherus subject of your control.',14,0,100,0,0,0, 'Q12641 - EMOTE_EYE_OF_ACHERUS_END'); 

-- Dun Morogh
-- Quest: The Tome of Divinity, http://old.wowhead.com/quest=1783
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`='13' AND `SourceEntry`='8593' AND `ElseGroup`='1' AND `ConditionValue2`='6172';

-- Item: Titanium Seal of Dalaran, http://old.wowhead.com/item=44430
DELETE FROM `spell_script_names` WHERE `spell_id`=60476;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES ('60476', 'spell_toss_your_luck');

-- Barrens
-- Quest: Lost in Battle, http://old.wowhead.com/quest=4921
UPDATE `creature_template` SET `npcflag` = 3 WHERE `entry` = 10668;

-- Ghostlands
-- Quest: Escape from the Catacombs, http://old.wowhead.com/quest=9212
UPDATE `quest_template` SET `SpecialFlags`='2' WHERE `Id`='9212'; 

-- Desolace
-- Quest: Kodo Roundup, http://old.wowhead.com/quest=5561
UPDATE `creature_template` SET `npcflag`='0' WHERE `entry`='11627';

-- Zul'Drak
-- The Champion of Anguish, http://old.wowhead.com/quest=12948
UPDATE `quest_template` SET `StartScript`='0' WHERE `Id`='12948';
UPDATE `creature_template` SET `ScriptName` = 'npc_vladof_butcher' WHERE `entry`=30022;

-- Elwynn Forest
-- Quest: Garments of the Light, http://old.wowhead.com/quest=5624
UPDATE `creature_template` SET `faction_A`='11',`faction_H`='11' WHERE `entry`='12423';
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1000174 AND -1000164;
INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
('0','-1000164','Ah, $GPriest:Priestess; you came along just in time. I appreciate it.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','2','garments SAY_COMMON_HEALED'),
('0','-1000165','Thank you! Thank you, $GPriest:Priestess;. Now I can take on those gnolls with your power to back me!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','1','1','garments SAY_DG_KEL_THANKS'),
('0','-1000166','Farewell to you, and may shadow always protect you!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','1','3','garments SAY_DG_KEL_GOODBYE'),
('0','-1000167','Thank you! Thank you, $GPriest:Priestess;. Now I can take on those murlocs with the Light on my side!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','7','1','garments SAY_ROBERTS_THANKS'),
('0','-1000168','Farewell to you, and may the Light be with you always.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','7','3','garments SAY_ROBERTS_GOODBYE'),
('0','-1000169','Thank you! Thank you, $GPriest:Priestess;. Now I can take on those humans with your power to back me!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','1','1','garments SAY_KORJA_THANKS'),
('0','-1000170','Farewell to you, and may our ancestors be with you always!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','1','3','garments SAY_KORJA_GOODBYE'),
('0','-1000171','Thank you! Thank you, $GPriest:Priestess;. Now I can take on those wendigo with the Light on my side!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','7','1','garments SAY_DOLF_THANKS'),
('0','-1000172','Farewell to you, and may the Light be with you always.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','7','3','garments SAY_DOLF_GOODBYE'),
('0','-1000173','Thank you! Thank you, $GPriest:Priestess;. Now I can take on those corrupt timberlings with Elune`s power behind me!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','2','1','garments SAY_SHAYA_THANKS'),
('0','-1000174','Farewell to you, and may Elune be with you always.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','2','3','garments SAY_SHAYA_GOODBYE');

-- Dustwallow Marsh
-- Quest: Cleansing Witch Hill, http://old.wowhead.com/quest=11183
DELETE FROM event_scripts WHERE id = 15452;
INSERT INTO `event_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES
('15452','2','10','23864','3000000','0','-2984.98','-3853.72','45.714','5.34');

-- Hellfire Peninsula
-- Quest: The Demoniac Scryer, http://old.wowhead.com/quest=10838
UPDATE `creature_template` SET `AIName` = 'EventAI' WHERE `entry`=22258;
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`)VALUES 
(NULL,'22258','10','0','100','1','1','0','0','0','11','38708','6','1','41','10000','0','0','0','0','0','0','');

-- Silverpine Forest
-- Quest: Pyrewood Ambush, http://old.wowhead.com/quest=452
UPDATE `quest_template` SET `SpecialFlags`='2' WHERE `Id`='452';

-- Icecrown
-- Quest: The Black Knight's Fall, http://old.wowhead.com/quest=13664
SET @QUEST := 13664;
SET @NPC_BLACK_KNIGHT := 33785;
SET @NPC_BLACK_KNIGHT_GRYPHON = 33513; 
SET @NPC_CAVIN := 33522;
SET @SPELL_CHARGE := 63003;
SET @SPELL_SHIELD_BREAKER := 65147;
SET @SPELL_DARK_SHIELD := 64505;
SET @SPELL_BLACK_NIGHT_TRANSFORM := 64490;
SET @SPELL_BLACK_NIGHT_TRANSFORM_2 := 64498;
SET @SPELL_FULL_HEAL := 25840;
SET @GOSSIP := 10383;
DELETE FROM `gossip_menu_option` WHERE `menu_id`=@GOSSIP;
INSERT INTO `gossip_menu_option` VALUES
(@GOSSIP,1,0,'Ask Cavin to summon the Black Knight.',1,1,0,0,0,0,NULL);
DELETE FROM conditions WHERE SourceGroup=@GOSSIP AND SourceTypeOrReferenceId=15;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
(15,@GOSSIP,1,0,9,@QUEST,0,0,0,'','Only show gossip when player is on quest The Black Knight Fall');
UPDATE `creature_template` SET AIName='SmartAI',`ScriptName` = '' WHERE `entry`=@NPC_CAVIN;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@NPC_CAVIN;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@NPC_CAVIN*100;
INSERT INTO `smart_scripts` VALUES
(@NPC_CAVIN,0,0,1,62,0,100,0,@GOSSIP,1,0,0,80,@NPC_CAVIN*100,0,2,0,0,0,1,0,0,0,0,0,0,0,'Cavin - On gossip option select - Run script'),
(@NPC_CAVIN,0,1,2,61,0,100,0,0,0,0,0,12,@NPC_BLACK_KNIGHT,1,120000,0,0,0,8,0,0,0,8436.9,970.9,544.7,0,'Cavin - On gossip option select - Summon the Black Knight'),
(@NPC_CAVIN,0,2,0,61,0,100,0,0,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Cavin - On gossip option select - Close gossip'),
(@NPC_CAVIN*100,9,0,0,0,0,100,0,0,0,0,0,81,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Cavin - On Script - Turn off Gossip & Gossip flags'),
(@NPC_CAVIN*100,9,1,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Cavin - On Script - Say text 0'),
(@NPC_CAVIN*100,9,2,0,0,0,100,0,3000,3000,0,0,1,1,0,0,0,0,0,7,0,0,0,0,0,0,0,'Cavin - On Script - Say text 1');
DELETE FROM `creature_text` WHERE `entry`=@NPC_CAVIN;
INSERT INTO `creature_text` VALUES 
(@NPC_CAVIN,0,0,'$N challenges the Black Knight to trial by combat!',14,0,0,0,0,0,'yell'),
(@NPC_CAVIN,1,0,'Good luck, $N.',12,0,0,0,0,0,'say');
UPDATE `creature_template` SET AIName='SmartAI', `ScriptName` = '' WHERE `entry`=@NPC_BLACK_KNIGHT;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@NPC_BLACK_KNIGHT;
DELETE FROM `smart_scripts` WHERE `source_type`=9 AND `entryorguid`=@NPC_BLACK_KNIGHT*100;
INSERT INTO `smart_scripts` VALUES
(@NPC_BLACK_KNIGHT,0,0,0,54,0,100,1,0,0,0,0,43,@NPC_BLACK_KNIGHT_GRYPHON,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - Just Summoned - Mount to entry'),
(@NPC_BLACK_KNIGHT,0,1,0,4,0,100,1,0,0,0,0,11,@SPELL_CHARGE,0,0,0,0,0,2,0,0,0,0,0,0,0,'Blackknight - On Aggro - Cast Charge'),
(@NPC_BLACK_KNIGHT,0,2,3,0,0,100,0,15000,20000,15000,20000,22,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Aggro - Set Phase 1'),
(@NPC_BLACK_KNIGHT,0,3,0,61,1,100,0,0,0,0,0,25,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - In Phase 1 - Flee for assist'),
(@NPC_BLACK_KNIGHT,0,4,0,9,1,100,0,5,30,1000,1000,11,@SPELL_CHARGE,0,0,0,0,0,2,0,0,0,0,0,0,0,'Blackknight - In Phase 1 - Cast Charge'),
(@NPC_BLACK_KNIGHT,0,5,0,9,1,100,0,3,30,1500,2000,11,@SPELL_SHIELD_BREAKER,0,0,0,0,0,2,0,0,0,0,0,0,0,'Blackknight - In Phase 1 & On Range - Cast Shield Breaker'),
(@NPC_BLACK_KNIGHT,0,6,0,6,0,100,1,0,0,0,0,81,1,0,0,0,0,0,9,@NPC_CAVIN,0,200,0,0,0,0,'Blackknight - On Death - Turn on Gossip & Gossip flags on Cavin'),
(@NPC_BLACK_KNIGHT,0,7,8,1,0,100,0,60000,60000,80000,80000,41,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - Out Of Combat after 60s - Despawn'),
(@NPC_BLACK_KNIGHT,0,8,0,61,0,100,0,0,0,0,0,81,1,0,0,0,0,0,9,@NPC_CAVIN,0,200,0,0,0,0,'Blackknight - Out Of Combat after 60s - Turn on Gossip & Gossip flags on Cavin'),
(@NPC_BLACK_KNIGHT,0,9,0,2,1,100,1,0,25,0,0,80,@NPC_BLACK_KNIGHT*100,2,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On 25% health - Run script'),
(@NPC_BLACK_KNIGHT*100,9,0,0,0,0,100,0,0,0,0,0,24,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - Evade'),
(@NPC_BLACK_KNIGHT*100,9,1,0,0,0,100,0,0,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - State passive'),
(@NPC_BLACK_KNIGHT*100,9,2,0,0,0,100,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - Say text 0'),
(@NPC_BLACK_KNIGHT*100,9,3,0,0,0,100,0,0,0,0,0,43,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - Unmount'),
(@NPC_BLACK_KNIGHT*100,9,4,0,0,0,100,0,0,0,0,0,11,@SPELL_DARK_SHIELD,2,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - Cast Dark Shield'),
(@NPC_BLACK_KNIGHT*100,9,5,0,0,0,100,0,6000,6000,0,0,11,@SPELL_BLACK_NIGHT_TRANSFORM,2,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - Apply Aura'),
(@NPC_BLACK_KNIGHT*100,9,6,0,0,0,100,0,0,0,0,0,11,@SPELL_FULL_HEAL,2,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - Full hp'),
(@NPC_BLACK_KNIGHT*100,9,7,0,0,0,100,0,1000,1000,0,0,11,@SPELL_BLACK_NIGHT_TRANSFORM_2,2,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - Increase Max Health'),
(@NPC_BLACK_KNIGHT*100,9,8,0,0,0,100,0,0,0,0,0,43,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Blackknight - On Script - Unmount player'),
(@NPC_BLACK_KNIGHT*100,9,9,0,0,0,100,0,0,0,0,0,8,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - State Aggresive'),
(@NPC_BLACK_KNIGHT*100,9,10,0,0,0,100,0,1000,1000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Blackknight - On Script - Say text 1'),
(@NPC_BLACK_KNIGHT*100,9,11,0,0,0,100,0,0,0,0,0,49,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Blackknight - On Script - Start Attack');
DELETE FROM `creature_text` WHERE `entry`=@NPC_BLACK_KNIGHT;
INSERT INTO `creature_text` VALUES 
(@NPC_BLACK_KNIGHT,0,0,'Get off that horse and fight me man-to-man!',14,0,0,0,0,0,'yell'),
(@NPC_BLACK_KNIGHT,1,0,'I will not fail you, master!',14,0,0,0,0,0,'yell');

-- Howling Fjord
-- Quest: The Shining Light, http://old.wowhead.com/quest=11288
UPDATE `quest_template` SET `LimitTime`=600 WHERE `id`=11288;
SET @Ghoul := 24177;
SET @SpellTrigger := 43202;
SET @Spell := 43203;
SET @Ares  := 24189;
UPDATE `creature_template` SET `AIname`='SmartAI' WHERE `entry`=@Ghoul;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@Ghoul;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@Ghoul,0,0,0,1,0,100,0,20000,300000,50000,350000,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Decomposing Ghoul - Occ - Say random text'),
(@Ghoul,0,1,2,8,0,100,0,@Spell,0,0,0,18,33685506,0,0,0,0,0,1,0,0,0,0,0,0,0,'Decomposing Ghoul - On hit by spell - Set unit flag for not targetable'),
(@Ghoul,0,2,3,61,0,100,0,0,0,0,0,2,35,0,0,0,0,0,1,0,0,0,0,0,0,0,'Decomposing Ghoul - Linked with previous event - Switch faction to clear aggro'),
(@Ghoul,0,3,0,61,0,100,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Decomposing Ghoul - Linked with previous event - Say random text'),
(@Ghoul,0,4,5,1,0,100,0,3500,3500,3500,3500,19,33685506,0,0,0,0,0,1,0,0,0,0,0,0,0,'Decomposing Ghoul - OOC for 3,5 sec - Remove unit flag'),
(@Ghoul,0,5,0,61,0,100,0,0,0,0,0,2,14,0,0,0,0,0,1,0,0,0,0,0,0,0,'Decomposing Ghoul - Linked with previous event - Change faction back to 14');
UPDATE `creature_template` SET `AIname`='SmartAI' WHERE `entry`=@Ares;
DELETE FROM `smart_scripts` WHERE `source_type`=0 AND `entryorguid`=@Ares;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@Ares,0,0,0,19,0,100,0,11288,0,0,0,85,@SpellTrigger,0,0,0,0,0,7,0,0,0,0,0,0,0,'Ares - On target quest accepted 11288 - Cast spell Shining Light');
DELETE FROM `creature_text` WHERE `entry`=@Ghoul;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@Ghoul,0,1,'Light... light so bright...',12,0,50,0,0,0,'Decomposing Ghoul - On spell hit'),
(@Ghoul,0,2,'ARGHHHH...',12,0,50,0,0,0,'Decomposing Ghoul - On spell hit'),
(@Ghoul,0,3,'Away... go...',12,0,50,0,0,0,'Decomposing Ghoul - On spell hit'),
(@Ghoul,0,4,'Bad light... hurt...',12,0,50,0,0,0,'Decomposing Ghoul - On spell hit'),
(@Ghoul,0,5,'BURNS! IT BURNS!',12,0,50,0,0,0,'Decomposing Ghoul - On spell hit'),
(@Ghoul,1,1,'So... Hungry...',12,0,50,0,0,0,'Decomposing Ghoul - OOC'),
(@Ghoul,1,2,'Closer... come closer...',12,0,50,0,0,0,'Decomposing Ghoul - OOC'),
(@Ghoul,1,3,'FEED ME...',12,0,50,0,0,0,'Decomposing Ghoul - OOC'),
(@Ghoul,1,4,'FOOD! EAT YOU!',12,0,50,0,0,0,'Decomposing Ghoul - OOC'),
(@Ghoul,1,5,'BRAINNNS!',12,0,50,0,0,0,'Decomposing Ghoul - OOC');
DELETE FROM `conditions` WHERE `SourceEntry`=@Spell AND `SourceTypeOrReferenceId`=13;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(13,1,@Spell,0,0,31,0,3,@Ghoul,0,0,0,'', 'Shinning Light can only hit Decomposing Ghouls');
DELETE FROM `conditions` WHERE `SourceEntry`=@Spell AND `SourceTypeOrReferenceId`=17;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES 
(17,0,@Spell,0,0,9,0,11288,0,0,0,0,'', 'Shinning Light can only hit targets on the quest');

-- .npc set health
DELETE FROM `command` WHERE NAME LIKE "npc set health";
INSERT INTO `command` (`name`, `security`, `help`) VALUES
('npc set health','3','Syntax: .npc set heath #hp\r\n\r\nModify the hp of the selected creature.');

-- Transmogrify
DELETE FROM creature_template WHERE entry = '190001'; 
INSERT INTO creature_template (entry, modelid1, name, subname, IconName, gossip_menu_id, minlevel, maxlevel, Health_mod, Mana_mod, Armor_mod, faction_A, faction_H, npcflag, speed_walk, speed_run, scale, rank, dmg_multiplier, unit_class, unit_flags, type, type_flags, InhabitType, RegenHealth, flags_extra, ScriptName) VALUES 
('190001', '15998', "Мастер трансмогрификации", "", 'Speak', '50000', 71, 71, 1.56, 1.56, 1.56, 35, 35, 3, 1, 1.14286, 1.25, 1, 1, 1, 2, 7, 138936390, 3, 1, 2, 'npc_transmogrify'); 

REPLACE INTO `gossip_menu` VALUES (51000, 51000);
REPLACE INTO npc_text (ID, text0_0, em0_1) VALUES
(51000, 'Put in the first slot of bag item, that you want to transmogrify. In the second slot, put item with perfect display.', 0);

-- Правильная фракция для стражников в подгороде
UPDATE `creature_template` SET faction_A = 85, `faction_H` = 85 WHERE entry = 36213;

-- Фикс телепортации на Isle of Conquest
DELETE FROM `creature` WHERE `id` IN (22515,23472) AND `map` = 628;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`) VALUES
(250194, 23472, 628, 3, 1, 0, 0, 1139.92, -780.212, 48.6757, 3.16908, 300, 0, 0, 4120, 0, 0),
(250214, 22515, 628, 3, 1, 0, 0, 323.214, -884.536, 48.9155, 1.59435, 300, 0, 0, 4120, 0, 0),
(250212, 22515, 628, 3, 1, 0, 0, 325.953, -782.401, 48.9163, 4.65741, 300, 0, 0, 4120, 0, 0),
(250210, 22515, 628, 3, 1, 0, 0, 393.258, -858.941, 48.9161, 3.22484, 300, 0, 0, 4120, 0, 0),
(250208, 22515, 628, 3, 1, 0, 0, 1233.08, -840.021, 48.9176, 1.51268, 300, 0, 0, 4120, 0, 0),
(250206, 22515, 628, 3, 1, 0, 0, 1162.9, -746.146, 48.6285, 6.1536, 300, 0, 0, 4120, 0, 0),
(250203, 22515, 628, 3, 1, 0, 0, 1235.15, -689.807, 49.1079, 1.52132, 300, 0, 0, 4120, 0, 0),
(250198, 23472, 628, 3, 1, 0, 0, 1235.61, -863.124, 48.9713, 4.7171, 300, 0, 0, 4120, 0, 0),
(250196, 23472, 628, 3, 1, 0, 0, 1236.6, -663.616, 47.8887, 3.00572, 300, 0, 0, 4120, 0, 0),
(250182, 23472, 628, 3, 1, 0, 0, 324.262, -745.282, 49.4923, 1.55901, 300, 0, 0, 4120, 0, 0),
(250180, 23472, 628, 3, 1, 0, 0, 311.937, -918.894, 48.6856, 4.76736, 300, 0, 0, 4120, 0, 0),
(250186, 23472, 628, 3, 1, 0, 0, 430.61, -857.491, 48.198, 0.074609, 300, 0, 0, 4120, 0, 0);

-- Мелкие корректировки спеллов
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (63644, 63645) AND `spell_effect` = -58427;
INSERT INTO `spell_linked_spell` VALUES
(63644, -58427,0,""),
(63645, -58427,0,"");
UPDATE `spell_proc_event` SET `Cooldown` = 1 WHERE `entry` IN (13983, 14070, 14071);

-- Cигнатуры для Simplefly
DELETE FROM warden_checks WHERE id IN (787,788,789);
INSERT INTO warden_checks VALUES ('787', '243', '', '', '7728616', '1', '75', 'Simplefly');
INSERT INTO warden_checks VALUES ('788', '243', '', '', '9993834', '1', '74', 'Simplefly');
INSERT INTO warden_checks VALUES ('789', '243', '', '', '9993835', '1', '52', 'Simplefly');

-- Фикс для Sylvanas Music Box, http://old.wowhead.com/item=52253
REPLACE INTO `spell_script_names` VALUES (73331,"spell_lament_of_the_highborne");

-- Некоторые из уже сконвертированных кондишнов
DELETE FROM `conditions` WHERE `ConditionTypeOrReference` = 18;
INSERT IGNORE `conditions` (`SourceTypeOrReferenceId`, `SourceGroup`, `SourceEntry`, `SourceId`, `ElseGroup`, `ConditionTypeOrReference`, `ConditionTarget`, `ConditionValue1`, `ConditionValue2`, `ConditionValue3`, `NegativeCondition`, `ErrorTextId`, `ScriptName`, `Comment`) VALUES
('13','1','62834','0','4','31','0','3','33344','0','0','0','','Boombot Boom - Pummeler target'),
('13','3','39844','0','0','31','0','5','185549','0','0','0','','Skyguard Blasting Charge - limit GO targets to Monstrous Kaliri Egg'),
('13','1','62834','0','0','32','0','144','0','0','0','0','','Boombot Boom - Player target'),
('13','1','62834','0','3','31','0','3','33343','0','0','0','','Boombot Boom - Scrapbot target'),
('13','1','62834','0','5','31','0','3','33346','0','0','0','','Boombot Boom - Boombot target'),
('13','1','62272','0','0','31','0','5','194151','0','0','0','',NULL),
('13','1','62272','0','1','31','0','3','32318','0','0','0','',NULL),
('13','3','63766','0','0','31','0','3','33661','0','0','0','','Arm Sweep (10m) Target'),
('13','3','63983','0','0','31','0','3','33661','0','0','0','','Arm Sweep (25m) Target'),
('13','1','48363','0','0','31','0','3','27315','0','0','0','',NULL),
('13','2','72869','0','0','31','0','3','38285','0','0','0','','Slime Puddle - target Mutated Abomination'),
('13','2','72456','0','0','31','0','3','38285','0','0','0','','Slime Puddle - target Mutated Abomination'),
('13','2','72868','0','0','31','0','3','37672','0','0','0','','Slime Puddle - target Mutated Abomination'),
('13','2','70346','0','0','31','0','3','37672','0','0','0','','Slime Puddle - target Mutated Abomination'),
('13','7','61920','0','2','31','0','3','32927','0','0','0','',NULL),
('13','7','61920','0','1','31','0','3','32867','0','0','0','',NULL),
('13','7','61920','0','0','31','0','3','32857','0','0','0','',NULL),
('13','3','63317','0','0','31','0','3','33388','0','0','0','','Flame Breath - Dark Rune Guardian'),
('13','1','73082','0','0','31','0','3','39420','0','0','0','',NULL),
('13','1','74455','0','0','31','0','3','39747','0','0','0','','Ragefire - Conflagration'),
('13','1','62834','0','2','31','0','3','33329','0','0','0','','Boombot Boom - Heart of the Deconstructor target'),
('13','1','62834','0','1','31','0','3','33293','0','0','0','','Boombot Boom - XT-002 target'),
('13','1','62488','0','0','31','0','3','33121','0','0','0','','Activate Construct to iron Construct'),
('13','1','62343','0','0','31','0','3','33121','0','0','0','','Heat to Iron Construct'),
('13','3','65045','0','6','31','0','3','34161','0','0','0','','Flames to Mechanostriker 54-A'),
('13','3','65045','0','5','31','0','3','33090','0','0','0','','Flames to Pool of Tar'),
('13','3','65045','0','4','31','0','3','33189','0','0','0','','Flames to Liquid pyrite'),
('13','3','65045','0','3','31','0','3','33237','0','0','0','','Flames to Ulduar Colossus'),
('13','3','65045','0','2','31','0','3','33572','0','0','0','','Flames to Steelforged Defender'),
('13','3','65045','0','1','31','0','3','33236','0','0','0','','Flames to Steelforged Defender'),
('13','3','65044','0','10','31','0','3','33060','0','0','0','','Flames to Salvaged Salvaged Siege Engine'),
('13','3','65045','0','0','31','0','3','34234','0','0','0','','Flames to Runeforged Sentry'),
('13','3','65044','0','8','31','0','3','34045','0','0','0','','Flames to Salvaged Chopper'),
('13','3','65044','0','9','31','0','3','33109','0','0','0','','Flames to Salvaged Demolisher'),
('13','3','65044','0','7','31','0','3','33062','0','0','0','','Flames to Salvaged Chopper'),
('13','1','62911','0','0','31','0','3','33365','0','0','0','','Thorim\'s Hammer to Thorim\'s Hammer'),
('13','1','62906','0','0','31','0','3','33367','0','0','0','','Freya\'s Ward to Freya\'s Ward'),
('13','3','65044','0','6','31','0','3','34161','0','0','0','','Flames to Mechanostriker 54-A'),
('13','3','65044','0','4','31','0','3','33189','0','0','0','','Flames to Liquid pyrite'),
('13','3','65044','0','5','31','0','3','33090','0','0','0','','Flames to Pool of Tar'),
('13','3','65044','0','2','31','0','3','33572','0','0','0','','Flames to Steelforged Defender'),
('13','3','65044','0','3','31','0','3','33237','0','0','0','','Flames to Ulduar Colossus'),
('13','3','65044','0','1','31','0','3','33236','0','0','0','','Flames to Steelforged Defender'),
('13','3','65044','0','0','31','0','3','34234','0','0','0','','Flames to Runeforged Sentry'),
('13','3','65045','0','7','31','0','3','33062','0','0','0','','Flames to Salvaged Chopper'),
('13','3','65045','0','8','31','0','3','34045','0','0','0','','Flames to Salvaged Chopper'),
('13','3','65045','0','9','31','0','3','33109','0','0','0','','Flames to Salvaged Demolisher'),
('13','3','65045','0','10','31','0','3','33060','0','0','0','','Flames to Salvaged Salvaged Siege Engine'),
('13','3','39844','0','1','31','0','3','22991','0','0','0','',NULL),
('13','1','44550','0','0','31','0','3','24820','0','0','0','',NULL),
('13','1','65387','0','0','32','0','144','0','0','0','0','',NULL),
('13','1','61901','0','0','31','0','3','32867','0','0','0','',NULL);

INSERT IGNORE `conditions`(`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`SourceId`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionTarget`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`NegativeCondition`,`ErrorTextId`,`ScriptName`,`Comment`) values 
(13,1,39921,0,0,31,0,3,23081,0,0,0,'','VimGol Pentagram visual'),
(13,1,51368,0,0,31,0,3,26693,0,0,0,'',NULL),
(13,1,62016,0,0,31,0,3,33378,0,0,0,'',NULL),
(13,1,62304,0,0,31,0,3,33105,0,0,0,'',NULL),
(13,2,62363,0,0,31,0,3,33214,0,0,0,'',NULL),
(13,4,62466,0,0,31,0,3,32780,0,0,0,'',NULL),
(13,1,62533,0,0,31,0,3,33108,0,0,0,'','Hodir\'s Fury'),
(13,1,62711,0,0,31,0,3,33118,0,0,0,'','Ingis - Grab'),
(13,1,62909,0,0,31,0,3,33369,0,0,0,'','Mimiron\'s Inferno'),
(13,7,62942,0,1,31,0,3,32874,0,0,0,'',NULL),
(13,7,62942,0,0,31,0,3,32872,0,0,0,'',NULL),
(13,7,62942,0,2,31,0,3,32875,0,0,0,'',NULL),
(13,7,62942,0,3,31,0,3,33110,0,0,0,'',NULL),
(13,1,62976,0,0,31,0,3,34055,0,0,0,'',NULL),
(13,1,63001,0,0,31,0,3,33438,0,0,0,'',''),
(13,6,63041,0,3,31,0,3,34057,0,0,0,'',NULL),
(13,6,63041,0,0,32,0,144,0,0,0,0,'',NULL),
(13,6,63041,0,1,31,0,3,33836,0,0,0,'',NULL),
(13,6,63041,0,4,31,0,3,34147,0,0,0,'',NULL),
(13,6,63041,0,5,31,0,3,34362,0,0,0,'',NULL),
(13,6,63041,0,2,31,0,3,33855,0,0,0,'',NULL),
(13,3,63414,0,0,31,0,3,33651,0,0,0,'',NULL),
(13,1,63882,0,0,31,0,3,33882,0,0,0,'','Effekt on Death Orb'),
(13,1,63886,0,0,31,0,3,33882,0,0,0,'','Effekt on Death Orb'),
(13,3,64021,0,1,31,0,3,33388,0,0,0,'','Flame Breath - Dark Rune Guardian'),
(13,3,64021,0,0,32,0,144,0,0,0,0,'','Flame Breath - Players'),
(13,3,64021,0,4,31,0,3,33846,0,0,0,'','Flame Breath - Dark Rune Sentinel'),
(13,3,64021,0,2,31,0,3,33453,0,0,0,'','Flame Breath - Dark Rune Watcher'),
(13,3,64021,0,3,31,0,3,33816,0,0,0,'','Flame Breath - Expedition Defender'),
(13,1,64098,0,0,31,0,3,32865,0,0,0,'',NULL),
(13,1,64172,0,0,31,0,3,33988,0,0,0,'','Effekt only for Immortal Guardians'),
(13,1,64184,0,0,31,0,3,33288,0,0,0,'','Effekt on YoggSaron'),
(13,1,64224,0,0,31,0,3,32934,0,0,0,'','Stone Grip Absorb'),
(13,1,64225,0,0,31,0,3,32934,0,0,0,'','Stone Grip Absorb'),
(13,1,64414,0,0,31,0,3,33109,0,0,0,'',NULL),
(13,1,64444,0,0,31,0,3,33670,0,0,0,'',NULL),
(13,1,64465,0,0,31,0,3,33988,0,0,0,'','Effekt only for Immortal Guardians'),
(13,2,64570,0,1,31,0,3,34363,0,0,0,'',NULL),
(13,2,64570,0,0,31,0,3,34121,0,0,0,'',NULL),
(13,1,64597,0,0,31,0,3,33105,0,0,0,'',NULL),
(13,1,64619,0,1,31,0,3,34363,0,0,0,'',NULL),
(13,1,64619,0,0,31,0,3,34121,0,0,0,'',NULL),
(13,4,64626,0,1,31,0,3,34363,0,0,0,'',NULL),
(13,4,64626,0,0,31,0,3,34121,0,0,0,'',NULL),
(13,1,64996,0,0,31,0,3,34246,0,0,0,'',NULL),
(13,1,65192,0,1,31,0,3,34363,0,0,0,'',NULL),
(13,1,65192,0,0,31,0,3,34121,0,0,0,'',NULL),
(13,2,65209,0,0,31,0,3,33134,0,0,0,'','Effekt only for Sara'),
(13,2,65209,0,1,31,0,3,33136,0,0,0,'','Effekt only for Guardian of YoggSaron'),
(13,4,65333,0,1,31,0,3,34363,0,0,0,'',NULL),
(13,4,65333,0,0,31,0,3,34121,0,0,0,'',NULL);


-- Some warnings fixes
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (SELECT `entry` FROM `creature_template` WHERE `AIName`="SmartAI");
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (SELECT `entry` FROM `creature_template` WHERE `AIName` ='');
DELETE FROM `creature_addon` WHERE guid NOT IN (SELECT `guid` FROM `creature`);
DELETE FROM `gameobject` WHERE `id` NOT IN (SELECT `entry` FROM `gameobject_template`);
UPDATE `creature` SET `spawndist` = 0 WHERE `MovementType`= 0;
UPDATE `creature_template` SET `exp` = 0 WHERE `exp` > 2;
DELETE FROM `conditions` WHERE ConditionTypeOrReference = 24 AND Sourceentry = 39651;
DELETE FROM `script_waypoint` WHERE entry = 33370;
DELETE FROM `db_script_string` WHERE entry IN (2000000599,2000000600,2000000601,2000000602);
DELETE FROM creature_template WHERE entry = 367880;
DELETE FROM `reference_loot_template` WHERE `entry` IN (34117,34118,34158,34159,34154);
DELETE FROM `gameobject_loot_template` WHERE entry IN (3458,3459,3460,3461,10961,15920,16841,26878,27725,40001,40002,201710,202336);
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
('34154','45088','4','1','1','1','1'),
('34154','45089','4','1','1','1','1'),
('34154','45090','4','1','1','1','1'),
('34154','45091','4','1','1','1','1'),
('34154','45092','4','1','1','1','1'),
('34154','45093','4','1','1','1','1'),
('34154','45094','4','1','1','1','1'),
('34154','45095','4','1','1','1','1'),
('34154','45096','4','1','1','1','1'),
('34154','45097','4','1','1','1','1'),
('34154','45098','4','1','1','1','1'),
('34154','45099','4','1','1','1','1'),
('34154','45100','4','1','1','1','1'),
('34154','45101','4','1','1','1','1'),
('34154','45102','4','1','1','1','1'),
('34154','45103','4','1','1','1','1'),
('34154','45104','4','1','1','1','1'),
('34154','45105','4','1','1','1','1'),
('34154','46027','14','1','1','1','1'),
('34154','46348','14','1','1','1','1');
