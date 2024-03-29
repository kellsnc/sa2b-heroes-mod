#include "stdafx.h"
#include "seaside-hill-deathzones.h"
#include "seaside-hill-paths.h"
#include "seaside-hill.h"

static ModelInfo * SH_PLATFOR;
static ModelInfo * SH_MORUINS;
static ModelInfo * SH_POLFLAG;
static ModelInfo * SH_WATERFS;
static ModelInfo * SH_FLOWERS;
static ModelInfo * SH_BRBLOCK;

static NJS_TEXLIST_ seasidehill_texlist = { arrayptrandlength(seasidehill_texname) };

static int ruin = 0;
static int flagtimer = 0;

static void __cdecl SHFlowers_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLandTable->TextureList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl SHFlowers(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	obj->field_4C = reinterpret_cast<void*>(GetSiblingModelByIndex(SH_FLOWERS->getmodel()->child, static_cast<int>(data->Scale.x)));

	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = SHFlowers_Display;
}

static void __cdecl SHWaterfallLarge_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(reinterpret_cast<NJS_TEXLIST*>(&HeroesWater_TexList));
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.x);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl SHWaterfallLarge(ObjectMaster* obj)
{
	auto model = SH_WATERFS->getmodel()->child->child->child;
	obj->field_4C = reinterpret_cast<void*>(model);
	model->sa2bmodel->Radius = 100000.0f;

	Play3DSound_EntityPosBank(obj->Data1.Entity, 7, &obj->Data1.Entity->Position, 60, 7);

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub_Delayed1 = SHWaterfallLarge_Display;
}

static void __cdecl SHWaterfallSmall_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture((NJS_TEXLIST*)&HeroesWater_TexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl SHWaterfallSmall(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;

	obj->field_4C = reinterpret_cast<void*>(GetChildModelByIndex(SH_WATERFS->getmodel(), static_cast<int>(data->Scale.x)));

	Play3DSound_EntityPosBank(data, 7, &data->Position, 30, 7);

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub_Delayed1 = SHWaterfallSmall_Display;
}

static void __cdecl SHFlag_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLandTable->TextureList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njScalef(data->Scale.z);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl SHFlag_DisplayAlpha(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLandTable->TextureList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njScalef(data->Scale.z);
	njRotateY_(0x2000 + (-0x500 + (0x1000 * (Angle)(1.0f - (sin(GetTimer()) / 10.0f)))));
	DrawSA2BModel(model->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl SHFlag_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		AddToCollisionList(obj);
	}
}

static void __cdecl SHFlag(ObjectMaster* obj)
{
	InitCollision(obj, &Col_Pole, 1, 4);

	obj->field_4C = reinterpret_cast<void*>(SH_POLFLAG->getmodel());

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = SHFlag_Main;
	obj->DisplaySub = SHFlag_Display;
	obj->DisplaySub_Delayed1 = SHFlag_DisplayAlpha;
}

static void __cdecl SHMovingPltfrms_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLandTable->TextureList);

	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);

	DrawSA2BModel(model->child->sa2bmodel);
	DrawSA2BModel(model->child->child->sa2bmodel);

	if (model->child->child->child)
	{
		DrawSA2BModel(model->child->child->child->sa2bmodel);
	}

	if (data->field_2 == 1)
	{
		njSetTexture((NJS_TEXLIST*)&HeroesWater_TexList);

		DrawSA2BModel(model->child->sibling->sa2bmodel);
	}
	
	njPopMatrixEx();
}

static void __cdecl SHMovingPltfrms_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		EntityData1* entity = obj->Data1.Entity;

		entity->field_2 = 0;

		if (ruin != 0 && ruin == static_cast<int>(entity->Scale.y))
		{
			if (entity->Position.y != entity->Scale.z)
			{
				if (entity->Scale.x >= entity->Scale.z)
				{
					if (entity->Position.y <= entity->Scale.z)
					{
						entity->Position.y = entity->Scale.z;
					}
					else if (entity->Position.y > entity->Scale.z)
					{
						entity->Position.y -= 2;
					}

					if (entity->Position.y == entity->Scale.x - 2)
					{
						Play3DSound_Vector(4100, &entity->Position, 0, 0, 100);
					}
				}
				else if (entity->Scale.x <= entity->Scale.z)
				{
					if (entity->Position.y >= entity->Scale.z)
					{
						entity->Position.y = entity->Scale.z;
					}
					else if (entity->Position.y < entity->Scale.z)
					{
						entity->Position.y += 2;
						entity->field_2 = 1;
					}

					if (entity->Position.y == entity->Scale.x + 2)
					{
						Play3DSound_Vector(4100, &entity->Position, 0, 0, 100);
					}

					if (entity->Position.y <= entity->Scale.z - 1 && entity->Position.y >= entity->Scale.z - 3)
					{
						Play3DSound_Vector(4100, &entity->Position, 0, 0, 100);
					}
				}
			}
		}

		AddToCollisionList(obj);
	}
}

