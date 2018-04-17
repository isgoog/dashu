/*
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

#include "AnticheatMgr.h"
#include "MapManager.h"
#include "Player.h"
#include "Configuration/Config.h"
#include "Opcodes.h"
#define CLIMB_ANGLE 1.9f
#include "Unit.h"
#pragma execution_character_set("utf-8")

AnticheatMgr::AnticheatMgr()
{
}

AnticheatMgr::~AnticheatMgr()
{
	m_Players.clear();
}

void AnticheatMgr::JumpHackDetection(Player* player, MovementInfo /* movementInfo */, uint32 opcode)
{
//	if (!sConfigMgr->GetBoolDefault("Anticheat.DetectJumpHack", true))
//		return;

	uint32 key = player->GetGUIDLow();

	if (m_Players[key].GetLastOpcode() == MSG_MOVE_JUMP && opcode == MSG_MOVE_JUMP)
	{
		TeleportBack(player, key);
		//sLog->outString("AnticheatMgr:: Jump-Hack detected player %s (%u)", player->GetName().c_str(), player->GetGUIDLow());
	}
}

void AnticheatMgr::WalkOnWaterHackDetection(Player* player, MovementInfo  movementInfo, uint32 opcode)
{
//	if (!sConfigMgr->GetBoolDefault("Anticheat.DetectWaterWalkHack", true))
//		return;

	uint32 key = player->GetGUIDLow();
	/* Thanks to @LilleCarl */
	if (!m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_WATERWALKING) && !movementInfo.HasMovementFlag(MOVEMENTFLAG_WATERWALKING))
		return;

	// if we are a ghost we can walk on water
	if (!player->IsAlive())
		return;

	if (player->HasAuraType(SPELL_AURA_FEATHER_FALL) ||
		player->HasAuraType(SPELL_AURA_SAFE_FALL) ||
		player->HasAuraType(SPELL_AURA_WATER_WALK))
		return;
	if (sConfigMgr->GetBoolDefault("Anticheat.KickPlayerWaterWalkHack", false))
	{
		/* cheap hack for now, look at "applyfortargets" later*/
		/*player->AddAura(SPELL_AURA_WATER_WALK, player);
		player->RemoveAura(SPELL_AURA_WATER_WALK);*/
		//cba to double check this, just adding a kick option
		player->GetSession()->KickPlayer(true);
		//sLog->outString("AnticheatMgr:: Walk on Water - Hack detected and counteracted by kicking player %s (%u)", player->GetName().c_str(), player->GetGUIDLow());
	}
	//else {
		//sLog->outString("AnticheatMgr:: Walk on Water - Hack detected player %s (%u)", player->GetName().c_str(), player->GetGUIDLow());
	//}

	TeleportBack(player, key);
}

void AnticheatMgr::FlyHackDetection(Player* player, MovementInfo  movementInfo, uint32 opcode)
{
//    if (!sConfigMgr->GetBoolDefault("Anticheat.DetectFlyHack", true))
//        return;

	//sLog->outString("AnticheatMgr:: Walk on Water - Hack detected player %s (%u)", player->GetName().c_str(), player->GetGUIDLow());

    uint32 key = player->GetGUIDLow();

	bool stricterChecks = true;
	stricterChecks = !(movementInfo.HasMovementFlag(MOVEMENTFLAG_ASCENDING) && !player->IsInWater());
	if (!m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_FLYING) && !m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_CAN_FLY) && stricterChecks)
        return;

    if (player->HasAuraType(SPELL_AURA_FLY) ||
        player->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED) ||
        player->HasAuraType(SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED))
        return;


