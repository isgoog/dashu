#include "Common.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "SpellMgr.h"
#include "UpdateMask.h"
#include "World.h"
#include "Group.h"
#include "Guild.h"
#include "ArenaTeam.h"
#include "Transport.h"
#include "Language.h"
#include "GameEventMgr.h"
#include "Spell.h"
#include "Chat.h"
#include "AccountMgr.h"
#include "InstanceSaveMgr.h"
#include "SpellAuras.h"
#include "Util.h"
#include "WaypointManager.h"
#include "GossipDef.h"
#include "Vehicle.h"
#include "AchievementMgr.h"
#include "DisableMgr.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "PoolMgr.h"
#include "Config.h"
#include "Pet.h"
#include "ScriptedGossip.h"
#include "BattlegroundMgr.h"

#pragma execution_character_set("utf-8")


void ObjectMgr::LoadxxItemTeleportMenu(uint32 MenuId, Player* player, Item* pitem)
{
	uint32 faction = 0;
	if (player->GetTeamId() == TEAM_ALLIANCE)
		faction = 1;
	else
		faction = 2;


	player->PlayerTalkClass->ClearMenus(); //清除菜单项

	for (xxItemTeleMap::iterator ltr = _xxItemTeleMap.begin(); ltr != _xxItemTeleMap.end(); ++ltr)
	{
		if (player->GetTeamId() == TEAM_ALLIANCE || player->GetTeamId() == TEAM_HORDE){
			if (ltr->second.parentid == MenuId && (ltr->second.factionid == 0 || faction == ltr->second.factionid))  // 载入指定页面的菜单
			{
				if (player->GetMapId() != 609){
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(ltr->second.menuid, 0, ltr->second.title.c_str(), ltr->second.menuid, ltr->second.usetype + 1000, "", 0);
				}
				else{
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, "未离开死亡骑士新手村无法使用传送宝石", 0, 0, "", 0);
				}
			}
		}
		else{
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, "未加入阵营无法使用传送宝石", 0, 0, "", 0);
		}
	}
	player->PlayerTalkClass->SendGossipMenu(907, pitem->GetGUID()); // 发送菜单
}

bool ObjectMgr::RunxxItemTeleport(uint32 action, uint32 sender, Player *player, Item *pitem)
{
	if (player->IsInCombat())
	{
		player->PlayerTalkClass->ClearMenus();
		return false;
	}

	xxItemTeleMap::iterator itr = _xxItemTeleMap.find(sender);
	if (itr == _xxItemTeleMap.end())
	{
		switch (action)
		{
		case 1101:
			PvpRankLevelUP(player, pitem);
			return true;
		case 1021:
			JfZyUP(player, pitem, 1);
			return true;
		case 1022:
			JfZyUP(player, pitem, 2);
			return true;
		case 1023:
			JfZyUP(player, pitem, 3);
			return true;
		case 1024:
			JfZyUP(player, pitem, 4);
			return true;
		case 1025:
			JfZyUP(player, pitem, 5);
			return true;
		case 1026:
			JfZyUP(player, pitem, 6);
			return true;
		case 1027:
			JfZyUP(player, pitem, 7);
			return true;
		case 1028:
			JfZyUP(player, pitem, 8);
			return true;
		case 1029:
			JfZyUP(player, pitem, 9);
			return true;
		case 1030:
			JfZyUP(player, pitem, 10);
			return true;
		case 1031:
			JfZyUP(player, pitem, 11);
			return true;
		case 1032:
			JfZyUP(player, pitem, 12);
			return true;
		case 1033:
			JfZyUP(player, pitem, 13);
			return true;
		case 1034:
			JfZyUP(player, pitem, 14);
			return true;
		case 1051:
			JfzhuanyeUP(player, pitem, 1);
			return true;
		case 1052:
			JfzhuanyeUP(player, pitem, 2);
			return true;
		case 1053:
			JfzhuanyeUP(player, pitem, 3);
			return true;
		case 1054:
			JfzhuanyeUP(player, pitem, 4);
			return true;
		case 1055:
			JfzhuanyeUP(player, pitem, 5);
			return true;
		case 1056:
			JfzhuanyeUP(player, pitem, 6);
			return true;
		case 1057:
			JfzhuanyeUP(player, pitem, 7);
			return true;
		case 1058:
			JfzhuanyeUP(player, pitem, 8);
			return true;
		case 1059:
			JfzhuanyeUP(player, pitem, 9);
			return true;
		case 1060:
			JfzhuanyeUP(player, pitem, 10);
			return true;
		case 1061:
			JfzhuanyeUP(player, pitem, 11);
			return true;
		case 1102:
			VipLevelUP(player, pitem);
			return true;
		case 1071:
			ShijianUP(player, pitem, 1);
			return true;
		case 1072:
			ShijianUP(player, pitem, 2);
			return true;
		case 1073:
			ShowshijianMenu(player, pitem);
			return true;
		case 1074:
			ShijianUP(player, pitem, 3);
			return true;
		case 1075:
			ShijianUP(player, pitem, 4);
			return true;
		case 1081:
			Huolichuansong(player, pitem);
			return true;
		case 1082://卡拉赞
			player->TeleportTo(0, -11121.8105469f, -2012.300293f, 47.1131783f, 0.0f);
			return true;
		case 1083://JJC
			player->TeleportTo(0, -13230.353516f, 224.304016f, 35.506493f, 0.0f);
			return true;
		case 1084://海加尔山
			player->TeleportTo(1, 4343.1513672f, -3353.9545898f, 1049.2070312f, 0.0f);
			return true;
		case 1085://风暴要塞
			player->TeleportTo(530, 3088.883545f, 1393.404907f, 185.878723f, 0.0f);
			return true;
		case 1086://积雪平原
			player->TeleportTo(37, -501.2999878f, -68.6999969f, 317.5f, 0.0f);
			return true;
		case 1087://十字军试炼
			player->TeleportTo(571, 8515.3496094f, 730.1699829f, 558.5939941f, 0.0f);
			return true;
		case 1088://冰冠堡垒
			player->TeleportTo(571, 5788.3598633f, 2070.6899414f, 636.0640259f, 0.0f);
			return true;
		case 1089://格鲁尔
			player->TeleportTo(530, 3549.800049f, 5085.970215f, 2.463320f, 0.0f);
			return true;
		case 1090://海加尔山
			player->TeleportTo(1, 5478.0600586f, -3730.8500977f, 1593.4399414f, 0.0f);
			return true;
		case 1091://黑暗之门
			player->TeleportTo(0, -11866.185547f, -3202.256592f, -22.349119f, 0.0f);
			return true;
		}
		return false;
	}

	switch (itr->second.needtype)
	{
	case 1://需要人物等级
		if (player->getLevel() < itr->second.needv1)
		{
			ChatHandler(player).PSendSysMessage(22002, itr->second.needv1);
			player->PlayerTalkClass->SendCloseGossip();
			return false;
		}
		break;
	case 3://需要积分
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) < (uint32)abs(itr->second.needv1))
		{
			ChatHandler(player).PSendSysMessage(22005, (uint32)abs(itr->second.needv1));
			player->PlayerTalkClass->SendCloseGossip();
			return false;
		}
		break;
	case 4://需要金币
		if (player->GetMoney() < (uint32)abs(itr->second.needv1))
		{
			ChatHandler(player).PSendSysMessage(22006, itr->second.needv1);
			player->PlayerTalkClass->SendCloseGossip();
			return false;
		}
		if (itr->second.needv1 < 0)
			player->ModifyMoney(itr->second.needv1);
		break;
	}

	switch (action)
	{
	case 1000: // 显示指定菜单
		LoadxxItemTeleportMenu(sender, player, pitem);
		return true;
	case 1001://传送
		xxTeleportFromMenuId(player, sender);
		break;
	case 1002://领取充值
		player->GetPayJF();
		//ChatHandler(player).PSendSysMessage(22000, player->GetJF());
		break;
	case 1003: // 修理装备
		player->DurabilityRepairAll(false, 0, false);
		break;
	case 1004://升级会员
		ShowVipMenu(player, pitem);
		return true;
	case 1005: // 个人银行
		player->GetSession()->SendShowBank(player->GetGUID());
		break;
	case 1006: //军衔系统
		ShowPvpRankMenu(player, pitem);
		return true;
	case 1007:
		if (player->GetIsvipgeted())
		{
			ChatHandler(player).PSendSysMessage("你今天已经领取过每日礼包,每日只能领取一次每日礼包");
			return false;
		}
		else
		{
			player->SetGetVipCredit(true);//设置为已经领取奖励
			if (GetVipMrJl(player, 0, 1) > 0 && GetVipMrJl(player, 1, 1) > 0)
				player->AddItem(GetVipMrJl(player, 0, 1), GetVipMrJl(player, 1, 1));
			if (GetVipMrJl(player, 0, 2) > 0 && GetVipMrJl(player, 1, 2) > 0)
				player->AddItem(GetVipMrJl(player, 0, 2), GetVipMrJl(player, 1, 2));
			if (GetVipMrJl(player, 0, 3) > 0 && GetVipMrJl(player, 1, 3) > 0)
				player->AddItem(GetVipMrJl(player, 0, 3), GetVipMrJl(player, 1, 3));
			if (GetVipMrJl(player, 0, 4) > 0 && GetVipMrJl(player, 1, 4) > 0)
				player->AddItem(GetVipMrJl(player, 0, 4), GetVipMrJl(player, 1, 4));
			if (GetVipMrJl(player, 0, 5) > 0 && GetVipMrJl(player, 1, 5) > 0)
				player->AddItem(GetVipMrJl(player, 0, 5), GetVipMrJl(player, 1, 5));
			player->PlayerTalkClass->SendCloseGossip();
			ChatHandler(player).PSendSysMessage("|CFFFF0000恭喜你获得每日礼包|r");
		}
		break;
	case 1008://光环重载
		player->LoginS();
		break;
	case 1009://活力传送
		HuoliMenu(player,pitem);
		return true;
	case 1010://活力传送
		KlzMenu(player, pitem);
		return true;
	case 1011://超级世界boss传送
		WorldbossMenu(player, pitem);
		return true;
	case 1012://活力传送
		FbysMenu(player, pitem);
		return true;
	case 1013://活力传送
		HjeMenu(player, pitem);
		return true;
	case 1014://活力传送
		JxpyMenu(player, pitem);
		return true;
	case 1015://活力传送
		TocMenu(player, pitem);
		return true;
	case 1016://活力传送
		IccMenu(player, pitem);
		return true;
	case 1017://活力传送
		GleMenu(player, pitem);
		return true;
	case 1018://活力传送
		YskkMenu(player, pitem);
		return true;
	case 1020://领取xuanchuan
		player->GetPayXC();
		break;
	case 1022://积分学习专业技能
		ShowJfzhuanyeMenu(player, pitem);
		return true;
	case 1023://查询会员属性
		XxHui(player, pitem);
		return true;
	case 1024://积分拍卖
		player->GetJlJF();
		return true;
	case 1027://积分升级专业技能
		ShowJfZyMenu(player, pitem);
		return true;
		//阵营 种族 外观 名字修改
	case 1031:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(LOGIN_CHANGE_FACTION_JF))
		{
			player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
			CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '64' WHERE guid = %u", player->GetGUID());
			ShowBuffSpawn(player);
			player->GetSession()->SendAreaTriggerMessage("重新登录以修改阵营");
			player->GetSession()->SendAreaTriggerMessage("感谢使用积分服务");
			player->CastSpell(player, 47292, true, NULL, NULL, player->GetGUID());
			//player->ModifyJF(-int32(sWorld->getIntConfig(LOGIN_CHANGE_FACTION_JF)));
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(LOGIN_CHANGE_FACTION_JF), true);
		}
		else player->GetSession()->SendNotification("你没有足够积分，请赞助我们获得积分 ");
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1032:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(LOGIN_CHANGE_RACE_JF))
		{
			player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
			CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '128' WHERE guid = %u", player->GetGUID());
			ShowBuffSpawn(player);
			player->GetSession()->SendAreaTriggerMessage("重新登录以修改种族");
			player->GetSession()->SendAreaTriggerMessage("感谢使用积分服务");
			player->CastSpell(player, 47292, true, NULL, NULL, player->GetGUID());
			//player->ModifyJF(-int32(sWorld->getIntConfig(LOGIN_CHANGE_RACE_JF)));
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(LOGIN_CHANGE_RACE_JF), true);
		}
		else player->GetSession()->SendNotification("你没有足够积分，请赞助我们获得积分 ");
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1033:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(LOGIN_CUSTOMIZE_JF))
		{
			player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
			CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '8' WHERE guid = %u", player->GetGUID());
			player->GetSession()->SendAreaTriggerMessage("重新登录以修改外观");
			player->GetSession()->SendAreaTriggerMessage("感谢使用积分服务");
			player->CastSpell(player, 47292, true, NULL, NULL, player->GetGUID());
			//player->ModifyJF(-int32(sWorld->getIntConfig(LOGIN_CUSTOMIZE_JF)));
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(LOGIN_CUSTOMIZE_JF), true);
		}
		else player->GetSession()->SendNotification("你没有足够积分，请赞助我们获得积分 ");
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1034:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(LOGIN_RENAME_JF))
		{
			player->SetAtLoginFlag(AT_LOGIN_RENAME);
			CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '1' WHERE guid = %u", player->GetGUID());
			player->GetSession()->SendAreaTriggerMessage("重新登录以修改名字");
			player->GetSession()->SendAreaTriggerMessage("感谢使用积分服务");
			player->CastSpell(player, 47292, true, NULL, NULL, player->GetGUID());
			//player->ModifyJF(-int32(sWorld->getIntConfig(LOGIN_RENAME_JF)));
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(LOGIN_RENAME_JF), true);
		}
		else player->GetSession()->SendNotification("你没有足够积分，请赞助我们获得积分 ");
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1035:
		for (uint8 x = 0; x < 74; ++x)
		{
			for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
			{
				sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUIDLow(), xxcoremapidid[x], Difficulty(i), true, player);
			}
		}
		player->SetTocid(0);
		player->SetIccid(0);
		player->SetKlzid(0);
		player->SetGleid(0);
		player->GetSession()->SendAreaTriggerMessage("你的所有副本进度已重置");
		return true;

	}
	player->PlayerTalkClass->SendCloseGossip();
	return true;
}

void ObjectMgr::xxTeleportFromMenuId(Player* player, uint32 MenuId)
{
	xxItemTeleMap::const_iterator ltr = _xxItemTeleMap.find(MenuId);
	if (ltr == _xxItemTeleMap.end())
		return;

	player->TeleportTo(ltr->second.tele_map, ltr->second.tele_x, ltr->second.tele_y, ltr->second.tele_z, 0);
}

void ObjectMgr::ShowJfzhuanyeMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	uint32 jf = sWorld->getIntConfig(ZY_XUEXI_JF) + (player->GetPlayerSkillCount() * 10000);
	std::stringstream ss("");
	ss << "|cff008000积分学习额外专业技能";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "你当前拥有积分:|cffFF0000[" << player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) << "|cff008000]";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "|cff008000------------------------------------------";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cffFF0000请先学习好2个专业再来这学习";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分学习一个额外的专业技能";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cff008000------------------------------------------";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000采矿专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(7, 0, ss.str().c_str(), 0, 1050 + 1, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000炼金专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, 0, ss.str().c_str(), 0, 1050 + 2, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000锻造专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(9, 0, ss.str().c_str(), 0, 1050 + 3, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000裁缝专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(10, 0, ss.str().c_str(), 0, 1050 + 4, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000制皮专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 1050 + 5, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000附魔专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 1050 + 6, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000珠宝专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, ss.str().c_str(), 0, 1050 + 7, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000工程专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(14, 0, ss.str().c_str(), 0, 1050 + 8, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000剥皮专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(15, 0, ss.str().c_str(), 0, 1050 + 9, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000铭文专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(16, 0, ss.str().c_str(), 0, 1050 + 10, "", 0);
	ss.str("");
	ss << jf << "|cff008000积分|cff004000学习|cffFF0000草药专业";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(17, 0, ss.str().c_str(), 0, 1050 + 11, "", 0);


	player->PlayerTalkClass->SendGossipMenu(907, item->GetGUID());
}

void ObjectMgr::JfzhuanyeUP(Player *player, Item *item, int8 sta)
{
	uint32 jf = sWorld->getIntConfig(ZY_XUEXI_JF) + (player->GetPlayerSkillCount() * 10000);
	switch (sta)
	{
	case 1:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(186))
		{
			//player->ModifyJF(-int32(sWorld->getIntConfig(ZY_XUEXI_JF)));
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(2575);
			player->ModifySkillCount(1);

		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 2:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(171))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(2259);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 3:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(164))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(2018);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 4:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(197))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(3908);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 5:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(165))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(2108);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 6:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(333))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(7411);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 7:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(755))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(25229);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 8:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(202))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(4036);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 9:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(393))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(8613);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 10:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(773))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(45357);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;
	case 11:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf && !player->HasSkill(182))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			player->learnSpell(2366);
			player->ModifySkillCount(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50001);
		}
		ShowJfzhuanyeMenu(player, item);
		break;

	}

}

