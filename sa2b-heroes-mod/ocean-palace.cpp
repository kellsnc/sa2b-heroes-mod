#include "stdafx.h"
#include "ocean-palace-paths.h"
#include "ocean-palace.h"

ModelInfo * OP_WATERFS;
ModelInfo * OP_FLOWERS;
ModelInfo * OP_TURFINS;
ModelInfo * OP_BOULDER;
ModelInfo * OP_POLFLAG;
ModelInfo * OP_SKYMDLS;
ModelInfo * OP_LNDFALL;
ModelInfo * OP_SCENARY;
ModelInfo * OP_LNDFALLCOL;

NJS_TEXLIST_ oceanpalace_texlist = { arrayptrandlength(oceanpalace_texname) };

extern CollisionData Col_Pole;

void OPFlowers_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->EntityData2;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawChunkModel(model->basicmodel);
	njPopMatrix(1u);
}

void OPFlowers(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	obj->EntityData2 = (UnknownData2*)OP_FLOWERS->getmodel()->child;

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = OPFlowers_Display;
}

void OPFlant_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->EntityData2;
	NJS_OBJECT* shadow = (NJS_OBJECT*)obj->UnknownA_ptr;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawChunkModel(model->basicmodel);

	if (data->Scale.x == 0) {
		DrawChunkModel(shadow->basicmodel);
	}
	
	njPopMatrix(1u);
}

void OPPlant(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	obj->EntityData2 = (UnknownData2*)GetChildModelByIndex(OP_FLOWERS->getmodel()->child->child, data->Scale.x);
	obj->UnknownA_ptr = (ObjUnknownA*)OP_FLOWERS->getmodel();

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = OPFlant_Display;
}

void OPWater_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->EntityData2;

	RenderInfo->CurrentTexlist = (NJS_TEXLIST*)&HeroesWater_TexList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawChunkModel(model->basicmodel);
	njPopMatrix(1u);
}

void OPWater(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	obj->EntityData2 = (UnknownData2*)GetChildModelByIndex(OP_WATERFS->getmodel(), data->Scale.x);

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = OPWater_Display;
}

void OPFallingStructure_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawChunkModel(model->basicmodel);
	njPopMatrix(1u);
}

void OPFallingStructure(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* dynobj = GetFreeDynObject();

	memcpy(dynobj, OP_LNDFALLCOL->getmodel(), sizeof(NJS_OBJECT));

	dynobj->pos[0] = data->Position.x;
	dynobj->pos[1] = data->Position.y;
	dynobj->pos[2] = data->Position.z;
	dynobj->ang[1] = data->Rotation.y;
	dynobj->evalflags = 0xFFFFFFF8;

	DynCol_Add(0x1, obj, dynobj);

	obj->EntityData2 = (UnknownData2*)dynobj;
	obj->field_4C = (void*)OP_LNDFALL->getmodel();

	obj->DeleteSub = ObjectFunc_DynColDelete;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = OPFallingStructure_Display;
}

void OPPOLE_Display(ObjectMaster *obj) {
	EntityData1* data = obj->Data1.Entity;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
		
	if (data->Scale.x == 1) {
		DrawChunkModel(OP_POLFLAG->getmodel()->child->basicmodel);
		RenderInfo->CurrentTexlist = (NJS_TEXLIST*)&HeroesWater_TexList;
		DrawChunkModel(OP_WATERFS->getmodel()->child->child->child->child->child->child->child->child->child->child->child->basicmodel);
	}
	else {
		DrawChunkModel(OP_POLFLAG->getmodel()->basicmodel);
		RenderInfo->CurrentTexlist = (NJS_TEXLIST*)&HeroesWater_TexList;
		DrawChunkModel(OP_WATERFS->getmodel()->child->child->child->child->child->child->child->child->child->child->basicmodel);
	}
		
	njPopMatrix(1u);
}

void OPPOLE_Main(ObjectMaster *obj) {
	if (ClipSetObject(obj)) {
		AddToCollisionList(obj);
	}
}

