/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

/*######
## npc_agnetta_tyrsdottar
######*/

#define SAY_AGGRO                  -1571003
#define GOSSIP_AGNETTA             "Skip the warmup, sister... or are you too scared to face soemeone your own size?"

enum eAgnetta
{
    QUEST_ITS_THAT_YOUR_GOBLIN      = 12969,
    FACTION_HOSTILE_AT1             = 45
};

class npc_agnetta_tyrsdottar : public CreatureScript
{
public:
    npc_agnetta_tyrsdottar() : CreatureScript("npc_agnetta_tyrsdottar") { }

    struct npc_agnetta_tyrsdottarAI : public ScriptedAI
    {
        npc_agnetta_tyrsdottarAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            me->RestoreFaction();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_agnetta_tyrsdottarAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_ITS_THAT_YOUR_GOBLIN) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_AGNETTA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        player->SEND_GOSSIP_MENU(13691, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            DoScriptText(SAY_AGGRO, creature);
            player->CLOSE_GOSSIP_MENU();
            creature->setFaction(FACTION_HOSTILE_AT1);
            creature->AI()->AttackStart(player);
        }

        return true;
    }
};

/*######
## npc_frostborn_scout
######*/

#define GOSSIP_ITEM1    "Are you okay? I've come to take you back to Frosthold if you can stand."
#define GOSSIP_ITEM2    "I'm sorry that I didn't get here sooner. What happened?"
#define GOSSIP_ITEM3    "I'll go get some help. Hang in there."

enum eFrostbornScout
{
    QUEST_MISSING_SCOUTS  =  12864
};

class npc_frostborn_scout : public CreatureScript
{
public:
    npc_frostborn_scout() : CreatureScript("npc_frostborn_scout") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {

        if (player->GetQuestStatus(QUEST_MISSING_SCOUTS) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->PlayerTalkClass->SendGossipMenu(13611, creature->GetGUID());
        }

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->PlayerTalkClass->SendGossipMenu(13612, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            player->PlayerTalkClass->SendGossipMenu(13613, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            player->PlayerTalkClass->SendGossipMenu(13614, creature->GetGUID());
            player->AreaExploredOrEventHappens(QUEST_MISSING_SCOUTS);
            break;
        }

        return true;
    }
};

/*######
## npc_thorim
######*/

#define GOSSIP_HN "Thorim?"
#define GOSSIP_SN1 "Can you tell me what became of Sif?"
#define GOSSIP_SN2 "He did more than that, Thorim. He controls Ulduar now."
#define GOSSIP_SN3 "It needn't end this way."

enum eThorim
{
    QUEST_SIBLING_RIVALRY = 13064,
    NPC_THORIM = 29445,
    GOSSIP_TEXTID_THORIM1 = 13799,
    GOSSIP_TEXTID_THORIM2 = 13801,
    GOSSIP_TEXTID_THORIM3 = 13802,
    GOSSIP_TEXTID_THORIM4 = 13803
};

class npc_thorim : public CreatureScript
{
public:
    npc_thorim() : CreatureScript("npc_thorim") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_SIBLING_RIVALRY) == QUEST_STATUS_INCOMPLETE) {
            player->ADD_GOSSIP_ITEM(0, GOSSIP_HN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM1, creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(0, GOSSIP_SN1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM2, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(0, GOSSIP_SN2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM3, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                player->ADD_GOSSIP_ITEM(0, GOSSIP_SN3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM4, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                player->CLOSE_GOSSIP_MENU();
                player->CompleteQuest(QUEST_SIBLING_RIVALRY);
                break;
        }
        return true;
    }
};

/*######
## npc_victorious_challenger
######*/

#define GOSSIP_CHALLENGER            "Let's do this, sister."

enum eVictoriousChallenger
{
    QUEST_TAKING_ALL_CHALLENGERS    = 12971,
    QUEST_DEFENDING_YOUR_TITLE      = 13423,

    SPELL_SUNDER_ARMOR              = 11971,
    SPELL_REND_VC                   = 11977
};

class npc_victorious_challenger : public CreatureScript
{
public:
    npc_victorious_challenger() : CreatureScript("npc_victorious_challenger") { }

    struct npc_victorious_challengerAI : public ScriptedAI
    {
        npc_victorious_challengerAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 SunderArmorTimer;
        uint32 RendTimer;

        void Reset()
        {
            me->RestoreFaction();

            SunderArmorTimer = 10000;
            RendTimer        = 15000;
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (RendTimer < diff)
            {
                DoCast(me->getVictim(), SPELL_REND_VC, true);
                RendTimer = 15000;
            }else RendTimer -= diff;

            if (SunderArmorTimer < diff)
            {
                DoCast(me->getVictim(), SPELL_SUNDER_ARMOR, true);
                SunderArmorTimer = 10000;
            }else SunderArmorTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            me->RestoreFaction();
        }

    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_TAKING_ALL_CHALLENGERS) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_DEFENDING_YOUR_TITLE) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CHALLENGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->setFaction(14);
            creature->AI()->AttackStart(player);
        }

        return true;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_victorious_challengerAI(creature);
    }
};

