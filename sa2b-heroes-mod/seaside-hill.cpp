#include "stdafx.h"
#include "seaside-hill-deathzones.h"
#include "seaside-hill-paths.h"
#include "seaside-hill.h"

ModelInfo * SH_PLATFOR;
ModelInfo * SH_MORUINS;
ModelInfo * SH_POLFLAG;
ModelInfo * SH_WATERFS;
ModelInfo * SH_FLOWERS;
ModelInfo * SH_BRBLOCK;

NJS_TEXLIST_ seasidehill_texlist = { arrayptrandlength(seasidehill_texname) };

static int ruin = 0;
static int flagtimer = 0;

void SHFlowers_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrix(1u);
}

void SHFlowers(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	obj->field_4C = (UnknownData2*)GetSiblingModelByIndex(SH_FLOWERS->getmodel()->child, static_cast<int>(data->Scale.x));

	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = SHFlowers_Display;
}

void SHWaterfallLarge_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->EntityData2;

	RenderInfo->CurrentTexlist = (NJS_TEXLIST*)&HeroesWater_TexList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.x);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrix(1u);
}

void SHWaterfallLarge(ObjectMaster* obj) {
	NJS_OBJECT* model = SH_WATERFS->getmodel()->child->child->child;
	obj->EntityData2 = (UnknownData2*)model;
	model->sa2bmodel->Radius = 100000.0f;

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = SHWaterfallLarge_Display;
}

void SHWaterfallSmall_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->EntityData2;

	RenderInfo->CurrentTexlist = (NJS_TEXLIST*)&HeroesWater_TexList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawSA2BModel(model->sa2bmodel);
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
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njScalef(data->Scale.z);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawSA2BModel(model->sa2bmodel);
	njRotateY(_nj_current_matrix_ptr_, data->Scale.y + (-0x500 + (0x1000 * (1 - (sin(GetTimer()) / 10)))));
	DrawSA2BModel(model->child->sa2bmodel);
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

	obj->field_4C = (UnknownData2*)SH_POLFLAG->getmodel();

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = SHFlag_Main;
	obj->DisplaySub = SHFlag_Display;
}

void SHMovingPltfrms_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;

	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);

	DrawSA2BModel(model->child->sa2bmodel);
	DrawSA2BModel(model->child->child->sa2bmodel);

	if (model->child->child->child) {
		DrawSA2BModel(model->child->child->child->sa2bmodel);
	}

	if (data->field_2 == 1) {
		RenderInfo->CurrentTexlist = (NJS_TEXLIST*)&HeroesWater_TexList;

		DrawSA2BModel(model->child->sibling->sa2bmodel);
	}
	
	njPopMatrix(1u);
}

void SHMovingPltfrms_Main(ObjectMaster* obj) {
	if (ClipSetObject(obj)) {
		EntityData1* entity = obj->Data1.Entity;

		entity->field_2 = 0;

		if (ruin != 0 && ruin == static_cast<int>(entity->Scale.y)) {
			if (entity->Position.y != entity->Scale.z) {
				if (entity->Scale.x >= entity->Scale.z) {
					if (entity->Position.y <= entity->Scale.z) {
						entity->Position.y = entity->Scale.z;
					}
					else if (entity->Position.y > entity->Scale.z) {
						entity->Position.y -= 2;
					}

					if (entity->Position.y == entity->Scale.x - 2) {
						PlaySoundProbably(13, 0, 0, 0);
					}
				}
				else if (entity->Scale.x <= entity->Scale.z) {
					if (entity->Position.y >= entity->Scale.z) {
						entity->Position.y = entity->Scale.z;
					}
					else if (entity->Position.y < entity->Scale.z) {
						entity->Position.y += 2;
						entity->field_2 = 1;
					}

					if (entity->Position.y == entity->Scale.x + 2) {
						PlaySoundProbably(13, 0, 0, 0);
					}

					if (entity->Position.y <= entity->Scale.z - 1 && entity->Position.y >= entity->Scale.z - 3) {
						PlaySoundProbably(13, 0, 0, 0);
					}
				}
			}
		}

		AddToCollisionList(obj);
	}
}

void SHMovingPltfrms(ObjectMaster* obj) {
	EntityData1* entity = obj->Data1.Entity;
	Uint8 id = static_cast<Uint8>(entity->Scale.x);

	obj->field_4C = GetSiblingModelByIndex(SH_MORUINS->getmodel()->child, id);

	switch (id) {
	case 0:
		InitCollision(obj, Col_MvPltfrm1, 3, 4);
		break;
	case 1:
		InitCollision(obj, &Col_MvPltfrm2, 1, 4);
		break;
	case 2:
		InitCollision(obj, &Col_MvPltfrm3, 1, 4);
		break;
	}

	entity->Scale.x = entity->Position.y;

	obj->MainSub = SHMovingPltfrms_Main;
	obj->DisplaySub = SHMovingPltfrms_Display;
}