//    uint32 key = player->GetGUIDLow();
//    if (player->HasAuraType(SPELL_AURA_FLY) || player->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED) || player->HasAuraType(SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED))//overkill but wth
//        return;
//	/*Thanks to @LilleCarl for info to check extra flag*/
//	bool stricterChecks = true;
//	if (sConfigMgr->GetBoolDefault("Anticheat.StricterFlyHackCheck", false))
//		stricterChecks = !(movementInfo.HasMovementFlag(MOVEMENTFLAG_ASCENDING) && !player->IsInWater());
//
//    if (!movementInfo.HasMovementFlag(MOVEMENTFLAG_CAN_FLY) && !movementInfo.HasMovementFlag(MOVEMENTFLAG_FLYING) && stricterChecks)
//		return;
	//setcanfly = false;
	BuildReport(player, FLY_HACK_REPORT);
    TeleportBack(player, key);
}

void AnticheatMgr::BuildReport(Player* player, uint8 reportType)
{
	uint32 key = player->GetGUID();

	if (MustCheckTempReports(reportType))
	{
		uint32 actualTime = getMSTime();

		if (!m_Players[key].GetTempReportsTimer(reportType))
			m_Players[key].SetTempReportsTimer(actualTime, reportType);

		if (getMSTimeDiff(m_Players[key].GetTempReportsTimer(reportType), actualTime) < 3000)
		{
			m_Players[key].SetTempReports(m_Players[key].GetTempReports(reportType) + 1, reportType);

			if (m_Players[key].GetTempReports(reportType) < 3)
				return;
		}
		else
		{
			m_Players[key].SetTempReportsTimer(actualTime, reportType);
			m_Players[key].SetTempReports(1, reportType);
			return;
		}
	}

	// generating creationTime for average calculation
	if (!m_Players[key].GetTotalReports())
		m_Players[key].SetCreationTime(getMSTime());

	// increasing total_reports
	m_Players[key].SetTotalReports(m_Players[key].GetTotalReports() + 1);
	// increasing specific cheat report
	m_Players[key].SetTypeReports(reportType, m_Players[key].GetTypeReports(reportType) + 1);

	// diff time for average calculation
	uint32 diffTime = getMSTimeDiff(m_Players[key].GetCreationTime(), getMSTime()) / IN_MILLISECONDS;

	if (diffTime > 0)
	{
		// Average == Reports per second
		float average = float(m_Players[key].GetTotalReports()) / float(diffTime);
		m_Players[key].SetAverage(average);
	}

	if (sWorld->getIntConfig(CONFIG_ANTICHEAT_MAX_REPORTS_FOR_DAILY_REPORT) < m_Players[key].GetTotalReports())
	{
		if (!m_Players[key].GetDailyReportState())
		{
			CharacterDatabase.PExecute("REPLACE INTO daily_players_reports (guid,average,total_reports,speed_reports,fly_reports,jump_reports,waterwalk_reports,teleportplane_reports,climb_reports,creation_time) VALUES (%u,%f,%u,%u,%u,%u,%u,%u,%u,%u);", player->GetGUID(), m_Players[player->GetGUID()].GetAverage(), m_Players[player->GetGUID()].GetTotalReports(), m_Players[player->GetGUID()].GetTypeReports(SPEED_HACK_REPORT), m_Players[player->GetGUID()].GetTypeReports(FLY_HACK_REPORT), m_Players[player->GetGUID()].GetTypeReports(JUMP_HACK_REPORT), m_Players[player->GetGUID()].GetTypeReports(WALK_WATER_HACK_REPORT), m_Players[player->GetGUID()].GetTypeReports(TELEPORT_PLANE_HACK_REPORT), m_Players[player->GetGUID()].GetTypeReports(CLIMB_HACK_REPORT), m_Players[player->GetGUID()].GetCreationTime());
			m_Players[key].SetDailyReportState(true);
		}
	}

	if (m_Players[key].GetTotalReports() > sWorld->getIntConfig(CONFIG_ANTICHEAT_REPORTS_INGAME_NOTIFICATION))
	{
		// display warning at the center of the screen, hacky way?
		std::string str = "";
		str = "|cFFFFFC00[反作弊系统]|cFF00FFFF[|cFF60FF00" + std::string(player->GetName().c_str()) + "|cFF00FFFF] 可能正在作弊!";
		WorldPacket data(SMSG_NOTIFICATION, (str.size() + 1));
		data << str;
		sWorld->SendGlobalGMMessage(&data);
		player->GetSession()->SendNotification("反外挂系统提示您：请珍惜您的账号不要作弊，我们已将您的作弊信息发送给管理员");
		player->GetSession()->KickPlayer();
	}
}