/*######
## npc_loklira_crone
######*/

#define GOSSIP_LOKLIRACRONE     "Tell me about this proposal"
#define GOSSIP_LOKLIRACRONE1    "What happened then?"
#define GOSSIP_LOKLIRACRONE2    "You want me to take part in the Hyldsmeet to end the war?"
#define GOSSIP_LOKLIRACRONE3    "Very well. I'll take part in this competition."

enum eLokliraCrone
{
    QUEST_HYLDSMEET     = 12970,

    GOSSIP_TEXTID_LOK1  = 13778,
    GOSSIP_TEXTID_LOK2  = 13779,
    GOSSIP_TEXTID_LOK3  = 13780
};

class npc_loklira_crone : public CreatureScript
{
public:
    npc_loklira_crone() : CreatureScript("npc_loklira_crone") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_HYLDSMEET) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOKLIRACRONE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOKLIRACRONE1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOK1, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOKLIRACRONE2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOK2, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOKLIRACRONE3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOK3, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                player->CLOSE_GOSSIP_MENU();
                player->CompleteQuest(QUEST_HYLDSMEET);
                break;
        }
        return true;
    }
};

/////////////////////
///npc_injured_goblin
/////////////////////

enum eInjuredGoblin
{
    QUEST_BITTER_DEPARTURE     = 12832,
    SAY_QUEST_ACCEPT           =  -1800042,
    SAY_END_WP_REACHED         =  -1800043
};

#define GOSSIP_ITEM_1       "I am ready, lets get you out of here"

class npc_injured_goblin : public CreatureScript
{
public:
    npc_injured_goblin() : CreatureScript("npc_injured_goblin") { }

    struct npc_injured_goblinAI : public npc_escortAI
    {
        npc_injured_goblinAI(Creature* creature) : npc_escortAI(creature) { }

        void WaypointReached(uint32 waypointId)
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
                case 26:
                    DoScriptText(SAY_END_WP_REACHED, me, player);
                    break;
                case 27:
                    player->GroupEventHappens(QUEST_BITTER_DEPARTURE, me);
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/) {}

        void Reset() {}

        void JustDied(Unit* /*killer*/)
        {
            Player* player = GetPlayerForEscort();
            if (HasEscortState(STATE_ESCORT_ESCORTING) && player)
                player->FailQuest(QUEST_BITTER_DEPARTURE);
        }

       void UpdateAI(const uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_injured_goblinAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_BITTER_DEPARTURE) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(0, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->PlayerTalkClass->SendGossipMenu(9999999, creature->GetGUID());
        }
        else
            player->SEND_GOSSIP_MENU(999999, creature->GetGUID());
        return true;
    }

    bool OnQuestAccept(Player* /*player*/, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_BITTER_DEPARTURE)
            DoScriptText(SAY_QUEST_ACCEPT, creature);

        return false;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        npc_escortAI* pEscortAI = CAST_AI(npc_injured_goblin::npc_injured_goblinAI, creature->AI());

        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            pEscortAI->Start(true, true, player->GetGUID());
            creature->setFaction(113);
        }
        return true;
    }
};

/*######
## npc_roxi_ramrocket
######*/

#define SPELL_MECHANO_HOG           60866
#define SPELL_MEKGINEERS_CHOPPER    60867

class npc_roxi_ramrocket : public CreatureScript
{
public:
    npc_roxi_ramrocket() : CreatureScript("npc_roxi_ramrocket") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        //Quest Menu
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        //Trainer Menu
        if ( creature->isTrainer() )
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

        //Vendor Menu
        if ( creature->isVendor() )
            if (player->HasSpell(SPELL_MECHANO_HOG) || player->HasSpell(SPELL_MEKGINEERS_CHOPPER))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
        case GOSSIP_ACTION_TRAIN:
            player->GetSession()->SendTrainerList(creature->GetGUID());
            break;
        case GOSSIP_ACTION_TRADE:
            player->GetSession()->SendListInventory(creature->GetGUID());
            break;
        }
        return true;
    }
};