void ObjectMgr::ShowJfZyMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();

	std::stringstream ss("");
	ss << "|cff008000积分提升专业技能";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "你当前拥有积分:[|cffFF0000" << player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) << "|cff008000]";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "|cff008000------------------------------------------";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000点积分可提升满一个专业技能";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cff008000------------------------------------------";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000采矿满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(7, 0, ss.str().c_str(), 0, 1020 + 1, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000炼金满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, 0, ss.str().c_str(), 0, 1020 + 2, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000锻造满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(9, 0, ss.str().c_str(), 0, 1020 + 3, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000裁缝满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(10, 0, ss.str().c_str(), 0, 1020 + 4, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000烹饪满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 1020 + 5, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000制皮满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 1020 + 6, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000钓鱼满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, ss.str().c_str(), 0, 1020 + 7, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000附魔满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(14, 0, ss.str().c_str(), 0, 1020 + 8, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000珠宝满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(15, 0, ss.str().c_str(), 0, 1020 + 9, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000工程满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(16, 0, ss.str().c_str(), 0, 1020 + 10, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000急救满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(17, 0, ss.str().c_str(), 0, 1020 + 11, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000草药满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(18, 0, ss.str().c_str(), 0, 1020 + 12, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000剥皮满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(19, 0, ss.str().c_str(), 0, 1020 + 13, "", 0);
	ss.str("");
	ss << sWorld->getIntConfig(ZY_TISHENG_JF) << "|cff008000积分|cff004000提升|cffFF0000铭文满级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 1020 + 14, "", 0);

	player->PlayerTalkClass->SendGossipMenu(907, item->GetGUID());
}

void ObjectMgr::JfZyUP(Player *player, Item *item, int8 sta)
{
	switch (sta)
	{
	case 1:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(186))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(186, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 2:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(171))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(171, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 3:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(164))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(164, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 4:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(197))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(197, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 5:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(185))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(185, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 6:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(165))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(165, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 7:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(356))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(356, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 8:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(333))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(333, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 9:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(755))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(755, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 10:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(202))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(202, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 11:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(129))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(129, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 12:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(182))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(182, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 13:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(393))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(393, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;
	case 14:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(ZY_TISHENG_JF) && player->HasSkill(773))
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(ZY_TISHENG_JF), true);
			player->SetSkill(773, 0, 450, 450);
			player->LoginS();
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50098);
		}
		ShowJfZyMenu(player, item);
		break;

	}

}

void ObjectMgr::ShowUpgradeMenu(Item *m_from, Item *target, Player *player)
{
	if (!m_from || !target || !player)
		return;

	player->PlayerTalkClass->ClearMenus();
	uint32 FromId = m_from->GetEntry(), TargetId = target->GetEntry();

	for (xxItemupMap::const_iterator itr = _xxItemupMap.begin(); itr != _xxItemupMap.end(); ++itr)
	{
		if (itr->second.ItemID == TargetId && (itr->second.FromId == 0 || itr->second.FromId == FromId))
		{
			bool isUpgrade = true;

			std::stringstream ss("");
			ss << "|cff004000强化:[|cff590248" << target->GetTemplate()->Name1 << "|cff004000] 需要:";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 1, 1, "", 0);

			if (itr->second.JFCost > 0)
			{
				ss.str("");
				ss << "|TInterface\\ICONS\\inv_misc_markoftheworldtree.blp:24|t|cff004000需要积分: |cff0000FF" << itr->second.JFCost;
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 1, 1, "", 0);
				if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) < itr->second.JFCost)
				{
					isUpgrade = false;
				}
			}

			if (itr->second.ReqItem1 > 0)
			{
				ss.str("");
				ss << "|TInterface\\ICONS\\INV_Misc_Bag_10_Black.blp:24|t|cff004000需要:[|cff800000" << sObjectMgr->GetItemNameLink(itr->second.ReqItem1) << "|cff004000] " << itr->second.ReqCount1 << "个";
				if (player->GetItemCount(itr->second.ReqItem1, false) + player->GetItemCount(itr->second.ReqItemBd1, false) >= itr->second.ReqCount1)
				{
					ss << " |cff004000√|r";
				}
				else
				{
					ss << " |cff800000×|r";
					isUpgrade = false;
				}
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 1, 1, "", 0);
			}

			if (itr->second.ReqItem2 > 0)
			{
				ss.str("");
				ss << "|TInterface\\ICONS\\INV_MISC_BAG_10_BLUE.blp:24|t|cff004000需要:[|cff800000" << sObjectMgr->GetItemNameLink(itr->second.ReqItem2) << "|cff004000] " << itr->second.ReqCount2 << "个";
				if (player->GetItemCount(itr->second.ReqItem2, false) + player->GetItemCount(itr->second.ReqItemBd2, false) >= itr->second.ReqCount2)
				{
					ss << " |cff004000√|r";
				}
				else
				{
					ss << " |cff800000×|r";
					isUpgrade = false;
				}
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 1, 1, "", 0);
			}

			if (itr->second.ReqItem3 > 0)
			{
				ss.str("");
				ss << "|TInterface\\ICONS\\INV_MISC_BAG_10_Green.blp:24|t|cff004000需要:[|cff800000" << sObjectMgr->GetItemNameLink(itr->second.ReqItem3) << "|cff004000] " << itr->second.ReqCount3 << "个";
				if (player->GetItemCount(itr->second.ReqItem3, false) + player->GetItemCount(itr->second.ReqItemBd3, false) >= itr->second.ReqCount3)
				{
					ss << " |cff004000√|r";
				}
				else
				{
					ss << " |cff800000×|r";
					isUpgrade = false;
				}
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(7, 0, ss.str().c_str(), 1, 1, "", 0);
			}

			if (itr->second.ReqItem4 > 0)
			{
				ss.str("");
				ss << "|TInterface\\ICONS\\INV_MISC_BAG_10_Red.blp:24|t|cff004000需要:[|cff800000" << sObjectMgr->GetItemNameLink(itr->second.ReqItem4) << "|cff004000] " << itr->second.ReqCount4 << "个";
				if (player->GetItemCount(itr->second.ReqItem4, false) + player->GetItemCount(itr->second.ReqItemBd4, false) >= itr->second.ReqCount4)
				{
					ss << " |cff004000√|r";
				}
				else
				{
					ss << " |cff800000×|r";
					isUpgrade = false;
				}
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, 0, ss.str().c_str(), 1, 1, "", 0);
			}

			if (itr->second.ReqItem5 > 0)
			{
				ss.str("");
				ss << "|TInterface\\ICONS\\INV_Misc_Bag_10.blp:24|t|cff004000需要:[|cff800000" << sObjectMgr->GetItemNameLink(itr->second.ReqItem5) << "|cff004000] " << itr->second.ReqCount5 << "个";
				if (player->GetItemCount(itr->second.ReqItem5, false) + player->GetItemCount(itr->second.ReqItemBd5, false) >= itr->second.ReqCount5)
				{
					ss << " |cff004000√|r";
				}
				else
				{
					ss << " |cff800000×|r";
					isUpgrade = false;
				}
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(9, 0, ss.str().c_str(), 1, 1, "", 0);
			}


			if (itr->second.JbCount > 0)
			{
				ss.str("");
				ss << "|TInterface\\ICONS\\inv_misc_markoftheworldtree.blp:24|t|cff004000需要金币: |cff0000FF" << itr->second.JbCount;
				if ((player->GetMoney() * 10000) < itr->second.JbCount)
				{
					ss << " |cff800000×|r";
					isUpgrade = false;
				}
				else
				{
					ss << " |cff004000√|r";
				}
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(10, 0, ss.str().c_str(), 1, 1, "", 0);
			}

			if (itr->second.VipLevel > 0)
			{
				ss.str("");
				ss << "|cff004000需要: 【|cff800000" << itr->second.VipLevel << "|cff004000】 级会员";
				if (player->GetPlayerViplevel() < itr->second.VipLevel)
				{
					ss << " |cff800000×|r";
					isUpgrade = false;
				}
				else
				{
					ss << " |cff800000√|r";
				}
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 1, 1, "", 0);
			}

			//if (itr->second.PvpLevel > 0)
			//{
			//ss.str("");
			//ss << "|cff004000需要: 【|cff800000" << itr->second.PvpLevel << "|cff004000】 级PVP等级";
			//if (player->GetPlayerPvprankLevel() < itr->second.PvpLevel)
			//{
			//	ss << " |cff800000×|r";
			//	isUpgrade = false;
			//}
			//else
			//{
			//	ss << " |cff800000√|r";
			//}
			//player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 1, 1, "", 0);
			//}

			//if (itr->second.PveLevel > 0)
			//{
			//ss.str("");
			//ss << "|cff004000需要: 【|cff800000" << itr->second.PveLevel << "|cff004000】 级PVE等级";
			//if (player->GetPlayerPverankLevel() < itr->second.PveLevel)
			//{
			//	ss << " |cff800000×|r";
			//	isUpgrade = false;
			//}
			//else
			//{
			//	ss << " |cff800000√|r";
			//}
			//player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 1, 1, "", 0);
			//}

			uint32 guardyItem = sWorld->getIntConfig(GUARDITEM);
			uint32 pro = itr->second.Pro;
			uint32 proItem = sWorld->getIntConfig(PROITEM);		// 幸运宝石ID
			uint32 maxPro = sWorld->getIntConfig(PROCOUNT);	// 一次最多可使用幸运宝石数量
			uint32 AddPro = sWorld->getIntConfig(ADDPRO);	// 获取增加的成功率
			uint32 haspro = player->GetItemCount(proItem, false);	// 获取玩家拥有的幸运宝石数
			uint32 proItem1 = sWorld->getIntConfig(PROITEM1);		// 幸运宝石ID1
			uint32 maxPro1 = sWorld->getIntConfig(PROCOUNT1);	// 一次最多可使用幸运宝石数量1
			uint32 AddPro1 = sWorld->getIntConfig(ADDPRO1);	// 获取增加的成功率1
			uint32 haspro1 = player->GetItemCount(proItem1, false);	// 获取玩家拥有的幸运宝石数1
			uint32 proItem2 = sWorld->getIntConfig(PROITEM2);		// 幸运宝石ID2
			uint32 maxPro2 = sWorld->getIntConfig(PROCOUNT2);	// 一次最多可使用幸运宝石数量2
			uint32 AddPro2 = sWorld->getIntConfig(ADDPRO2);	// 获取增加的成功率2
			uint32 haspro2 = player->GetItemCount(proItem2, false);	// 获取玩家拥有的幸运宝石数2
			uint32 proItem3 = sWorld->getIntConfig(PROITEM3);		// 幸运宝石ID3
			uint32 maxPro3 = sWorld->getIntConfig(PROCOUNT3);	// 一次最多可使用幸运宝石数量3
			uint32 AddPro3 = sWorld->getIntConfig(ADDPRO3);	// 获取增加的成功率3
			uint32 haspro3 = player->GetItemCount(proItem3, false);	// 获取玩家拥有的幸运宝石数3
			haspro = haspro < maxPro ? haspro : maxPro;
			haspro1 = haspro1 < maxPro1 ? haspro1 : maxPro1;
			haspro2 = haspro2 < maxPro2 ? haspro2 : maxPro2;
			haspro3 = haspro3 < maxPro3 ? haspro3 : maxPro3;
			pro += (AddPro * haspro) + (AddPro1 * haspro1) + (AddPro2 * haspro2) + (AddPro3 * haspro3) + GetAddUpPro(player);
			pro = pro > 100 ? 100 : pro;

			ss.str("");
			ss << "|cff004000基础成功率:|cff800000" << itr->second.Pro << "%";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, ss.str().c_str(), 1, 1, "", 0);
			ss.str("");
			ss << "|cff004000当前VIP加成(" << GetAddUpPro(player) << "%)" << "包内幸运宝石加成(" << (AddPro * haspro) + (AddPro1 * haspro1) + (AddPro2 * haspro2) + (AddPro3 * haspro3) << "%)";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(14, 0, ss.str().c_str(), 1, 1, "", 0);
			ss.str("");
			ss << "|cff004000最终成功率:|cff800000" << itr->second.Pro + GetAddUpPro(player) + (AddPro * haspro) + (AddPro1 * haspro1) + (AddPro2 * haspro2) + (AddPro3 * haspro3) << "%";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(15, 0, ss.str().c_str(), 1, 1, "", 0);
			if (itr->second.Destory == 0)
			{
				if (guardyItem > 0 && player->GetItemCount(guardyItem, false) > 0)
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(16, 0, "|cff004000失败后: |cff800000 销毁|r |cff004000(有防暴)", 1, 1, "", 0);
				else
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(17, 0, "|cff004000失败后: |cff800000 销毁|r |cff004000(无防暴)", 1, 1, "", 0);
			}
			else
				if (itr->second.Destory == itr->second.ItemID){
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(18, 0, "|cff004000失败后: |cff800000 不变|r", 1, 1, "", 0);
				}
				else
				{
					ss.str("");
					ss << "|cff004000失败后变成:  [" << sObjectMgr->GetItemNameLink(itr->second.Destory) << "]";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(19, 0, ss.str().c_str(), 1, 1, "", 0);
				}

			if (itr->second.RewItem == 0)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, "|cff004000成功后: |cff800000 销毁!?|r", 1, 1, "", 0);
			}
			else
			{
				ss.str("");
				ss << "|cff004000成功后:[|cff590248" << sObjectMgr->GetItemNameLink(itr->second.RewItem) << "|cff004000]";
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(21, 0, ss.str().c_str(), 1, 1, "", 0);
			}

			if (isUpgrade)
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(22, 1, "->>      点击此处升级     <<-", 1, 1000, "", 0);
			}
			else
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(23, 0, "|cff800000->>    不满足升级条件    <<-|r", 1, 1, "", 0);
			}
			player->PlayerTalkClass->SendGossipMenu(907, m_from->GetGUID());
			return;
		}
	}
}


void ObjectMgr::UpgradeThisItem(Item *target, Player *player, Item* m_from)
{
	if (!target || !m_from || !player)
		return;

	uint32 itemId = target->GetEntry();
	uint32 fromid = m_from->GetEntry();
	const std::string itemname = target->GetTemplate()->Name1;
	const std::string fromname = m_from->GetTemplate()->Name1;

	for (xxItemupMap::const_iterator itr = _xxItemupMap.begin(); itr != _xxItemupMap.end(); ++itr)
	{
		if (fromid != itr->second.FromId && itr->second.FromId != 0)		// 不是使用这个强化宝石
			continue;

		if (itemId == itr->second.ItemID)
		{
			// 销毁原物品
			player->DestroyItemCount(target->GetEntry(), 1, true);

			if (itr->second.JFCost > 0)
			{
				player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), itr->second.JFCost, true);
			}

			if (itr->second.JbCount > 0)
			{
				player->ModifyMoney(-int32(itr->second.JbCount * 10000));
			}

			if (itr->second.ReqItem1 > 0 && itr->second.ReqCount1 > 0)	// 需要物品1
			{
				if (player->GetItemCount(itr->second.ReqItemBd1, false) >= itr->second.ReqCount1)
				{
					player->DestroyItemCount(itr->second.ReqItemBd1, itr->second.ReqCount1, true);
				}
				else
				{
					uint32 a = itr->second.ReqCount1 - player->GetItemCount(itr->second.ReqItemBd1, false);
					uint32 b = itr->second.ReqCount1 - a;
					if (b == 0)
					{
						player->DestroyItemCount(itr->second.ReqItem1, itr->second.ReqCount1, true);
					}
					else
					{
						player->DestroyItemCount(itr->second.ReqItem1, a, true);
						player->DestroyItemCount(itr->second.ReqItemBd1, b, true);
					}

				}
			}

			if (itr->second.ReqItem2 > 0 && itr->second.ReqCount2 > 0)	// 需要物品2
			{
				if (player->GetItemCount(itr->second.ReqItemBd2, false) >= itr->second.ReqCount2)
				{
					player->DestroyItemCount(itr->second.ReqItemBd2, itr->second.ReqCount2, true);
				}
				else
				{
					uint32 a = itr->second.ReqCount2 - player->GetItemCount(itr->second.ReqItemBd2, false);
					uint32 b = itr->second.ReqCount2 - a;
					if (b == 0)
					{
						player->DestroyItemCount(itr->second.ReqItem2, itr->second.ReqCount2, true);
					}
					else
					{
						player->DestroyItemCount(itr->second.ReqItem2, a, true);
						player->DestroyItemCount(itr->second.ReqItemBd2, b, true);
					}

				}
			}

			if (itr->second.ReqItem3 > 0 && itr->second.ReqCount3 > 0)	// 需要物品3
			{
				if (player->GetItemCount(itr->second.ReqItemBd3, false) >= itr->second.ReqCount3)
				{
					player->DestroyItemCount(itr->second.ReqItemBd3, itr->second.ReqCount3, true);
				}
				else
				{
					uint32 a = itr->second.ReqCount3 - player->GetItemCount(itr->second.ReqItemBd3, false);
					uint32 b = itr->second.ReqCount3 - a;
					if (b == 0)
					{
						player->DestroyItemCount(itr->second.ReqItem3, itr->second.ReqCount3, true);
					}
					else
					{
						player->DestroyItemCount(itr->second.ReqItem3, a, true);
						player->DestroyItemCount(itr->second.ReqItemBd3, b, true);
					}

				}
			}

			if (itr->second.ReqItem4 > 0 && itr->second.ReqCount4 > 0)	// 需要物品4
			{
				if (player->GetItemCount(itr->second.ReqItemBd4, false) >= itr->second.ReqCount4)
				{
					player->DestroyItemCount(itr->second.ReqItemBd4, itr->second.ReqCount4, true);
				}
				else
				{
					uint32 a = itr->second.ReqCount4 - player->GetItemCount(itr->second.ReqItemBd4, false);
					uint32 b = itr->second.ReqCount4 - a;
					if (b == 0)
					{
						player->DestroyItemCount(itr->second.ReqItem4, itr->second.ReqCount4, true);
					}
					else
					{
						player->DestroyItemCount(itr->second.ReqItem4, a, true);
						player->DestroyItemCount(itr->second.ReqItemBd4, b, true);
					}

				}
			}

			if (itr->second.ReqItem5 > 0 && itr->second.ReqCount5 > 0)	// 需要物品5
			{
				if (player->GetItemCount(itr->second.ReqItemBd5, false) >= itr->second.ReqCount5)
				{
					player->DestroyItemCount(itr->second.ReqItemBd5, itr->second.ReqCount5, true);
				}
				else
				{
					uint32 a = itr->second.ReqCount5 - player->GetItemCount(itr->second.ReqItemBd5, false);
					uint32 b = itr->second.ReqCount5 - a;
					if (b == 0)
					{
						player->DestroyItemCount(itr->second.ReqItem5, itr->second.ReqCount5, true);
					}
					else
					{
						player->DestroyItemCount(itr->second.ReqItem5, a, true);
						player->DestroyItemCount(itr->second.ReqItemBd5, b, true);
					}

				}
			}


			// 销毁原物品
			uint32 x = urand(1, 100), pro = itr->second.Pro, haspro = 0, haspro1 = 0, haspro2 = 0, haspro3 = 0;
			uint32 proItem = sWorld->getIntConfig(PROITEM);
			uint32 maxPro = sWorld->getIntConfig(PROCOUNT);
			uint32 AddPro = sWorld->getIntConfig(ADDPRO);
			//uint32 haspro = player->GetItemCount(proItem, false);	// 获取玩家拥有的幸运宝石数
			uint32 proItem1 = sWorld->getIntConfig(PROITEM1);		// 幸运宝石ID1
			uint32 maxPro1 = sWorld->getIntConfig(PROCOUNT1);	// 一次最多可使用幸运宝石数量1
			uint32 AddPro1 = sWorld->getIntConfig(ADDPRO1);	// 获取增加的成功率1
			uint32 proItem2 = sWorld->getIntConfig(PROITEM2);		// 幸运宝石ID2
			uint32 maxPro2 = sWorld->getIntConfig(PROCOUNT2);	// 一次最多可使用幸运宝石数量2
			uint32 AddPro2 = sWorld->getIntConfig(ADDPRO2);	// 获取增加的成功率2
			uint32 proItem3 = sWorld->getIntConfig(PROITEM3);		// 幸运宝石ID3
			uint32 maxPro3 = sWorld->getIntConfig(PROCOUNT3);	// 一次最多可使用幸运宝石数量3
			uint32 AddPro3 = sWorld->getIntConfig(ADDPRO3);	// 获取增加的成功率3

			if (proItem>0)
			{
				haspro = player->GetItemCount(proItem, false);
				haspro = haspro < maxPro ? haspro : maxPro;
			}
			if (proItem1>0)
			{
				haspro1 = player->GetItemCount(proItem1, false);
				haspro1 = haspro1 < maxPro1 ? haspro1 : maxPro1;
			}
			if (proItem2>0)
			{
				haspro2 = player->GetItemCount(proItem2, false);
				haspro2 = haspro2 < maxPro2 ? haspro2 : maxPro2;
			}
			if (proItem3>0)
			{
				haspro3 = player->GetItemCount(proItem3, false);
				haspro3 = haspro3 < maxPro3 ? haspro3 : maxPro3;
			}

			pro += (AddPro * haspro) + (AddPro1 * haspro1) + (AddPro2 * haspro2) + (AddPro3 * haspro3) + GetAddUpPro(player);
			pro = pro > 100 ? 100 : pro;
			player->DestroyItemCount(proItem, haspro, true);
			player->DestroyItemCount(proItem1, haspro1, true);
			player->DestroyItemCount(proItem2, haspro2, true);
			player->DestroyItemCount(proItem3, haspro3, true);

			if (x <= pro)		// 中奖
			{
				// 发送新道具
				player->AddItem(itr->second.RewItem, 1);
				ChatHandler(player).PSendSysMessage(22038, itemId, itemname, itr->second.RewItem, sObjectMgr->GetItemNameLink(itr->second.RewItem));

			}
			else{
				if (itr->second.Destory == itr->second.ItemID)
				{			// 物品不变
					player->AddItem(itr->second.ItemID, 1);
					ChatHandler(player).PSendSysMessage(22040, itemId, itemname);
					player->PlayerTalkClass->SendCloseGossip();
					return;
				}

				uint32 guardyItem = sWorld->getIntConfig(GUARDITEM);
				if (guardyItem > 0)
				{
					if (player->GetItemCount(guardyItem, false) > 0)
					{
						player->AddItem(itr->second.ItemID, 1);
						player->DestroyItemCount(guardyItem, 1, true);
						ChatHandler(player).PSendSysMessage(22042, itemId, itemname);
						player->PlayerTalkClass->SendCloseGossip();
						return;
					}
				}

				if (itr->second.Destory == 0)
				{			// 摧毁
					ChatHandler(player).PSendSysMessage(22041, itemId, itemname);
				}
				else{		// 获得失败后物品
					ChatHandler(player).PSendSysMessage(22039, itemId, itemname, itr->second.Destory, sObjectMgr->GetItemNameLink(itr->second.Destory));
					player->AddItem(itr->second.Destory, 1);
				}
			}
			player->PlayerTalkClass->SendCloseGossip();
			return;
		}
	}
}

uint32 ObjectMgr::GetBattlegroundValue(uint32 bgtype, uint32 index)
{
	xxBattleMap::const_iterator itr = _xxBattleMap.find(bgtype);
	if (itr == _xxBattleMap.end())
	{
		return 0;
	}

	switch (index)
	{
	case 1:
		return itr->second.winitem;
	case 2:
		return itr->second.winitem1;
	case 3:
		return itr->second.winitem2;
	case 4:
		return itr->second.winitem3;
	case 5:
		return itr->second.wincount;
	case 6:
		return itr->second.wincount1;
	case 7:
		return itr->second.wincount2;
	case 8:
		return itr->second.wincount3;
	case 11:
		return itr->second.loseitem;
	case 12:
		return itr->second.loseitem1;
	case 13:
		return itr->second.loseitem2;
	case 14:
		return itr->second.loseitem3;
	case 15:
		return itr->second.losecount;
	case 16:
		return itr->second.losecount1;
	case 17:
		return itr->second.losecount2;
	case 18:
		return itr->second.losecount3;
	case 21:
		return itr->second.killitem;
	case 22:
		return itr->second.killitem1;
	case 23:
		return itr->second.killitem2;
	case 24:
		return itr->second.killitem3;
	case 25:
		return itr->second.killcount;
	case 26:
		return itr->second.killcount1;
	case 27:
		return itr->second.killcount2;
	case 28:
		return itr->second.killcount3;
	}
	return 0;
}

void ObjectMgr::ShowFuyinMenu(Player* player, Item* pitem)
{

	player->PlayerTalkClass->ClearMenus();
	uint32 jinbi = 10;
	std::stringstream ss("");

	//判断有点数 显示加点菜单

	ss.str("");
	ss << "你当前剩余可加点数|cff004000" << player->GetFuyin() << "|r点";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
	
	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "共加点" << player->GetPlayerJfypoint(0) << "|r次|Cffff00ff=提高攻击强度|CFF00FF00" << player->GetPlayerJfypoint(0) << "|Cffff00ff%|CFF00ff11╋|r";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 1011, 1011, "", 0);


	ss.str("");
	ss << "共加点" << player->GetPlayerJfypoint(1) << "|r次|Cffff00ff=提高法术强度|CFF00FF00" << player->GetPlayerJfypoint(1) << "|Cffff00ff%|CFF00ff11╋|r";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 1011, 1012, "", 0);

	ss.str("");
	ss << "共加点" << player->GetPlayerJfypoint(2) << "|r次|Cffff00ff=提高生命上限|CFF00FF00" << player->GetPlayerJfypoint(2) << "|Cffff00ff%|CFF00ff11╋|r";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 1011, 1013, "", 0);



	ss.str("");
	ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00重置所有已加点数|r费用" << jinbi << "金币";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5,0,ss.str().c_str(),1019,1019,"",0);


	player->PlayerTalkClass->SendGossipMenu(907, pitem->GetGUID());
}

