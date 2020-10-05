#include "stdafx.h"
#include "seaside-hill-deathzones.h"
#include "seaside-hill-paths.h"
#include "seaside-hill.h"

ModelInfo * SH_PLATFOR;
ModelInfo * SH_MORUINS;
ModelInfo * SH_POLFLAG;
ModelInfo * SH_WATERFS;
ModelInfo * SH_FLOWERS;

NJS_TEXNAME_ seasidehill_texname[] {
	{ "k1_flo2", 0, 0 },
	{ "k1_kab01", 0, 0 },
	{ "k1_kab03", 0, 0 },
	{ "k1_kab11", 0, 0 },
	{ "k1_kab12", 0, 0 },
	{ "k1_kuj01", 0, 0 },
	{ "k1_kuj11", 0, 0 },
	{ "k1_kuj12", 0, 0 },
	{ "k1_m_k01", 0, 0 },
	{ "k1_mit01", 0, 0 },
	{ "k1_mit11", 0, 0 },
	{ "k1_rop01", 0, 0 },
	{ "k1_rop02", 0, 0 },
	{ "k1_sna01", 0, 0 },
	{ "k1_sna02", 0, 0 },
	{ "k1_sna03", 0, 0 },
	{ "k1_sra02", 0, 0 },
	{ "k1_sya01", 0, 0 },
	{ "k1_sya02", 0, 0 },
	{ "k1_sya03", 0, 0 },
	{ "k1_tika1", 0, 0 },
	{ "k1_tika1_", 0, 0 },
	{ "k1_tika2", 0, 0 },
	{ "k1_tika2_", 0, 0 },
	{ "k1_u1.1", 0, 0 },
	{ "k1_u1.2", 0, 0 },
	{ "k1_u1.3", 0, 0 },
	{ "k1_u1.4", 0, 0 },
	{ "k1_u1.5", 0, 0 },
	{ "k1_u1.6", 0, 0 },
	{ "k1_u1.7", 0, 0 },
	{ "k1_u1.8", 0, 0 },
	{ "k1_u1.9", 0, 0 },
	{ "k1_u1.10", 0, 0 },
	{ "k1_u1.11", 0, 0 },
	{ "k1_u1.12", 0, 0 },
	{ "k1_u1.13", 0, 0 },
	{ "k1_u1.14", 0, 0 },
	{ "k1_u1.15", 0, 0 },
	{ "k1_u1.16", 0, 0 },
	{ "k1_u1.17", 0, 0 },
	{ "k1_u1.18", 0, 0 },
	{ "k1_u1.19", 0, 0 },
	{ "k1_u1.20", 0, 0 },
	{ "k1_umi02", 0, 0 },
	{ "k1_umi03", 0, 0 },
	{ "k1_umi11", 0, 0 },
	{ "k1_umi13", 0, 0 },
	{ "k1_umi14", 0, 0 },
	{ "k1_yasi1", 0, 0 },
	{ "m1_1001", 0, 0 },
	{ "m1_1002", 0, 0 },
	{ "m1_1003", 0, 0 },
	{ "m1_1004", 0, 0 },
	{ "m1_1005", 0, 0 },
	{ "m1_1006", 0, 0 },
	{ "m1_1007", 0, 0 },
	{ "m1_1008", 0, 0 },
	{ "m1_1009", 0, 0 },
	{ "m1_1010", 0, 0 },
	{ "m1_1011", 0, 0 },
	{ "m1_1012", 0, 0 },
	{ "m1_2001", 0, 0 },
	{ "m1_2004", 0, 0 },
	{ "m1_2005", 0, 0 },
	{ "m1_2006", 0, 0 },
	{ "m1_2008", 0, 0 },
	{ "m1_2011", 0, 0 },
	{ "m1_2012", 0, 0 },
	{ "m1_2013", 0, 0 },
	{ "m1_5002", 0, 0 },
	{ "pk1_flo1", 0, 0 },
	{ "pk1_flo3", 0, 0 },
	{ "pk1_flo4", 0, 0 },
	{ "pk1_flo5", 0, 0 },
	{ "pk1_flo6", 0, 0 },
	{ "pk1_flo7", 0, 0 },
	{ "pk1_hika", 0, 0 },
	{ "pk1_par1", 0, 0 },
	{ "pk1_yas2", 0, 0 },
	{ "pk1_yas3", 0, 0 },
	{ "pkb1_hta", 0, 0 },
	{ "tk1_mizu", 0, 0 },
	{ "tk1_nam1", 0, 0 },
};

NJS_TEXLIST_ seasidehill_texlist = { arrayptrandlength(seasidehill_texname) };

