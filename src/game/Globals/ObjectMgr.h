/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: http://github.com/azerothcore/azerothcore-wotlk/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef _OBJECTMGR_H
#define _OBJECTMGR_H

#include "Log.h"
#include "Object.h"
#include "Bag.h"
#include "Creature.h"
#include "DynamicObject.h"
#include "GameObject.h"
#include "TemporarySummon.h"
#include "Corpse.h"
#include "QuestDef.h"
#include "ItemPrototype.h"
#include "NPCHandler.h"
#include "DatabaseEnv.h"
#include "Mail.h"
#include "Map.h"
#include "ObjectAccessor.h"
#include "ObjectDefines.h"
#include <ace/Singleton.h>
#include "VehicleDefines.h"
#include <string>
#include <map>
#include <limits>
#include "ConditionMgr.h"
#include <functional>

class Item;
struct AccessRequirement;
struct PlayerClassInfo;
struct PlayerClassLevelInfo;
struct PlayerInfo;
struct PlayerLevelInfo;

// GCC have alternative #pragma pack(N) syntax and old gcc version not support pack(push, N), also any gcc version not support it at some platform
#if defined(__GNUC__)
#pragma pack(1)
#else
#pragma pack(push, 1)
#endif

struct PageText
{
    std::string Text;
    uint16 NextPage;
};

/// Key for storing temp summon data in TempSummonDataContainer
struct TempSummonGroupKey
{
    TempSummonGroupKey(uint32 summonerEntry, SummonerType summonerType, uint8 group)
        : _summonerEntry(summonerEntry), _summonerType(summonerType), _summonGroup(group)
    {
    }

    bool operator<(TempSummonGroupKey const& rhs) const
    {
        // memcmp is only reliable if struct doesn't have any padding (packed)
        return memcmp(this, &rhs, sizeof(TempSummonGroupKey)) < 0;
    }

private:
    uint32 _summonerEntry;      ///< Summoner's entry
    SummonerType _summonerType; ///< Summoner's type, see SummonerType for available types
    uint8 _summonGroup;         ///< Summon's group id
};

// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined(__GNUC__)
#pragma pack()
#else
#pragma pack(pop)
#endif

// DB scripting commands
enum ScriptCommands
{
    SCRIPT_COMMAND_TALK                  = 0,                // source/target = Creature, target = any, datalong = talk type (0=say, 1=whisper, 2=yell, 3=emote text, 4=boss emote text), datalong2 & 1 = player talk (instead of creature), dataint = string_id
    SCRIPT_COMMAND_EMOTE                 = 1,                // source/target = Creature, datalong = emote id, datalong2 = 0: set emote state; > 0: play emote state
    SCRIPT_COMMAND_FIELD_SET             = 2,                // source/target = Creature, datalong = field id, datalog2 = value
    SCRIPT_COMMAND_MOVE_TO               = 3,                // source/target = Creature, datalong2 = time to reach, x/y/z = destination
    SCRIPT_COMMAND_FLAG_SET              = 4,                // source/target = Creature, datalong = field id, datalog2 = bitmask
    SCRIPT_COMMAND_FLAG_REMOVE           = 5,                // source/target = Creature, datalong = field id, datalog2 = bitmask
    SCRIPT_COMMAND_TELEPORT_TO           = 6,                // source/target = Creature/Player (see datalong2), datalong = map_id, datalong2 = 0: Player; 1: Creature, x/y/z = destination, o = orientation
    SCRIPT_COMMAND_QUEST_EXPLORED        = 7,                // target/source = Player, target/source = GO/Creature, datalong = quest id, datalong2 = distance or 0
    SCRIPT_COMMAND_KILL_CREDIT           = 8,                // target/source = Player, datalong = creature entry, datalong2 = 0: personal credit, 1: group credit
    SCRIPT_COMMAND_RESPAWN_GAMEOBJECT    = 9,                // source = WorldObject (summoner), datalong = GO guid, datalong2 = despawn delay
    SCRIPT_COMMAND_TEMP_SUMMON_CREATURE  = 10,               // source = WorldObject (summoner), datalong = creature entry, datalong2 = despawn delay, x/y/z = summon position, o = orientation
    SCRIPT_COMMAND_OPEN_DOOR             = 11,               // source = Unit, datalong = GO guid, datalong2 = reset delay (min 15)
    SCRIPT_COMMAND_CLOSE_DOOR            = 12,               // source = Unit, datalong = GO guid, datalong2 = reset delay (min 15)
    SCRIPT_COMMAND_ACTIVATE_OBJECT       = 13,               // source = Unit, target = GO
    SCRIPT_COMMAND_REMOVE_AURA           = 14,               // source (datalong2 != 0) or target (datalong2 == 0) = Unit, datalong = spell id
    SCRIPT_COMMAND_CAST_SPELL            = 15,               // source and/or target = Unit, datalong2 = cast direction (0: s->t 1: s->s 2: t->t 3: t->s 4: s->creature with dataint entry), dataint & 1 = triggered flag
    SCRIPT_COMMAND_PLAY_SOUND            = 16,               // source = WorldObject, target = none/Player, datalong = sound id, datalong2 (bitmask: 0/1=anyone/player, 0/2=without/with distance dependency, so 1|2 = 3 is target with distance dependency)
    SCRIPT_COMMAND_CREATE_ITEM           = 17,               // target/source = Player, datalong = item entry, datalong2 = amount
    SCRIPT_COMMAND_DESPAWN_SELF          = 18,               // target/source = Creature, datalong = despawn delay

    SCRIPT_COMMAND_LOAD_PATH             = 20,               // source = Unit, datalong = path id, datalong2 = is repeatable
    SCRIPT_COMMAND_CALLSCRIPT_TO_UNIT    = 21,               // source = WorldObject (if present used as a search center), datalong = script id, datalong2 = unit lowguid, dataint = script table to use (see ScriptsType)
    SCRIPT_COMMAND_KILL                  = 22,               // source/target = Creature, dataint = remove corpse attribute

    // AzerothCore only
    SCRIPT_COMMAND_ORIENTATION           = 30,               // source = Unit, target (datalong > 0) = Unit, datalong = > 0 turn source to face target, o = orientation
    SCRIPT_COMMAND_EQUIP                 = 31,               // soucre = Creature, datalong = equipment id
    SCRIPT_COMMAND_MODEL                 = 32,               // source = Creature, datalong = model id
    SCRIPT_COMMAND_CLOSE_GOSSIP          = 33,               // source = Player
    SCRIPT_COMMAND_PLAYMOVIE             = 34                // source = Player, datalong = movie id
};

// Benchmarked: Faster than UNORDERED_MAP (insert/find)
typedef std::map<uint32, PageText> PageTextContainer;

// Benchmarked: Faster than std::map (insert/find)
typedef UNORDERED_MAP<uint16, InstanceTemplate> InstanceTemplateContainer;

struct GameTele
{
    float  position_x;
    float  position_y;
    float  position_z;
    float  orientation;
    uint32 mapId;
    std::string name;
    std::wstring wnameLow;
};

/*WQCORE全局数据类型定义开始*/
struct xx_creature_tele //传送表
{
	uint32 menuid;
	uint32 parentid;
	std::string title;
	float tele_x;
	float tele_y;
	float tele_z;
	uint32 tele_map;
	uint32 usetype;
	int32 factionid;
};
typedef std::map<uint32, xx_creature_tele> xxCreatureTeleMap;

struct xx_item_tele //传送表
{
	uint32 menuid;
	uint32 parentid;
	std::string title;
	float tele_x;
	float tele_y;
	float tele_z;
	uint32 tele_map;
	uint32 usetype;
	int32 usev1;
	int32 usev2;
	uint32 needtype;
	int32 needv1;
	int32 needv2;
	int32 factionid;
	uint32 vip;
	int32 v1;
	int32 v2;
};
typedef std::map<uint32, xx_item_tele> xxItemTeleMap;

struct xx_skill //传送表
{
	uint32 skillid;
	uint32 aura1;
	uint32 aura2;
	uint32 aura3;
	uint32 aura4;
	uint32 aura5;
	uint32 aura6;
	uint32 aura7;
	uint32 aura8;
	uint32 aura9;
};
typedef std::map<uint32, xx_skill> xxSkillMap;

// 升级宝石
struct xx_itemup
{
	uint32 ItemID;
	uint32 RewItem;
	uint32 JFCost;
	uint32 ReqItem1;
	uint32 ReqItemBd1;
	uint32 ReqItem2;
	uint32 ReqItemBd2;
	uint32 ReqItem3;
	uint32 ReqItemBd3;
	uint32 ReqItem4;
	uint32 ReqItemBd4;
	uint32 ReqItem5;
	uint32 ReqItemBd5;
	uint32 ReqCount1;
	uint32 ReqCount2;
	uint32 ReqCount3;
	uint32 ReqCount4;
	uint32 ReqCount5;
	uint32 upLevel;
	uint32 JFRew;
	uint32 Pro;
	uint32 Destory;
	uint32 VipLevel;
	uint32 FromId;
	uint32 PvpLevel;
	uint32 PveLevel;
	uint32 JbCount;
};
typedef std::map<uint64, xx_itemup> xxItemupMap;

// 百团战场
struct xx_battle
{
	uint32 Entry;
	uint32 winitem;
	uint32 wincount;
	uint32 winitem1;
	uint32 wincount1;
	uint32 winitem2;
	uint32 wincount2;
	uint32 winitem3;
	uint32 wincount3;
	uint32 loseitem;
	uint32 losecount;
	uint32 loseitem1;
	uint32 losecount1;
	uint32 loseitem2;
	uint32 losecount2;
	uint32 loseitem3;
	uint32 losecount3;
	uint32 killitem;
	uint32 killcount;
	uint32 killitem1;
	uint32 killcount1;
	uint32 killitem2;
	uint32 killcount2;
	uint32 killitem3;
	uint32 killcount3;
	uint32 maxhealth;

};
typedef std::map<uint32, xx_battle> xxBattleMap;

struct xx_pvprank
{
	uint32 pvp_level;
	uint32 lmTitleId;
	uint32 blTitleId;
	uint32 lmreq_ItemId1;
	uint32 lmreq_ItemId2;
	uint32 lmreq_ItemCount1;
	uint32 lmreq_ItemCount2;
	uint32 blreq_ItemId1;
	uint32 blreq_ItemId2;
	uint32 blreq_ItemCount1;
	uint32 blreq_ItemCount2;
	uint32 lmrew_ItemId1;
	uint32 lmrew_ItemCount1;
	uint32 blrew_ItemId1;
	uint32 blrew_ItemCount1;
	uint32 lmAura;
	uint32 blAura;
	uint32 add_talent;
	uint32 add_pvp;
};
typedef std::map<uint32, xx_pvprank> xxPvpRankMap;

