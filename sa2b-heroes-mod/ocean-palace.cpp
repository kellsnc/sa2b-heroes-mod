#include "stdafx.h"
#include "ocean-palace.h"

ModelInfo * OP_WATERFS;
ModelInfo * OP_FLOWERS;
ModelInfo * OP_TURFINS;
ModelInfo * OP_BOULDER;
ModelInfo * OP_POLFLAG;
ModelInfo * OP_SKYMDLS;

NJS_TEXNAME oceanpalace_texname[114];
NJS_TEXLIST oceanpalace_texlist{ arrayptrandlength(oceanpalace_texname) };

extern CollisionData Col_Pole;

void OPWaterfalls(ObjectMaster *a1) {
	if (!CurrentLandTable) return;

	EntityData1 *Data1 = a1->Data1.Entity;

	if (Data1->Action == 0) {
		a1->DisplaySub = a1->MainSub;
		Data1->Action = 1;
	}

	for (int i = 0; i < LengthOfArray(OceanPalace_Waterfalls); ++i) {
		if (CheckModelDisplay2(OceanPalace_Waterfalls[i])) {
			SOI_LIST2 item = OceanPalace_Waterfalls[i];

			RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
			njPushMatrix(0);
			njTranslate(_nj_current_matrix_ptr_, item.Position.x, item.Position.y, item.Position.z);
			njRotateX(_nj_current_matrix_ptr_, item.Rotation[0]);
			njRotateY(_nj_current_matrix_ptr_, item.Rotation[1]);
			njRotateZ(_nj_current_matrix_ptr_, item.Rotation[2]);
			njScale(item.Scale.x, item.Scale.y, item.Scale.z);

			switch (item.Model) {
			case 0: DrawModel(OP_WATERFS->getmodel()->basicmodel); break;
			case 1: DrawModel(OP_WATERFS->getmodel()->child->basicmodel); break;
			case 2: DrawModel(OP_WATERFS->getmodel()->child->child->basicmodel); break;
			case 3: DrawModel(OP_WATERFS->getmodel()->child->child->child->basicmodel); break;
			case 4: DrawModel(OP_WATERFS->getmodel()->child->child->child->child->basicmodel); break;
			case 5: DrawModel(OP_WATERFS->getmodel()->child->child->child->child->child->basicmodel); break;
			case 6: DrawModel(OP_WATERFS->getmodel()->child->child->child->child->child->child->basicmodel); break;
			case 7: DrawModel(OP_WATERFS->getmodel()->child->child->child->child->child->child->child->basicmodel); break;
			case 8: DrawModel(OP_WATERFS->getmodel()->child->child->child->child->child->child->child->child->basicmodel); break;
			case 9: DrawModel(OP_WATERFS->getmodel()->child->child->child->child->child->child->child->child->child->basicmodel); break;
			}

			njPopMatrix(1u);
		}
	}
}

void OPPOLE_Display(ObjectMaster *obj) {
	EntityData1* data = obj->Data1.Entity;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslate(_nj_current_matrix_ptr_, data->Position.x, data->Position.y, data->Position.z);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
		
	if (data->Scale.x == 1) {
		DrawModel(OP_POLFLAG->getmodel()->child->basicmodel);
		DrawModel(OP_WATERFS->getmodel()->child->child->child->child->child->child->child->child->child->child->child->basicmodel);
	}
	else {
		DrawModel(OP_POLFLAG->getmodel()->basicmodel);
		DrawModel(OP_WATERFS->getmodel()->child->child->child->child->child->child->child->child->child->child->basicmodel);
	}
		
	njPopMatrix(1u);
}

void OPPOLE_Main(ObjectMaster *obj) {
	if (!ClipSetObject(obj)) {
		AddToCollisionList(obj);
	}
}

void OPPOLE(ObjectMaster *obj)
{
	InitCollision(obj, &Col_Pole, 1, 4);

	obj->MainSub = OPPOLE_Main;
	obj->DisplaySub = &OPPOLE_Display;
}

ObjectListEntry OceanPalaceObjectList_list[] = {
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
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, nullptr },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 160000, nullptr },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, nullptr },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Common, DistObj_UseDist, 2360000, (ObjectFuncPtr)DashRamp_Main },
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
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, Beetle_Attack },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, Beetle_Attack },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 250000, Beetle_Attack },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 250000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)E_GOLD},
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 160000, (ObjectFuncPtr)KDITEMBOX },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Stationary },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Electric },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Attack },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 1360000, (ObjectFuncPtr)SpringA_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1000000, OPPOLE },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 8000000, OPPOLE },
	{ (LoadObj)0 },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 2400000, Boxes },
};

void OceanPalace_FreeModels() {
	FreeMDL(OP_TURFINS);
	FreeMDL(OP_POLFLAG);
	FreeMDL(OP_FLOWERS);
	FreeMDL(OP_BOULDER);
	FreeMDL(OP_WATERFS);
}

void OceanPalace_LoadObjects() {
	LoadObject(LoadObj_Data1, "OPWaterfalls", OPWaterfalls, 3);
	/*LoadObject(LoadObj_Data1, 3, OPFlowers);
	LoadObject(LoadObj_Data1, 3, OPFins_Main);
	LoadObject(LoadObj_Data1, 3, OPBoulders);*/
}

void OceanPalace_OnFrame() {
	ChunkHandler("OP", OceanPalaceChunks, LengthOfArray(OceanPalaceChunks));
	AnimateTextures(OceanPalaceAnimTexs, 2);

	if (GameState == GameStates_Ingame && restart) {
		OceanPalace_LoadObjects();
		restart = false;
	}
}

void OceanPalace_Load() {
	CommonLevelInit();

	LoadLevelChunks("OP", OceanPalaceChunks, LengthOfArray(OceanPalaceChunks), (char*)"oceanpalace", &oceanpalace_texlist);
	CurrentLevelTexList = CurrentLandTable->TextureList;

	for (uint8_t i = 0; i < LengthOfArray(OceanPalaceObjectList_list); ++i) {
		CityEscape_ObjectArray[i] = OceanPalaceObjectList_list[i];
	}

	void* setfile = LoadSETFile(2048, (char*)"ocean-palace-set.bin", (char*)"dummy-set.bin");
	LoadSetObject(&CityEscape_ObjectList, setfile);
	LoadStageLight("stg13_light.bin");
	LoadStagePaths(OceanPalacePathList);
	LoadLevelMusic((char*)"oceanpalace.adx");
	LoadDeathZones(SeasideHillDeathZones);
	LoadFogData_Fogtask("stg13_fog.bin", (FogData*)0x1A280C8);

	OP_WATERFS = LoadMDL("OP_WATERFS");
	OP_FLOWERS = LoadMDL("OP_FLOWERS");
	OP_TURFINS = LoadMDL("OP_TURFINS");
	OP_BOULDER = LoadMDL("OP_BOULDER");
	OP_POLFLAG = LoadMDL("OP_POLFLAG");
	OP_SKYMDLS = LoadMDL("OP_SKYMDLS");
	OceanPalace_LoadObjects();
	CommonObjects_LoadModels();
}

void OceanPalace_Init(const char *path, const HelperFunctions &helperFunctions) {
	MetalHarborHeader.Init = OceanPalace_Load;
	MetalHarborHeader.subprgmanager = nullptr;
	SetStartEndPoints(helperFunctions, &op_startpos, &op_2pintro, &op_endpos, &op_endpos23);
}