float ruin = 0;
static int flagtimer = 0;

void SHFlowers_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->EntityData2;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawModel(model->basicmodel);
	njPopMatrix(1u);
}

void SHFlowers(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	obj->EntityData2 = (UnknownData2*)GetChildModelByIndex(SH_FLOWERS->getmodel(), data->Scale.x);

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = SHFlowers_Display;
}

void SHWaterfallLarge_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->EntityData2;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.x);
	DrawModel(model->basicmodel);
	njPopMatrix(1u);
}

void SHWaterfallLarge(ObjectMaster* obj) {
	obj->EntityData2 = (UnknownData2*)SH_WATERFS->getmodel()->child->child->child;

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = SHWaterfallLarge_Display;
}

void SHWaterfallSmall_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->EntityData2;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawModel(model->basicmodel);
	njPopMatrix(1u);
}

void SHWaterfallSmall(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	obj->EntityData2 = (UnknownData2*)GetChildModelByIndex(SH_WATERFS->getmodel(), data->Scale.x);

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = SHWaterfallSmall_Display;
}

void SHFlag_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njScalef(data->Scale.z);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawModel(SH_POLFLAG->getmodel()->basicmodel);
	njRotateY(_nj_current_matrix_ptr_, data->Scale.y + (-0x500 + (0x1000 * (1 - (sin(GetTimer()) / 10)))));
	DrawModel(SH_POLFLAG->getmodel()->child->basicmodel);
	njPopMatrix(1u);
}

void SHFlag_Main(ObjectMaster* obj) {
	if (ClipSetObject(obj)) {
		AddToCollisionList(obj);
	}
}

void SHFlag(ObjectMaster* obj)
{
	InitCollision(obj, &Col_Pole, 1, 4);

	obj->EntityData2 = (UnknownData2*)SH_POLFLAG->getmodel();

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = SHFlag_Main;
	obj->DisplaySub = SHFlag_Display;
}

void SHMovingPltfrms_Display(ObjectMaster* a1) {
	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &a1->Data1.Entity->Position);
	njRotateY(_nj_current_matrix_ptr_, a1->Data1.Entity->Rotation.y);

	switch (a1->Data1.Entity->Action) {
	case 0:
		DrawModel(SH_MORUINS->getmodel()->basicmodel);
		break;
	case 1:
		DrawModel(SH_MORUINS->getmodel()->child->basicmodel);
		break;
	case 2:
		DrawModel(SH_MORUINS->getmodel()->child->child->basicmodel);
		break;
	}

	njPopMatrix(1u);
}

void SHMovingPltfrms_Main(ObjectMaster* a1) {
	if (ClipSetObject(a1)) {
		EntityData1* entity = a1->Data1.Entity;

		if (ruin != 0 && ruin == entity->Scale.y) {
			if (entity->Position.y != entity->Scale.z) {
				if (entity->Scale.x >= entity->Scale.z) {
					if (entity->Position.y <= entity->Scale.z) {
						entity->Position.y = entity->Scale.z;
					}
					else if (entity->Position.y > entity->Scale.z) entity->Position.y -= 2;

					if (entity->Position.y == entity->Scale.x - 2) PlaySoundProbably(13, 0, 0, 0);
				}
				else if (entity->Scale.x <= entity->Scale.z) {
					if (entity->Position.y >= entity->Scale.z) {
						entity->Position.y = entity->Scale.z;
					}
					else if (entity->Position.y < entity->Scale.z) entity->Position.y += 2;

					if (entity->Position.y == entity->Scale.x + 2) PlaySoundProbably(13, 0, 0, 0);
					if (entity->Position.y <= entity->Scale.z - 1 && entity->Position.y >= entity->Scale.z - 3) PlaySoundProbably(13, 0, 0, 0);
				}
			}
		}

		AddToCollisionList(a1);
	}
}

void SHMovingPltfrms(ObjectMaster* a1)
{
	EntityData1* entity = a1->Data1.Entity;

	entity->Action = entity->Scale.x;
	entity->Scale.x = entity->Position.y;

	switch (entity->Action) {
	case 0:
		InitCollision(a1, Col_MvPltfrm1, 3, 4);
		break;
	case 1:
		InitCollision(a1, Col_MvPltfrm2, 1, 4);
		break;
	case 2:
		InitCollision(a1, &Col_MvPltfrm3, 1, 4);
		break;
	}

	a1->MainSub = &SHMovingPltfrms_Main;
	a1->DisplaySub = &SHMovingPltfrms_Display;
}

