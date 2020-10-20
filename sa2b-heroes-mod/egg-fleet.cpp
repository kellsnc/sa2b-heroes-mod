#include "stdafx.h"
#include "egg-fleet.h"
#include "egg-fleet-paths.h"
#include "egg-fleet-deathzones.h"

ModelInfo* EF_SKYMDLS;
ModelInfo* EF_PROPPLR;
ModelInfo* EF_EHELICE;
ModelInfo* EF_EBIGFAN;
ModelInfo* EF_EBIGFANCOL;

NJS_TEXLIST_ eggfleet_texlist = { arrayptrandlength(eggfleet_texname) };

bool Fans_IsSpecificPlayerInCylinder(EntityData1* entity, NJS_VECTOR* center, float radius, float height);

void __cdecl EFBigFan_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	njSetTexlist(CurrentLevelTexList);
	njPushMatrix(0);
	njTranslateEx(&data->Position);
	njRotateY_(data->Rotation.y);
	DrawSA2BModel(model->sa2bmodel);

	njPopMatrix(0);
	njRotateY_(data->Scale.z);
	DrawSA2BModel(model->child->sa2bmodel);
	njPopMatrix(1);

	DrawSA2BModel(model->child->child->sa2bmodel);
	njPopMatrix(1u);
}

void EFBigFan_DisplayAlpha(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	njSetTexlist(CurrentLevelTexList);
	njPushMatrix(0);
	njTranslateEx(&data->Position);
	njRotateY_(data->Rotation.y);
	DrawSA2BModel(model->child->child->sa2bmodel);
	njPopMatrix(1u);
}

void __cdecl EFBigFan_Main(ObjectMaster* obj) {
	if (ClipSetObject(obj)) {
		EntityData1* data = obj->Data1.Entity;

		if (MainCharObj1[0]) {
			if (Fans_IsSpecificPlayerInCylinder(MainCharObj1[0], &data->Position, 130.0f, data->Scale.x)) {
				data->Index = 20;
			}

			if (data->Index != 0) {
				MainCharObj2[0]->Speed.y = 0.25f;
				MainCharObj1[0]->Status |= 0x1000;
				MainCharObj1[0]->NextAction = 8;
				MainCharObj1[0]->Position.y += 1.0f;
				data->Index -= 1;
			}
		}

		if (MainCharObj1[1]) {
			if (Fans_IsSpecificPlayerInCylinder(MainCharObj1[1], &data->Position, 130.0f, data->Scale.x)) {
				data->field_2 = 20;
			}
			else {
				data->field_2 = 0;
			}

			if (data->field_2 != 0) {
				MainCharObj2[1]->Speed.y = 0.25f;
				MainCharObj1[1]->Status |= 0x1000;
				MainCharObj1[1]->NextAction = 8;
				MainCharObj1[1]->Position.y += 1.0f;
				data->field_2 -= 1;
			}
		}

		data->Scale.z -= data->Scale.x * 80.0f;
	}
}

void __cdecl EFBigFan(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (data->Scale.y != 1) {
		obj->MainSub = ObjFan;
		data->Scale.y = data->Scale.x * 80.0f;
		return;
	}

	obj->DeleteSub = ObjectFunc_DynColDelete;
	obj->MainSub = EFBigFan_Main;
	obj->DisplaySub = EFBigFan_Display;
	obj->field_1C = EFBigFan_DisplayAlpha;

	Play3DSound_EntityPosBank(obj->Data1.Entity, 7, &obj->Data1.Entity->Position, 50, 5);

	NJS_OBJECT* dynobj = GetFreeDynObject();

	memcpy(dynobj, EF_EBIGFANCOL->getmodel(), sizeof(NJS_OBJECT));

	dynobj->pos[0] = data->Position.x;
	dynobj->pos[1] = data->Position.y;
	dynobj->pos[2] = data->Position.z;
	dynobj->ang[1] = data->Rotation.y;
	dynobj->evalflags = 0xFFFFFFF8;

	DynCol_Add(0x1, obj, dynobj);

	obj->EntityData2 = (UnknownData2*)dynobj;
	obj->field_4C = EF_EBIGFAN->getmodel();
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

void __cdecl EFHelice_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	njSetTexlist(CurrentLevelTexList);
	njPushMatrix(0);
	njTranslateEx(&data->Position);
	njRotateY_(data->Rotation.y);
	njRotateX_(data->Rotation.x);
	DrawSA2BModel(model->sa2bmodel);
	njRotateZ_(data->Scale.z);
	DrawSA2BModel(model->child->sa2bmodel);
	DrawSA2BModel(model->child->child->sa2bmodel);
	njPopMatrix(1u);
}

void __cdecl EFHelice_Main(ObjectMaster* obj) {
	if (ClipSetObject(obj)) {
		EntityData1* data = obj->Data1.Entity;

		data->Scale.z -= 1200.0f;
	}
}

void __cdecl EFHelice(ObjectMaster* obj) {
	obj->MainSub = EFHelice_Main;
	obj->DisplaySub = EFHelice_Display;
	
	Play3DSound_EntityPosBank(obj->Data1.Entity, 7, &obj->Data1.Entity->Position, 70, 5);

	obj->field_4C = EF_EHELICE->getmodel();
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
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 4060000, EFBigFan },
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
	LoadStageSounds("se_ac_gf.mlt", (void*)0x8A0F60);
	
	LoadObject((LoadObj)0, "SKYBOX", EggFleet_SkyBox, 1)->DisplaySub = EggFleet_SkyBox;

	EF_SKYMDLS = LoadMDL("EF_SKYMDLS", ModelFormat_SA2B);
	EF_PROPPLR = LoadMDL("EF_PROPPLR", ModelFormat_SA2B);
	EF_EHELICE = LoadMDL("EF_EHELICE", ModelFormat_SA2B);
	EF_EBIGFAN = LoadMDL("EF_EBIGFAN", ModelFormat_SA2B);
	EF_EBIGFANCOL = LoadMDL("EF_EBIGFAN", ModelFormat_Basic);

	SetPropellerModel(EF_PROPPLR->getmodel());
}

void EggFleetDelete() {
	FreeMDL(EF_SKYMDLS);
	FreeMDL(EF_PROPPLR);
	FreeMDL(EF_EHELICE);
	FreeMDL(EF_EBIGFAN);
	FreeMDL(EF_EBIGFANCOL);

	CommonLevelDelete();
}

void EggFleet_Init(const char* path, const HelperFunctions& helperFunctions) {
	FinalRushHeader.Init = EggFleet_Load;
	FinalRushHeader.subprgmanager = EggFleet_Main;
	FinalRushHeader.anonymous_2 = EggFleetDelete;
	SetStartEndPoints(helperFunctions, &ef_startpos, &ef_2pintro, &ef_endpos, &ef_endpos23);
}