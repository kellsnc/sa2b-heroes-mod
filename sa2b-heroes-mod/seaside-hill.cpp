#include "stdafx.h"
#include "seaside-hill-deathzones.h"
#include "seaside-hill.h"

ModelInfo * SH_PLATFOR;
ModelInfo * SH_MORUINS;
ModelInfo * SH_POLFLAG;
ModelInfo * SH_WATERFS;
ModelInfo * SH_FLOWERS;

float ruin = 0;
static int flagtimer = 0;

void SHFlowers(ObjectMaster *a1) {
	EntityData1 *Data1 = a1->Data1.Entity;
		
	if (Data1->Action == 0) {
		a1->DisplaySub = a1->MainSub;
		Data1->Action = 1;
	}

	for (int i = 0; i < LengthOfArray(SeasideHill_Flowers); ++i) {
		if (CheckModelDisplay2(SeasideHill_Flowers[i])) {
			SOI_LIST2 item = SeasideHill_Flowers[i];

			RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
			njPushMatrix(0);
			njTranslate(_nj_current_matrix_ptr_, item.Position.x, item.Position.y, item.Position.z);
			njRotateX(_nj_current_matrix_ptr_, item.Rotation[0]);
			njRotateY(_nj_current_matrix_ptr_, item.Rotation[1]);
			njRotateZ(_nj_current_matrix_ptr_, item.Rotation[2]);
			njScale(item.Scale.x, item.Scale.y, item.Scale.z);

			switch (item.Model) {
			case 0: DrawModel(SH_FLOWERS->getmodel()->basicmodel); break;
			case 1: DrawModel(SH_FLOWERS->getmodel()->child->basicmodel); break;
			case 2: DrawModel(SH_FLOWERS->getmodel()->child->child->basicmodel); break;
			case 3: DrawModel(SH_FLOWERS->getmodel()->child->child->child->basicmodel); break;
			case 4: DrawModel(SH_FLOWERS->getmodel()->child->child->child->child->basicmodel); break;
			case 5: DrawModel(SH_FLOWERS->getmodel()->child->child->child->child->child->basicmodel); break;
			case 6: DrawModel(SH_FLOWERS->getmodel()->child->child->child->child->child->child->basicmodel); break;
			case 7: DrawModel(SH_FLOWERS->getmodel()->child->child->child->child->child->child->child->basicmodel); break;
			case 8: DrawModel(SH_FLOWERS->getmodel()->child->child->child->child->child->child->child->child->basicmodel); break;
			}

			njPopMatrix(1u);
		}
	}
}

void SHWaterfalls(ObjectMaster *a1) {
	EntityData1 *Data1 = a1->Data1.Entity;

	if (Data1->Action == 0) {
		a1->DisplaySub = a1->MainSub;
		Data1->Action = 1;
	}

	for (int i = 0; i < LengthOfArray(SeasideHill_Waterfalls); ++i) {
		if (CheckModelDisplay2(SeasideHill_Waterfalls[i])) {
			SOI_LIST2 item = SeasideHill_Waterfalls[i];

			RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
			njPushMatrix(0);
			njTranslate(_nj_current_matrix_ptr_, item.Position.x, item.Position.y, item.Position.z);
			njRotateX(_nj_current_matrix_ptr_, item.Rotation[0]);
			njRotateY(_nj_current_matrix_ptr_, item.Rotation[1]);
			njRotateZ(_nj_current_matrix_ptr_, item.Rotation[2]);
			njScale(item.Scale.x, item.Scale.y, item.Scale.z);

			switch (item.Model) {
			case 0: DrawModel(SH_WATERFS->getmodel()->basicmodel); break;
			case 1: DrawModel(SH_WATERFS->getmodel()->child->basicmodel); break;
			case 2: DrawModel(SH_WATERFS->getmodel()->child->child->basicmodel); break;
			case 3: DrawModel(SH_WATERFS->getmodel()->child->child->child->basicmodel); break;
			}

			njPopMatrix(1u);
		}
	}
}

void SHSpikes_Display(ObjectMaster *a1)
{
	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslate(_nj_current_matrix_ptr_, a1->Data1.Entity->Position.x, a1->Data1.Entity->Position.y, a1->Data1.Entity->Position.z);
	njRotateY(_nj_current_matrix_ptr_, a1->Data1.Entity->Rotation.y);
	DrawModel(SH_POLFLAG->getmodel()->basicmodel);
	njRotateY(_nj_current_matrix_ptr_, -a1->Data1.Entity->Rotation.y + a1->Data1.Entity->Scale.z);
	njScale(0.8f, 1, 1);
	DrawModel(SH_POLFLAG->getmodel()->child->basicmodel);
	njPopMatrix(1u);
}