void ObjectMgr::ShowJntpMenu(Player* player, Item* pitem)
{

	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	xxjntp::iterator itr = m_xxjntpmap.find(player->GetJntp() + 1);
	if (itr == m_xxjntpmap.end())
		return;
	//判断有点数 显示加点菜单
	bool a = true;
	bool b = true;
	bool c = true;
	ss.str("");
	ss << "你当前神技突破等级|cff004000" << player->GetJntp() << "|r级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "神技(光明审判)为你自身提高攻击强度" << player->GetJntp() * 1000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJntp() + 1) * 1000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);


	ss.str("");
	ss << "神技(光明审判)为你自身提高法术强度" << player->GetJntp() * 1000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJntp() + 1) * 1000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "神技(光明审判)为你自身提高生命上限" << player->GetJntp() * 2000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJntp() + 1) * 2000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "神技(光明审判)技能伤害受到" << player->GetJntp() + 1 << "%主属性加成|r|Cffff00ff↑|CFF00FF00" << player->GetJntp() + 2 << "%主属性加成";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "本次突破需要消耗：";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 0, "", 0);
	if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
	{
		if (player->GetItemCount(itr->second.reqitem1, false) >= itr->second.reqitemcount1)
			a = true;
		else
			a = false;

		ss.str("");
		ss << GetItemNameLink(itr->second.reqitem1) << "X" << itr->second.reqitemcount1;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (itr->second.reqitem2 > 0 && itr->second.reqitemcount2 > 0)
	{
		if (player->GetItemCount(itr->second.reqitem2, false) >= itr->second.reqitemcount2)
			b = true;
		else
			b = false;

		ss.str("");
		ss << GetItemNameLink(itr->second.reqitem2) << "X" << itr->second.reqitemcount2;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(14, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (itr->second.jb > 0)
	{
		if ((player->GetMoney() * 10000) >= itr->second.jb)
			c = true;
		else
			c = false;

		ss.str("");
		ss << "金币：" << "X" << itr->second.jb;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(15, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	
	if (player->GetJntp() <= itr->second.shangxian)
	{
		if (a && b && c)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00点击进行进行突破";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 1011, 1011, "", 0);
		}
		else
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00所需物品不足，无法突破";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 0, "", 0);
		}
		
	}
	else
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00已经达到最高突破等级";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 0, "", 0);
	}


	player->PlayerTalkClass->SendGossipMenu(60011, pitem->GetGUID());
}

void ObjectMgr::ShowJnjxMenu(Player* player, Item* pitem)
{

	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	xxjnjx::iterator itr = m_xxjnjxmap.find(player->GetJnjx() + 1);
	if (itr == m_xxjnjxmap.end())
		return;
	//判断有点数 显示加点菜单
	bool a = true;
	bool b = true;
	bool c = true;
	ss.str("");
	ss << "你当前神技觉醒等级|cff004000" << player->GetJnjx() << "|r级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "神技(光明审判)为你自身提高攻击强度" << player->GetJnjx() * 2000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJnjx() + 1) * 2000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);


	ss.str("");
	ss << "神技(光明审判)为你自身提高法术强度" << player->GetJnjx() * 2000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJnjx() + 1) * 2000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "神技(光明审判)为你自身提高生命上限" << player->GetJnjx() * 4000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJnjx() + 1) * 4000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "神技(光明审判)技能伤害提高" << player->GetJnjx() * 10000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJnjx() + 1) * 10000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "本次觉醒需要消耗：";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 0, "", 0);
	if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
	{
		if (player->GetItemCount(itr->second.reqitem1, false) >= itr->second.reqitemcount1)
			a = true;
		else
			a = false;

		ss.str("");
		ss << GetItemNameLink(itr->second.reqitem1) << "X" << itr->second.reqitemcount1;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (itr->second.reqitem2 > 0 && itr->second.reqitemcount2 > 0)
	{
		if (player->GetItemCount(itr->second.reqitem2, false) >= itr->second.reqitemcount2)
			b = true;
		else
			b = false;

		ss.str("");
		ss << GetItemNameLink(itr->second.reqitem2) << "X" << itr->second.reqitemcount2;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(14, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (itr->second.jb > 0)
	{
		if ((player->GetMoney() * 10000) >= itr->second.jb)
			c = true;
		else
			c = false;

		ss.str("");
		ss << "金币：" << "X" << itr->second.jb;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(15, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (player->GetJntp() <= itr->second.shangxian)
	{
		if (a && b && c)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00点击进行进行觉醒";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 1012, 1012, "", 0);
		}
		else
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00所需物品不足，无法觉醒";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 0, "", 0);
		}
	}
	else
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00已经达到最高觉醒等级";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 0, "", 0);
	}


	player->PlayerTalkClass->SendGossipMenu(60012, pitem->GetGUID());
}

void ObjectMgr::ShowJnpyMenu(Player* player, Item* pitem)
{

	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	xxjnpy::iterator itr = m_xxjnpymap.find(player->GetJnpy() + 1);
	if (itr == m_xxjnpymap.end())
		return;
	//判断有点数 显示加点菜单

	bool a = true;
	bool b = true;
	bool c = true;

	ss.str("");
	ss << "你当前神技培养等级|cff004000" << player->GetJnpy() << "|r级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "神技(光明审判)为你自身提高攻击强度" << player->GetJnpy() * 3000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJnpy() + 1) * 3000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);


	ss.str("");
	ss << "神技(光明审判)为你自身提高法术强度" << player->GetJnpy() * 3000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJnpy() + 1) * 3000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "神技(光明审判)为你自身提高生命上限" << player->GetJnpy() * 6000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJnpy() + 1) * 6000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "神技(光明审判)技能伤害提高" << player->GetJnpy() * 1000 << "|r|Cffff00ff↑|CFF00FF00" << (player->GetJnpy() + 1) * 1000;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "本次培养需要消耗：";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 0, "", 0);
	if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
	{
		if (player->GetItemCount(itr->second.reqitem1, false) >= itr->second.reqitemcount1)
			a = true;
		else
			a = false;

		ss.str("");
		ss << GetItemNameLink(itr->second.reqitem1) << "X" << itr->second.reqitemcount1;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (itr->second.reqitem2 > 0 && itr->second.reqitemcount2 > 0)
	{
		if (player->GetItemCount(itr->second.reqitem2, false) >= itr->second.reqitemcount2)
			b = true;
		else
			b = false;

		ss.str("");
		ss << GetItemNameLink(itr->second.reqitem2) << "X" << itr->second.reqitemcount2;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(14, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (itr->second.jb > 0)
	{
		if ((player->GetMoney() * 10000) >= itr->second.jb)
			c = true;
		else
			c = false;
		ss.str("");
		ss << "金币：" << "X" << itr->second.jb;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(15, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (player->GetJntp() <= itr->second.shangxian)
	{
		if (a && b && c)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00点击进行进行培养";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 1013, 1013, "", 0);
		}
		else
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00所需物品不足，无法培养";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 0, "", 0);
		}
	}
	else
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00已经达到最高培养等级";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 0, "", 0);
	}


	player->PlayerTalkClass->SendGossipMenu(60013, pitem->GetGUID());
}

void ObjectMgr::Updatejntp(Player* player, Item* pitem, uint32 uiAction)
{
	xxjntp::iterator itr = m_xxjntpmap.find(player->GetJntp() + 1);
	if (itr == m_xxjntpmap.end())
		return;

	//获得剩余点数
	switch (uiAction)
	{
	case 1011: //升级攻击强度

			if (itr->second.jb > 0)
				player->ModifyMoney(-int32(itr->second.jb * 10000));
			if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
				player->DestroyItemCount(itr->second.reqitem1, itr->second.reqitemcount1, true);
			if (itr->second.reqitem2 > 0 && itr->second.reqitemcount2 > 0)
				player->DestroyItemCount(itr->second.reqitem2, itr->second.reqitemcount2, true);
			player->ModifyJntp(1);
			player->UpdateAttackPowerAndDamage();
			player->UpdateAttackPowerAndDamage(true);
			player->UpdateSpellDamageAndHealingBonus();
			player->UpdateMaxHealth();
			ShowJntpMenu(player, pitem);
		break;
	}
	return;
}

void ObjectMgr::Updatejnjx(Player* player, Item* pitem, uint32 uiAction)
{
	xxjnjx::iterator itr = m_xxjnjxmap.find(player->GetJnjx() + 1);
	if (itr == m_xxjnjxmap.end())
		return;

	//获得剩余点数
	switch (uiAction)
	{
	case 1012: //升级攻击强度

		if (itr->second.jb > 0)
			player->ModifyMoney(-int32(itr->second.jb * 10000));
		if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
			player->DestroyItemCount(itr->second.reqitem1, itr->second.reqitemcount1, true);
		if (itr->second.reqitem2 > 0 && itr->second.reqitemcount2 > 0)
			player->DestroyItemCount(itr->second.reqitem2, itr->second.reqitemcount2, true);
		player->ModifyJnjx(1);
		player->UpdateAttackPowerAndDamage();
		player->UpdateAttackPowerAndDamage(true);
		player->UpdateSpellDamageAndHealingBonus();
		player->UpdateMaxHealth();
		ShowJnjxMenu(player, pitem);
		break;
	}
	return;
}

void ObjectMgr::Updatejnpy(Player* player, Item* pitem, uint32 uiAction)
{
	xxjnpy::iterator itr = m_xxjnpymap.find(player->GetJnpy() + 1);
	if (itr == m_xxjnpymap.end())
		return;

	//获得剩余点数
	switch (uiAction)
	{
	case 1013: //升级攻击强度

		if (itr->second.jb > 0)
			player->ModifyMoney(-int32(itr->second.jb * 10000));
		if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
			player->DestroyItemCount(itr->second.reqitem1, itr->second.reqitemcount1, true);
		if (itr->second.reqitem2 > 0 && itr->second.reqitemcount2 > 0)
			player->DestroyItemCount(itr->second.reqitem2, itr->second.reqitemcount2, true);
		player->ModifyJnpy(1);
		player->UpdateAttackPowerAndDamage();
		player->UpdateAttackPowerAndDamage(true);
		player->UpdateSpellDamageAndHealingBonus();
		player->UpdateMaxHealth();
		ShowJnpyMenu(player, pitem);
		break;
	}
	return;
}

void ObjectMgr::Updatefuyin(Player* player, Item* pitem, uint32 uiAction)
{
	//获得剩余点数
	uint32 jinbi = 10;
	switch (uiAction)
	{
	case 1011: //升级攻击强度

		if (player->GetFuyin() > 0)
		{
			player->ModifyFuyin(-1);
			player->ModifyPlayerJfypoint(1, 0);//加攻击强度点数
			ShowFuyinMenu(player, pitem);
			player->UpdateAttackPowerAndDamage();
			player->UpdateAttackPowerAndDamage(true);
			
		}
		else
		{
			ChatHandler(player).PSendSysMessage("点数不足，无法进行此操作");
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;
	case 1012://升级法术强度
		if (player->GetFuyin() > 0)
		{
			player->ModifyFuyin(-1);
			player->ModifyPlayerJfypoint(1, 1);//加点数
			ShowFuyinMenu(player, pitem);
			player->UpdateSpellDamageAndHealingBonus();
		}
		else
		{
			ChatHandler(player).PSendSysMessage("点数不足，无法进行此操作");
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;
	case 1013:
		if (player->GetFuyin() > 0)
		{
			player->ModifyFuyin(-1);
			player->ModifyPlayerJfypoint(1, 2);//加点数
			ShowFuyinMenu(player, pitem);
			player->UpdateMaxHealth();
		}
		else
		{
			ChatHandler(player).PSendSysMessage("点数不足，无法进行此操作");
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;
	case 1019:
		if ((player->GetMoney() * 10000) >= jinbi * 10000)
		{
			int32 j;
			for (int i = 0; i <= 2; i++)
			{
				j = (int32)player->GetPlayerJfypoint(i);
				player->ModifyFuyin(j);//加点数
				player->ModifyPlayerJfypoint(-j, i);//加力量点数
			}
			player->ModifyMoney(-int32(jinbi * 10000));
			ShowFuyinMenu(player, pitem);
			player->UpdateAttackPowerAndDamage();
			player->UpdateAttackPowerAndDamage(true);
			player->UpdateSpellDamageAndHealingBonus();
			player->UpdateMaxHealth();
			ChatHandler(player).PSendSysMessage("符印点重置成功,请下次谨慎加点");
		}
		else
		{
			ChatHandler(player).PSendSysMessage("金币不足，无法进行此操作");
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;
	}
		/*case 5:
		if (Getfuyinjp4(player, 2) > 0)
		{
			if (player->GetItemCount(Getfuyinjp4(player, 1)) >= Getfuyinjp4(player, 2))
				player->DestroyItemCount(Getfuyinjp4(player, 1), Getfuyinjp4(player, 2), true);
			else
			{
				ChatHandler(player).PSendSysMessage("您的升级物品不足");
				player->PlayerTalkClass->SendCloseGossip();
				return;
			}//扣点数
			player->ModifyPlayerJfypoint(1, 5);//加点数
			player->ModifymyfyStats(4, (int32)jefypoint[4]);//加属性属性点
			player->ModifyFuyin(1);
			//ShowFuyinMenu(player, pitem);
		}
		else
		{
			ChatHandler(player).PSendSysMessage("不足条件无法进行此操作");
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;
	case 6:
		if (Getfuyinjp5(player, 2) > 0)
		{
			if (player->GetItemCount(Getfuyinjp5(player, 1)) >= Getfuyinjp5(player, 2))
				player->DestroyItemCount(Getfuyinjp5(player, 1), Getfuyinjp5(player, 2), true);
			else
			{
				ChatHandler(player).PSendSysMessage("您的升级物品不足");
				player->PlayerTalkClass->SendCloseGossip();
				return;
			}//扣点数
			player->ModifyPlayerJfypoint(1, 6);//加点数
			player->ModifymyfyStats(5, (int32)jefypoint[5]);//加属性属性点
			player->ModifyFuyin(1);
			//ShowFuyinMenu(player, pitem);
		}
		else
		{
			ChatHandler(player).PSendSysMessage("不足条件无法进行此操作");
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;
	case 7:
		if (Getfuyinjp6(player, 2) > 0)
		{
			if (player->GetItemCount(Getfuyinjp6(player, 1)) >= Getfuyinjp6(player, 2))
				player->DestroyItemCount(Getfuyinjp6(player, 1), Getfuyinjp6(player, 2), true);
			else
			{
				ChatHandler(player).PSendSysMessage("您的升级物品不足");
				player->PlayerTalkClass->SendCloseGossip();
				return;
			}//扣点数
			player->ModifyPlayerJfypoint(1, 7);//加点数
			player->ModifymyfyStats(6, (int32)jefypoint[6]);//加属性属性点
			player->ModifyFuyin(1);
			//ShowFuyinMenu(player, pitem);
		}
		else
		{
			ChatHandler(player).PSendSysMessage("不足条件无法进行此操作");
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;
	case 10:
		if (Getfuyinjp7(player, 2) > 0)
		{
			if (player->GetItemCount(Getfuyinjp7(player, 1)) >= Getfuyinjp7(player, 2))
				player->DestroyItemCount(Getfuyinjp7(player, 1), Getfuyinjp7(player, 2), true);
			else
			{
				ChatHandler(player).PSendSysMessage("您的升级物品不足");
				player->PlayerTalkClass->SendCloseGossip();
				return;
			}//扣点数
			player->ModifyPlayerJfypoint(1, 8);//加点数
			player->ModifymyfyStats(7, (int32)jefypoint[7]);//加属性属性点
			player->ModifyFuyin(1);
			//ShowFuyinMenu(player, pitem);
		}
		else
		{
			ChatHandler(player).PSendSysMessage("不足条件无法进行此操作");
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;
	case 9:
		if (Getfuyinjp8(player, 2) > 0)
		{
			if (player->GetItemCount(Getfuyinjp8(player, 1)) >= Getfuyinjp8(player, 2))
				player->DestroyItemCount(Getfuyinjp8(player, 1), Getfuyinjp8(player, 2), true);
			else
			{
				ChatHandler(player).PSendSysMessage("您的升级物品不足");
				player->PlayerTalkClass->SendCloseGossip();
				return;
			}//扣点数
			player->ModifyPlayerJfypoint(1, 9);//加点数
			player->ModifymyfyStats(9, (int32)jefypoint[9]);//加属性属性点
			player->ModifyFuyin(1);
			//ShowFuyinMenu(player, pitem);
		}
		else
		{
			ChatHandler(player).PSendSysMessage("不足条件无法进行此操作");
			player->PlayerTalkClass->SendCloseGossip();
		}
		break;

	}*/
	return;
}

uint32 ObjectMgr::GetAddOnlinePoint(Player* player)
{
	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(player->GetPlayerViplevel());
	if (itr == _xxVipSystemMap.end())
		return 0;

	return itr->second.add_online_point;
}

uint32 ObjectMgr::GetVipMrJl(Player* player, int8 sta, uint8 index)
{
	xxVipSystemMrMap::const_iterator itr = _xxVipSystemMrMap.find(player->GetPlayerViplevel());
	if (itr == _xxVipSystemMrMap.end())
		return 0;
	switch (index)
	{
	case 1:
		switch (sta)
		{
		case 0:
			return itr->second.RewardItemId1;
		case 1:
			return itr->second.RewardItemCount1;
		}
	case 2:
		switch (sta)
		{
		case 0:
			return itr->second.RewardItemId2;
		case 1:
			return itr->second.RewardItemCount2;
		}
	case 3:
		switch (sta)
		{
		case 0:
			return itr->second.RewardItemId3;
		case 1:
			return itr->second.RewardItemCount3;
		}
	case 4:
		switch (sta)
		{
		case 0:
			return itr->second.RewardItemId4;
		case 1:
			return itr->second.RewardItemCount4;
		}
	case 5:
		switch (sta)
		{
		case 0:
			return itr->second.RewardItemId5;
		case 1:
			return itr->second.RewardItemCount5;
		}
	}
	return 0;
}

const char* ObjectMgr::GetLoginAnnounce(Player *player)
{
	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(player->GetPlayerViplevel());

	if (itr == _xxVipSystemMap.end())
		return itr->second.LoginAnnounce.c_str();
	return itr->second.LoginAnnounce.c_str();
}

std::string ObjectMgr::GetVipTitle(Player* player)
{
	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(player->GetPlayerViplevel());
	if (itr == _xxVipSystemMap.end())
		return "";

	return itr->second.Title;
}

// 获取会员喊话颜色
std::string ObjectMgr::GetVipColor(Player* player)
{
	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(player->GetPlayerViplevel());
	if (itr == _xxVipSystemMap.end())
		return "";

	return itr->second.SayColor;
}

uint32 ObjectMgr::GetVipAura(Player* player)
{
	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(player->GetPlayerViplevel());
	if (itr == _xxVipSystemMap.end())
		return 0;

	return itr->second.Aura;
}

float ObjectMgr::GetVipShuXingStat(Player * player)
{
	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(player->GetPlayerViplevel());
	if (itr == _xxVipSystemMap.end())
		return 0;
	return itr->second.quanshuxing;

}

// 获取物品强化成功率加成
uint32 ObjectMgr::GetAddUpPro(Player* player)
{
	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(player->GetPlayerViplevel());
	if (itr == _xxVipSystemMap.end())
		return 0;

	return itr->second.rate_upgrade_pro;
}

// 获取升级会员获得物品奖励
uint32 ObjectMgr::GetUpdateVipRewarItem(Player *player)
{
	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(player->GetPlayerViplevel());

	if (itr == _xxVipSystemMap.end())
		return 0;

	if (itr->second.RewardItemCount == 0 || itr->second.RewardItemId == 0)
		return 0;

	player->AddItem(itr->second.RewardItemId, itr->second.RewardItemCount);
	return 0;
}

void ObjectMgr::ShowVipMenu(Player *player, Item *item)
{
	// 显示VIP菜单
	player->PlayerTalkClass->ClearMenus();
	uint32 nextlevel = player->GetPlayerViplevel() + 1;
	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(nextlevel);

	if (itr == _xxVipSystemMap.end())
	{
		std::stringstream ss("");
		ss << "|TInterface\\ICONS\\Achievement_PVP_A_15.blp:24|t|cff008000当前VIP等级:|cffFF0000" << player->GetPlayerViplevel() << "|cff008000级";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, "|TInterface\\ICONS\\Ability_Mage_TormentOfTheWeak.blp:24|t|cff0000A0VIP升至最高级无法继续提升!|r", 0, 0, "", 0);
		player->PlayerTalkClass->SendGossipMenu(907, item->GetGUID());
		return;
	}

	uint32 Jf = itr->second.req_jf;
	uint32 Rup = itr->second.rate_upgrade_pro;
	uint32 Aop = itr->second.add_online_point;
	uint32 LiLiang = itr->second.addliliang;
	uint32 MinJie = itr->second.addminjie;
	uint32 NaiLi = itr->second.addnaili;
	uint32 ZhiLi = itr->second.addzhili;
	uint32 JingShen = itr->second.addjingshen;
	uint32 JiSu = itr->second.addjisu;
	uint32 ItemId = itr->second.RewardItemId;
	uint32 ItemCount = itr->second.RewardItemCount;
	std::string titleid = itr->second.Title;
	uint32 ItemId1 = itr->second.ReqardItemId;
	uint32 ItemCount1 = itr->second.ReqardItemCount;
	std::string spelltitleid = itr->second.SpellTitle;
	//std::string yz=GetStringConfig(YINZINAME).c_str();

	std::stringstream ss("");
	//ss << "|cff008000绑定积分=积分,升级时优先消耗绑定积分,不够部分积分才由积分支出|r";
	//player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
	//ss.str("");
	ss << "|TInterface\\ICONS\\Achievement_PVP_A_15.blp:24|t|cff008000|cff008000当前VIP等级:|cffFF0000" << player->GetPlayerViplevel() << "|cff008000级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, "|TInterface\\ICONS\\Achievement_PVP_G_06.blp:18|t|cff0000A0升级到下一级需要:|r", 0, 0, "", 0);

	if (Jf>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000需要" << GetItemNameLink(sWorld->getIntConfig(CORE_JF_ID)) << ":[|cffFF0000" << Jf << "|cff008000]";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (Jf>0 && ItemId1>0 && ItemCount1>0)
	{
		ss.str("");
		ss << "|cff008000或者";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (ItemId1>0 && ItemCount1>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000物品:[|cffFF0000" << GetItemNameLink(ItemId1) << "|cff008000] x |cffFF0000" << ItemCount1;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(7, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	ss.str("");
	ss << "|TInterface\\ICONS\\Achievement_WorldEvent_Brewmaster.blp:18|t|cff008000获得VIP: |cffFF0000" << titleid;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, 0, ss.str().c_str(), 0, 0, "", 0);

	if (Rup>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级后加成:[|cffFF0000" << Rup << "|cff008000]点强化几率";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(9, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (Aop>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级后加成:[|cffFF0000" << Aop << "|cff008000]点积分泡点";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(10, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (itr->second.quanshuxing > 1)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级后加成:[|cffFF0000" << (float(itr->second.quanshuxing - 1)) * 100 << "%|cff008000]全属性";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (LiLiang>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级后加成:[|cffFF0000" << LiLiang << "|cff008000]力量";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (MinJie>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级后加成:[|cffFF0000" << MinJie << "|cff008000]敏捷";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (NaiLi>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级后加成:[|cffFF0000" << NaiLi << "|cff008000]耐力";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(14, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (ZhiLi>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级后加成:[|cffFF0000" << ZhiLi << "|cff008000]智力";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(15, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (JingShen>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级后加成:[|cffFF0000" << JingShen << "|cff008000]精神";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(16, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	if (JiSu>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级后加成:[|cffFF0000" << JiSu << "|cff008000]急速";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(17, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	ss.str("");
	ss << "|cff008000获得VIP属性: |cffFF0000" << spelltitleid;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(18, 0, ss.str().c_str(), 0, 0, "", 0);

	if (ItemId>0 && ItemCount>0)
	{
		ss.str("");
		ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000升级额外获得:[|cffFF0000" << GetItemNameLink(ItemId) << "|cff008000] x |cffFF0000" << ItemCount;
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(19, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, "      |TInterface\\ICONS\\Ability_Mage_FieryPayback.blp:16|t|cff008000-->> 点击升级 <<--|TInterface\\ICONS\\Ability_Mage_FieryPayback.blp:16|t", 0, 1100 + 2, "", 0);
	player->PlayerTalkClass->SendGossipMenu(907, item->GetGUID());
}

void ObjectMgr::VipLevelUP(Player *player, Item *item)
{
	uint32 nextlevel = player->GetPlayerViplevel() + 1;
	uint32 Jf = GetVipUINT32(nextlevel, 1);
	uint32 ItemId1 = GetVipUINT32(nextlevel, 2);
	uint32 ItemCount1 = GetVipUINT32(nextlevel, 3);
	bool allow = false;
	bool allowa = false;

	if (sWorld->getBoolConfig(CONFIG_AUTOVIPON))
	{
		if (ItemId1 > 0 && ItemCount1 > 0)
		{
			if (player->GetItemCount(ItemId1, false) >= ItemCount1)
			{
				allow = true;
			}
			else
				allow = false;
		}
		if (Jf > 0)
		{
			if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= Jf)
			{
				allow = true;
			}
			else
				allow = false;

		}

		if (allow)
		{

			if (Jf > 0)
			{
				player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), Jf, true);
			}

			if (ItemId1 > 0 && ItemCount1 > 0)
				player->DestroyItemCount(ItemId1, ItemCount1, true);

			player->SetPlayerVipLevel(nextlevel);
			player->LoginS();
			ChatHandler(player).PSendSysMessage(50097, player->GetPlayerViplevel());
			GetUpdateVipRewarItem(player);
			ShowVipMenu(player, item);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50096);
			ShowVipMenu(player, item);
		}
	}
	else
	{

		if (ItemId1 > 0 && ItemCount1 > 0)
		{
			if (player->GetItemCount(ItemId1, false) >= ItemCount1)
			{
				allowa = true;
			}
			else if (Jf > 0)
			{
				if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= Jf)
				{
					allow = true;
				}

			}

		}

		if (allowa)
		{

			if (ItemId1 > 0 && ItemCount1 > 0)
				player->DestroyItemCount(ItemId1, ItemCount1, true);

			player->SetPlayerVipLevel(nextlevel);

			///ShowBuffSpawn(player);
			player->LoginS();
			ChatHandler(player).PSendSysMessage(50097, player->GetPlayerViplevel());
			GetUpdateVipRewarItem(player);
			ShowVipMenu(player, item);
		}
		else if (allow)
		{

			if (Jf > 0)
			{
				player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), Jf, true);
			}

			player->SetPlayerVipLevel(nextlevel);
			player->LoginS();
			ChatHandler(player).PSendSysMessage(50097, player->GetPlayerViplevel());
			GetUpdateVipRewarItem(player);
			ShowVipMenu(player, item);
		}
		else
		{
			ChatHandler(player).PSendSysMessage(50096);
			ShowVipMenu(player, item);
		}
	}
}

uint32 ObjectMgr::GetVipUINT32(uint32 level, uint8 index)
{
	if (index>3)
		return 0;

	xxVipSystemMap::const_iterator itr = _xxVipSystemMap.find(level);
	if (itr == _xxVipSystemMap.end())
		return uint32(-1);

	switch (index)
	{
	case 0:
		return 0;
	case 1:
		return itr->second.req_jf;
	case 2:
		return itr->second.ReqardItemId;
	case 3:
		return itr->second.ReqardItemCount;
	}
	return 0;
}

std::string ObjectMgr::GetItemNameLink(uint32 ItemId)
{
	if (ItemId == 0)
		return "<UnKnow>";

	ItemTemplate const* proto = sObjectMgr->GetItemTemplate(ItemId);
	if (!proto)
		return "<UnKnow>";

	return proto->Name1;
}

void ObjectMgr::LoadxxCreatureTeleportMenu(uint32 MenuId, Player* player, Creature* pcreature)
{
	uint32 faction = 0;
	if (player->GetTeamId() == TEAM_ALLIANCE)
		faction = 1;
	else
		faction = 2;


	player->PlayerTalkClass->ClearMenus(); //清除菜单项

	for (xxCreatureTeleMap::iterator ltr = _xxCreatureTeleMap.begin(); ltr != _xxCreatureTeleMap.end(); ++ltr)
	{
		if (player->GetTeamId() == TEAM_ALLIANCE || player->GetTeamId() == TEAM_HORDE){
			if (ltr->second.parentid == MenuId && (ltr->second.factionid == 0 || faction == ltr->second.factionid))  // 载入指定页面的菜单
			{
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(ltr->second.menuid, 0, ltr->second.title.c_str(), ltr->second.menuid, ltr->second.usetype + 1000, "", 0);
			}
		}
		else{
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, "未加入阵营无法使用传送", 0, 0, "", 0);
		}
	}
	player->PlayerTalkClass->SendGossipMenu(907, pcreature->GetGUID()); // 发送菜单
}

bool ObjectMgr::RunxxCreatureTeleport(uint32 action, uint32 sender, Player *player, Creature *pcreature)
{
	if (player->IsInCombat())
	{
		player->PlayerTalkClass->ClearMenus();
		return false;
	}

	xxCreatureTeleMap::iterator itr = _xxCreatureTeleMap.find(sender);
	if (itr == _xxCreatureTeleMap.end())
	{
		switch (action)
		{
		case 1101:
			player->GetPayJF();
			return true;
		case 1102:
			player->GetJlJF();
			return true;
		
		}
		return false;
	}

	switch (action)
	{
	case 1000: // 显示指定菜单
		LoadxxCreatureTeleportMenu(sender, player, pcreature);
		return true;
	case 1001://传送
		xxCreatureTeleportFromMenuId(player, sender);
		break;
	case 1002://领取积分
		XxZz(player, pcreature);
		return true;
	case 1003://领取积分
		XxJl(player, pcreature);
		return true;
	case 1031:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(LOGIN_CHANGE_FACTION_JF))
		{
			player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
			CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '64' WHERE guid = %u", player->GetGUID());
			player->GetSession()->SendAreaTriggerMessage("重新登录以修改阵营");
			player->GetSession()->SendAreaTriggerMessage("感谢使用赞助服务");
			player->CastSpell(player, 47292, true, NULL, NULL, player->GetGUID());
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(LOGIN_CHANGE_FACTION_JF), true);
		}
		else player->GetSession()->SendNotification("你没有购买权限，请赞助我们 ");
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1032:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(LOGIN_CHANGE_RACE_JF))
		{
			player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
			CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '128' WHERE guid = %u", player->GetGUID());
			player->GetSession()->SendAreaTriggerMessage("重新登录以修改种族");
			player->GetSession()->SendAreaTriggerMessage("感谢使用赞助服务");
			player->CastSpell(player, 47292, true, NULL, NULL, player->GetGUID());
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(LOGIN_CHANGE_RACE_JF), true);
		}
		else player->GetSession()->SendNotification("你没有购买权限，请赞助我们 ");
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1033:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(LOGIN_CUSTOMIZE_JF))
		{
			player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
			CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '8' WHERE guid = %u", player->GetGUID());
			player->GetSession()->SendAreaTriggerMessage("重新登录以修改外观");
			player->GetSession()->SendAreaTriggerMessage("感谢使用赞助服务");
			player->CastSpell(player, 47292, true, NULL, NULL, player->GetGUID());
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(LOGIN_CUSTOMIZE_JF), true);
		}
		else player->GetSession()->SendNotification("你没有购买权限，请赞助我们 ");
		player->CLOSE_GOSSIP_MENU();
		break;
	case 1034:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= sWorld->getIntConfig(LOGIN_RENAME_JF))
		{
			player->SetAtLoginFlag(AT_LOGIN_RENAME);
			CharacterDatabase.PExecute("UPDATE characters SET at_login = at_login | '1' WHERE guid = %u", player->GetGUID());
			player->GetSession()->SendAreaTriggerMessage("重新登录以修改名字");
			player->GetSession()->SendAreaTriggerMessage("感谢使用赞助服务");
			player->CastSpell(player, 47292, true, NULL, NULL, player->GetGUID());
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), sWorld->getIntConfig(LOGIN_RENAME_JF), true);
		}
		else player->GetSession()->SendNotification("你没有购买权限，请赞助我们 ");
		player->CLOSE_GOSSIP_MENU();
		break;
	}
	player->PlayerTalkClass->SendCloseGossip();
	return true;

}
void ObjectMgr::xxCreatureTeleportFromMenuId(Player* player, uint32 MenuId)
{
	xxCreatureTeleMap::const_iterator ltr = _xxCreatureTeleMap.find(MenuId);
	if (ltr == _xxCreatureTeleMap.end())
		return;

	player->TeleportTo(ltr->second.tele_map, ltr->second.tele_x, ltr->second.tele_y, ltr->second.tele_z, 0);
}
void ObjectMgr::XxZz(Player * player, Creature *pcreature)
{
	std::stringstream ss("");
	player->PlayerTalkClass->ClearMenus();

	ss.str("");
	ss << "|cff008000本服务器赞助比例：|cFF0000FF（1:1）";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "|cffFF0000赞助方法：打开登录器输入6，回车即可";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "|cff008000点击领取赞助奖励|cFF0000FF";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1101, "", 0);



	player->PlayerTalkClass->SendCloseGossip();
	player->PlayerTalkClass->SendGossipMenu(907, pcreature->GetGUID());

}

