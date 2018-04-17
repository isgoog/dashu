#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "Chat.h"
#include "Spell.h"
#include "Battleground.h"
#include "ReputationMgr.h"
#include "Guild.h"
#include <unordered_map>
#include <cstring>
//#include "CustomVendor.h"

#pragma execution_character_set("utf-8")

enum ZidingyiEvents
{
	EVENT_SPELL_1 = 1,
	EVENT_SPELL_2,
	EVENT_SPELL_3,
	EVENT_SPELL_SOUL_FLAY,
	EVENT_SPELL_BERSERK,
};

class Duel_Reset : public PlayerScript
{
public:
	Duel_Reset() : PlayerScript("Duel_Reset"){}
	bool UsingPreDuelInfo = false; // CHange this to false if you want a full reset.

	struct MyData
	{
		uint64 resethealth;
		uint64 resetPower;
		uint64 resetEnergy;
		uint64 resetRage;
	};

	std::unordered_map<uint64, MyData> playerData;
	void GetInfoPreDuel(Player* playerwin, Player* playerlose)
	{
		playerData[playerwin->GetGUID()].resethealth = playerwin->GetHealth();
		playerData[playerwin->GetGUID()].resetPower = playerwin->GetPower(playerwin->getPowerType());
		playerData[playerlose->GetGUID()].resethealth = playerlose->GetHealth();
		playerData[playerlose->GetGUID()].resetPower = playerlose->GetPower(playerlose->getPowerType());

	}
	void DoFullReset(Player* playerwin, Player* playerlose)
	{
		playerData[playerwin->GetGUID()].resethealth = playerwin->GetMaxHealth();
		playerData[playerwin->GetGUID()].resetPower = playerwin->GetMaxPower(playerlose->getPowerType());
		playerData[playerlose->GetGUID()].resethealth = playerlose->GetMaxHealth();
		playerData[playerlose->GetGUID()].resetPower = playerlose->GetMaxPower(playerwin->getPowerType());
	}

	void OnDuelStart(Player* playerwin, Player* playerlose)
	{
		if (!UsingPreDuelInfo)
		{
			DoFullReset(playerwin, playerlose);
		}
		if (UsingPreDuelInfo)
		{
			GetInfoPreDuel(playerwin, playerlose);
		}
	}

	void OnDuelEnd(Player* playerwin, Player* playerlose, DuelCompleteType /*type*/)
	{
		playerwin->SetHealth(playerData[playerwin->GetGUID()].resethealth);
		playerwin->SetPower(playerwin->getPowerType(), playerData[playerwin->GetGUID()].resetPower);
		playerlose->SetHealth(playerData[playerlose->GetGUID()].resethealth);
		playerlose->SetPower(playerlose->getPowerType(), playerData[playerlose->GetGUID()].resetPower);

		if (!UsingPreDuelInfo)
		{
			playerwin->GetSession()->SendAreaTriggerMessage("你的血蓝技能CD 已重置.");
			playerlose->GetSession()->SendAreaTriggerMessage("你的血蓝技能CD 已重置.");
			playerwin->RemoveAllSpellCooldown();
			playerlose->RemoveAllSpellCooldown();
		}
		else
		{
			playerwin->GetSession()->SendAreaTriggerMessage("Your Health & Mana has been reset to what they were before the duel!");
			playerlose->GetSession()->SendAreaTriggerMessage("Your Health & Mana has been reset to what they were before the duel!");
		}
		playerData.erase(playerwin->GetGUID());
		playerData.erase(playerlose->GetGUID());
	}
};

class xx_npc_trainer1 : public CreatureScript
{
public:
	xx_npc_trainer1() : CreatureScript("xx_npc_chuansong") {}
	bool OnUse(Player* player, Creature* creature, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat())
		{
			OnGossipHello(player, creature);
			return true;
		}
		else
		{
			player->ClearInCombat();
			return false;
		}
	}


	bool OnGossipHello(Player* player, Creature* pcreature)
	{
		sObjectMgr->LoadxxCreatureTeleportMenu(0, player, pcreature);
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* pcreature, uint32 uiSender, uint32 uiAction)
	{

		sObjectMgr->RunxxCreatureTeleport(uiAction, uiSender, player, pcreature);
		return true;
	}
};

class npc_additem : public CreatureScript
{
public:
	npc_additem() : CreatureScript("xx_npc_additem") { }

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
	{
		pPlayer->PlayerTalkClass->ClearMenus();
		std::stringstream ss("");
		ss << "|cff008000幻化物品售价：" << sWorld->getIntConfig(ZY_HUANHUA_JF) << sObjectMgr->GetItemNameLink(sWorld->getIntConfig(CORE_JF_ID));
		pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);
		ss.str("");
		ss << "|cff008000获取方式：输入想要幻化的物品ID，物品直接发放到您的背包";
		pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
		ss.str("");
		ss << "|cffFF0000查询方式：查询ID可打开网页|nhttp://db.178.com/wow/";
		pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);
		ss.str("");
		ss << "|cffFF0000输入物品名字，点击搜索，鼠标箭头悬停在物品名称上，即可看到物品ID";
		pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);
		ss.str("");
		ss << "|cffFF0000复制网站链接请到群公告查询";
		pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
		pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "点击输入物品ID", GOSSIP_SENDER_MAIN, 1000 + 1, "", 0, true);

		pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());

		return true;
	}

	bool OnGossipSelectCode(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction, const char* code)
	{
		player->PlayerTalkClass->ClearMenus();
		if (uiSender == GOSSIP_SENDER_MAIN)
		{
			uint32 a = 0;
			uint32 b = 0;
			switch (uiAction)
			{
			case 1001:
				std::string name(code);
				if (!name.empty())
					a = atoi(name.c_str());
				ItemTemplate const* proto = sObjectMgr->GetItemTemplate(a);
				if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_HUANHUA_JF))
				{
				
				if (a == 0 && !proto)
				{
					player->GetSession()->SendAreaTriggerMessage("你输入的物品ID不正确");
				}
				else
				{
					b = sObjectMgr->ShowItemSpawn(a);
					if (b == 0)
					{
					     player->GetSession()->SendAreaTriggerMessage("你输入的物品ID不存在");
					}
					else
					{
						player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_HUANHUA_JF), true);
						player->AddItem(b, 1);
					}
					    
				}
				}
				else
				{
					player->GetSession()->SendAreaTriggerMessage("不满足购买条件");
				}
				
				//ChatHandler handler(player->GetSession());
				//arena_spectator_commands::HandleSpectateCommand(&handler, name.c_str());

				return true;
			}
		}

		return false;
	}
};