bool AnticheatMgr::MustCheckTempReports(uint8 type)
{
	if (type == JUMP_HACK_REPORT)
		return false;

	return true;
}

void AnticheatMgr::TeleportPlaneHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode)
{
	//if (!sConfigMgr->GetBoolDefault("Anticheat.DetectTelePlaneHack", true))
	//	return;

	uint32 key = player->GetGUIDLow();

	if (m_Players[key].GetLastMovementInfo().pos.GetPositionZ() != 0 ||
		movementInfo.pos.GetPositionZ() != 0)
		return;

	if (movementInfo.HasMovementFlag(MOVEMENTFLAG_FALLING))
		return;

	// DEAD_FALLING was deprecated
	//if (player->getDeathState() == DEAD_FALLING)
	//    return;
	float x, y, z;
	player->GetPosition(x, y, z);
	float ground_Z = player->GetMap()->GetHeight(x, y, z);
	float z_diff = fabs(ground_Z - z);

	// we are not really walking there
	if (z_diff > 1.0f)
	{
		//sLog->outString("AnticheatMgr:: Teleport To Plane - Hack detected player %s (%u)", player->GetName().c_str(), player->GetGUIDLow());
//		BuildReport(player, TELEPORT_PLANE_HACK_REPORT);
		TeleportBack(player, key);
	}
}

void AnticheatMgr::StartHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode)
{
//	if (!sConfigMgr->GetBoolDefault("Anticheat.Enabled", 0))
//		return;
//
//	if (player->IsGameMaster())
//		return;

	uint32 key = player->GetGUIDLow();

	if (!m_Players[key].GetLastMovementInfo().valid)
	{
		//sLog->outString("AnticheatMgr:: notvalid");

		m_Players[key].SetLastMovementInfo(movementInfo);
		m_Players[key].SetLastOpcode(opcode);
		return;
	}


	if (player->IsInFlight() || player->GetTransport() || player->GetVehicle())
	{
//		sLog->outString("AnticheatMgr:: flight transport vehicle锛?);

		m_Players[key].SetLastMovementInfo(movementInfo);
		m_Players[key].SetLastOpcode(opcode);
		return;
	}

	bool b = SpeedHackDetection(player, movementInfo, opcode);

	if (b)
		return;

	FlyHackDetection(player, movementInfo, opcode);
	WalkOnWaterHackDetection(player, movementInfo, opcode);
	JumpHackDetection(player, movementInfo, opcode);
	TeleportPlaneHackDetection(player, movementInfo, opcode);
	ClimbHackDetection(player, movementInfo, opcode);

//	sLog->outString("AnticheatMgr:: normal锛?);
	m_Players[key].SetLastMovementInfo(movementInfo);
	m_Players[key].SetLastOpcode(opcode);
}

// basic detection
void AnticheatMgr::ClimbHackDetection(Player *player, MovementInfo movementInfo, uint32 opcode)
{
//	if (!sConfigMgr->GetBoolDefault("Anticheat.DetectClimbHack", false))
//		return;

	uint32 key = player->GetGUIDLow();

	if (opcode != MSG_MOVE_HEARTBEAT ||
		m_Players[key].GetLastOpcode() != MSG_MOVE_HEARTBEAT)
		return;

	// in this case we don't care if they are "legal" flags, they are handled in another parts of the Anticheat Manager.
	if (player->IsInWater() ||
		player->IsFlying() ||
		player->IsFalling())
		return;

	Position playerPos;
	// Position pos = player->GetPosition();

	float deltaZ = fabs(playerPos.GetPositionZ() - movementInfo.pos.GetPositionZ());
	float deltaXY = movementInfo.pos.GetExactDist2d(&playerPos);

	float angle = Position::NormalizeOrientation(tan(deltaZ / deltaXY));

	if (angle > CLIMB_ANGLE)
	{
		//sLog->outString("AnticheatMgr:: Climb-Hack detected player %s (%u)", player->GetName().c_str(), player->GetGUIDLow());
		TeleportBack(player, key);
//		BuildReport(player, CLIMB_HACK_REPORT);
	}
}

