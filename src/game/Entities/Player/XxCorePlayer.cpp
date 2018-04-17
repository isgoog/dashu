#include "Common.h"
#include "Object.h"
#include "Language.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "Opcodes.h"
#include "SpellMgr.h"
#include "World.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "UpdateMask.h"
#include "Player.h"
#include "Vehicle.h"
#include "SkillDiscovery.h"
#include "QuestDef.h"
#include "GossipDef.h"
#include "UpdateData.h"
#include "Channel.h"
#include "ChannelMgr.h"
#include "MapManager.h"
#include "MapInstanced.h"
#include "InstanceSaveMgr.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "ObjectMgr.h"
#include "GuildMgr.h"
#include "ObjectAccessor.h"
#include "CreatureAI.h"
#include "Formulas.h"
#include "Group.h"
#include "Guild.h"
#include "Pet.h"
#include "Util.h"
#include "Unit.h"
#include "Transport.h"
#include "Weather.h"
#include "Battleground.h"
#include "BattlegroundAV.h"
#include "BattlegroundMgr.h"
#include "OutdoorPvP.h"
#include "OutdoorPvPMgr.h"
#include "ArenaTeam.h"
#include "Chat.h"
#include "config.h"
#include "Spell.h"
#include "SocialMgr.h"
#include "GameEventMgr.h"
#include "AchievementMgr.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "ConditionMgr.h"
#include "DisableMgr.h"
#include "WeatherMgr.h"
#include "LFGMgr.h"
#include "CharacterDatabaseCleaner.h"
#include "InstanceScript.h"
#include <cmath>

#pragma execution_character_set("utf-8")

bool Player::DoSpamCheck(std::string message, uint32 a)
{
	//wqcore
	if ((time(NULL) - m_repeatTO) > 3)
	{
		MessageCache.clear();
		m_repeatIT = 0;
		m_repeatIT1 = 0;
	}
	transform(message.begin(), message.end(), message.begin(), toupper);

	if (a == m_repeatIT1) // Not found, add it
	{
		MessageCache.insert(MessageCache.end(), message);

		if (m_repeatTO == NULL)
			m_repeatTO = time(NULL);

		// Double check if we need to reset the time in case of a fast spammer who would be able to say something twice.
		if ((time(NULL) - m_repeatTO) > 3) // Reset the time
			m_repeatTO = time(NULL);
		m_repeatIT1 = 1;

	}
	else // We have found a double message
	{
		++m_repeatIT;
		if (m_repeatIT > 3)
		{
			time_t mutetime = time(NULL) + 5;
			GetSession()->m_muteTime = mutetime;
			ChatHandler(this).PSendSysMessage("Yor chat has been blocked for %u Seconds because you repeated youself for over %u times in a time of %u seconds.\n\n", 5, 5, 3);
			return false;
		}

		time_t TimeLeft = 3 - (time(NULL) - m_repeatTO);
		ChatHandler(this).PSendSysMessage("世界聊天每 %u 秒可以发送一次信息，还剩余 %u 秒可再次发送.\n\n", 3, TimeLeft);
		return false;
	}
	return true;
}

uint32 Player::GetPlayerViplevel()
{
	if (!Viplevel || Viplevel > 100)
		Viplevel = 0;
	return Viplevel;
}

void Player::AutoGive101()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 101);

	}
}

uint32 Player::GetFuyin()
{
	return Fuyin;
}

uint32 Player::GetHuoli()
{
	return huolizhi;
}
uint32 Player::GetShangrenshuaxin()
{
	return shangrenshuaxin;
}

uint32 Player::Getsxshangxian()
{
	return sxshangxian;
}

uint32 Player::GetShangpin1()
{
	return shangpin1;
}

uint32 Player::GetShangpin2()
{
	return shangpin2;
}