void ObjectMgr::XxJl(Player * player, Creature *pcreature)
{
	std::stringstream ss("");
	player->PlayerTalkClass->ClearMenus();

	ss.str("");
	ss << "|cff008000为服务器宣传奖励：|cFF0000FF（50积分）";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "|cffFF0000宣传方法：给10个百人以上魔兽私服群宣传我们服务器，然后清晰截图发给群主换取奖励";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cffFF0000有任何疑问请在群里问询，或者密群主问询";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
	if (player->GetPlayerViplevel() > 0)
	{
		ss.str("");
		ss << "|cff008000您已经领取过宣传奖励啦，感谢您的支持|cFF0000FF";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	else
	{
		ss.str("");
		ss << "|cff008000点击领取宣传奖励|cFF0000FF";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1102, "", 0);
	}
	



	player->PlayerTalkClass->SendCloseGossip();
	player->PlayerTalkClass->SendGossipMenu(907, pcreature->GetGUID());

}

void ObjectMgr::SendAutoGiver(Player *player)
{
	uint32 vip = 0;
	uint32 honor = 0;
	uint32 a = 0;
	uint32 b = 0;
	uint32 c = 0;
	uint32 d = 0;
	uint32 e = 0;
	uint32 f = 0;
	// 发送默认泡点数据AUTOGIVERON
	if (sWorld->getBoolConfig(CONFIG_AUTOGIVERON))
	{
		if (sWorld->getIntConfig(CONFIG_AUTOGIVERJF) > 0)
		{
			vip = player->GetPlayerViplevel();
			//vip = player->GetJF() / sWorld->getIntConfig(CONFIG_AUTOGIVERJF);
			//honor = urand(sWorld->getIntConfig(CORE_AUTOGIVERHONOR_COUNT1), sWorld->getIntConfig(CORE_AUTOGIVERHONOR_COUNT2));
			if (sWorld->getBoolConfig(CONFIG_AUTOVIPON))
			{
				player->AddItem(sWorld->getIntConfig(CORE_AUTOGIVERITEM_ID), sWorld->getIntConfig(CORE_AUTOGIVERITEM_ID_COUNT) + vip);
				ChatHandler(player).PSendSysMessage(32021, GetItemNameLink(sWorld->getIntConfig(CORE_AUTOGIVERITEM_ID)), sWorld->getIntConfig(CORE_AUTOGIVERITEM_ID_COUNT), vip);
			}
			else
			{
				player->AddItem(sWorld->getIntConfig(CORE_AUTOGIVERITEM_ID), sWorld->getIntConfig(CORE_AUTOGIVERITEM_ID_COUNT));
				ChatHandler(player).PSendSysMessage(32021, GetItemNameLink(sWorld->getIntConfig(CORE_AUTOGIVERITEM_ID)), sWorld->getIntConfig(CORE_AUTOGIVERITEM_ID_COUNT));
			}

		}
		player->ModifyJF(1);
		if (player->m_zaixian < 30)
		{
			player->m_zaixian = player->m_zaixian + 1;
		}
		else
		{
			ChatHandler(player).PSendSysMessage("你当前剩余的泡点时间为%u分钟，具体信息请在泡点查询中查看",player->GetJF());
			player->m_zaixian = 0;
		}
		if (sWorld->getIntConfig(CORE_GOLD_ID) > 0)
		{
			player->ModifyMoney(sWorld->getIntConfig(CORE_GOLD_ID));
		}
			
		if (player->GetMapId() == 607)
		{
			if (player->GetHuoli() >= 18)
			{
				player->ModifyHuoli(-18);
			}

		}
		else
		{
			if (player->GetHuoli() < 180)
			{
				player->ModifyHuoli(1);
			}
			
		}

	}

	return;

}

std::string ObjectMgr::GetNameLink(Player* player)
{
	std::string name = player->GetName();
	std::string color;
	switch (player->getClass())
	{
	case CLASS_DEATH_KNIGHT:
		color = "|cffC41F3B";
		break;
	case CLASS_DRUID:
		color = "|cffFF7D0A";
		break;
	case CLASS_HUNTER:
		color = "|cffABD473";
		break;
	case CLASS_MAGE:
		color = "|cff69CCF0";
		break;
	case CLASS_PALADIN:
		color = "|cffF58CBA";
		break;
	case CLASS_PRIEST:
		color = "|cffFFFFFF";
		break;
	case CLASS_ROGUE:
		color = "|cffFFF569";
		break;
	case CLASS_SHAMAN:
		color = "|cff0070DE";
		break;
	case CLASS_WARLOCK:
		color = "|cff9482C9";
		break;
	case CLASS_WARRIOR:
		color = "|cffC79C6E";
		break;
	}
	return "|Hplayer:" + name + "|h|cffFFFFFF[" + color + name + "|cffFFFFFF]|h|r";
}

bool ObjectMgr::WorldSayCommand(Player *player, const char *args)
{
	if (!player->DoSpamCheck(args, 0))
		return false;
	if (!args)
		return false;


	//if (sObjectMgr->GetIntConfig(WORLDSAYON) == 0)
		//return false;

	//// 角色不存在
	if (!player || !player->IsInWorld())
		return false;

	char buff[2048];
	if (player->getLevel() >= 60)
	{

		if (player->GetTeam() == ALLIANCE)
		{
			sprintf(buff, "|CFFF0BCDC世界聊天|CFF153CFF[联盟]%s:|CFFF0BCDC%s|r",sObjectMgr->GetNameLink(player).c_str(), args);
		}
		else
		{
			sprintf(buff, "|CFFF0BCDC世界聊天|cffFF0000[部落]%s:|CFFF0BCDC%s|r", sObjectMgr->GetNameLink(player).c_str(), args);
		}
		sWorld->SendServerMessage(SERVER_MSG_STRING, buff, 0);

	}
	else
	{
		player->GetSession()->SendNotification("需要达到60级才可以使用世界聊天");
	}
	
	return true;
}

uint32 ObjectMgr::ShowItemSpawn(uint32 item)
{
	uint32 bitem = 0;
	uint32 aitem = item;
	for (xxItembMap::const_iterator itr = _xxItembMap.begin(); itr != _xxItembMap.end(); ++itr)
	{

		if (itr->second.ItembID >0)
		{
			if (aitem == itr->second.ItembID)
			{
				bitem = itr->second.ItembID;
				break;
			}

		}
		//printf("%u !\n", itr->second.guid);
	}

	return bitem;
}

bool ObjectMgr::CheckEnterBattleground(Player *player, uint32 Entry)
{

	xxBattleMap::const_iterator itr = _xxBattleMap.find(Entry);
	if (itr == _xxBattleMap.end())
	{
		ChatHandler(player).PSendSysMessage("|cffFF0000【战场】|cff0000FF该战场未开放!|r");
		return false;	// 找不到相关战场数据
	}
	bool a;
	if (sWorld->START_BONUS_BG_KAISHI_AS && sWorld->getBoolConfig(BG_AS_ON))
		a = true;
	else
		a = false;
	switch (Entry)
	{
	case 1:
		if (!sWorld->START_BONUS_BG_KAISHI_AS)
		{
			ChatHandler(player).PSendSysMessage("|cffFF0000【战场】|cff0000FF此战场尚未到达开放时间");
			return false;
		}
		break;
	case 2:
		//判断是否为许可时间
		if (!sWorld->START_BONUS_BG_KAISHI || a)
		{
			ChatHandler(player).PSendSysMessage("|cffFF0000【战场】|cff0000FF此战场尚未到达开放时间");
			return false;

		}
		break;
	case 3:
		if (!sWorld->START_BONUS_BG_KAISHI_ALX || a)
		{
			ChatHandler(player).PSendSysMessage("|cffFF0000【战场】|cff0000FF此战场尚未到达开放时间");
			return false;

		}
		break;
	case 7:
		if (!sWorld->START_BONUS_BG_KAISHI_FB || a)
		{
			ChatHandler(player).PSendSysMessage("|cffFF0000【战场】|cff0000FF此战场尚未到达开放时间");
			return false;

		}
		break;
	case 32:
		ChatHandler(player).PSendSysMessage("|cffFF0000【战场】|cff0000FF此战场尚未到达开放时间");
		return false;
	case 9:
		ChatHandler(player).PSendSysMessage("|cffFF0000【战场】|cff0000FF此战场尚未到达开放时间");
		return false;
	case 30:
		ChatHandler(player).PSendSysMessage("|cffFF0000【战场】|cff0000FF此战场尚未到达开放时间");
		return false;

	}
	if (itr->second.maxhealth > player->GetMaxHealth())
	{
		ChatHandler(player).PSendSysMessage("|cffFF0000【战场】|cff0000FF进入此战场需要:|cff00800010000|cff0000FF点血量!您的血量不足,无法进入!|r");
		return false;
	}
	return true;
}

