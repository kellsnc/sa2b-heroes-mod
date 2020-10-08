#include "stdafx.h"

NJS_TEXNAME heroescmn_texname[41];
NJS_TEXLIST heroescmn_texlist = { arrayptrandlengthT(heroescmn_texname, Uint32) };

ModelInfo * CO_DSHHOOP;
ModelInfo * CO_COMNFAN;

void DashHoop_Display(ObjectMaster* a1) {
	RenderInfo->CurrentTexlist = &heroescmn_texlist;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &a1->Data1.Entity->Position);
	njRotateX(_nj_current_matrix_ptr_, a1->Data1.Entity->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, a1->Data1.Entity->Rotation.y + 0x4000);
	DrawChunkModel(CO_DSHHOOP->getmodel()->basicmodel);
	njPopMatrix(1u);
}

void DashHoop_Perform(ObjectMaster *a1) {
	EntityData1* entity = a1->Data1.Entity;
	EntityData1* player = MainCharObj1[entity->Index];
	
	entity->Rotation.z += 1;
	float s = (float)(entity->Rotation.z * 0.025f);

	if (s >= 1) {
		DeleteObject_(a1);
		return;
	}
	
	TransformSpline(&player->Position, &entity->Position, &entity->Scale, s);
}

void DashHoop_Main(ObjectMaster* a1) {
	if (ClipSetObject(a1)) {
		if (!a1->Data1.Entity->Action) {
			uint8_t id = IsPlayerInsideSphere(&a1->Data1.Entity->Position, 60);
			if (id) {
				PlaySoundProbably(4099, 0, 0, 0);
				a1->Data1.Entity->Action = 30;

				MainCharObj2[id - 1]->Speed.x /= 2;
				MainCharObj2[id - 1]->Speed.y = 0;
				MainCharObj2[id - 1]->Speed.z = 0;
				
				AddScore(5);

				ObjectMaster * obj = LoadObject(4, "DashHoop_Perform", DashHoop_Perform, LoadObj_Data1);
				obj->Data1.Entity->Index = id - 1;
				obj->Data1.Entity->Position = a1->Data1.Entity->Position;
				obj->Data1.Entity->Scale = a1->Data1.Entity->Scale;
			}
		}
		else {
			--a1->Data1.Entity->Action;
		}
	}
}

void DashHoop(ObjectMaster* a1) {
	a1->Data1.Entity->Rotation = fPositionToRotation(&a1->Data1.Entity->Position, &a1->Data1.Entity->Scale);
	a1->DisplaySub = DashHoop_Display;
	a1->MainSub = DashHoop_Main;
}

void ObjFan_Display(ObjectMaster *a1)
{
	RenderInfo->CurrentTexlist = &heroescmn_texlist;
	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &a1->Data1.Entity->Position);
	njRotateY(_nj_current_matrix_ptr_, a1->Data1.Entity->Rotation.y + 0x4000);
	DrawChunkModel(CO_COMNFAN->getmodel()->basicmodel);
	njRotateY(_nj_current_matrix_ptr_, a1->Data1.Entity->Scale.z);
	DrawChunkModel(CO_COMNFAN->getmodel()->child->basicmodel);
	njPopMatrix(1u);
}

void ObjFan(ObjectMaster *obj)
{
	EntityData1* data = obj->Data1.Entity;
	
	if (data->Action == 0) {
		obj->DisplaySub = ObjFan_Display;
		data->Action = 1;
	}

	if (ClipSetObject(obj)) {
		data->Scale.z += data->Scale.y;

		int slot = IsPlayerInsideSphere(&data->Position, 45.0f);
		if (slot > 0) {
			EntityData1 *entity = MainCharObj1[slot - 1];
			CharObj2Base *co2 = MainCharObj2[slot - 1];
			if (co2 != NULL) {
				co2->Speed.x = 0; co2->Speed.z = 0;
				entity->Rotation.x = 0;
				entity->Rotation.z = 0;
				co2->Speed.y = data->Scale.x;
				co2->AnimInfo.Current = 23;
			}
		}
	}
}



void RingGroup(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;
	if (data->Scale.z) {
		ClipSetObject(obj);
		return;
	}
	
	data->Scale.z = data->Scale.y;
	data->Scale.y = data->Scale.x;
	data->Scale.x = data->Scale.z;
	data->Scale.z = data->Scale.y;

	NJS_VECTOR dir = { 0, 0, 20 * data->Scale.y };

	float* matrix = njPushUnitMatrix();
	NJS_VECTOR* pos = &data->Position;
	njTranslateV(matrix, pos);
	njRotateZ(matrix, data->Rotation.z);
	njRotateY(matrix, data->Rotation.y);
	njRotateX(matrix, data->Rotation.x);
	njCalcPoint(matrix, &data->Position, &dir, false);
	njPopMatrix(1u);

	obj->MainSub = (ObjectFuncPtr)RingLinearMain;
	obj->MainSub(obj);
}