uint32 Player::GetShangpin3()
{
	return shangpin3;
}
uint32 Player::GetShangpin4()
{
	return shangpin4;
}
uint32 Player::GetShangpin5()
{
	return shangpin5;
}
uint32 Player::GetSp1()
{
	return sp1;
}
uint32 Player::GetSp2()
{
	return sp2;
}
uint32 Player::GetSp3()
{
	return sp3;
}
uint32 Player::GetSp4()
{
	return sp4;
}
uint32 Player::GetSp5()
{
	return sp5;
}

uint32 Player::GetTocid()
{
	return m_tocid;
}

uint32 Player::GetKlzid()
{
	return m_klzid;
}

uint32 Player::GetGleid()
{
	return m_gleid;
}

uint32 Player::GetYaoshitoc()
{
	return m_yaoshitoc;
}

uint32 Player::GetYaoshiicc()
{
	return m_yaoshiicc;
}

uint32 Player::GetIccid()
{
	return m_iccid;
}

void Player::ModifyJntp(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			jntupo = int32(jntupo) > -ttcs ? jntupo + ttcs : 0;
		}
		else
		{
			jntupo += ttcs;
		}
	}
}

void Player::ModifyHuoli(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			huolizhi = int32(huolizhi) > -ttcs ? huolizhi + ttcs : 0;
		}
		else
		{
			huolizhi += ttcs;
		}
	}
}

void Player::ModifyShangrenshuaxin(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			shangrenshuaxin = int32(shangrenshuaxin) > -ttcs ? shangrenshuaxin + ttcs : 0;
		}
		else
		{
			shangrenshuaxin += ttcs;
		}
	}
}

void Player::Modifysxshangxian(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			sxshangxian = int32(sxshangxian) > -ttcs ? sxshangxian + ttcs : 0;
		}
		else
		{
			sxshangxian += ttcs;
		}
	}
}

void Player::ModifyJnjx(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			jnjuexing = int32(jnjuexing) > -ttcs ? jnjuexing + ttcs : 0;
		}
		else
		{
			jnjuexing += ttcs;
		}
	}
}

void Player::ModifyJnpy(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			jnpeiyang = int32(jnpeiyang) > -ttcs ? jnpeiyang + ttcs : 0;
		}
		else
		{
			jnpeiyang += ttcs;
		}
	}
}

uint32 Player::GetTTcishu()
{
	return TTcishu;
}

uint32 Player::GetTTjifen()
{
	return TTjifen;
}

uint32 Player::GetTT2cishu()
{
	return TTcishu2;
}

uint32 Player::GetTTzhaohuan1()
{
	return TTzhaohuan1;
}

uint32 Player::GetTTzhaohuan2()
{
	return TTzhaohuan2;
}

uint32 Player::GetTT2jifen()
{
	return TTjifen2;
}

uint32 Player::GetTTboshu()
{
	return TTboshu;
}

uint32 Player::GetTTsaodang()
{
	return TTsaodang;
}

void Player::ModifyTTcishu(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			TTcishu = int32(TTcishu) > -ttcs ? TTcishu + ttcs : 0;
		}
		else
		{
			TTcishu += ttcs;
		}
	}
}

void Player::ModifyTTzhaohuan1(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			TTzhaohuan1 = int32(TTzhaohuan1) > -ttcs ? TTzhaohuan1 + ttcs : 0;
		}
		else
		{
			TTzhaohuan1 += ttcs;
		}
	}
}

void Player::ModifyTTzhaohuan2(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			TTzhaohuan2 = int32(TTzhaohuan2) > -ttcs ? TTzhaohuan2 + ttcs : 0;
		}
		else
		{
			TTzhaohuan2 += ttcs;
		}
	}
}

void Player::ModifyTTcishu2(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			TTcishu2 = int32(TTcishu2) > -ttcs ? TTcishu2 + ttcs : 0;
		}
		else
		{
			TTcishu2 += ttcs;
		}
	}
}

void Player::ModifyTTjifen(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			TTjifen = int32(TTjifen) > -ttcs ? TTjifen + ttcs : 0;
		}
		else
		{
			TTjifen += ttcs;
		}
	}
}