void ObjectMgr::AddToBG(Player* player)
{
	WorldPacket Packet;
	Packet << uint64(0);
	Packet << uint32(2);
	Packet << uint32(2);
	Packet << uint8(0);
	player->GetSession()->HandleBattlemasterJoinOpcode(Packet);
	player->GetSession()->SendPacket(&Packet);

	return;
}

void ObjectMgr::AddToBG1(Player* player)
{
	WorldPacket Packet;
	Packet << uint64(0);
	Packet << uint32(3);
	Packet << uint32(3);
	Packet << uint8(0);
	player->GetSession()->HandleBattlemasterJoinOpcode(Packet);
	player->GetSession()->SendPacket(&Packet);

	return;
}

void ObjectMgr::AddToBG2(Player* player)
{
	WorldPacket Packet;
	Packet << uint64(0);
	Packet << uint32(7);
	Packet << uint32(7);
	Packet << uint8(0);
	player->GetSession()->HandleBattlemasterJoinOpcode(Packet);
	player->GetSession()->SendPacket(&Packet);
	return;
}

void ObjectMgr::AddToBG3(Player* player)
{
	WorldPacket Packet;
	Packet << uint64(0);
	Packet << uint32(1);
	Packet << uint32(1);
	Packet << uint8(0);
	player->GetSession()->HandleBattlemasterJoinOpcode(Packet);
	player->GetSession()->SendPacket(&Packet);

	return;
}

void ObjectMgr::AddToBG101(Player* player)
{
	if (player->GetTeamId() == TEAM_ALLIANCE)
		player->TeleportTo(571, 5104.750000f, 2300.949951f, 368.567993f, 0.0f);
	else
		player->TeleportTo(571, 5014.450195f, 3640.870117f, 361.390015f, 0.0f);
	return;
}

void ObjectMgr::AddToBG111(Player* player)
{
	if (player->GetTeamId() == TEAM_ALLIANCE)
		player->TeleportTo(1, -1760.1374512f, 2556.2568359f, 83.7752991f, 0.0f);
	else
		player->TeleportTo(1, -525.824707f, 2319.8735352f, 95.7050247f, 0.0f);
	return;
}

void ObjectMgr::AddToBG112(Player* player)
{
	if (player->GetTeamId() == TEAM_ALLIANCE)
		player->TeleportTo(0, -11128.3193359f, -2961.8234863f, 8.0483875f, 0.0f);
	else
		player->TeleportTo(0, -11598.28125f, -3115.6789551f, 6.2438402f, 0.0f);
	return;
}

void ObjectMgr::AddToBG113(Player* player)
{
	if (player->GetTeamId() == TEAM_ALLIANCE)
		player->TeleportTo(1, -7020.6552734f, -1277.0410156f, -268.2399292f, 0.0f);
	else
		player->TeleportTo(1, -7347.4838867f, -1490.8032227f, -258.3225708f, 0.0f);
	return;
}

void ObjectMgr::AddToBG114(Player* player)
{
	if (player->GetTeamId() == TEAM_ALLIANCE)
		player->TeleportTo(0, -1379.1430664f, -3445.6953125f, 52.6007843f, 0.0f);
	else
		player->TeleportTo(0, -1009.8833008f, -2583.1591797f, 62.1069031f, 0.0f);
	return;
}

void ObjectMgr::AddToBG115(Player* player)
{
	if (player->GetTeamId() == TEAM_ALLIANCE)
		player->TeleportTo(0, -14431.7099609f, 451.4545898f, 3.692426f, 0.0f);
	else
		player->TeleportTo(0, -14431.7099609f, 451.4545898f, 3.692426f, 0.0f);
	return;
}

void ObjectMgr::AddToBG116(Player* player)
{
	if (player->GetTeamId() == TEAM_ALLIANCE)
		player->TeleportTo(530, -1852.487793f, 5403.6245117f, -12.4276819f, 0.0f);
	else
		player->TeleportTo(530, -1852.487793f, 5403.6245117f, -12.4276819f, 0.0f);
	return;
}

void ObjectMgr::AddToBG117(Player* player)
{
	if (player->GetTeamId() == TEAM_ALLIANCE)
		player->TeleportTo(571, 5104.750000f, 2300.949951f, 368.567993f, 0.0f);
	else
		player->TeleportTo(571, 5014.450195f, 3640.870117f, 361.390015f, 0.0f);
	return;
}

void ObjectMgr::AddToBG118(Player* player)
{
	if (player->GetTeamId() == TEAM_ALLIANCE)
		player->TeleportTo(571, 5104.750000f, 2300.949951f, 368.567993f, 0.0f);
	else
		player->TeleportTo(571, 5014.450195f, 3640.870117f, 361.390015f, 0.0f);
	return;
}

void ObjectMgr::AddToBG120(Player* player)
{
	player->TeleportTo(0, -13230.353516f, 224.304016f, 35.506493f, 0.0f);
	return;
}

void ObjectMgr::AddToBG123(Player* player)
{
	player->TeleportTo(0, -11866.185547f, -3202.256592f, -22.349119f, 0.0f);
	return;
}

void ObjectMgr::AddToFuben(Player* player, uint32 sender, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;
	
	player->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, at->target_Orientation, TELE_TO_NOT_LEAVE_TRANSPORT);
	player->m_sender = sender;
	return;
}

void ObjectMgr::AddToFuben1(Player* player, uint32 sender, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	if (sender == 0)
	{
		ChatHandler(player).PSendSysMessage("官方难度关闭，请选择+1或者以上进入");
		return;
	}
	xxItemMap::const_iterator itr = _xxItemMap.find(sender);
	if (itr == _xxItemMap.end())
		return;
	if (player->GetYaoshitoc() < sender)
	{
		if (itr->second.ItemID > 0)
			player->DestroyItemCount(itr->second.ItemID, 1, true);
		if (player->GetYaoshitoc() < sender)
		    player->SetYaoshitoc(sender);
	}

	player->SetTocid(sender);
	player->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, at->target_Orientation, TELE_TO_NOT_LEAVE_TRANSPORT);
	return;
}

void ObjectMgr::AddToFuben2(Player* player, uint32 sender, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	if (sender == 0)
	{
		ChatHandler(player).PSendSysMessage("官方难度关闭，请选择+1或者以上进入");
		return;
	}
		
	xxItemiccMap::const_iterator itr = _xxItemiccMap.find(sender);
	if (itr == _xxItemiccMap.end())
		return;
	if (player->GetYaoshiicc() < sender)
	{
		if (itr->second.ItemID > 0)
			player->DestroyItemCount(itr->second.ItemID, 1, true);
		if (player->GetYaoshiicc() < sender)
		    player->SetYaoshiicc(sender);
	}
	

	player->SetIccid(sender);
	player->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, at->target_Orientation, TELE_TO_NOT_LEAVE_TRANSPORT);
	return;
}

void ObjectMgr::SendBoxText(Player* player, uint32 action)
{
	player->PlayerTalkClass->ClearMenus();
	player->m_action = action;
	std::stringstream ss("");

	switch (action)
	{

	case 1:
		if (!player->GetBattleground())
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|奥山开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n奥山战斗开始\n战场结束后无论胜负都会获得额外的奖励\n点击接受加入战场队列！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
		}
		break;
	case 2:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|战歌峡谷开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n战歌峡谷战斗开始\n战场结束后无论胜负都会获得额外的奖励\n点击接受加入战场队列！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
		}
		break;
	case 3:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|阿拉希开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n阿拉希战斗开始\n战场结束后无论胜负都会获得额外的奖励\n点击接受加入战场队列！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
		}
		break;
	case 7:
		if (!!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|风暴之眼开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n风暴之眼战斗开始\n战场结束后无论胜负都会获得额外的奖励\n点击接受加入战场队列！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
		}
		break;
	case 101:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|冬拥湖战斗开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n冬拥湖战斗开始\n点击接受可直接传送到冬拥湖！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
		}
		break;
	case 111:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n屠魔勇士活动开始\n点击接受可直接传送到屠魔勇士！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
			break;
		}
	case 112:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n夺宝奇兵活动开始\n点击接受可直接传送到夺宝奇兵！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
			break;
		}
	case 113:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n天草降临活动开始\n点击接受可直接传送到天草降临！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
			break;
		}
	case 114:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n黄金矿工活动开始\n点击接受可直接传送到黄金矿工！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
			break;
		}
	case 115:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n钓鱼大赛活动开始\n点击接受可直接传送到钓鱼大赛！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
			break;
		}
	case 116:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n生化危机活动开始\n点击接受可直接传送到生化危机！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
			break;
		}
	case 117:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n冬拥湖战斗开始\n点击接受可直接传送到冬拥湖！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
			break;
		}
	case 118:
		if (!player->GetBattleground() && !sWorld->START_BONUS_BG_KAISHI_AS)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n冬拥湖战斗开始2211\n点击接受可直接传送到冬拥湖！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
			break;
		}
	case 120:
			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n超级世界首领出现了\n点击接受可直接传送！", 0, false);
			player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
			break;
	case 123:
		player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n陨石矿坑活动开始了,符印碎片，积分，神器锻造石等你来拿\n点击接受可直接传送！", 0, false);
		player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
		break;
	case 124:
		player->ADD_GOSSIP_ITEM_EXTENDED(30, "|特色活动开始|r", 0, action, "|TInterface/FlavorImages/BloodElfLogo-small:64:64:0:-30|t\n \n \n \n \n \n追击小偷活动开始了，金币，积分等你来拿\n点击接受可直接传送！", 0, false);
		player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
		break;


	}
	return;
}

uint32 ObjectMgr::isBossCoreA(uint32 enry) const
{
	return isboss[enry];
}

void ObjectMgr::setisBossCoreA(uint32 enry)
{
	for (uint32 i = 0; i >= 204800; ++i)
		isboss[i] = enry;
}

void ObjectMgr::setisBossCoreB(uint32 index, uint32 enry)
{
	//for (uint32 i = 0; i >= 204800; ++i)
	isboss[index] = enry;
}


void ObjectMgr::czisBossCoreA(uint32 enry)
{
	isboss[enry] = 0;
}

uint32 ObjectMgr::GetAddPvpTalent(Player* player)
{
	xxPvpRankMap::const_iterator itr = m_xxPvpRankMap.find(player->GetPlayerPvprankLevel());
	if (itr == m_xxPvpRankMap.end())
		return 0;

	return itr->second.add_talent;
}

uint32 ObjectMgr::GetAddPvpShuxing(Player* player)
{
	xxPvpRankMap::const_iterator itr = m_xxPvpRankMap.find(player->GetPlayerPvprankLevel());
	if (itr == m_xxPvpRankMap.end())
		return 0;

	return itr->second.add_pvp;
}

uint32 ObjectMgr::GetPvpRankUINT32(uint32 level, uint8 index)
{
	if (index>30)
		return 0;

	xxPvpRankMap::const_iterator itr = m_xxPvpRankMap.find(level);
	if (itr == m_xxPvpRankMap.end())
		return uint32(-1);

	switch (index)
	{
	case 0:
		return itr->second.lmTitleId;
	case 1:
		return itr->second.blTitleId;
	case 2:
		return itr->second.lmreq_ItemId1;
	case 3:
		return itr->second.lmreq_ItemId2;
	case 4:
		return itr->second.lmreq_ItemCount1;
	case 5:
		return itr->second.lmreq_ItemCount2;
	case 12:
		return itr->second.blreq_ItemId1;
	case 13:
		return itr->second.blreq_ItemId2;
	case 14:
		return itr->second.blreq_ItemCount1;
	case 15:
		return itr->second.blreq_ItemCount2;
	case 21:
		return itr->second.lmrew_ItemId1;
	case 22:
		return itr->second.lmrew_ItemCount1;
	case 23:
		return itr->second.blrew_ItemId1;
	case 24:
		return itr->second.blrew_ItemCount1;

	}
	return 0;
}

void ObjectMgr::ShowPvpRankMenu(Player *player, Item *item)
{
	// 显示军衔菜单
	player->PlayerTalkClass->ClearMenus();
	uint32 nextlevel = player->GetPlayerPvprankLevel() + 1;
	xxPvpRankMap::const_iterator itr = m_xxPvpRankMap.find(nextlevel);

	if (itr == m_xxPvpRankMap.end())
	{
		std::stringstream ss("");
		ss << "|TInterface\\ICONS\\Achievement_PVP_A_15.blp:24|t|cff008000当前军衔等级:|cffFF0000" << player->GetPlayerPvprankLevel() << "|cff008000级";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, "|TInterface\\ICONS\\Ability_Mage_TormentOfTheWeak.blp:24|t|cff0000A0军衔等级升至最高级无法继续提升!|r", 0, 0, "", 0);
		player->PlayerTalkClass->SendGossipMenu(907, item->GetGUID());
		return;
	}


	uint32 lmItemId1 = itr->second.lmreq_ItemId1;
	uint32 lmItemId2 = itr->second.lmreq_ItemId2;
	uint32 lmItemCount1 = itr->second.lmreq_ItemCount1;
	uint32 lmItemCount2 = itr->second.lmreq_ItemCount2;
	uint32 blItemId1 = itr->second.blreq_ItemId1;
	uint32 blItemId2 = itr->second.blreq_ItemId2;
	uint32 blItemCount1 = itr->second.blreq_ItemCount1;
	uint32 blItemCount2 = itr->second.blreq_ItemCount2;
	uint32 lmtitleid = itr->second.lmTitleId;
	uint32 bltitleid = itr->second.blTitleId;
	uint32 add_talent = itr->second.add_talent;
	uint32 add_pvp = itr->second.add_pvp;

	std::stringstream ss("");
	ss << "|TInterface\\ICONS\\Achievement_PVP_A_15.blp:24|t|cff008000|cff008000当前军衔等级:|cffFF0000" << player->GetPlayerPvprankLevel() << "|cff008000级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, "|TInterface\\ICONS\\Achievement_PVP_G_06.blp:18|t|cff0000A0升级到下一级需要:|r", 0, 0, "", 0);
	if (player->GetTeamId() == TEAM_ALLIANCE)
	{
		if (lmItemId1>0 && lmItemCount1>0)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000物品1:[|cffFF0000" << GetItemNameLink(lmItemId1) << "|cff008000] x |cffFF0000" << lmItemCount1;
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
		}
		if (lmItemId2>0 && lmItemCount2>0)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000物品2:[|cffFF0000" << GetItemNameLink(lmItemId2) << "|cff008000] x |cffFF0000" << lmItemCount2;
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 0, 0, "", 0);
		}
	}
	else
	{
		if (blItemId1>0 && blItemCount1>0)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000物品1:[|cffFF0000" << GetItemNameLink(blItemId1) << "|cff008000] x |cffFF0000" << blItemCount1;
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
		}
		if (blItemId2>0 && blItemCount2>0)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000物品2:[|cffFF0000" << GetItemNameLink(blItemId2) << "|cff008000] x |cffFF0000" << blItemCount2;
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 0, 0, "", 0);
		}
	}

	ss.str("");
	ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000额外天赋点数变为:|cffFF0000[" << add_talent << "]";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(10, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000额外BUFF升级为:|cffFF0000[" << lmtitleid << "]级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);
	//ss.str("");
	//ss << "|TInterface\\ICONS\\ACHIEVEMENT_WIN_WINTERGRASP.blp:18|t|cff008000额外生命上限提升至:|cffFF0000[" << add_pvp << "]%";
	//->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 0, "", 0);


	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, "      |TInterface\\ICONS\\Ability_Mage_FieryPayback.blp:16|t|cff008000-->> 点击升级 <<--|TInterface\\ICONS\\Ability_Mage_FieryPayback.blp:16|t", 0, 1100 + 1, "", 0);
	player->PlayerTalkClass->SendGossipMenu(907, item->GetGUID());
}

void ObjectMgr::PvpRankLevelUP(Player *player, Item *item)
{
	uint32 nextlevel = player->GetPlayerPvprankLevel() + 1;
	uint32 lmItemId1 = GetPvpRankUINT32(nextlevel, 2);
	uint32 lmItemId2 = GetPvpRankUINT32(nextlevel, 3);
	uint32 lmItemCount1 = GetPvpRankUINT32(nextlevel, 4);
	uint32 lmItemCount2 = GetPvpRankUINT32(nextlevel, 5);
	uint32 blItemId1 = GetPvpRankUINT32(nextlevel, 12);
	uint32 blItemId2 = GetPvpRankUINT32(nextlevel, 13);
	uint32 blItemCount1 = GetPvpRankUINT32(nextlevel, 14);
	uint32 blItemCount2 = GetPvpRankUINT32(nextlevel, 15);
	uint32 lmrewItemId1 = GetPvpRankUINT32(nextlevel, 21);
	uint32 lmrewItemCount1 = GetPvpRankUINT32(nextlevel, 22);
	uint32 blrewItemId1 = GetPvpRankUINT32(nextlevel, 23);
	uint32 blrewItemCount1 = GetPvpRankUINT32(nextlevel, 24);
	bool allow = true;

	if (player->GetTeamId() == TEAM_ALLIANCE)
	{
		if (lmItemId1 > 0 && lmItemCount1 > 0)
			if (player->GetItemCount(lmItemId1, false) < lmItemCount1)
				allow = false;

		if (lmItemId2 > 0 && lmItemCount2 > 0)
			if (player->GetItemCount(lmItemId2, false) < lmItemCount2)
				allow = false;
	}
	else
	{
		if (blItemId1 > 0 && blItemCount1 > 0)
			if (player->GetItemCount(blItemId1, false) < blItemCount1)
				allow = false;

		if (blItemId2 > 0 && blItemCount2 > 0)
			if (player->GetItemCount(blItemId2, false) < blItemCount2)
				allow = false;
	}


	if (allow)
	{
		if (player->GetTeamId() == TEAM_ALLIANCE)
		{
			if (lmItemId1 > 0 && lmItemCount1 > 0)
				player->DestroyItemCount(lmItemId1, lmItemCount1, true);

			if (lmItemId2 > 0 && lmItemCount2 > 0)
				player->DestroyItemCount(lmItemId2, lmItemCount2, true);

			if (lmrewItemId1 > 0 && lmrewItemCount1 > 0)
				player->AddItem(lmrewItemId1, lmrewItemCount1);
		}
		else
		{
			if (blItemId1 > 0 && blItemCount1 > 0)
				player->DestroyItemCount(blItemId1, blItemCount1, true);

			if (blItemId2 > 0 && blItemCount2 > 0)
				player->DestroyItemCount(blItemId2, blItemCount2, true);

			if (blrewItemId1 > 0 && blrewItemCount1 > 0)
				player->AddItem(blrewItemId1, blrewItemCount1);
		}


		player->SetPlayerPvprankLevel(nextlevel);

		if (GetPvpRankUINT32(nextlevel, 0) > 0 || GetPvpRankUINT32(nextlevel, 1) > 0)
		{
			if (player->GetTeamId() == TEAM_ALLIANCE)
			{
				CharTitlesEntry const* titleEntry = sCharTitlesStore.LookupEntry(GetPvpRankUINT32(nextlevel, 0));
				if (titleEntry)
					player->SetTitle(titleEntry);
			}
			else
			{
				CharTitlesEntry const* titleEntry = sCharTitlesStore.LookupEntry(GetPvpRankUINT32(nextlevel, 1));
				if (titleEntry)
					player->SetTitle(titleEntry);
			}

		}
		player->LoginS();
		player->LoginSt();
		player->UpdateMaxHealth();
		player->InitTalentForLevel();
		ChatHandler(player).PSendSysMessage("PVP等级升级至：%u", player->GetPlayerPvprankLevel());
		ShowPvpRankMenu(player, item);
	}
	else{
		ChatHandler(player).PSendSysMessage("条件不足升级失败");
		ShowPvpRankMenu(player, item);
	}
}

void ObjectMgr::ShowBuffSpawn(Player* player)
{
	//player->RemoveAllAuras();
	for (xxItembuffMap::const_iterator itr = _xxItembuffMap.begin(); itr != _xxItembuffMap.end(); ++itr)
	{
		if (itr->second.buffID >0)
		{
			player->RemoveAurasDueToSpell(itr->second.buffID, player->GetGUID());
			//printf("%u !\n", itr->second.buffID);

		}
	}

}

uint32 ObjectMgr::GetPvpAura(Player* player)
{
	xxPvpRankMap::const_iterator itr = m_xxPvpRankMap.find(player->GetPlayerPvprankLevel());
	if (itr == m_xxPvpRankMap.end())
		return 0;

	if (player->GetTeamId() == TEAM_ALLIANCE)
		return itr->second.lmAura;
	else
		return itr->second.blAura;
}

uint32 ObjectMgr::GetRaid(Creature *pcreature, int8 sta)
{
	xxRaidMap::const_iterator itr = m_xxRaidMap.find(pcreature->GetCreatureTemplate()->lootid);
	if (itr == m_xxRaidMap.end())
		return 0;

	switch (sta)
	{

	case 1:
		return itr->second.lootid1;
	case 2:
		return itr->second.lootid2;
	case 3:
		return itr->second.lootid3;
	case 4:
		return itr->second.lootid4;
	case 5:
		return itr->second.lootid5;
	case 6:
		return itr->second.lootid6;
	case 7:
		return itr->second.lootid7;
	case 8:
		return itr->second.lootid8;
	case 9:
		return itr->second.lootid9;
	case 10:
		return itr->second.lootid10;
	}
	return 0;
}