class xx_npc_trainer : public CreatureScript
{
public:
	xx_npc_trainer() : CreatureScript("xx_npc_trainer") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_WorldEvent_Reindeer.blp:24|t学习双天赋", 1, 1000 + 2);
		player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\INV_Ingot_Titansteel_blue.blp:24|t重置技能天赋", 1, 1000 + 6);
		player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\INV_Glyph_MajorShaman.blp:24|t清除所有雕文", 1, 1000 + 7);
		player->PlayerTalkClass->SendGossipMenu(907, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		uint32 NPCID = 0;
		switch (uiAction)
		{
		case 1000 + 2:	// 双天赋
			if (player->GetSpecsCount() == 1 && player->getLevel() >= sWorld->getIntConfig(CONFIG_MIN_DUALSPEC_LEVEL))
			{
				// Cast spells that teach dual spec
				// Both are also ImplicitTarget self and must be cast by player
				player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
				player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());

				// Should show another Gossip text with "Congratulations..."
				player->PlayerTalkClass->SendCloseGossip();
			}
			//player->PlayerTalkClass->SendCloseGossip();
			return true;
		case 1000 + 6:    // 重置职业天赋
			player->resetTalents(true);
			player->InitTalentForLevel();
			player->SendTalentsInfoData(false);
			player->PlayerTalkClass->SendCloseGossip();
			ChatHandler(player).PSendSysMessage("重置角色天赋成功.");
			return true;
		case 1000 + 7:	// 清除所有雕文
			for (int slot = 0; slot < MAX_GLYPH_SLOT_INDEX; ++slot)
			{
				if (uint32 glyph = player->GetGlyph(slot))
				{
					if (GlyphPropertiesEntry const *gp = sGlyphPropertiesStore.LookupEntry(glyph))
					{
						player->RemoveAurasDueToSpell(gp->SpellId);
						player->SetGlyph(slot, 0, true);
						player->SendTalentsInfoData(false);
					}
				}
			}
			player->PlayerTalkClass->SendCloseGossip();
			return true;
		case 1000 + 8:	// 再见
			player->PlayerTalkClass->SendCloseGossip();
			return true;

		}
	}

};

class xx_item_teleport : public ItemScript
{
public:
	xx_item_teleport() : ItemScript("xx_item_teleport") {}
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat() || !player->GetBattleground())
		{
			OnGossipHello(player, item);
			return true;
		}
		else
		{
			player->CastSpell(player, 41592, true);
			player->ClearInCombat();
			return false;
		}
	}


	bool OnGossipHello(Player* player, Item* pitem)
	{
		sObjectMgr->LoadxxItemTeleportMenu(0, player, pitem);
		return true;
	}

	bool OnGossipSelect1(Player* player, Item* pitem, uint32 uiSender, uint32 uiAction)
	{
		sObjectMgr->RunxxItemTeleport(uiAction, uiSender, player, pitem);
		return true;
	}
};

class xx_item_upgrade : public ItemScript
{
public:
	xx_item_upgrade() : ItemScript("xx_itemup") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat() && item->GetTemplate()->Spells[0].SpellId == 13262)
		{

			if (!targets.GetItemTarget())
				return true;

			if (player->GetItemByPos(targets.GetItemTarget()->GetPos()) != targets.GetItemTarget())
				return true;

			if (targets.GetItemTarget() && item)
			{
				uint32 ItemID = targets.GetItemTarget()->GetEntry();
				player->UpgradeSetFromItem(item);
				player->UpgradeSetTargetItem(targets.GetItemTarget());
				sObjectMgr->ShowUpgradeMenu(item, targets.GetItemTarget(), player);
				return true;
			}
		}
		return true;
	}

	bool OnGossipSelect1(Player* player, Item* pitem, uint32 uiSender, uint32 uiAction)
	{
		if (!player->UpgradeGetTargetItem() || !player->UpgradeGetFromItem())
			return true;

		if (uiAction == 1000)
			sObjectMgr->UpgradeThisItem(player->UpgradeGetTargetItem(), player, player->UpgradeGetFromItem());
		return true;
	}
};

class xx_fuyin_stone : public ItemScript
{
public:
	xx_fuyin_stone() : ItemScript("xx_fuyin_stone"){}
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat())
		{
			OnGossipHello(player, item);
			return true;
		}
		return true;
	}

	bool OnGossipHello(Player* player, Item* pitem)
	{
		sObjectMgr->ShowFuyinMenu(player, pitem);
		return true;
	}

	bool OnGossipSelect1(Player* player, Item* pitem, uint32 uiSender, uint32 uiAction)
	{
		//sObjectMgr->Updatefuyintc(player, pitem, uiSender, uiAction);
		sObjectMgr->Updatefuyin(player, pitem, uiAction);
		//sObjectMgr->Runxxfuyin(uiAction, uiSender, player, pitem);
		return true;
	}
};

class xx_item_gradecj : public ItemScript
{
public:
	xx_item_gradecj() : ItemScript("xx_itemcj") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat() && item->GetTemplate()->Spells[0].SpellId == 13262)
		{

			if (!targets.GetItemTarget())
				return true;

			if (player->GetItemByPos(targets.GetItemTarget()->GetPos()) != targets.GetItemTarget())
				return true;

			if (targets.GetItemTarget() && item)
			{
				uint32 ItemID = targets.GetItemTarget()->GetEntry();
				player->UpgradeSetFromItem(item);
				player->UpgradeSetTargetItem(targets.GetItemTarget());
				sObjectMgr->ShowCjgradeMenu(item, targets.GetItemTarget(), player);
				return true;
			}
		}
		return true;
	}

	bool OnGossipSelect1(Player* player, Item* pitem, uint32 uiSender, uint32 uiAction)
	{
		if (!player->UpgradeGetTargetItem() || !player->UpgradeGetFromItem())
			return true;

		if (uiAction == 1000)
			sObjectMgr->UpgradeThisItemcj(player->UpgradeGetTargetItem(), player, player->UpgradeGetFromItem());
		return true;
	}
};

class xx_item_gradezh : public ItemScript
{
public:
	xx_item_gradezh() : ItemScript("xx_itemzh") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat() && item->GetTemplate()->Spells[0].SpellId == 13262)
		{

			if (!targets.GetItemTarget())
				return true;

			if (player->GetItemByPos(targets.GetItemTarget()->GetPos()) != targets.GetItemTarget())
				return true;

			if (targets.GetItemTarget() && item)
			{
				uint32 ItemID = targets.GetItemTarget()->GetEntry();
				player->UpgradeSetFromItem(item);
				player->UpgradeSetTargetItem(targets.GetItemTarget());
				sObjectMgr->ShowZhgradeMenu(item, targets.GetItemTarget(), player);
				return true;
			}
		}
		return true;
	}

	bool OnGossipSelect1(Player* player, Item* pitem, uint32 uiSender, uint32 uiAction)
	{
		if (!player->UpgradeGetTargetItem() || !player->UpgradeGetFromItem())
			return true;

		if (uiAction == 1000)
			sObjectMgr->UpgradeThisItemzh(player->UpgradeGetTargetItem(), player, player->UpgradeGetFromItem());
		return true;
	}
};

class xx_suoyaoshi : public ItemScript
{
public:
	xx_suoyaoshi() : ItemScript("xx_suoyaoshi") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!item)
			return false;

		if (!player->IsInCombat())
		{
			if (player->GetTTcishu() > 0)
			{
				if (player->GetMapId() != 650)
				{
					player->SetTTcishu(0);
					player->SetTTsaodang(0);
					player->DestroyItemCount(item->GetEntry(), 1, true);
				}
				else
				{
					ChatHandler(player).PSendSysMessage("无法在锁妖塔副本中使用");
				}
			}
			else
			{
				ChatHandler(player).PSendSysMessage("您目前可挑战锁妖塔无需使用");
			}
			return true;
		}
		else
		{
			ChatHandler(player).PSendSysMessage("战斗中无法使用");
			return true;
		}
		
	}
};

class spell_fuhuo : public SpellScriptLoader
{
public:
	spell_fuhuo() : SpellScriptLoader("spell_fuhuo") { }

	class spell_fuhuo_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_fuhuo_SpellScript);

		void ConsumeReagents()
		{
			if (Player* player = GetCaster()->ToPlayer())
				player->DestroyItemCount(sWorld->getIntConfig(FUHUOITEM), 1, true);
		}

		void Register() override
		{
			
			OnCast += SpellCastFn(spell_fuhuo_SpellScript::ConsumeReagents);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_fuhuo_SpellScript();
	}
};