void Player::ModifyTTjifen2(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			TTjifen2 = int32(TTjifen2) > -ttcs ? TTjifen2 + ttcs : 0;
		}
		else
		{
			TTjifen2 += ttcs;
		}
	}
}

void Player::ModifyFuyin(int32 bw)
{
	if (this && this->IsInWorld())
	{
		if (bw < 0)
		{
			//ChatHandler(this).PSendSysMessage(50004, -bw);
			Fuyin = int32(Fuyin) > -bw ? Fuyin + bw : 0;
		}
		else
		{
			
			Fuyin += bw;
		}
	}
}

uint32 Player::GetPlayerSkillCount()
{
	//if (!SkillCount || SkillCount > 100)
	//SkillCount = 0;
	return SkillCount;
}

void Player::ModifySkillCount(int32 bw)
{
	if (this && this->IsInWorld())
	{
		if (bw < 0)
		{
			SkillCount = int32(SkillCount) > -bw ? SkillCount + bw : 0;
		}
		else
		{
			SkillCount += bw;
		}
	}
}

void Player::LoadxxPlayerInfo()
{
	bool isFirstLogin = false;
	QueryResult result = LoginDatabase.PQuery("Select  Viplevel, JF, ZZ, xuanchuan, xuanchuanyes, vipcreditget  FROM xx_account_extra WHERE id = %u", GetSession()->GetAccountId());
	if (!result)
	{
		//第一次登陆
		LoginDatabase.PExecute("insert into xx_account_extra (id,viplevel,jf,zz,xuanchuan,xuanchuanyes,vipcreditget) values (%u,0,0,0,0,0,0)", GetSession()->GetAccountId());
		isFirstLogin = true;
	}
	else
	{
		Field *fields = result->Fetch();
		Viplevel = fields[0].GetUInt32();
		JF = fields[1].GetInt32();
		ZZ = fields[2].GetInt32();
		xuanchuan = fields[3].GetInt32();
		xuanchuanyes = fields[4].GetInt32();
		if (fields[5].GetUInt32() >0)
			vipcreditget = true;

	}

	//获得角色真气经络和属性数据
	QueryResult result2 = CharacterDatabase.PQuery("Select  pvprank,fuyin,ttcishu,ttjifen,ttboshu,ttsaodang,ttcishu2,ttjifen2,skillcount,tocid,iccid,jntupo,jnjuexing,jnpeiyang,huolizhi,klzid,yaoshitoc,yaoshiicc,ttzhaohuan1,ttzhaohuan2,shangpin1,shangpin2,shangpin3,shangpin4,shangpin5,sp1,sp2,sp3,sp4,sp5,shangrenshuaxin,sxshangxian,gleid,cjjf,zbcj FROM xx_character_extra WHERE guid = %u", GetGUID());
	if (!result2)
	{
		//第一次登陆
		CharacterDatabase.PExecute("insert into xx_character_extra (guid,pvprank,fuyin,ttcishu,ttjifen,ttboshu,ttsaodang,ttcishu2,ttjifen2,skillcount,tocid,iccid,jntupo,jnjuexing,jnpeiyang,huolizhi,klzid,yaoshitoc,yaoshiicc,ttzhaohuan1,ttzhaohuan2,shangpin1,shangpin2,shangpin3,shangpin4,shangpin5,sp1,sp2,sp3,sp4,sp5,shangrenshuaxin,sxshangxian,gleid,cjjf,zbcj) values (%u,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)", GetGUID());
		isFirstLogin = true;
	}
	else
	{
		Field *fields2 = result2->Fetch();
		pvprank = fields2[0].GetUInt32();
		Fuyin = fields2[1].GetUInt32();
		TTcishu = fields2[2].GetUInt32();
		TTjifen = fields2[3].GetUInt32();
		TTboshu = fields2[4].GetUInt32();
		TTsaodang = fields2[5].GetUInt32();
		TTcishu2 = fields2[6].GetUInt32();
		TTjifen2 = fields2[7].GetUInt32();
		SkillCount = fields2[8].GetUInt32();
		m_tocid = fields2[9].GetUInt32();
		m_iccid = fields2[10].GetUInt32();
		jntupo = fields2[11].GetUInt32();
		jnjuexing = fields2[12].GetUInt32();
		jnpeiyang = fields2[13].GetUInt32();
		huolizhi = fields2[14].GetUInt32();
		m_klzid = fields2[15].GetUInt32();
		m_yaoshitoc = fields2[16].GetUInt32();
		m_yaoshiicc = fields2[17].GetUInt32();
		TTzhaohuan1 = fields2[18].GetUInt32();
		TTzhaohuan2 = fields2[19].GetUInt32();
		shangpin1 = fields2[20].GetUInt32();
		shangpin2 = fields2[21].GetUInt32();
		shangpin3 = fields2[22].GetUInt32();
		shangpin4 = fields2[23].GetUInt32();
		shangpin5 = fields2[24].GetUInt32();
		sp1 = fields2[25].GetUInt32();
		sp2 = fields2[26].GetUInt32();
		sp3 = fields2[27].GetUInt32();
		sp4 = fields2[28].GetUInt32();
		sp5 = fields2[29].GetUInt32();
		shangrenshuaxin = fields2[30].GetUInt32();
		sxshangxian = fields2[31].GetInt32();
		m_gleid = fields2[32].GetUInt32();
		cjjf = fields2[33].GetUInt32();
		zbcj = fields2[34].GetUInt32();
	}

	/*QueryResult result3 = CharacterDatabase.PQuery("Select  fuyin FROM xx_character_fuyinextra WHERE guid = %u", GetGUID());
	if (!result3)
	{
		//第一次登陆
		CharacterDatabase.PExecute("insert into xx_character_fuyinextra (guid,fuyin) values (%u,0)", GetGUID());
		isFirstLogin = true;
	}
	else
	{
		Field *fields3 = result3->Fetch();
		/*ModifymyfyStats(0, fields3[0].GetInt32());
		ModifymyfyStats(1, fields3[1].GetInt32());
		ModifymyfyStats(2, fields3[2].GetInt32());
		ModifymyfyStats(3, fields3[3].GetInt32());
		addgq = fields3[4].GetUInt32();
		addfq = fields3[5].GetUInt32();
		addjs = fields3[6].GetUInt32();
		addbj = fields3[7].GetUInt32();
		addrx = fields3[8].GetUInt32();
		Fuyin = fields3[0].GetUInt32();
	}*/

	QueryResult result4 = CharacterDatabase.PQuery("Select point,point1,point2,point3,point4,point5,point6,point7,point8,point9 FROM xx_character_fuyin WHERE guid = %u", GetGUID());
	if (!result4)
	{
		CharacterDatabase.PExecute("insert into xx_character_fuyin (guid,point,point1,point2,point3,point4,point5,point6,point7,point8,point9) values (%u,0,0,0,0,0,0,0,0,0,0)", GetGUID());
	}
	else
	{
		Field *fields4 = result4->Fetch();
		for (uint32 i = 0; i <= 9; i++)
		{
			fypoint[i] = fields4[i].GetUInt32();
		}
	}

	//RemoveAllAuras();
	
	//添加PVP BUFF
	//获取天赋
	m_AddTalent = sObjectMgr->GetAddPvpTalent(this);
	m_pvpadd = sObjectMgr->GetAddPvpShuxing(this);
	//LoginSt();
	LoginMSG(isFirstLogin);
	
}