void OPPOLE(ObjectMaster *obj) {
	InitCollision(obj, &Col_Pole, 1, 4);

	obj->MainSub = OPPOLE_Main;
	obj->DisplaySub = &OPPOLE_Display;
}

void OPFins_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y + 0x8000);

	NJS_OBJECT* object = OP_TURFINS->getmodel();

	njPushMatrix(0); {
		njTranslate(_nj_current_matrix_ptr_, -60, -20, -90);
		njRotateY(_nj_current_matrix_ptr_, data->Rotation.z - 0x7000);
		njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
		DrawChunkModel(object->basicmodel);
		njPopMatrix(1u);
	}

	njPushMatrix(0); {
		njTranslate(_nj_current_matrix_ptr_, 60, -20, -90);
		njRotateY(_nj_current_matrix_ptr_, -data->Rotation.z + 0x7000);
		njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
		DrawChunkModel(object->child->basicmodel);
		njPopMatrix(1u);
	}

	njPushMatrix(0); {
		njTranslate(_nj_current_matrix_ptr_, -60, -15, 60);
		njRotateY(_nj_current_matrix_ptr_, data->Rotation.z - 0x7000);
		njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
		DrawChunkModel(object->child->child->basicmodel);
		njPopMatrix(1u);
	}

	njPushMatrix(0); {
		njTranslate(_nj_current_matrix_ptr_, 60, -15, 60);
		njRotateY(_nj_current_matrix_ptr_, -data->Rotation.z + 0x7000);
		njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
		DrawChunkModel(object->child->child->child->basicmodel);
		njPopMatrix(1u);
	}
	
	njPopMatrix(1u);
}

void OPFins_Main(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (ClipSetObject(obj)) {
		data->field_6++;

		if (data->field_6 > 300) {
			data->field_6 = 0;
			data->Rotation.x = 0;
			data->Rotation.z = 0;
		}

		short finsstate = data->field_6;

		if (finsstate <= 100) {
			data->Rotation.z -= 100;
			data->Rotation.x += 10;
		}
		if (finsstate > 100) {
			data->Rotation.z += 50.5f;
			data->Rotation.x -= 5;
		}
	}
}

void OPFins(ObjectMaster* obj)
{
	obj->MainSub = OPFins_Main;
	obj->DisplaySub = &OPFins_Display;
}

void OPLandMove_Display(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	int playerid = static_cast<int>(data->Scale.x);

	if (CurrentScreen == playerid) {
		Sint32 chunk = CurrentChunk[playerid];

		if (chunk > 6) {
			return;
		}

		EntityData1* data = obj->Data1.Entity;
		NJS_OBJECT* model = (NJS_OBJECT*)obj->EntityData2;

		RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
		njPushMatrix(0);
		njTranslate(_nj_current_matrix_ptr_, 2100, 0, -44000);
		njTranslateZ(data->Scale.y);

		njPushMatrix(0); {
			njRotateX(_nj_current_matrix_ptr_, 0x4000);
			njScalef(2.0f);
			DrawChunkModel(model->child->basicmodel);
			njPopMatrix(1);
		}

		njTranslate(_nj_current_matrix_ptr_, -2500, 0, 29000);
		njRotateX(_nj_current_matrix_ptr_, 0x4000);
		njScalef(2.0f);
		DrawChunkModel(model->child->sibling->basicmodel);
		DrawChunkModel(model->child->sibling->sibling->basicmodel);

		njPopMatrix(1u);
	}
}

void OPLandMove_Main(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	int playerid = static_cast<int>(data->Scale.x);
	Sint32 chunk = CurrentChunk[playerid];

	if (!MainCharObj1[playerid] || MainCharObj1[playerid]->Position.z < -31200.0f) {
		DeleteObject_(obj);
		return;
	}

	if (data->Action == 0) {
		if (chunk == 5) {
			obj->DisplaySub = OPLandMove_Display;
			data->Action = 1;
		}
	}
	else if (data->Action == 1) {
		if (IsPlayerIDInsideSphere(2100.0f, 280.0f, -30300.0f, 100.0f, playerid)) {
			data->Action = 2;
		}

		if (data->Scale.y < 8800.0f) {
			data->Scale.y += 2.5f;
		}
	}
	else {
		CameraScreenArray[playerid]->pos = { 2360.0f, 112.0f, -31000.0f };
	}
}

