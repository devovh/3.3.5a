#include "Define.h"
#include "GossipDef.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "player_store_manager.h"
#include "WorldSession.h"
#include "ObjectMgr.h"
#include <sstream>
#include <string>
#include <vector>

std::string getString(std::string string, uint32 number);
std::string getDPString(std::string string, uint32 number, uint8 quality);
uint32 getDPFromID(uint32 item_id);

bool canRun = true;

class dp_items
{
public:
	dp_items()	{}
	dp_items(uint32 item_id, uint8 item_type, std::string item_name, uint8 quality, uint32 dp_cost)
	{
		this->item_id = item_id;
		this->dp_cost = dp_cost;
		this->quality = quality;
		this->item_type = item_type;
		this->item_name = item_name;
	}
	inline uint32	getItemID()		{ return item_id; }
	inline uint32	getDPCost()		{ return dp_cost; }
	inline uint8	getQuality()	{ return quality; }
	inline uint8	getItemType()	{ return item_type; }
	inline std::string getName()	{ return item_name; }

private:
	uint32 item_id, dp_cost;
	uint8 quality, item_type;
	std::string item_name;
};

std::vector<dp_items> items;

class load_dp : public WorldScript
{
public:
	load_dp() : WorldScript("load_dp") {}

	void OnStartup() {
		QueryResult loadQuery = WorldDatabase.Query(loadStmnt.c_str());
		Field *fields = loadQuery->Fetch();
		if (fields) {
			do
			{
				dp_items item = dp_items(fields[0].GetUInt32(), fields[1].GetUInt8(), fields[2].GetString(), fields[3].GetUInt8(), fields[4].GetUInt32());
				items.push_back(item);
			} while (loadQuery->NextRow());
			TC_LOG_INFO("server.loading", "DP Items Loaded Successfully.");
		}
		else
		{
			canRun = false;
		}
		QueryResult testQuery = LoginDatabase.Query("SELECT * from account LIMIT 1;");
		if (testQuery->GetFieldCount() < 25)
		{
			TC_LOG_INFO("server.loading", "ERROR: Missing dp_balance column.");
			canRun = false;
		}
		else
		{
			TC_LOG_INFO("server.loading", "DP System Loaded Successfully.");
		}		
	}

private:
	std::string loadStmnt = "SELECT * from dp_items;";

};

class gossip_dp : public CreatureScript {
public:
	gossip_dp() : CreatureScript("gossip_dp") { }

	uint32 getDP(Player* player)
	{
		QueryResult dQuery = LoginDatabase.Query(getString(dpQuery, player->GetSession()->GetAccountId()).c_str());
		Field *field = dQuery->Fetch();
		return field[0].GetUInt32();
	}

	bool OnGossipHello(Player* player, Creature* creature) 
	{
		if (canRun)
		{
			if (player->IsInCombat())
			{
				player->GetSession()->SendAreaTriggerMessage("???? ?? ??????");
				return false;
			}

            uint32 coins = Maelstrom::sStoreMgr->GetAccountCoins(player->GetSession()->GetAccountId());
			std::string name = player->GetName();
			std::ostringstream femb;
		    femb << "??????????????????|cffB404AE " << name << "|r\n";
			femb << "???????? ?? ?????? ???????????????????????? ?????????????? ?????? ?????????????? ???? ?????????????? ???????????????????? ???? ???? ?????????? ?????????? ?? ?????????????? <?????????????????????????? ??????????????>:\n\n";
		    femb << "* ?????????? ???????????????? ?????????????????? ?? ??????:\n";
		    femb << "* ?? ?????? ???????????????? ?????????????? ?? ???? ???????????? ???????????????? ???????????????????? ?????????????? ?????? ??????????\n";
		    femb << "\n     ?? ??????: [|cffB404AE " << coins << " |r] ??????????????.\n";

            player->PlayerTalkClass->ClearMenus();
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_shoulder_126:20:20:-20:0|tC?????? ??9", GOSSIP_SENDER_MAIN, 3); // ????????????
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_shoulder_126:20:20:-20:0|tC?????? ??11", GOSSIP_SENDER_MAIN, 8); // ????????????
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_belt_48b:20:20:-20:0|t?????? C???? | ?????? ??????", GOSSIP_SENDER_MAIN, 4); // ????????????
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_staff_112:20:20:-20:0|t???????????? ???? ??????????", GOSSIP_SENDER_MAIN, 2); // ????????????
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_staff_112:20:20:-20:0|t???????????? ??????????", GOSSIP_SENDER_MAIN, 5); // ????????????
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_shirt_orange_01:20:20:-20:0|t????????????", GOSSIP_SENDER_MAIN, 7);
			if (player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID || player->getClass() == CLASS_PALADIN)
			{
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_qirajidol_strife:20:20:-20:0|t????????????????", GOSSIP_SENDER_MAIN, 6); // ????????????
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
			player->PlayerTalkClass->SendGossipMenu(femb.str().c_str(), creature->GetGUID());
			return true;
		}
		else
		{
			return false;
		}

	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 actions)
	{
		player->PlayerTalkClass->ClearMenus();
		if (sender == GOSSIP_SENDER_MAIN) 
		{
			switch (actions)
			{
            case 2: // ???????????? ??8 
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_weapon_shortblade_104:20:20:-20:0|t??????????????", GOSSIP_SENDER_MAIN, 10);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_weapon_hand_33:20:20:-20:0|t????????????????", GOSSIP_SENDER_MAIN, 11);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_axe_113:20:20:-20:0|t????????????", GOSSIP_SENDER_MAIN, 12);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_mace_116:20:20:-20:0|t????????????????", GOSSIP_SENDER_MAIN, 13);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_sword_153:20:20:-20:0|t????????", GOSSIP_SENDER_MAIN, 14);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_weapon_staff_109:20:20:-20:0|t??????????????????", GOSSIP_SENDER_MAIN, 15);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_staff_108:20:20:-20:0|t????????????", GOSSIP_SENDER_MAIN, 16);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_weapon_bow_55:20:20:-20:0|t?????????????? ??????", GOSSIP_SENDER_MAIN, 17);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_shield_72:20:20:-20:0|t???????? | ?????????? ????????", GOSSIP_SENDER_MAIN, 18);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;