bool Player::LoginSt()
{
	m_AddTalent = sObjectMgr->GetAddPvpTalent(this);
	m_pvpadd = sObjectMgr->GetAddPvpShuxing(this);
	return true;
}

bool Player::LoginS()
{
	sObjectMgr->ShowBuffSpawn(this);
	uint32 aura;
	aura = sObjectMgr->GetPvpAura(this);
	if (aura >0)
		AddAura(aura, this);

	if (sObjectMgr->GetVipAura(this) >0)
		AddAura(sObjectMgr->GetVipAura(this), this);

	if (HasSkill(186))//采矿
	{
		if (sObjectMgr->GetSkillAura(this, 186) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 186), this);
	}
	if (HasSkill(171))//炼金
	{
		if (sObjectMgr->GetSkillAura(this, 171) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 171), this);
	}
	if (HasSkill(164))//锻造
	{
		if (sObjectMgr->GetSkillAura(this, 164) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 164), this);
	}
	if (HasSkill(197))//裁缝
	{
		if (sObjectMgr->GetSkillAura(this, 197) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 197), this);
	}
	if (HasSkill(185))//烹饪
	{
		if (sObjectMgr->GetSkillAura(this, 185) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 185), this);
	}
	if (HasSkill(165))//制皮
	{
		if (sObjectMgr->GetSkillAura(this, 165) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 165), this);
	}
	if (HasSkill(356))//钓鱼
	{
		if (sObjectMgr->GetSkillAura(this, 356) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 356), this);
	}
	if (HasSkill(333))//附魔
	{
		if (sObjectMgr->GetSkillAura(this, 333) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 333), this);
	}
	if (HasSkill(755))//珠宝
	{
		if (sObjectMgr->GetSkillAura(this, 755) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 755), this);
	}
	if (HasSkill(202))//工程
	{
		if (sObjectMgr->GetSkillAura(this, 202) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 202), this);
	}
	if (HasSkill(129))//急救
	{
		if (sObjectMgr->GetSkillAura(this, 129) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 129), this);
	}
	if (HasSkill(182))//采药
	{
		if (sObjectMgr->GetSkillAura(this, 182) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 182), this);
	}
	if (HasSkill(393))//拨皮
	{
		if (sObjectMgr->GetSkillAura(this, 393) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 393), this);
	}
	if (HasSkill(773))//铭文
	{
		if (sObjectMgr->GetSkillAura(this, 773) > 0)
			AddAura(sObjectMgr->GetSkillAura(this, 773), this);
	}
	return true;
}
bool Player::LoginMSG(bool isFirstLogin)
{
	char buff[2048];
	if (isFirstLogin)
	{
		std::string wqRace, wqTeam, wqClass;
		switch (this->getRace())
		{
		case RACE_HUMAN:
			wqRace = "人类";
			break;
		case RACE_DWARF:
			wqRace = "矮人";
			break;
		case RACE_ORC:
			wqRace = "兽人";
			break;
		case RACE_NIGHTELF:
			wqRace = "暗夜";
			break;
		case RACE_UNDEAD_PLAYER:
			wqRace = "亡灵";
			break;
		case RACE_TAUREN:
			wqRace = "牛头人";
			break;
		case RACE_GNOME:
			wqRace = "侏儒";
			break;
		case RACE_TROLL:
			wqRace = "巨魔";
			break;
		case RACE_BLOODELF:
			wqRace = "血精灵";
			break;
		case RACE_DRAENEI:
			wqRace = "德莱尼";
			break;
		default:
			wqRace = "<UnKnow>";
		}
		switch (this->getClass())
		{
		case CLASS_WARRIOR:
			wqClass = "战士";
			break;
		case CLASS_PALADIN:
			wqClass = "骑士";
			break;
		case CLASS_HUNTER:
			wqClass = "猎人";
			break;
		case CLASS_ROGUE:
			wqClass = "盗贼";
			break;
		case CLASS_PRIEST:
			wqClass = "牧师";
			break;
		case CLASS_DEATH_KNIGHT:
			wqClass = "死骑";
			break;
		case CLASS_SHAMAN:
			wqClass = "萨满";
			break;
		case CLASS_MAGE:
			wqClass = "法师";
			break;
		case CLASS_WARLOCK:
			wqClass = "术士";
			break;
		case CLASS_DRUID:
			wqClass = "小德";
			break;
		default:
			wqClass = "<Unknow>";
		}

		if (GetTeamId() == TEAM_ALLIANCE)
			sprintf(buff, "|TInterface\\ICONS\\Achievement_PVP_A_A.blp:18|t|cff008000%s|cffFF8000%s|r的|cffffffff|Hplayer:%s|h[%s]|h|r第一次来到这个世界,请大家多多关照!", wqRace.c_str(), wqClass.c_str(), GetName(), GetName());
		else
			sprintf(buff, "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t|cff008000%s|cffFF8000%s|r的|cffffffff|Hplayer:%s|h[%s]|h|r第一次来到这个世界,请大家多多关照!", wqRace.c_str(), wqClass.c_str(), GetName(), GetName());
		sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
		return true;
	}
	if (GetTeamId() == TEAM_ALLIANCE)
		sprintf(buff, "|TInterface\\ICONS\\Achievement_PVP_A_A.blp:18|t欢迎|Hplayer:%s|h[%s]|h|r登陆魔兽世界!", GetName(), GetName());
	else
		sprintf(buff, "|TInterface\\ICONS\\Achievement_PVP_H_H.blp:18|t欢迎|Hplayer:%s|h[%s]|h|r登陆魔兽世界!", GetName(), GetName());
	sWorld->SendServerMessage(SERVER_MSG_STRING, buff);
	return true;
}

