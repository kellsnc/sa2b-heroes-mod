#include "stdafx.h"

NJS_TEXNAME heroescmn_texname[41];
NJS_TEXLIST heroescmn_texlist = { arrayptrandlengthT(heroescmn_texname, Uint32) };

TexPackInfo heroestexpacks[] = {
	{ "heroescmn", &heroescmn_texlist },
	{ "heroescmn", &heroescmn_texlist },
	{ 0 }
};

NJS_TEXLIST **copylist = { nullptr };

ModelInfo * CO_DSHHOOP;

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
	EntityData1* parent = a1->Child->Data1.Entity;
	EntityData1* player = MainCharObj1[entity->Index];

	entity->Scale.y += 0.05f;

	if (entity->Scale.y >= 1) {
		a1->Child = nullptr;
		DeleteObject_(a1);
		return;
	}

	TransformSpline(player, parent->Position, parent->Scale, entity->Scale.y);
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
				obj->Child = a1;
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

	switch (CurrentLevel) {
	case 13:
		WriteData((NJS_TEXLIST****)0x5DCE6C, &copylist);
		WriteData((TexPackInfo**)0x5DCE71, static_cast<TexPackInfo*>(heroestexpacks));
		WriteData((NJS_TEXLIST****)0x5DD3E4, &copylist);
		WriteData((TexPackInfo**)0x5DD3E9, static_cast<TexPackInfo*>(heroestexpacks));
		break;
	}
	
	CO_DSHHOOP = LoadMDL("CO_DSHHOOP");
}

void CommonObjects_FreeModels() {
	FreeTexList(&heroescmn_texlist);

	FreeMDL(CO_DSHHOOP);
}