uint32 ObjectMgr::GetSuoyao(uint32 sta, int8 a)
{
	xxSuoyaoMap::const_iterator itr = m_xxSuoyaoMap.find(sta);
	if (itr == m_xxSuoyaoMap.end())
		return 0;

	switch (a)
	{

	case 1:
		return itr->second.bossid;
	case 2:
		return itr->second.npcid;
	}
	return 0;
	
}

uint32 ObjectMgr::GetTongtian(uint32 sta)
{
	xxTongtianMap::const_iterator itr = m_xxTongtianMap.find(sta);
	if (itr == m_xxTongtianMap.end())
		return 0;


		return itr->second.bossid;

}



std::string ObjectMgr::GetRaidBuff(int8 sta)
{
	if (sWorld->getIntConfig(RAID_1) == 2)
	{
		switch (sta)
		{

		case 1:
			return "+1";
		case 2:
			return "+2";
		case 3:
			return "+3";
		case 4:
			return "+4";
		case 5:
			return "+5";
		case 6:
			return "+6";
		case 7:
			return "+7";
		case 8:
			return "+8";
		case 9:
			return "+9";
		case 10:
			return "+10";
		}
	}
	else
	{
		switch (sta)
		{

		case 1:
			return "★";
		case 2:
			return "★★";
		case 3:
			return "★★★";
		case 4:
			return "★★★★";
		case 5:
			return "★★★★★";
		}
	}
	
	return "官方";
}

void ObjectMgr::SendTocText(Player* player, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	player->PlayerTalkClass->ClearMenus();
	player->m_action = action;
	Group* group = player->GetGroup();
	if (group)
	{
		for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
		{
			Player* groupGuy = itr->GetSource();
			if (!groupGuy)
				continue;

			if (group->IsLeader(player->GetGUID()))
			{
				if (groupGuy->GetMapId() == at->target_mapId)
				{
					ChatHandler(player).PSendSysMessage("队伍中有成员在当前副本中，无法调整额外难度");
					player->PlayerTalkClass->ClearMenus();
					return;
				}
				else
				{
					std::stringstream ss("");
					ss << "|cff008000副本难度选择";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
					
					for (xxItemMap::const_iterator itr = _xxItemMap.begin(); itr != _xxItemMap.end(); ++itr)
					{
						if (player->GetItemCount(itr->second.ItemID, false) > 0 || player->GetYaoshitoc() >= itr->second.level)
						{
							ss.str("");
							ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000+" << itr->second.level;
							player->PlayerTalkClass->GetGossipMenu().AddMenuItem(itr->second.level + 1, 0, ss.str().c_str(), itr->second.level, action, "", 0);
							
						}
					}
					ss.str("");
					ss << "|TInterface/ICONS/Spell_Arcane_PortalThunderBluff.blp:25:25:-19:0|t|cffFF0000官方";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, action, "", 0);
				}
			}
			else
			{
				//AddToFuben(player, 0, action);
				ChatHandler(player).PSendSysMessage("额外难度模式只支持单人进入");
				player->PlayerTalkClass->ClearMenus();
				return;
			}

		}

	}
	else
	{
		std::stringstream ss("");
		ss << "|cff008000副本难度选择";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);

		for (xxItemMap::const_iterator itr = _xxItemMap.begin(); itr != _xxItemMap.end(); ++itr)
		{
			if (player->GetItemCount(itr->second.ItemID, false) > 0 || player->GetYaoshitoc() >= itr->second.level)
			{
				ss.str("");
				ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000+" << itr->second.level;
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(itr->second.level + 1, 0, ss.str().c_str(), itr->second.level, action, "", 0);

			}
		}
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalThunderBluff.blp:25:25:-19:0|t|cffFF0000官方";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, action, "", 0);
	}
	player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
	return;
}

void ObjectMgr::SendIccText(Player* player, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	player->PlayerTalkClass->ClearMenus();
	player->m_action = action;
	Group* group = player->GetGroup();
	if (group)
	{
		for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
		{
			Player* groupGuy = itr->GetSource();
			if (!groupGuy)
				continue;

			if (group->IsLeader(player->GetGUID()))
			{
				if (groupGuy->GetMapId() == at->target_mapId)
				{
					ChatHandler(player).PSendSysMessage("队伍中有成员在当前副本中，无法调整额外难度");
					player->PlayerTalkClass->ClearMenus();
					return;
				}
				else
				{
					std::stringstream ss("");
					ss << "|cff008000副本难度选择";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
					for (xxItemiccMap::const_iterator itr = _xxItemiccMap.begin(); itr != _xxItemiccMap.end(); ++itr)
					{
						if (player->GetItemCount(itr->second.ItemID, false) > 0 || player->GetYaoshiicc() >= itr->second.level)
						{
							ss.str("");
							ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000+" << itr->second.level;
							player->PlayerTalkClass->GetGossipMenu().AddMenuItem(itr->second.level + 1, 0, ss.str().c_str(), itr->second.level, action, "", 0);

						}
					}
					ss.str("");
					ss << "|TInterface/ICONS/Spell_Arcane_PortalThunderBluff.blp:25:25:-19:0|t|cffFF0000官方";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, action, "", 0);
				}
			}
			else
			{
				//AddToFuben(player, 0, action);
				ChatHandler(player).PSendSysMessage("额外难度模式只支持单人进入");
				player->PlayerTalkClass->ClearMenus();
				return;
			}

		}

	}
	else
	{
		std::stringstream ss("");
		ss << "|cff008000副本难度选择";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
		
		for (xxItemiccMap::const_iterator itr = _xxItemiccMap.begin(); itr != _xxItemiccMap.end(); ++itr)
		{
			if (player->GetItemCount(itr->second.ItemID, false) > 0 || player->GetYaoshiicc() >= itr->second.level)
			{
				ss.str("");
				ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000+" << itr->second.level;
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(itr->second.level + 1, 0, ss.str().c_str(), itr->second.level, action, "", 0);

			}
		}
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalThunderBluff.blp:25:25:-19:0|t|cffFF0000官方";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, action, "", 0);
	}
	player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
	return;
}

void ObjectMgr::SendFubenText(Player* player, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	player->PlayerTalkClass->ClearMenus();
	player->m_action = action;
	Group* group = player->GetGroup();
	if (group)
	{
		for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
		{
			Player* groupGuy = itr->GetSource();
			if (!groupGuy)
				continue;

			if (group->IsLeader(player->GetGUID()))
			{
				if (groupGuy->GetMapId() == at->target_mapId)
				{
					ChatHandler(player).PSendSysMessage("队伍中有成员在副本中，无法进行副本难度切换，需要所有人员退出副本由队长先进本切换难度");
					player->PlayerTalkClass->ClearMenus();
					return;
				}
				else
				{
					std::stringstream ss("");
					ss << "|cff008000副本难度选择";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
					ss.str("");
					ss << "|TInterface/ICONS/Spell_Arcane_PortalThunderBluff.blp:25:25:-19:0|t|cffFF0000官方";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, action, "", 0);
					ss.str("");
					ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000★";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 1, action, "", 0);
					ss.str("");
					ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000★★";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 2, action, "", 0);
					ss.str("");
					ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000★★★";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 3, action, "", 0);
					ss.str("");
					ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-18:0|t|cffFF0000★★★★";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 4, action, "", 0);
					ss.str("");
					ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-18:0|t|cffFF0000★★★★★";
					player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 5, action, "", 0);
				}
			}
			else
			{
				AddToFuben(player,0,action);
				ChatHandler(player).PSendSysMessage("只有队长才可以切换副本难度");
			}
			
		}
		
	}
	else
	{ 
		std::stringstream ss("");
		ss << "|cff008000副本难度选择";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalThunderBluff.blp:25:25:-19:0|t|cffFF0000官方";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, action, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000★";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 1, action, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000★★";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 2, action, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000★★★";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 3, action, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-18:0|t|cffFF0000★★★★";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 4, action, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-18:0|t|cffFF0000★★★★★";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 5, action, "", 0);
	}
		player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
	return;
}

void ObjectMgr::SendSuoyaoText(Player* player, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	player->PlayerTalkClass->ClearMenus();
	player->m_action = action;
	Group* group = player->GetGroup();
	if (group)
	{
				AddToFuben(player, 0, action);
				ChatHandler(player).PSendSysMessage("只有非组队情况下可激活日常副本");
	}
	else
	{
		std::stringstream ss("");
		ss << "|cff008000进入选择";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalThunderBluff.blp:25:25:-19:0|t|cffFF0000进入官方副本";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, action, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000挑战锁妖塔（日常）";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 1, action, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000挑战通天塔（日常）";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 2, action, "", 0);
		ss.str("");
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000挑战召唤塔（日常）";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 3, action, "", 0);
	}
	player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
	return;
}

uint32 ObjectMgr::IsSuoyaoEntry(uint32 entry, int8 a)
{
	xxSuoMap::const_iterator itr = m_xxSuoMap.find(entry);
	if (itr == m_xxSuoMap.end())
		return 0;
	switch (a)
	{

	case 1:
		return itr->second.minjf;
	case 2:
		return itr->second.maxjf;
	}
	return 0;
}

uint32 ObjectMgr::IsTongtianEntry(uint32 entry, int8 a)
{
	xxTongMap::const_iterator itr = m_xxTongMap.find(entry);
	if (itr == m_xxTongMap.end())
		return 0;
	switch (a)
	{

	case 1:
		return itr->second.minjf;
	case 2:
		return itr->second.maxjf;
	}
	return 0;
}

void ObjectMgr::GetKillCretureCredit(Player * player, Creature *creature)
{
	if (!creature || !player)
		return;

	//判断是否是当前挑战怪物

	if (IsSuoyaoEntry(creature->GetEntry(), 1) > 0 && IsSuoyaoEntry(creature->GetEntry(), 2) > 0)
	{
		player->ModifyTTjifen(urand(IsSuoyaoEntry(creature->GetEntry(), 1), IsSuoyaoEntry(creature->GetEntry(), 2)));
	}

	if (IsTongtianEntry(creature->GetEntry(), 1) > 0 && IsTongtianEntry(creature->GetEntry(), 2) > 0)
	{
		player->ModifyTTjifen2(urand(IsTongtianEntry(creature->GetEntry(), 1), IsTongtianEntry(creature->GetEntry(), 2)));
	}

	if (player->GetHuoli() >= 18)
	{
		if (IsHuoliEntry(creature->GetEntry(), 1) > 0 && IsHuoliEntry(creature->GetEntry(), 2) > 0 && IsHuoliEntry(creature->GetEntry(), 3) > 0)
		{
			player->AddItem(IsHuoliEntry(creature->GetEntry(), 1), urand(IsHuoliEntry(creature->GetEntry(), 2), IsHuoliEntry(creature->GetEntry(), 3)));
		}
		else if (IsHuoliEntry(creature->GetEntry(), 1) > 0 && IsHuoliEntry(creature->GetEntry(), 2) > 0)
		{
			player->AddItem(IsHuoliEntry(creature->GetEntry(), 1), IsHuoliEntry(creature->GetEntry(), 2));
		}

		if (IsHuoliEntry(creature->GetEntry(), 4) > 0 && IsHuoliEntry(creature->GetEntry(), 5) > 0)
		{
			player->ModifyMoney(urand(IsHuoliEntry(creature->GetEntry(), 4), IsHuoliEntry(creature->GetEntry(), 5)));
		}
		
	}
	else if (player->GetMapId() == 607)
	{
		ChatHandler(player).PSendSysMessage("你当前剩余活力值为%u点，无法再获得战利品", player->GetHuoli());
	}
	
}

uint32 ObjectMgr::IsHuoliEntry(uint32 entry, int8 a)
{
	xxHuoliMap::const_iterator itr = m_xxHuoliMap.find(entry);
	if (itr == m_xxHuoliMap.end())
		return 0;
	switch (a)
	{
	case 1:
		return itr->second.itemid;
	case 2:
		return itr->second.minitem;
	case 3:
		return itr->second.maxitem;
	case 4:
		return itr->second.minmoney;
	case 5:
		return itr->second.maxmoney;
	}
	return 0;
}

uint32 ObjectMgr::GetSkillAura(Player* player, uint32 skill)
{
	xxSkillMap::const_iterator itr = m_xxSkillMap.find(skill);

	if (itr == m_xxSkillMap.end())
		return 0;

	if (player->GetSkillValue(skill) > 0 && player->GetSkillValue(skill) < 50)
	{
		return 0;
	}
	else if (player->GetSkillValue(skill) > 49 && player->GetSkillValue(skill) < 100)
	{
		return itr->second.aura1;
	}
	else if (player->GetSkillValue(skill) > 99 && player->GetSkillValue(skill) < 150)
	{
		return itr->second.aura2;
	}
	else if (player->GetSkillValue(skill) > 149 && player->GetSkillValue(skill) < 200)
	{
		return itr->second.aura3;
	}
	else if (player->GetSkillValue(skill) > 199 && player->GetSkillValue(skill) < 250)
	{
		return itr->second.aura4;
	}
	else if (player->GetSkillValue(skill) > 249 && player->GetSkillValue(skill) < 300)
	{
		return itr->second.aura5;
	}
	else if (player->GetSkillValue(skill) > 299 && player->GetSkillValue(skill) < 350)
	{
		return itr->second.aura6;
	}
	else if (player->GetSkillValue(skill) > 349 && player->GetSkillValue(skill) < 400)
	{
		return itr->second.aura7;
	}
	else if (player->GetSkillValue(skill) > 399 && player->GetSkillValue(skill) < 450)
	{
		return itr->second.aura8;
	}
	else if (player->GetSkillValue(skill) > 449)
	{
		return itr->second.aura9;
	}
}

void ObjectMgr::ShowCjgradeMenu(Item *m_from, Item *target, Player *player)
{
	if (!m_from || !target || !player)
		return;

	player->PlayerTalkClass->ClearMenus();
	uint32 FromId = m_from->GetEntry(), TargetId = target->GetEntry();

	for (xxItemcjMap::const_iterator itr = _xxItemcjMap.begin(); itr != _xxItemcjMap.end(); ++itr)
	{
		if (itr->second.ItemID == TargetId && (itr->second.FromId == 0 || itr->second.FromId == FromId))
		{

			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|物品拆解|r", 1, 1000, "装备拆解\n你确定要那么做吗，如要继续请按确定", 0, false);

			player->PlayerTalkClass->SendGossipMenu(907, m_from->GetGUID());
			return;
		}
	}
}

void ObjectMgr::UpgradeThisItemcj(Item *target, Player *player, Item* m_from)
{
	if (!target || !m_from || !player)
		return;

	uint32 itemId = target->GetEntry();
	uint32 fromid = m_from->GetEntry();
	const std::string itemname = target->GetTemplate()->Name1;
	const std::string fromname = m_from->GetTemplate()->Name1;

	for (xxItemcjMap::const_iterator itr = _xxItemcjMap.begin(); itr != _xxItemcjMap.end(); ++itr)
	{
		if (fromid != itr->second.FromId && itr->second.FromId != 0)		// 不是使用这个强化宝石
			continue;

		if (itemId == itr->second.ItemID)
		{
			// 销毁原物品
			player->DestroyItemCount(target->GetEntry(), 1, true);
			if (itr->second.RewItem > 0 && itr->second.RewItemmin > 0)
			    player->AddItem(itr->second.RewItem, itr->second.RewItemmin);
			if (itr->second.RewItemmax > 0)
			{
				uint32 a = urand(0 , 100);
				if (a > 80)
				   player->AddItem(itr->second.RewItemmax, 1);
			}
			    
			return;
		}
	}
}

void ObjectMgr::ShowZhgradeMenu(Item *m_from, Item *target, Player *player)
{
	if (!m_from || !target || !player)
		return;

	player->PlayerTalkClass->ClearMenus();
	uint32 FromId = m_from->GetEntry(), TargetId = target->GetEntry();

	for (xxItemzhMap::const_iterator itr = _xxItemzhMap.begin(); itr != _xxItemzhMap.end(); ++itr)
	{
		if (itr->second.ItemID == TargetId && (itr->second.FromId == 0 || itr->second.FromId == FromId))
		{

			player->ADD_GOSSIP_ITEM_EXTENDED(30, "|！！！！|r", 1, 1000, "你确定要那么做吗，如要继续请按确定", itr->second.Jb * 10000, false);

			player->PlayerTalkClass->SendGossipMenu(907, m_from->GetGUID());
			return;
		}
	}
}

void ObjectMgr::UpgradeThisItemzh(Item *target, Player *player, Item* m_from)
{
	if (!target || !m_from || !player)
		return;

	uint32 itemId = target->GetEntry();
	uint32 fromid = m_from->GetEntry();
	const std::string itemname = target->GetTemplate()->Name1;
	const std::string fromname = m_from->GetTemplate()->Name1;

	for (xxItemzhMap::const_iterator itr = _xxItemzhMap.begin(); itr != _xxItemzhMap.end(); ++itr)
	{
		if (fromid != itr->second.FromId && itr->second.FromId != 0)		// 不是使用这个强化宝石
			continue;

		if (itemId == itr->second.ItemID)
		{
			// 销毁原物品
			if (player->HasEnoughMoney(itr->second.Jb * GOLD))
			{
				player->DestroyItemCount(target->GetEntry(), 1, true);
				player->DestroyItemCount(m_from->GetEntry(), 1, true);
				player->AddItem(itr->second.RewItem, itr->second.RewItemmin);
				if (itr->second.Jb > 0)
				    player->ModifyMoney(-int32(itr->second.Jb * GOLD), true);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("|CFFFF0000 您的金币不足%u枚, 不能进行此操作!", itr->second.Jb);
			}
			
			return;
		}
	}
}

void ObjectMgr::XxHui(Player * player, Item * pitem)
{
	std::stringstream ss("");
	player->PlayerTalkClass->ClearMenus();

	ss.str("");
	ss << "|cffFF0000你当前的|cFF0000FF会员等级:|cffFF0000" << player->GetPlayerViplevel();
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cffFF0000你当前拥有|cFF0000FF" << sObjectMgr->GetItemNameLink(sWorld->getIntConfig(CORE_JF_ID)) << ":|cffFF0000" << player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false);
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cffFF0000你当前拥有活力值:|cFF0000FF" << player->GetHuoli() << "/180|cffFF0000点";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cffFF0000你当前拥有|cFF0000FF泡点时间:|cffFF0000" << player->GetJF() << "|cffFF0000分钟";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);
	if (player->GetTTcishu() == 0)
	{
		ss.str("");
		ss << "|cFF0000FF你今日锁妖塔挑战状态:|cff008000尚未挑战";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	else
	{
		ss.str("");
		ss << "|cFF0000FF你今日锁妖塔挑战状态:|cffFF0000已经挑战";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (player->GetTT2cishu() == 0)
	{
		ss.str("");
		ss << "|cFF0000FF你今日通天塔挑战状态:|cff008000尚未挑战";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	else
	{
		ss.str("");
		ss << "|cFF0000FF你今日通天塔挑战状态:|cffFF0000已经挑战";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	ss.str("");
	ss << "|cFF0000FF你今日还可召唤海加尔山首领:" << 5 - player->GetTTzhaohuan1() << "|cffFF0000次";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cFF0000FF你今日还可召唤积雪平原首领:" << 3 - player->GetTTzhaohuan2() << "|cffFF0000次";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(7, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cffFF0000点击使用泡点时间|cFF0000FF兑换奖励";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(16, 0, ss.str().c_str(), 0, 1070 + 3, "", 0);
	//player->PlayerTalkClass->SendCloseGossip();
	player->PlayerTalkClass->SendGossipMenu(907, pitem->GetGUID());

}

uint32 ObjectMgr::GetRaidBox(uint32 loot, int8 sta)
{
	xxRaidBoxMap::const_iterator itr = m_xxRaidBoxMap.find(loot);
	if (itr == m_xxRaidBoxMap.end())
		return 0;

	switch (sta)
	{

	case 1:
		return itr->second.lootid1;
	case 2:
		return itr->second.lootid2;
	case 3:
		return itr->second.lootid3;
	case 4:
		return itr->second.lootid4;
	case 5:
		return itr->second.lootid5;
	case 6:
		return itr->second.lootid6;
	case 7:
		return itr->second.lootid7;
	case 8:
		return itr->second.lootid8;
	case 9:
		return itr->second.lootid9;
	case 10:
		return itr->second.lootid10;
	}
	return 0;
}

void ObjectMgr::ShowBossSpawn(Player* player, Creature *pcreature, int8 sta)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss;
	time_t curtime = time(NULL);
	for (xxnpcMap::const_iterator itr = _xxnpcMap.begin(); itr != _xxnpcMap.end(); ++itr)
	{
		int nexttime;
		if (itr->second.npcID > 0 && itr->second.id == sta)
		{
			ss.str("");
			nexttime = player->GetMap()->GetCreatureRespawnTime(itr->second.npcID) - curtime;
			nexttime = nexttime > 0 ? nexttime / 60 : 0;
			if (nexttime > 0)
				ss << GetCreatureTemplate(GetCreatureData(itr->second.npcID)->id)->Name << "--" << GetCreatureTemplate(GetCreatureData(itr->second.npcID)->id)->SubName << "---下次刷新时间为" << nexttime << "分钟后";
			else
				ss << GetCreatureTemplate(GetCreatureData(itr->second.npcID)->id)->Name << "--" << GetCreatureTemplate(GetCreatureData(itr->second.npcID)->id)->SubName << "|Cff00ff00已经刷新|r";



			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(itr->second.npcID, 0, ss.str().c_str(), 0, 0, "", 0);
		}
		//printf("%u !\n", itr->second.guid);
	}

	player->PlayerTalkClass->SendGossipMenu(60003, pcreature->GetGUID());
}

void ObjectMgr::ShowshijianMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	
	uint32 jf = 60;
	std::stringstream ss("");
	ss << "|cff008000泡点时间兑换奖励";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "你当前拥有泡点时间:|cffFF0000[" << player->GetJF() << "|cff008000]|cffFF0000分钟";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "|cff008000------------------------------------------";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
	
	//ss.str("");
	//ss << jf << "|cff008000分钟|cff004000兑换|cffFF00001个时间徽记";
	//player->PlayerTalkClass->GetGossipMenu().AddMenuItem(7, 0, ss.str().c_str(), 0, 1070 + 1, "", 0);
	ss.str("");
	ss << jf << "|cff008000分钟|cff004000兑换|cffFF0000600个积分";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(8, 0, ss.str().c_str(), 0, 1070 + 2, "", 0);
	ss.str("");
	ss << jf << "|cff008000分钟|cff004000兑换|cffFF0000600个金币";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(9, 0, ss.str().c_str(), 0, 1070 + 4, "", 0);
	//ss.str("");
	//ss << jf * 2 << "|cff008000分钟|cff004000兑换|cffFF00001个宝石箱";
	//player->PlayerTalkClass->GetGossipMenu().AddMenuItem(10, 0, ss.str().c_str(), 0, 1070 + 5, "", 0);
	
	player->PlayerTalkClass->SendGossipMenu(907, item->GetGUID());
}

void ObjectMgr::ShijianUP(Player *player, Item *item, int8 sta)
{
	uint32 jf = 60;
	switch (sta)
	{
	case 1:
		if (player->GetJF() >= jf)
		{
			player->ModifyJF(-int32(jf));
			//player->SaveJF();
			player->AddItem(18, 1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage("泡点时间不足");
		}
		break;
	case 2:
		if (player->GetJF() >= jf)
		{
			player->ModifyJF(-int32(jf));
			player->AddItem(sWorld->getIntConfig(CORE_JF_ID),600);
			//player->SaveJF();
		}
		else
		{
			ChatHandler(player).PSendSysMessage("泡点时间不足");
		}
		break;
	case 3:
		if (player->GetJF() >= jf)
		{
			player->ModifyJF(-int32(jf));
			player->ModifyMoney(600 * GOLD, true);
			//player->SaveJF();
		}
		else
		{
			ChatHandler(player).PSendSysMessage("泡点时间不足");
		}
		break;
	case 4:
		if (player->GetJF() >= (jf * 2))
		{
			player->ModifyJF(-int32(jf * 2));
			player->AddItem(14, 1);
			//player->SaveJF();
		}
		else
		{
			ChatHandler(player).PSendSysMessage("泡点时间不足");
		}
		break;

	}

}

void ObjectMgr::HuoliMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000你当前拥有活力值:[|cffFF0000" << player->GetHuoli() << "|cff008000]点";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cff008000点击进入活力地图";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1081, "", 0);

	player->PlayerTalkClass->SendGossipMenu(60005, item->GetGUID());
}