uint32 Player::GetJF()
{
	JF = (JF<0 || JF> 100000000) ? 0 : JF;
	return JF;
}

uint32 Player::GetXC()
{
	return xuanchuan;
}

uint32 Player::GetXCYES()
{
	return xuanchuanyes;
}

uint32 Player::GetZZ()
{
	return ZZ;
}

uint32 Player::ModifyJF(int32 Value)
{
	if (this && this->IsInWorld())
	{
		JF = Value < 0 && JF <= Value ? 0 : JF + Value;
	}
	return (uint32)JF;
}

uint32 Player::ModifyZZ(int32 Value)
{
	if (this && this->IsInWorld())
	{
		ZZ = Value < 0 && ZZ <= Value ? 0 : ZZ + Value;
	}
	return (uint32)ZZ;
}

void Player::SaveJF()
{
	uint32 isget;
	isget = vipcreditget ? 1 : 0;
	if (GetPlayerViplevel() > 0 || GetJF() > 0 || GetZZ() > 0 || isget > 0 || GetXC() > 0 || GetXCYES() >= 0)
	{
		LoginDatabase.PExecute("UPDATE xx_account_extra SET viplevel=%u,jf=%u,zz=%u,xuanchuan=%u,xuanchuanyes=%u,vipcreditget=%u WHERE id = %u", GetPlayerViplevel(), GetJF(), GetZZ(), GetXC(), GetXCYES(), isget, GetSession()->GetAccountId());
	
	}
}