void SHSpikes_Main(ObjectMaster *a1)
{
	if (ClipSetObject(a1)) {
		AddToCollisionList(a1);

		if (a1->Data1.Entity->Scale.z > 4000) a1->Data1.Entity->Scale.y = 1;
		if (a1->Data1.Entity->Scale.z == 0) a1->Data1.Entity->Scale.y = 0;

		if (a1->Data1.Entity->Scale.y == 0) a1->Data1.Entity->Scale.z += 10;
		if (a1->Data1.Entity->Scale.y == 1) a1->Data1.Entity->Scale.z -= 10;

		SHSpikes_Display(a1);
	}
}

void SHSpikes(ObjectMaster *a1)
{
	InitCollision(a1, &Col_Pole, 1, 4);
	a1->Data1.Entity->Scale.y = 0;

	a1->MainSub = &SHSpikes_Main;
	a1->DisplaySub = &SHSpikes_Display;
}

ObjectListEntry SeasideHillObjectList_list[] = {
	{ LoadObj_Data1, ObjIndex_Common, 0x10, 0.0, RingMain, (char*)"aRing1" },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)SpringA_Main },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, SpringB_Main },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1), ObjIndex_Stage, DistObj_UseDist, 360000, DashPanel_Main },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)LongSpring_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, Omochao_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)SKULL },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1), ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)EmeraldPiece_Load },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, GoalRing_Main },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)ORI },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 160000, (ObjectFuncPtr)PSKULL },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, ItemBoxBalloon },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 160000, ItemBox_Main },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)ROCKET },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)ROCKETMISSILE },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CHAOPIPE },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)MINIMAL },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 4000000, (ObjectFuncPtr)KDITEMBOX },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_6, DistObj_UseDist, 360000, Checkpoint_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)CWALL },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)RingLinearMain },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)RingCircleMain },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCYL },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCUBE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)SPHERE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)HINTBOX },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 40000, (ObjectFuncPtr)IRONBALL2 },
	{ LoadObj_Data1, ObjIndex_4, DistObj_UseDist, 40000, (ObjectFuncPtr)IRONBALL2 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)E_AI },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 160000, (ObjectFuncPtr)E_AI },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)E_GOLD },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)DashRamp_Main },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Big_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, WoodenCrate_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, IronCrate_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, SOLIDBOX },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)0x5E8EF0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)0x5E2C30 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, Beetle_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, Beetle_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 250000, Beetle_Main },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)E_AI },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)E_AI },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 250000, (ObjectFuncPtr)E_AI },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)E_GOLD},
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 160000, (ObjectFuncPtr)KDITEMBOX },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Main },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2400000, SHSpikes },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
};

void SeasideHill_LoadModels() {
	SH_FLOWERS = LoadMDL("SH_FLOWERS");
	SH_WATERFS = LoadMDL("SH_WATERFS");
	SH_POLFLAG = LoadMDL("SH_POLFLAG");

	LoadObject(LoadObj_Data1, "SHFlowers", SHFlowers, 3);
	LoadObject(LoadObj_Data1, "SHWaterfalls", SHWaterfalls, 3);
}

void SeasideHill_FreeModels() {
	FreeMDL(SH_FLOWERS);
	FreeMDL(SH_WATERFS);
	FreeMDL(SH_POLFLAG);
}

void __cdecl SeasideHill_SkyBox(ObjectMaster *a1) {

}

void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions) {
	WriteData((ObjectFuncPtr*)0x5DD213, SeasideHill_SkyBox);
	WriteData((LoopHead***)0x5DD124, SeasideHillPathList);
	WriteData((DeathZone**)0x5DD226, SeasideHillDeathZones);

	for (uint8_t i = 0; i < 92; ++i) {
		CityEscape_ObjectArray[i] = SeasideHillObjectList_list[i];
	}

	for (uint8_t i = 0; i < Characters_Amy; i++)
	{
		helperFunctions.RegisterStartPosition(i, startpos);
	}
}

void SeasideHill_OnFrame() {
	ChunkHandler("SH", SeasideHillChunks, LengthOfArray(SeasideHillChunks));
	AnimateTextures(SeasideHillAnimTexs, 2);
}