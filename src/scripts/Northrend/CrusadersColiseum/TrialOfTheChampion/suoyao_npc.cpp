#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "trial_of_the_champion.h"
#include "Player.h"
#include "ScriptedEscortAI.h"
#include "SpellScript.h"
#pragma execution_character_set("utf-8")

enum SuoyaoEvents
{
	EVENT_SPELL_1 = 1,
	EVENT_SPELL_2,
	EVENT_SPELL_3,
};

class xx_suoyaota : public CreatureScript
{
public:
	xx_suoyaota() : CreatureScript("xx_suoyaota") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{

		if (!player || !player->IsInWorld())
			return false;

		player->PlayerTalkClass->ClearMenus();
		

		std::stringstream ss;

		if (player->GetTTjifen() > 0 && !player->IsInCombat())
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --领取锁妖塔奖励--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(21, 0, ss.str().c_str(), 1001, 1001, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60001, creature->GetGUID());
			return true;
		}

		if (player->GetTTcishu() > 0)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --抱歉您今日已经挑战过锁妖塔--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60001, creature->GetGUID());
			return true;
		}

		if (player->IsInCombat())
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --请脱离战斗后再和我对话--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60001, creature->GetGUID());
			return true;
		}

		if (player->GetOriginalGroup())
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --组队状态不能挑战锁妖塔--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60001, creature->GetGUID());
			return true;
		}


		if (player->GetTTboshu() > 0 && player->GetTTsaodang() == 0)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    您上次挑战至" << player->GetTTboshu() << "波";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(27, 0, ss.str().c_str(), 0, 0, "", 0);
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    扫荡至上次波数需要花费" << player->GetTTboshu() * 2<< "金币";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(28, 0, ss.str().c_str(), 0, 0, "", 0);
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    |CFF00CCFF点击扫荡至上次波数";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(29, 0, ss.str().c_str(), 1002, 1002, "", 0);
		}

		ss.str("");
		ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:24|t |CFF00CCFF我已经了解了,开始我的挑战";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(30, 0, ss.str().c_str(), 1000, 1000, "", 0);

		player->PlayerTalkClass->SendGossipMenu(60001, creature->GetGUID());

		return true;
	}
	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		InstanceScript* pInstance = creature->GetInstanceScript();
		if (!pInstance)
			return true;

		if (uiSender == 1002)
		{
			if (player->GetTTboshu() > 0)
			{
				player->ModifyMoney(-int32(player->GetTTboshu()*20000));
				pInstance->SetData(DATA_BOSHU_ENTRY, player->GetTTboshu());
				pInstance->SetData(DATA_PLAYER_BOSHU, player->GetTTboshu());
				for (uint32 i = 0; i < player->GetTTboshu(); i++)
				{
					player->ModifyTTjifen(urand(sObjectMgr->IsSuoyaoEntry(99101 + i, 1), sObjectMgr->IsSuoyaoEntry(99101 + i, 2)));
					player->ModifyTTjifen(urand(sObjectMgr->IsSuoyaoEntry(99001 + i, 1), sObjectMgr->IsSuoyaoEntry(99001 + i, 2)));
					player->ModifyTTjifen(urand(sObjectMgr->IsSuoyaoEntry(99101 + i, 1), sObjectMgr->IsSuoyaoEntry(99101 + i, 2)));
					player->ModifyTTjifen(urand(sObjectMgr->IsSuoyaoEntry(99101 + i, 1), sObjectMgr->IsSuoyaoEntry(99101 + i, 2)));
				}
				player->SendUpdateWorldState(UPDATE_STATE_UI_BOSHU_COUNT, pInstance->GetData(DATA_BOSHU_ENTRY));
				player->SendUpdateWorldState(UPDATE_STATE_UI_JIFEN_COUNT, player->GetTTjifen());
				if (player->GetTTboshu() == 100)
				{
					player->ModifyTTcishu(1);
					player->SetTTsaodang(player->GetTTboshu());
				}
				else
				{
					player->SetTTsaodang(player->GetTTboshu());
				}
				
			}
		}
		if (uiSender == 1000)
		{
			if (pInstance->GetData(DATA_BOSHU_ENTRY) < 100)
			{
				pInstance->SetData(DATA_SUOYAO_STAT, 0);
				player->ModifyTTcishu(1);
			}
			
		}
		if (uiSender == 1001)
		{
			uint32 jf = player->GetTTjifen();
			if (jf > 0)
			{ 
				player->ModifyMoney(jf);
				player->AddItem(sWorld->getIntConfig(CORE_SUOYAOITEM_ID), jf/10000);
				player->AddItem(sWorld->getIntConfig(CORE_JF_ID), jf/40000);
				player->ModifyTTjifen(-int32(jf));
				player->SendUpdateWorldState(UPDATE_STATE_UI_JIFEN_COUNT, player->GetTTjifen());
				
			}
			
			
		}

		return true;
	}

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new xx_suoyaotaAI(pCreature);
	}

	struct xx_suoyaotaAI : public CreatureAI
	{
		xx_suoyaotaAI(Creature *pCreature) : CreatureAI(pCreature) { pInstance = me->GetInstanceScript(); }

		InstanceScript* pInstance;

		void Reset()
		{
			if (!pInstance)
				return;
			
		}

		void EnterCombat(Unit* who)
		{

		}
		void JustDied(Unit* Killer)
		{
			pInstance->SetData(DATA_SUOYAO_END, 0);
		}

		void UpdateAI(uint32 diff) 
		{
			/*events.Update(diff);
			switch (events.GetEvent())
			{
			case EVENT_SUMMON_NPC:
			{
				if (pInstance->GetData(DATA_SHIJIAN_ENTRY) == 0)
				{
					events.ScheduleEvent(EVENT_KAIMEN, 6000);
					pInstance->SetData(DATA_BOSHU_ENTRY, pInstance->GetData(DATA_BOSHU_ENTRY) + 1);
				}
				if (pInstance->GetData(DATA_SHIJIAN_ENTRY) >= 60)
				{
					pInstance->SetData(DATA_SHIJIAN_ENTRY, 0);
				}
				pInstance->SetData(DATA_SHIJIAN_ENTRY, pInstance->GetData(DATA_SHIJIAN_ENTRY) + 1);
				events.ScheduleEvent(EVENT_SUMMON_NPC, 1000);
			}
			break;
			case EVENT_KAIMEN:
			{
				
				pInstance->HandleGameObject(150077, true);
				events.ScheduleEvent(EVENT_GUANMEN, 6000);
				events.PopEvent();
			}
			break;
			case EVENT_GUANMEN:
			{
				pInstance->HandleGameObject(150077, false);
				events.PopEvent();
			}
			break;
			}*/
		}
	};
};