void SHRuinTrigger(ObjectMaster* obj) {
	if (ClipSetObject(obj)) {
		EntityData1* data = obj->Data1.Entity;

		if (ruin != data->Scale.x) {
			if (IsPlayerInsideSphere(&data->Position, data->Scale.y * 3)) {
				ruin = static_cast<int>(data->Scale.x);
			}
		}
	}
}

void SHPlatforms_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScale(data->Scale.x, data->Scale.y, data->Scale.z);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrix(1u);
}

void SHPlatforms(ObjectMaster* obj)
{
	InitCollision(obj, &Col_Platform, 1, 4);

	obj->field_4C = SH_PLATFOR->getmodel();

	obj->MainSub = MainSub_Collision;
	obj->DisplaySub = SHPlatforms_Display;
}

void SHBreakableBlock_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateZ(_nj_current_matrix_ptr_, data->Rotation.z);
	njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawSA2BModel(model->child->sa2bmodel);
	njPopMatrix(1u);
}

void SHBreakableBlock_Main(ObjectMaster* obj) {
	if (ClipSetObject(obj)) {
		EntityData1* entity = obj->Data1.Entity;
		ObjectMaster* player = GetCollidingPlayer(obj);

		if (player && player->Data1.Entity->Status & Status_Attack && player->Data1.Entity->Position.y < entity->Position.y + 30) {
			NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;
			model = model->child->sibling->child;

			LoadBreaker(&entity->Position, &entity->Rotation, model, 0.0f, 15.0f, 0.0f, 60);
			PlaySoundProbably(4112, 0, 1, 127);
			UpdateSetDateAndDelete(obj);
		}

		AddToCollisionList(obj);
	}
}

void SHBreakableBlock(ObjectMaster* obj) {
	EntityData1* entity = obj->Data1.Entity;

	obj->field_4C = (ObjectFuncPtr)SH_BRBLOCK->getmodel();

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = SHBreakableBlock_Main;
	obj->DisplaySub = SHBreakableBlock_Display;

	InitCollision(obj, &Col_BreakBlock, 1, 4);

	entity->Collision->CollisionArray[0].field_24 = entity->Rotation.x;
	entity->Collision->CollisionArray[0].field_2C = entity->Rotation.z;
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
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 6460000, SHWaterfallLarge },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, SHWaterfallSmall },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, SHFlag },
	{ (LoadObj)0 }, // large bird
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Common, DistObj_UseDist, 2360000, (ObjectFuncPtr)DashRamp_Main },
	{ (LoadObj)0 }, // seagull
	{ (LoadObj)0 }, // whale
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, SHBreakableBlock }, // 43
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
	AnimateTexlist(&HeroesWater_TexList, 2, (Uint32*)&obj->Data1.Entity->Scale.x, (void**)&obj->field_4C);
}

void SeasideHill_Load() {
	CurrentHeroesLevel = HeroesLevelIDs::SeasideHill;

	CommonLevelInit();

	LoadChunkFile("resource\\gd_pc\\s01_blk.bin");
	LoadLandTable("resource\\gd_pc\\s01.sa2lvl", LandTableFormat_SA2);
	LoadLevelTex((NJS_TEXLIST*)&seasidehill_texlist, "s01");
	LoadTXCFile("resource\\gd_pc\\s01.txc");
	
	LoadLevelLayout(&SeasideHillObjectList, "s01_P1.bin", "s01_DB.bin");

	LoadStageLight("stg13_light.bin");
	LoadLevelMusic((char*)"seasidehill.adx");
	LoadStagePaths(SeasideHillPathList);
	LoadDeathZones(SeasideHillDeathZones);
	LoadFogData_Fogtask("stg13_fog.bin", (FogData*)0x1A280C8);

	LoadTextureList("s01w", (NJS_TEXLIST*)&HeroesWater_TexList);
	
	SH_FLOWERS = LoadMDL("SH_FLOWERS", ModelFormat_SA2B);
	SH_WATERFS = LoadMDL("SH_WATERFS", ModelFormat_SA2B);
	SH_POLFLAG = LoadMDL("SH_POLFLAG", ModelFormat_SA2B);
	SH_MORUINS = LoadMDL("SH_MORUINS", ModelFormat_SA2B);
	SH_PLATFOR = LoadMDL("SH_PLATFOR", ModelFormat_SA2B);
	SH_BRBLOCK = LoadMDL("SH_BRBLOCK", ModelFormat_SA2B);
}

void SeasideHill_Delete() {
	FreeMDL(SH_MORUINS);
	FreeMDL(SH_FLOWERS);
	FreeMDL(SH_WATERFS);
	FreeMDL(SH_POLFLAG);
	FreeMDL(SH_PLATFOR);
	FreeMDL(SH_BRBLOCK);

	FreeTexList((NJS_TEXLIST*)&HeroesWater_TexList);
	CommonLevelDelete();
}

void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions) {
	CityEscapeHeader.Init = SeasideHill_Load;
	CityEscapeHeader.subprgmanager = SeasideHill_Main;
	CityEscapeHeader.anonymous_2 = SeasideHill_Delete;
	SetStartEndPoints(helperFunctions, &sh_startpos, &sh_2pintro, &sh_endpos, &sh_endpos23);
}