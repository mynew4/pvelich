/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Npc_Taxi
SD%Complete: 0%
SDComment: To be used for taxi NPCs that are located globally.
SDCategory: NPCs
EndScriptData
*/

#include "ScriptPCH.h"

#define GOSSIP_SUSURRUS         "Я готов(а)."
#define GOSSIP_NETHER_DRAKE     "Я готов(а) к полету, дракон!"
#define GOSSIP_BRAZEN           "Я готов(а) идти в Крепость Дарнхольд."
#define GOSSIP_IRONWING         "Я хотел(а) бы сделать полет вокруг Гавани Штормграда."
#define GOSSIP_DABIREE1         "Отвези меня к Вратам Муркет и Шаадраз."
#define GOSSIP_DABIREE2         "Отвези меня на Парящую Заставу."
#define GOSSIP_WINDBELLOW1      "Отвези меня на Косогор Бездны."
#define GOSSIP_WINDBELLOW2      "Отвези меня на Пик Чести."
#define GOSSIP_BRACK1           "Отвези меня к Вратам Муркет и Шаадраз."
#define GOSSIP_BRACK2           "Отвези меня на Косогор Бездны."
#define GOSSIP_BRACK3           "Отвези меня на Заставу Хребтолома."
#define GOSSIP_IRENA            "Отвези меня в Скеттис пожалуйста."
#define GOSSIP_CLOUDBREAKER1    "Мне приказали провести удар с воздуха."
#define GOSSIP_CLOUDBREAKER2    "Мне необходимо перехватить подкрепление Клинка Света."
#define GOSSIP_DRAGONHAWK       "<Поездка на драконадоре в Солнечный край>"
#define GOSSIP_VERONIA          "Отвези меня в Манагорн Коруу пожалуйста."
#define GOSSIP_DEESAK           "Отвези меня в Огри'лу пожалуйста."
#define GOSSIP_AFRASASTRASZ1    "Лорд Афрасастраз, я хотел(а) бы вернуться на землю."
#define GOSSIP_AFRASASTRASZ2    "Лорд, мне нужно попасть на второй этаж храма."
#define GOSSIP_TARIOLSTRASZ1    "Лорд, мне нужно попасть на второй этаж храма."
#define GOSSIP_TARIOLSTRASZ2    "Можете ли вы отправить меня к Лорду Афрасастразу в середину храма?"
#define GOSSIP_TORASTRASZA1     "Лорд Афрасастраз, я хотел(а) бы попасть в середину храма."
#define GOSSIP_TORASTRASZA2     "Да, пожалуйста. Я хотел(а) бы вернуться на первый этаж храма."
#define GOSSIP_CAMILLE1         "Мне нужен ветрокрыл для полета."
#define GOSSIP_CAMILLE2         "<Мне необходимо летное средство, для выполнения специального задания.>"
#define GOSSIP_CRIMSONWING      "<Дайте грифона для обследования острова Алькац.>"
#define GOSSIP_THRICESTAR1      "Как вы думаете я могу проехать на одном из этих летательных аппаратов?"
#define GOSSIP_THRICESTAR2      "Кара, мне нужно взлететь чтобы найти Бикси в Кельях Смерти."
#define GOSSIP_WILLIAMKEILAR1   "Отвези меня к Северной Башне."
#define GOSSIP_WILLIAMKEILAR2   "Отвези меня к Восточной башне."
#define GOSSIP_WILLIAMKEILAR3   "Отвези меня к Башне Королевской Стражи."