void DashRampAdjust(ObjectMaster* obj) {
	obj->Data1.Entity->Scale.x /= 2;
	obj->Data1.Entity->Scale.y /= 1.5f;

	obj->MainSub = (ObjectFuncPtr)DashRamp_Main;
	obj->MainSub(obj);
}

void Beetle_Stationary(ObjectMaster* a1) {
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0xC1;
	entity->Scale = { 0.10, 3.50, 51 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void Beetle_Attack(ObjectMaster* a1) {
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0x1;
	entity->Rotation.z = 0x1C0;
	entity->Scale = { 4, 1, 150 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void Beetle_Electric(ObjectMaster* a1) {
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0x101;
	entity->Scale = { 0.10, 3.50, 51 };
	a1->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void Robots(ObjectMaster* a1) {
	EntityData1* entity = a1->Data1.Entity;
	entity->Rotation.x = 0x1;
	entity->Rotation.z = 0x100;
	entity->Scale = { 0, 1, 126 };
	a1->MainSub = (ObjectFuncPtr)E_AI;
}

void Breaker_GetPoint(NJS_VECTOR* orig, Rotation* rot, NJS_VECTOR* dir) {
	njPushUnitMatrix();
	njRotateZ(_nj_current_matrix_ptr_, rot->z);
	njRotateX(_nj_current_matrix_ptr_, rot->x);
	njRotateY(_nj_current_matrix_ptr_, rot->y);
	njCalcPoint(_nj_current_matrix_ptr_, dir, dir, true);
	njAddVector(dir, orig);
	njPopMatrix(1u);
}

void ObjectBreaker_Display(ObjectMaster* obj) {
	EntityData1* pdata = obj->Parent->Data1.Entity;
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	RenderInfo->CurrentTexlist = CurrentLandTable->TextureList;

	njPushMatrix(0);
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njTranslateY(pdata->Scale.x - (pdata->Scale.z * 4));

	njRotateZ(_nj_current_matrix_ptr_, pdata->Rotation.z);
	njRotateX(_nj_current_matrix_ptr_, pdata->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, pdata->Rotation.y);
	
	njRotateZ(_nj_current_matrix_ptr_, data->Rotation.z);
	njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);

	DrawSA2BModel(model->sa2bmodel);
	njPopMatrix(1);
}

void ObjectBreaker_Main(ObjectMaster* obj) {
	EntityData1* pdata = obj->Parent->Data1.Entity;
	EntityData1* data = obj->Data1.Entity;

	data->Rotation.x += 0x100 + rand() % 0x100;
	data->Rotation.y += 0x100 + rand() % 0x100;
	data->Rotation.z += 0x100 + rand() % 0x100;

	data->Position = GetPathPosition(&pdata->Position, &data->Scale, 1.0f + pdata->Scale.z / 10);
}

void ObjBreaker(ObjectMaster* obj) {
	EntityData1* data = obj->Data1.Entity;

	data->Scale.z += 1;

	if (data->Scale.z > data->Scale.y) {
		DeleteObject_(obj);
	}
}

void LoadBreaker(NJS_VECTOR* pos, Rotation* rot, NJS_OBJECT* object, Float Yoff, Float time) {
	ObjectMaster* obj = LoadObject(5, "OBJ_BRK", ObjBreaker, LoadObj_Data1);
	EntityData1* data = obj->Data1.Entity;

	data->Position = *pos;
	data->Rotation = *rot;
	data->Scale.x = Yoff;
	data->Scale.y = time;

	while (object) {
		ObjectMaster* part = LoadChildObject(LoadObj_Data1, ObjectBreaker_Main, obj);
		EntityData1* partdata = part->Data1.Entity;

		part->DisplaySub = ObjectBreaker_Display;
		part->field_4C = object;

		NJS_VECTOR dir = { object->pos[0], object->pos[1], object->pos[2] };

		Breaker_GetPoint(&data->Position, &data->Rotation, &dir);

		partdata->Scale = dir;

		object = object->sibling;
	}
}

void CommonObjects_LoadModels() {
	LoadTextureList((char*)"heroescmn", &heroescmn_texlist);	
	CO_DSHHOOP = LoadMDL("CO_DSHHOOP", ModelFormat_Chunk);
	CO_COMNFAN = LoadMDL("CO_COMNFAN", ModelFormat_Chunk);
}

void CommonObjects_FreeModels() {
	FreeTexList(&heroescmn_texlist);

	FreeMDL(CO_DSHHOOP);
	FreeMDL(CO_COMNFAN);
}