class boss_suoyao : public CreatureScript
{
public:
	boss_suoyao() : CreatureScript("boss_suoyao") { }

	struct boss_suoyaoAI : public ScriptedAI
	{
		boss_suoyaoAI(Creature* pCreature) : ScriptedAI(pCreature)
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
			events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
			events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
			events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			if (pInstance->GetData(DATA_BOSHU_ENTRY) > 0)
			{
				me->CastSpell(me, sWorld->getIntConfig(SUOYAO_BUFF) + pInstance->GetData(DATA_BOSHU_ENTRY), true);
			}
			else
			{
				me->CastSpell(me, sWorld->getIntConfig(SUOYAO_BUFF), true);
			}

		}

		void JustDied(Unit* /*killer*/)
		{
			
			pInstance->SetData(DATA_PLAYER_BOSHU, 0);
		}

		void EnterEvadeMode()
		{
			me->CastSpell(me, 7, false);
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
				me->CastSpell(me->GetVictim(), 24573, false);
				events.RepeatEvent(urand(10000, 12000));
				break;
			case EVENT_SPELL_2:
				me->CastSpell(me->GetVictim(), 75418, false);
				events.RepeatEvent(urand(14000, 16000));
				break;
			case EVENT_SPELL_3:
				me->CastSpell(me->GetVictim(), 60899, false);
				events.RepeatEvent(urand(18000, 22000));
				break;
			}

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new boss_suoyaoAI(pCreature);
	}
};

