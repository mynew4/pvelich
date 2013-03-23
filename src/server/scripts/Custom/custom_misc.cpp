/*
* Copyright (C) 2008 - 2011 Trinity <http://www.trinitycore.org/>
*
* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
*
* Copyright (C) 2011 Arcanum Core Private <https://bitbucket.org/Dimitro/arcanum-core-private/>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "ScriptPCH.h"
#include "Config.h"
#include "AccountMgr.h"

#define NPC_ENTRY_TO_SUMMON 100000
#define UNSUMMON_TIME 30000

#define FROST_EMBLEM 49426
#define TRIUMPH_EMBLEM 47241

/*
#define ITEM_COMPARE_ENTRY 12345
#define ITEM_COMPARE_COUNT 6
#define ITEM_RESULT_ENTRY 54321
#define ITEM_RESULT_COUNT 1
*/

class item_custom_summon : public ItemScript
{
public:
    item_custom_summon() : ItemScript("item_custom_summon") {}

    bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& /*targets*/)
    {
        if ((pPlayer->isInCombat()) || (pPlayer->isInFlight()) || (pPlayer->isDead()))
        {
            pPlayer->SendEquipError(EQUIP_ERR_NOT_IN_COMBAT, pItem, NULL);
            return false;
        }

        if (pPlayer->IsMounted())
        {
            pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, pItem, NULL);
            return false;
        }

        pPlayer->SummonCreature(NPC_ENTRY_TO_SUMMON, pPlayer->GetPositionX()+1, pPlayer->GetPositionY(), pPlayer->GetPositionZ()+2, 0, TEMPSUMMON_TIMED_DESPAWN, UNSUMMON_TIME);
        return false;
    }
};

class npc_emblem_exchanger : public CreatureScript
{
public:
    npc_emblem_exchanger() : CreatureScript("npc_emblem_exchanger") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM_EXTENDED(0, "Сменить эмблемы льда на эмблемы триумфа", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "Введите количество эмблем, которые вы хотите обменять.", 0, true);
        player->ADD_GOSSIP_ITEM_EXTENDED(0, "Сменить эмблемы триумфа на эмблемы льда", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2, "Введите количество эмблем, которые вы хотите обменять.", 0, true);

        player->SEND_GOSSIP_MENU(3961, creature->GetGUID());
        return true;
    }

    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction, const char* code)
    {
        player->PlayerTalkClass->ClearMenus();

        if (!*code)
            return false;

        uint16 count = (uint16)atoi((char*)code);

        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            if (player->GetItemCount(FROST_EMBLEM) >= count)
            {
                player->DestroyItemCount(FROST_EMBLEM, count, true, false);
                player->AddItem(TRIUMPH_EMBLEM, count*sWorld->getIntConfig(CONFIG_TRIUMPH_FOR_FROST_COUNT));
            }
            else
            {
                creature->MonsterWhisper("Недостаточно эмблем льда.", player->GetGUID());
            }
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
        {
            if (player->GetItemCount(TRIUMPH_EMBLEM) >= count /*дробные эмблемы льда не есть хорошо*/ && ((count % sWorld->getIntConfig(CONFIG_TRIUMPH_FOR_FROST_COUNT)) == 0))
            {
                player->DestroyItemCount(TRIUMPH_EMBLEM, count, true, false);
                player->AddItem(FROST_EMBLEM, count/sWorld->getIntConfig(CONFIG_TRIUMPH_FOR_FROST_COUNT));
            }
            else
            {
                creature->MonsterWhisper("Недостаточно эмблем триумфа или введенное число не кратно курсу обмена.", player->GetGUID());
            }
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        return true;
    }
};

class npc_vip_vendor : public CreatureScript
{
public:
    npc_vip_vendor() : CreatureScript("npc_vip_vendor") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetSession()->IsPremium() || player->isGameMaster())
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        }
        else
            creature->MonsterWhisper("Ваш аккаунт не является VIP аккаунтом.", player->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();

        if (uiAction == GOSSIP_ACTION_TRADE)
            player->GetSession()->SendListInventory(creature->GetGUID());
        return true;
    }
};