class xx_npc_lingqu : public CreatureScript
{
public:
	xx_npc_lingqu() : CreatureScript("xx_npc_lingqu") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		
		if (player->GetItemCount(26, false) >= 1)
		{
			player->PlayerTalkClass->ClearMenus();

			switch (player->getClass())
			{
			case 1: // 战士
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-战士", 1, 1000 + 10);
				break;
			case 2: // 骑士
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-骑士", 1, 1000 + 10);
				break;
			case 3:	// 猎人
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-猎人", 1, 1000 + 10);
				break;
			case 4: // 潜行者
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-盗贼", 1, 1000 + 10);
				break;
			case 5: // 牧师
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-牧师", 1, 1000 + 10);
				break;
			case 6: // 死骑
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-死骑", 1, 1000 + 10);
				break;
			case 7: // 萨满
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-萨满", 1, 1000 + 10);
				break;
			case 8: // 法师
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-法师", 1, 1000 + 10);
				break;
			case 9: // 术士
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-术士", 1, 1000 + 10);
				break;
			case 11: // 德鲁伊
				player->ADD_GOSSIP_ITEM(0, "|TInterface\\ICONS\\Achievement_BG_winSOA_underXminutes.blp:24|t点击领取出生装备-小德", 1, 1000 + 10);
				break;
			}
			player->PlayerTalkClass->SendGossipMenu(60002, creature->GetGUID());
			return true;
		}
		else
		{
			player->PlayerTalkClass->SendGossipMenu(60002, creature->GetGUID());
			return false;
		}
		
		
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		uint32 NPCID = 0;
		switch (uiAction)
		{
		case 1000 + 10:
			switch (player->getClass())
			{
			case 1: // 战士
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200114, 2);
				player->AddItem(200117, 1);
				player->AddItem(200131, 1);
				player->AddItem(200122, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200111, 1);
				player->AddItem(200112, 1);
				player->AddItem(200113, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200001, 1);
				player->AddItem(200002, 1);
				player->AddItem(200003, 1);
				player->AddItem(200004, 1);
				player->AddItem(200005, 1);
				player->AddItem(200006, 1);
				player->AddItem(200007, 1);
				player->AddItem(200008, 1);
				player->AddItem(200009, 1);
				player->AddItem(200010, 1);
				player->AddItem(200133, 1);
				break;
			case 2: // 骑士
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200114, 2);
				player->AddItem(200118, 1);
				player->AddItem(200123, 1);
				player->AddItem(200127, 1);
				player->AddItem(200131, 1);
				player->AddItem(200122, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200111, 1);
				player->AddItem(200112, 1);
				player->AddItem(200113, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200046, 1);
				player->AddItem(200047, 1);
				player->AddItem(200048, 1);
				player->AddItem(200049, 1);
				player->AddItem(200050, 1);
				player->AddItem(200051, 1);
				player->AddItem(200052, 1);
				player->AddItem(200053, 1);
				player->AddItem(200054, 1);
				player->AddItem(200055, 1);
				player->AddItem(200056, 1);
				player->AddItem(200057, 1);
				player->AddItem(200058, 1);
				player->AddItem(200059, 1);
				player->AddItem(200060, 1);
				player->AddItem(200133, 1);
				break;
			case 3:	// 猎人
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200116, 2);
				player->AddItem(200117, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200108, 1);
				player->AddItem(200109, 1);
				player->AddItem(200110, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200066, 1);
				player->AddItem(200067, 1);
				player->AddItem(200068, 1);
				player->AddItem(200069, 1);
				player->AddItem(200070, 1);
				break;
			case 4: // 潜行者
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200120, 2);
				player->AddItem(200121, 1);
				player->AddItem(200122, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200105, 1);
				player->AddItem(200106, 1);
				player->AddItem(200107, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200031, 1);
				player->AddItem(200032, 1);
				player->AddItem(200033, 1);
				player->AddItem(200034, 1);
				player->AddItem(200035, 1);
				player->AddItem(200117, 1);
				player->AddItem(200132, 1);
				break;
			case 5: // 牧师
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200115, 2);
				player->AddItem(200118, 1);
				player->AddItem(200123, 1);
				player->AddItem(200124, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200102, 1);
				player->AddItem(200103, 1);
				player->AddItem(200104, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200036, 1);
				player->AddItem(200037, 1);
				player->AddItem(200038, 1);
				player->AddItem(200039, 1);
				player->AddItem(200040, 1);
				player->AddItem(200041, 1);
				player->AddItem(200042, 1);
				player->AddItem(200043, 1);
				player->AddItem(200044, 1);
				player->AddItem(200045, 1);
				break;
			case 6: // 死骑
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200114, 2);
				player->AddItem(200130, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200111, 1);
				player->AddItem(200112, 1);
				player->AddItem(200113, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200086, 1);
				player->AddItem(200087, 1);
				player->AddItem(200088, 1);
				player->AddItem(200089, 1);
				player->AddItem(200090, 1);
				player->AddItem(200091, 1);
				player->AddItem(200092, 1);
				player->AddItem(200093, 1);
				player->AddItem(200094, 1);
				player->AddItem(200095, 1);
				player->AddItem(200120, 2);
				break;
			case 7: // 萨满
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200115, 2);
				player->AddItem(200118, 1);
				player->AddItem(200121, 2);
				player->AddItem(200123, 1);
				player->AddItem(200129, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200108, 1);
				player->AddItem(200109, 1);
				player->AddItem(200110, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200016, 1);
				player->AddItem(200017, 1);
				player->AddItem(200018, 1);
				player->AddItem(200019, 1);
				player->AddItem(200020, 1);
				player->AddItem(200021, 1);
				player->AddItem(200022, 1);
				player->AddItem(200023, 1);
				player->AddItem(200024, 1);
				player->AddItem(200025, 1);
				player->AddItem(200026, 1);
				player->AddItem(200027, 1);
				player->AddItem(200028, 1);
				player->AddItem(200029, 1);
				player->AddItem(200030, 1);
				break;
			case 8: // 法师
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200115, 2);
				player->AddItem(200124, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200102, 1);
				player->AddItem(200103, 1);
				player->AddItem(200104, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200061, 1);
				player->AddItem(200062, 1);
				player->AddItem(200063, 1);
				player->AddItem(200064, 1);
				player->AddItem(200065, 1);
				break;
			case 9: // 术士
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200115, 2);
				player->AddItem(200124, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200102, 1);
				player->AddItem(200103, 1);
				player->AddItem(200104, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200011, 1);
				player->AddItem(200012, 1);
				player->AddItem(200013, 1);
				player->AddItem(200014, 1);
				player->AddItem(200015, 1);
				break;
			case 11: // 德鲁伊
				player->DestroyItemCount(26, 1, true);
				player->AddItem(200115, 2);
				player->AddItem(200116, 2);
				player->AddItem(200118, 1);
				player->AddItem(200123, 1);
				player->AddItem(200128, 1);
				player->AddItem(200125, 1);
				player->AddItem(200126, 1);
				player->AddItem(200105, 1);
				player->AddItem(200106, 1);
				player->AddItem(200107, 1);
				player->AddItem(200101, 1);
				player->AddItem(200100, 1);
				player->AddItem(200096, 1);
				player->AddItem(200097, 1);
				player->AddItem(200098, 1);
				player->AddItem(200099, 1);
				player->AddItem(200071, 1);
				player->AddItem(200072, 1);
				player->AddItem(200073, 1);
				player->AddItem(200074, 1);
				player->AddItem(200075, 1);
				player->AddItem(200076, 1);
				player->AddItem(200077, 1);
				player->AddItem(200078, 1);
				player->AddItem(200079, 1);
				player->AddItem(200080, 1);
				player->AddItem(200081, 1);
				player->AddItem(200082, 1);
				player->AddItem(200083, 1);
				player->AddItem(200084, 1);
				player->AddItem(200085, 1);
				break;
			}
		}
		return true;

	}

};