struct xx_raid
{
	uint32 id;
	uint32 lootid1;
	uint32 lootid2;
	uint32 lootid3;
	uint32 lootid4;
	uint32 lootid5;
	uint32 lootid6;
	uint32 lootid7;
	uint32 lootid8;
	uint32 lootid9;
	uint32 lootid10;
};
typedef std::map<uint32, xx_raid> xxRaidMap;

struct xx_raidbox
{
	uint32 id;
	uint32 lootid1;
	uint32 lootid2;
	uint32 lootid3;
	uint32 lootid4;
	uint32 lootid5;
	uint32 lootid6;
	uint32 lootid7;
	uint32 lootid8;
	uint32 lootid9;
	uint32 lootid10;
};
typedef std::map<uint32, xx_raidbox> xxRaidBoxMap;

struct xx_suoyao
{
	uint32 level;
	uint32 bossid;
	uint32 npcid;

};
typedef std::map<uint32, xx_suoyao> xxSuoyaoMap;

struct xx_tongtian
{
	uint32 level;
	uint32 bossid;

};
typedef std::map<uint32, xx_tongtian> xxTongtianMap;

struct xx_suo
{
	uint32 npcid;
	uint32 minjf;
	uint32 maxjf;

};
typedef std::map<uint32, xx_suo> xxSuoMap;

struct xx_huoli
{
	uint32 npcid;
	uint32 itemid;
	uint32 minitem;
	uint32 maxitem;
	uint32 minmoney;
	uint32 maxmoney;

};
typedef std::map<uint32, xx_huoli> xxHuoliMap;

struct xx_tong
{
	uint32 npcid;
	uint32 minjf;
	uint32 maxjf;

};
typedef std::map<uint32, xx_tong> xxTongMap;

struct xx_fuyin
{
	uint32 level;
	uint32 reqitem1;
	uint32 reqitem2;
	uint32 reqitem3;
	uint32 reqitemcount1;
	uint32 reqitemcount2;
	uint32 reqitemcount3;
	uint32 shangxian;
};
typedef std::map<uint32, xx_fuyin> xxfuyin;

struct xx_yuyi
{
	uint32 level;
	uint32 reqitem1;
	uint32 reqitemcount1;
	uint32 jb;
	uint32 shangxian;
};
typedef std::map<uint32, xx_yuyi> xxyuyi;

struct xx_jntp
{
	uint32 level;
	uint32 reqitem1;
	uint32 reqitem2;
	uint32 reqitemcount1;
	uint32 reqitemcount2;
	uint32 jb;
	uint32 shangxian;
};
typedef std::map<uint32, xx_jntp> xxjntp;

struct xx_jnjx
{
	uint32 level;
	uint32 reqitem1;
	uint32 reqitem2;
	uint32 reqitemcount1;
	uint32 reqitemcount2;
	uint32 jb;
	uint32 shangxian;
};
typedef std::map<uint32, xx_jnjx> xxjnjx;

struct xx_jnpy
{
	uint32 level;
	uint32 reqitem1;
	uint32 reqitem2;
	uint32 reqitemcount1;
	uint32 reqitemcount2;
	uint32 jb;
	uint32 shangxian;
};
typedef std::map<uint32, xx_jnpy> xxjnpy;

struct xx_cjjf
{
	uint32 id;
	uint32 rewitem;
	uint32 rewitemcount;
	uint32 gonggao;

};
typedef std::map<uint32, xx_cjjf> xxcjjf;

struct xx_cjzjf
{
	uint32 id;
	uint32 rewitem;
	uint32 gonggao;

};
typedef std::map<uint32, xx_cjzjf> xxcjzjf;

struct xx_cjzzjf
{
	uint32 id;
	uint32 rewitem;
	uint32 gonggao;

};
typedef std::map<uint32, xx_cjzzjf> xxcjzzjf;

struct xx_itembuff
{
	uint32 buffID;
};
typedef std::map<uint64, xx_itembuff> xxItembuffMap;

// VIP系统
struct xx_vip_system
{
	uint32		VipLevel;
	std::string Title;
	std::string SayColor;
	uint32		add_talent;
	uint32		rate_drop_pro;
	uint32		rate_upgrade_pro;
	uint32		add_online_point;
	std::string LoginAnnounce;
	uint32		req_jf;
	uint32		ReqardItemId;
	uint32		ReqardItemCount;
	uint32		RewardItemId;
	uint32		RewardItemCount;
	uint32		Aura;
	uint32		addliliang;
	uint32		addminjie;
	uint32		addnaili;
	uint32		addzhili;
	uint32		addjingshen;
	uint32		addjisu;
	uint32		addjingtong;
	uint32		addrenxing;
	uint32		tongtianadd;
	uint32		startlevel;
	uint32		dkstartlevel;
	float		quanshuxing;
	uint32		add_online_item;
	std::string SpellTitle;
};
typedef std::map<uint32, xx_vip_system> xxVipSystemMap;

struct xx_vip_systemmr
{
	uint32		VipLevel;
	uint32		RewardItemId1;
	uint32		RewardItemId2;
	uint32		RewardItemId3;
	uint32		RewardItemId4;
	uint32		RewardItemId5;
	uint32		RewardItemCount1;
	uint32		RewardItemCount2;
	uint32		RewardItemCount3;
	uint32		RewardItemCount4;
	uint32		RewardItemCount5;

};
typedef std::map<uint32, xx_vip_systemmr> xxVipSystemMrMap;

struct xx_itemb
{
	uint32 ItembID;
};
typedef std::map<uint64, xx_itemb> xxItembMap;

struct xx_npc
{
	uint32 id;
	uint32 npcID;
};
typedef std::map<uint64, xx_npc> xxnpcMap;

struct xx_item
{
	uint32 level;
	uint32 ItemID;
};
typedef std::map<uint64, xx_item> xxItemMap;

struct xx_itemicc
{
	uint32 level;
	uint32 ItemID;
};
typedef std::map<uint64, xx_itemicc> xxItemiccMap;

struct xx_itemcj
{
	uint32 ItemID;
	uint32 RewItem;
	uint32 RewItemmin;
	uint32 RewItemmax;
	uint32 FromId;
};
typedef std::map<uint64, xx_itemcj> xxItemcjMap;

struct xx_itemzh
{
	uint32 ItemID;
	uint32 RewItem;
	uint32 RewItemmin;
	uint32 Jb;
	uint32 FromId;
};
typedef std::map<uint64, xx_itemzh> xxItemzhMap;

typedef UNORDERED_MAP<uint32, GameTele > GameTeleContainer;

enum ScriptsType
{
    SCRIPTS_FIRST = 1,

    SCRIPTS_SPELL = SCRIPTS_FIRST,
    SCRIPTS_EVENT,
    SCRIPTS_WAYPOINT,

    SCRIPTS_LAST
};

enum eScriptFlags
{
    // Talk Flags
    SF_TALK_USE_PLAYER          = 0x1,

    // Emote flags
    SF_EMOTE_USE_STATE          = 0x1,

    // TeleportTo flags
    SF_TELEPORT_USE_CREATURE    = 0x1,

    // KillCredit flags
    SF_KILLCREDIT_REWARD_GROUP  = 0x1,

    // RemoveAura flags
    SF_REMOVEAURA_REVERSE       = 0x1,

    // CastSpell flags
    SF_CASTSPELL_SOURCE_TO_TARGET = 0,
    SF_CASTSPELL_SOURCE_TO_SOURCE = 1,
    SF_CASTSPELL_TARGET_TO_TARGET = 2,
    SF_CASTSPELL_TARGET_TO_SOURCE = 3,
    SF_CASTSPELL_SEARCH_CREATURE  = 4,
    SF_CASTSPELL_TRIGGERED      = 0x1,

    // PlaySound flags
    SF_PLAYSOUND_TARGET_PLAYER  = 0x1,
    SF_PLAYSOUND_DISTANCE_SOUND = 0x2,

    // Orientation flags
    SF_ORIENTATION_FACE_TARGET  = 0x1,
};

struct ScriptInfo
{
    ScriptsType type;
    uint32 id;
    uint32 delay;
    ScriptCommands command;

    union
    {
        struct
        {
            uint32 nData[3];
            float  fData[4];
        } Raw;

        struct                      // SCRIPT_COMMAND_TALK (0)
        {
            uint32 ChatType;        // datalong
            uint32 Flags;           // datalong2
            int32  TextID;          // dataint
        } Talk;

        struct                      // SCRIPT_COMMAND_EMOTE (1)
        {
            uint32 EmoteID;         // datalong
            uint32 Flags;           // datalong2
        } Emote;

        struct                      // SCRIPT_COMMAND_FIELD_SET (2)
        {
            uint32 FieldID;         // datalong
            uint32 FieldValue;      // datalong2
        } FieldSet;

        struct                      // SCRIPT_COMMAND_MOVE_TO (3)
        {
            uint32 Unused1;         // datalong
            uint32 TravelTime;      // datalong2
            int32  Unused2;         // dataint

            float DestX;
            float DestY;
            float DestZ;
        } MoveTo;

        struct                      // SCRIPT_COMMAND_FLAG_SET (4)
                                    // SCRIPT_COMMAND_FLAG_REMOVE (5)
        {
            uint32 FieldID;         // datalong
            uint32 FieldValue;      // datalong2
        } FlagToggle;

        struct                      // SCRIPT_COMMAND_TELEPORT_TO (6)
        {
            uint32 MapID;           // datalong
            uint32 Flags;           // datalong2
            int32  Unused1;         // dataint

            float DestX;
            float DestY;
            float DestZ;
            float Orientation;
        } TeleportTo;

        struct                      // SCRIPT_COMMAND_QUEST_EXPLORED (7)
        {
            uint32 QuestID;         // datalong
            uint32 Distance;        // datalong2
        } QuestExplored;

        struct                      // SCRIPT_COMMAND_KILL_CREDIT (8)
        {
            uint32 CreatureEntry;   // datalong
            uint32 Flags;           // datalong2
        } KillCredit;

