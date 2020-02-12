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

void OPFins_Display(ObjectMaster *a1) {
	if (CurrentChunk == 4 || CurrentChunk == 5) {
		for (int i = 0; i < LengthOfArray(OceanPalace_EventObjects); ++i) {
			if (OceanPalace_EventObjects[i].Model > 1 && CheckModelDisplay2(OceanPalace_EventObjects[i])) {
				SOI_LIST2 item = OceanPalace_EventObjects[i];

				RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
				njPushMatrix(0);
				njTranslateV(_nj_current_matrix_ptr_, &item.Position);
				njRotateX(_nj_current_matrix_ptr_, item.Rotation[0]);
				njRotateY(_nj_current_matrix_ptr_, item.Rotation[1]);
				njRotateZ(_nj_current_matrix_ptr_, item.Rotation[2]);
				njScale(item.Scale.x, item.Scale.y, item.Scale.z);

				switch (item.Model) {
				case 2: DrawModel(OP_TURFINS->getmodel()->basicmodel); break;
				case 3: DrawModel(OP_TURFINS->getmodel()->child->basicmodel); break;
				case 4: DrawModel(OP_TURFINS->getmodel()->child->child->basicmodel); break;
				case 5: DrawModel(OP_TURFINS->getmodel()->child->child->child->basicmodel); break;
				}

				njPopMatrix(1u);
			}
		}
	}
}

void OPFins_Main(ObjectMaster *obj) {
	EntityData1* data = obj->Data1.Entity;

	if (data->Action == 0) {
		obj->DisplaySub = OPFins_Display;
		data->Action = 1;
	}

	if (CurrentChunk == 5) {
		data->Scale.x++;
		if (data->Scale.x > 300) data->Scale.x = 0;

		short finsstate = data->Scale.x;

		for (Int i = 9; i < 41; ++i) {
			if (finsstate <= 100) {
				OceanPalace_EventObjects[i].Rotation[1] -= 100;
			}
			if (finsstate > 100) {
				OceanPalace_EventObjects[i].Rotation[1] += 50.5f;
			}
		}
		for (Int i = 41; i < 73; ++i) {
			if (finsstate <= 100) {
				OceanPalace_EventObjects[i].Rotation[1] += 100;
			}
			if (finsstate > 100) {
				OceanPalace_EventObjects[i].Rotation[1] -= 50.5f;
			}
		}
		for (Int i = 9; i < 73; ++i) {
			if (finsstate <= 100) {
				OceanPalace_EventObjects[i].Rotation[0] += 10;
			}
			if (finsstate > 100) {
				OceanPalace_EventObjects[i].Rotation[0] -= 5;
			}
		}
	}
}

void OPFlowers(ObjectMaster* a1) {
	EntityData1 *Data1 = a1->Data1.Entity;

	if (Data1->Action == 0) {
		a1->DisplaySub = a1->MainSub;
		a1->MainSub = nullptr;
		Data1->Action = 1;
		return;
	}

	for (int i = 0; i < LengthOfArray(OceanPalace_Flowers); ++i) {
		if (CheckModelDisplay2(OceanPalace_Flowers[i])) {
			SOI_LIST2 item = OceanPalace_Flowers[i];

			RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
			njPushMatrix(0);
			njTranslateV(_nj_current_matrix_ptr_, &item.Position);
			njRotateX(_nj_current_matrix_ptr_, item.Rotation[0]);
			njRotateY(_nj_current_matrix_ptr_, item.Rotation[1]);
			njRotateZ(_nj_current_matrix_ptr_, item.Rotation[2]);
			njScale(item.Scale.x, item.Scale.y, item.Scale.z);

			switch (item.Model) {
			case 0: DrawModel(OP_FLOWERS->getmodel()->basicmodel); break;
			case 1: DrawModel(OP_FLOWERS->getmodel()->child->basicmodel); break;
			case 2: DrawModel(OP_FLOWERS->getmodel()->child->child->basicmodel); break;
			case 3: DrawModel(OP_FLOWERS->getmodel()->child->child->child->basicmodel); break;
			}

			njPopMatrix(1u);
		}
	}
}