void ObjectMgr::WorldbossMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000点击前往挑战超级世界首领";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1083, "", 0);

	player->PlayerTalkClass->SendGossipMenu(60007, item->GetGUID());
}

void ObjectMgr::KlzMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000点击前往卡拉赞";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 1082, "", 0);

	player->PlayerTalkClass->SendGossipMenu(60006, item->GetGUID());
}

void ObjectMgr::FbysMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000点击前往风暴要塞";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 1085, "", 0);

	player->PlayerTalkClass->SendGossipMenu(60006, item->GetGUID());
}

void ObjectMgr::GleMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000点击前往格鲁尔巢穴";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 1089, "", 0);

	player->PlayerTalkClass->SendGossipMenu(60014, item->GetGUID());
}

void ObjectMgr::YskkMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000点击前往陨石矿坑";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 1091, "", 0);

	player->PlayerTalkClass->SendGossipMenu(60015, item->GetGUID());
}

void ObjectMgr::HjeMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000点击前往海加尔山-初级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 1084, "", 0);
	ss.str("");
	ss << "|cff008000点击前往海加尔山-高级";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1090, "", 0);
	player->PlayerTalkClass->SendGossipMenu(60010, item->GetGUID());
}

void ObjectMgr::JxpyMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000点击前往积雪平原";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 1086, "", 0);

	player->PlayerTalkClass->SendGossipMenu(60011, item->GetGUID());
}

void ObjectMgr::TocMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000点击前往十字军试炼";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 1087, "", 0);

	player->PlayerTalkClass->SendGossipMenu(60012, item->GetGUID());
}

void ObjectMgr::IccMenu(Player *player, Item *item)
{
	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");
	ss << "|cff008000点击前往冰冠堡垒";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 1088, "", 0);

	player->PlayerTalkClass->SendGossipMenu(60013, item->GetGUID());
}

void ObjectMgr::Huolichuansong(Player *player, Item *item)
{
	uint32 a = urand(1,5);
	switch (a)
	{
	case 1:
		player->TeleportTo(607, 1370.941895f, -316.822937f, 35.023113f, 0.0f);
		break;
	case 2:
		player->TeleportTo(607, 1353.891602f, 224.069412f, 35.215942f, 0.0f);
		break;
	case 3:
		player->TeleportTo(607, 1571.044312f, 88.399315f, 4.380305f, 0.0f);
		break;
	case 4:
		player->TeleportTo(607, 1566.034424f, -149.091125f, 5.710584f, 0.0f);
		break;
	case 5:
		player->TeleportTo(607, 835.919983f, -108.733231f, 111.584303f, 0.0f);
		break;

	}
	return;
}

void ObjectMgr::SendKlzText(Player* player, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	player->PlayerTalkClass->ClearMenus();
	player->m_action = action;

	
	std::stringstream ss("");
				

						if (player->GetItemCount(60036, false) > 0)
						{
								ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000点击进入卡拉赞";
								player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 1, action, "", 0);
								//ChatHandler(player).PSendSysMessage("暂未开放，敬请期待");
								//AddToFuben(player, 0, action);
						}
						else
						{
							ChatHandler(player).PSendSysMessage("缺少钥匙无法进入");
							//ChatHandler(player).PSendSysMessage("暂未开放，敬请期待");
							//AddToFuben(player, 0, action);
						}

	player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
	return;
}

void ObjectMgr::SendFbysText(Player* player, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	player->PlayerTalkClass->ClearMenus();
	player->m_action = action;


	std::stringstream ss("");


	if (player->GetItemCount(60036, false) > 0)
	{
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000点击进入风暴要塞";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 1, action, "", 0);
		//ChatHandler(player).PSendSysMessage("暂未开放，敬请期待");
		//AddToFuben(player, 0, action);
	}
	else
	{
		ChatHandler(player).PSendSysMessage("缺少钥匙无法进入");
		//ChatHandler(player).PSendSysMessage("暂未开放，敬请期待");
		//AddToFuben(player, 0, action);
	}

	player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
	return;
}

void ObjectMgr::SendGleText(Player* player, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	player->PlayerTalkClass->ClearMenus();
	player->m_action = action;


	std::stringstream ss("");


	if (player->GetItemCount(60069, false) > 0)
	{
		ss << "|TInterface/ICONS/Spell_Arcane_PortalTheramore.blp:25:25:-19:0|t|cffFF0000点击进入格鲁尔巢穴";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 1, action, "", 0);
		//ChatHandler(player).PSendSysMessage("暂未开放，敬请期待");
		//AddToFuben(player, 0, action);
	}
	else
	{
		ChatHandler(player).PSendSysMessage("缺少钥匙无法进入");
		//ChatHandler(player).PSendSysMessage("暂未开放，敬请期待");
		//AddToFuben(player, 0, action);
	}

	player->PlayerTalkClass->SendGossipMenu(907, player->GetGUID());
	return;
}



void ObjectMgr::AddToFuben3(Player* player, uint32 sender, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

		player->DestroyItemCount(60036, 1, true);

	player->SetKlzid(sender);
	player->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, at->target_Orientation, TELE_TO_NOT_LEAVE_TRANSPORT);
	return;
}

void ObjectMgr::AddToFuben4(Player* player, uint32 sender, uint32 action)
{
	AreaTrigger const* at = GetAreaTrigger(action);
	if (!at)
		return;

	player->DestroyItemCount(60069, 1, true);

	player->SetGleid(sender);
	player->TeleportTo(at->target_mapId, at->target_X, at->target_Y, at->target_Z, at->target_Orientation, TELE_TO_NOT_LEAVE_TRANSPORT);
	return;
}

void ObjectMgr::XxShangren(Player * player, Creature *pcreature)
{
	std::stringstream ss("");
	player->PlayerTalkClass->ClearMenus();

	uint32 vip = player->GetPlayerViplevel();
	uint32 shangxian = 10 + (vip * 3);

	ss.str("");
	ss << "|cff008000欢迎光临日常商城";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);

	if (player->GetSp1() == 0)
	{
		switch (player->GetShangpin1())
		{
		case 0:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 1:
			ss.str("");
			ss << "|cffFF0000300个积分购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 2:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 3:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 4:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 5:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 6:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 7:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 8:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 9:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 10:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 11:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 12:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 13:
			ss.str("");
			ss << "|cffFF0000300个积分购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 14:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 15:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 16:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 17:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 18:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 19:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 20:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 21:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 22:
			ss.str("");
			ss << "|cffFF0000500个日常徽章购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 23:
			ss.str("");
			ss << "|cffFF00001000个积分购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 24:
			ss.str("");
			ss << "|cffFF000010000个积分购买2000金币";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 25:
			ss.str("");
			ss << "|cffFF000015000个积分购买1个符印点数+1";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 26:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 27:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 28:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 29:
			ss.str("");
			ss << "|cffFF00002000个积分购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 30:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		case 31:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 1000, "", 0);
			break;
		}
	}
	else
	{
		ss.str("");
		ss << "|cffFF0000已售完";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (player->GetSp2() == 0)
	{
		switch (player->GetShangpin2())
		{
		case 0:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 1:
			ss.str("");
			ss << "|cffFF0000300个积分购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 2:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 3:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 4:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 5:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 6:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 7:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 8:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 9:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 10:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 11:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 12:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 13:
			ss.str("");
			ss << "|cffFF0000300个积分购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 14:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 15:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 16:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 17:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 18:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 19:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 20:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 21:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 22:
			ss.str("");
			ss << "|cffFF0000500个日常徽章购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 23:
			ss.str("");
			ss << "|cffFF00001000个积分购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 24:
			ss.str("");
			ss << "|cffFF000010000个积分购买2000金币";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 25:
			ss.str("");
			ss << "|cffFF000015000个积分购买1个符印点数+1";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 26:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 27:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 28:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 29:
			ss.str("");
			ss << "|cffFF00002000个积分购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 30:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		case 31:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 1001, "", 0);
			break;
		}
	}
	else
	{
		ss.str("");
		ss << "|cffFF0000已售完";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (player->GetSp3() == 0)
	{
		switch (player->GetShangpin3())
		{
		case 0:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 1:
			ss.str("");
			ss << "|cffFF0000300个积分购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 2:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 3:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 4:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 5:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 6:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 7:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 8:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 9:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 10:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 11:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 12:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 13:
			ss.str("");
			ss << "|cffFF0000300个积分购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 14:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 15:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 16:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 17:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 18:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 19:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 20:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 21:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 22:
			ss.str("");
			ss << "|cffFF0000500个日常徽章购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 23:
			ss.str("");
			ss << "|cffFF00001000个积分购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 24:
			ss.str("");
			ss << "|cffFF000010000个积分购买2000金币";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 25:
			ss.str("");
			ss << "|cffFF000015000个积分购买1个符印点数+1";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 26:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 27:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 28:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 29:
			ss.str("");
			ss << "|cffFF00002000个积分购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 30:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		case 31:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 1002, "", 0);
			break;
		}
	}
	else
	{
		ss.str("");
		ss << "|cffFF0000已售完";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (player->GetSp4() == 0)
	{
		switch (player->GetShangpin4())
		{
		case 0:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 1:
			ss.str("");
			ss << "|cffFF0000300个积分购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 2:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 3:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 4:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 5:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 6:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 7:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 8:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 9:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 10:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 11:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 12:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 13:
			ss.str("");
			ss << "|cffFF0000300个积分购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 14:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 15:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 16:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 17:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 18:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 19:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 20:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 21:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 22:
			ss.str("");
			ss << "|cffFF0000500个日常徽章购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 23:
			ss.str("");
			ss << "|cffFF00001000个积分购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 24:
			ss.str("");
			ss << "|cffFF000010000个积分购买2000金币";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 25:
			ss.str("");
			ss << "|cffFF000015000个积分购买1个符印点数+1";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 26:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 27:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 28:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 29:
			ss.str("");
			ss << "|cffFF00002000个积分购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 30:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		case 31:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 1003, "", 0);
			break;
		}
	}
	else
	{
		ss.str("");
		ss << "|cffFF0000已售完";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);
	}

	if (player->GetSp5() == 0)
	{
		switch (player->GetShangpin5())
		{
		case 0:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 1:
			ss.str("");
			ss << "|cffFF0000300个积分购买5个神技之魂";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 2:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 3:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技突破石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 4:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 5:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技觉醒石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 6:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 7:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个神技培养石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 8:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 9:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个羽翼之灵";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 10:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 11:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个背包兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 12:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 13:
			ss.str("");
			ss << "|cffFF0000300个积分购买1个海加尔山首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 14:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 15:
			ss.str("");
			ss << "|cffFF0000300个积分购买2个传说升级兑换卷";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 16:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 17:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个荣耀钻石";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 18:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 19:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个陨石碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 20:
			ss.str("");
			ss << "|cffFF0000150个日常徽章购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 21:
			ss.str("");
			ss << "|cffFF0000300个积分购买50个冰晶碎片";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 22:
			ss.str("");
			ss << "|cffFF0000500个日常徽章购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 23:
			ss.str("");
			ss << "|cffFF00001000个积分购买1个积雪平原首领召唤次数增加牌";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 24:
			ss.str("");
			ss << "|cffFF000010000个积分购买2000金币";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 25:
			ss.str("");
			ss << "|cffFF000015000个积分购买1个符印点数+1";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 26:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 27:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返格鲁尔";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 28:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 29:
			ss.str("");
			ss << "|cffFF00002000个积分购买3个传说升级凭证";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 30:
			ss.str("");
			ss << "|cffFF00001000个日常徽章购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		case 31:
			ss.str("");
			ss << "|cffFF00002000个积分购买1个重返风暴要塞";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 1004, "", 0);
			break;
		}
	}
	else
	{
		ss.str("");
		ss << "|cffFF0000已售完";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);
	}
	ss.str("");
	ss << "|cff008000------------------------------------------";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(9, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cff008000剩余免费刷新次数|cffFF0000" << player->GetShangrenshuaxin() << "/10";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(10, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cff008000剩余日常徽章和积分刷新次数|cffFF0000" << shangxian - player->Getsxshangxian() << "/" << shangxian;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "|cff008000------------------------------------------";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 0, "", 0);
	if (player->GetShangrenshuaxin() > 0)
	{
		ss.str("");
		ss << "|cffFF0000免费刷新出售的商品";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 1010, "", 0);
	}
	if (player->Getsxshangxian() < shangxian)
	{
		ss.str("");
		ss << "50个日常徽章刷新出售的商品";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(21, 0, ss.str().c_str(), 0, 1011, "", 0);

		ss.str("");
		ss << "|cffFF0000100个积分刷新出售的商品";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(22, 0, ss.str().c_str(), 0, 1012, "", 0);
	}



	player->PlayerTalkClass->SendCloseGossip();
	player->PlayerTalkClass->SendGossipMenu(60009, pcreature->GetGUID());

}