/*######
## npc_quest_12851
######*/

enum eQuest_12851
{
    SPELL_ABLAZE          = 54683
};

class npc_quest_12851 : public CreatureScript
{
public:
    npc_quest_12851() : CreatureScript("npc_quest_12851") {}

    struct npc_quest_12851AI : public ScriptedAI
    {
        npc_quest_12851AI(Creature* pCreature) : ScriptedAI(pCreature) {}

        bool bBurned;
        uint32 uiDespawnTimer;

        void Reset()
        {
            bBurned = false;
            uiDespawnTimer = 5000;
            me->SetCorpseDelay(5);
        }

        void SpellHit(Unit * /*caster*/, const SpellInfo* spell)
        {
            if (spell->Id == SPELL_ABLAZE)
                bBurned = true;
        }

        void UpdateAI(const uint32 diff)
        {
            // keep this until icefang uses waypoint movement
            if (bBurned && me->isAlive())
                if (uiDespawnTimer < diff)
                {
                    me->Kill(me);
                }else uiDespawnTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_quest_12851AI(creature);
    }
};


/*######
## Quest: Cold Hearted (12856)
######*/

enum eColdHearted
{
    SPELL_KILL_CREDIT_PRISONER          = 55144,
    SPELL_KILL_CREDIT_DRAKE             = 55143,
    SPELL_SUMMON_LIBERATED              = 55073
};

const Position FreedDrakeWaypoints[6] =
{
    {7250.15f, -2327.22f, 869.03f, 0.0f},
    {7118.79f, -2122.05f, 841.32f, 0.0f},
    {7052.86f, -1905.99f, 888.59f, 0.0f},
    {7038.24f, -1822.77f, 857.94f, 0.0f},
    {7044.09f, -1792.25f, 841.69f, 0.0f},
    {7071.20f, -1780.73f, 822.42f, 0.0f}
};

class npc_freed_protodrake : public CreatureScript
{
public:
    npc_freed_protodrake() : CreatureScript("npc_freed_protodrake") { }

    struct npc_freed_protodrakeAI : public ScriptedAI
    {
        npc_freed_protodrakeAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        uint8 count;
        bool wp_reached;
        bool movementStarted;

        void Reset()
        {
            count = 0;
            wp_reached = false;
            movementStarted = false;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE || id != count)
                return;

            if (id < 5)
            {
                ++count;
                wp_reached = true;
            }
            else // reached village, give credits
            {
                Unit* player = me->GetVehicleKit()->GetPassenger(0); // get player
                if (player && player->GetTypeId() == TYPEID_PLAYER)
                {
                    for (uint8 i = 1; i < 4; ++i) // try to get prisoners
                        if (Unit* prisoner = me->GetVehicleKit()->GetPassenger(i))
                        {
                            if (prisoner->GetTypeId() != TYPEID_UNIT)
                                return;

                            DoCast(player, SPELL_KILL_CREDIT_PRISONER, true);
                            //DoCast(player, SPELL_SUMMON_LIBERATED, true);
                            prisoner->ExitVehicle();
                            prisoner->ToCreature()->AI()->DoAction(0);
                        }

                    DoCast(player, SPELL_KILL_CREDIT_DRAKE, true);
                    player->ExitVehicle();
                }
            }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!me->isCharmed() && !movementStarted)
            {
                me->SetSpeed(MOVE_FLIGHT, 5.0f);
                movementStarted = true;
                wp_reached = true;
            }

            if (wp_reached)
            {
                wp_reached = false;
                me->GetMotionMaster()->MovePoint(count, FreedDrakeWaypoints[count]);
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_freed_protodrakeAI(pCreature);
    }
};

/*######
## npc_brunnhildar_prisoner
######*/

enum eBrunnhildarPrisoner
{
    SPELL_ICE_BLOCK                   = 54894,
    SPELL_ICE_SHARD                   = 55046,
    SPELL_ICE_SHARD_IMPACT            = 55047
};

class npc_brunnhildar_prisoner : public CreatureScript
{
public:
    npc_brunnhildar_prisoner() : CreatureScript("npc_brunnhildar_prisoner") {}

    struct npc_brunnhildar_prisonerAI : public ScriptedAI
    {
        npc_brunnhildar_prisonerAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 uiCheckTimer;

        void Reset()
        {
            uiCheckTimer = 10*IN_MILLISECONDS;
            DoCast(me, SPELL_ICE_BLOCK, true);
        }

