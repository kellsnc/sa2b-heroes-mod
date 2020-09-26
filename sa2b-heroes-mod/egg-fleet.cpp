#include "stdafx.h"
#include "egg-fleet.h"

ModelInfo* EF_SKYMDLS;
ModelInfo* EF_CANNON1;
ModelInfo* EF_BULLETS;
ModelInfo* EF_PROPPLR;
ModelInfo* EF_BGSHIPS;

NJS_TEXNAME_ eggfleet_texname[]{
	{ "d_130001", 0, 0 },
	{ "d_130002", 0, 0 },
	{ "d_130003", 0, 0 },
	{ "d_130004", 0, 0 },
	{ "d_130005", 0, 0 },
	{ "d_130006", 0, 0 },
	{ "d_130007", 0, 0 },
	{ "d_130009", 0, 0 },
	{ "d_130010", 0, 0 },
	{ "d_130011", 0, 0 },
	{ "d_130012", 0, 0 },
	{ "d_130013", 0, 0 },
	{ "d_130014", 0, 0 },
	{ "d_130015", 0, 0 },
	{ "d_130016", 0, 0 },
	{ "d_130017", 0, 0 },
	{ "d_130018", 0, 0 },
	{ "d_130021", 0, 0 },
	{ "d_130022", 0, 0 },
	{ "d_130024", 0, 0 },
	{ "d_130025", 0, 0 },
	{ "d_130028", 0, 0 },
	{ "d_130029", 0, 0 },
	{ "d_130030", 0, 0 },
	{ "d_130031", 0, 0 },
	{ "d_130033", 0, 0 },
	{ "d_130036", 0, 0 },
	{ "d_130037", 0, 0 },
	{ "d_130038", 0, 0 },
	{ "d_130039", 0, 0 },
	{ "d_130042", 0, 0 },
	{ "d_130043", 0, 0 },
	{ "d_130044", 0, 0 },
	{ "d_130045", 0, 0 },
	{ "d_140020", 0, 0 },
	{ "ef_flash1", 0, 0 },
	{ "ef_flash4red", 0, 0 },
	{ "ef_smog4A", 0, 0 },
	{ "ef_smoke4wh", 0, 0 },
	{ "kumo64", 0, 0 },
	{ "kumo512", 0, 0 },
	{ "n1_1301", 0, 0 },
	{ "n1_1302", 0, 0 },
	{ "n1_1303", 0, 0 },
	{ "n1_1304", 0, 0 },
	{ "n1_1305", 0, 0 },
	{ "n1_1306", 0, 0 },
	{ "n1_1307", 0, 0 },
	{ "n1_1308", 0, 0 },
	{ "n1_1309", 0, 0 },
	{ "n1_1310", 0, 0 },
	{ "n1_1311", 0, 0 },
	{ "n1_1312", 0, 0 },
	{ "n1_1313", 0, 0 },
	{ "n1_1314", 0, 0 },
	{ "n1_1315", 0, 0 },
	{ "n1_1316", 0, 0 },
	{ "n1_1317", 0, 0 },
	{ "n1_1318", 0, 0 },
	{ "n1_1319", 0, 0 },
	{ "n1_1320", 0, 0 },
	{ "n1_1321", 0, 0 },
	{ "n1_1322", 0, 0 },
	{ "n1_1323", 0, 0 },
	{ "n1_1324", 0, 0 },
	{ "n1_1325", 0, 0 },
	{ "n1_1326", 0, 0 },
	{ "n1_1327", 0, 0 },
	{ "n1_1328", 0, 0 },
	{ "n1_1329", 0, 0 },
	{ "n1_1330", 0, 0 },
	{ "n1_1331", 0, 0 },
	{ "n1_1332", 0, 0 },
	{ "n1_1333", 0, 0 },
	{ "n1_1334", 0, 0 },
	{ "n1_1335", 0, 0 },
	{ "n1_1336", 0, 0 },
	{ "n1_1337", 0, 0 },
	{ "n1_1338", 0, 0 },
	{ "n1_1339", 0, 0 },
	{ "n1_1340", 0, 0 },
	{ "n1_1341", 0, 0 },
	{ "n1_1342", 0, 0 },
	{ "n13_a1.1", 0, 0 },
	{ "n13_a1.2", 0, 0 },
	{ "n13_a1.3", 0, 0 },
	{ "n13_a1.4", 0, 0 },
	{ "n13_a1.5", 0, 0 },
	{ "n13_a1.6", 0, 0 },
	{ "n13_a1.7", 0, 0 },
	{ "n13_a1.8", 0, 0 },
	{ "pn_1301", 0, 0 },
	{ "pn_1302", 0, 0 },
	{ "pn_1303", 0, 0 },
	{ "stg07_exproA", 0, 0 },
	{ "tn_1301", 0, 0 },
};

