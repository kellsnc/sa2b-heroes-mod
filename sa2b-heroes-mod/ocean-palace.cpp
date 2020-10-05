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

NJS_TEXNAME_ oceanpalace_texname[]{
	{ "tk1_sib2", 0, 0 },
	{ "s2_kao3", 0, 0 },
	{ "s2_kao2", 0, 0 },
	{ "s2_kao1", 0, 0 },
	{ "pm2_005", 0, 0 },
	{ "pm2_004", 0, 0 },
	{ "pm2_003", 0, 0 },
	{ "pm2_002", 0, 0 },
	{ "pm2_001", 0, 0 },
	{ "pk2_flo2", 0, 0 },
	{ "pk2_flo1", 0, 0 },
	{ "pk1_sib1", 0, 0 },
	{ "m2_sima9", 0, 0 },
	{ "m2_sima8", 0, 0 },
	{ "m2_sima7", 0, 0 },
	{ "m2_sima4", 0, 0 },
	{ "m2_sima3", 0, 0 },
	{ "m2_sima2", 0, 0 },
	{ "m2_sima1", 0, 0 },
	{ "m2_6003", 0, 0 },
	{ "m2_6002", 0, 0 },
	{ "m2_6001", 0, 0 },
	{ "m2_5002", 0, 0 },
	{ "m2_2021", 0, 0 },
	{ "m2_2020", 0, 0 },
	{ "m2_2019", 0, 0 },
	{ "m2_2018", 0, 0 },
	{ "m2_2017", 0, 0 },
	{ "m2_2016", 0, 0 },
	{ "m2_2015", 0, 0 },
	{ "m2_2014", 0, 0 },
	{ "m2_2013", 0, 0 },
	{ "m2_2012", 0, 0 },
	{ "m2_2011", 0, 0 },
	{ "m2_2010", 0, 0 },
	{ "m2_2009", 0, 0 },
	{ "m2_2008", 0, 0 },
	{ "m2_2007", 0, 0 },
	{ "m2_2006", 0, 0 },
	{ "m2_2005", 0, 0 },
	{ "m2_2004", 0, 0 },
	{ "m2_2002", 0, 0 },
	{ "m2_2001", 0, 0 },
	{ "m2_1014", 0, 0 },
	{ "m2_1013", 0, 0 },
	{ "m2_1012", 0, 0 },
	{ "m2_1011", 0, 0 },
	{ "m2_1010", 0, 0 },
	{ "m2_1009", 0, 0 },
	{ "m2_1008", 0, 0 },
	{ "m2_1007", 0, 0 },
	{ "m2_1006", 0, 0 },
	{ "m2_1005", 0, 0 },
	{ "m2_1004", 0, 0 },
	{ "m2_1003", 0, 0 },
	{ "m2_1002", 0, 0 },
	{ "m2_1001", 0, 0 },
	{ "m1_2011", 0, 0 },
	{ "m1_1012", 0, 0 },
	{ "m1_1011", 0, 0 },
	{ "m1_1010", 0, 0 },
	{ "m1_1007", 0, 0 },
	{ "m1_1004", 0, 0 },
	{ "k2_tika2", 0, 0 },
	{ "k2_tika1", 0, 0 },
	{ "k2_miti2", 0, 0 },
	{ "k2_miti1", 0, 0 },
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
	{ "k1_kame3", 0, 0 },
	{ "k1_kame2", 0, 0 },
	{ "k1_kame1", 0, 0 },
};

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
	DrawModel(model->basicmodel);
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
	DrawModel(model->basicmodel);

	if (data->Scale.x == 0) {
		DrawModel(shadow->basicmodel);
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

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawModel(model->basicmodel);
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
	DrawModel(model->basicmodel);
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
		DrawModel(object->basicmodel);
		njPopMatrix(1u);
	}

	njPushMatrix(0); {
		njTranslate(_nj_current_matrix_ptr_, 60, -20, -90);
		njRotateY(_nj_current_matrix_ptr_, -data->Rotation.z + 0x7000);
		njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
		DrawModel(object->child->basicmodel);
		njPopMatrix(1u);
	}

	njPushMatrix(0); {
		njTranslate(_nj_current_matrix_ptr_, -60, -15, 60);
		njRotateY(_nj_current_matrix_ptr_, data->Rotation.z - 0x7000);
		njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
		DrawModel(object->child->child->basicmodel);
		njPopMatrix(1u);
	}

	njPushMatrix(0); {
		njTranslate(_nj_current_matrix_ptr_, 60, -15, 60);
		njRotateY(_nj_current_matrix_ptr_, -data->Rotation.z + 0x7000);
		njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
		DrawModel(object->child->child->child->basicmodel);
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
			DrawModel(model->child->basicmodel);
			njPopMatrix(1);
		}

		njTranslate(_nj_current_matrix_ptr_, -2500, 0, 29000);
		njRotateX(_nj_current_matrix_ptr_, 0x4000);
		njScalef(2.0f);
		DrawModel(model->child->sibling->basicmodel);
		DrawModel(model->child->sibling->sibling->basicmodel);

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

			DrawModel(OP_BOULDER->getmodel()->basicmodel);
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

	DrawModel(OP_BOULDER->getmodel()->basicmodel);
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
	DrawModel(OP_SKYMDLS->getmodel()->basicmodel);
	DrawModel(OP_SKYMDLS->getmodel()->child->basicmodel);
	njPopMatrix(1u);
}

void OceanPalace_Main(ObjectMaster* obj) {
	
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

	OP_WATERFS = LoadMDL("OP_WATERFS");
	OP_FLOWERS = LoadMDL("OP_FLOWERS");
	OP_TURFINS = LoadMDL("OP_TURFINS");
	OP_BOULDER = LoadMDL("OP_BOULDER");
	OP_POLFLAG = LoadMDL("OP_POLFLAG");
	OP_SKYMDLS = LoadMDL("OP_SKYMDLS");
	OP_LNDFALL = LoadMDL("OP_LNDFALL");
	OP_SCENARY = LoadMDL("OP_SCENARY");
	OP_LNDFALLCOL = LoadCOLMDL("OP_LNDFALL");
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