void OPWaterfalls(ObjectMaster *a1) {
	if (!CurrentLandTable) return;

	EntityData1 *Data1 = a1->Data1.Entity;

	if (Data1->Action == 0) {
		a1->DisplaySub = a1->MainSub;
		a1->MainSub = nullptr;
		Data1->Action = 1;
		return;
	}

	for (int i = 0; i < LengthOfArray(OceanPalace_Waterfalls); ++i) {
		if (CheckModelDisplay2(OceanPalace_Waterfalls[i])) {
			SOI_LIST2 item = OceanPalace_Waterfalls[i];

			RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
			njPushMatrix(0);
			njTranslateV(_nj_current_matrix_ptr_, &item.Position);
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
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
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
	if (ClipSetObject(obj)) {
		AddToCollisionList(obj);
	}
}

void OPPOLE(ObjectMaster *obj)
{
	InitCollision(obj, &Col_Pole, 1, 4);

	obj->MainSub = OPPOLE_Main;
	obj->DisplaySub = &OPPOLE_Display;
}

void BoulderPath(ObjectMaster *obj) {
	EntityData1* data = obj->Data1.Entity;
	LoopHead * loopdata = &OP_BoulderPaths[data->Index];

	if (data->Action == 0) {
		obj->DisplaySub = obj->MainSub;
		obj->MainSub = nullptr;
		data->Action = 1;
		return;
	}
	else {
		if (data->field_6 < loopdata->Count) {
			if (GameState != GameStates_Pause) {
				data->Scale.x = data->Scale.x + (loopdata->TotalDistance / loopdata->Points[data->field_6].Distance) / loopdata->TotalDistance * 7;
				TransformSpline(&data->Position, loopdata->Points[data->field_6].Position, loopdata->Points[data->field_6 + 1].Position, data->Scale.x);
				if (loopdata->Points[data->field_6].YRot != 0) data->Rotation.y = loopdata->Points[data->field_6].YRot;
				if (data->Scale.x > 1) { data->Scale.x = 0; data->field_6++; }
				data->Rotation.x += 1500;

				data->Status = IsPlayerInsideSphere(&data->Position, 130.0f);
				if (data->Status) {
					char player = data->Status - 1;
					EntityData1 *ed1 = MainCharObj1[player];
					CharObj2Base *co2 = MainCharObj2[player];

					GameState = GameStates_RestartLevel_1;

					ed1->Rotation.y = data->Rotation.y + 0x4000;
					co2->Speed.x = 22;
					co2->Speed.y = 2;
				}
			}

			RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
			njPushMatrix(0);

			njTranslateV(_nj_current_matrix_ptr_, &data->Position);
			njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
			njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);

			DrawModel(OP_BOULDER->getmodel()->basicmodel);
			njPopMatrix(1u);
		}
		else {
			DeleteObject(obj);
		}
	}
}

void OPBoulders_Display(ObjectMaster *obj) {
	if (CurrentChunk < 6)
		return;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);

	switch (obj->Data1.Entity->Action) {
	case 1:
		njTranslate(_nj_current_matrix_ptr_, -8200.3408f, 2030, -39259.3);
		njRotateY(_nj_current_matrix_ptr_, 32768);
		break;
	case 2:
		njTranslate(_nj_current_matrix_ptr_, -8274.9741f, 1363, -44980.36);
		njRotateY(_nj_current_matrix_ptr_, 24735);
		break;
	case 3:
		njTranslate(_nj_current_matrix_ptr_, -6785.288f, 963, -46514.48);
		njRotateY(_nj_current_matrix_ptr_, 32768);
		break;
	}

	DrawModel(OP_BOULDER->getmodel()->basicmodel);
	njPopMatrix(1u);
}

void OPBoulders(ObjectMaster *obj) {
	if (CurrentChunk < 6)
		return;

	EntityData1* data = obj->Data1.Entity;

	switch (data->Action)
	{
	case 0:
		obj->DisplaySub = OPBoulders_Display;
		data->Action = 1;
		break;
	case 1:
		if (IsPlayerInsideSphere(&OceanPalaceTrigger, 45.0f) == 1) {
			data->Action = 2;
			LoadChildObject(LoadObj_Data1, BoulderPath, obj);
		}

		break;
	case 2:
		if (obj->Child->Data1.Entity->Position.z < -44954) {
			data->Action = 3;

			LoadChildObject(LoadObj_Data1, BoulderPath, obj)->Data1.Entity->Index = 1;
		}

		break;
	case 3:
		if (obj->Child->Data1.Entity->Position.z < -46583) {
			data->Action = 0;

			LoadChildObject(LoadObj_Data1, BoulderPath, obj)->Data1.Entity->Index = 2;
		}

		break;
	}
}

NJS_VECTOR pos;

void BoulderCam(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	
	if (IsPlayerInsideSphere(&data->Position, data->Scale.y)) {
		if (data->Scale.x == 8) {
			pos = OP_BoulderPaths[0].Points[10].Position;
			data->field_6 = 10;
			data->Scale.z = 0;
			data->Action = 1;
		}
		else {
			data->Action = 0;
			data->field_6 = 0;
		}
	}

	if (data->Action == 1) {
		LoopHead* loopdata = &OP_BoulderPaths[0];

		if (data->field_6 == 79) return;

		float dist = GetDistance(&pos, &MainCharObj1[0]->Position);
		float speed = (1 - (dist / 500)) * 24;
		if (speed < 0) speed = 0;

		data->Scale.z = data->Scale.z + (loopdata->TotalDistance / loopdata->Points[data->field_6].Distance) / loopdata->TotalDistance * speed;
		TransformSpline(&stru_1DCFF40.field_194, loopdata->Points[data->field_6].Position, loopdata->Points[data->field_6 + 1].Position, data->Scale.z);
		stru_1DCFF40.field_194.y -= 50;
		if (loopdata->Points[data->field_6].YRot != 0) data->Rotation.y = loopdata->Points[data->field_6].YRot;
		if (data->Scale.z > 1) { data->Scale.z = 0; data->field_6++; }
		pos = stru_1DCFF40.field_194;
	}
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
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, RingGroup },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, RingGroup },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCYL },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCUBE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)SPHERE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)HINTBOX },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 40000, (ObjectFuncPtr)IRONBALL2 },
	{ LoadObj_Data1, ObjIndex_4, DistObj_UseDist, 40000, (ObjectFuncPtr)IRONBALL2 },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 160000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)E_GOLD },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, ObjFan },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1160000, ObjFan },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, ObjFan },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1460000, ObjFan },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 50000, BoulderCam },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Common, DistObj_UseDist, 2360000, DashRampAdjust },
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
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 160000, ItemBoxAir_Main },
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