class npc_suoyao : public CreatureScript
{
public:
	npc_suoyao() : CreatureScript("npc_suoyao") { }

	struct npc_suoyaoAI : public ScriptedAI
	{
		npc_suoyaoAI(Creature* pCreature) : ScriptedAI(pCreature)
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
			if (pInstance->GetData(DATA_BOSHU_ENTRY) > 0)
			{
				me->CastSpell(me, sWorld->getIntConfig(SUOYAO_BUFF) + pInstance->GetData(DATA_BOSHU_ENTRY), true);
			}
			else
			{
				me->CastSpell(me, sWorld->getIntConfig(SUOYAO_BUFF), true);
			}

		}

		void EnterEvadeMode()
		{
			me->CastSpell(me, 7, false);
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
		return new npc_suoyaoAI(pCreature);
	}
};

class xx_tongtianta : public CreatureScript
{
public:
	xx_tongtianta() : CreatureScript("xx_tongtianta") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{

		if (!player || !player->IsInWorld())
			return false;

		player->PlayerTalkClass->ClearMenus();


		std::stringstream ss;

		if (player->GetTT2jifen() > 0 && !player->IsInCombat())
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --领取通天塔奖励--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(21, 0, ss.str().c_str(), 1001, 1001, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60004, creature->GetGUID());
			return true;
		}

		if (player->GetTT2cishu() > 0)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --抱歉您今日已经挑战过通天塔--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60004, creature->GetGUID());
			return true;
		}

		if (player->IsInCombat())
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --请脱离战斗后再和我对话--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60004, creature->GetGUID());
			return true;
		}

		if (player->GetOriginalGroup())
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --组队状态不能挑战通天塔--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(4, 0, ss.str().c_str(), 0, 0, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60004, creature->GetGUID());
			return true;
		}

		ss.str("");
		ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:24|t |CFF00CCFF我已经了解了,开始我的挑战";
		player->PlayerTalkClass->GetGossipMenu().AddMenuItem(30, 0, ss.str().c_str(), 1000, 1000, "", 0);

		player->PlayerTalkClass->SendGossipMenu(60004, creature->GetGUID());

		return true;
	}
	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		InstanceScript* pInstance = creature->GetInstanceScript();
		if (!pInstance)
			return true;

		if (uiSender == 1000)
		{
			if (pInstance->GetData(DATA_CENGSHU_ENTRY) < 100)
			{
				pInstance->SetData(DATA_TONGTIAN_STAT, 0);
				player->ModifyTTcishu2(1);
			}

		}
		if (uiSender == 1001)
		{
			uint32 jf = player->GetTT2jifen();
			if (jf > 0)
			{
				player->ModifyMoney(jf);
				player->AddItem(sWorld->getIntConfig(CORE_SUOYAOITEM_ID), jf / 10000);
				player->AddItem(sWorld->getIntConfig(CORE_JF_ID), jf / 40000);
				player->ModifyTTjifen2(-int32(jf));
				player->SendUpdateWorldState(6011, player->GetTT2jifen());

			}


		}

		return true;
	}

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new xx_tongtiantaAI(pCreature);
	}

	struct xx_tongtiantaAI : public CreatureAI
	{
		xx_tongtiantaAI(Creature *pCreature) : CreatureAI(pCreature) { pInstance = me->GetInstanceScript(); }

		InstanceScript* pInstance;

		void Reset()
		{
			if (!pInstance)
				return;

		}

		void EnterCombat(Unit* who)
		{

		}
		void JustDied(Unit* Killer)
		{
			pInstance->SetData(DATA_TONGTIAN_END, 0);
		}

		void UpdateAI(uint32 diff)
		{
			/*events.Update(diff);
			switch (events.GetEvent())
			{
			case EVENT_SUMMON_NPC:
			{
			if (pInstance->GetData(DATA_SHIJIAN_ENTRY) == 0)
			{
			events.ScheduleEvent(EVENT_KAIMEN, 6000);
			pInstance->SetData(DATA_BOSHU_ENTRY, pInstance->GetData(DATA_BOSHU_ENTRY) + 1);
			}
			if (pInstance->GetData(DATA_SHIJIAN_ENTRY) >= 60)
			{
			pInstance->SetData(DATA_SHIJIAN_ENTRY, 0);
			}
			pInstance->SetData(DATA_SHIJIAN_ENTRY, pInstance->GetData(DATA_SHIJIAN_ENTRY) + 1);
			events.ScheduleEvent(EVENT_SUMMON_NPC, 1000);
			}
			break;
			case EVENT_KAIMEN:
			{

			pInstance->HandleGameObject(150077, true);
			events.ScheduleEvent(EVENT_GUANMEN, 6000);
			events.PopEvent();
			}
			break;
			case EVENT_GUANMEN:
			{
			pInstance->HandleGameObject(150077, false);
			events.PopEvent();
			}
			break;
			}*/
		}
	};
};

