/*
* Copyright (C) 2013-2015 MegaSource <http://www.megasource.com.br>
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


#include "Cfbg.h"
#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "Player.h"
#include "Chat.h"
#include "BattlegroundQueue.h"

/*####################################################################################
###############################CROSSFACTION BATTLEGROUNDS#############################
####################################################################################*/
uint8 Unit::getRace(bool forceoriginal) const
{
	if (GetTypeId() == TYPEID_PLAYER)
	{
		Player* pPlayer = ((Player*)this);

		if (forceoriginal)
			return pPlayer->getCFSRace();

		if (pPlayer->InArena())
			return GetByteValue(UNIT_FIELD_BYTES_0, 0);

		if (!pPlayer->IsPlayingNative())
			return pPlayer->getFRace();
	}

	return GetByteValue(UNIT_FIELD_BYTES_0, 0);
}

bool Player::SendRealNameQuery()
{
	if (IsPlayingNative())
		return false;

	WorldPacket data(SMSG_NAME_QUERY_RESPONSE, (8 + 1 + 1 + 1 + 1 + 1 + 10));
	data.appendPackGUID(GetGUID());                             // player guid
	data << uint8(0);                                       // added in 3.1; if > 1, then end of packet
	data << GetName();                                   // played name
	data << uint8(0);                                       // realm name for cross realm BG usage
	data << uint8(getCFSRace());
	data << uint8(getGender());
	data << uint8(getClass());
	data << uint8(0);                                   // is not declined
	GetSession()->SendPacket(&data);

	return true;
}

void Player::SetFakeRaceAndMorph()
{
	//m_FakeRace = gett() == TEAM_ALLIANCE ? RACE_BLOODELF : RACE_HUMAN; 
	if (getClass() == CLASS_DRUID)
	{
		if (GetCFSTeam() == TEAM_ALLIANCE)
		{
			m_FakeMorph = GetDisplayId();
			m_FakeRace = RACE_TAUREN;
		}
		else if (getGender() == GENDER_MALE) // HORDE PLAYER, ONLY HAVE MALE NELF ID
		{
			m_FakeMorph = GetDisplayId();
			m_FakeRace = RACE_NIGHTELF;
		}
		else
		{ 
			m_FakeMorph = GetDisplayId();
			m_FakeRace = RACE_NIGHTELF;
		}
	}
	else if (getClass() == CLASS_SHAMAN && GetCFSTeam() == TEAM_HORDE && getGender() == GENDER_FEMALE)
	{
		m_FakeMorph = GetDisplayId();
		m_FakeRace = RACE_DRAENEI;
	}
	else
	{
		m_FakeRace = GetCFSTeam() == TEAM_ALLIANCE ? RACE_BLOODELF : RACE_HUMAN;
		m_FakeMorph = GetDisplayId();

	}
}

bool Player::SendBattleGroundChat(uint32 msgtype, std::string message)
{
	// Select distance to broadcast to.
	float distance = msgtype == CHAT_MSG_SAY ? sWorld->getFloatConfig(CONFIG_LISTEN_RANGE_SAY) : sWorld->getFloatConfig(CONFIG_LISTEN_RANGE_YELL);

	if (Battleground* pBattleGround = GetBattleground())
	{
		if (pBattleGround->isArena()) // Only fake chat in BG's. CFBG should not interfere with arenas.
			return false;

		for (Battleground::BattlegroundPlayerMap::const_iterator itr = pBattleGround->GetPlayers().begin(); itr != pBattleGround->GetPlayers().end(); ++itr)
		{
			if (Player* pPlayer = ObjectAccessor::FindPlayer(itr->first))
			{
				if (GetDistance2d(pPlayer->GetPositionX(), pPlayer->GetPositionY()) <= distance)
				{
					WorldPacket data(SMSG_MESSAGECHAT, 200);

					if (GetTeam() == pPlayer->GetTeam())
					{
						WorldPacket data;
						ChatHandler::BuildChatPacket(data, ChatMsg(msgtype), LANG_UNIVERSAL, pPlayer, NULL, message);
						pPlayer->GetSession()->SendPacket(&data);
					}
					else if (msgtype != CHAT_MSG_EMOTE)
					{
						WorldPacket data;
						ChatHandler::BuildChatPacket(data, ChatMsg(msgtype), pPlayer->GetTeam() == TEAM_ALLIANCE ? LANG_ORCISH : LANG_COMMON, pPlayer, NULL, message);
						pPlayer->GetSession()->SendPacket(&data);
					}
					pPlayer->GetSession()->SendPacket(&data);
				}
			}
		}
		return true;
	}
	else
		return false;
}

void Player::MorphFit(bool value)
{
	if (!IsPlayingNative() && value)
	{
		SetDisplayId(GetFakeMorph());
		SetNativeDisplayId(GetFakeMorph());
	}
	else
		InitDisplayIds();
}