        void DoAction(const int32 /*param*/)
        {
            me->Kill(me);
            me->Respawn();
        }

        void SpellHit(Unit* caster, const SpellInfo* spell) 
        {
            if (spell->Id == SPELL_ICE_SHARD)
            {
                DoCast(me, SPELL_ICE_SHARD_IMPACT, true);

                if (caster->IsVehicle())
                {
                    uint8 seat = caster->GetVehicleKit()->GetNextEmptySeat(0, true);
                    if (seat <= 0)
                        return;

                    me->EnterVehicle(caster);
                    me->RemoveAurasDueToSpell(SPELL_ICE_BLOCK);
                    caster->SetSpeed(MOVE_FLIGHT, 3.0f);
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (uiCheckTimer < diff)
            {
                if (!me->HasUnitState(UNIT_STATE_ONVEHICLE))
                {
                    // return home
                    if (me->GetDistance(me->GetHomePosition()) > 30.0f)
                        DoAction(0);
                }
                else
                {
                    if (me->GetPositionY() > -2595.0f)
                    {
                        // remove player control
                        if (Unit* base = me->GetVehicleBase())
                            if (base->isCharmed())
                                base->RemoveCharmedBy(base->GetCharmer());
                    }
                }

                uiCheckTimer = 10*IN_MILLISECONDS;
            }else uiCheckTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_brunnhildar_prisonerAI(creature);
    }
};

class npc_hyldsmeet_protodrake : public CreatureScript
{
    enum NPCs
    {
        NPC_HYLDSMEET_DRAKERIDER = 29694
    };

    public:
        npc_hyldsmeet_protodrake() : CreatureScript("npc_hyldsmeet_protodrake") { }

        class npc_hyldsmeet_protodrakeAI : public CreatureAI
        {
            public:
                npc_hyldsmeet_protodrakeAI(Creature* creature) : CreatureAI(creature), _accessoryRespawnTimer(0), _vehicleKit(creature->GetVehicleKit()) {}

                void PassengerBoarded(Unit* who, int8 /*seat*/, bool apply)
                {
                    if (apply)
                        return;

                    if (who->GetEntry() == NPC_HYLDSMEET_DRAKERIDER)
                        _accessoryRespawnTimer = 5 * MINUTE * IN_MILLISECONDS;
                }

                void UpdateAI(uint32 const diff)
                {
                    //! We need to manually reinstall accessories because the vehicle itself is friendly to players,
                    //! so EnterEvadeMode is never triggered. The accessory on the other hand is hostile and killable.
                    if (_accessoryRespawnTimer && _accessoryRespawnTimer <= diff && _vehicleKit)
                    {
                        _vehicleKit->InstallAllAccessories(true);
                        _accessoryRespawnTimer = 0;
                    }
                    else
                        _accessoryRespawnTimer -= diff;
                }
            
            private:
                uint32 _accessoryRespawnTimer;
                Vehicle* _vehicleKit;
        };
        
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_hyldsmeet_protodrakeAI (creature);
        }
};

/*######
## Quest: Forging a Head (12985)
######*/

enum eDeadIrongiant
{
    ENTRY_AMBUSHER              = 30208,
    SPELL_SALVAGE_CORPSE        = 56227,
    SPELL_CREATE_EYES           = 56230
};

class npc_dead_irongiant : public CreatureScript
{
public:
    npc_dead_irongiant() : CreatureScript("npc_dead_irongiant") {}

    struct npc_dead_irongiantAI : public ScriptedAI
    {
        npc_dead_irongiantAI(Creature *pCreature) : ScriptedAI(pCreature) {}

        void SpellHit(Unit *caster, const SpellEntry *spell) 
        {
            if (spell->Id == SPELL_SALVAGE_CORPSE)
            {
                if (!urand(0,2))
                {
                    for (uint8 i = 0; i < 3; ++i)
                        if (Creature *temp = me->SummonCreature(ENTRY_AMBUSHER, 0, 0, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60*IN_MILLISECONDS))
                            temp->AI()->AttackStart(caster);
                }
                else
                {
                    me->CastSpell(caster, SPELL_CREATE_EYES, true);
                }

                me->DespawnOrUnsummon(500);
            }
        }
    };