class boss_zidingyi : public CreatureScript
{
public:
	boss_zidingyi() : CreatureScript("boss_zidingyi") { }

	struct boss_zidingyiAI : public ScriptedAI
	{
		boss_zidingyiAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			pInstance = pCreature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		EventMap events;
		void Reset()
		{
			events.Reset();

		}

		void EnterCombat(Unit* who)
		{
			events.Reset();
			
			if (me->GetEntry() <= 98005)
			{
				me->CastSpell(me, 934001, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
			}
			else if (me->GetEntry() > 98005 && me->GetEntry() <= 98010)
			{
				me->CastSpell(me, 934002, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
			}
			else if (me->GetEntry() > 98010 && me->GetEntry() <= 98015)
			{
				me->CastSpell(me, 934003, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
				events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			}
			else if (me->GetEntry() > 98015 && me->GetEntry() <= 98020)
			{
				me->CastSpell(me, 934004, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
				events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			}
			else if (me->GetEntry() > 98020 && me->GetEntry() <= 98025)
			{
				me->CastSpell(me, 934005, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
				events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			}
			else if (me->GetEntry() > 98025 && me->GetEntry() <= 98030)
			{
				me->CastSpell(me, 934006, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
				events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			}
			else if (me->GetEntry() > 98030 && me->GetEntry() <= 98035)
			{
				me->CastSpell(me, 934007, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
				events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			}
			else if (me->GetEntry() > 98035 && me->GetEntry() <= 98040)
			{
				me->CastSpell(me, 934008, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
				events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			}
			else if (me->GetEntry() > 98040 && me->GetEntry() <= 98045)
			{
				me->CastSpell(me, 934009, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
				events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			}
			else if (me->GetEntry() > 98045)
			{
				me->CastSpell(me, 934010, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
				events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			}
			   
			
			

		}

		void JustDied(Unit* killer)
		{
			uint32 a = urand(1, 100);
			if (a >= 95)
			{
				//me->SummonCreature(70004, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 180);
				me->CastSpell((Unit*)NULL, 938001, true);
				char buff[2048];
				sprintf(buff, "|CFF00FF00【隐藏商人】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,隐藏商人出现了~|r", killer->GetName(), killer->GetName(), me->GetName());
				sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
			}
			//sLog->outString("JustDied  (%u)", a);
		}

		uint32 DoSpellCasta(uint32 BossSpell)
		{
			switch (BossSpell)
			{
			case 0:
				return 24573;//致死打击-释放
			case 1:
				return 75418;//震荡波-释放
			case 2:
				return 60899;//击飞-释放
			case 3:
				return 71001;//凋零-释放
			case 4:
				return 59192;//仇恨打击-释放
			case 5:
				return 66012;//寒冰打击-释放
			default:
				return 0;
			}
		}

		uint32 DoSpellCastb(uint32 BossSpell)
		{
			switch (BossSpell)
			{
			case 0:
				return 62910;//咪咪-释放
			case 1:
				return 71058;//冰霜吐息-释放
			case 2:
				return 75956;//黑暗吐息
			case 3:
				return 57544;//灰烬使者-释放
			case 4:
				return 22247;//镇压光环-释放
			default:
				return 0;
			}
		}

		uint32 DoSpellCastc(uint32 BossSpell)
		{
			switch (BossSpell)
			{
			case 0:
				return 935001;//升天-释放
			case 1:
				return 32309;//酸液箭释放
			case 2:
				return 935002;//巫妖王之怒-释放
			case 3:
				return 935001;//升天-释放
			default:
				return 0;
			}
		}

		void UpdateAI(uint32 diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			switch (events.GetEvent())
			{
			case 0:
				break;
			case EVENT_SPELL_1:
				me->CastSpell(me->GetVictim(), DoSpellCasta(urand(0, 5)), false);
				events.RepeatEvent(urand(10000, 12000));
				break;
			case EVENT_SPELL_2:
				me->CastSpell(me->GetVictim(), DoSpellCastb(urand(0, 4)), false);
				events.RepeatEvent(urand(14000, 16000));
				break;
			case EVENT_SPELL_3:
				me->CastSpell((Unit*)NULL, DoSpellCastc(urand(0, 3)), false);
				events.RepeatEvent(urand(18000, 22000));
				break;
			}

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new boss_zidingyiAI(pCreature);
	}
};

class npc_world : public CreatureScript
{
public:
	npc_world() : CreatureScript("xx_npc_world") { }

	bool OnGossipHello(Player* pPlayer, Creature* pCreature)
	{
		pPlayer->PlayerTalkClass->ClearMenus();
		std::stringstream ss("");
		
		ss << "|cff008000-------------------------------";
		pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);
		if (pCreature->GetMapId() == 37)
		{
			ss.str("");
			ss << "|cFF0000FF点击查看积雪平原野外首领刷新状态";
			pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(30, 0, ss.str().c_str(), 0, 1004, "", 0);
		}
		else
		{
			ss.str("");
			ss << "|cFF0000FF点击查看初级野外首领刷新状态";
			pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			ss.str("");
			ss << "|cFF0000FF点击查看中级野外首领刷新状态";
			pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			ss.str("");
			ss << "|cFF0000FF点击查看高级野外首领刷新状态";
			pPlayer->PlayerTalkClass->GetGossipMenu().AddMenuItem(29, 0, ss.str().c_str(), 0, 1003, "", 0);
		}
		

		pPlayer->PlayerTalkClass->SendGossipMenu(60003, pCreature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* pcreature, uint32 uiSender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (uiAction)
		{
		case 1001:
			sObjectMgr->ShowBossSpawn(player, pcreature,1);
			return true;
		case 1002:
			sObjectMgr->ShowBossSpawn(player, pcreature,2);
			return true;
		case 1003:
			sObjectMgr->ShowBossSpawn(player, pcreature,3);
			return true;
		case 1004:
			sObjectMgr->ShowBossSpawn(player, pcreature, 4);
			return true;
		}

	}
};

class spell_wuli : public SpellScriptLoader
{
public:
	spell_wuli() : SpellScriptLoader("spell_wuli") { }

	class spell_wuli_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_wuli_SpellScript);

		void CalculateDamage(SpellEffIndex /*effIndex*/)
		{
			float a = 0.3f * float(GetCaster()->GetTotalStatValue(STAT_STRENGTH));
			float b = 0.3f * float(GetCaster()->GetTotalStatValue(STAT_AGILITY));
			float c = 0.3f * float(GetCaster()->GetTotalStatValue(STAT_INTELLECT));
			float d = std::max(a, b);
			//float distance = std::max(0.3f * float(GetCaster()->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask())), 0.3f * float(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK)));
			float distance = std::max(c, d);

				SetHitDamage(int32(GetHitDamage() + distance));
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_wuli_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_wuli_SpellScript();
	}
};

class spell_shenji : public SpellScriptLoader
{
public:
	spell_shenji() : SpellScriptLoader("spell_shenji") { }

	class spell_shenji_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_shenji_SpellScript);

		void CalculateDamage(SpellEffIndex /*effIndex*/)
		{
			float tp = float(GetCaster()->GetJntp() + 1) / 100.0f;
			uint32 jx = GetCaster()->GetJnjx() * 10000;
			uint32 py = GetCaster()->GetJnpy() * 1000;
			float a = tp * float(GetCaster()->GetTotalStatValue(STAT_STRENGTH));
			float b = tp * float(GetCaster()->GetTotalStatValue(STAT_AGILITY));
			float c = tp * float(GetCaster()->GetTotalStatValue(STAT_INTELLECT));
			float d = std::max(a, b);
			//float distance = std::max(0.3f * float(GetCaster()->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask())), 0.3f * float(GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK)));
			float distance = std::max(c, d);

			SetHitDamage(int32(GetHitDamage() + jx + py + distance));
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_shenji_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_shenji_SpellScript();
	}
};

class xx_fuyinshi : public ItemScript
{
public:
	xx_fuyinshi() : ItemScript("xx_fuyinshi") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!item)
			return false;

		if (!player->IsInCombat())
		{
			if (item->GetEntry() == 60011)
			{
				player->ModifyFuyin(1);
				ChatHandler(player).PSendSysMessage("获得符印点数：1");
				player->DestroyItemCount(item->GetEntry(), 1, true);
				return true;
			}
			else if (item->GetEntry() == 60012)
			{
				player->ModifyFuyin(2);
				ChatHandler(player).PSendSysMessage("获得符印点数：2");
				player->DestroyItemCount(item->GetEntry(), 1, true);
				return true;
			}
			else if (item->GetEntry() == 60013)
			{
				uint32 a = urand(0, 2);
				if (a > 0)
				{
					player->ModifyFuyin(a);
					ChatHandler(player).PSendSysMessage("获得符印点数：%u",a);
				}
				else
					ChatHandler(player).PSendSysMessage("哎呀，发生了一件可怕的事情");
				player->DestroyItemCount(item->GetEntry(), 1, true);
				return true;
			}
		}	
		else
		{
			ChatHandler(player).PSendSysMessage("战斗中无法使用");
			return true;
		}

	}
};

class xx_jineng_stone : public ItemScript
{
public:
	xx_jineng_stone() : ItemScript("xx_jineng_stone"){}
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat())
		{
			if (player->HasSpell(936011))
			{
				OnGossipHello(player, item);
				return true;
			}
			else
			{
				player->PlayerTalkClass->ClearMenus();
				std::stringstream ss("");
				ss << "|cff008000点击学习神技（光明审判）";
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 1000, 1000, "", 0);
				player->PlayerTalkClass->SendGossipMenu(60010, item->GetGUID());
				return true;
			}
		}
		return true;
	}

	bool OnGossipHello(Player* player, Item* pitem)
	{
		player->PlayerTalkClass->ClearMenus();
		std::stringstream ss("");

		ss << "|cff008000-------------------------------";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);
		ss.str("");
		ss << "|cFF0000FF点击进行神技（光明审判）突破";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 1001, 1001, "", 0);
		ss.str("");
		ss << "|cFF0000FF点击进行神技（光明审判）觉醒";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 1002, 1002, "", 0);
		ss.str("");
		ss << "|cFF0000FF点击进行神技（光明审判）培养";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(29, 0, ss.str().c_str(), 1003, 1003, "", 0);

		player->PlayerTalkClass->SendGossipMenu(60010, pitem->GetGUID());
		return true;
	}