            case 4:
                        //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_belt_70:20:20:-20:0|t????????", GOSSIP_SENDER_MAIN, 19);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_boots_cloth_32:20:20:-20:0|t????????????", GOSSIP_SENDER_MAIN, 20);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_bracer_50:20:20:-20:0|t????????????????", GOSSIP_SENDER_MAIN, 21);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_jewelry_necklace_36:20:20:-20:0|t??????", GOSSIP_SENDER_MAIN, 22);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_misc_cape_18:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 23);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\Inv_misc_gem_bloodstone_03:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 24);
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_jewelry_ring_60:20:20:-20:0|t????????????", GOSSIP_SENDER_MAIN, 60);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;

            case 5:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_weapon_shortblade_104:20:20:-20:0|t??????????????", GOSSIP_SENDER_MAIN, 25);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_weapon_hand_33:20:20:-20:0|t????????????????", GOSSIP_SENDER_MAIN, 26);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_axe_113:20:20:-20:0|t????????????", GOSSIP_SENDER_MAIN, 27);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_mace_116:20:20:-20:0|t????????????????", GOSSIP_SENDER_MAIN, 28);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_sword_153:20:20:-20:0|t????????", GOSSIP_SENDER_MAIN, 29);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_weapon_staff_109:20:20:-20:0|t??????????????????", GOSSIP_SENDER_MAIN, 30);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_staff_108:20:20:-20:0|t????????????", GOSSIP_SENDER_MAIN, 31);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_weapon_bow_55:20:20:-20:0|t?????????????? ??????", GOSSIP_SENDER_MAIN, 32);
			//player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_shield_72:20:20:-20:0|t???????? | ?????????? ????????", GOSSIP_SENDER_MAIN, 33);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
            break;

			case 7:
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_misc_bag_17:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 34);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_shirt_blue_01:20:20:-20:0|t??????????????", GOSSIP_SENDER_MAIN, 35);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "|TInterface\\icons\\inv_shirt_guildtabard_01:20:20:-20:0|t???????????????? ??????????????", GOSSIP_SENDER_MAIN, 36);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
                        break;

			case 34: // ??????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 45)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 7);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 35: // ??????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 46)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 7);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 36: // ??????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 47)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 7);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;

			case 6: // ??????????
			{
				switch (player->getClass())
				{
				case CLASS_PALADIN:
			    for (unsigned int i = 0; i < items.size(); i++){
			    if (items.at(i).getItemType() == 40)
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			    }
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());				
                break;
                case CLASS_DEATH_KNIGHT:
			    for (unsigned int i = 0; i < items.size(); i++){
			    if (items.at(i).getItemType() == 41)
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			    }
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());					
                break;
                case CLASS_SHAMAN:
			    for (unsigned int i = 0; i < items.size(); i++){
			    if (items.at(i).getItemType() == 42)
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			    }
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());					
                break;
                case CLASS_DRUID:
			    for (unsigned int i = 0; i < items.size(); i++){
			    if (items.at(i).getItemType() == 43)
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			    }
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());					
                break;				
				}
			}
            break;

            // ???????????? ?????? 
            case 25: // ??????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 31)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 5);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 26: // ????????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 32)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 5);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 27: // ????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 33)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 5);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 28: // ????????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 34)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 5);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 29: // ????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 35)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 5);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 30: // ??????????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 36)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 5);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 31: // ????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 37)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 5);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 32: // ?????????????? ??????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 38)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 5);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 33: // ???????? ?????????? ????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 39)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 5);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break; 

			case 19: // ????????
			for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 11)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 4);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
			case 20: // ????????????
			for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 12)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 4);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;			
			case 21: // ????????????????
			for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 13)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 4);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;			
			case 22: // ??????
			for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 14)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 4);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;			
			case 23: // ??????????
			for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 15)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 4);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;			
			case 24: // ??????????
			for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 16)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			case 60: // ????????????
			for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 44)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 4);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break; 

            case 8: // ???????? ??11
            {
                switch (player->getClass())
				{
				case CLASS_WARRIOR:	
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 51)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;
                case CLASS_PALADIN:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 52)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
                case CLASS_HUNTER:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 53)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
                case CLASS_MAGE:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 54)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_WARLOCK:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 55)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_ROGUE:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 56)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_PRIEST:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 57)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_DEATH_KNIGHT:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 58)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_SHAMAN:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 59)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_DRUID:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 60)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;
				}
            }
            break;			         

            case 3: // ???????? ??9
            {
                switch (player->getClass())
				{
				case CLASS_WARRIOR:	
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 21)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;
                case CLASS_PALADIN:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 22)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
                case CLASS_HUNTER:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 23)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
                case CLASS_MAGE:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 24)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_WARLOCK:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 25)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_ROGUE:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 26)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_PRIEST:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 27)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_DEATH_KNIGHT:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 28)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_SHAMAN:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 29)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;				
				case CLASS_DRUID:
				for (unsigned int i = 0; i < items.size(); i++){
				if (items.at(i).getItemType() == 30)
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
				}
			    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
			    player->SEND_GOSSIP_MENU(1, creature->GetGUID());
				break;
				}
            }
            break;
            // ???????????? ??8 
            case 10: // ??????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 1)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 11: // ????????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 2)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 12: // ????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 3)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 13: // ????????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 4)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 14: // ????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 5)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 15: // ??????????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 6)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 16: // ????????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 7)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 17: // ?????????????? ??????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 8)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break;
            case 18: // ???????? ?????????? ????????
            for (unsigned int i = 0; i < items.size(); i++){
			if (items.at(i).getItemType() == 9)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_BATTLE, getDPString(items.at(i).getName(), items.at(i).getDPCost(), items.at(i).getQuality()).c_str(), GOSSIP_SENDER_MAIN+1, items.at(i).getItemID());
			}
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "|TInterface\\icons\\Spell_chargenegative:20:20:-20:0|t??????????", GOSSIP_SENDER_MAIN, 2);
			player->SEND_GOSSIP_MENU(1, creature->GetGUID());
			break; 

            // ???????? ??8  

			case GOSSIP_ACTION_INFO_DEF + 6:
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case GOSSIP_ACTION_INFO_DEF + 8:
				player->PlayerTalkClass->ClearMenus();
				OnGossipHello(player, creature);
				break;
			}
		}
	    else if (sender == GOSSIP_SENDER_MAIN + 1)
		{
			uint32 dpCost = getDPFromID(actions);	
			uint32 dpBAL = getDP(player);
			if (dpCost <= dpBAL)
			{
				if (player->AddItem(actions, 1)) {
					LoginDatabase.PExecute(accountQuery.c_str(), (dpBAL - dpCost), player->GetSession()->GetAccountId());
					player->GetSession()->SendNotification("?????????????? - ???? ?????????????? ???????????? ??????????????.");
				}
				else
				{
					player->GetSession()->SendNotification("???????????? - ?????????????????? ????????????, ???????? ?? ?????? ?????????? ?????????? ?????????????????? ?????? ?? ?????? ???????? ?????????? ?? ??????????. ???????????????? ?????????????????????????? ???????? ?? ?????? ???????????? ??????????????.");
				}
			}
			else
			{
				player->GetSession()->SendNotification("???????????? - ???????????????????????? ??????????????.");
			}
			player->PlayerTalkClass->SendCloseGossip();
		}
		return true;
	}