void OPLandMove(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	if (!MainCharObj1[static_cast<int>(data->Scale.x)]) {
		DeleteObject_(obj);
		return;
	}

	obj->EntityData2 = (UnknownData2*)OP_SCENARY->getmodel();

	obj->DeleteSub = DeleteFunc_ResetVars;
	obj->MainSub = OPLandMove_Main;
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

				NJS_VECTOR pos1 = loopdata->Points[data->field_6].Position;
				NJS_VECTOR pos2 = loopdata->Points[data->field_6 + 1].Position;

				NJS_VECTOR fixoffset = { 9000, -1.8f, 2900 };

				njAddVector(&pos1, &fixoffset);
				njAddVector(&pos2, &fixoffset);

				TransformSpline(&data->Position, &pos1, &pos2, data->Scale.x);
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

			DrawChunkModel(OP_BOULDER->getmodel()->basicmodel);
			njPopMatrix(1u);
		}
		else {
			DeleteObject(obj);
		}
	}
}

void OPBoulders_Display(ObjectMaster *obj) {
	if (CurrentChunk[0] < 6)
		return;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);

	njTranslate(_nj_current_matrix_ptr_, 9000, -1.8f, 2900);

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

	DrawChunkModel(OP_BOULDER->getmodel()->basicmodel);
	njPopMatrix(1u);
}

void OPBoulders(ObjectMaster *obj) {
	if (CurrentChunk[0] < 6)
		return;

	EntityData1* data = obj->Data1.Entity;

	switch (data->Action)
	{
	case 0:
		obj->DisplaySub = OPBoulders_Display;
		data->Action = 1;
		break;
	case 1:
		if (IsPlayerInsideSphere(800.0f, 1399.2f, -37145.0f, 45.0f) == 1) {
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

		NJS_VECTOR pos1 = loopdata->Points[data->field_6].Position;
		NJS_VECTOR pos2 = loopdata->Points[data->field_6 + 1].Position;

		NJS_VECTOR fixoffset = { 9000, -1.8f, 2900 };

		njAddVector(&pos1, &fixoffset);
		njAddVector(&pos2, &fixoffset);

		TransformSpline(&CameraInfo.Position, &pos1, &pos2, data->Scale.z);
		CameraInfo.Position.y -= 50;
		if (loopdata->Points[data->field_6].YRot != 0) data->Rotation.y = loopdata->Points[data->field_6].YRot;
		if (data->Scale.z > 1) { data->Scale.z = 0; data->field_6++; }
		pos = CameraInfo.Position;
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
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 1360000, (ObjectFuncPtr)SpringA_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 160000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)E_GOLD },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, ObjFan },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, OPPOLE },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1000000, nullptr }, //(ObjectFuncPtr)EFLENSF0
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, OPFlowers },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 50000, BoulderCam },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 6460000, OPWater },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, OPPlant },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, OPPOLE },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Common, DistObj_UseDist, 1360000, DashRampAdjust },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 5460000, OPLandMove },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 6460000, OPFins },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 5460000, OPFallingStructure },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
	{ (LoadObj)0 },
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

ObjectListHead OceanPalaceObjectList = { arraylengthandptr(OceanPalaceObjectList_list) };

void OceanPalace_SkyBox(ObjectMaster* obj) {
	NJS_VECTOR* position = &CameraScreenArray[CurrentScreen]->pos;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslate(_nj_current_matrix_ptr_, position->x, 0.0f, position->z);
	DrawSA2BModel(OP_SKYMDLS->getmodel()->sa2bmodel);
	DrawSA2BModel(OP_SKYMDLS->getmodel()->child->sa2bmodel);
	njPopMatrix(1u);
}

