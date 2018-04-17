/*
* Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
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

#ifndef DEF_KARAZHAN_H
#define DEF_KARAZHAN_H

#define DataHeader "KZ"

uint32 const EncounterCount = 12;
#define MAX_ENCOUNTER      12
enum KZDataTypes
{
    DATA_ATTUMEN = 0,
    DATA_MOROES = 1,
    DATA_MAIDEN = 2,
    DATA_OPTIONAL_BOSS = 3,
    DATA_OPERA_PERFORMANCE = 4,
    DATA_CURATOR = 5,
    DATA_ARAN = 6,
    DATA_TERESTIAN = 7,
    DATA_NETHERSPITE = 8,
    DATA_CHESS = 9,
    DATA_MALCHEZZAR = 10,
    DATA_NIGHTBANE = 11,
    DATA_SERVANT_QUARTERS = 12,
    DATA_SELECTED_RARE = 13,

    DATA_OPERA_OZ_DEATHCOUNT = 14,

    DATA_KILREK = 15,
    MAX_ENCOUNTERS = 16,
    DATA_GO_CURTAINS = 18,
    DATA_GO_STAGEDOORLEFT = 19,
    DATA_GO_STAGEDOORRIGHT = 20,
    DATA_GO_LIBRARY_DOOR = 21,
    DATA_GO_MASSIVE_DOOR = 22,
    DATA_GO_NETHER_DOOR = 23,
    DATA_GO_GAME_DOOR = 24,
    DATA_GO_GAME_EXIT_DOOR = 25,

    DATA_IMAGE_OF_MEDIVH = 26,
    DATA_MASTERS_TERRACE_DOOR_1 = 27,
    DATA_MASTERS_TERRACE_DOOR_2 = 28,
    DATA_GO_SIDE_ENTRANCE_DOOR = 29,
	DATA_TEAM_IN_INSTANCE = 31,
	DATA_CHESS_DAMAGE = 32,
    DATA_PRINCE = 30
};

enum KZOperaEvents
{
    EVENT_OZ = 1,
    EVENT_HOOD = 2,
    EVENT_RAJ = 3
};



enum KZMiscCreatures
{
    NPC_HYAKISS_THE_LURKER = 16179,
    NPC_ROKAD_THE_RAVAGER = 16181,
    NPC_SHADIKITH_THE_GLIDER = 16180,
    NPC_TERESTIAN_ILLHOOF = 15688,
    NPC_MOROES = 15687,
    NPC_ATTUMEN_THE_HUNTSMAN = 15550,
    NPC_ATTUMEN_THE_HUNTSMAN_MOUNTED = 16152,
    NPC_NIGHTBANE = 17225,
	NPC_ECHO_MEDIVH = 16816,

	// Chess event
	NPC_ORC_GRUNT = 17469,                    // pawn
	NPC_ORC_WOLF = 21748,                    // knight
	NPC_ORC_WARLOCK = 21750,                    // queen
	NPC_ORC_NECROLYTE = 21747,                    // bishop
	NPC_SUMMONED_DAEMON = 21726,                    // rook
	NPC_WARCHIEF_BLACKHAND = 21752,                    // king
	NPC_INVISIBLE_STALKER = 22519,                    // placeholder for dead chess npcs
	NPC_CHESS_STATUS_BAR = 22520,                    // npc that controlls the transformation of dead pieces
	NPC_CHESS_VICTORY_CONTROLLER = 22524,
	NPC_NIGHTBANE_HELPER = 17260,
	NPC_HUMAN_FOOTMAN = 17211,                    // pawn
	NPC_HUMAN_CHARGER = 21664,                    // knight
	NPC_HUMAN_CONJURER = 21683,                    // queen
	NPC_HUMAN_CLERIC = 21682,                    // bishop
	NPC_CONJURED_WATER_ELEMENTAL = 21160,                    // rook
	NPC_KING_LLANE = 21684,                    // king
	NPC_SQUARE_WHITE = 17208,                    // chess white square
	NPC_SQUARE_BLACK = 17305,                    // chess black square

    // Trash
    NPC_COLDMIST_WIDOW = 16171,
    NPC_COLDMIST_STALKER = 16170,
    NPC_SHADOWBAT = 16173,
    NPC_VAMPIRIC_SHADOWBAT = 16175,
    NPC_GREATER_SHADOWBAT = 16174,
    NPC_PHASE_HOUND = 16178,
    NPC_DREADBEAST = 16177,
    NPC_SHADOWBEAST = 16176,
    NPC_KILREK = 17229,
    NPC_RELAY = 17645
};

enum KZGameObjectIds
{
    GO_STAGE_CURTAIN = 183932,
    GO_STAGE_DOOR_LEFT = 184278,
    GO_STAGE_DOOR_RIGHT = 184279,
    GO_PRIVATE_LIBRARY_DOOR = 184517,
    GO_MASSIVE_DOOR = 185521,
    GO_GAMESMAN_HALL_DOOR = 184276,
    GO_GAMESMAN_HALL_EXIT_DOOR = 184277,
    GO_NETHERSPACE_DOOR = 185134,
    GO_MASTERS_TERRACE_DOOR = 184274,
    GO_MASTERS_TERRACE_DOOR2 = 184280,
    GO_SIDE_ENTRANCE_DOOR = 184275,
    GO_DUST_COVERED_CHEST = 185119
};

enum KZMisc
{
    OPTIONAL_BOSS_REQUIRED_DEATH_COUNT = 50
};

enum KarazhanSpells
{
	// Chess event spells
	SPELL_CLEAR_BOARD = 37366,                    // spell cast to clear the board at the end of the event
	SPELL_GAME_IN_SESSION = 39331,                    // debuff on players received while the game is in session
	SPELL_FORCE_KILL_BUNNY = 45260,                    // triggers 45259
	SPELL_GAME_OVER = 39401,                    // cast by Medivh on game end
	SPELL_VICTORY_VISUAL = 39395,                    // cast by the Victory controller on game end
    SPELL_RATTLED = 32437,
    SPELL_OVERLOAD = 29766,
    SPELL_BLINK = 29884
};

enum Miscs
{
	FACTION_ID_CHESS_HORDE = 1689,
	FACTION_ID_CHESS_ALLIANCE = 1690
};

enum Actions
{
	AI_EVENT_CUSTOM_A = 1,
	AI_EVENT_CUSTOM_B = 2,
};

const Position OptionalSpawn[] =
{
	{ -10960.981445f, -1940.138428f, 46.178097f, 4.12f }, // Hyakiss the Lurker
	{ -10945.769531f, -2040.153320f, 49.474438f, 0.077f }, // Shadikith the Glider
	{ -10899.903320f, -2085.573730f, 49.474449f, 1.38f }  // Rokad the Ravager
};

class instance_karazhan : public InstanceMapScript
{
public:
	instance_karazhan() : InstanceMapScript("instance_karazhan", 532) { }

	InstanceScript* GetInstanceScript(InstanceMap* map) const override
	{
		return new instance_karazhan_InstanceMapScript(map);
	}

	struct instance_karazhan_InstanceMapScript : public InstanceScript
	{
		instance_karazhan_InstanceMapScript(Map* map) : InstanceScript(map)
		{
			SetBossNumber(EncounterCount);
			memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
			// 1 - OZ, 2 - HOOD, 3 - RAJ, this never gets altered.
			OperaEvent = urand(EVENT_OZ, EVENT_RAJ);
			OzDeathCount = 0;
			OptionalBossCount = 0;
			m_uiAllianceStalkerCount = 0;
			m_uiHordeStalkerCount = 0;
			m_bFriendlyGame = false;
			m_uiTeam = 0;
			m_uiChessResetTimer = 0;
			m_uiChessDamages = 0;
			m_uiMedivhGUID = 0;
			m_uiChessVicConGUID = 0;
			//m_auiEncounter[9] = NOT_STARTED;
			sLog->outCommand(123, "1111111111111");
			//sLog->outCommand(123, "EventPlayerCapturedFlag %s", m_auiEncounter[9]);
		}

		bool IsEncounterInProgress() const
		{
			for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
			if (m_auiEncounter[i] == IN_PROGRESS)
				return true;

			return false;
		}

		void OnCreatureCreate(Creature* creature) override
		{
			switch (creature->GetEntry())
			{
			case NPC_KILREK:
				m_uiKilrekGUID = creature->GetGUID();
				break;
			case NPC_TERESTIAN_ILLHOOF:
				m_uiTerestianGUID = creature->GetGUID();
				break;
			case NPC_MOROES:
				m_uiMoroesGUID = creature->GetGUID();
				break;
			case NPC_NIGHTBANE:
				m_uiNightBaneGUID = creature->GetGUID();
			case NPC_RELAY:
				m_uiRelayGUID = creature->GetGUID();
			case NPC_HUMAN_CHARGER:
			case NPC_HUMAN_CLERIC:
			case NPC_HUMAN_CONJURER:
			case NPC_HUMAN_FOOTMAN:
			case NPC_CONJURED_WATER_ELEMENTAL:
			case NPC_KING_LLANE:
				m_lChessPiecesAlliance.push_back(creature->GetGUID());
				break;
			case NPC_ORC_GRUNT:
			case NPC_ORC_NECROLYTE:
			case NPC_ORC_WARLOCK:
			case NPC_ORC_WOLF:
			case NPC_SUMMONED_DAEMON:
			case NPC_WARCHIEF_BLACKHAND:
				m_lChessPiecesHorde.push_back(creature->GetGUID());
				break;
			case NPC_NIGHTBANE_HELPER:
				if (creature->GetPositionZ() < 100.0f)
					m_lNightbaneGroundTriggers.push_back(creature->GetGUID());
				else
					m_lNightbaneAirTriggers.push_back(creature->GetGUID());
				break;
			case NPC_INVISIBLE_STALKER:
				if (creature->GetPositionY() < -1870.0f)
					m_lChessHordeStalkerList.push_back(creature->GetGUID());
				else
					m_lChessAllianceStalkerList.push_back(creature->GetGUID());
				break;
			case NPC_CHESS_STATUS_BAR:
				if (creature->GetPositionY() < -1870.0f)
					m_HordeStatusGuid = creature->GetGUID();
				else
					m_AllianceStatusGuid = creature->GetGUID();
				break;
			case NPC_ECHO_MEDIVH:
				m_uiMedivhGUID = creature->GetGUID();
				break;
			case NPC_CHESS_VICTORY_CONTROLLER:
				m_uiChessVicConGUID = creature->GetGUID();
				//m_mNpcEntryGuidStore[creature->GetEntry()] = creature->GetGUID();
				break;
			}
		}

		void OnUnitDeath(Unit* unit) override
		{
			Creature* creature = unit->ToCreature();
			if (!creature)
				return;

			switch (creature->GetEntry())
			{
			case NPC_COLDMIST_WIDOW:
			case NPC_COLDMIST_STALKER:
			case NPC_SHADOWBAT:
			case NPC_VAMPIRIC_SHADOWBAT:
			case NPC_GREATER_SHADOWBAT:
			case NPC_PHASE_HOUND:
			case NPC_DREADBEAST:
			case NPC_SHADOWBEAST:
				if (GetBossState(DATA_OPTIONAL_BOSS) == TO_BE_DECIDED)
				{
					++OptionalBossCount;
					if (OptionalBossCount == OPTIONAL_BOSS_REQUIRED_DEATH_COUNT)
					{
						switch (urand(NPC_HYAKISS_THE_LURKER, NPC_ROKAD_THE_RAVAGER))
						{
						case NPC_HYAKISS_THE_LURKER:
							instance->SummonCreature(NPC_HYAKISS_THE_LURKER, OptionalSpawn[0]);
							break;
						case NPC_SHADIKITH_THE_GLIDER:
							instance->SummonCreature(NPC_SHADIKITH_THE_GLIDER, OptionalSpawn[1]);
							break;
						case NPC_ROKAD_THE_RAVAGER:
							instance->SummonCreature(NPC_ROKAD_THE_RAVAGER, OptionalSpawn[2]);
							break;
						}
					}
				}
				break;
			default:
				break;
			}
		}

		void SetData(uint32 type, uint32 data) override
		{
			switch (type)
			{
			case DATA_OPERA_OZ_DEATHCOUNT:
				if (data == SPECIAL)
					++OzDeathCount;
				else if (data == IN_PROGRESS)
					OzDeathCount = 0;
				break;
			case DATA_CHESS_DAMAGE:
				m_uiChessDamages += data;
				break;
			case DATA_CHESS:
			{
							   if (data == DONE)
							   {
								   // doors and loot are not handled for friendly games
								   if (GetData(DATA_CHESS) != SPECIAL)
								   {
									   //                            DoUseDoorOrButton(GO_GAMESMANS_HALL_EXIT_DOOR);
									   DoRespawnGameObject(DustCoveredChest, DAY);
									   if (GameObject* loot = instance->GetGameObject(DustCoveredChest))
										   loot->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
								   }

								   // cast game end spells
								   if (Creature* pMedivh = instance->GetCreature(GetData64(NPC_ECHO_MEDIVH)))
								   {
									   pMedivh->CastSpell(pMedivh, SPELL_FORCE_KILL_BUNNY, true);
									   pMedivh->CastSpell(pMedivh, SPELL_GAME_OVER, true);
									   pMedivh->CastSpell(pMedivh, SPELL_CLEAR_BOARD, true);
								   }
								   if (Creature* pController = instance->GetCreature(GetData64(NPC_CHESS_VICTORY_CONTROLLER)))
									   pController->CastSpell(pController, SPELL_VICTORY_VISUAL, true);
								   DoRemoveAurasDueToSpellOnPlayers(SPELL_GAME_IN_SESSION);
								   DoRemoveAurasDueToSpellOnPlayers(SPELL_GAME_OVER);

								   m_bFriendlyGame = false;
								   m_uiChessResetTimer = 35000;
							   }
							   else if (data == FAIL)
							   {
								   // clean the board for reset
								   if (Creature* pMedivh = instance->GetCreature(GetData64(NPC_ECHO_MEDIVH)))
								   {
									   pMedivh->CastSpell(pMedivh, SPELL_GAME_OVER, true);
									   pMedivh->CastSpell(pMedivh, SPELL_CLEAR_BOARD, true);
								   }
								   DoRemoveAurasDueToSpellOnPlayers(SPELL_GAME_IN_SESSION);
								   m_uiChessResetTimer = 35000;
							   }
							   else if (data == IN_PROGRESS || data == SPECIAL)
								   DoPrepareChessEvent();
							   m_auiEncounter[9] = data;
							   break;
			}
			}
			if (data == DONE)
			{
				OUT_SAVE_INST_DATA;

				std::ostringstream saveStream;
				saveStream << m_auiEncounter[0] << ' ' << m_auiEncounter[1] << ' ' << m_auiEncounter[2] << ' '
					<< m_auiEncounter[3] << ' ' << m_auiEncounter[4] << ' ' << m_auiEncounter[5] << ' ' << m_auiEncounter[6] << ' '
					<< m_auiEncounter[7] << ' ' << m_auiEncounter[8] << ' ' << m_auiEncounter[9] << ' ' << m_auiEncounter[10] << ' ' << m_auiEncounter[11];

				strSaveData = saveStream.str();

				SaveToDB();
				OUT_SAVE_INST_DATA_COMPLETE;
			}
		}

		bool SetBossState(uint32 type, EncounterState state) override
		{
			if (!InstanceScript::SetBossState(type, state))
				return false;

			switch (type)
			{
			case DATA_OPERA_PERFORMANCE:
				if (state == DONE)
				{
					HandleGameObject(m_uiStageDoorLeftGUID, true);
					HandleGameObject(m_uiStageDoorRightGUID, true);
					if (GameObject* sideEntrance = instance->GetGameObject(m_uiSideEntranceDoor))
						sideEntrance->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);

				}
				break;
			case DATA_CHESS:
				if (state == DONE)
					DoRespawnGameObject(DustCoveredChest, DAY);
				break;
			default:
				break;
			}

			return true;
		}


		void OnGameObjectCreate(GameObject* go) override
		{
			switch (go->GetEntry())
			{
			case GO_STAGE_CURTAIN:
				m_uiCurtainGUID = go->GetGUID();
				break;
			case GO_STAGE_DOOR_LEFT:
				m_uiStageDoorLeftGUID = go->GetGUID();
				if (GetBossState(DATA_OPERA_PERFORMANCE) == DONE)
					go->SetGoState(GO_STATE_ACTIVE);
				break;
			case GO_STAGE_DOOR_RIGHT:
				m_uiStageDoorRightGUID = go->GetGUID();
				if (GetBossState(DATA_OPERA_PERFORMANCE) == DONE)
					go->SetGoState(GO_STATE_ACTIVE);
				break;
			case GO_PRIVATE_LIBRARY_DOOR:
				m_uiLibraryDoor = go->GetGUID();
				break;
			case GO_MASSIVE_DOOR:
				m_uiMassiveDoor = go->GetGUID();
				if (GetBossState(DATA_ARAN) == !IN_PROGRESS)
					go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
				else
					go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
				break;
			case GO_GAMESMAN_HALL_DOOR:
				m_uiGamesmansDoor = go->GetGUID();
				break;
			case GO_GAMESMAN_HALL_EXIT_DOOR:
				m_uiGamesmansExitDoor = go->GetGUID();
				break;
			case GO_NETHERSPACE_DOOR:
				m_uiNetherspaceDoor = go->GetGUID();
				if (GetBossState(DATA_PRINCE) == !IN_PROGRESS)
					go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
				else
					go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
				break;
			case GO_MASTERS_TERRACE_DOOR:
				MastersTerraceDoor[0] = go->GetGUID();
				break;
			case GO_MASTERS_TERRACE_DOOR2:
				MastersTerraceDoor[1] = go->GetGUID();
				break;
			case GO_SIDE_ENTRANCE_DOOR:
				m_uiSideEntranceDoor = go->GetGUID();
				if (GetBossState(DATA_OPERA_PERFORMANCE) == DONE)
					go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
				else
					go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
				break;
			case GO_DUST_COVERED_CHEST:
				DustCoveredChest = go->GetGUID();
				break;


			}

			switch (OperaEvent)
			{
				/// @todo Set Object visibilities for Opera based on performance
			case EVENT_OZ:
				break;

			case EVENT_HOOD:
				break;

			case EVENT_RAJ:
				break;
			}
		}

		uint32 GetData(uint32 type) const override
		{
			switch (type)
			{
			case DATA_OPERA_PERFORMANCE:
				return OperaEvent;
			case DATA_OPERA_OZ_DEATHCOUNT:
				return OzDeathCount;

			case DATA_KILREK:
				return m_uiKilrekGUID;
			case DATA_TERESTIAN:
				return m_uiTerestianGUID;
			case DATA_MOROES:
				return m_uiMoroesGUID;
			case DATA_GO_STAGEDOORLEFT:
				return m_uiStageDoorLeftGUID;
			case DATA_GO_STAGEDOORRIGHT:
				return m_uiStageDoorRightGUID;
			case DATA_GO_CURTAINS:
				return m_uiCurtainGUID;
			case DATA_GO_LIBRARY_DOOR:
				return m_uiLibraryDoor;
			case DATA_GO_MASSIVE_DOOR:
				return m_uiMassiveDoor;
			case DATA_GO_SIDE_ENTRANCE_DOOR:
				return m_uiSideEntranceDoor;
			case DATA_GO_GAME_DOOR:
				return m_uiGamesmansDoor;
			case DATA_GO_GAME_EXIT_DOOR:
				return m_uiGamesmansExitDoor;
			case DATA_GO_NETHER_DOOR:
				return m_uiNetherspaceDoor;
			case DATA_MASTERS_TERRACE_DOOR_1:
				return MastersTerraceDoor[0];
			case DATA_MASTERS_TERRACE_DOOR_2:
				return MastersTerraceDoor[1];
			case DATA_IMAGE_OF_MEDIVH:
				return ImageGUID;
			case DATA_TEAM_IN_INSTANCE:     
				return m_uiTeam;
			case DATA_CHESS:                
				return m_auiEncounter[9];
			case DATA_CHESS_DAMAGE:         
				return m_uiChessDamages;
			}

			return 0;


		}

		uint64 GetData64(uint32 data) const
		{
			switch (data)
			{
			case DATA_KILREK:                   return m_uiKilrekGUID;
			case DATA_TERESTIAN:                return m_uiTerestianGUID;
			case DATA_MOROES:                   return m_uiMoroesGUID;
			case DATA_GO_STAGEDOORLEFT:         return m_uiStageDoorLeftGUID;
			case DATA_GO_STAGEDOORRIGHT:        return m_uiStageDoorRightGUID;
			case DATA_GO_CURTAINS:              return m_uiCurtainGUID;
			case DATA_GO_LIBRARY_DOOR:          return m_uiLibraryDoor;
			case DATA_GO_MASSIVE_DOOR:          return m_uiMassiveDoor;
			case DATA_GO_SIDE_ENTRANCE_DOOR:    return m_uiSideEntranceDoor;
			case DATA_GO_GAME_DOOR:             return m_uiGamesmansDoor;
			case DATA_GO_GAME_EXIT_DOOR:        return m_uiGamesmansExitDoor;
			case DATA_GO_NETHER_DOOR:           return m_uiNetherspaceDoor;
			case DATA_MASTERS_TERRACE_DOOR_1:   return MastersTerraceDoor[0];
			case DATA_MASTERS_TERRACE_DOOR_2:   return MastersTerraceDoor[1];
			case DATA_IMAGE_OF_MEDIVH:          return ImageGUID;
			case DATA_NIGHTBANE:                return m_uiNightBaneGUID;
			case NPC_ECHO_MEDIVH:               return m_uiMedivhGUID;
			case NPC_CHESS_VICTORY_CONTROLLER:  return m_uiChessVicConGUID;
			}

			return 0;
		}
		void GetChessPiecesByFaction(std::list<uint64 >& lList, uint32 uiFaction) { lList = uiFaction == FACTION_ID_CHESS_ALLIANCE ? m_lChessPiecesAlliance : m_lChessPiecesHorde; }
		bool IsCaseOccupied(Creature* creature)
		{
			for (std::list<uint64 >::const_iterator itr = m_lChessPiecesAlliance.begin(); itr != m_lChessPiecesAlliance.end(); ++itr)
			if (Creature* pChessPiece = instance->GetCreature(*itr))
			if (pChessPiece->IsAlive())
			if (pChessPiece->AI()->GetGUID() == creature->GetGUID())
				return true;

			for (std::list<uint64 >::const_iterator itr = m_lChessPiecesHorde.begin(); itr != m_lChessPiecesHorde.end(); ++itr)
			if (Creature* pChessPiece = instance->GetCreature(*itr))
			if (pChessPiece->IsAlive())
			if (pChessPiece->AI()->GetGUID() == creature->GetGUID())
				return true;
			return false;
		}
		bool instance_karazhan::instance_karazhan_InstanceMapScript::IsFriendlyGameReady()
		{
			return m_bFriendlyGame;
		}
		void DoMoveChessPieceToSides(uint32 uiSpellId, uint32 uiFaction, bool bGameEnd /*= false*/)
		{
			// assign proper faction variables
			std::vector<uint64 >& vStalkers = uiFaction == FACTION_ID_CHESS_ALLIANCE ? m_vAllianceStalkers : m_vHordeStalkers;
			uint32 uiCount = uiFaction == FACTION_ID_CHESS_ALLIANCE ? m_uiAllianceStalkerCount : m_uiHordeStalkerCount;

			// get the proper statusBar npc
			Creature* pStatusBar = instance->GetCreature(uiFaction == FACTION_ID_CHESS_ALLIANCE ? m_AllianceStatusGuid : m_HordeStatusGuid);
			if (!pStatusBar)
				return;

			if (vStalkers.size() < uiCount + 1)
				return;

			// handle stalker transformation
			if (Creature* pStalker = instance->GetCreature(vStalkers[uiCount]))
			{
				// need to provide specific target, in order to ensure the logic of the event
				pStatusBar->CastSpell(pStalker, uiSpellId, true);
				uiFaction == FACTION_ID_CHESS_ALLIANCE ? ++m_uiAllianceStalkerCount : ++m_uiHordeStalkerCount;
			}

			// handle emote on end game
			if (bGameEnd)
			{
				// inverse factions
				vStalkers.clear();
				vStalkers = uiFaction == FACTION_ID_CHESS_ALLIANCE ? m_vHordeStalkers : m_vAllianceStalkers;

				for (std::vector<uint64 >::const_iterator itr = vStalkers.begin(); itr != vStalkers.end(); ++itr)
				{
					if (Creature* pStalker = instance->GetCreature(*itr))
						pStalker->HandleEmoteCommand(EMOTE_STATE_APPLAUD);
				}
			}
		}
		void Update(uint32 uiDiff)
		{
			if (m_uiChessResetTimer)
			{
				// respawn all chess pieces and side stalkers on the original position
				if (m_uiChessResetTimer <= uiDiff)
				{
					for (std::list<uint64 >::const_iterator itr = m_lChessPiecesAlliance.begin(); itr != m_lChessPiecesAlliance.end(); ++itr)
					{
						if (Creature* pTemp = instance->GetCreature(*itr))
						{
							if (!pTemp->IsAlive())
								pTemp->Respawn();
							else
							{
								float x, y, z, o;
								pTemp->GetHomePosition(x, y, z, o);
								pTemp->NearTeleportTo(x, y, z, o);
							}
							pTemp->SetVisible(true);
						}
					}
					for (std::list<uint64 >::const_iterator itr = m_lChessPiecesHorde.begin(); itr != m_lChessPiecesHorde.end(); ++itr)
					{
						if (Creature* pTemp = instance->GetCreature(*itr))
						{
							if (!pTemp->IsAlive())
								pTemp->Respawn();
							else
							{
								float x, y, z, o;
								pTemp->GetHomePosition(x, y, z, o);
								pTemp->NearTeleportTo(x, y, z, o);
							}
							pTemp->SetVisible(true);
						}
					}

					for (std::list<uint64 >::const_iterator itr = m_lChessAllianceStalkerList.begin(); itr != m_lChessAllianceStalkerList.end(); ++itr)
					{
						if (Creature* pTemp = instance->GetCreature(*itr))
						{
							if (!pTemp->IsAlive())
								pTemp->Respawn();
							else
							{
								float x, y, z, o;
								pTemp->GetHomePosition(x, y, z, o);
								pTemp->NearTeleportTo(x, y, z, o);
							}
							pTemp->SetVisible(true);
							pTemp->HandleEmoteCommand(EMOTE_STATE_NONE);
						}
					}
					for (std::list<uint64 >::const_iterator itr = m_lChessHordeStalkerList.begin(); itr != m_lChessHordeStalkerList.end(); ++itr)
					{
						if (Creature* pTemp = instance->GetCreature(*itr))
						{
							if (!pTemp->IsAlive())
								pTemp->Respawn();
							else
							{
								float x, y, z, o;
								pTemp->GetHomePosition(x, y, z, o);
								pTemp->NearTeleportTo(x, y, z, o);
							}
							pTemp->SetVisible(true);
							pTemp->HandleEmoteCommand(EMOTE_STATE_NONE);
						}
					}

					for (std::vector<uint64 >::const_iterator itr = m_vHordeStalkers.begin(); itr != m_vHordeStalkers.end(); ++itr)
					if (Creature* pStalker = instance->GetCreature(*itr))
						pStalker->RemoveAllAuras();

					for (std::vector<uint64 >::const_iterator itr = m_vAllianceStalkers.begin(); itr != m_vAllianceStalkers.end(); ++itr)
					if (Creature* pStalker = instance->GetCreature(*itr))
						pStalker->RemoveAllAuras();

					if (GetData(DATA_CHESS) == FAIL || GetData(DATA_CHESS) == IN_PROGRESS)
						SetData(DATA_CHESS, NOT_STARTED);
					else if (GetData(DATA_CHESS) == DONE)
						m_bFriendlyGame = true;

					m_uiChessDamages = 0;
					m_uiChessResetTimer = 0;
					if (Creature* pMedivh = instance->GetCreature(GetData64(NPC_ECHO_MEDIVH)))
						pMedivh->AI()->Reset();
				}
				else
					m_uiChessResetTimer -= uiDiff;
			}
		}

		void DoPrepareChessEvent()
		{
			sLog->outCommand(123, "maidiwenchufazhiqian");
			m_uiChessDamages = 0;

			if (Creature* pMedivh = instance->GetCreature(GetData64(NPC_ECHO_MEDIVH)))
				pMedivh->AI()->DoAction(AI_EVENT_CUSTOM_B);

			// Allow all the chess pieces to init start position
			for (std::list<uint64 >::const_iterator itr = m_lChessPiecesAlliance.begin(); itr != m_lChessPiecesAlliance.end(); ++itr)
			if (Creature* pChessPiece = instance->GetCreature(*itr))
			{
				Creature* pSquare = GetClosestCreatureWithEntry(pChessPiece, NPC_SQUARE_BLACK, 2.0f);
				if (!pSquare)
					pSquare = GetClosestCreatureWithEntry(pChessPiece, NPC_SQUARE_WHITE, 2.0f);
				else
				{
					Creature* pSquare2 = GetClosestCreatureWithEntry(pChessPiece, NPC_SQUARE_WHITE, 2.0f);
					if (pSquare2)
					if (pChessPiece->GetExactDist2d(pSquare2->GetPositionX(), pSquare2->GetPositionY()) < pChessPiece->GetExactDist2d(pSquare->GetPositionX(), pSquare->GetPositionY()))
						pSquare = pSquare2;
				}
				if (!pSquare)
					return;

				// send event which will prepare the current square
				pChessPiece->AI()->SetGUID(pSquare->GetGUID());
				pChessPiece->AI()->DoAction(AI_EVENT_CUSTOM_B);
			}

			for (std::list<uint64 >::const_iterator itr = m_lChessPiecesHorde.begin(); itr != m_lChessPiecesHorde.end(); ++itr)
			if (Creature* pChessPiece = instance->GetCreature(*itr))
			{
				Creature* pSquare = GetClosestCreatureWithEntry(pChessPiece, NPC_SQUARE_BLACK, 2.0f);
				if (!pSquare)
					pSquare = GetClosestCreatureWithEntry(pChessPiece, NPC_SQUARE_WHITE, 2.0f);
				else
				{
					Creature* pSquare2 = GetClosestCreatureWithEntry(pChessPiece, NPC_SQUARE_WHITE, 2.0f);
					if (pSquare2)
					if (pChessPiece->GetExactDist2d(pSquare2->GetPositionX(), pSquare2->GetPositionY()) < pChessPiece->GetExactDist2d(pSquare->GetPositionX(), pSquare->GetPositionY()))
						pSquare = pSquare2;
				}

				if (!pSquare)
					return;

				// send event which will prepare the current square
				pChessPiece->AI()->SetGUID(pSquare->GetGUID());
				pChessPiece->AI()->DoAction(AI_EVENT_CUSTOM_B);
			}

			// add silence debuff
			DoCastSpellOnPlayers(SPELL_GAME_IN_SESSION);
			m_uiAllianceStalkerCount = 0;
			m_uiHordeStalkerCount = 0;
			m_vHordeStalkers.clear();
			m_vAllianceStalkers.clear();

			// sort stalkers depending on side
			std::list<Creature*> lStalkers;
			for (std::list<uint64 >::const_iterator itr = m_lChessHordeStalkerList.begin(); itr != m_lChessHordeStalkerList.end(); ++itr)
			if (Creature* pTemp = instance->GetCreature(*itr))
				lStalkers.push_back(pTemp);

			if (lStalkers.empty())
				return;

			// get the proper statusBar npc
			Creature* pStatusBar = instance->GetCreature(m_HordeStatusGuid);
			if (!pStatusBar)
				return;

			lStalkers.sort(Trinity::ObjectDistanceOrderPred(pStatusBar));
			for (std::list<Creature*>::const_iterator itr = lStalkers.begin(); itr != lStalkers.end(); ++itr)
				m_vHordeStalkers.push_back((*itr)->GetGUID());

			lStalkers.clear();
			for (std::list<uint64 >::const_iterator itr = m_lChessAllianceStalkerList.begin(); itr != m_lChessAllianceStalkerList.end(); ++itr)
			if (Creature* pTemp = instance->GetCreature(*itr))
				lStalkers.push_back(pTemp);

			if (lStalkers.empty())
				return;

			// get the proper statusBar npc
			pStatusBar = instance->GetCreature(m_AllianceStatusGuid);
			if (!pStatusBar)
				return;

			lStalkers.sort(Trinity::ObjectDistanceOrderPred(pStatusBar));
			for (std::list<Creature*>::const_iterator itr = lStalkers.begin(); itr != lStalkers.end(); ++itr)
				m_vAllianceStalkers.push_back((*itr)->GetGUID());
		}
		
		void Load(char const* chrIn)
		{
			if (!chrIn)
			{
				OUT_LOAD_INST_DATA_FAIL;
				return;
			}

			OUT_LOAD_INST_DATA(chrIn);
			std::istringstream loadStream(chrIn);

			loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
				>> m_auiEncounter[4] >> m_auiEncounter[5] >> m_auiEncounter[6] >> m_auiEncounter[7]
				>> m_auiEncounter[8] >> m_auiEncounter[9] >> m_auiEncounter[10] >> m_auiEncounter[11];
			for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
			if (m_auiEncounter[i] == IN_PROGRESS)                // Do not load an encounter as "In Progress" - reset it instead.
				m_auiEncounter[i] = NOT_STARTED;
			OUT_LOAD_INST_DATA_COMPLETE;
		}
		std::string GetSaveData()
		{
			return strSaveData;
		}

		void OnPlayerEnter(Player* player)
		{
			if (!m_uiTeam)
				m_uiTeam = player->GetTeamId();
		}
	private:
		uint32 OperaEvent;
		uint32 OzDeathCount;
		uint32 OptionalBossCount;
		uint32 m_auiEncounter[MAX_ENCOUNTER];
		std::string strSaveData;
		uint32 m_uiTeam;
		uint64 m_uiCurtainGUID;
		uint64 m_uiStageDoorLeftGUID;
		uint64 m_uiStageDoorRightGUID;
		uint64 m_uiKilrekGUID;
		uint64 m_uiTerestianGUID;
		uint64 m_uiMoroesGUID;
		uint64 m_uiNightBaneGUID;
		uint64 EchoOfMedivhGUID;
		uint64 m_uiLibraryDoor;                                     // Door at Shade of Aran
		uint64 m_uiMassiveDoor;                                     // Door at Netherspite
		uint64 m_uiSideEntranceDoor;                                // Side Entrance
		uint64 m_uiGamesmansDoor;                                   // Door before Chess
		uint64 m_uiGamesmansExitDoor;                               // Door after Chess
		uint64 m_uiNetherspaceDoor;                                // Door at Malchezaar
		uint64 m_uiServantsAccessDoor;                              // Door to Brocken Stair
		uint64 MastersTerraceDoor[2];
		uint64 ImageGUID;
		uint64 DustCoveredChest;
		uint64 m_uiRelayGUID;
		uint32 m_uiAllianceStalkerCount;
		uint32 m_uiHordeStalkerCount;
		uint64 m_HordeStatusGuid;
		uint64 m_AllianceStatusGuid;
		bool m_bFriendlyGame;
		uint32 m_uiChessResetTimer;
		std::list<uint64 > m_lNightbaneGroundTriggers;
		std::list<uint64 > m_lNightbaneAirTriggers;

		std::list<uint64 > m_lChessHordeStalkerList;
		std::list<uint64 > m_lChessAllianceStalkerList;
		std::list<uint64 > m_lChessPiecesAlliance;
		std::list<uint64 > m_lChessPiecesHorde;
		std::vector<uint64 > m_vHordeStalkers;
		std::vector<uint64 > m_vAllianceStalkers;
		uint32 m_uiChessDamages;

		uint64 m_uiMedivhGUID;
		uint64 m_uiChessVicConGUID;
	};
};

#endif