class boss_tongtian : public CreatureScript
{
public:
	boss_tongtian() : CreatureScript("boss_tongtian") { }

	struct boss_tongtianAI : public ScriptedAI
	{
		boss_tongtianAI(Creature* pCreature) : ScriptedAI(pCreature)
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
			events.ScheduleEvent(EVENT_SPELL_1, urand(10000, 12000));
			events.ScheduleEvent(EVENT_SPELL_2, urand(14000, 16000));
			events.ScheduleEvent(EVENT_SPELL_3, urand(18000, 22000));
			if (pInstance->GetData(DATA_CENGSHU_ENTRY) > 0)
			{
				me->CastSpell(me, sWorld->getIntConfig(SUOYAO_BUFF) + pInstance->GetData(DATA_CENGSHU_ENTRY), true);
			}
			else
			{
				me->CastSpell(me, sWorld->getIntConfig(SUOYAO_BUFF), true);
			}

		}

		void JustDied(Unit* killer)
		{

			if (killer == me)
				return;

			if (pInstance->GetData(DATA_CENGSHU_ENTRY) < 100 && pInstance->GetData(DATA_DAOJISHI_ENTRY) > 0)
			{
				pInstance->SetData(DATA_TONGTIAN_STAT, 0);
			}
		}

		//void KilledUnit(Unit* /*victim*/ )
		//{
		//	me->CastSpell(me, 7, false);
		//}

		void EnterEvadeMode()
		{
			me->CastSpell(me, 7, false);
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
				me->CastSpell(me->GetVictim(), 24573, false);
				events.RepeatEvent(urand(10000, 12000));
				break;
			case EVENT_SPELL_2:
				me->CastSpell(me->GetVictim(), 75418, false);
				events.RepeatEvent(urand(14000, 16000));
				break;
			case EVENT_SPELL_3:
				me->CastSpell(me->GetVictim(), 60899, false);
				events.RepeatEvent(urand(18000, 22000));
				break;
			}

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new boss_tongtianAI(pCreature);
	}
};

class xx_zhaohuanta : public CreatureScript
{
public:
	xx_zhaohuanta() : CreatureScript("xx_zhaohuanta") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{

		if (!player || !player->IsInWorld())
			return false;

		player->PlayerTalkClass->ClearMenus();


		std::stringstream ss;

		if (player->GetTTzhaohuan1() >= 5 && player->GetTTzhaohuan2() >= 3)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --抱歉您今日可召唤首领的次数已用完--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(2, 0, ss.str().c_str(), 0, 0, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60008, creature->GetGUID());
			return true;
		}

