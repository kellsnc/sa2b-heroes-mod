#include "stdafx.h"

NJS_TEXNAME heroescmn_texname[41];
NJS_TEXLIST heroescmn_texlist = { arrayptrandlengthT(heroescmn_texname, Uint32) };

ModelInfo * CO_DSHHOOP;
ModelInfo * CO_COMNFAN;

void DashHoop_Display(ObjectMaster* a1) {
	RenderInfo->CurrentTexlist = &heroescmn_texlist;
	njPushMatrix(0);
	njTranslate(_nj_current_matrix_ptr_, a1->Data1.Entity->Position.x, a1->Data1.Entity->Position.y, a1->Data1.Entity->Position.z);
	njRotateX(_nj_current_matrix_ptr_, a1->Data1.Entity->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, a1->Data1.Entity->Rotation.y + 0x4000);
	DrawModel(CO_DSHHOOP->getmodel()->basicmodel);
	njPopMatrix(1u);
}

void DashHoop_Perform(ObjectMaster *a1) {
	EntityData1* entity = a1->Data1.Entity;
	EntityData1* player = MainCharObj1[entity->Index];
	
	entity->Rotation.z += 1;
	float s = (float)entity->Rotation.z * 0.05f;

	if (s >= 1) {
		DeleteObject_(a1);
		return;
	}
	
	TransformSpline(player, entity->Position, entity->Scale, s);
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
	a1->Data1.Entity->Rotation = fPositionToRotation(a1->Data1.Entity->Position, a1->Data1.Entity->Scale);
	a1->DisplaySub = DashHoop_Display;
	a1->MainSub = DashHoop_Main;
}

void ObjFan_Display(ObjectMaster *a1)
{
	RenderInfo->CurrentTexlist = &heroescmn_texlist;
	njPushMatrix(0);
	njTranslate(_nj_current_matrix_ptr_, a1->Data1.Entity->Position.x, a1->Data1.Entity->Position.y, a1->Data1.Entity->Position.z);
	njRotateY(_nj_current_matrix_ptr_, a1->Data1.Entity->Rotation.y + 0x4000);
	DrawModel(CO_COMNFAN->getmodel()->basicmodel);
	njRotateY(_nj_current_matrix_ptr_, a1->Data1.Entity->Scale.z);
	DrawModel(CO_COMNFAN->getmodel()->child->basicmodel);
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

void Boxes(ObjectMaster* a1) {
	uint8_t type = a1->Data1.Entity->Scale.x;

	switch (type) {
	case 0:
		a1->MainSub = WoodenCrate_Main;
		break;
	case 1:
		a1->MainSub = IronCrate_Main;
		break;
	case 2:
		a1->MainSub = (ObjectFuncPtr)IronEggmanCrate;
		break;
	case 3:
		a1->MainSub = SOLIDBOX;
		break;
	}
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

void CommonObjects_LoadModels() {
	LoadTextureList((char*)"heroescmn", &heroescmn_texlist);	
	CO_DSHHOOP = LoadMDL("CO_DSHHOOP");
	CO_COMNFAN = LoadMDL("CO_COMNFAN");
}

void CommonObjects_FreeModels() {
	FreeTexList(&heroescmn_texlist);

	FreeMDL(CO_DSHHOOP);
	FreeMDL(CO_COMNFAN);
}