bool ObjectMgr::RunxxShangren(uint32 action, uint32 sender, Player *player, Creature *pcreature)
{
	if (player->IsInCombat())
	{
		player->PlayerTalkClass->ClearMenus();
		return false;
	}

	switch (action)
	{
	case 1000: // 显示指定菜单
		switch (player->GetShangpin1())
		{
		case 0:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 1:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 2:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 3:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 4:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 5:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 6:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 7:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 8:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 9:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 10:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 11:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 12:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 13:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 14:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 15:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 16:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 17:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 18:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 19:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 20:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 21:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 22:
			if (player->GetItemCount(6, false) >= 500)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(6, 500, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 23:
			if (player->GetItemCount(15, false) >= 1000)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(15, 1000, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 24:
			if (player->GetItemCount(15, false) >= 10000)
			{
				player->ModifyMoney(2000*10000);
				player->DestroyItemCount(15, 10000, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 25:
			if (player->GetItemCount(15, false) >= 15000)
			{
				player->AddItem(60011, 1);
				player->DestroyItemCount(15, 15000, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 26:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 27:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 28:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 29:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 30:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 31:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp1(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		}
		return true;
	case 1001://传送
		switch (player->GetShangpin2())
		{
		case 0:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 1:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 2:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 3:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 4:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 5:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 6:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 7:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 8:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 9:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 10:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 11:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 12:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 13:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 14:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 15:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 16:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 17:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 18:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 19:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 20:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 21:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 22:
			if (player->GetItemCount(6, false) >= 500)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(6, 500, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 23:
			if (player->GetItemCount(15, false) >= 1000)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(15, 1000, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 24:
			if (player->GetItemCount(15, false) >= 10000)
			{
				player->ModifyMoney(2000 * 10000);
				player->DestroyItemCount(15, 10000, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 25:
			if (player->GetItemCount(15, false) >= 15000)
			{
				player->AddItem(60011, 1);
				player->DestroyItemCount(15, 15000, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 26:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 27:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 28:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 29:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 30:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 31:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp2(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		}
		return true;
	case 1002://领取积分
		switch (player->GetShangpin3())
		{
		case 0:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 1:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 2:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 3:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 4:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 5:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 6:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 7:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 8:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 9:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 10:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 11:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 12:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 13:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 14:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 15:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 16:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 17:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 18:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 19:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 20:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 21:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 22:
			if (player->GetItemCount(6, false) >= 500)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(6, 500, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 23:
			if (player->GetItemCount(15, false) >= 1000)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(15, 1000, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 24:
			if (player->GetItemCount(15, false) >= 10000)
			{
				player->ModifyMoney(2000 * 10000);
				player->DestroyItemCount(15, 10000, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 25:
			if (player->GetItemCount(15, false) >= 15000)
			{
				player->AddItem(60011, 1);
				player->DestroyItemCount(15, 15000, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 26:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 27:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 28:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 29:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 30:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 31:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp3(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		}
		return true;
	case 1003://领取积分
		switch (player->GetShangpin4())
		{
		case 0:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 1:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 2:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 3:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 4:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 5:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 6:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 7:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 8:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 9:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 10:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 11:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 12:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 13:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 14:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 15:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 16:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 17:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 18:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 19:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 20:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 21:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 22:
			if (player->GetItemCount(6, false) >= 500)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(6, 500, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 23:
			if (player->GetItemCount(15, false) >= 1000)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(15, 1000, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 24:
			if (player->GetItemCount(15, false) >= 10000)
			{
				player->ModifyMoney(2000 * 10000);
				player->DestroyItemCount(15, 10000, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 25:
			if (player->GetItemCount(15, false) >= 15000)
			{
				player->AddItem(60011, 1);
				player->DestroyItemCount(15, 15000, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 26:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 27:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 28:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 29:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 30:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 31:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp4(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		}
		return true;
	case 1004:
		switch (player->GetShangpin5())
		{
		case 0:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 1:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60022, 5);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 2:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 3:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60023, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 4:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 5:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60024, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 6:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 7:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60025, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 8:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 9:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60005, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 10:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 11:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60001, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 12:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 13:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60006, 1);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 14:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 15:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(60034, 2);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 16:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 17:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(4, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 18:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 19:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(9, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 20:
			if (player->GetItemCount(6, false) >= 150)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(6, 150, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 21:
			if (player->GetItemCount(15, false) >= 300)
			{
				player->AddItem(10, 50);
				player->DestroyItemCount(15, 300, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 22:
			if (player->GetItemCount(6, false) >= 500)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(6, 500, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 23:
			if (player->GetItemCount(15, false) >= 1000)
			{
				player->AddItem(60007, 1);
				player->DestroyItemCount(15, 1000, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 24:
			if (player->GetItemCount(15, false) >= 10000)
			{
				player->ModifyMoney(2000 * 10000);
				player->DestroyItemCount(15, 10000, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 25:
			if (player->GetItemCount(15, false) >= 15000)
			{
				player->AddItem(60011, 1);
				player->DestroyItemCount(15, 15000, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 26:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 27:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60069, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 28:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 29:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60035, 3);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 30:
			if (player->GetItemCount(6, false) >= 1000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(6, 1000, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		case 31:
			if (player->GetItemCount(15, false) >= 2000)
			{
				player->AddItem(60036, 1);
				player->DestroyItemCount(15, 2000, true);
				player->SetSp5(1);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("不满足购买条件");
			}
			XxShangren(player, pcreature);
			return true;
		}
		return true;
	case 1010:
		player->SetShangpin1(urand(0, 31));
		player->SetShangpin2(urand(0, 31));
		player->SetShangpin3(urand(0, 31));
		player->SetShangpin4(urand(0, 31));
		player->SetShangpin5(urand(0, 31));
		player->SetSp1(0);
		player->SetSp2(0);
		player->SetSp3(0);
		player->SetSp4(0);
		player->SetSp5(0);
		player->ModifyShangrenshuaxin(-1);
		XxShangren(player, pcreature);
		return true;
	case 1011:
		if (player->GetItemCount(6, false) >= 50)
		{
			player->SetShangpin1(urand(0, 31));
			player->SetShangpin2(urand(0, 31));
			player->SetShangpin3(urand(0, 31));
			player->SetShangpin4(urand(0, 31));
			player->SetShangpin5(urand(0, 31));
			player->SetSp1(0);
			player->SetSp2(0);
			player->SetSp3(0);
			player->SetSp4(0);
			player->SetSp5(0);
			player->DestroyItemCount(6, 50, true);
			player->Modifysxshangxian(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage("不满足条件");
		}
		XxShangren(player, pcreature);
		return true;
	case 1012:
		if (player->GetItemCount(15, false) >= 100)
		{
			player->SetShangpin1(urand(0, 31));
			player->SetShangpin2(urand(0, 31));
			player->SetShangpin3(urand(0, 31));
			player->SetShangpin4(urand(0, 31));
			player->SetShangpin5(urand(0, 31));
			player->SetSp1(0);
			player->SetSp2(0);
			player->SetSp3(0);
			player->SetSp4(0);
			player->SetSp5(0);
			player->DestroyItemCount(15, 100, true);
			player->Modifysxshangxian(1);
		}
		else
		{
			ChatHandler(player).PSendSysMessage("不满足条件");
		}
		XxShangren(player, pcreature);
		return true;
	}
	player->PlayerTalkClass->SendCloseGossip();
	return true;

}

void ObjectMgr::ShowYuyiMenu(Player* player, Item* pitem)
{

	player->PlayerTalkClass->ClearMenus();
	bool a = true;
	bool c = true;
	std::stringstream ss("");
	xxyuyi::iterator itr = m_xxyuyimap.find(player->GetPlayerJfypoint(3) + 1);
	if (itr == m_xxyuyimap.end())
		return;
	//判断有点数 显示加点菜
	ss.str("");
	ss << "你当前突破次数|cff004000" << player->GetPlayerJfypoint(4) << "|r次";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "羽翼为你提高力量" << player->GetPlayerJfypoint(3) * 100 << "|r点|Cffff00ff↑|CFF00FF00" << (player->GetPlayerJfypoint(3) + 1) * 100;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);


	ss.str("");
	ss << "羽翼为你提高敏捷" << player->GetPlayerJfypoint(3) * 100 << "|r点|Cffff00ff↑|CFF00FF00" << (player->GetPlayerJfypoint(3) + 1) * 100;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "羽翼为你提高耐力" << player->GetPlayerJfypoint(3) * 100 << "|r点|Cffff00ff↑|CFF00FF00" << (player->GetPlayerJfypoint(3) + 1) * 100;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "羽翼为你提高智力" << player->GetPlayerJfypoint(3) * 100 << "|r点|Cffff00ff↑|CFF00FF00" << (player->GetPlayerJfypoint(3) + 1) * 100;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(5, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "羽翼为你提高精神" << player->GetPlayerJfypoint(3) * 100 << "|r点|Cffff00ff↑|CFF00FF00" << (player->GetPlayerJfypoint(3) + 1) * 100;
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(6, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "羽翼突破为你提高全属性" << player->GetPlayerJfypoint(4) << "|r%|Cffff00ff↑|CFF00FF00" << player->GetPlayerJfypoint(4) + 1 << "|r%";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(7, 0, ss.str().c_str(), 0, 0, "", 0);

	if (player->GetPlayerJfypoint(3) == itr->second.shangxian)
	{
		ss.str("");
		ss << "_____________________________";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);
		ss.str("");
		ss << "本次突破需要消耗：";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 0, "", 0);
		if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
		{
			if (player->GetItemCount(itr->second.reqitem1, false) >= itr->second.reqitemcount1)
				a = true;
			else
				a = false;

			ss.str("");
			ss << GetItemNameLink(itr->second.reqitem1) << "X" << itr->second.reqitemcount1;
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, ss.str().c_str(), 0, 0, "", 0);
		}
		if (itr->second.jb > 0)
		{
			if ((player->GetMoney() * 10000) >= itr->second.jb)
				c = true;
			else
				c = false;
			ss.str("");
			ss << "金币：" << "X" << itr->second.jb;
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(15, 0, ss.str().c_str(), 0, 0, "", 0);
		}
		if (a && c)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|cff004000点击进行进行突破";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 1001, 1001, "", 0);
		}
		else
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|cff004000所需物品不足，无法突破";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 0, "", 0);
		}
	}
	else
	{
		ss.str("");
		ss << "_____________________________";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);
		ss.str("");
		ss << "本次培养需要消耗：";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(12, 0, ss.str().c_str(), 0, 0, "", 0);
		if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
		{
			if (player->GetItemCount(itr->second.reqitem1, false) >= itr->second.reqitemcount1)
				a = true;
			else
				a = false;

			ss.str("");
			ss << GetItemNameLink(itr->second.reqitem1) << "X" << itr->second.reqitemcount1;
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(13, 0, ss.str().c_str(), 0, 0, "", 0);
		}
			if (itr->second.jb > 0)
			{
				if ((player->GetMoney() * 10000) >= itr->second.jb)
					c = true;
				else
					c = false;
				ss.str("");
				ss << "金币：" << "X" << itr->second.jb;
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(15, 0, ss.str().c_str(), 0, 0, "", 0);
			}
			if (a && c)
			{
				ss.str("");
				ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|CFF00FF00点击进行进行培养";
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 1000, 1000, "", 0);
			}
			else
			{
				ss.str("");
				ss << "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|cff004000所需物品不足，无法培养";
				player->PlayerTalkClass->GetGossipMenu().AddMenuItem(20, 0, ss.str().c_str(), 0, 0, "", 0);
			}

		}

		


	player->PlayerTalkClass->SendGossipMenu(907, pitem->GetGUID());
}

void ObjectMgr::Updateyuyi(Player* player, Item* pitem, uint32 uiAction)
{
	xxyuyi::iterator itr = m_xxyuyimap.find(player->GetPlayerJfypoint(3) + 1);
	if (itr == m_xxyuyimap.end())
		return;

	//获得剩余点数
	switch (uiAction)
	{
	case 1000: //升级攻击强度

		if (itr->second.jb > 0)
			player->ModifyMoney(-int32(itr->second.jb * 10000));
		if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
			player->DestroyItemCount(itr->second.reqitem1, itr->second.reqitemcount1, true);
		player->ModifyPlayerJfypoint(1, 3);
		ShowYuyiMenu(player, pitem);
		for (uint8 i = STAT_STRENGTH; i < MAX_STATS; ++i)
			player->UpdateStats(Stats(i));
		break;
	}
	return;
}

void ObjectMgr::Updateyuyi1(Player* player, Item* pitem, uint32 uiAction)
{
	xxyuyi::iterator itr = m_xxyuyimap.find(player->GetPlayerJfypoint(3) + 1);
	if (itr == m_xxyuyimap.end())
		return;

	//获得剩余点数
	switch (uiAction)
	{
	case 1001: //升级攻击强度

		if (itr->second.jb > 0)
			player->ModifyMoney(-int32(itr->second.jb * 10000));
		if (itr->second.reqitem1 > 0 && itr->second.reqitemcount1 > 0)
			player->DestroyItemCount(itr->second.reqitem1, itr->second.reqitemcount1, true);
		player->ModifyPlayerJfypoint(1, 3);
		player->ModifyPlayerJfypoint(1, 4);
		ShowYuyiMenu(player, pitem);
		for (uint8 i = STAT_STRENGTH; i < MAX_STATS; ++i)
			player->UpdateStats(Stats(i));
		break;
	}
	return;
}

uint32 ObjectMgr::ShowItemcjSpawn(uint32 item, int8 sta)
{
	xxcjjf::iterator itr = m_xxcjjfmap.find(item);
	if (itr == m_xxcjjfmap.end())
		return 0;

	switch (sta)
	{
	case 0:
		return itr->second.rewitem;
	case 1:
		return itr->second.rewitemcount;
	case 2:
		return itr->second.gonggao;
	}

	return 0;
}

void ObjectMgr::ShowCjMenu(Player* player, Creature *pcreature)
{

	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");

	ss.str("");
	ss << "你当前的抽奖积分为|cff004000" << player->Getcjjf();
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "一键兑换抽奖积分";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(22, 0, ss.str().c_str(), 0, 1000, "", 0);


	ss.str("");
	ss << "抽一次";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(32, 0, ss.str().c_str(), 1, 1001, "", 0);

	ss.str("");
	ss << "抽十次";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(33, 0, ss.str().c_str(), 10, 1001, "", 0);


	player->PlayerTalkClass->SendGossipMenu(60011, pcreature->GetGUID());
}

void ObjectMgr::Updatecjjf(Player* player, Creature *pcreature, uint32 sender, uint32 uiAction)
{
	uint32 zhongjiang;
	uint32 jf = sender * 100;
	//获得剩余点数
	switch (uiAction)
	{
	case 1000: //升级攻击强度

		/*if (player->GetItemCount(52185, false) > 0)//源质矿石
		{
			player->Modifycjjf(player->GetItemCount(52185, false) * 5);
			player->DestroyItemCount(52185, player->GetItemCount(52185, false), true);

		}
		if (player->GetItemCount(52186, false) > 0)//源质锭
		{
			player->Modifycjjf(player->GetItemCount(52186, false) * 5);
			player->DestroyItemCount(52186, player->GetItemCount(52186, false), true);

		}*/
		if (player->GetItemCount(36903, false) > 0)//蛇信草
		{
			player->Modifycjjf(player->GetItemCount(36903, false) * 5);
			player->DestroyItemCount(36903, player->GetItemCount(36903, false), true);

		}
		if (player->GetItemCount(36905, false) > 0)//巫妖花
		{
			player->Modifycjjf(player->GetItemCount(36905, false) * 5);
			player->DestroyItemCount(36905, player->GetItemCount(36905, false), true);
		}
		if (player->GetItemCount(36908, false) > 0)//雪莲花
		{
			player->Modifycjjf(player->GetItemCount(36908, false) * 10);
			player->DestroyItemCount(36908, player->GetItemCount(36908, false), true);

		}
		if (player->GetItemCount(36906, false) > 0)// 冰棘草
		{
			player->Modifycjjf(player->GetItemCount(36906, false) * 5);
			player->DestroyItemCount(36906, player->GetItemCount(36906, false), true);

		}
		if (player->GetItemCount(36910, false) > 0)//泰坦神铁矿石
		{
			player->Modifycjjf(player->GetItemCount(36910, false) * 10);
			player->DestroyItemCount(36910, player->GetItemCount(36910, false), true);

		}
		if (player->GetItemCount(36912, false) > 0)//萨隆邪铁矿石
		{
			player->Modifycjjf(player->GetItemCount(36912, false) * 5);
			player->DestroyItemCount(36912, player->GetItemCount(36912, false), true);

		}
		if (player->GetItemCount(33470, false) > 0)//霜纹布
		{
			player->Modifycjjf(player->GetItemCount(33470, false) * 2);
			player->DestroyItemCount(33470, player->GetItemCount(33470, false), true);

		}
		if (player->GetItemCount(38425, false) > 0)//厚北皮
		{
			player->Modifycjjf(player->GetItemCount(38425, false) * 6);
			player->DestroyItemCount(38425, player->GetItemCount(38425, false), true);

		}
		if (player->GetItemCount(44128, false) > 0)//极地毛皮
		{
			player->Modifycjjf(player->GetItemCount(44128, false) * 10);
			player->DestroyItemCount(44128, player->GetItemCount(44128, false), true);

		}
		break;
	case 1001:
		if (player->Getcjjf() >= jf)
		{
			player->Modifycjjf(-int32(jf));
			for (int i = 0; i < sender; ++i)
			{
				zhongjiang = urand(0, 9000);

				player->AddItem(ShowItemcjSpawn(zhongjiang, 0), ShowItemcjSpawn(zhongjiang, 1));
				if (ShowItemcjSpawn(zhongjiang, 2) > 0)
				{
					char buff[2048];
					sprintf(buff, "|CFF00FF00【大奖】:|r玩家|cffffffff|Hplayer:%s|h[%s]|h|r抽中了|cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]X%u|r运气真是太好了~|r", player->GetName(), player->GetName(), ShowItemcjSpawn(zhongjiang, 0), GetItemNameLink(ShowItemcjSpawn(zhongjiang, 0)), ShowItemcjSpawn(zhongjiang, 1));
					sWorld->SendServerMessage(SERVER_MSG_STRING, buff);

				}

			}
		}
		else
		{
			ChatHandler(player).PSendSysMessage("抱歉你的抽奖积分不足");
		}
		break;
	}
	ShowCjMenu(player, pcreature);
	return;
}

bool ObjectMgr::xxAHRewardGg(Player* player, uint64 owner, uint32 item, uint32 count, uint32 buyout)
{
	if (!player || !player->IsInWorld())
		return false;


	if (!sWorld->getBoolConfig(CONFIG_AHSL))
		return true;

	if (sWorld->getBoolConfig(CONFIG_AHSL))
	{
		//Player * own = GetPlayer(owner);
		if (buyout > 99)
		{
			//char s[2048] = { 0 };
			//strcpy_s(s, GetItemNameLink(item).c_str());
			//sWorld->SendWorldWideScreenText(70003, player->GetName(), item, s, count, buyout);
			char buff[2048];
			sprintf(buff, "|CFF00FF00【积分拍卖行】:|r玩家|cffffffff|Hplayer:%s|h[%s]|h|r在积分拍卖行中出售|cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]X%u售价%u积分|r需要的赶紧去抢购~|r", player->GetName(), player->GetName(), item, GetItemNameLink(item), count, buyout);
			sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
		}
	}
	//GetItemNameLink(item)
	return true;
}

bool ObjectMgr::xxAHRewardOwner(Player* pl, uint64 owner, int32 ejf)
{
	if (!pl || !pl->IsInWorld())
		return false;

	//if (ejf >1)
	//ejf= ejf < 10? (ejf - 1):(ejf - uint32(float(GetIntConfig(AHSL)) * 0.01 * (float)ejf));

	if (!sWorld->getBoolConfig(CONFIG_AHSL))
		return true;

	if (sWorld->getBoolConfig(CONFIG_AHSL))
	{
		if (pl->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) <  (uint32)ejf)
		{
			ChatHandler(pl).PSendSysMessage("您的积分不足支付此次交易，1铜=1积分");
			return false;
		}
		pl->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), ejf, true);
		if (ejf >1)
			ejf= ejf < 10? (ejf - 1):(ejf - uint32(float(10) * 0.01 * (float)ejf));
		//Player * own = GetPlayer(owner);
		//if (own && own->IsInWorld())
		//	own->AddItem(sWorld->getIntConfig(CORE_JF_ID), ejf);
		//else
			LoginDatabase.PExecute("insert into xx_ahitem_get (id,paytime,charge,geted) values (%u,now(),%u,0)", sObjectMgr->GetPlayerAccountIdByGUID(owner), ejf);
	}
	return true;
}

void ObjectMgr::ShowCjzMenu(Player* player, Creature *pcreature)
{

	player->PlayerTalkClass->ClearMenus();
	std::stringstream ss("");

	ss.str("");
	ss << "你当前的冰霜纹章数量为|cff004000" << player->GetItemCount(49426, false);
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(1, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "你当前的积分数量为|cff004000" << player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false);
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
	ss.str("");
	ss << "你当前已抽奖|cff004000" << player->Getzbcj() << "次";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "_____________________________";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(11, 0, ss.str().c_str(), 0, 0, "", 0);

	ss.str("");
	ss << "使用冰霜纹章抽奖";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(32, 0, ss.str().c_str(), 1, 1001, "", 0);

	ss.str("");
	ss << "使用积分抽奖";
	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(33, 0, ss.str().c_str(), 1, 1002, "", 0);


	player->PlayerTalkClass->SendGossipMenu(60012, pcreature->GetGUID());
}

void ObjectMgr::Updatecjzjf(Player* player, Creature *pcreature, uint32 sender, uint32 uiAction)
{
	uint32 zhongjiang;
	uint32 bswz = 100;
	uint32 jf = 1000;
	switch (uiAction)
	{
	case 1001: 
		if (player->GetItemCount(49426, false) >= bswz)
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), bswz, true);
			if (player->Getzbcj() < 4)
			{
				zhongjiang = urand(0, 17247);
				player->Modifyzbcj(1);
				player->AddItem(ShowItemcjzSpawn(zhongjiang, 0), 1);
				if (ShowItemcjzSpawn(zhongjiang, 1) > 0)
				{
					char buff[2048];
					sprintf(buff, "|CFF00FF00【大奖】:|r玩家|cffffffff|Hplayer:%s|h[%s]|h|r抽中了|cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]X%u|r运气真是太好了~|r", player->GetName(), player->GetName(), ShowItemcjzSpawn(zhongjiang, 0), GetItemNameLink(ShowItemcjzSpawn(zhongjiang, 0)), 1);
					sWorld->SendServerMessage(SERVER_MSG_STRING, buff);

				}
			}
			else
			{
				zhongjiang = urand(0, 5985);
				player->Setzbcj(0);
				player->AddItem(ShowItemcjzzSpawn(zhongjiang, 0), 1);
				if (ShowItemcjzzSpawn(zhongjiang, 1) > 0)
				{
					char buff[2048];
					sprintf(buff, "|CFF00FF00【大奖】:|r玩家|cffffffff|Hplayer:%s|h[%s]|h|r抽中了|cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]X%u|r运气真是太好了~|r", player->GetName(), player->GetName(), ShowItemcjzzSpawn(zhongjiang, 0), GetItemNameLink(ShowItemcjzzSpawn(zhongjiang, 0)), 1);
					sWorld->SendServerMessage(SERVER_MSG_STRING, buff);

				}
			}

		}
		else
		{
			ChatHandler(player).PSendSysMessage("抱歉你的冰霜纹章不足");
		}
		break;
	case 1002:
		if (player->GetItemCount(sWorld->getIntConfig(CORE_JF_ID), false) >= jf)
		{
			player->DestroyItemCount(sWorld->getIntConfig(CORE_JF_ID), jf, true);
			if (player->Getzbcj() < 4)
			{
				zhongjiang = urand(0, 17247);
				player->Modifyzbcj(1);
				player->AddItem(ShowItemcjzSpawn(zhongjiang, 0), 1);
				if (ShowItemcjzSpawn(zhongjiang, 1) > 0)
				{
					char buff[2048];
					sprintf(buff, "|CFF00FF00【大奖】:|r玩家|cffffffff|Hplayer:%s|h[%s]|h|r抽中了|cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]X%u|r运气真是太好了~|r", player->GetName(), player->GetName(), ShowItemcjzSpawn(zhongjiang, 0), GetItemNameLink(ShowItemcjzSpawn(zhongjiang, 0)), 1);
					sWorld->SendServerMessage(SERVER_MSG_STRING, buff);

				}
			}
			else
			{
				zhongjiang = urand(0, 5985);
				player->Setzbcj(0);
				player->AddItem(ShowItemcjzzSpawn(zhongjiang, 0), 1);
				if (ShowItemcjzzSpawn(zhongjiang, 1) > 0)
				{
					char buff[2048];
					sprintf(buff, "|CFF00FF00【大奖】:|r玩家|cffffffff|Hplayer:%s|h[%s]|h|r抽中了|cffffffff|Hitem:%d:0:0:0:0:0:0:0|h[%s]X%u|r运气真是太好了~|r", player->GetName(), player->GetName(), ShowItemcjzzSpawn(zhongjiang, 0), GetItemNameLink(ShowItemcjzzSpawn(zhongjiang, 0)), 1);
					sWorld->SendServerMessage(SERVER_MSG_STRING, buff);

				}
			}

		}
		else
		{
			ChatHandler(player).PSendSysMessage("抱歉你的积分不足");
		}
		break;
	}
	ShowCjzMenu(player, pcreature);
	return;
}

uint32 ObjectMgr::ShowItemcjzSpawn(uint32 item, int8 sta)
{
	xxcjzjf::iterator itr = m_xxcjzjfmap.find(item);
	if (itr == m_xxcjzjfmap.end())
		return 0;

	switch (sta)
	{
	case 0:
		return itr->second.rewitem;
	case 1:
		return itr->second.gonggao;
	}

	return 0;
}

uint32 ObjectMgr::ShowItemcjzzSpawn(uint32 item, int8 sta)
{
	xxcjzjf::iterator itr = m_xxcjzjfmap.find(item);
	if (itr == m_xxcjzjfmap.end())
		return 0;

	switch (sta)
	{
	case 0:
		return itr->second.rewitem;
	case 1:
		return itr->second.gonggao;
	}

	return 0;
}