	bool OnGossipSelect1(Player* player, Item* pitem, uint32 uiSender, uint32 uiAction)
	{
		switch (uiAction)
		{
		case 1000:
			player->learnSpell(936011);
			OnGossipHello(player, pitem);
			return true;
		case 1001:
			sObjectMgr->ShowJntpMenu(player, pitem);
			return true;
		case 1002:
			sObjectMgr->ShowJnjxMenu(player, pitem);
			return true;
		case 1003:
			sObjectMgr->ShowJnpyMenu(player, pitem);
			return true;
		case 1011:
			sObjectMgr->Updatejntp(player, pitem, uiAction);
			return true;
		case 1012:
			sObjectMgr->Updatejnjx(player, pitem, uiAction);
			return true;
		case 1013:
			sObjectMgr->Updatejnpy(player, pitem, uiAction);
			return true;
		}
		return true;
	}
};

class boss_zidingyitwo : public CreatureScript
{
public:
	boss_zidingyitwo() : CreatureScript("boss_zidingyitwo") { }

	struct boss_zidingyitwoAI : public ScriptedAI
	{
		boss_zidingyitwoAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			pInstance = pCreature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		EventMap events;
		void Reset()
		{
			events.Reset();
			me->CastSpell(me, 934011, true);
		}

		void EnterCombat(Unit* who)
		{
			events.Reset();
				me->CastSpell(me, 934011, true);
				events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
				events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
				events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
				events.ScheduleEvent(EVENT_SPELL_BERSERK, 600000);




		}

		void JustDied(Unit* killer)
		{
			uint32 a = urand(1, 100);
			if (a >= 95)
			{
				//me->SummonCreature(70004, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 180);
				me->CastSpell((Unit*)NULL, 938001, true);
				char buff[2048];
				sprintf(buff, "|CFF00FF00【隐藏商人】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,隐藏商人出现了~|r", killer->GetName(), killer->GetName(), me->GetName());
				sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
			}
			//sLog->outString("JustDied  (%u)", a);
		}

		uint32 DoSpellCasta(uint32 BossSpell)
		{
			switch (BossSpell)
			{
			case 0:
				return 24573;//致死打击-释放
			case 1:
				return 75418;//震荡波-释放
			case 2:
				return 60899;//击飞-释放
			case 3:
				return 71001;//凋零-释放
			case 4:
				return 59192;//仇恨打击-释放
			case 5:
				return 66012;//寒冰打击-释放
			default:
				return 0;
			}
		}

		uint32 DoSpellCastb(uint32 BossSpell)
		{
			switch (BossSpell)
			{
			case 0:
				return 62910;//咪咪-释放
			case 1:
				return 71058;//冰霜吐息-释放
			case 2:
				return 75956;//黑暗吐息
			case 3:
				return 57544;//灰烬使者-释放
			case 4:
				return 22247;//镇压光环-释放
			default:
				return 0;
			}
		}

		uint32 DoSpellCastc(uint32 BossSpell)
		{
			switch (BossSpell)
			{
			case 0:
				return 935001;//升天-释放
			case 1:
				return 32309;//酸液箭释放
			case 2:
				return 935002;//巫妖王之怒-释放
			case 3:
				return 935001;//升天-释放
			default:
				return 0;
			}
		}

		void UpdateAI(uint32 diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			switch (events.GetEvent())
			{
			case 0:
				break;
			case EVENT_SPELL_1:
				me->CastSpell(me->GetVictim(), DoSpellCasta(urand(0, 5)), false);
				events.RepeatEvent(urand(10000, 12000));
				break;
			case EVENT_SPELL_2:
				me->CastSpell(me->GetVictim(), DoSpellCastb(urand(0, 4)), false);
				events.RepeatEvent(urand(14000, 16000));
				break;
			case EVENT_SPELL_3:
				me->CastSpell((Unit*)NULL, DoSpellCastc(urand(0, 3)), false);
				events.RepeatEvent(urand(18000, 22000));
				break;
			case EVENT_SPELL_BERSERK:
				me->CastSpell(me, 934013, true);
				break;
			}

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new boss_zidingyitwoAI(pCreature);
	}
};

class boss_zidingyixiao : public CreatureScript
{
public:
	boss_zidingyixiao() : CreatureScript("boss_zidingyixiao") { }