void Player::FitPlayerInTeam(bool action, Battleground* pBattleGround)
{
	SetFakeRaceAndMorph();

	if (!pBattleGround)
		pBattleGround = GetBattleground();

	if ((!pBattleGround || pBattleGround->isArena()) && action)
		return;

	if (!IsPlayingNative() && action)
		setFactionForRace(getRace());
	else
		setFactionForRace(getCFSRace());

	if (action)
		SetForgetBGPlayers(true);
	else
		SetForgetInListPlayers(true);

	MorphFit(action);

	if (pBattleGround && action)
		SendChatMessage("%sYou are playing for the %s%s in this %s", MSG_COLOR_WHITE, GetTeam() == TEAM_ALLIANCE ? MSG_COLOR_DARKBLUE"alliance" : MSG_COLOR_RED"horde", MSG_COLOR_WHITE, pBattleGround->GetName());
}

void Player::DoForgetPlayersInList()
{
	// m_FakePlayers is filled from a vector within the battleground
	// they were in previously so all players that have been in that BG will be invalidated.
	for (FakePlayers::const_iterator itr = m_FakePlayers.begin(); itr != m_FakePlayers.end(); ++itr)
	{
		WorldPacket data(SMSG_INVALIDATE_PLAYER, 8);
		data << *itr;
		GetSession()->SendPacket(&data);
		if (Player* pPlayer = ObjectAccessor::FindPlayer(*itr))
			GetSession()->SendNameQueryOpcode(pPlayer->GetGUID());
	}
	m_FakePlayers.clear();
}

void Player::DoForgetPlayersInBG(Battleground* pBattleGround)
{
	for (Battleground::BattlegroundPlayerMap::const_iterator itr = pBattleGround->GetPlayers().begin(); itr != pBattleGround->GetPlayers().end(); ++itr)
	{
		// Here we invalidate players in the bg to the added player
		WorldPacket data1(SMSG_INVALIDATE_PLAYER, 8);
		data1 << itr->first;
		GetSession()->SendPacket(&data1);

		if (Player* pPlayer = ObjectAccessor::FindPlayer(itr->first))
		{
			GetSession()->SendNameQueryOpcode(pPlayer->GetGUID()); // Send namequery answer instantly if player is available
			// Here we invalidate the player added to players in the bg
			WorldPacket data2(SMSG_INVALIDATE_PLAYER, 8);
			data2 << GetGUID();
			pPlayer->GetSession()->SendPacket(&data2);
			pPlayer->GetSession()->SendNameQueryOpcode(GetGUID());
		}
	}
}

bool BattlegroundQueue::CheckCrossFactionMatch(BattlegroundBracketId bracket_id, Battleground* bg)
{
	if (!sWorld->getBoolConfig(CROSSFACTION_SYSTEM_BATTLEGROUNDS) || bg->isArena())
		return false; // Only do this if crossbg's are enabled.

	// Here we will add all players to selectionpool, later we check if there are enough and launch a bg.
	FillXPlayersToBG(bracket_id, bg, true);

	if (sBattlegroundMgr->isTesting() && (m_SelectionPools[TEAM_ALLIANCE].GetPlayerCount() || m_SelectionPools[TEAM_HORDE].GetPlayerCount()))
		return true;

	uint8 MPT = bg->GetMinPlayersPerTeam();
	if (m_SelectionPools[TEAM_ALLIANCE].GetPlayerCount() < MPT || m_SelectionPools[TEAM_HORDE].GetPlayerCount() < MPT)
		return false;

	return true;
}

// This function will invite players in the least populated faction, which makes battleground queues much faster.
// This function will return true if cross faction battlegrounds are enabled, otherwise return false,
// which is useful in FillPlayersToBG. Because then we can interrupt the regular invitation if cross faction bg's are enabled.


int32 BattlegroundQueue::PreAddPlayers(QueuedGroupMap m_PreGroupMap, int32 MaxAdd, uint32 MaxInTeam)
{
	int32 LeftToAdd = MaxAdd;
	uint32 Added = 0;

	for (QueuedGroupMap::reverse_iterator itr = m_PreGroupMap.rbegin(); itr != m_PreGroupMap.rend(); ++itr)
	{
		int32 PlayerSize = itr->first;
		bool alliance = itr->second->teamId == TEAM_ALLIANCE;

		if (PlayerSize <= LeftToAdd && m_SelectionPools[alliance ? TEAM_ALLIANCE : TEAM_HORDE].AddGroup(itr->second, MaxInTeam))
			LeftToAdd -= PlayerSize, Added -= PlayerSize;
	}

	return LeftToAdd;
}

void Player::SendChatMessage(const char *format, ...)
{
	if (!IsInWorld())
		return;

	if (format)
	{
		va_list ap;
		char str[2048];
		va_start(ap, format);
		vsnprintf(str, 2048, format, ap);
		va_end(ap);

		ChatHandler(GetSession()).SendSysMessage(str);
	}
}