#include "stdafx.h"
#include "egg-fleet.h"
#include "egg-fleet-paths.h"
#include "egg-fleet-deathzones.h"

ModelInfo* EF_SKYMDLS;
ModelInfo* EF_CANNON1;
ModelInfo* EF_BULLETS;
ModelInfo* EF_PROPPLR;
ModelInfo* EF_BGSHIPS;

NJS_TEXLIST_ eggfleet_texlist = { arrayptrandlength(eggfleet_texname) };

void __cdecl EFBigFans(ObjectMaster* obj) {

}

void __cdecl EFCannon(ObjectMaster* obj) {

}

void __cdecl EFPlatforms(ObjectMaster* obj) {

}

void __cdecl EFPipeline(ObjectMaster* obj) {

}

void __cdecl EFShipDoor(ObjectMaster* obj) {

}

void __cdecl EFShipConveyor(ObjectMaster* obj) {

}

void __cdecl EFAntenna(ObjectMaster* obj) {

}

void __cdecl EFRailSign(ObjectMaster* obj) {

}

void __cdecl EFMissilePods(ObjectMaster* obj) {

}

void __cdecl EFHelice(ObjectMaster* obj) {

}

void __cdecl ECBarrier(ObjectMaster* obj) {

}

ObjectListEntry EggFleetObjectList_list[] = {
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 1360000, (ObjectFuncPtr)SpringA_Main },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 1360000, SpringB_Main },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1), ObjIndex_Stage, DistObj_UseDist, 1360000, DashPanel_Main },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Stage, DistObj_UseDist, 1360000, (ObjectFuncPtr)LongSpring_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, Omochao_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)SKULL },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1), ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)EmeraldPiece_Load },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1360000, GoalRing_Main },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)ORI },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 560000, CONTCHAO },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 1360000, DashHoop },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, ItemBoxBalloon },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 160000, ItemBox_Main },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)ROCKET },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)ROCKETMISSILE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_Default, 0, (ObjectFuncPtr)CHAOPIPE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_Default, 0, (ObjectFuncPtr)MINIMAL },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)E_GOLD},
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_Default, 0, Checkpoint_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)CWALL },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, RingGroup },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)SPHERE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCYL },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCUBE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, 0, nullptr }, //ottotto
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)HINTBOX },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, //rhino
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, //sweep
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Common, DistObj_UseDist, 2360000, DashRampAdjust },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 160000, ItemBoxAir_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Stationary },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Electric },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Attack },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, ItemBoxBalloon },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Stage, DistObj_UseDist, 1360000, (ObjectFuncPtr)LongSpring_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, // uni A
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, // uni B
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, // uni C
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Attack },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1000000, WoodenCrate_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1360000, ObjCannon },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, nullptr },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, OBJCASE },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1360000, (ObjectFuncPtr)UDREEL }, //45
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 4060000, EFBigFans },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1060000, EFCannon },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, EFPlatforms },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, EFPipeline },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2060000, EFShipDoor }, //50
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 5060000, EFShipConveyor },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2060000, EFAntenna },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2060000, EFRailSign },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, EFMissilePods },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, EFHelice }, //55
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, ECBarrier },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, e2000_Init },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 10000000, Flyer_Init },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1000000, Flyer_Trigger },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, Laserdoor }
};

ObjectListHead EggFleetObjectList = { arraylengthandptr(EggFleetObjectList_list) };

void EggFleet_SkyBox(ObjectMaster* obj) {
	NJS_VECTOR* position = &CameraScreenArray[CurrentScreen]->pos;

	njPushMatrix(0);
	njSetTexlist(CurrentLevelTexList);
	njTranslate(_nj_current_matrix_ptr_, position->x, position->y, position->z);
	njScalef(0.25f);
	DrawSA2BModel(EF_SKYMDLS->getmodel()->sa2bmodel);
	DrawSA2BModel(EF_SKYMDLS->getmodel()->child->sa2bmodel);
	njPopMatrix(1u);
}

void EggFleet_Main(ObjectMaster* obj) {
	
}

void EggFleet_Load() {
	CurrentHeroesLevel = HeroesLevelIDs::EggFleet;
	CommonLevelInit();
	
	LoadChunkFile("resource\\gd_pc\\s13_blk.bin");
	LoadLandTable("resource\\gd_pc\\s13.sa2lvl", LandTableFormat_SA2);
	LoadLevelTex((NJS_TEXLIST*)&eggfleet_texlist, "s13");
	LoadTXCFile("resource\\gd_pc\\s13.txc");

	LoadLevelLayout(&EggFleetObjectList, "s13_P1.bin", "s13_DB.bin");

	LoadStageLight("stg13_light.bin");
	LoadStagePaths(EggFleetPathList);
	LoadLevelMusic((char*)"eggfleet.adx");
	LoadDeathZones(EggFleetDeathZones);
	LoadFogData_Fogtask("stg13_fog.bin", (FogData*)0x1A280C8);
	
	LoadObject((LoadObj)0, "SKYBOX", EggFleet_SkyBox, 1)->DisplaySub = EggFleet_SkyBox;

	EF_SKYMDLS = LoadMDL("EF_SKYMDLS", ModelFormat_SA2B);
	EF_CANNON1 = LoadMDL("EF_CANNON1", ModelFormat_Chunk);
	EF_BULLETS = LoadMDL("EF_BULLETS", ModelFormat_Chunk);
	EF_PROPPLR = LoadMDL("EF_PROPPLR", ModelFormat_Chunk);
	EF_BGSHIPS = LoadMDL("EF_BGSHIPS", ModelFormat_Chunk);
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