	struct boss_zidingyixiaoAI : public ScriptedAI
	{
		boss_zidingyixiaoAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			pInstance = pCreature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		EventMap events;
		void Reset()
		{
			events.Reset();
		}

		void EnterCombat(Unit* who)
		{
			events.Reset();

		}

		void JustDied(Unit* killer)
		{
			uint32 a = urand(1, 100);
			uint32 b = urand(1, 1000);
			if (me->GetEntry() == 98112)
			{
				if (a >= 95)
				{
					me->CastSpell((Unit*)NULL, 938112, true);
					char buff[2048];
					sprintf(buff, "|CFF00FF00【小偷BOSS】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,小偷之王从天而降~|r", killer->GetName(), killer->GetName(), me->GetName());
					sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
				}
				
			}
			else
			{ 
				if (a >= 95)
				{
					if (b == 1000)
					{
						me->CastSpell((Unit*)NULL, 938111, true);
						char buff[2048];
						sprintf(buff, "|CFF00FF00【神秘BOSS】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,吉安娜·普劳德摩尔从天而降~|r", killer->GetName(), killer->GetName(), me->GetName());
						sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
					}
					else if (b >= 950)
					{
						me->CastSpell((Unit*)NULL, 938110, true);
						char buff[2048];
						sprintf(buff, "|CFF00FF00【神秘BOSS】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,玛兰黛从天而降~|r", killer->GetName(), killer->GetName(), me->GetName());
						sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
					}
					else if (b >= 900)
					{
						me->CastSpell((Unit*)NULL, 938109, true);
						char buff[2048];
						sprintf(buff, "|CFF00FF00【神秘BOSS】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,大领主提里奥·弗丁从天而降~|r", killer->GetName(), killer->GetName(), me->GetName());
						sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
					}
					else if (b >= 800)
					{
						me->CastSpell((Unit*)NULL, 938108, true);
						char buff[2048];
						sprintf(buff, "|CFF00FF00【神秘BOSS】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,伊利丹·怒风从天而降~|r", killer->GetName(), killer->GetName(), me->GetName());
						sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
					}
					else if (b >= 700)
					{
						me->CastSpell((Unit*)NULL, 938107, true);
						char buff[2048];
						sprintf(buff, "|CFF00FF00【神秘BOSS】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,帕奇维克从天而降~|r", killer->GetName(), killer->GetName(), me->GetName());
						sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
					}
					else if (b >= 600)
					{
						me->CastSpell((Unit*)NULL, 938106, true);
						char buff[2048];
						sprintf(buff, "|CFF00FF00【神秘BOSS】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,石木长者从天而降~|r", killer->GetName(), killer->GetName(), me->GetName());
						sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
					}
					else if (b >= 500)
					{
						me->CastSpell((Unit*)NULL, 938105, true);
						char buff[2048];
						sprintf(buff, "|CFF00FF00【神秘BOSS】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,奥妮克希亚从天而降~|r", killer->GetName(), killer->GetName(), me->GetName());
					}
					else if (b >= 400)
					{
						me->CastSpell((Unit*)NULL, 938104, true);
					}
					else if (b >= 300)
					{
						me->CastSpell((Unit*)NULL, 938103, true);
					}
					else if (b >= 200)
					{
						me->CastSpell((Unit*)NULL, 938102, true);
					}
					else
					{
						me->CastSpell((Unit*)NULL, 938101, true);
					}
				}
			}
		}

		void UpdateAI(uint32 diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new boss_zidingyixiaoAI(pCreature);
	}
};

class boss_zidingyiworld : public CreatureScript
{
public:
	boss_zidingyiworld() : CreatureScript("boss_zidingyiworld") { }

	struct boss_zidingyiworldAI : public ScriptedAI
	{
		boss_zidingyiworldAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			pInstance = pCreature->GetInstanceScript();
		}

		InstanceScript* pInstance;
		EventMap events;
		void Reset()
		{
			events.Reset();
			me->CastSpell(me, 934014, true);
		}

		void EnterCombat(Unit* who)
		{
			events.Reset();
			me->CastSpell(me, 934014, true);
			me->CastSpell(me, 70842, true);
			events.ScheduleEvent(EVENT_SPELL_SOUL_FLAY, 0);
			//events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
			events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
			events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			events.ScheduleEvent(EVENT_SPELL_BERSERK, 900000);





		}

		void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask)
		{
			if (damage >= me->GetPower(POWER_MANA))
			{
				damage -= me->GetPower(POWER_MANA);
				me->SetPower(POWER_MANA, 0);
				me->RemoveAurasDueToSpell(70842);
			}
		}

		void JustDied(Unit* killer)
		{
			uint32 a = urand(1, 100);
			if (a >= 95)
			{
				//me->SummonCreature(70004, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 180);
				me->CastSpell((Unit*)NULL, 938001, true);
				char buff[2048];
				sprintf(buff, "|CFF00FF00【隐藏商人】:|r|cffffffff|Hplayer:%s|h[%s]|h|r将|cffffffff[%s]|r击杀后,隐藏商人出现了~|r", killer->GetName(), killer->GetName(), me->GetName());
				sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
			}
			//sLog->outString("JustDied  (%u)", a);
		}

		uint32 DoSpellCasta(uint32 BossSpell)
		{
			switch (BossSpell)
			{
			case 0:
				return 24573;//致死打击-释放
			case 1:
				return 75418;//震荡波-释放
			case 2:
				return 60899;//击飞-释放
			case 3:
				return 71001;//凋零-释放
			case 4:
				return 59192;//仇恨打击-释放
			case 5:
				return 66012;//寒冰打击-释放
			default:
				return 0;
			}
		}

		uint32 DoSpellCastb(uint32 BossSpell)
		{
			switch (BossSpell)
			{
			case 0:
				return 62910;//咪咪-释放
			case 1:
				return 62910;//冰霜吐息-释放
			case 2:
				return 62910;//黑暗吐息
			case 3:
				return 22247;//灰烬使者-释放
			case 4:
				return 22247;//镇压光环-释放
			default:
				return 0;
			}
		}

		uint32 DoSpellCastc(uint32 BossSpell)
		{
			switch (BossSpell)
			{
			case 0:
				return 935003;//升天-释放
			case 1:
				return 935003;//酸液箭释放
			case 2:
				return 935004;//巫妖王之怒-释放
			case 3:
				return 935004;//升天-释放
			default:
				return 0;
			}
		}