void OceanPalace_SkyBox(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslate(_nj_current_matrix_ptr_, data->Position.x, 1.8f, data->Position.z);
	DrawModel(OP_SKYMDLS->getmodel()->basicmodel);
	DrawModel(OP_SKYMDLS->getmodel()->child->basicmodel);
	njPopMatrix(1u);
}

void OceanPalace_Main(ObjectMaster* obj) {
	ChunkHandler("OP", OceanPalaceChunks, LengthOfArray(OceanPalaceChunks));
	AnimateTextures(OceanPalaceAnimTexs, 2);
	
	obj->Data1.Entity->Position = MainCharObj1[0]->Position;

	if (obj->Data1.Entity->Action == 0) {
		LoadObject(LoadObj_Data1, "OPWaterfalls", OPWaterfalls, 3);
		LoadObject(LoadObj_Data1, "OPFlowers", OPFlowers, 3);
		LoadObject(LoadObj_Data1, "OPFins_Main", OPFins_Main, 3);
		LoadObject(LoadObj_Data1, "OPBoulders", OPBoulders, 3);
		obj->DisplaySub = OceanPalace_SkyBox;
		obj->Data1.Entity->Action = 1;
	}
}

void OceanPalace_Load() {
	CommonLevelInit();

	LoadLevelChunks("OP", OceanPalaceChunks, LengthOfArray(OceanPalaceChunks), (char*)"oceanpalace", &oceanpalace_texlist);
	CurrentLevelTexList = CurrentLandTable->TextureList;

	for (uint8_t i = 0; i < LengthOfArray(OceanPalaceObjectList_list); ++i) {
		CityEscape_ObjectArray[i] = OceanPalaceObjectList_list[i];
	}

	void* setfile = nullptr;

	if (CurrentLevel = LevelIDs_MetalHarbor) {
		setfile = LoadSETFile(2048, (char*)"ocean-palace-set.bin", (char*)"dummy-set.bin");
	}
	else {
		setfile = LoadSETFile(2048, (char*)"ocean-palace-set-2p.bin", (char*)"dummy-set.bin");
	}
	
	LoadSetObject(&CityEscape_ObjectList, setfile);
	LoadStageLight("stg13_light.bin");
	LoadStagePaths(OceanPalacePathList);
	LoadLevelMusic((char*)"oceanpalace.adx");
	LoadDeathZones(SeasideHillDeathZones);
	LoadFogData_Fogtask("stg13_fog.bin", (FogData*)0x1A280C8);
	LoadTextures(CommonTextureInfoPtr);
	OP_WATERFS = LoadMDL("OP_WATERFS");
	OP_FLOWERS = LoadMDL("OP_FLOWERS");
	OP_TURFINS = LoadMDL("OP_TURFINS");
	OP_BOULDER = LoadMDL("OP_BOULDER");
	OP_POLFLAG = LoadMDL("OP_POLFLAG");
	OP_SKYMDLS = LoadMDL("OP_SKYMDLS");
}

void OceanPalaceDelete() {
	FreeMDL(OP_TURFINS);
	FreeMDL(OP_POLFLAG);
	FreeMDL(OP_FLOWERS);
	FreeMDL(OP_BOULDER);
	FreeMDL(OP_WATERFS);

	CommonLevelDelete();
}

void OceanPalace_Init(const char *path, const HelperFunctions &helperFunctions) {
	MetalHarborHeader.Init = OceanPalace_Load;
	MetalHarborHeader.subprgmanager = OceanPalace_Main;
	MetalHarborHeader.anonymous_2 = OceanPalaceDelete;
	MetalHarbor2PHeader.Init = OceanPalace_Load;
	MetalHarbor2PHeader.subprgmanager = OceanPalace_Main;
	MetalHarbor2PHeader.anonymous_2 = OceanPalaceDelete;
	SetStartEndPoints(helperFunctions, &op_startpos, nullptr, &op_endpos, &op_endpos23);
	op_startpos.Level = LevelIDs_MetalHarbor2P;
	op_endpos.Level = LevelIDs_MetalHarbor2P;
	op_endpos23.Level = LevelIDs_MetalHarbor2P;
	SetStartEndPoints(helperFunctions, &op_startpos, &op_2pintro, &op_endpos, &op_endpos23);
}