        struct                      // SCRIPT_COMMAND_RESPAWN_GAMEOBJECT (9)
        {
            uint32 GOGuid;          // datalong
            uint32 DespawnDelay;    // datalong2
        } RespawnGameobject;

        struct                      // SCRIPT_COMMAND_TEMP_SUMMON_CREATURE (10)
        {
            uint32 CreatureEntry;   // datalong
            uint32 DespawnDelay;    // datalong2
            uint32 CheckIfExists;   // dataint

            float PosX;
            float PosY;
            float PosZ;
            float Orientation;
        } TempSummonCreature;

        struct                      // SCRIPT_COMMAND_CLOSE_DOOR (12)
                                    // SCRIPT_COMMAND_OPEN_DOOR (11)
        {
            uint32 GOGuid;          // datalong
            uint32 ResetDelay;      // datalong2
        } ToggleDoor;

                                    // SCRIPT_COMMAND_ACTIVATE_OBJECT (13)

        struct                      // SCRIPT_COMMAND_REMOVE_AURA (14)
        {
            uint32 SpellID;         // datalong
            uint32 Flags;           // datalong2
        } RemoveAura;

        struct                      // SCRIPT_COMMAND_CAST_SPELL (15)
        {
            uint32 SpellID;         // datalong
            uint32 Flags;           // datalong2
            int32  CreatureEntry;   // dataint

            float SearchRadius;
        } CastSpell;

        struct                      // SCRIPT_COMMAND_PLAY_SOUND (16)
        {
            uint32 SoundID;         // datalong
            uint32 Flags;           // datalong2
        } PlaySound;

        struct                      // SCRIPT_COMMAND_CREATE_ITEM (17)
        {
            uint32 ItemEntry;       // datalong
            uint32 Amount;          // datalong2
        } CreateItem;

        struct                      // SCRIPT_COMMAND_DESPAWN_SELF (18)
        {
            uint32 DespawnDelay;    // datalong
        } DespawnSelf;

        struct                      // SCRIPT_COMMAND_LOAD_PATH (20)
        {
            uint32 PathID;          // datalong
            uint32 IsRepeatable;    // datalong2
        } LoadPath;

        struct                      // SCRIPT_COMMAND_CALLSCRIPT_TO_UNIT (21)
        {
            uint32 CreatureEntry;   // datalong
            uint32 ScriptID;        // datalong2
            uint32 ScriptType;      // dataint
        } CallScript;

        struct                      // SCRIPT_COMMAND_KILL (22)
        {
            uint32 Unused1;         // datalong
            uint32 Unused2;         // datalong2
            int32  RemoveCorpse;    // dataint
        } Kill;

        struct                      // SCRIPT_COMMAND_ORIENTATION (30)
        {
            uint32 Flags;           // datalong
            uint32 Unused1;         // datalong2
            int32  Unused2;         // dataint

            float Unused3;
            float Unused4;
            float Unused5;
            float Orientation;
        } Orientation;

        struct                      // SCRIPT_COMMAND_EQUIP (31)
        {
            uint32 EquipmentID;     // datalong
        } Equip;

        struct                      // SCRIPT_COMMAND_MODEL (32)
        {
            uint32 ModelID;         // datalong
        } Model;

                                    // SCRIPT_COMMAND_CLOSE_GOSSIP (33)

        struct                      // SCRIPT_COMMAND_PLAYMOVIE (34)
        {
            uint32 MovieID;         // datalong
        } PlayMovie;
    };

    std::string GetDebugInfo() const;
};

typedef std::multimap<uint32, ScriptInfo> ScriptMap;
typedef std::map<uint32, ScriptMap > ScriptMapMap;
typedef std::multimap<uint32, uint32> SpellScriptsContainer;
typedef std::pair<SpellScriptsContainer::iterator, SpellScriptsContainer::iterator> SpellScriptsBounds;
extern ScriptMapMap sSpellScripts;
extern ScriptMapMap sEventScripts;
extern ScriptMapMap sWaypointScripts;

std::string GetScriptsTableNameByType(ScriptsType type);
ScriptMapMap* GetScriptsMapByType(ScriptsType type);
std::string GetScriptCommandName(ScriptCommands command);

struct SpellClickInfo
{
    uint32 spellId;
    uint8 castFlags;
    SpellClickUserTypes userType;

    // helpers
    bool IsFitToRequirements(Unit const* clicker, Unit const* clickee) const;
};

typedef std::multimap<uint32, SpellClickInfo> SpellClickInfoContainer;
typedef std::pair<SpellClickInfoContainer::const_iterator, SpellClickInfoContainer::const_iterator> SpellClickInfoMapBounds;

struct AreaTrigger
{
    uint32 target_mapId;
    float  target_X;
    float  target_Y;
    float  target_Z;
    float  target_Orientation;
};

struct BroadcastText
{
    BroadcastText() : Id(0), Language(0), EmoteId0(0), EmoteId1(0), EmoteId2(0),
                      EmoteDelay0(0), EmoteDelay1(0), EmoteDelay2(0), SoundId(0), Unk1(0), Unk2(0)
    {
        MaleText.resize(DEFAULT_LOCALE + 1);
        FemaleText.resize(DEFAULT_LOCALE + 1);
    }

    uint32 Id;
    uint32 Language;
    StringVector MaleText;
    StringVector FemaleText;
    uint32 EmoteId0;
    uint32 EmoteId1;
    uint32 EmoteId2;
    uint32 EmoteDelay0;
    uint32 EmoteDelay1;
    uint32 EmoteDelay2;
    uint32 SoundId;
    uint32 Unk1;
    uint32 Unk2;
    // uint32 VerifiedBuild;

    std::string const& GetText(LocaleConstant locale = DEFAULT_LOCALE, uint8 gender = GENDER_MALE, bool forceGender = false) const
    {
        if (gender == GENDER_FEMALE && (forceGender || !FemaleText[DEFAULT_LOCALE].empty()))
        {
            if (FemaleText.size() > size_t(locale) && !FemaleText[locale].empty())
                return FemaleText[locale];
            return FemaleText[DEFAULT_LOCALE];
        }
        // else if (gender == GENDER_MALE)
        {
            if (MaleText.size() > size_t(locale) && !MaleText[locale].empty())
                return MaleText[locale];
            return MaleText[DEFAULT_LOCALE];
        }
    }
};

typedef std::unordered_map<uint32, BroadcastText> BroadcastTextContainer;

typedef std::set<uint32> CellGuidSet;
typedef UNORDERED_MAP<uint32/*player guid*/, uint32/*instance*/> CellCorpseSet;
struct CellObjectGuids
{
    CellGuidSet creatures;
    CellGuidSet gameobjects;
    CellCorpseSet corpses;
};
typedef UNORDERED_MAP<uint32/*cell_id*/, CellObjectGuids> CellObjectGuidsMap;
typedef UNORDERED_MAP<uint32/*(mapid, spawnMode) pair*/, CellObjectGuidsMap> MapObjectGuids;

// Trinity string ranges
#define MIN_TRINITY_STRING_ID           1                    // 'trinity_string'
#define MAX_TRINITY_STRING_ID           2000000000
#define MIN_DB_SCRIPT_STRING_ID        MAX_TRINITY_STRING_ID // 'db_script_string'
#define MAX_DB_SCRIPT_STRING_ID        2000010000
#define MIN_CREATURE_AI_TEXT_STRING_ID (-1)                 // 'creature_ai_texts'
#define MAX_CREATURE_AI_TEXT_STRING_ID (-1000000)

// Trinity Trainer Reference start range
#define TRINITY_TRAINER_START_REF      200000

struct TrinityStringLocale
{
    StringVector Content;
};

typedef std::map<uint64, uint64> LinkedRespawnContainer;
typedef UNORDERED_MAP<uint32, CreatureData> CreatureDataContainer;
typedef UNORDERED_MAP<uint32, GameObjectData> GameObjectDataContainer;
typedef std::map<TempSummonGroupKey, std::vector<TempSummonData> > TempSummonDataContainer;
typedef UNORDERED_MAP<uint32, CreatureLocale> CreatureLocaleContainer;
typedef UNORDERED_MAP<uint32, GameObjectLocale> GameObjectLocaleContainer;
typedef UNORDERED_MAP<uint32, ItemLocale> ItemLocaleContainer;
typedef UNORDERED_MAP<uint32, ItemSetNameLocale> ItemSetNameLocaleContainer;
typedef UNORDERED_MAP<uint32, QuestLocale> QuestLocaleContainer;
typedef UNORDERED_MAP<uint32, NpcTextLocale> NpcTextLocaleContainer;
typedef UNORDERED_MAP<uint32, PageTextLocale> PageTextLocaleContainer;
typedef UNORDERED_MAP<int32, TrinityStringLocale> TrinityStringLocaleContainer;
typedef UNORDERED_MAP<uint32, GossipMenuItemsLocale> GossipMenuItemsLocaleContainer;
typedef UNORDERED_MAP<uint32, PointOfInterestLocale> PointOfInterestLocaleContainer;

typedef std::multimap<uint32, uint32> QuestRelations;
typedef std::pair<QuestRelations::const_iterator, QuestRelations::const_iterator> QuestRelationBounds;

struct PetLevelInfo
{
    PetLevelInfo() : health(0), mana(0), armor(0), min_dmg(0), max_dmg(0) { for (uint8 i=0; i < MAX_STATS; ++i) stats[i] = 0; }

    uint16 stats[MAX_STATS];
    uint16 health;
    uint16 mana;
    uint32 armor;
    uint16 min_dmg;
    uint16 max_dmg;
};

struct MailLevelReward
{
    MailLevelReward() : raceMask(0), mailTemplateId(0), senderEntry(0) {}
    MailLevelReward(uint32 _raceMask, uint32 _mailTemplateId, uint32 _senderEntry) : raceMask(_raceMask), mailTemplateId(_mailTemplateId), senderEntry(_senderEntry) {}

    uint32 raceMask;
    uint32 mailTemplateId;
    uint32 senderEntry;
};

typedef std::list<MailLevelReward> MailLevelRewardList;
typedef UNORDERED_MAP<uint8, MailLevelRewardList> MailLevelRewardContainer;

// We assume the rate is in general the same for all three types below, but chose to keep three for scalability and customization
struct RepRewardRate
{
    float questRate;            // We allow rate = 0.0 in database. For this case, it means that
    float questDailyRate;
    float questWeeklyRate;
    float questMonthlyRate;
    float questRepeatableRate;
    float creatureRate;         // no reputation are given at all for this faction/rate type.
    float spellRate;
};

