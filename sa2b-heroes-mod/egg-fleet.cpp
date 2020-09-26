#include "stdafx.h"
#include "egg-fleet.h"

ModelInfo* EF_SKYMDLS;
ModelInfo* EF_CANNON1;
ModelInfo* EF_BULLETS;
ModelInfo* EF_PROPPLR;
ModelInfo* EF_BGSHIPS;

NJS_TEXNAME eggfleet_texname[96];
NJS_TEXLIST eggfleet_texlist{ arrayptrandlength(eggfleet_texname) };

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
	EntityData1* data = obj->Data1.Entity;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslate(_nj_current_matrix_ptr_, data->Position.x, 1.8f, data->Position.z);
	njScale(0.1f, 0.1f, 0.1f);
	DrawModel(EF_SKYMDLS->getmodel()->basicmodel);
	DrawModel(EF_SKYMDLS->getmodel()->child->basicmodel);
	njPopMatrix(1u);
}

void EggFleet_Main(ObjectMaster* obj) {
	AnimateTextures(arrayptrandlength(EggFleetAnimTexs));

	obj->Data1.Entity->Position = MainCharObj1[0]->Position;

	if (obj->Data1.Entity->Action == 0) {
		obj->DisplaySub = EggFleet_SkyBox;
		obj->Data1.Entity->Action = 1;
	}
}

void EggFleet_Load() {
	CommonLevelInit();

	CurrentLevelTexList = CurrentLandTable->TextureList;

	for (uint8_t i = 0; i < LengthOfArray(EggFleetObjectList_list); ++i) {
		CityEscape_ObjectArray[i] = EggFleetObjectList_list[i];
	}

	void* setfile = LoadSETFile(2048, (char*)"final-rush-set.bin", (char*)"dummy-set.bin");

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