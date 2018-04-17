#include "ObjectMgr.h"
#include "Common.h"
#include "Log.h"
#include <WINSOCK2.h>
#include "Config.h"
#pragma comment(lib,"ws2_32.lib")
#include <sstream>


void ObjectMgr::LoadxxCreatureTeleport()
{
	_xxCreatureTeleMap.clear();				//         0        1        2      3       4      5      6          7       8       9     10        11      12		   13
	QueryResult result = WorldDatabase.Query("SELECT MenuId, ParentId, Title, tele_x, tele_y, tele_z, tele_map, UseType, faction FROM xx_npc_teleport");

	if (!result)
	{
		sLog->outString( ">> Loaded 0 xx_npc_teleport data. DB table `xx_npc_teleport` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_creature_tele xxCreatureTeleSt;
	do
	{
		Field *fields = result->Fetch();
		xxCreatureTeleSt.menuid = fields[0].GetUInt32();
		xxCreatureTeleSt.parentid = fields[1].GetUInt32();
		xxCreatureTeleSt.title = fields[2].GetString();
		xxCreatureTeleSt.tele_x = fields[3].GetFloat();
		xxCreatureTeleSt.tele_y = fields[4].GetFloat();
		xxCreatureTeleSt.tele_z = fields[5].GetFloat();
		xxCreatureTeleSt.tele_map = fields[6].GetUInt32();
		xxCreatureTeleSt.usetype = fields[7].GetUInt32();
		xxCreatureTeleSt.factionid = fields[8].GetInt32();
		_xxCreatureTeleMap.insert(xxCreatureTeleMap::value_type(xxCreatureTeleSt.menuid, xxCreatureTeleSt));
		++counter;
	} while (result->NextRow());
	sLog->outString( ">> Loaded %u XXCORE-NPCTelePort Data.", counter);
}

void ObjectMgr::LoadxxItemb()
{
	_xxItembMap.clear();					 //        0        1      2         3         4         5         6         7         8           9        10         11           12        13     14    15     16        17
	QueryResult result = WorldDatabase.Query("SELECT ItembID FROM xx_worlditem");

	if (!result)
	{
		sLog->outString( ">> Loaded 0 xx_worlditem data. DB table `xx_worlditem` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_itemb xx_itembSt;
	do
	{
		Field *fields = result->Fetch();
		xx_itembSt.ItembID = fields[0].GetUInt32();
		_xxItembMap.insert(xxItembMap::value_type(counter, xx_itembSt));
		++counter;
	} while (result->NextRow());
	sLog->outString( ">> Loaded %u  xx_worlditem Data.", counter);
}

// 加载传送表
void ObjectMgr::LoadxxItemTeleport()
{
	_xxItemTeleMap.clear();				//         0        1        2      3       4      5      6          7       8       9     10        11      12		   13
	QueryResult result = WorldDatabase.Query("SELECT MenuId, ParentId, Title, tele_x, tele_y, tele_z, tele_map, UseType, UseV1, UseV2, NeedType, NeedV1, NeedV2, faction, vip, v1, v2 FROM xx_item_teleport");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_item_teleport data. DB table `xx_item_teleport` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_item_tele xxItemTeleSt;
	do
	{
		Field *fields = result->Fetch();
		xxItemTeleSt.menuid = fields[0].GetUInt32();
		xxItemTeleSt.parentid = fields[1].GetUInt32();
		xxItemTeleSt.title = fields[2].GetString();
		xxItemTeleSt.tele_x = fields[3].GetFloat();
		xxItemTeleSt.tele_y = fields[4].GetFloat();
		xxItemTeleSt.tele_z = fields[5].GetFloat();
		xxItemTeleSt.tele_map = fields[6].GetUInt32();
		xxItemTeleSt.usetype = fields[7].GetUInt32();
		xxItemTeleSt.usev1 = fields[8].GetInt32();
		xxItemTeleSt.usev2 = fields[9].GetInt32();
		xxItemTeleSt.needtype = fields[10].GetUInt32();
		xxItemTeleSt.needv1 = fields[11].GetInt32();
		xxItemTeleSt.needv2 = fields[12].GetInt32();
		xxItemTeleSt.factionid = fields[13].GetInt32();
		xxItemTeleSt.vip = fields[14].GetUInt32();
		xxItemTeleSt.v1 = fields[15].GetInt32();
		xxItemTeleSt.v2 = fields[16].GetInt32();
		_xxItemTeleMap.insert(xxItemTeleMap::value_type(xxItemTeleSt.menuid, xxItemTeleSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u XXCORE-TelePort Data.", counter);
}

void ObjectMgr::LoadxxItemup()
{
	_xxItemupMap.clear();					 //        0        1      2         3         4         5         6         7         8           9        10         11           12        13     14    15     16        17
	QueryResult result = WorldDatabase.Query("SELECT ItemID, RewItem, JFCost, ReqItem1,ReqItemBd1, ReqItem2,ReqItemBd2, ReqItem3,ReqItemBd3, ReqItem4,ReqItemBd4, ReqItem5,ReqItemBd5, ReqCount1, ReqCount2, ReqCount3, ReqCount4, ReqCount5, uplevel, pro, Destory, viplevel, FromId,PvpLevel,PveLevel,JbCount FROM xx_itemup");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_itemup data. DB table `xx_itemup` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_itemup xx_itemupSt;
	do
	{
		Field *fields = result->Fetch();
		xx_itemupSt.ItemID = fields[0].GetUInt32();
		xx_itemupSt.RewItem = fields[1].GetUInt32();
		xx_itemupSt.JFCost = fields[2].GetUInt32();
		xx_itemupSt.ReqItem1 = fields[3].GetUInt32();
		xx_itemupSt.ReqItemBd1 = fields[4].GetUInt32();
		xx_itemupSt.ReqItem2 = fields[5].GetUInt32();
		xx_itemupSt.ReqItemBd2 = fields[6].GetUInt32();
		xx_itemupSt.ReqItem3 = fields[7].GetUInt32();
		xx_itemupSt.ReqItemBd3 = fields[8].GetUInt32();
		xx_itemupSt.ReqItem4 = fields[9].GetUInt32();
		xx_itemupSt.ReqItemBd4 = fields[10].GetUInt32();
		xx_itemupSt.ReqItem5 = fields[11].GetUInt32();
		xx_itemupSt.ReqItemBd5 = fields[12].GetUInt32();
		xx_itemupSt.ReqCount1 = fields[13].GetUInt32();
		xx_itemupSt.ReqCount2 = fields[14].GetUInt32();
		xx_itemupSt.ReqCount3 = fields[15].GetUInt32();
		xx_itemupSt.ReqCount4 = fields[16].GetUInt32();
		xx_itemupSt.ReqCount5 = fields[17].GetUInt32();
		xx_itemupSt.upLevel = fields[18].GetUInt32();
		xx_itemupSt.Pro = fields[19].GetUInt32();
		xx_itemupSt.Destory = fields[20].GetUInt32();
		xx_itemupSt.VipLevel = fields[21].GetUInt32();
		xx_itemupSt.FromId = fields[22].GetUInt32();
		xx_itemupSt.PvpLevel = fields[23].GetUInt32();
		xx_itemupSt.PveLevel = fields[24].GetUInt32();
		xx_itemupSt.JbCount = fields[25].GetUInt32();
		_xxItemupMap.insert(xxItemupMap::value_type(counter, xx_itemupSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u  Item Upgrade Data.", counter);
}

// 加载战场控制表
void ObjectMgr::LoadxxBattleground()
{
	_xxBattleMap.clear();							//0    1     2      3			4			5			6				7			8			9			10			11		12			13			14		15		16		17		18
	QueryResult result = WorldDatabase.Query("SELECT id, winitem, winitem1, winitem2, winitem3, winitemcount, winitemcount1, winitemcount2, winitemcount3, loseitem, loseitem1, loseitem2, loseitem3, loseitemcount, loseitemcount1, loseitemcount2, loseitemcount3,killitem,killitem1,killitem2,killitem3,killcount,killcount1,killcount2,killcount3,maxhealth FROM xx_battleground");
	if (!result)
	{
		sLog->outString("Load 0 xx_battle_template Data, Table `xx_battle_template` is Empty!");
		return;
	}
	uint32 counter = 0;
	xx_battle xx_battleSt;
	do{
		Field *fields = result->Fetch();
		xx_battleSt.Entry = fields[0].GetUInt32();
		xx_battleSt.winitem = fields[1].GetUInt32();
		xx_battleSt.winitem1 = fields[2].GetUInt32();
		xx_battleSt.winitem2 = fields[3].GetUInt32();
		xx_battleSt.winitem3 = fields[4].GetUInt32();
		xx_battleSt.wincount = fields[5].GetUInt32();
		xx_battleSt.wincount1 = fields[6].GetUInt32();
		xx_battleSt.wincount2 = fields[7].GetUInt32();
		xx_battleSt.wincount3 = fields[8].GetUInt32();
		xx_battleSt.loseitem = fields[9].GetUInt32();
		xx_battleSt.loseitem1 = fields[10].GetUInt32();
		xx_battleSt.loseitem2 = fields[11].GetUInt32();
		xx_battleSt.loseitem3 = fields[12].GetUInt32();
		xx_battleSt.losecount = fields[13].GetUInt32();
		xx_battleSt.losecount1 = fields[14].GetUInt32();
		xx_battleSt.losecount2 = fields[15].GetUInt32();
		xx_battleSt.losecount3 = fields[16].GetUInt32();
		xx_battleSt.killitem = fields[17].GetUInt32();
		xx_battleSt.killitem1 = fields[18].GetUInt32();
		xx_battleSt.killitem2 = fields[19].GetUInt32();
		xx_battleSt.killitem3 = fields[20].GetUInt32();
		xx_battleSt.killcount = fields[21].GetUInt32();
		xx_battleSt.killcount1 = fields[22].GetUInt32();
		xx_battleSt.killcount2 = fields[23].GetUInt32();
		xx_battleSt.killcount3 = fields[24].GetUInt32();
		xx_battleSt.maxhealth = fields[25].GetUInt32();
		counter++;
		_xxBattleMap.insert(xxBattleMap::value_type(xx_battleSt.Entry, xx_battleSt));
	} while (result->NextRow());
	sLog->outString(">> Load %u For xx_battle Data!!", counter);
	return;
}

void ObjectMgr::LoadPvpRankSystem()
{
	m_xxPvpRankMap.clear();		               //        0            1         2		  3			  4			    5          6
	QueryResult result = WorldDatabase.Query("SELECT pvp_level, lmTitleId, blTitleId, lmreq_ItemId1, lmreq_ItemId2, lmreq_Count1, lmreq_Count2,blreq_ItemId1, blreq_ItemId2, blreq_Count1, blreq_Count2,lmrew_ItemId1,lmrew_Count1,blrew_ItemId1,blrew_Count1,lmaura,blaura,add_talent,add_pvp FROM xx_pvprank");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_pvprank data. DB table `xx_pvprank` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_pvprank xx_pvprankSt;
	do
	{
		Field *fields = result->Fetch();
		xx_pvprankSt.pvp_level = fields[0].GetUInt32();
		xx_pvprankSt.lmTitleId = fields[1].GetUInt32();
		xx_pvprankSt.blTitleId = fields[2].GetUInt32();
		xx_pvprankSt.lmreq_ItemId1 = fields[3].GetUInt32();
		xx_pvprankSt.lmreq_ItemId2 = fields[4].GetUInt32();
		xx_pvprankSt.lmreq_ItemCount1 = fields[5].GetUInt32();
		xx_pvprankSt.lmreq_ItemCount2 = fields[6].GetUInt32();
		xx_pvprankSt.blreq_ItemId1 = fields[7].GetUInt32();
		xx_pvprankSt.blreq_ItemId2 = fields[8].GetUInt32();
		xx_pvprankSt.blreq_ItemCount1 = fields[9].GetUInt32();
		xx_pvprankSt.blreq_ItemCount2 = fields[10].GetUInt32();
		xx_pvprankSt.lmrew_ItemId1 = fields[11].GetUInt32();
		xx_pvprankSt.lmrew_ItemCount1 = fields[12].GetUInt32();
		xx_pvprankSt.blrew_ItemId1 = fields[13].GetUInt32();
		xx_pvprankSt.blrew_ItemCount1 = fields[14].GetUInt32();
		xx_pvprankSt.lmAura = fields[15].GetUInt32();
		xx_pvprankSt.blAura = fields[16].GetUInt32();
		xx_pvprankSt.add_talent = fields[17].GetUInt32();
		xx_pvprankSt.add_pvp = fields[18].GetUInt32();
		m_xxPvpRankMap.insert(xxPvpRankMap::value_type(xx_pvprankSt.pvp_level, xx_pvprankSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u pvprank Data.", counter);
}

void ObjectMgr::LoadMapidvalue()
{											//         0     1
	QueryResult result = WorldDatabase.Query("SELECT stat, value FROM xx_mapid_add");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_mapid_add data. DB table `xx_mapid_add` is empty.");
		return;
	}

	uint32 counter = 0;
	do
	{
		Field *fields = result->Fetch();
		xxcoremapid[fields[0].GetInt8()] = fields[1].GetInt32();
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_mapid_add Data.", counter);
}

void ObjectMgr::LoadMapididvalue()
{											//         0     1
	QueryResult result = WorldDatabase.Query("SELECT stat, value FROM xx_mapid");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_mapid data. DB table `xx_mapid` is empty.");
		return;
	}

	uint32 counter = 0;
	do
	{
		Field *fields = result->Fetch();
		xxcoremapidid[fields[0].GetInt8()] = fields[1].GetInt32();
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_mapid Data.", counter);
}

void ObjectMgr::LoadFuyinData()
{
	m_xxfuyinmap.clear();			      //         0             1
	QueryResult result = WorldDatabase.Query("SELECT level,reqitem1,reqitem2,reqitem3,reqitemcount1,reqitemcount2,reqitemcount3,shangxian FROM xx_fuyin_update");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_fuyin_update data. DB table `xx_fuyin_update` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_fuyin xxfuyinSt;
	do
	{
		Field *fields = result->Fetch();
		xxfuyinSt.level = fields[0].GetUInt32();
		xxfuyinSt.reqitem1 = fields[1].GetUInt32();
		xxfuyinSt.reqitem2 = fields[2].GetUInt32();
		xxfuyinSt.reqitem3 = fields[3].GetUInt32();
		xxfuyinSt.reqitemcount1 = fields[4].GetUInt32();
		xxfuyinSt.reqitemcount2 = fields[5].GetUInt32();
		xxfuyinSt.reqitemcount3 = fields[6].GetUInt32();
		xxfuyinSt.shangxian = fields[7].GetUInt32();
		m_xxfuyinmap.insert(xxfuyin::value_type(xxfuyinSt.level, xxfuyinSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_fuyin_update Data.", counter);
}

void ObjectMgr::LoadxxVipSystem()
{
	_xxVipSystemMap.clear();			      //         0        1        2         3              4             5              6               7					8				9				10		11       12
	QueryResult result = WorldDatabase.Query("SELECT viplevel, Title, SayColor,  add_talent, rate_drop_pro, rate_upgrade_pro, add_online_point, LogonAnnounce, req_jf, ReqardItem, ReqardCount, RewardItem, RewardCount,aura,addliliang,addminjie,addnaili,addzhili,addjingshen,addjisu,addjingtong,addrenxing,tongtianadd,startlevel,dkstartlevel,quanshuxing,add_online_item,SpellTitle  FROM xx_vip_system");

	if (!result)
	{
		sLog->outString(">> Loaded 0 XXCCORE-vip data. DB table `xx_vip_system` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_vip_system xxVipSystemSt;
	do{
		Field *fields = result->Fetch();
		xxVipSystemSt.VipLevel = fields[0].GetUInt32();
		xxVipSystemSt.Title = fields[1].GetString();
		xxVipSystemSt.SayColor = fields[2].GetString();
		xxVipSystemSt.add_talent = fields[3].GetUInt32();
		xxVipSystemSt.rate_drop_pro = fields[4].GetUInt32();
		xxVipSystemSt.rate_upgrade_pro = fields[5].GetUInt32();
		xxVipSystemSt.add_online_point = fields[6].GetUInt32();
		xxVipSystemSt.LoginAnnounce = fields[7].GetString();
		xxVipSystemSt.req_jf = fields[8].GetUInt32();
		xxVipSystemSt.ReqardItemId = fields[9].GetUInt32();
		xxVipSystemSt.ReqardItemCount = fields[10].GetUInt32();
		xxVipSystemSt.RewardItemId = fields[11].GetUInt32();
		xxVipSystemSt.RewardItemCount = fields[12].GetUInt32();
		xxVipSystemSt.Aura = fields[13].GetUInt32();
		xxVipSystemSt.addliliang = fields[14].GetUInt32();
		xxVipSystemSt.addminjie = fields[15].GetUInt32();
		xxVipSystemSt.addnaili = fields[16].GetUInt32();
		xxVipSystemSt.addzhili = fields[17].GetUInt32();
		xxVipSystemSt.addjingshen = fields[18].GetUInt32();
		xxVipSystemSt.addjisu = fields[19].GetUInt32();
		xxVipSystemSt.addjingtong = fields[20].GetUInt32();
		xxVipSystemSt.addrenxing = fields[21].GetUInt32();
		xxVipSystemSt.tongtianadd = fields[22].GetUInt32();
		xxVipSystemSt.startlevel = fields[23].GetUInt32();
		xxVipSystemSt.dkstartlevel = fields[24].GetUInt32();
		xxVipSystemSt.quanshuxing = fields[25].GetFloat();
		xxVipSystemSt.add_online_item = fields[26].GetUInt32();
		xxVipSystemSt.SpellTitle = fields[27].GetString();
		//xxVipSystemSt.minjie = fields[26].GetUInt32();
		//xxVipSystemSt.naili = fields[27].GetUInt32();
		//xxVipSystemSt.zhili = fields[28].GetUInt32();
		//xxVipSystemSt.jingshen = fields[29].GetUInt32();
		_xxVipSystemMap.insert(xxVipSystemMap::value_type(xxVipSystemSt.VipLevel, xxVipSystemSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u Vip Data.", counter);
}

void ObjectMgr::LoadxxVipSystemMr()
{
	_xxVipSystemMrMap.clear();			      //         0        1        2         3              4             5              6               7					8				9				10		11       12
	QueryResult result = WorldDatabase.Query("SELECT viplevel,RewardItem1,RewardItem2,RewardItem3, RewardItem4,RewardItem5,RewardCount1,RewardCount2,RewardCount3,RewardCount4,RewardCount5  FROM xx_vip_systemmr");

	if (!result)
	{
		sLog->outString(">> Loaded 0 XXCCORE-vipmr data. DB table `xx_vip_systemmr` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_vip_systemmr xxVipSystemmrSt;
	do{
		Field *fields = result->Fetch();
		xxVipSystemmrSt.VipLevel = fields[0].GetUInt32();
		xxVipSystemmrSt.RewardItemId1 = fields[1].GetUInt32();
		xxVipSystemmrSt.RewardItemId2 = fields[2].GetUInt32();
		xxVipSystemmrSt.RewardItemId3 = fields[3].GetUInt32();
		xxVipSystemmrSt.RewardItemId4 = fields[4].GetUInt32();
		xxVipSystemmrSt.RewardItemId5 = fields[5].GetUInt32();
		xxVipSystemmrSt.RewardItemCount1 = fields[6].GetUInt32();
		xxVipSystemmrSt.RewardItemCount2 = fields[7].GetUInt32();
		xxVipSystemmrSt.RewardItemCount3 = fields[8].GetUInt32();
		xxVipSystemmrSt.RewardItemCount4 = fields[9].GetUInt32();
		xxVipSystemmrSt.RewardItemCount5 = fields[10].GetUInt32();
		_xxVipSystemMrMap.insert(xxVipSystemMrMap::value_type(xxVipSystemmrSt.VipLevel, xxVipSystemmrSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u Vipmr Data.", counter);
}

void ObjectMgr::LoadxxItembuff()
{
	_xxItembuffMap.clear();					 //        0        1      2         3         4         5         6         7         8           9        10         11           12        13     14    15     16        17
	QueryResult result = WorldDatabase.Query("SELECT buffID FROM xx_buff");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_buff data. DB table `xx_buff` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_itembuff xx_itembuffSt;
	do
	{
		Field *fields = result->Fetch();
		xx_itembuffSt.buffID = fields[0].GetUInt32();
		_xxItembuffMap.insert(xxItembuffMap::value_type(counter, xx_itembuffSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u  xx_buff Data.", counter);
}

void ObjectMgr::LoadRaidSystem()
{
	m_xxRaidMap.clear();		               //        0            1         2		  3			  4			    5          6
	QueryResult result = WorldDatabase.Query("SELECT id, lootid1, lootid2, lootid3, lootid4, lootid5, lootid6, lootid7, lootid8, lootid9, lootid10 FROM xx_Raid");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_Raid data. DB table `xx_Raid` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_raid xx_raidSt;
	do
	{
		Field *fields = result->Fetch();
		xx_raidSt.id = fields[0].GetUInt32();
		xx_raidSt.lootid1= fields[1].GetUInt32();
		xx_raidSt.lootid2 = fields[2].GetUInt32();
		xx_raidSt.lootid3 = fields[3].GetUInt32();
		xx_raidSt.lootid4 = fields[4].GetUInt32();
		xx_raidSt.lootid5 = fields[5].GetUInt32();
		xx_raidSt.lootid6 = fields[6].GetUInt32();
		xx_raidSt.lootid7 = fields[7].GetUInt32();
		xx_raidSt.lootid8 = fields[8].GetUInt32();
		xx_raidSt.lootid9 = fields[9].GetUInt32();
		xx_raidSt.lootid10 = fields[10].GetUInt32();
		m_xxRaidMap.insert(xxRaidMap::value_type(xx_raidSt.id, xx_raidSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u Raid Data.", counter);
}

void ObjectMgr::LoadSuoyaoSystem()
{
	m_xxSuoyaoMap.clear();		               //        0            1         2		  3			  4			    5          6
	QueryResult result = WorldDatabase.Query("SELECT level, bossid, npcid FROM xx_suoyao");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_Suoyao data. DB table `xx_Suoyao` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_suoyao xx_suoyaoSt;
	do
	{
		Field *fields = result->Fetch();
		xx_suoyaoSt.level = fields[0].GetUInt32();
		xx_suoyaoSt.bossid = fields[1].GetUInt32();
		xx_suoyaoSt.npcid = fields[2].GetUInt32();
		m_xxSuoyaoMap.insert(xxSuoyaoMap::value_type(xx_suoyaoSt.level, xx_suoyaoSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u Suoyao Data.", counter);
}

void ObjectMgr::LoadSuoSystem()
{
	m_xxSuoMap.clear();		               //        0            1         2		  3			  4			    5          6
	QueryResult result = WorldDatabase.Query("SELECT npcid, minjf,maxjf FROM xx_suo");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_Suo data. DB table `xx_Suo` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_suo xx_suoSt;
	do
	{
		Field *fields = result->Fetch();
		xx_suoSt.npcid = fields[0].GetUInt32();
		xx_suoSt.minjf = fields[1].GetUInt32();
		xx_suoSt.maxjf = fields[2].GetUInt32();
		m_xxSuoMap.insert(xxSuoMap::value_type(xx_suoSt.npcid, xx_suoSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u Suo Data.", counter);
}

void ObjectMgr::LoadTongtianSystem()
{
	m_xxTongtianMap.clear();		               //        0            1         2		  3			  4			    5          6
	QueryResult result = WorldDatabase.Query("SELECT level, bossid FROM xx_tongtian");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_tongtian data. DB table `xx_tongtian` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_tongtian xx_tongtianSt;
	do
	{
		Field *fields = result->Fetch();
		xx_tongtianSt.level = fields[0].GetUInt32();
		xx_tongtianSt.bossid = fields[1].GetUInt32();
		m_xxTongtianMap.insert(xxTongtianMap::value_type(xx_tongtianSt.level, xx_tongtianSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u tongtian Data.", counter);
}

void ObjectMgr::LoadTongSystem()
{
	m_xxTongMap.clear();		               //        0            1         2		  3			  4			    5          6
	QueryResult result = WorldDatabase.Query("SELECT npcid, minjf,maxjf FROM xx_tong");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_Tong data. DB table `xx_Tong` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_tong xx_tongSt;
	do
	{
		Field *fields = result->Fetch();
		xx_tongSt.npcid = fields[0].GetUInt32();
		xx_tongSt.minjf = fields[1].GetUInt32();
		xx_tongSt.maxjf = fields[2].GetUInt32();
		m_xxTongMap.insert(xxTongMap::value_type(xx_tongSt.npcid, xx_tongSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u Tong Data.", counter);
}

void ObjectMgr::LoadSkillSystem()
{
	m_xxSkillMap.clear();		               //        0            1         2		  3			  4			    5          6
	QueryResult result = WorldDatabase.Query("SELECT skillid, aura1, aura2, aura3, aura4, aura5, aura6, aura7, aura8, aura9 FROM xx_skill");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_skill data. DB table `xx_skill` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_skill xx_skillSt;
	do
	{
		Field *fields = result->Fetch();
		xx_skillSt.skillid = fields[0].GetUInt32();
		xx_skillSt.aura1 = fields[1].GetUInt32();
		xx_skillSt.aura2 = fields[2].GetUInt32();
		xx_skillSt.aura3 = fields[3].GetUInt32();
		xx_skillSt.aura4 = fields[4].GetUInt32();
		xx_skillSt.aura5 = fields[5].GetUInt32();
		xx_skillSt.aura6 = fields[6].GetUInt32();
		xx_skillSt.aura7 = fields[7].GetUInt32();
		xx_skillSt.aura8 = fields[8].GetUInt32();
		xx_skillSt.aura9 = fields[9].GetUInt32();
		m_xxSkillMap.insert(xxSkillMap::value_type(xx_skillSt.skillid, xx_skillSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u Skill Data.", counter);
}

void ObjectMgr::LoadxxItem()
{
	_xxItemMap.clear();					 //        0        1      2         3         4         5         6         7         8           9        10         11           12        13     14    15     16        17
	QueryResult result = WorldDatabase.Query("SELECT level, ItemID FROM xx_item");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_item data. DB table `xx_item` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_item xx_itemSt;
	do
	{
		Field *fields = result->Fetch();
		xx_itemSt.level = fields[0].GetUInt32();
		xx_itemSt.ItemID = fields[1].GetUInt32();
		_xxItemMap.insert(xxItemMap::value_type(counter, xx_itemSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u  xx_item Data.", counter);
}

void ObjectMgr::LoadxxItemicc()
{
	_xxItemiccMap.clear();					 //        0        1      2         3         4         5         6         7         8           9        10         11           12        13     14    15     16        17
	QueryResult result = WorldDatabase.Query("SELECT level, ItemID FROM xx_itemicc");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_itemicc data. DB table `xx_itemicc` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_itemicc xx_itemiccSt;
	do
	{
		Field *fields = result->Fetch();
		xx_itemiccSt.level = fields[0].GetUInt32();
		xx_itemiccSt.ItemID = fields[1].GetUInt32();
		_xxItemiccMap.insert(xxItemiccMap::value_type(counter, xx_itemiccSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u  xx_itemicc Data.", counter);
}

void ObjectMgr::LoadxxItemcj()
{
	_xxItemcjMap.clear();					 //        0        1      2         3         4         5         6         7         8           9        10         11           12        13     14    15     16        17
	QueryResult result = WorldDatabase.Query("SELECT ItemID, RewItem, RewItemmin, RewItemmax,FromId FROM xx_itemcj");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_itemcj data. DB table `xx_itemcj` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_itemcj xx_itemcjSt;
	do
	{
		Field *fields = result->Fetch();
		xx_itemcjSt.ItemID = fields[0].GetUInt32();
		xx_itemcjSt.RewItem = fields[1].GetUInt32();
		xx_itemcjSt.RewItemmin = fields[2].GetUInt32();
		xx_itemcjSt.RewItemmax = fields[3].GetUInt32();
		xx_itemcjSt.FromId = fields[4].GetUInt32();
		_xxItemcjMap.insert(xxItemcjMap::value_type(counter, xx_itemcjSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u  Item cjgrade Data.", counter);
}

void ObjectMgr::LoadxxItemzh()
{
	_xxItemzhMap.clear();					 //        0        1      2         3         4         5         6         7         8           9        10         11           12        13     14    15     16        17
	QueryResult result = WorldDatabase.Query("SELECT ItemID, RewItem, RewItemmin, Jb, FromId FROM xx_itemzh");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_itemzh data. DB table `xx_itemzh` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_itemzh xx_itemzhSt;
	do
	{
		Field *fields = result->Fetch();
		xx_itemzhSt.ItemID = fields[0].GetUInt32();
		xx_itemzhSt.RewItem = fields[1].GetUInt32();
		xx_itemzhSt.RewItemmin = fields[2].GetUInt32();
		xx_itemzhSt.Jb = fields[3].GetUInt32();
		xx_itemzhSt.FromId = fields[4].GetUInt32();
		_xxItemzhMap.insert(xxItemzhMap::value_type(counter, xx_itemzhSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u  Item zhgrade Data.", counter);
}

void ObjectMgr::LoadRaidBoxSystem()
{
	m_xxRaidBoxMap.clear();		               //        0            1         2		  3			  4			    5          6
	QueryResult result = WorldDatabase.Query("SELECT id, lootid1, lootid2, lootid3, lootid4, lootid5, lootid6, lootid7, lootid8, lootid9, lootid10 FROM xx_RaidBox");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_RaidBox data. DB table `xx_RaidBox` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_raidbox xx_raidboxSt;
	do
	{
		Field *fields = result->Fetch();
		xx_raidboxSt.id = fields[0].GetUInt32();
		xx_raidboxSt.lootid1 = fields[1].GetUInt32();
		xx_raidboxSt.lootid2 = fields[2].GetUInt32();
		xx_raidboxSt.lootid3 = fields[3].GetUInt32();
		xx_raidboxSt.lootid4 = fields[4].GetUInt32();
		xx_raidboxSt.lootid5 = fields[5].GetUInt32();
		xx_raidboxSt.lootid6 = fields[6].GetUInt32();
		xx_raidboxSt.lootid7 = fields[7].GetUInt32();
		xx_raidboxSt.lootid8 = fields[8].GetUInt32();
		xx_raidboxSt.lootid9 = fields[9].GetUInt32();
		xx_raidboxSt.lootid10 = fields[10].GetUInt32();
		m_xxRaidBoxMap.insert(xxRaidBoxMap::value_type(xx_raidboxSt.id, xx_raidboxSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u RaidBox Data.", counter);
}

void ObjectMgr::Loadxxnpc()
{
	_xxnpcMap.clear();					 //        0        1      2         3         4         5         6         7         8           9        10         11           12        13     14    15     16        17
	QueryResult result = WorldDatabase.Query("SELECT id, npcID FROM xx_worldnpc");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_worldnpc data. DB table `xx_worldnpc` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_npc xx_npcSt;
	do
	{
		Field *fields = result->Fetch();
		xx_npcSt.id = fields[0].GetUInt32();
		xx_npcSt.npcID = fields[1].GetUInt32();
		_xxnpcMap.insert(xxnpcMap::value_type(counter, xx_npcSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u  xx_worldnpc Data.", counter);
}

void ObjectMgr::LoadJntupoData()
{
	m_xxjntpmap.clear();			      //         0             1
	QueryResult result = WorldDatabase.Query("SELECT level,reqitem1,reqitem2,reqitemcount1,reqitemcount2,jb,shangxian FROM xx_jntp_update");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_jntp_update data. DB table `xx_jntp_update` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_jntp xxjntpSt;
	do
	{
		Field *fields = result->Fetch();
		xxjntpSt.level = fields[0].GetUInt32();
		xxjntpSt.reqitem1 = fields[1].GetUInt32();
		xxjntpSt.reqitem2 = fields[2].GetUInt32();
		xxjntpSt.reqitemcount1 = fields[3].GetUInt32();
		xxjntpSt.reqitemcount2 = fields[4].GetUInt32();
		xxjntpSt.jb = fields[5].GetUInt32();
		xxjntpSt.shangxian = fields[6].GetUInt32();
		m_xxjntpmap.insert(xxjntp::value_type(xxjntpSt.level, xxjntpSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_jntp_update Data.", counter);
}

void ObjectMgr::LoadJnjuexingData()
{
	m_xxjnjxmap.clear();			      //         0             1
	QueryResult result = WorldDatabase.Query("SELECT level,reqitem1,reqitem2,reqitemcount1,reqitemcount2,jb,shangxian FROM xx_jnjx_update");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_jnjx_update data. DB table `xx_jnjx_update` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_jnjx xxjnjxSt;
	do
	{
		Field *fields = result->Fetch();
		xxjnjxSt.level = fields[0].GetUInt32();
		xxjnjxSt.reqitem1 = fields[1].GetUInt32();
		xxjnjxSt.reqitem2 = fields[2].GetUInt32();
		xxjnjxSt.reqitemcount1 = fields[3].GetUInt32();
		xxjnjxSt.reqitemcount2 = fields[4].GetUInt32();
		xxjnjxSt.jb = fields[5].GetUInt32();
		xxjnjxSt.shangxian = fields[6].GetUInt32();
		m_xxjnjxmap.insert(xxjnjx::value_type(xxjnjxSt.level, xxjnjxSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_jnjx_update Data.", counter);
}

void ObjectMgr::LoadJnpeiyangData()
{
	m_xxjnpymap.clear();			      //         0             1
	QueryResult result = WorldDatabase.Query("SELECT level,reqitem1,reqitem2,reqitemcount1,reqitemcount2,jb,shangxian FROM xx_jnpy_update");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_jnpy_update data. DB table `xx_jnpy_update` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_jnpy xxjnpySt;
	do
	{
		Field *fields = result->Fetch();
		xxjnpySt.level = fields[0].GetUInt32();
		xxjnpySt.reqitem1 = fields[1].GetUInt32();
		xxjnpySt.reqitem2 = fields[2].GetUInt32();
		xxjnpySt.reqitemcount1 = fields[3].GetUInt32();
		xxjnpySt.reqitemcount2 = fields[4].GetUInt32();
		xxjnpySt.jb = fields[5].GetUInt32();
		xxjnpySt.shangxian = fields[6].GetUInt32();
		m_xxjnpymap.insert(xxjnpy::value_type(xxjnpySt.level, xxjnpySt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_jnpy_update Data.", counter);
}

void ObjectMgr::LoadHuoliSystem()
{
	m_xxHuoliMap.clear();		               //        0            1         2		  3			  4			    5          6
	QueryResult result = WorldDatabase.Query("SELECT npcid, itemid, minitem,maxitem,minmoney,maxmoney FROM xx_huoli");

	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_Huoli data. DB table `xx_Huoli` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_huoli xx_huoliSt;
	do
	{
		Field *fields = result->Fetch();
		xx_huoliSt.npcid = fields[0].GetUInt32();
		xx_huoliSt.itemid = fields[1].GetUInt32();
		xx_huoliSt.minitem = fields[2].GetUInt32();
		xx_huoliSt.maxitem = fields[3].GetUInt32();
		xx_huoliSt.minmoney = fields[4].GetUInt32();
		xx_huoliSt.maxmoney = fields[5].GetUInt32();
		m_xxHuoliMap.insert(xxHuoliMap::value_type(xx_huoliSt.npcid, xx_huoliSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u Huoli Data.", counter);
}

void ObjectMgr::LoadYuyiData()
{
	m_xxyuyimap.clear();			      //         0             1
	QueryResult result = WorldDatabase.Query("SELECT level,reqitem1,reqitemcount1,jb,shangxian FROM xx_yuyi_update");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_yuyi_update data. DB table `xx_yuyi_update` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_yuyi xxyuyiSt;
	do
	{
		Field *fields = result->Fetch();
		xxyuyiSt.level = fields[0].GetUInt32();
		xxyuyiSt.reqitem1 = fields[1].GetUInt32();
		xxyuyiSt.reqitemcount1 = fields[2].GetUInt32();
		xxyuyiSt.jb = fields[3].GetUInt32();
		xxyuyiSt.shangxian = fields[4].GetUInt32();
		m_xxyuyimap.insert(xxyuyi::value_type(xxyuyiSt.level, xxyuyiSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_yuyi_update Data.", counter);
}

void ObjectMgr::Loadxxcjjf()
{
	m_xxcjjfmap.clear();			      //         0             1
	QueryResult result = WorldDatabase.Query("SELECT id,rewitem,rewitemcount,gonggao FROM xx_cjjf_update");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_cjjf_update data. DB table `xx_cjjf_update` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_cjjf xxcjjfSt;
	do
	{
		Field *fields = result->Fetch();
		xxcjjfSt.id = fields[0].GetUInt32();
		xxcjjfSt.rewitem = fields[1].GetUInt32();
		xxcjjfSt.rewitemcount = fields[2].GetUInt32();
		xxcjjfSt.gonggao = fields[3].GetUInt32();
		m_xxcjjfmap.insert(xxcjjf::value_type(xxcjjfSt.id, xxcjjfSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_cjjf_update Data.", counter);
}

void ObjectMgr::Loadxxcjzjf()
{
	m_xxcjjfmap.clear();			      //         0             1
	QueryResult result = WorldDatabase.Query("SELECT id,rewitem,gonggao FROM xx_cjzjf_update");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_cjzjf_update data. DB table `xx_cjzjf_update` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_cjzjf xxcjjfSt;
	do
	{
		Field *fields = result->Fetch();
		xxcjjfSt.id = fields[0].GetUInt32();
		xxcjjfSt.rewitem = fields[1].GetUInt32();
		xxcjjfSt.gonggao = fields[2].GetUInt32();
		m_xxcjzjfmap.insert(xxcjzjf::value_type(xxcjjfSt.id, xxcjjfSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_cjzjf_update Data.", counter);
}

void ObjectMgr::Loadxxcjzzjf()
{
	m_xxcjjfmap.clear();			      //         0             1
	QueryResult result = WorldDatabase.Query("SELECT id,rewitem,gonggao FROM xx_cjzzjf_update");
	if (!result)
	{
		sLog->outString(">> Loaded 0 xx_cjzzjf_update data. DB table `xx_cjzzjf_update` is empty.");
		return;
	}

	uint32 counter = 0;
	xx_cjzzjf xxcjjfSt;
	do
	{
		Field *fields = result->Fetch();
		xxcjjfSt.id = fields[0].GetUInt32();
		xxcjjfSt.rewitem = fields[1].GetUInt32();
		xxcjjfSt.gonggao = fields[2].GetUInt32();
		m_xxcjzzjfmap.insert(xxcjzzjf::value_type(xxcjjfSt.id, xxcjjfSt));
		++counter;
	} while (result->NextRow());
	sLog->outString(">> Loaded %u xx_cjzzjf_update Data.", counter);
}

void ObjectMgr::LoadAllxxCoreData()
{
	sLog->outString("-----------------Loading XXCORE Setting-----------------");


	LoadxxCreatureTeleport();
	LoadxxItemb();
	LoadxxItemTeleport();
	LoadxxItemup();
	LoadxxBattleground();
	LoadPvpRankSystem();
	LoadMapidvalue();
	LoadMapididvalue();
	LoadFuyinData();
	LoadxxVipSystem();
	LoadxxVipSystemMr();
	LoadxxItembuff();
	LoadRaidSystem();
	LoadSuoyaoSystem();
	LoadSuoSystem();
	LoadSkillSystem();	
	LoadxxItem();
	LoadxxItemcj();
	LoadRaidBoxSystem();
	LoadxxItemicc();
	Loadxxnpc();
	LoadTongtianSystem();
	LoadTongSystem();
	LoadxxItemzh();
	LoadJntupoData();
	LoadJnjuexingData();
	LoadJnpeiyangData();
	LoadHuoliSystem();
	LoadYuyiData();
	Loadxxcjjf();
	Loadxxcjzjf();
}