void SHRuinTrigger(ObjectMaster* a1)
{
	if (ClipSetObject(a1)) {
		if (ruin != a1->Data1.Entity->Scale.x) {
			if (IsPlayerInsideSphere(&a1->Data1.Entity->Position, a1->Data1.Entity->Scale.y * 3)) {
				ruin = a1->Data1.Entity->Scale.x;
			}
		}
	}
}

void SHPlatforms_Display(ObjectMaster* a1) {
	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &a1->Data1.Entity->Position);
	njRotateY(_nj_current_matrix_ptr_, a1->Data1.Entity->Rotation.y);
	njScale(a1->Data1.Entity->Scale.x, a1->Data1.Entity->Scale.y, a1->Data1.Entity->Scale.z);
	DrawModel(SH_PLATFOR->getmodel()->basicmodel);
	njPopMatrix(1u);
}

void SHPlatforms_Main(ObjectMaster* a1)
{
	if (ClipSetObject(a1)) {
		AddToCollisionList(a1);
	}
}

void SHPlatforms(ObjectMaster* a1)
{
	InitCollision(a1, &Col_Platform, 1, 4);

	a1->MainSub = &SHPlatforms_Main;
	a1->DisplaySub = &SHPlatforms_Display;
}

ObjectListEntry SeasideHillObjectList_list[] = {
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
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 4000000, (ObjectFuncPtr)KDITEMBOX },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_Default, 0, Checkpoint_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)CWALL },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)RingLinearMain },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)RingCircleMain },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCYL },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCUBE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)SPHERE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)HINTBOX },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 40000, (ObjectFuncPtr)IRONBALL2 },
	{ LoadObj_Data1, ObjIndex_4, DistObj_UseDist, 40000, (ObjectFuncPtr)IRONBALL2 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 160000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)E_GOLD },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, SHMovingPltfrms },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 160000, SHRuinTrigger },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, SHPlatforms },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, SHFlowers },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, SHWaterfallLarge },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, SHWaterfallSmall },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, SHFlag },
	{ (LoadObj)0 }, // large bird
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Common, DistObj_UseDist, 2360000, (ObjectFuncPtr)DashRamp_Main },
	{ (LoadObj)0 }, // seagull
	{ (LoadObj)0 }, // whale
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Big_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, WoodenCrate_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, IronCrate_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, (ObjectFuncPtr)IronEggmanCrate },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, SOLIDBOX },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 160000, (ObjectFuncPtr)KDITEMBOX },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, Beetle_Attack },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, Beetle_Attack },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 250000, Beetle_Attack },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 250000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)E_GOLD},
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Stationary },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Electric },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Attack },
};

ObjectListHead SeasideHillObjectList = { arraylengthandptr(SeasideHillObjectList_list) };

void SeasideHill_Main(ObjectMaster* obj) {
	
}

void SeasideHill_Load() {
	CurrentHeroesLevel = HeroesLevelIDs::SeasideHill;

	CommonLevelInit();

	LoadChunkFile("resource\\gd_pc\\s01_blk.bin");
	LoadLandTable("resource\\gd_pc\\s01.sa2lvl");
	LoadLevelTex((NJS_TEXLIST*)&seasidehill_texlist, "s01");
	LoadTXCFile("resource\\gd_pc\\s01.txc");
	
	LoadLevelLayout(&SeasideHillObjectList, "s01_P1.bin", "s01_DB.bin");

	LoadStageLight("stg13_light.bin");
	LoadLevelMusic((char*)"seasidehill.adx");
	LoadStagePaths(SeasideHillPathList);
	LoadDeathZones(SeasideHillDeathZones);
	LoadFogData_Fogtask("stg13_fog.bin", (FogData*)0x1A280C8);
	
	SH_FLOWERS = LoadMDL("SH_FLOWERS");
	SH_WATERFS = LoadMDL("SH_WATERFS");
	SH_POLFLAG = LoadMDL("SH_POLFLAG");
	SH_MORUINS = LoadMDL("SH_MORUINS");
	SH_PLATFOR = LoadMDL("SH_PLATFOR");
}

void SeasideHill_Delete() {
	FreeMDL(SH_MORUINS);
	FreeMDL(SH_FLOWERS);
	FreeMDL(SH_WATERFS);
	FreeMDL(SH_POLFLAG);
	FreeMDL(SH_PLATFOR);

	CommonLevelDelete();
}

void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions) {
	CityEscapeHeader.Init = SeasideHill_Load;
	CityEscapeHeader.subprgmanager = SeasideHill_Main;
	CityEscapeHeader.anonymous_2 = SeasideHill_Delete;
	SetStartEndPoints(helperFunctions, &sh_startpos, &sh_2pintro, &sh_endpos, &sh_endpos23);
}