		void UpdateAI(uint32 diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			switch (events.GetEvent())
			{
			case 0:
				break;
			case EVENT_SPELL_1:
				me->CastSpell(me->GetVictim(), DoSpellCasta(urand(0, 5)), false);
				events.RepeatEvent(urand(10000, 12000));
				break;
			case EVENT_SPELL_2:
				me->CastSpell(me->GetVictim(), DoSpellCastb(urand(0, 4)), false);
				events.RepeatEvent(urand(14000, 16000));
				break;
			case EVENT_SPELL_3:
				me->CastSpell((Unit*)NULL, DoSpellCastc(urand(0, 3)), false);
				events.RepeatEvent(urand(18000, 22000));
				break;
			case EVENT_SPELL_SOUL_FLAY:
				me->CastSpell(me->GetVictim(), 940001, false);
				events.RepeatEvent(urand(4000, 5000));
				break;
			case EVENT_SPELL_BERSERK:
				me->CastSpell(me, 934013, true);
				break;
			}

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new boss_zidingyiworldAI(pCreature);
	}
};

class xx_chibang_stone : public ItemScript
{
public:
	xx_chibang_stone() : ItemScript("xx_chibang_stone"){}
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat())
		{
			if (player->HasSpell(920026) && player->HasSpell(920029) && player->HasSpell(920030) && player->HasSpell(920031) && player->HasSpell(920032))
			{
				OnGossipHello(player, item);
				return true;
			}
			else
			{
				player->PlayerTalkClass->ClearMenus();
				std::stringstream ss("");
				ss << "|cff008000点击学习羽翼视觉技能";
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 1010, 1010, "", 0);
				player->PlayerTalkClass->SendGossipMenu(907, item->GetGUID());
				return true;
			}
		}
		return true;
	}

	bool OnGossipHello(Player* player, Item* pitem)
	{
		sObjectMgr->ShowYuyiMenu(player, pitem);
		return true;
	}

	bool OnGossipSelect1(Player* player, Item* pitem, uint32 uiSender, uint32 uiAction)
	{
		switch (uiAction)
		{
		case 1010:
			player->learnSpell(920026);
			player->learnSpell(920029);
			player->learnSpell(920030);
			player->learnSpell(920031);
			player->learnSpell(920032);
			OnGossipHello(player, pitem);
			return true;
		case 1000:
			sObjectMgr->Updateyuyi(player, pitem, uiAction);
			return true;
		case 1001:
			sObjectMgr->Updateyuyi1(player, pitem, uiAction);
			return true;
		}

			

		return true;
	}
};

class xx_zhaohuan1shi : public ItemScript
{
public:
	xx_zhaohuan1shi() : ItemScript("xx_zhaohuanshi1") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		uint32 a = urand(100, 300);
		if (!item)
			return false;

		if (!player->IsInCombat())
		{
				if (player->GetTTzhaohuan1() > 0)
				{

					player->ModifyTTzhaohuan1(-1);
					player->AddItem(6, a);
					player->DestroyItemCount(item->GetEntry(), 1, true);

					ChatHandler(player).PSendSysMessage("海加尔山首领召唤次数+1,获得日常徽章%u",a);
				}
				else
				{
					ChatHandler(player).PSendSysMessage("您5次召唤次数满了，请消耗后再使用");
				}
				return true;	
		}
		else
		{
			ChatHandler(player).PSendSysMessage("战斗中无法使用");
			return true;
		}

	}
};

class xx_zhaohuan2shi : public ItemScript
{
public:
	xx_zhaohuan2shi() : ItemScript("xx_zhaohuanshi2") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		uint32 a = urand(200, 500);
		if (!item)
			return false;

		if (!player->IsInCombat())
		{
			if (player->GetTTzhaohuan2() > 0)
			{

				player->ModifyTTzhaohuan2(-1);
				player->AddItem(6, a);
				player->DestroyItemCount(item->GetEntry(), 1, true);

				ChatHandler(player).PSendSysMessage("积雪平原首领召唤次数+1,获得日常徽章%u", a);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("您3次召唤次数满了，请消耗后再使用");
			}
			return true;
		}
		else
		{
			ChatHandler(player).PSendSysMessage("战斗中无法使用");
			return true;
		}

	}
};

class xx_npc_shangren : public CreatureScript
{
public:
	xx_npc_shangren() : CreatureScript("xx_npc_shangren") {}
	bool OnUse(Player* player, Creature* creature, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat())
		{
			OnGossipHello(player, creature);
			return true;
		}
		else
		{
			player->ClearInCombat();
			return false;
		}
	}


	bool OnGossipHello(Player* player, Creature* pcreature)
	{
		sObjectMgr->XxShangren(player, pcreature);
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* pcreature, uint32 uiSender, uint32 uiAction)
	{

		sObjectMgr->RunxxShangren(uiAction, uiSender, player, pcreature);
		return true;
	}
};

class xx_huiyuanshi : public ItemScript
{
public:
	xx_huiyuanshi() : ItemScript("xx_huiyuanshi") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!item)
			return false;

		if (!player->IsInCombat())
		{
			if (item->GetEntry() == 60070)
			{
				if (player->GetPlayerViplevel() < 3)
				{
					player->SetPlayerVipLevel(3);
					player->LoginS();
					ChatHandler(player).PSendSysMessage("恭喜你VIP提升至3级");
					player->DestroyItemCount(item->GetEntry(), 1, true);
					return true;
				}
				else
				{
					ChatHandler(player).PSendSysMessage("您已经使用过啦");
					return true;
				}
				
			}
			else if (item->GetEntry() == 60071)
			{
				if (player->GetPlayerViplevel() == 3)
				{
					player->SetPlayerVipLevel(6);
					player->LoginS();
					ChatHandler(player).PSendSysMessage("恭喜你VIP提升至6级");
					player->DestroyItemCount(item->GetEntry(), 1, true);
					return true;
				}
				else if (player->GetPlayerViplevel() < 3)
				{
					ChatHandler(player).PSendSysMessage("您是否忘记使用vip3凭证");
					return true;
				}
				else if (player->GetPlayerViplevel() >= 6)
				{
					ChatHandler(player).PSendSysMessage("您已经使用过啦");
				}
				
			}
		}
		else
		{
			ChatHandler(player).PSendSysMessage("战斗中无法使用");
			return true;
		}

	}
};