void OceanPalace_Main(ObjectMaster* obj) {
	AnimateTexlist(&HeroesWater_TexList, 2, (Uint32*)&obj->Data1.Entity->Scale.x, (void**)&obj->field_4C);
}

void OceanPalace_Load() {
	CurrentHeroesLevel = HeroesLevelIDs::OceanPalace;

	CommonLevelInit();
	
	LoadChunkFile("resource\\gd_pc\\s02_blk.bin");
	LoadLandTable("resource\\gd_pc\\s02.sa2lvl");
	LoadLevelTex((NJS_TEXLIST*)&oceanpalace_texlist, "s02");
	LoadTXCFile("resource\\gd_pc\\s02.txc");
	
	LoadLevelLayout(&OceanPalaceObjectList, "s02_P1.bin", "s02_DB.bin");
	
	LoadStageLight("stg13_light.bin");
	LoadStagePaths(OceanPalacePathList);
	LoadLevelMusic((char*)"oceanpalace.adx");
	LoadDeathZones(SeasideHillDeathZones);
	LoadFogData_Fogtask("stg13_fog.bin", (FogData*)0x1A280C8);

	LoadObject((LoadObj)0, "SKYBOX", OceanPalace_SkyBox, 1)->DisplaySub = OceanPalace_SkyBox;
	LoadObject(LoadObj_Data1, "OP BOULDERS", OPBoulders, 2);

	LoadTextureList("s02w", (NJS_TEXLIST*)&HeroesWater_TexList);

	OP_WATERFS = LoadMDL("OP_WATERFS", ModelFormat_Chunk);
	OP_FLOWERS = LoadMDL("OP_FLOWERS", ModelFormat_Chunk);
	OP_TURFINS = LoadMDL("OP_TURFINS", ModelFormat_Chunk);
	OP_BOULDER = LoadMDL("OP_BOULDER", ModelFormat_Chunk);
	OP_POLFLAG = LoadMDL("OP_POLFLAG", ModelFormat_Chunk);
	OP_SKYMDLS = LoadMDL("OP_SKYMDLS", ModelFormat_SA2B);
	OP_LNDFALL = LoadMDL("OP_LNDFALL", ModelFormat_Chunk);
	OP_SCENARY = LoadMDL("OP_SCENARY", ModelFormat_Chunk);
	OP_LNDFALLCOL = LoadMDL("OP_LNDFALL", ModelFormat_Basic);
}

void OceanPalaceDelete() {
	FreeMDL(OP_TURFINS);
	FreeMDL(OP_POLFLAG);
	FreeMDL(OP_FLOWERS);
	FreeMDL(OP_BOULDER);
	FreeMDL(OP_WATERFS);
	FreeMDL(OP_SKYMDLS);
	FreeMDL(OP_LNDFALL);
	FreeMDL(OP_LNDFALLCOL);

	FreeTexList((NJS_TEXLIST*)&HeroesWater_TexList);
	CommonLevelDelete();
}

void OceanPalace_Init(const char *path, const HelperFunctions &helperFunctions) {
	MetalHarborHeader.Init = OceanPalace_Load;
	MetalHarborHeader.subprgmanager = OceanPalace_Main;
	MetalHarborHeader.anonymous_2 = OceanPalaceDelete;
	MetalHarbor2PHeader.Init = OceanPalace_Load;
	MetalHarbor2PHeader.subprgmanager = OceanPalace_Main;
	MetalHarbor2PHeader.anonymous_2 = OceanPalaceDelete;
	SetStartEndPoints(helperFunctions, &op_startpos, &op_2pintro, &op_endpos, &op_endpos23);
	op_startpos.Level = LevelIDs_MetalHarbor2P;
	op_endpos.Level = LevelIDs_MetalHarbor2P;
	op_endpos23.Level = LevelIDs_MetalHarbor2P;
	op_2pintro.Level = LevelIDs_MetalHarbor2P;
	SetStartEndPoints(helperFunctions, &op_startpos, &op_2pintro, &op_endpos, &op_endpos23);
}