private:
	std::string accountQuery = "UPDATE account SET coin = %u WHERE id = %u;";
	std::string currentDP = "|TInterface\\icons\\Inv_misc_token_thrallmar:25:25:-15:0|t?????????????? ???? ???????????????? : ";
	std::string notEnoughDP = "?? ?????? ???? ???????????????????? ??????????????, ???? ?????????????? ???????????????? ???? ?????????????? ?????????? ?????? ???????????? ???? ??????????.";
	std::string dpQuery = "SELECT coin FROM account WHERE id=";
};

uint32 getDPFromID(uint32 item_id)
{
	uint32 dpCost = 99999;
	for (unsigned int i = 0; i < items.size(); i++)
		if (item_id == items.at(i).getItemID())
			dpCost = items.at(i).getDPCost();
	return dpCost;
}
std::string getString(std::string string, uint32 number)
{
	std::ostringstream oss;
	oss << string << number;
	return oss.str();
}
std::string getDPString(std::string string, uint32 number, uint8 quality)
{

	//Colors currently disabled.
	std::string color;
	switch (quality)
	{
	case 0:
		color = "|cff9d9d9d";
		break;
	case 1:
		color = "|cffffffff";
		break;
	case 2:
		color = "|cff47b247";
		break;
	case 3:
		color = "|cff00003d";
		break;
	case 5:
		color = "|cff331f00";
		break;
	default:
		color = "|cff3d003d";
		break;
	}
	std::ostringstream oss;
	//oss << color << string << " - (" << number << "DP)"; //With Color
	oss << color << string << " - (|cffE80000" << number << "|r ??????????????)"; //Without color
	return oss.str();
}


void AddSC_DPSystem()
{
	new load_dp();
	new gossip_dp();
}