struct ReputationOnKillEntry
{
    uint32 RepFaction1;
    uint32 RepFaction2;
    uint32 ReputationMaxCap1;
    int32 RepValue1;
    uint32 ReputationMaxCap2;
    int32 RepValue2;
    bool IsTeamAward1;
    bool IsTeamAward2;
    bool TeamDependent;
};

struct RepSpilloverTemplate
{
    uint32 faction[MAX_SPILLOVER_FACTIONS];
    float faction_rate[MAX_SPILLOVER_FACTIONS];
    uint32 faction_rank[MAX_SPILLOVER_FACTIONS];
};

struct PointOfInterest
{
    uint32 entry;
    float x;
    float y;
    uint32 icon;
    uint32 flags;
    uint32 data;
    std::string icon_name;
};

struct GossipMenuItems
{
    uint32          MenuId;
    uint32          OptionIndex;
    uint8           OptionIcon;
    std::string     OptionText;
    uint32          OptionType;
    uint32          OptionNpcflag;
    uint32          ActionMenuId;
    uint32          ActionPoiId;
    bool            BoxCoded;
    uint32          BoxMoney;
    std::string     BoxText;
    ConditionList   Conditions;
};

struct GossipMenus
{
    uint32          entry;
    uint32          text_id;
    ConditionList   conditions;
};

typedef std::multimap<uint32, GossipMenus> GossipMenusContainer;
typedef std::pair<GossipMenusContainer::const_iterator, GossipMenusContainer::const_iterator> GossipMenusMapBounds;
typedef std::pair<GossipMenusContainer::iterator, GossipMenusContainer::iterator> GossipMenusMapBoundsNonConst;
typedef std::multimap<uint32, GossipMenuItems> GossipMenuItemsContainer;
typedef std::pair<GossipMenuItemsContainer::const_iterator, GossipMenuItemsContainer::const_iterator> GossipMenuItemsMapBounds;
typedef std::pair<GossipMenuItemsContainer::iterator, GossipMenuItemsContainer::iterator> GossipMenuItemsMapBoundsNonConst;

struct QuestPOIPoint
{
    int32 x;
    int32 y;

    QuestPOIPoint() : x(0), y(0) {}
    QuestPOIPoint(int32 _x, int32 _y) : x(_x), y(_y) {}
};

struct QuestPOI
{
    uint32 Id;
    int32 ObjectiveIndex;
    uint32 MapId;
    uint32 AreaId;
    uint32 FloorId;
    uint32 Unk3;
    uint32 Unk4;
    std::vector<QuestPOIPoint> points;

    QuestPOI() : Id(0), ObjectiveIndex(0), MapId(0), AreaId(0), FloorId(0), Unk3(0), Unk4(0) {}
    QuestPOI(uint32 id, int32 objIndex, uint32 mapId, uint32 areaId, uint32 floorId, uint32 unk3, uint32 unk4) : Id(id), ObjectiveIndex(objIndex), MapId(mapId), AreaId(areaId), FloorId(floorId), Unk3(unk3), Unk4(unk4) {}
};

typedef std::vector<QuestPOI> QuestPOIVector;
typedef UNORDERED_MAP<uint32, QuestPOIVector> QuestPOIContainer;

struct GraveyardData
{
    uint32 safeLocId;
    TeamId teamId;
};

typedef std::multimap<uint32, GraveyardData> GraveyardContainer;
typedef std::pair<GraveyardContainer::const_iterator, GraveyardContainer::const_iterator> GraveyardMapBounds;
typedef std::pair<GraveyardContainer::iterator, GraveyardContainer::iterator> GraveyardMapBoundsNonConst;

typedef UNORDERED_MAP<uint32, VendorItemData> CacheVendorItemContainer;
typedef UNORDERED_MAP<uint32, TrainerSpellData> CacheTrainerSpellContainer;

enum SkillRangeType
{
    SKILL_RANGE_LANGUAGE,                                   // 300..300
    SKILL_RANGE_LEVEL,                                      // 1..max skill for level
    SKILL_RANGE_MONO,                                       // 1..1, grey monolite bar
    SKILL_RANGE_RANK,                                       // 1..skill for known rank
    SKILL_RANGE_NONE,                                       // 0..0 always
};

SkillRangeType GetSkillRangeType(SkillLineEntry const* pSkill, bool racial);

#define MAX_PLAYER_NAME          12                         // max allowed by client name length
#define MAX_INTERNAL_PLAYER_NAME 15                         // max server internal player name length (> MAX_PLAYER_NAME for support declined names)
#define MAX_PET_NAME             12                         // max allowed by client name length
#define MAX_CHARTER_NAME         24                         // max allowed by client name length
#define MAX_CHANNEL_NAME         50                         // pussywizard

bool normalizePlayerName(std::string& name);

struct LanguageDesc
{
    Language lang_id;
    uint32   spell_id;
    uint32   skill_id;
};

extern LanguageDesc lang_description[LANGUAGES_COUNT];
LanguageDesc const* GetLanguageDescByID(uint32 lang);

struct DungeonEncounter
{
    DungeonEncounter(DungeonEncounterEntry const* _dbcEntry, EncounterCreditType _creditType, uint32 _creditEntry, uint32 _lastEncounterDungeon)
        : dbcEntry(_dbcEntry), creditType(_creditType), creditEntry(_creditEntry), lastEncounterDungeon(_lastEncounterDungeon) { }

    DungeonEncounterEntry const* dbcEntry;
    EncounterCreditType creditType;
    uint32 creditEntry;
    uint32 lastEncounterDungeon;
};

typedef std::list<DungeonEncounter const*> DungeonEncounterList;
typedef UNORDERED_MAP<uint32, DungeonEncounterList> DungeonEncounterContainer;

class PlayerDumpReader;

class ObjectMgr
{
    friend class PlayerDumpReader;
    friend class ACE_Singleton<ObjectMgr, ACE_Null_Mutex>;

    private:
        ObjectMgr();
        ~ObjectMgr();