void Player::SaveCharacter(SQLTransaction& trans)
{
	//保存积分
	SaveJF();
	trans->PAppend("update xx_character_extra set pvprank=%u,fuyin=%u,ttcishu=%u,ttjifen=%u,ttboshu=%u,ttsaodang=%u,ttcishu2=%u,ttjifen2=%u,skillcount=%u,tocid=%u,iccid=%u,jntupo=%u,jnjuexing=%u,jnpeiyang=%u,huolizhi=%u,klzid=%u,yaoshitoc=%u,yaoshiicc=%u,ttzhaohuan1=%u,ttzhaohuan2=%u,shangpin1=%u,shangpin2=%u,shangpin3=%u,shangpin4=%u,shangpin5=%u,sp1=%u,sp2=%u,sp3=%u,sp4=%u,sp5=%u,shangrenshuaxin=%u,sxshangxian=%u,gleid=%u,cjjf=%u,zbcj=%u where guid=%u", 
		pvprank, Fuyin, TTcishu, TTjifen, TTboshu, TTsaodang, TTcishu2, TTjifen2, SkillCount, m_tocid, m_iccid, jntupo, jnjuexing, jnpeiyang, huolizhi, m_klzid, m_yaoshitoc, m_yaoshiicc, TTzhaohuan1, TTzhaohuan2, 
		shangpin1, shangpin2, shangpin3, shangpin4, shangpin5, sp1, sp2, sp3, sp4, sp5, shangrenshuaxin, sxshangxian, m_gleid, cjjf, zbcj, GetGUID());
	trans->PAppend("update xx_character_fuyin set point=%u,point1=%u,point2=%u,point3=%u,point4=%u,point5=%u,point6=%u,point7=%u,point8=%u,point9=%u where guid=%u", fypoint[0], fypoint[1], fypoint[2], fypoint[3], fypoint[4], fypoint[5], fypoint[6], fypoint[7], fypoint[8], fypoint[9], GetGUID());
	return;
}