		if (player->IsInCombat())
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:16|t    --请脱离战斗后再和我对话--";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(3, 0, ss.str().c_str(), 0, 0, "", 0);
			player->PlayerTalkClass->SendGossipMenu(60008, creature->GetGUID());
			return true;
		}
		if (player->GetTTzhaohuan1() < 5)
		{
			ss.str("");
			ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:24|t |CFF00CCFF我要召唤海加尔山首领";
			player->PlayerTalkClass->GetGossipMenu().AddMenuItem(30, 0, ss.str().c_str(), 1000, 1000, "", 0);
		}
		//if (player->GetTTzhaohuan2() < 3)
		//{
		//	ss.str("");
		//	ss << "|TInterface\\ICONS\\INV_Weapon_Shortblade_99.blp:24|t |CFF00CCFF我要召唤积雪平原首领";
		//	player->PlayerTalkClass->GetGossipMenu().AddMenuItem(31, 0, ss.str().c_str(), 1001, 1001, "", 0);
		//}

		player->PlayerTalkClass->SendGossipMenu(60008, creature->GetGUID());

		return true;
	}
	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		uint32 a = player->GetTTzhaohuan1() * 100;
		uint32 b = player->GetTTzhaohuan2() * 200;
		InstanceScript* pInstance = creature->GetInstanceScript();
		if (!pInstance)
			return true;

		if (uiSender == 1000)
		{
			if (player->GetItemCount(15, false) >= a)
			{
				pInstance->SetData(DATA_ZHAOHUAN1_STAT, 0);
				player->ModifyTTzhaohuan1(1);
				player->DestroyItemCount(15, a, true);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("需要消耗%u个积分才可召唤", a);
			}
				

		}

		if (uiSender == 1001)
		{
			if (player->GetItemCount(15, false) >= b)
			{
				pInstance->SetData(DATA_ZHAOHUAN2_STAT, 0);
				player->ModifyTTzhaohuan2(1);
				player->DestroyItemCount(15, b, true);
			}
			else
			{
				ChatHandler(player).PSendSysMessage("需要消耗%u个积分才可召唤", b);
			}
				

		}

		return true;
	}

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new xx_zhaohuantaAI(pCreature);
	}

	struct xx_zhaohuantaAI : public CreatureAI
	{
		xx_zhaohuantaAI(Creature *pCreature) : CreatureAI(pCreature) { pInstance = me->GetInstanceScript(); }

		InstanceScript* pInstance;

		void Reset()
		{
			if (!pInstance)
				return;

		}

		void EnterCombat(Unit* who)
		{

		}
		void JustDied(Unit* Killer)
		{
			pInstance->SetData(DATA_TONGTIAN_END, 0);
		}

		void UpdateAI(uint32 diff)
		{
			/*events.Update(diff);
			switch (events.GetEvent())
			{
			case EVENT_SUMMON_NPC:
			{
			if (pInstance->GetData(DATA_SHIJIAN_ENTRY) == 0)
			{
			events.ScheduleEvent(EVENT_KAIMEN, 6000);
			pInstance->SetData(DATA_BOSHU_ENTRY, pInstance->GetData(DATA_BOSHU_ENTRY) + 1);
			}
			if (pInstance->GetData(DATA_SHIJIAN_ENTRY) >= 60)
			{
			pInstance->SetData(DATA_SHIJIAN_ENTRY, 0);
			}
			pInstance->SetData(DATA_SHIJIAN_ENTRY, pInstance->GetData(DATA_SHIJIAN_ENTRY) + 1);
			events.ScheduleEvent(EVENT_SUMMON_NPC, 1000);
			}
			break;
			case EVENT_KAIMEN:
			{

			pInstance->HandleGameObject(150077, true);
			events.ScheduleEvent(EVENT_GUANMEN, 6000);
			events.PopEvent();
			}
			break;
			case EVENT_GUANMEN:
			{
			pInstance->HandleGameObject(150077, false);
			events.PopEvent();
			}
			break;
			}*/
		}
	};
};

void AddSC_xx_suoyaota()
{
	new xx_suoyaota();
	new boss_suoyao();
	new npc_suoyao();
	new xx_tongtianta();
	new boss_tongtian();
	new xx_zhaohuanta();
}