    public:
		//WQCORE 方法定义开始
		void LoadAllxxCoreData();
		std::string GetItemNameLink(uint32 ItemId);
		void LoadxxCreatureTeleport();
		bool RunxxCreatureTeleport(uint32 action, uint32 sender, Player *player, Creature *pcreature);
		bool RunxxShangren(uint32 action, uint32 sender, Player *player, Creature *pcreature);
		void xxCreatureTeleportFromMenuId(Player* player, uint32 MenuId);
		void LoadxxCreatureTeleportMenu(uint32 /*menuid*/, Player* /*player*/, Creature* /*pcreature*/);
		void LoadxxItemb();
		void LoadxxItem();
		void LoadxxItemicc();
		void ShowCjgradeMenu(Item *m_from, Item *target, Player *player);
		void UpgradeThisItemcj(Item *target, Player *player, Item* m_from);
		void ShowZhgradeMenu(Item *m_from, Item *target, Player *player);
		void UpgradeThisItemzh(Item *target, Player *player, Item* m_from);
		void LoadxxItemcj();
		void LoadxxItemzh();
		bool WorldSayCommand(Player *player, const char *args);
		std::string GetNameLink(Player* player);
		uint32 ShowItemSpawn(uint32 item);
		void AddToBG(Player* player);
		void AddToBG1(Player* player);
		void AddToBG2(Player* player);
		void AddToBG3(Player* player);
		void AddToBG101(Player* player);
		void AddToBG111(Player* player);
		void AddToBG112(Player* player);
		void AddToBG113(Player* player);
		void AddToBG114(Player* player);
		void AddToBG115(Player* player);
		void AddToBG116(Player* player);
		void AddToBG117(Player* player);
		void AddToBG118(Player* player);
		void AddToBG120(Player* player);
		void AddToBG123(Player* player);
		void XxHui(Player * player, Item * pitem);
		void ShowCjMenu(Player* player, Creature *pcreature);
		void Updatecjjf(Player* player, Creature *pcreature, uint32 sender, uint32 uiAction);
		uint32 ShowItemcjSpawn(uint32 item, int8 sta);
		void ShowCjzMenu(Player* player, Creature *pcreature);
		void Updatecjzjf(Player* player, Creature *pcreature, uint32 sender, uint32 uiAction);
		uint32 ShowItemcjzSpawn(uint32 item, int8 sta);
		uint32 ShowItemcjzzSpawn(uint32 item, int8 sta);
		bool xxAHRewardGg(Player* player, uint64 owner, uint32 item, uint32 count, uint32 buyout);
		bool xxAHRewardOwner(Player* pl, uint64 owner, int32 JF);
		void Loadxxcjjf();
		void Loadxxcjzjf();
		void Loadxxcjzzjf();
		void AddToFuben(Player* player, uint32 sender, uint32 action);
		void AddToFuben1(Player* player, uint32 sender, uint32 action);
		void AddToFuben2(Player* player, uint32 sender, uint32 action);
		void AddToFuben3(Player* player, uint32 sender, uint32 action);
		void AddToFuben4(Player* player, uint32 sender, uint32 action);
		void SendBoxText(Player* player, uint32 action);
		void SendFubenText(Player* player, uint32 action);
		void SendTocText(Player* player, uint32 action);
		void SendIccText(Player* player, uint32 action);
		void SendKlzText(Player* player, uint32 action);
		void SendFbysText(Player* player, uint32 action);
		void SendGleText(Player* player, uint32 action);
		void SendSuoyaoText(Player* player, uint32 action);
		void XxZz(Player * player, Creature *pcreature);
		void XxJl(Player * player, Creature *pcreature);
		void XxShangren(Player * player, Creature *pcreature);
		uint32 GetRaid(Creature *pcreature, int8 sta);
		uint32 GetRaidBox(uint32 loot, int8 sta);
		void ShowBossSpawn(Player* player, Creature *pcreature, int8 sta);
		void Loadxxnpc();
		uint32 GetSuoyao(uint32 sta, int8 a);
		uint32 GetTongtian(uint32 sta);
		void GetKillCretureCredit(Player * player, Creature *creature);
		uint32 IsSuoyaoEntry(uint32 enry, int8 a);
		uint32 IsHuoliEntry(uint32 enry, int8 a);
		uint32 IsTongtianEntry(uint32 enry, int8 a);
		std::string GetRaidBuff(int8 sta);
		uint32 GetPvpAura(Player* player);
		void ShowPvpRankMenu(Player *player, Item *item);
		void PvpRankLevelUP(Player *player, Item *item);
		uint32 GetPvpRankUINT32(uint32 level, uint8 index);
		uint32 GetAddPvpTalent(Player* player);			// 获取增加的潜能点
		uint32 GetAddPvpShuxing(Player* player);
		void LoadxxItemTeleportMenu(uint32 /*menuid*/, Player* /*player*/, Item* /*pitem*/);
		void HuoliMenu(Player *player, Item *item);
		void KlzMenu(Player *player, Item *item);
		void FbysMenu(Player *player, Item *item);
		void GleMenu(Player *player, Item *item);
		void YskkMenu(Player *player, Item *item);
		void HjeMenu(Player *player, Item *item);
		void JxpyMenu(Player *player, Item *item);
		void TocMenu(Player *player, Item *item);
		void IccMenu(Player *player, Item *item);
		void WorldbossMenu(Player *player, Item *item);
		bool RunxxItemTeleport(uint32 action, uint32 sender, Player *player, Item *pitem);
		void xxTeleportFromMenuId(Player* player, uint32 MenuId);
		void ShowJfzhuanyeMenu(Player *player, Item *item);
		void ShowshijianMenu(Player *player, Item *item);
		void ShijianUP(Player *player, Item *item, int8 sta);
		void Huolichuansong(Player *player, Item *item);
		void JfzhuanyeUP(Player *player, Item *item, int8 sta);
		void ShowJfZyMenu(Player *player, Item *item);
		void JfZyUP(Player *player, Item *item, int8 sta);
		void ShowUpgradeMenu(Item *m_from, Item *target, Player *player);
		void UpgradeThisItem(Item *target, Player *player, Item* m_from);
		uint32 GetBattlegroundValue(uint32 bgtype, uint32 index);
		void ShowFuyinMenu(Player* player, Item* pitem);
		void ShowYuyiMenu(Player* player, Item* pitem);
		void ShowJntpMenu(Player* player, Item* pitem);
		void ShowJnjxMenu(Player* player, Item* pitem);
		void ShowJnpyMenu(Player* player, Item* pitem);
		void Updatefuyin(Player* player, Item* pitem, uint32 uiAction);
		void Updatejntp(Player* player, Item* pitem, uint32 uiAction);
		void Updateyuyi(Player* player, Item* pitem, uint32 uiAction);
		void Updateyuyi1(Player* player, Item* pitem, uint32 uiAction);
		void Updatejnjx(Player* player, Item* pitem, uint32 uiAction);
		void Updatejnpy(Player* player, Item* pitem, uint32 uiAction);
		uint32 GetAddOnlinePoint(Player *player);		// 获取增加的泡点
		uint32 GetVipMrJl(Player *player, int8 sta, uint8 index);
		const char *GetLoginAnnounce(Player *player);			// 获取会员上线公告
		uint32 GetUpdateVipRewarItem(Player *player);	// 获取会员升级奖励
		uint32 GetAddUpPro(Player *player);				// 获得增加的成功率
		std::string GetVipTitle(Player* player);		// 获取VIP标题
		std::string GetVipColor(Player* player);		// 获取VIP喊话颜色
		uint32 GetVipAura(Player* player);
		float GetVipShuXingStat(Player * player);
		void ShowVipMenu(Player *player, Item *item);
		uint32 GetVipUINT32(uint32 level, uint8 index);
		void VipLevelUP(Player *player, Item *item);
		void ShowBuffSpawn(Player* player);
		bool CheckEnterBattleground(Player *player, uint32 Entry);
		void SendAutoGiver(Player *player);
		uint32 isBossCoreA(uint32 enry) const;
		void setisBossCoreA(uint32 enry);
		void setisBossCoreB(uint32 index,uint32 enry);
		void czisBossCoreA(uint32 enry);
		void LoadxxItemTeleport();
		void LoadxxItemup();
		void LoadxxBattleground();
		void LoadPvpRankSystem();
		void LoadRaidSystem();
		void LoadRaidBoxSystem();
		void LoadSuoyaoSystem();
		void LoadTongtianSystem();
		void LoadSuoSystem();
		void LoadTongSystem();
		void LoadHuoliSystem();
		void LoadMapidvalue();
		void LoadMapididvalue();
		void LoadFuyinData();
		void LoadYuyiData();
		void LoadJntupoData();
		void LoadJnjuexingData();
		void LoadJnpeiyangData();
		void LoadxxVipSystem();
		void LoadxxVipSystemMr();
		void LoadxxItembuff();
		uint32 GetSkillAura(Player* player, uint32 skill);
		void LoadSkillSystem();
		uint32 xxcoremapid[72];
		uint32 xxcoremapidid[74];

        typedef UNORDERED_MAP<uint32, Item*> ItemMap;

        typedef UNORDERED_MAP<uint32, Quest*> QuestMap;

        typedef UNORDERED_MAP<uint32, AreaTrigger> AreaTriggerContainer;

        typedef UNORDERED_MAP<uint32, uint32> AreaTriggerScriptContainer;

        typedef UNORDERED_MAP<uint32, AccessRequirement*> AccessRequirementContainer;

        typedef UNORDERED_MAP<uint32, RepRewardRate > RepRewardRateContainer;
        typedef UNORDERED_MAP<uint32, ReputationOnKillEntry> RepOnKillContainer;
        typedef UNORDERED_MAP<uint32, RepSpilloverTemplate> RepSpilloverTemplateContainer;

        typedef UNORDERED_MAP<uint32, PointOfInterest> PointOfInterestContainer;

        typedef std::vector<std::string> ScriptNameContainer;

        typedef std::map<uint32, uint32> CharacterConversionMap;

		Player* GetPlayer(const char* name) const { return sObjectAccessor->FindPlayerByName(name); }
		Player* GetPlayer(uint64 guid) const { return ObjectAccessor::FindPlayer(guid); }
        Player* GetPlayerByLowGUID(uint32 lowguid) const;

        GameObjectTemplate const* GetGameObjectTemplate(uint32 entry);
        bool IsGameObjectStaticTransport(uint32 entry);
        GameObjectTemplateContainer const* GetGameObjectTemplates() const { return &_gameObjectTemplateStore; }
        int LoadReferenceVendor(int32 vendor, int32 item_id, std::set<uint32> *skip_vendors);

        void LoadGameObjectTemplate();
        void AddGameobjectInfo(GameObjectTemplate* goinfo);

        CreatureTemplate const* GetCreatureTemplate(uint32 entry);
        CreatureTemplateContainer const* GetCreatureTemplates() const { return &_creatureTemplateStore; }
        CreatureModelInfo const* GetCreatureModelInfo(uint32 modelId);
        CreatureModelInfo const* GetCreatureModelRandomGender(uint32* displayID);
        static uint32 ChooseDisplayId(CreatureTemplate const* cinfo, CreatureData const* data = NULL);
        static void ChooseCreatureFlags(CreatureTemplate const* cinfo, uint32& npcflag, uint32& unit_flags, uint32& dynamicflags, CreatureData const* data = NULL);
        EquipmentInfo const* GetEquipmentInfo(uint32 entry, int8& id);
        CreatureAddon const* GetCreatureAddon(uint32 lowguid);
        GameObjectAddon const* GetGameObjectAddon(uint32 lowguid);
        CreatureAddon const* GetCreatureTemplateAddon(uint32 entry);
        ItemTemplate const* GetItemTemplate(uint32 entry);
        ItemTemplateContainer const* GetItemTemplateStore() const { return &_itemTemplateStore; }

        ItemSetNameEntry const* GetItemSetNameEntry(uint32 itemId)
        {
            ItemSetNameContainer::iterator itr = _itemSetNameStore.find(itemId);
            if (itr != _itemSetNameStore.end())
                return &itr->second;
            return NULL;
        }

        InstanceTemplate const* GetInstanceTemplate(uint32 mapId);

        PetLevelInfo const* GetPetLevelInfo(uint32 creature_id, uint8 level) const;

        PlayerClassInfo const* GetPlayerClassInfo(uint32 class_) const
        {
            if (class_ >= MAX_CLASSES)
                return NULL;
            return _playerClassInfo[class_];
        }
        void GetPlayerClassLevelInfo(uint32 class_, uint8 level, PlayerClassLevelInfo* info) const;

        PlayerInfo const* GetPlayerInfo(uint32 race, uint32 class_) const;

        void GetPlayerLevelInfo(uint32 race, uint32 class_, uint8 level, PlayerLevelInfo* info) const;

        uint64 GetPlayerGUIDByName(std::string const& name) const;
        bool GetPlayerNameByGUID(uint64 guid, std::string &name) const;
        TeamId GetPlayerTeamIdByGUID(uint64 guid) const;
        uint32 GetPlayerAccountIdByGUID(uint64 guid) const;
        uint32 GetPlayerAccountIdByPlayerName(std::string const& name) const;

        uint32 GetNearestTaxiNode(float x, float y, float z, uint32 mapid, uint32 teamId);
        void GetTaxiPath(uint32 source, uint32 destination, uint32 &path, uint32 &cost);
        uint32 GetTaxiMountDisplayId(uint32 id, TeamId teamId, bool allowed_alt_team = false);

        GameObjectQuestItemList const* GetGameObjectQuestItemList(uint32 id) const
        {
            GameObjectQuestItemMap::const_iterator itr = _gameObjectQuestItemStore.find(id);
            if (itr != _gameObjectQuestItemStore.end())
                return &itr->second;
            return NULL;
        }
        GameObjectQuestItemMap const* GetGameObjectQuestItemMap() const { return &_gameObjectQuestItemStore; }

        CreatureQuestItemList const* GetCreatureQuestItemList(uint32 id) const
        {
            CreatureQuestItemMap::const_iterator itr = _creatureQuestItemStore.find(id);
            if (itr != _creatureQuestItemStore.end())
                return &itr->second;
            return NULL;
        }
        CreatureQuestItemMap const* GetCreatureQuestItemMap() const { return &_creatureQuestItemStore; }

        Quest const* GetQuestTemplate(uint32 quest_id) const
        {
            return quest_id < _questTemplatesFast.size() ? _questTemplatesFast[quest_id] : NULL;
        }

        QuestMap const& GetQuestTemplates() const { return _questTemplates; }

        uint32 GetQuestForAreaTrigger(uint32 Trigger_ID) const
        {
            QuestAreaTriggerContainer::const_iterator itr = _questAreaTriggerStore.find(Trigger_ID);
            if (itr != _questAreaTriggerStore.end())
                return itr->second;
            return 0;
        }