uint32 Player::GetPayJF()
{
	uint32 JF_NEW1;
	//领取充值积分
	QueryResult result1 = LoginDatabase.PQuery("Select sum(charge) FROM xx_jf_get WHERE id = %u and geted=0", GetSession()->GetAccountId());
	if (result1)
	{
		Field *fields1 = result1->Fetch();
		JF_NEW1 = fields1[0].GetInt32();
		LoginDatabase.PExecute("UPDATE xx_jf_get SET geted = 1 WHERE id = %u and geted=0", GetSession()->GetAccountId());
		if (JF_NEW1 > 0)
		{
			AddItem(sWorld->getIntConfig(CORE_JF_ID), JF_NEW1);
			ModifyMoney(JF_NEW1 * 1000);
			this->GetSession()->SendNotification("恭喜你赞助奖励领取成功，感谢您的慷慨");
		}
		else
			this->GetSession()->SendNotification("您还没赞助我们哟");
			
	}
	//SaveJF();
	return JF_NEW1;
}

uint32 Player::GetPayXC()
{
	uint32 JF_NEW1;
	//领取充值积分
	QueryResult result1 = LoginDatabase.PQuery("Select sum(charge) FROM xx_xc_get WHERE id = %u and geted = 0", GetSession()->GetAccountId());
	if (result1)
	{
		if (GetXCYES() == 0)
		{
			Field *fields1 = result1->Fetch();
			JF_NEW1 = fields1[0].GetInt32();
			LoginDatabase.PExecute("UPDATE xx_xc_get SET geted = 1 WHERE id = %u and geted=0", GetSession()->GetAccountId());
			if (JF_NEW1 > GetXC())
			{
				SetXC(JF_NEW1);
				SetXCYES(1);
				if (JF_NEW1 == 1)
				{
					AddItem(60070 ,3);
					AddItem(60072, 1000);
				}
				else
				{
					AddItem(60070, 1);
					AddItem(60072, 500);
				}
				
				this->GetSession()->SendNotification("恭喜你宣传奖励领取成功，感谢您的支持");
			}
			else
				this->GetSession()->SendNotification("您今日还没有帮我们宣传哟");
		}
		else
			this->GetSession()->SendNotification("您今日已经领取过宣传奖励了哟");

	}
	//SaveJF();
	return JF_NEW1;
}

uint32 Player::GetJlJF()
{
	uint32 JF_NEW1;
	//领取奖励行积分
	QueryResult result1 = LoginDatabase.PQuery("Select sum(charge) FROM xx_ahitem_get WHERE id = %u and geted=0", GetSession()->GetAccountId());
	if (result1)
	{
		Field *fields1 = result1->Fetch();
		JF_NEW1 = fields1[0].GetInt32();
		LoginDatabase.PExecute("UPDATE xx_ahitem_get SET geted = 1 WHERE id = %u and geted=0", GetSession()->GetAccountId());
		if (JF_NEW1 > 0)
		{
				AddItem(sWorld->getIntConfig(CORE_JF_ID), JF_NEW1);
				this->GetSession()->SendNotification("恭喜领取积分拍卖行售卖所得的积分");
			
		}
		else
			this->GetSession()->SendNotification("您在积分拍卖行没有售卖掉的东西哟");

	}
	//SaveJF();
	return JF_NEW1;
}