class npc_event_trap : public CreatureScript
{
public:
    npc_event_trap() : CreatureScript("npc_event_trap") { }

    struct npc_event_trapAI : public ScriptedAI
    {
        npc_event_trapAI(Creature* creature) : ScriptedAI(creature) 
        {
            me->SetVisible(false);
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!who || who->GetTypeId() != TYPEID_PLAYER || who->ToPlayer()->isGameMaster())
                return;

            if (me->IsWithinDist(who, 1.5f, false))
                DoCast(who, 66797);
         }
    };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_event_trapAI(creature);
        }

};

class gm_monitoring : public PlayerScript
{
public:
    gm_monitoring() : PlayerScript("gm_monitoring") {}

    void OnLogin(Player* player)
    {
        if (sWorld->getBoolConfig(CONFIG_GM_ENTERS_GAME))
        {
            if (player && AccountMgr::IsGMAccount(player->GetSession()->GetSecurity()))
            {
                std::string sText = ("Игровой мастер " + std::string(player->GetSession()->GetPlayerName()) + " входит в игру.");
                sWorld->SendServerMessage(SERVER_MSG_STRING, sText.c_str());
            }
        }
    }
    
    void OnLogout(Player* player)
    {
        if (sWorld->getBoolConfig(CONFIG_GM_ENTERS_GAME))
        {
            if (player && AccountMgr::IsGMAccount(player->GetSession()->GetSecurity()))
            {
                std::string sText = ("Игровой мастер " + std::string(player->GetSession()->GetPlayerName()) + " покидает игру.");
                sWorld->SendServerMessage(SERVER_MSG_STRING, sText.c_str());
            }
        }
    }
};

class ip_check : public PlayerScript
{
public:
    ip_check() : PlayerScript("ip_check") {}

    void OnLogin(Player* player)
    {
        if (sWorld->getBoolConfig(CONFIG_MULTIBOXING_KICK_ENABLE))
        {
            if (player->GetSession()->GetSecurity() > SEC_PLAYER)
                return;

            if (sWorld->getBoolConfig(CONFIG_MULTIBOXING_KICK_ONLY_ON_BG_OR_ARENA) && player->GetMap()->IsBattlegroundOrArena())
            {
                PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_IP_COUNT);
                stmt->setUInt32(0, player->GetSession()->GetAccountId());
                PreparedQueryResult result = LoginDatabase.Query(stmt);

                if(!result)
                    return;

                Field* fields = result->Fetch();
                uint16 count = fields[0].GetUInt16();

                if (!count)
                    return;

                if (count > 1)
                    player->GetSession()->KickPlayer();
            }
            else
            {
                PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_IP_COUNT);
                stmt->setUInt32(0, player->GetSession()->GetAccountId());
                PreparedQueryResult result = LoginDatabase.Query(stmt);

                if(!result)
                    return;

                Field* fields = result->Fetch();
                uint16 count = fields[0].GetUInt16();

                if (!count)
                    return;

                if (count > 1)
                    player->GetSession()->KickPlayer();
            }
        }
        return;
    }
};