        bool IsTavernAreaTrigger(uint32 Trigger_ID) const
        {
            return _tavernAreaTriggerStore.find(Trigger_ID) != _tavernAreaTriggerStore.end();
        }

        GossipText const* GetGossipText(uint32 Text_ID) const;

        WorldSafeLocsEntry const* GetDefaultGraveyard(TeamId teamId);
        WorldSafeLocsEntry const* GetClosestGraveyard(float x, float y, float z, uint32 MapId, TeamId teamId);
        bool AddGraveyardLink(uint32 id, uint32 zoneId, TeamId teamId, bool persist = true);
        void RemoveGraveyardLink(uint32 id, uint32 zoneId, TeamId teamId, bool persist = false);
        void LoadGraveyardZones();
        GraveyardData const* FindGraveyardData(uint32 id, uint32 zone);

        AreaTrigger const* GetAreaTrigger(uint32 trigger) const
        {
            AreaTriggerContainer::const_iterator itr = _areaTriggerStore.find(trigger);
            if (itr != _areaTriggerStore.end())
                return &itr->second;
            return NULL;
        }

        AccessRequirement const* GetAccessRequirement(uint32 mapid, Difficulty difficulty) const
        {
            AccessRequirementContainer::const_iterator itr = _accessRequirementStore.find(MAKE_PAIR32(mapid, difficulty));
            if (itr != _accessRequirementStore.end())
                return itr->second;
            return NULL;
        }

        AreaTrigger const* GetGoBackTrigger(uint32 Map) const;
        AreaTrigger const* GetMapEntranceTrigger(uint32 Map) const;

        uint32 GetAreaTriggerScriptId(uint32 trigger_id);
        SpellScriptsBounds GetSpellScriptsBounds(uint32 spell_id);

        RepRewardRate const* GetRepRewardRate(uint32 factionId) const
        {
            RepRewardRateContainer::const_iterator itr = _repRewardRateStore.find(factionId);
            if (itr != _repRewardRateStore.end())
                return &itr->second;

            return NULL;
        }

        ReputationOnKillEntry const* GetReputationOnKilEntry(uint32 id) const
        {
            RepOnKillContainer::const_iterator itr = _repOnKillStore.find(id);
            if (itr != _repOnKillStore.end())
                return &itr->second;
            return NULL;
        }

        int32 GetBaseReputationOf(FactionEntry const* factionEntry, uint8 race, uint8 playerClass);

        RepSpilloverTemplate const* GetRepSpilloverTemplate(uint32 factionId) const
        {
            RepSpilloverTemplateContainer::const_iterator itr = _repSpilloverTemplateStore.find(factionId);
            if (itr != _repSpilloverTemplateStore.end())
                return &itr->second;

            return NULL;
        }

        PointOfInterest const* GetPointOfInterest(uint32 id) const
        {
            PointOfInterestContainer::const_iterator itr = _pointsOfInterestStore.find(id);
            if (itr != _pointsOfInterestStore.end())
                return &itr->second;
            return NULL;
        }

        QuestPOIVector const* GetQuestPOIVector(uint32 questId)
        {
            QuestPOIContainer::const_iterator itr = _questPOIStore.find(questId);
            if (itr != _questPOIStore.end())
                return &itr->second;
            return NULL;
        }

        VehicleAccessoryList const* GetVehicleAccessoryList(Vehicle* veh) const;

        DungeonEncounterList const* GetDungeonEncounterList(uint32 mapId, Difficulty difficulty)
        {
            UNORDERED_MAP<uint32, DungeonEncounterList>::const_iterator itr = _dungeonEncounterStore.find(MAKE_PAIR32(mapId, difficulty));
            if (itr != _dungeonEncounterStore.end())
                return &itr->second;
            return NULL;
        }

        void LoadQuests();
        void LoadQuestStartersAndEnders()
        {
            sLog->outString("Loading GO Start Quest Data...");
            LoadGameobjectQuestStarters();
            sLog->outString("Loading GO End Quest Data...");
            LoadGameobjectQuestEnders();
            sLog->outString("Loading Creature Start Quest Data...");
            LoadCreatureQuestStarters();
            sLog->outString("Loading Creature End Quest Data...");
            LoadCreatureQuestEnders();
        }
        void LoadGameobjectQuestStarters();
        void LoadGameobjectQuestEnders();
        void LoadCreatureQuestStarters();
        void LoadCreatureQuestEnders();

        QuestRelations* GetGOQuestRelationMap()
        {
            return &_goQuestRelations;
        }

        QuestRelations* GetGOQuestInvolvedRelationMap()
        {
            return &_goQuestInvolvedRelations;
        }

        QuestRelationBounds GetGOQuestRelationBounds(uint32 go_entry)
        {
            return _goQuestRelations.equal_range(go_entry);
        }

        QuestRelationBounds GetGOQuestInvolvedRelationBounds(uint32 go_entry)
        {
            return _goQuestInvolvedRelations.equal_range(go_entry);
        }

        QuestRelations* GetCreatureQuestRelationMap()
        {
            return &_creatureQuestRelations;
        }

        QuestRelations* GetCreatureQuestInvolvedRelationMap()
        {
            return &_creatureQuestInvolvedRelations;
        }

        QuestRelationBounds GetCreatureQuestRelationBounds(uint32 creature_entry)
        {
            return _creatureQuestRelations.equal_range(creature_entry);
        }

        QuestRelationBounds GetCreatureQuestInvolvedRelationBounds(uint32 creature_entry)
        {
            return _creatureQuestInvolvedRelations.equal_range(creature_entry);
        }

        void LoadEventScripts();
        void LoadSpellScripts();
        void LoadWaypointScripts();

        void LoadSpellScriptNames();
        void ValidateSpellScripts();
        void InitializeSpellInfoPrecomputedData();

        bool LoadTrinityStrings(char const* table, int32 min_value, int32 max_value);
        bool LoadTrinityStrings() { return LoadTrinityStrings("trinity_string", MIN_TRINITY_STRING_ID, MAX_TRINITY_STRING_ID); }
        void LoadDbScriptStrings();
        void LoadBroadcastTexts();
        void LoadBroadcastTextLocales();
        void LoadCreatureClassLevelStats();
        void LoadCreatureLocales();
        void LoadCreatureTemplates();
        void LoadCreatureTemplateAddons();
        void CheckCreatureTemplate(CreatureTemplate const* cInfo);
        void LoadGameObjectQuestItems();
        void LoadCreatureQuestItems();
        void LoadTempSummons();
        void LoadCreatures();
        void LoadLinkedRespawn();
        bool SetCreatureLinkedRespawn(uint32 guid, uint32 linkedGuid);
        void LoadCreatureAddons();
        void LoadGameObjectAddons();
        void LoadCreatureModelInfo();
        void LoadEquipmentTemplates();
        void LoadGameObjectLocales();
        void LoadGameobjects();
        void LoadItemTemplates();
        void LoadItemLocales();
        void LoadItemSetNames();
        void LoadItemSetNameLocales();
        void LoadQuestLocales();
        void LoadNpcTextLocales();
        void LoadPageTextLocales();
        void LoadGossipMenuItemsLocales();
        void LoadPointOfInterestLocales();
        void LoadInstanceTemplate();
        void LoadInstanceEncounters();
        void LoadMailLevelRewards();
        void LoadVehicleTemplateAccessories();
        void LoadVehicleAccessories();

        void LoadGossipText();

        void LoadAreaTriggerTeleports();
        void LoadAccessRequirements();
        void LoadQuestAreaTriggers();
        void LoadAreaTriggerScripts();
        void LoadTavernAreaTriggers();
        void LoadGameObjectForQuests();

        void LoadPageTexts();
        PageText const* GetPageText(uint32 pageEntry);

        void LoadPlayerInfo();
        void LoadPetLevelInfo();
        void LoadExplorationBaseXP();
        void LoadPetNames();
        void LoadPetNumber();
        void LoadCorpses();
        void LoadFishingBaseSkillLevel();

        void LoadReputationRewardRate();
        void LoadReputationOnKill();
        void LoadReputationSpilloverTemplate();

        void LoadPointsOfInterest();
        void LoadQuestPOI();

        void LoadNPCSpellClickSpells();

        void LoadGameTele();

        void LoadGossipMenu();
        void LoadGossipMenuItems();

        void LoadVendors();
        void LoadTrainerSpell();
        void AddSpellToTrainer(uint32 entry, uint32 spell, uint32 spellCost, uint32 reqSkill, uint32 reqSkillValue, uint32 reqLevel);

        std::string GeneratePetName(uint32 entry);
        uint32 GetBaseXP(uint8 level);
        uint32 GetXPForLevel(uint8 level) const;

        int32 GetFishingBaseSkillLevel(uint32 entry) const
        {
            FishingBaseSkillContainer::const_iterator itr = _fishingBaseForAreaStore.find(entry);
            return itr != _fishingBaseForAreaStore.end() ? itr->second : 0;
        }

        void ReturnOrDeleteOldMails(bool serverUp);

        CreatureBaseStats const* GetCreatureBaseStats(uint8 level, uint8 unitClass);

        void SetHighestGuids();
        uint32 GenerateLowGuid(HighGuid guidhigh);
        uint32 GenerateAuctionID();
        uint64 GenerateEquipmentSetGuid();
        uint32 GenerateMailID();
        uint32 GeneratePetNumber();

        typedef std::multimap<int32, uint32> ExclusiveQuestGroups;
        typedef std::pair<ExclusiveQuestGroups::const_iterator, ExclusiveQuestGroups::const_iterator> ExclusiveQuestGroupsBounds;

        ExclusiveQuestGroups mExclusiveQuestGroups;

        MailLevelReward const* GetMailLevelReward(uint32 level, uint32 raceMask)
        {
            MailLevelRewardContainer::const_iterator map_itr = _mailLevelRewardStore.find(level);
            if (map_itr == _mailLevelRewardStore.end())
                return NULL;

            for (MailLevelRewardList::const_iterator set_itr = map_itr->second.begin(); set_itr != map_itr->second.end(); ++set_itr)
                if (set_itr->raceMask & raceMask)
                    return &*set_itr;

            return NULL;
        }

        CellObjectGuids const& GetCellObjectGuids(uint16 mapid, uint8 spawnMode, uint32 cell_id)
        {
            MapObjectGuids::const_iterator itr1 = _mapObjectGuidsStore.find(MAKE_PAIR32(mapid, spawnMode));
            if (itr1 != _mapObjectGuidsStore.end())
            {
                CellObjectGuidsMap::const_iterator itr2 = itr1->second.find(cell_id);
                if (itr2 != itr1->second.end())
                    return itr2->second;
            }
            return _emptyCellObjectGuids;
        }