void Player::AutoGive()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendAutoGiver(this);

	}
}

void Player::AutoGive1()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 2);

	}
}

void Player::AutoGive2()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 3);

	}
}

void Player::AutoGive3()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 7);

	}
}

void Player::AutoGive4()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 1);

	}
}

void Player::AutoGiveHd1()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 111);

	}
}

void Player::AutoGiveHd2()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 112);

	}
}

void Player::AutoGiveHd3()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 113);

	}
}

void Player::AutoGiveHd4()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 114);

	}
}

void Player::AutoGiveHd5()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 115);

	}
}

void Player::AutoGiveHd6()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 116);

	}
}

void Player::AutoGiveHd7()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 117);

	}
}

void Player::AutoGiveHd8()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 118);

	}
}

void Player::AutoGiveHd120()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 120);

	}
}

void Player::AutoGiveHd123()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 123);

	}
}

void Player::AutoGiveHd124()
{
	if (this->IsInWorld() && this->IsAlive())
	{
		sObjectMgr->SendBoxText(this, 124);

	}
}

void Player::RewardBattleCredit(uint32 bttype, bool iswiner)
{
	if (!this->IsInWorld())
		return;
	uint32 item, count, item1, count1, item2, count2, item3, count3;

	if (iswiner)
	{
		item = sObjectMgr->GetBattlegroundValue(bttype, 1);
		count = sObjectMgr->GetBattlegroundValue(bttype, 5);
		item1 = sObjectMgr->GetBattlegroundValue(bttype, 2);
		count1 = sObjectMgr->GetBattlegroundValue(bttype, 6);
		item2 = sObjectMgr->GetBattlegroundValue(bttype, 3);
		count2 = sObjectMgr->GetBattlegroundValue(bttype, 7);
		item3 = sObjectMgr->GetBattlegroundValue(bttype, 4);
		count3 = sObjectMgr->GetBattlegroundValue(bttype, 8);


		if (item> 0 && count> 0)
			AddItem(item, count);
		if (item1> 0 && count1> 0)
			AddItem(item1, count1);
		if (item2> 0 && count2> 0)
			AddItem(item2, count2);
		if (item3> 0 && count3> 0)
			AddItem(item3, count3);



	}
	else
	{
		item = sObjectMgr->GetBattlegroundValue(bttype, 11);
		count = sObjectMgr->GetBattlegroundValue(bttype, 15);
		item1 = sObjectMgr->GetBattlegroundValue(bttype, 12);
		count1 = sObjectMgr->GetBattlegroundValue(bttype, 16);
		item2 = sObjectMgr->GetBattlegroundValue(bttype, 13);
		count2 = sObjectMgr->GetBattlegroundValue(bttype, 17);
		item3 = sObjectMgr->GetBattlegroundValue(bttype, 14);
		count3 = sObjectMgr->GetBattlegroundValue(bttype, 18);


		if (item> 0 && count> 0)
			AddItem(item, count);
		if (item1> 0 && count1> 0)
			AddItem(item1, count1);
		if (item2> 0 && count2> 0)
			AddItem(item2, count2);
		if (item3> 0 && count3> 0)
			AddItem(item3, count3);




	}

}

void Player::Modifycjjf(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			cjjf = int32(cjjf) > -ttcs ? cjjf + ttcs : 0;
		}
		else
		{
			cjjf += ttcs;
		}
	}
}

void Player::Modifyzbcj(int32 ttcs)
{
	if (this && this->IsInWorld())
	{
		if (ttcs < 0)
		{
			zbcj = int32(zbcj) > -ttcs ? zbcj + ttcs : 0;
		}
		else
		{
			zbcj += ttcs;
		}
	}
}

void Player::CantAuctionBuy()
{
	ChatHandler(this).PSendSysMessage("【失败提示】:当前服务器开启积分拍卖行,不允许使用竞标!");
}