class xx_lingqushi : public ItemScript
{
public:
	xx_lingqushi() : ItemScript("xx_lingqushi") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!item)
			return false;

		if (!player->IsInCombat())
		{
			switch (player->getClass())
			{
			case 1: // 战士
				player->AddItem(220114, 2);
				player->AddItem(220117, 1);
				player->AddItem(220131, 1);
				player->AddItem(220122, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220111, 1);
				player->AddItem(220112, 1);
				player->AddItem(220113, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220001, 1);
				player->AddItem(220002, 1);
				player->AddItem(220003, 1);
				player->AddItem(220004, 1);
				player->AddItem(220005, 1);
				player->AddItem(220006, 1);
				player->AddItem(220007, 1);
				player->AddItem(220008, 1);
				player->AddItem(220009, 1);
				player->AddItem(220010, 1);
				player->AddItem(220133, 1);
				break;
			case 2: // 骑士
				player->AddItem(220114, 1);
				player->AddItem(220118, 1);
				player->AddItem(220123, 1);
				player->AddItem(220127, 1);
				player->AddItem(220131, 1);
				player->AddItem(220122, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220111, 1);
				player->AddItem(220112, 1);
				player->AddItem(220113, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220046, 1);
				player->AddItem(220047, 1);
				player->AddItem(220048, 1);
				player->AddItem(220049, 1);
				player->AddItem(220050, 1);
				player->AddItem(220051, 1);
				player->AddItem(220052, 1);
				player->AddItem(220053, 1);
				player->AddItem(220054, 1);
				player->AddItem(220055, 1);
				player->AddItem(220056, 1);
				player->AddItem(220057, 1);
				player->AddItem(220058, 1);
				player->AddItem(220059, 1);
				player->AddItem(220060, 1);
				player->AddItem(220133, 1);
				break;
			case 3:	// 猎人
				player->AddItem(220116, 1);
				player->AddItem(220117, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220108, 1);
				player->AddItem(220109, 1);
				player->AddItem(220110, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220066, 1);
				player->AddItem(220067, 1);
				player->AddItem(220068, 1);
				player->AddItem(220069, 1);
				player->AddItem(220070, 1);
				break;
			case 4: // 潜行者
				player->AddItem(220120, 2);
				player->AddItem(220121, 1);
				player->AddItem(220122, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220105, 1);
				player->AddItem(220106, 1);
				player->AddItem(220107, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220031, 1);
				player->AddItem(220032, 1);
				player->AddItem(220033, 1);
				player->AddItem(220034, 1);
				player->AddItem(220035, 1);
				player->AddItem(220117, 1);
				player->AddItem(220132, 1);
				break;
			case 5: // 牧师
				player->AddItem(220115, 1);
				player->AddItem(220118, 1);
				player->AddItem(220123, 1);
				player->AddItem(220124, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220102, 1);
				player->AddItem(220103, 1);
				player->AddItem(220104, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220036, 1);
				player->AddItem(220037, 1);
				player->AddItem(220038, 1);
				player->AddItem(220039, 1);
				player->AddItem(220040, 1);
				player->AddItem(220041, 1);
				player->AddItem(220042, 1);
				player->AddItem(220043, 1);
				player->AddItem(220044, 1);
				player->AddItem(220045, 1);
				break;
			case 6: // 死骑
				player->AddItem(220114, 1);
				player->AddItem(220130, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220111, 1);
				player->AddItem(220112, 1);
				player->AddItem(200113, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220086, 1);
				player->AddItem(220087, 1);
				player->AddItem(220088, 1);
				player->AddItem(220089, 1);
				player->AddItem(220090, 1);
				player->AddItem(220091, 1);
				player->AddItem(220092, 1);
				player->AddItem(220093, 1);
				player->AddItem(220094, 1);
				player->AddItem(220095, 1);
				player->AddItem(220120, 2);
				break;
			case 7: // 萨满
				player->AddItem(220115, 1);
				player->AddItem(220118, 1);
				player->AddItem(220121, 2);
				player->AddItem(220123, 1);
				player->AddItem(220129, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220108, 1);
				player->AddItem(220109, 1);
				player->AddItem(220110, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220016, 1);
				player->AddItem(220017, 1);
				player->AddItem(220018, 1);
				player->AddItem(220019, 1);
				player->AddItem(220020, 1);
				player->AddItem(220021, 1);
				player->AddItem(220022, 1);
				player->AddItem(220023, 1);
				player->AddItem(220024, 1);
				player->AddItem(220025, 1);
				player->AddItem(220026, 1);
				player->AddItem(220027, 1);
				player->AddItem(220028, 1);
				player->AddItem(220029, 1);
				player->AddItem(220030, 1);
				break;
			case 8: // 法师
				player->AddItem(220115, 1);
				player->AddItem(220124, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220102, 1);
				player->AddItem(220103, 1);
				player->AddItem(220104, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220061, 1);
				player->AddItem(220062, 1);
				player->AddItem(220063, 1);
				player->AddItem(220064, 1);
				player->AddItem(220065, 1);
				break;
			case 9: // 术士
				player->AddItem(220115, 1);
				player->AddItem(220124, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220102, 1);
				player->AddItem(220103, 1);
				player->AddItem(220104, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220011, 1);
				player->AddItem(220012, 1);
				player->AddItem(220013, 1);
				player->AddItem(220014, 1);
				player->AddItem(220015, 1);
				break;
			case 11: // 德鲁伊
				player->AddItem(220115, 1);
				player->AddItem(220116, 1);
				player->AddItem(220118, 1);
				player->AddItem(220123, 1);
				player->AddItem(220128, 1);
				player->AddItem(220125, 1);
				player->AddItem(220126, 1);
				player->AddItem(220105, 1);
				player->AddItem(220106, 1);
				player->AddItem(220107, 1);
				player->AddItem(220101, 1);
				player->AddItem(220100, 1);
				player->AddItem(220096, 1);
				player->AddItem(220097, 1);
				player->AddItem(220098, 1);
				player->AddItem(220099, 1);
				player->AddItem(220071, 1);
				player->AddItem(220072, 1);
				player->AddItem(220073, 1);
				player->AddItem(220074, 1);
				player->AddItem(220075, 1);
				player->AddItem(220076, 1);
				player->AddItem(220077, 1);
				player->AddItem(220078, 1);
				player->AddItem(220079, 1);
				player->AddItem(220080, 1);
				player->AddItem(220081, 1);
				player->AddItem(220082, 1);
				player->AddItem(220083, 1);
				player->AddItem(220084, 1);
				player->AddItem(220085, 1);
				break;
			}
			player->DestroyItemCount(item->GetEntry(), 1, true);
		}
		else
		{
			ChatHandler(player).PSendSysMessage("战斗中无法使用");
			return true;
		}

	}
};

class xx_chiheshi : public ItemScript
{
public:
	xx_chiheshi() : ItemScript("xx_chiheshi") { }
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets)
	{
		if (!item)
			return false;

		if (!player->IsInCombat())
		{
			if (player->GetMapId() == 649 || player->GetMapId() == 631)
			{
				player->CastSpell(player,985011,false);
				return true;
			}
			else 
			{
				ChatHandler(player).PSendSysMessage("只能在部分团队副本使用");
				return true;
			}
		}
		else
		{
			ChatHandler(player).PSendSysMessage("战斗中无法使用");
			return true;
		}

	}
};

class xx_npc_choujiang : public CreatureScript
{
public:
	xx_npc_choujiang() : CreatureScript("xx_npc_choujiang") {}
	bool OnUse(Player* player, Creature* creature, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat())
		{
			OnGossipHello(player, creature);
			return true;
		}
		else
		{
			player->ClearInCombat();
			return false;
		}
	}


	bool OnGossipHello(Player* player, Creature* pcreature)
	{
		sObjectMgr->ShowCjMenu(player, pcreature);
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* pcreature, uint32 uiSender, uint32 uiAction)
	{

		sObjectMgr->Updatecjjf(player, pcreature, uiSender, uiAction);
		return true;
	}
};

class xx_npc_choujiangzb : public CreatureScript
{
public:
	xx_npc_choujiangzb() : CreatureScript("xx_npc_choujiangzb") {}
	bool OnUse(Player* player, Creature* creature, SpellCastTargets const& targets)
	{
		if (!player->IsInCombat())
		{
			OnGossipHello(player, creature);
			return true;
		}
		else
		{
			player->ClearInCombat();
			return false;
		}
	}


	bool OnGossipHello(Player* player, Creature* pcreature)
	{
		sObjectMgr->ShowCjzMenu(player, pcreature);
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* pcreature, uint32 uiSender, uint32 uiAction)
	{

		sObjectMgr->Updatecjzjf(player, pcreature, uiSender, uiAction);
		return true;
	}
};

void AddSC_xxScript()
{
	new xx_npc_trainer1();
	new npc_additem();
	new Duel_Reset();
	new xx_npc_trainer();
	new xx_item_teleport();
	new xx_item_upgrade();
	new xx_fuyin_stone();
	new xx_item_gradecj();
	new xx_suoyaoshi();
	new spell_fuhuo();
	new xx_npc_lingqu();
	new boss_zidingyi();
	new npc_world();
	new spell_wuli();
	new xx_fuyinshi();
	new xx_item_gradezh();
	new xx_jineng_stone();
	new spell_shenji();
	new boss_zidingyitwo();
	new boss_zidingyixiao();
	new boss_zidingyiworld();
	new xx_chibang_stone();
	new xx_zhaohuan1shi();
	new xx_zhaohuan2shi();
	new xx_npc_shangren();
	new xx_huiyuanshi();
	new xx_lingqushi();
	new xx_chiheshi();
	new xx_npc_choujiang();
	new xx_npc_choujiangzb();
}