class npc_taxi : public CreatureScript
{
public:
    npc_taxi() : CreatureScript("npc_taxi") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        switch (creature->GetEntry())
        {
        case 17435: // Azuremyst Isle - Susurrus
            if (player->HasItemCount(23843, 1, true))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SUSURRUS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            break;
        case 20903: // Netherstorm - Protectorate Nether Drake
            if (player->GetQuestStatus(10438) == QUEST_STATUS_INCOMPLETE && player->HasItemCount(29778, 1))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_NETHER_DRAKE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            break;
        case 18725: // Old Hillsbrad Foothills - Brazen
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BRAZEN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            break;
        case 29154: // Stormwind City - Thargold Ironwing
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_IRONWING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            break;
        case 19409: // Hellfire Peninsula - Wing Commander Dabir'ee
            //Mission: The Murketh and Shaadraz Gateways
            if (player->GetQuestStatus(10146) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DABIREE1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);

            //Shatter Point
            if (!player->GetQuestRewardStatus(10340))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DABIREE2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            break;
        case 20235: // Hellfire Peninsula - Gryphoneer Windbellow
            //Mission: The Abyssal Shelf || Return to the Abyssal Shelf
            if (player->GetQuestStatus(10163) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(10346) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WINDBELLOW1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);

            //Go to the Front
            if (player->GetQuestStatus(10382) != QUEST_STATUS_NONE && !player->GetQuestRewardStatus(10382))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WINDBELLOW2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            break;
        case 19401: // Hellfire Peninsula - Wing Commander Brack
            //Mission: The Murketh and Shaadraz Gateways
            if (player->GetQuestStatus(10129) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BRACK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);

            //Mission: The Abyssal Shelf || Return to the Abyssal Shelf
            if (player->GetQuestStatus(10162) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(10347) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BRACK2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);

            //Spinebreaker Post
            if (player->GetQuestStatus(10242) == QUEST_STATUS_COMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BRACK3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            break;
        case 23413: // Blade's Edge Mountains - Skyguard Handler Irena
            if (player->GetReputationRank(1031) >= REP_HONORED)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_IRENA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            break;
        case 25059: // Isle of Quel'Danas - Ayren Cloudbreaker
            if (player->GetQuestStatus(11532) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(11533) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CLOUDBREAKER1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);

            if (player->GetQuestStatus(11542) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(11543) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CLOUDBREAKER2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
            break;
        case 25236: // Isle of Quel'Danas - Unrestrained Dragonhawk
            if (player->GetQuestStatus(11542) == QUEST_STATUS_COMPLETE || player->GetQuestStatus(11543) == QUEST_STATUS_COMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DRAGONHAWK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
            break;
        case 20162: // Netherstorm - Veronia
            //Behind Enemy Lines
            if (player->GetQuestStatus(10652) != QUEST_STATUS_REWARDED)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VERONIA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
            break;
        case 23415: // Terokkar Forest - Skyguard Handler Deesak
            if (player->GetReputationRank(1031) >= REP_HONORED)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_DEESAK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
            break;
        case 27575: // Dragonblight - Lord Afrasastrasz
            // middle -> ground
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_AFRASASTRASZ1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
            // middle -> top
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_AFRASASTRASZ2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
            break;
        case 26443: // Dragonblight - Tariolstrasz //need to check if quests are required before gossip available (12123, 12124)
            // ground -> top
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TARIOLSTRASZ1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
            // ground -> middle
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TARIOLSTRASZ2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
            break;
        case 26949: // Dragonblight - Torastrasza
            // top -> middle
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TORASTRASZA1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
            // top -> ground
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TORASTRASZA2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
            break;
        case 23816: // Howling Fjord - Bat Handler Camille
            if (!player->GetQuestRewardStatus(11229))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAMILLE1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
            if (player->GetQuestStatus(11170) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CAMILLE2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
            break;
        case 23704: // Dustwallow Marsh - Cassa Crimsonwing
            if (player->GetQuestStatus(11142) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CRIMSONWING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+25);
            break;
        case 26602:
            if (creature->isTaxi())
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TAXI, GOSSIP_THRICESTAR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);

            if (player->GetQuestStatus(11692) == QUEST_STATUS_COMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_THRICESTAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
            break;
        case 17209:
            player->SetTaxiCheater(true);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WILLIAMKEILAR1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WILLIAMKEILAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WILLIAMKEILAR3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
            break;
        }

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF:
            //spellId is correct, however it gives flight a somewhat funny effect //TaxiPath 506.
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 32474, true);
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(627);                  //TaxiPath 627 (possibly 627+628(152->153->154->155))
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            if (!player->HasItemCount(25853, 1))
                player->SEND_GOSSIP_MENU(9780, creature->GetGUID());
            else
            {
                player->CLOSE_GOSSIP_MENU();
                player->ActivateTaxiPathTo(534);              //TaxiPath 534
            }
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 53335, true);               //TaxiPath 1041 (Stormwind Harbor)
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 33768, true);               //TaxiPath 585 (Gateways Murket and Shaadraz)
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 35069, true);               //TaxiPath 612 (Taxi - Hellfire Peninsula - Expedition Point to Shatter Point)
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 33899, true);               //TaxiPath 589 (Aerial Assault Flight (Alliance))
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 35065, true);               //TaxiPath 607 (Taxi - Hellfire Peninsula - Shatter Point to Beach Head)
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 33659, true);               //TaxiPath 584 (Gateways Murket and Shaadraz)
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 33825, true);               //TaxiPath 587 (Aerial Assault Flight (Horde))
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 34578, true);               //TaxiPath 604 (Taxi - Reaver's Fall to Spinebreaker Ridge)
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 41278, true);               //TaxiPath 706
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 45071, true);               //TaxiPath 779
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 45113, true);               //TaxiPath 784
            break;
        case GOSSIP_ACTION_INFO_DEF + 14:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 45353, true);               //TaxiPath 788
            break;
        case GOSSIP_ACTION_INFO_DEF + 15:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 34905, true);               //TaxiPath 606
            break;
        case GOSSIP_ACTION_INFO_DEF + 16:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 41279, true);               //TaxiPath 705 (Taxi - Skettis to Skyguard Outpost)
            break;
        case GOSSIP_ACTION_INFO_DEF + 17:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(882);
            break;
        case GOSSIP_ACTION_INFO_DEF + 18:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(881);
            break;
        case GOSSIP_ACTION_INFO_DEF + 19:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(878);
            break;
        case GOSSIP_ACTION_INFO_DEF + 20:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(883);
            break;
        case GOSSIP_ACTION_INFO_DEF + 21:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(880);
            break;
        case GOSSIP_ACTION_INFO_DEF + 22:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(879);
            break;
        case GOSSIP_ACTION_INFO_DEF + 23:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 43074, true);               //TaxiPath 736
            break;
        case GOSSIP_ACTION_INFO_DEF + 24:
            player->CLOSE_GOSSIP_MENU();
            //player->ActivateTaxiPathTo(738);
            player->CastSpell(player, 43136, false);
            break;
        case GOSSIP_ACTION_INFO_DEF + 25:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 42295, true);
            break;
        case GOSSIP_ACTION_INFO_DEF + 26:
            player->GetSession()->SendTaxiMenu(creature);
            break;
        case GOSSIP_ACTION_INFO_DEF + 27:
            player->CLOSE_GOSSIP_MENU();
            player->CastSpell(player, 51446, false);
            break;
        case GOSSIP_ACTION_INFO_DEF + 28:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(494);
            break;
        case GOSSIP_ACTION_INFO_DEF + 29:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(495);
            break;
        case GOSSIP_ACTION_INFO_DEF + 30:
            player->CLOSE_GOSSIP_MENU();
            player->ActivateTaxiPathTo(496);
            break;
        }

        return true;
    }
};

void AddSC_npc_taxi()
{
    new npc_taxi;
}