NJS_TEXLIST_ eggfleet_texlist = { arrayptrandlength(eggfleet_texname) };

ObjectListEntry EggFleetObjectList_list[] = {
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Stage, 0x10, 1060000, nullptr }
};

ObjectListHead EggFleetObjectList = { arraylengthandptrT(EggFleetObjectList_list, int) };

void EggFleet_SkyBox(ObjectMaster* obj) {
	NJS_VECTOR* position = &CameraPosArray[CurrentScreen * 2];

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslate(_nj_current_matrix_ptr_, position->x, 0.0f, position->z);
	DrawModel(EF_SKYMDLS->getmodel()->basicmodel);
	DrawModel(EF_SKYMDLS->getmodel()->child->basicmodel);
	njPopMatrix(1u);
}

void EggFleet_Main(ObjectMaster* obj) {
	obj->Data1.Entity->Position = MainCharObj1[0]->Position;

	if (obj->Data1.Entity->Action == 0) {
		LoadObject((LoadObj)0, "SKYBOX", EggFleet_SkyBox, 1)->DisplaySub = EggFleet_SkyBox;
		obj->Data1.Entity->Action = 1;
	}
}

void EggFleet_Load() {
	CurrentHeroesLevel = HeroesLevelIDs::EggFleet;
	CommonLevelInit();
	
	LoadChunkFile("resource\\gd_pc\\s13_blk.bin");
	LoadLandTable("resource\\gd_pc\\s13.sa2lvl");
	LoadLevelTex((NJS_TEXLIST*)&eggfleet_texlist, "s13");
	LoadTXCFile("resource\\gd_pc\\s13.txc");

	for (uint8_t i = 0; i < LengthOfArray(EggFleetObjectList_list); ++i) {
		CityEscape_ObjectArray[i] = EggFleetObjectList_list[i];
	}

	void* setfile = LoadSETFile(2048, (char*)"egg-fleet-set.bin", (char*)"dummy-set.bin");

	LoadSetObject(&CityEscape_ObjectList, setfile);
	LoadStageLight("stg13_light.bin");
	LoadStagePaths(EggFleetPathList);
	LoadLevelMusic((char*)"eggfleet.adx");
	LoadDeathZones(EggFleetDeathZones);
	LoadFogData_Fogtask("stg13_fog.bin", (FogData*)0x1A280C8);
	LoadTextures(CommonTextureInfoPtr);
	EF_SKYMDLS = LoadMDL("EF_SKYMDLS");
	EF_CANNON1 = LoadMDL("EF_CANNON1");
	EF_BULLETS = LoadMDL("EF_BULLETS");
	EF_PROPPLR = LoadMDL("EF_PROPPLR");
	EF_BGSHIPS = LoadMDL("EF_BGSHIPS");
}

void EggFleetDelete() {
	FreeMDL(EF_SKYMDLS);
	FreeMDL(EF_CANNON1);
	FreeMDL(EF_BULLETS);
	FreeMDL(EF_PROPPLR);
	FreeMDL(EF_BGSHIPS);

	CommonLevelDelete();
}

void EggFleet_Init(const char* path, const HelperFunctions& helperFunctions) {
	FinalRushHeader.Init = EggFleet_Load;
	FinalRushHeader.subprgmanager = EggFleet_Main;
	FinalRushHeader.anonymous_2 = EggFleetDelete;
	SetStartEndPoints(helperFunctions, &ef_startpos, &ef_2pintro, &ef_endpos, &ef_endpos23);
}