    CreatureAI* GetAI(Creature *creature) const
    {
        return new npc_dead_irongiantAI(creature);
    }
};

/*####################
# spell_contact_brann
#####################*/

enum ContactBrannData
{
    SPELL_CONTACT_BRANN = 61122,
    NPC_BRANN = 29579,
    ZONE_STORM_PEAKS = 67
};

class spell_contact_brann : public SpellScriptLoader
{
public:
    spell_contact_brann() : SpellScriptLoader("spell_contact_brann") {}

    class spell_contact_brann_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_contact_brann_SpellScript)

        bool Validate(SpellInfo const* /*spell*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_CONTACT_BRANN))
                return false;
            return true;
        }

        void HandleScriptEffect(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            if (Unit* caster = GetCaster())
               if (caster->ToPlayer())
                   if (caster->ToPlayer()->GetZoneId() == ZONE_STORM_PEAKS)
                       caster->SummonCreature(NPC_BRANN, caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 120000);
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_contact_brann_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_contact_brann_SpellScript();
    }
};

/*######
## npc_archivist_mechaton
######*/

enum eMechaton
{
    NPC_ARCHIVIST_MECHATON  = 29775,
    SPELL_ARCHIVISTS_SCAN   = 55224,
    SPELL_CHARGED_DISK      = 55197,
    GO_FLOOR_GLYPH          = 191762,
    GO_ENERGY_COLUMN        = 191763,
    SAY_1                   = 1,
    SAY_2                   = 2,
    SAY_3                   = 3,
    SAY_4                   = 4,
    EMOTE_1                 = 5,
    SAY_5                   = 6,
    SAY_6                   = 7,
    SAY_7                   = 8
};

class npc_archivist_mechaton : public CreatureScript
{
public:
    npc_archivist_mechaton() : CreatureScript("npc_archivist_mechaton") {}

    struct npc_archivist_mechatonAI : public ScriptedAI
    {
        npc_archivist_mechatonAI(Creature* pCreature) : ScriptedAI(pCreature) 
        {
            if(me->isSummon())
            {
                me->SummonGameObject(GO_FLOOR_GLYPH, 7991.89f, -827.66f, 968.156f, -2.33874f, 0, 0, 0, 0, 27);
                me->SummonGameObject(GO_ENERGY_COLUMN, 7991.8f, -827.639f, 968.16f, 0.90757f, 0, 0, 0, 0, 27);
            }

            FirstTime = true;
        }

        uint8   saycount;
        uint32  saytimer;
        bool    FirstTime;

        void Reset()
        {
            saytimer = 0;
        
            if(FirstTime)
                saycount = 1;
            else
            {   
                saycount = 0;
                me->DespawnOrUnsummon();
            }
        }
        
        void DoNextText(uint32 timer)
        {
            saytimer = timer;
            ++saycount;
        }

        void UpdateAI(uint32 const diff)
        {
            if(saytimer <= diff)    
            {            
                Unit* pSummoner = me->ToTempSummon()->GetSummoner();
                
                switch(saycount)
                {
                    case 1:
                        Talk(SAY_1);
                        DoNextText(4000);
                        break;
                    case 2:
                        Talk(SAY_2);
                        DoNextText(3000);
                        break;
                    case 3:
                        Talk(SAY_3);
                        DoNextText(4000);
                        break;
                    case 4:
                        Talk(SAY_4);
                        me->CastSpell(pSummoner, SPELL_ARCHIVISTS_SCAN, true);
                        DoNextText(1100);
                        break;
                    case 5:
                        Talk(EMOTE_1);
                        DoNextText(8000);
                        break;
                    case 6:
                        Talk(SAY_5);
                        me->CombatStop();
                        DoNextText(4000);
                        break;
                    case 7:
                        Talk(SAY_6);
                        DoNextText(5000);
                        break;
                    case 8:
                        Talk(SAY_7);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->AI()->AttackStart(pSummoner);
                        DoNextText(0);
                        FirstTime = false;
                        break;
                }
            }else saytimer -= diff;

            DoMeleeAttackIfReady();

            if (!UpdateVictim())
                return;
        }  
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_archivist_mechatonAI(pCreature);
    }
};

void AddSC_storm_peaks()
{
    new npc_agnetta_tyrsdottar();
    new npc_frostborn_scout();
    new npc_thorim();
    new npc_victorious_challenger();
    new npc_loklira_crone();
    new npc_injured_goblin();
    new npc_roxi_ramrocket();
    new npc_quest_12851();
    new npc_freed_protodrake();
    new npc_brunnhildar_prisoner();
    new npc_hyldsmeet_protodrake();
    new npc_dead_irongiant();
    new spell_contact_brann();
    new npc_archivist_mechaton();
}