        CellObjectGuidsMap const& GetMapObjectGuids(uint16 mapid, uint8 spawnMode)
        {
            MapObjectGuids::const_iterator itr1 = _mapObjectGuidsStore.find(MAKE_PAIR32(mapid, spawnMode));
            if (itr1 != _mapObjectGuidsStore.end())
                return itr1->second;
            return _emptyCellObjectGuidsMap;
        }

        /**
         * Gets temp summon data for all creatures of specified group.
         *
         * @param summonerId   Summoner's entry.
         * @param summonerType Summoner's type, see SummonerType for available types.
         * @param group        Id of required group.
         *
         * @return null if group was not found, otherwise reference to the creature group data
         */
        std::vector<TempSummonData> const* GetSummonGroup(uint32 summonerId, SummonerType summonerType, uint8 group) const
        {
            TempSummonDataContainer::const_iterator itr = _tempSummonDataStore.find(TempSummonGroupKey(summonerId, summonerType, group));
            if (itr != _tempSummonDataStore.end())
                return &itr->second;
                   
            return NULL;
        }

        BroadcastText const* GetBroadcastText(uint32 id) const
        {
            BroadcastTextContainer::const_iterator itr = _broadcastTextStore.find(id);
            if (itr != _broadcastTextStore.end())
                return &itr->second;
            return nullptr;
        }
        CreatureData const* GetCreatureData(uint32 guid) const
        {
            CreatureDataContainer::const_iterator itr = _creatureDataStore.find(guid);
            if (itr == _creatureDataStore.end()) return NULL;
            return &itr->second;
        }
        CreatureData& NewOrExistCreatureData(uint32 guid) { return _creatureDataStore[guid]; }
        void DeleteCreatureData(uint32 guid);
        uint64 GetLinkedRespawnGuid(uint64 guid) const
        {
            LinkedRespawnContainer::const_iterator itr = _linkedRespawnStore.find(guid);
            if (itr == _linkedRespawnStore.end()) return 0;
            return itr->second;
        }

        GameObjectData const* GetGOData(uint32 guid) const
        {
            GameObjectDataContainer::const_iterator itr = _gameObjectDataStore.find(guid);
            if (itr == _gameObjectDataStore.end()) return NULL;
            return &itr->second;
        }
        CreatureLocale const* GetCreatureLocale(uint32 entry) const
        {
            CreatureLocaleContainer::const_iterator itr = _creatureLocaleStore.find(entry);
            if (itr == _creatureLocaleStore.end()) return NULL;
            return &itr->second;
        }
        GameObjectLocale const* GetGameObjectLocale(uint32 entry) const
        {
            GameObjectLocaleContainer::const_iterator itr = _gameObjectLocaleStore.find(entry);
            if (itr == _gameObjectLocaleStore.end()) return NULL;
            return &itr->second;
        }
        ItemLocale const* GetItemLocale(uint32 entry) const
        {
            ItemLocaleContainer::const_iterator itr = _itemLocaleStore.find(entry);
            if (itr == _itemLocaleStore.end()) return NULL;
            return &itr->second;
        }
        ItemSetNameLocale const* GetItemSetNameLocale(uint32 entry) const
        {
            ItemSetNameLocaleContainer::const_iterator itr = _itemSetNameLocaleStore.find(entry);
            if (itr == _itemSetNameLocaleStore.end())return NULL;
            return &itr->second;
        }
        PageTextLocale const* GetPageTextLocale(uint32 entry) const
        {
            PageTextLocaleContainer::const_iterator itr = _pageTextLocaleStore.find(entry);
            if (itr == _pageTextLocaleStore.end()) return NULL;
            return &itr->second;
        }
        QuestLocale const* GetQuestLocale(uint32 entry) const
        {
            QuestLocaleContainer::const_iterator itr = _questLocaleStore.find(entry);
            if (itr == _questLocaleStore.end()) return NULL;
            return &itr->second;
        }
        GossipMenuItemsLocale const* GetGossipMenuItemsLocale(uint32 entry) const
        {
            GossipMenuItemsLocaleContainer::const_iterator itr = _gossipMenuItemsLocaleStore.find(entry);
            if (itr == _gossipMenuItemsLocaleStore.end()) return NULL;
            return &itr->second;
        }
        PointOfInterestLocale const* GetPointOfInterestLocale(uint32 poi_id) const
        {
            PointOfInterestLocaleContainer::const_iterator itr = _pointOfInterestLocaleStore.find(poi_id);
            if (itr == _pointOfInterestLocaleStore.end()) return NULL;
            return &itr->second;
        }
        NpcTextLocale const* GetNpcTextLocale(uint32 entry) const
        {
            NpcTextLocaleContainer::const_iterator itr = _npcTextLocaleStore.find(entry);
            if (itr == _npcTextLocaleStore.end()) return NULL;
            return &itr->second;
        }
        GameObjectData& NewGOData(uint32 guid) { return _gameObjectDataStore[guid]; }
        void DeleteGOData(uint32 guid);

        TrinityStringLocale const* GetTrinityStringLocale(int32 entry) const
        {
            TrinityStringLocaleContainer::const_iterator itr = _trinityStringLocaleStore.find(entry);
            if (itr == _trinityStringLocaleStore.end()) return NULL;
            return &itr->second;
        }
        const char *GetTrinityString(int32 entry, LocaleConstant locale_idx) const;
        const char *GetTrinityStringForDBCLocale(int32 entry) const { return GetTrinityString(entry, DBCLocaleIndex); }
        LocaleConstant GetDBCLocaleIndex() const { return DBCLocaleIndex; }
        void SetDBCLocaleIndex(LocaleConstant locale) { DBCLocaleIndex = locale; }

        void AddCorpseCellData(uint32 mapid, uint32 cellid, uint32 player_guid, uint32 instance);
        void DeleteCorpseCellData(uint32 mapid, uint32 cellid, uint32 player_guid);

        // grid objects
        void AddCreatureToGrid(uint32 guid, CreatureData const* data);
        void RemoveCreatureFromGrid(uint32 guid, CreatureData const* data);
        void AddGameobjectToGrid(uint32 guid, GameObjectData const* data);
        void RemoveGameobjectFromGrid(uint32 guid, GameObjectData const* data);
        uint32 AddGOData(uint32 entry, uint32 map, float x, float y, float z, float o, uint32 spawntimedelay = 0, float rotation0 = 0, float rotation1 = 0, float rotation2 = 0, float rotation3 = 0);
        uint32 AddCreData(uint32 entry, uint32 map, float x, float y, float z, float o, uint32 spawntimedelay = 0);
        bool MoveCreData(uint32 guid, uint32 map, Position pos);

        // reserved names
        void LoadReservedPlayersNames();
        bool IsReservedName(std::string const& name) const;

        // name with valid structure and symbols
        static uint8 CheckPlayerName(std::string const& name, bool create = false);
        static PetNameInvalidReason CheckPetName(std::string const& name);
        static bool IsValidCharterName(std::string const& name);
        static bool IsValidChannelName(std::string const& name);

        static bool CheckDeclinedNames(std::wstring w_ownname, DeclinedName const& names);

        GameTele const* GetGameTele(uint32 id) const
        {
            GameTeleContainer::const_iterator itr = _gameTeleStore.find(id);
            if (itr == _gameTeleStore.end()) return NULL;
            return &itr->second;
        }
        GameTele const* GetGameTele(std::string const& name) const;
        GameTeleContainer const& GetGameTeleMap() const { return _gameTeleStore; }
        bool AddGameTele(GameTele& data);
        bool DeleteGameTele(std::string const& name);

        TrainerSpellData const* GetNpcTrainerSpells(uint32 entry) const
        {
            CacheTrainerSpellContainer::const_iterator  iter = _cacheTrainerSpellStore.find(entry);
            if (iter == _cacheTrainerSpellStore.end())
                return NULL;

            return &iter->second;
        }

        VendorItemData const* GetNpcVendorItemList(uint32 entry) const
        {
            CacheVendorItemContainer::const_iterator iter = _cacheVendorItemStore.find(entry);
            if (iter == _cacheVendorItemStore.end())
                return NULL;

            return &iter->second;
        }

        void AddVendorItem(uint32 entry, uint32 item, int32 maxcount, uint32 incrtime, uint32 extendedCost, bool persist = true); // for event
        bool RemoveVendorItem(uint32 entry, uint32 item, bool persist = true); // for event
        bool IsVendorItemValid(uint32 vendor_entry, uint32 item, int32 maxcount, uint32 ptime, uint32 ExtendedCost, Player* player = NULL, std::set<uint32>* skip_vendors = NULL, uint32 ORnpcflag = 0) const;

        void LoadScriptNames();
        ScriptNameContainer &GetScriptNames() { return _scriptNamesStore; }
        const char * GetScriptName(uint32 id) const { return id < _scriptNamesStore.size() ? _scriptNamesStore[id].c_str() : ""; }
        uint32 GetScriptId(const char *name);

        SpellClickInfoMapBounds GetSpellClickInfoMapBounds(uint32 creature_id) const
        {
            return _spellClickInfoStore.equal_range(creature_id);
        }

        GossipMenusMapBounds GetGossipMenusMapBounds(uint32 uiMenuId) const
        {
            return _gossipMenusStore.equal_range(uiMenuId);
        }

        GossipMenusMapBoundsNonConst GetGossipMenusMapBoundsNonConst(uint32 uiMenuId)
        {
            return _gossipMenusStore.equal_range(uiMenuId);
        }

        GossipMenuItemsMapBounds GetGossipMenuItemsMapBounds(uint32 uiMenuId) const
        {
            return _gossipMenuItemsStore.equal_range(uiMenuId);
        }
        GossipMenuItemsMapBoundsNonConst GetGossipMenuItemsMapBoundsNonConst(uint32 uiMenuId)
        {
            return _gossipMenuItemsStore.equal_range(uiMenuId);
        }

        // for wintergrasp only
        GraveyardContainer GraveyardStore;

        static void AddLocaleString(std::string const& s, LocaleConstant locale, StringVector& data);
        static inline void GetLocaleString(const StringVector& data, int loc_idx, std::string& value)
        {
            if (data.size() > size_t(loc_idx) && !data[loc_idx].empty())
                value = data[loc_idx];
        }