static void __cdecl SHMovingPltfrms(ObjectMaster* obj)
{
	auto entity = obj->Data1.Entity;
	auto id = static_cast<int>(entity->Scale.x);

	obj->field_4C = reinterpret_cast<void*>(GetSiblingModelByIndex(SH_MORUINS->getmodel()->child, id));

	switch (id)
	{
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

static void __cdecl SHRuinTrigger(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		auto data = obj->Data1.Entity;

		if (ruin != data->Scale.x)
		{
			if (IsPlayerInsideSphere(&data->Position, data->Scale.y * 3))
			{
				ruin = static_cast<int>(data->Scale.x);
			}
		}
	}
}

static void __cdecl SHPlatforms_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLandTable->TextureList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScale_(data->Scale.x, data->Scale.y, data->Scale.z);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl SHPlatforms(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;

	InitCollision(obj, &Col_Platform, 1, 4);

	obj->field_4C = SH_PLATFOR->getmodel();
	data->Collision->CollisionArray[0].param1 *= data->Scale.x;
	data->Collision->CollisionArray[0].param2 *= data->Scale.y;
	data->Collision->CollisionArray[0].param3 *= data->Scale.z;

	obj->MainSub = MainSub_Collision;
	obj->DisplaySub = SHPlatforms_Display;
}

static void __cdecl SHBreakableBlock_Display(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLandTable->TextureList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateZ(_nj_current_matrix_ptr_, data->Rotation.z);
	njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawSA2BModel(model->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl SHBreakableBlock_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		auto entity = obj->Data1.Entity;
		auto player = GetCollidingPlayer(obj);

		if (player && player->Data1.Entity->Status & Status_Attack && player->Data1.Entity->Position.y < entity->Position.y + 30)
		{
			NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;
			model = model->child->sibling->child;

			LoadBreaker(&entity->Position, &entity->Rotation, model, 0.0f, 15.0f, 0.0f, 60);
			Play3DSound_Vector(4100, &entity->Position, 0, 0, 70);
			UpdateSetDataAndDelete(obj);
		}

		AddToCollisionList(obj);
	}
}

static void __cdecl SHBreakableBlock(ObjectMaster* obj)
{
	auto entity = obj->Data1.Entity;

	obj->field_4C = reinterpret_cast<void*>(SH_BRBLOCK->getmodel());

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = SHBreakableBlock_Main;
	obj->DisplaySub = SHBreakableBlock_Display;

	InitCollision(obj, &Col_BreakBlock, 1, 4);

	entity->Collision->CollisionArray[0].rotation.x = entity->Rotation.x;
	entity->Collision->CollisionArray[0].rotation.z = entity->Rotation.z;
}

static ObjectListEntry SeasideHillObjectList_list[]
{
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
	{ LoadObj_Data1, ObjIndex_Common, DistObj_Default, 0, (ObjectFuncPtr)0x48ADE0 },
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
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 1560000, (ObjectFuncPtr)LIGHT_SW },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Big_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, WoodenCrate_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, IronCrate_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, (ObjectFuncPtr)IronEggmanCrate },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, SOLIDBOX },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 160000, ItemBoxAir_Main },
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

static ObjectListHead SeasideHillObjectList = { arraylengthandptrT(SeasideHillObjectList_list, int) };

static void __cdecl SeasideHillCam(CameraInfo* cam, CameraParam* param)
{
	CameraPos = { 1295.0f, 2300.0f, -32873.0f };
	CameraTgt = MainCharObj1[CurrentScreen]->Position;
	CameraTargetMode = 0;

	if (CameraTgt.z < -32873.0f)
	{
		ReleaseCamera(CurrentScreen, cam->currentCameraSlot);
	}
}

static void __cdecl SeasideHill_Main(ObjectMaster* obj)
{
	AnimateTexlist(&HeroesWater_TexList, 2, (Uint32*)&obj->Data1.Entity->Scale.x, (void**)&obj->field_4C);

	// Temporary camera for SH
	for (int i = 0; i < 4; ++i)
	{
		auto cam = pCameraLocations[i];
		auto player = MainCharObj1[i];

		if (player && cam)
		{
			if (player->Position.z < -31317.0f && player->Position.z > -32873.0f)
			{
				if (GetCameraMode(i, GetCurrentCameraSlot(i)) != CameraMode_User)
				{
					RegisterEventCameraFunc(i, SeasideHillCam);
					SetAdjustMode(i, GetCurrentCameraSlot(i), CameraAdjust_None);
				}
			}
		}
	}
}

static void __cdecl SeasideHill_Load()
{
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
	LoadStageSounds("se_ac_gf.mlt", (void*)0x8A0F60);

	LoadTextureList("s01w", (NJS_TEXLIST*)&HeroesWater_TexList);
	
	LoadMDL(&SH_FLOWERS, "SH_FLOWERS", ModelFormat_SA2B);
	LoadMDL(&SH_WATERFS, "SH_WATERFS", ModelFormat_SA2B);
	LoadMDL(&SH_POLFLAG, "SH_POLFLAG", ModelFormat_SA2B);
	LoadMDL(&SH_MORUINS, "SH_MORUINS", ModelFormat_SA2B);
	LoadMDL(&SH_PLATFOR, "SH_PLATFOR", ModelFormat_SA2B);
	LoadMDL(&SH_BRBLOCK, "SH_BRBLOCK", ModelFormat_SA2B);
}

static void __cdecl SeasideHill_Delete()
{
	FreeMDL(&SH_MORUINS);
	FreeMDL(&SH_FLOWERS);
	FreeMDL(&SH_WATERFS);
	FreeMDL(&SH_POLFLAG);
	FreeMDL(&SH_PLATFOR);
	FreeMDL(&SH_BRBLOCK);

	FreeTexList((NJS_TEXLIST*)&HeroesWater_TexList);
	CommonLevelDelete();
}

void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions)
{
	CityEscapeHeader.Init = SeasideHill_Load;
	CityEscapeHeader.subprgmanager = SeasideHill_Main;
	CityEscapeHeader.Free = SeasideHill_Delete;

	SetStartEndPoints(helperFunctions, &sh_startpos, &sh_2pintro, &sh_endpos, &sh_endpos23);
}