bool AnticheatMgr::SpeedHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode)
{
//	if (!sConfigMgr->GetBoolDefault("Anticheat.DetectSpeedHack", true))
	if (player->m_check96)
		return false;

	uint32 key = player->GetGUIDLow();

	// We also must check the map because the movementFlag can be modified by the client.
	// If we just check the flag, they could always add that flag and always skip the speed hacking detection.
	// 369 == DEEPRUN TRAM
	if (m_Players[key].GetLastMovementInfo().HasMovementFlag(MOVEMENTFLAG_ONTRANSPORT) && player->GetMapId() == 369)
		return false;

	uint32 distance2D = (uint32)movementInfo.pos.GetExactDist2d(&m_Players[key].GetLastMovementInfo().pos);
	uint8 moveType = 0;

	// we need to know HOW is the player moving
	// TO-DO: Should we check the incoming movement flags?
	if (player->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING))
		moveType = MOVE_SWIM;
	else if (player->IsFlying())
		moveType = MOVE_FLIGHT;
	else if (player->HasUnitMovementFlag(MOVEMENTFLAG_WALKING))
		moveType = MOVE_WALK;
	else
		moveType = MOVE_RUN;

	// how many yards the player can do in one sec.
	uint32 speedRate = (uint32)(player->GetSpeed(UnitMoveType(moveType)) + movementInfo.jump.xyspeed);

	// how long the player took to move to here.
	uint32 timeDiff = getMSTimeDiff(m_Players[key].GetLastMovementInfo().time, movementInfo.time);

	if (!timeDiff)
		timeDiff = 1;

	// this is the distance doable by the player in 1 sec, using the time done to move to this point.
	uint32 clientSpeedRate = distance2D * 1000 / timeDiff;

	// we did the (uint32) cast to accept a margin of tolerance
	if (clientSpeedRate > speedRate)
	{
//		BuildReport(player, SPEED_HACK_REPORT);
		TeleportBack(player, key);
		//sLog->outString("AnticheatMgr:: Speed-Hack detected player %s (%u)", player->GetName().c_str(), player->GetGUIDLow());

		m_Players[key].SetLastMovementInfo(movementInfo);
		m_Players[key].SetLastOpcode(opcode);
		return true;
	}

	return false;
}


void AnticheatMgr::TeleportBack(Player *player,uint32 &key) {
	if (player->ignore_next_check)
	{
		//sLog->outString("AnticheatMgr:: ignore_next_check true");
		player->ignore_next_check = false;
	} else {
		//sLog->outString("AnticheatMgr:: ignore_next_check false");

		MovementInfo lastMovmentInfo = m_Players[key].GetLastMovementInfo();

		float x = lastMovmentInfo.pos.m_positionX;
		float y = lastMovmentInfo.pos.m_positionY;
		float z = lastMovmentInfo.pos.m_positionZ;
		float ori = lastMovmentInfo.pos.m_orientation;



		//sLog->outString("AnticheatMgr::map %u x %.2f y %.2f z %.2f ori %.2f",player->GetMapId(),x, y, z, ori);

		//player->NearTeleportTo(x, y, z, ori);
		bool s = player->TeleportTo(player->GetMapId(), x, y, z, ori);

		//sLog->outString("AnticheatMgr::  s %s ", s ? "True" : "False");
	}
}