        CharacterConversionMap FactionChangeAchievements;
        CharacterConversionMap FactionChangeItems;
        CharacterConversionMap FactionChangeQuests;
        CharacterConversionMap FactionChangeReputation;
        CharacterConversionMap FactionChangeSpells;
        CharacterConversionMap FactionChangeTitles;

        void LoadFactionChangeAchievements();
        void LoadFactionChangeItems();
        void LoadFactionChangeQuests();
        void LoadFactionChangeReputations();
        void LoadFactionChangeSpells();
        void LoadFactionChangeTitles();

    private:
        // first free id for selected id type
        uint32 _auctionId; // pussywizard: accessed by a single thread
        uint64 _equipmentSetGuid; // pussywizard: accessed by a single thread
        uint32 _itemTextId; // pussywizard: unused? xD
        uint32 _mailId; ACE_Thread_Mutex _mailIdMutex;
        uint32 _hiPetNumber; ACE_Thread_Mutex _hiPetNumberMutex;

        // first free low guid for selected guid type
        uint32 _hiCharGuid; // pussywizard: accessed by a single thread
        uint32 _hiCreatureGuid; ACE_Thread_Mutex _hiCreatureGuidMutex;
        uint32 _hiPetGuid; ACE_Thread_Mutex _hiPetGuidMutex;
        uint32 _hiVehicleGuid; ACE_Thread_Mutex _hiVehicleGuidMutex;
        uint32 _hiItemGuid; ACE_Thread_Mutex _hiItemGuidMutex;
        uint32 _hiGoGuid; ACE_Thread_Mutex _hiGoGuidMutex;
        uint32 _hiDoGuid; ACE_Thread_Mutex _hiDoGuidMutex;
        uint32 _hiCorpseGuid; ACE_Thread_Mutex _hiCorpseGuidMutex;
        uint32 _hiMoTransGuid; ACE_Thread_Mutex _hiMoTransGuidMutex;

        QuestMap _questTemplates;
        std::vector<Quest*> _questTemplatesFast; // pussywizard

        typedef UNORDERED_MAP<uint32, GossipText> GossipTextContainer;
        typedef UNORDERED_MAP<uint32, uint32> QuestAreaTriggerContainer;
        typedef std::set<uint32> TavernAreaTriggerContainer;

		/*WQCORE数据类型定义区开始*/
		xxCreatureTeleMap _xxCreatureTeleMap;
		xxItembMap _xxItembMap;
		xxnpcMap _xxnpcMap;
		xxItembuffMap _xxItembuffMap;
		xxPvpRankMap m_xxPvpRankMap;
		xxRaidMap m_xxRaidMap;
		xxRaidBoxMap m_xxRaidBoxMap;
		xxSuoyaoMap m_xxSuoyaoMap;
		xxTongtianMap m_xxTongtianMap;
		xxSuoMap m_xxSuoMap;
		xxTongMap m_xxTongMap;
		xxHuoliMap m_xxHuoliMap;
		xxfuyin m_xxfuyinmap;
		xxyuyi m_xxyuyimap;
		xxjntp m_xxjntpmap;
		xxjnjx m_xxjnjxmap;
		xxjnpy m_xxjnpymap;
		xxcjjf m_xxcjjfmap;
		xxcjzjf m_xxcjzjfmap;
		xxcjzzjf m_xxcjzzjfmap;
		xxVipSystemMap _xxVipSystemMap;
		xxVipSystemMrMap _xxVipSystemMrMap;
		xxItemupMap _xxItemupMap;
		xxBattleMap _xxBattleMap;
		xxItemTeleMap _xxItemTeleMap;
		xxSkillMap m_xxSkillMap;
		xxItemMap _xxItemMap;
		xxItemiccMap _xxItemiccMap;
		xxItemcjMap _xxItemcjMap;
		xxItemzhMap _xxItemzhMap;
		uint32 isboss[204800];

        QuestAreaTriggerContainer _questAreaTriggerStore;
        TavernAreaTriggerContainer _tavernAreaTriggerStore;
        GossipTextContainer _gossipTextStore;
        AreaTriggerContainer _areaTriggerStore;
        AreaTriggerScriptContainer _areaTriggerScriptStore;
        AccessRequirementContainer _accessRequirementStore;
        DungeonEncounterContainer _dungeonEncounterStore;

        RepRewardRateContainer _repRewardRateStore;
        RepOnKillContainer _repOnKillStore;
        RepSpilloverTemplateContainer _repSpilloverTemplateStore;

        GossipMenusContainer _gossipMenusStore;
        GossipMenuItemsContainer _gossipMenuItemsStore;
        PointOfInterestContainer _pointsOfInterestStore;

        QuestPOIContainer _questPOIStore;

        QuestRelations _goQuestRelations;
        QuestRelations _goQuestInvolvedRelations;
        QuestRelations _creatureQuestRelations;
        QuestRelations _creatureQuestInvolvedRelations;

        //character reserved names
        typedef std::set<std::wstring> ReservedNamesContainer;
        ReservedNamesContainer _reservedNamesStore;

        GameTeleContainer _gameTeleStore;

        ScriptNameContainer _scriptNamesStore;

        SpellClickInfoContainer _spellClickInfoStore;

        SpellScriptsContainer _spellScriptsStore;

        VehicleAccessoryContainer _vehicleTemplateAccessoryStore;
        VehicleAccessoryContainer _vehicleAccessoryStore;

        LocaleConstant DBCLocaleIndex;

        PageTextContainer _pageTextStore;
        InstanceTemplateContainer _instanceTemplateStore;

    private:
        void LoadScripts(ScriptsType type);
        void CheckScripts(ScriptsType type, std::set<int32>& ids);
        void LoadQuestRelationsHelper(QuestRelations& map, std::string const& table, bool starter, bool go);
        void PlayerCreateInfoAddItemHelper(uint32 race_, uint32 class_, uint32 itemId, int32 count);

        MailLevelRewardContainer _mailLevelRewardStore;

        CreatureBaseStatsContainer _creatureBaseStatsStore;

        typedef std::map<uint32, PetLevelInfo*> PetLevelInfoContainer;
        // PetLevelInfoContainer[creature_id][level]
        PetLevelInfoContainer _petInfoStore;                            // [creature_id][level]

        PlayerClassInfo* _playerClassInfo[MAX_CLASSES];

        void BuildPlayerLevelInfo(uint8 race, uint8 class_, uint8 level, PlayerLevelInfo* plinfo) const;

        PlayerInfo* _playerInfo[MAX_RACES][MAX_CLASSES];

        typedef std::vector<uint32> PlayerXPperLevel;       // [level]
        PlayerXPperLevel _playerXPperLevel;

        typedef std::map<uint32, uint32> BaseXPContainer;          // [area level][base xp]
        BaseXPContainer _baseXPTable;

        typedef std::map<uint32, int32> FishingBaseSkillContainer; // [areaId][base skill level]
        FishingBaseSkillContainer _fishingBaseForAreaStore;

        typedef std::map<uint32, StringVector> HalfNameContainer;
        HalfNameContainer _petHalfName0;
        HalfNameContainer _petHalfName1;

        typedef UNORDERED_MAP<uint32, ItemSetNameEntry> ItemSetNameContainer;
        ItemSetNameContainer _itemSetNameStore;

        MapObjectGuids _mapObjectGuidsStore;
        CellObjectGuidsMap _emptyCellObjectGuidsMap;
        CellObjectGuids _emptyCellObjectGuids;
        CreatureDataContainer _creatureDataStore;
        CreatureTemplateContainer _creatureTemplateStore;
        std::vector<CreatureTemplate*> _creatureTemplateStoreFast; // pussywizard
        CreatureModelContainer _creatureModelStore;
        CreatureAddonContainer _creatureAddonStore;
        CreatureAddonContainer _creatureTemplateAddonStore;
        GameObjectAddonContainer _gameObjectAddonStore;
        GameObjectQuestItemMap _gameObjectQuestItemStore;
        CreatureQuestItemMap _creatureQuestItemStore;
        EquipmentInfoContainer _equipmentInfoStore;
        LinkedRespawnContainer _linkedRespawnStore;
        CreatureLocaleContainer _creatureLocaleStore;
        GameObjectDataContainer _gameObjectDataStore;
        GameObjectLocaleContainer _gameObjectLocaleStore;
        GameObjectTemplateContainer _gameObjectTemplateStore;
        /// Stores temp summon data grouped by summoner's entry, summoner's type and group id
        TempSummonDataContainer _tempSummonDataStore;

        BroadcastTextContainer _broadcastTextStore;
        ItemTemplateContainer _itemTemplateStore;
        std::vector<ItemTemplate*> _itemTemplateStoreFast; // pussywizard
        ItemLocaleContainer _itemLocaleStore;
        ItemSetNameLocaleContainer _itemSetNameLocaleStore;
        QuestLocaleContainer _questLocaleStore;
        NpcTextLocaleContainer _npcTextLocaleStore;
        PageTextLocaleContainer _pageTextLocaleStore;
        TrinityStringLocaleContainer _trinityStringLocaleStore;
        GossipMenuItemsLocaleContainer _gossipMenuItemsLocaleStore;
        PointOfInterestLocaleContainer _pointOfInterestLocaleStore;

        CacheVendorItemContainer _cacheVendorItemStore;
        CacheTrainerSpellContainer _cacheTrainerSpellStore;

        std::set<uint32> _difficultyEntries[MAX_DIFFICULTY - 1]; // already loaded difficulty 1 value in creatures, used in CheckCreatureTemplate
        std::set<uint32> _hasDifficultyEntries[MAX_DIFFICULTY - 1]; // already loaded creatures with difficulty 1 values, used in CheckCreatureTemplate

        enum CreatureLinkedRespawnType
        {
            CREATURE_TO_CREATURE,
            CREATURE_TO_GO,         // Creature is dependant on GO
            GO_TO_GO,
            GO_TO_CREATURE,         // GO is dependant on creature
        };

        std::set<uint32> _transportMaps; // Helper container storing map ids that are for transports only, loaded from gameobject_template
};

#define sObjectMgr ACE_Singleton<ObjectMgr, ACE_Null_Mutex>::instance()

// scripting access functions
bool LoadTrinityStrings(char const* table, int32 start_value = MAX_CREATURE_AI_TEXT_STRING_ID, int32 end_value = std::numeric_limits<int32>::min());

#endif