/*
class npc_honor_exchanger : public CreatureScript
{
public:
    npc_honor_exchanger() : CreatureScript("npc_honor_exchanger") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM_EXTENDED(0, "Обменять хонор на АП", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "Введите количество хонора, которые вы хотите обменять.", 0, true);
        player->ADD_GOSSIP_ITEM_EXTENDED(0, "Обменять АП на хонор", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2, "Введите количество ап, которые вы хотите обменять.", 0, true);

        player->SEND_GOSSIP_MENU(3961, creature->GetGUID());
        return true;
    }

    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction, const char* code)
    {
        player->PlayerTalkClass->ClearMenus();

        if (!*code)
            return false;

        uint16 count = (uint16)atoi((char*)code);

        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            if (player->GetHonorPoints() >= count && ((count % sWorld->getIntConfig(CONFIG_AP_FOR_HONOR_COUNT)) == 0))
            {
                player->ModifyHonorPoints(-count);
                player->ModifyArenaPoints(count/sWorld->getIntConfig(CONFIG_AP_FOR_HONOR_COUNT));
            }
            else
            {
                creature->MonsterWhisper("Недостаточно хонора.", player->GetGUID());
            }
            player->CLOSE_GOSSIP_MENU();
            return true;
        }

        if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
        {
            if (player->GetArenaPoints() >= count)
            {
                player->ModifyArenaPoints(-count);
                player->ModifyHonorPoints(count*sWorld->getIntConfig(CONFIG_AP_FOR_HONOR_COUNT));
            }
            else
            {
                creature->MonsterWhisper("Недостаточно АП.", player->GetGUID());
            }
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        return true;
    }
};

class item_compare : public ItemScript
{
public:
    item_compare() : ItemScript("item_compare") {}

    bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const&)
    {
        if ((pPlayer->isInCombat()) || (pPlayer->isInFlight()) || (pPlayer->isDead()))
        {
            pPlayer->SendEquipError(EQUIP_ERR_NOT_IN_COMBAT, pItem, NULL);
            return false;
        }

        if (pPlayer->IsMounted())
        {
            pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, pItem, NULL);
            return false;
        }

        if (pPlayer->HasItemCount(ITEM_COMPARE_ENTRY, ITEM_COMPARE_COUNT, false))
        {
            pPlayer->DestroyItemCount(ITEM_COMPARE_ENTRY, ITEM_COMPARE_COUNT, true, false);
            pPlayer->AddItem(ITEM_RESULT_ENTRY, ITEM_RESULT_COUNT);
        }

        else
        pPlayer->Whisper("У вас недостаточное количество вещей", LANG_UNIVERSAL, pPlayer->GetGUID());

        return false;
    }
};
*/

/*
create table `character_morphs`( 
   `guid` int(10) UNSIGNED NOT NULL COMMENT 'Character guid', 
   `morph` int(5) UNSIGNED NOT NULL COMMENT 'Character morph'
 )  Engine='Default' comment='' row_format=Default charset=utf8 collate=utf8_general_ci


class morphing_on_login : public PlayerScript
{
public:
    morphing_on_login() : PlayerScript("morphing_on_login") {}

    void OnLogin(Player* player)
    {
        int64 pguid = player->GetGUID();
        QueryResult morph = CharacterDatabase.PQuery("SELECT morph from character_morphs WHERE guid = '%u'", pguid);
        QueryResult scale = CharacterDatabase.PQuery("SELECT scale from character_morphs WHERE guid = '%u'", pguid);

            if (morph)
                player->SetDisplayId(morph->Fetch()->GetUInt32());

            if (scale)
                player->SetFloatValue(OBJECT_FIELD_SCALE_X, scale->Fetch()->GetFloat());
    }
};

class morphing_tabard : public ItemScript
{
public:
    morphing_tabard() : ItemScript("morphing_tabard") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const&)
    {
        if ((player->isInCombat()) || (player->isInFlight()) || (player->isDead()))
        {
            player->SendEquipError(EQUIP_ERR_NOT_IN_COMBAT, item, NULL);
            return false;
        }

        if (player->IsMounted())
        {
            player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, item, NULL);
            return false;
        }

        uint64 pguid = player->GetGUID();
        QueryResult morph = CharacterDatabase.PQuery("SELECT morph FROM character_tabard_morphs WHERE guid = '%u'", pguid);

        if (morph)
            player->SetDisplayId(morph->Fetch()->GetUInt32());

        return false;
    }
};
*/

void AddSC_custom_misc()
{
    new item_custom_summon();
    new npc_emblem_exchanger();
    new npc_vip_vendor();
    new npc_event_trap();
    new gm_monitoring();
    new ip_check();
    //new morphing_tabard();
    //new morphing_on_login();
    //new item_compare();
    //hearthstone_without_cooldown();
}
