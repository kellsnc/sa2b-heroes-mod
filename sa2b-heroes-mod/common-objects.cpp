#include "stdafx.h"

NJS_TEXNAME heroescmn_texname[91];
NJS_TEXLIST heroescmn_texlist = { arrayptrandlengthT(heroescmn_texname, Uint32) };

static ModelInfo* CO_DSHHOOP;
static ModelInfo* CO_COMNFAN;
static ModelInfo* CO_COMNFANCOL;

static void __cdecl DashHoop_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(&heroescmn_texlist);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawSA2BModel(model->sa2bmodel);
	DrawSA2BModel(model->child->sa2bmodel);
	DrawSA2BModel(model->child->sibling->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl DashHoop_Perform(ObjectMaster *obj)
{
	auto entity = obj->Data1.Entity;
	auto player = MainCharObj1[entity->Index];
	
	entity->Rotation.z += 1;
	float s = (float)(entity->Rotation.z * 0.025f);

	if (s >= 1)
	{
		DeleteObject_(obj);
		return;
	}
	
	TransformSpline(&player->Position, &entity->Position, &entity->Scale, s);
}

static void __cdecl DashHoop_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		auto data = obj->Data1.Entity;

		if (data->Action == 0)
		{
			int id = IsPlayerInsideSphere(&data->Position, 60);

			if (id)
			{
				PlaySoundProbably(4099, 0, 0, 0);
				data->Action = 30;

				MainCharObj2[id - 1]->Speed.x /= 2;
				MainCharObj2[id - 1]->Speed.y = 0;
				MainCharObj2[id - 1]->Speed.z = 0;
				
				AddScore(5);

				ObjectMaster * obj = LoadObject(4, "DashHoop_Perform", DashHoop_Perform, LoadObj_Data1);
				obj->Data1.Entity->Index = id - 1;
				obj->Data1.Entity->Position = data->Position;
				obj->Data1.Entity->Scale = data->Scale;
			}
		}
		else
		{
			--data->Action;
		}
	}
}

void __cdecl DashHoop(ObjectMaster* obj)
{
	obj->Data1.Entity->Rotation = fPositionToRotation(&obj->Data1.Entity->Position, &obj->Data1.Entity->Scale);
	obj->DisplaySub = DashHoop_Display;
	obj->MainSub = DashHoop_Main;

	obj->field_4C = reinterpret_cast<void*>(CO_DSHHOOP->getmodel());
}

bool Fans_IsSpecificPlayerInCylinder(EntityData1* entity, NJS_VECTOR* center, float radius, float height)
{
	auto pos = &entity->Position;

	if ((powf(pos->x - center->x, 2) + pow(pos->z - center->z, 2)) <= pow(radius, 2) &&
		pos->y > center->y && pos->y < center->y + height * 40)
	{
		return true;
	}

	return false;
}

static void __cdecl ObjFan_Display(ObjectMaster *obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(&heroescmn_texlist);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY_(data->Rotation.y + 0x4000);
	DrawSA2BModel(CO_COMNFAN->getmodel()->sa2bmodel);
	njRotateY_(static_cast<Angle>(data->Scale.z));
	DrawSA2BModel(CO_COMNFAN->getmodel()->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl ObjFan_Main(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;

	if (!ClipSetObject(obj))
	{
		data->Scale.z += data->Scale.y;

		if (MainCharObj1[0])
		{
			if (Fans_IsSpecificPlayerInCylinder(MainCharObj1[0], &data->Position, 45.5f, data->Scale.x))
			{
				data->Index = 20;
			}

			if (data->Index != 0)
			{
				MainCharObj2[0]->Speed.y = 2.5f;
				MainCharObj1[0]->Status |= 0x1000;
				MainCharObj1[0]->NextAction = 8;
				data->Index -= 1;
			}
		}

		if (MainCharObj1[1])
		{
			if (Fans_IsSpecificPlayerInCylinder(MainCharObj1[1], &data->Position, 45.5f, data->Scale.x))
			{
				data->field_2 = 20;
			}
			else
			{
				data->field_2 = 0;
			}

			if (data->field_2 != 0)
			{
				MainCharObj2[1]->Speed.y = 2.5f;
				MainCharObj1[1]->Status |= 0x1000;
				MainCharObj1[1]->NextAction = 8;
				data->field_2 -= 1;
			}
		}
	}
}

void __cdecl ObjFan(ObjectMaster *obj)
{
	auto data = obj->Data1.Entity;
	auto dynobj = GetFreeDyncolObjectEntry();

	memcpy(dynobj, CO_COMNFANCOL->getmodel(), sizeof(NJS_OBJECT));

	dynobj->pos[0] = data->Position.x;
	dynobj->pos[1] = data->Position.y;
	dynobj->pos[2] = data->Position.z;
	dynobj->ang[1] = data->Rotation.y;
	dynobj->evalflags = 0xFFFFFFF8;

	DynCol_Add(SurfaceFlag_Solid, obj, dynobj);

	obj->EntityData2 = reinterpret_cast<UnknownData2*>(dynobj);
	obj->field_4C = reinterpret_cast<void*>(CO_COMNFAN->getmodel());

	obj->DeleteSub = ObjectFunc_DynColDelete;
	obj->MainSub = ObjFan_Main;
	obj->DisplaySub = ObjFan_Display;
}

void __cdecl RingGroup(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;

	if (data->Scale.z)
	{
		ClipSetObject(obj);
		return;
	}
	
	data->Scale.z = data->Scale.y;
	data->Scale.y = data->Scale.x;
	data->Scale.x = data->Scale.z;
	data->Scale.z = data->Scale.y;

	NJS_VECTOR dir = { 0, 0, 20 * data->Scale.y };

	njPushUnitMatrix();
	NJS_VECTOR* pos = &data->Position;
	njTranslateV(_nj_current_matrix_ptr_, pos);
	njRotateZ(_nj_current_matrix_ptr_, data->Rotation.z);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
	njCalcPoint(_nj_current_matrix_ptr_, &data->Position, &dir, false);
	njPopMatrixEx();

	obj->MainSub = reinterpret_cast<ObjectFuncPtr>(RingLinearMain);
	obj->MainSub(obj);
}

void __cdecl DashRampAdjust(ObjectMaster* obj)
{
	obj->Data1.Entity->Scale.x /= 2;
	obj->Data1.Entity->Scale.y /= 1.5f;

	obj->MainSub = reinterpret_cast<ObjectFuncPtr>(DashRamp_Main);
	obj->MainSub(obj);
}

void __cdecl Beetle_Stationary(ObjectMaster* obj)
{
	auto entity = obj->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0xC1;
	entity->Scale = { 0.10f, 3.5f, 51.0f };
	obj->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void __cdecl Beetle_Attack(ObjectMaster* obj)
{
	auto entity = obj->Data1.Entity;
	entity->Rotation.x = 0x1;
	entity->Rotation.z = 0x1C0;
	entity->Scale = { 4, 1, 150 };
	obj->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void __cdecl Beetle_Electric(ObjectMaster* obj)
{
	auto entity = obj->Data1.Entity;
	entity->Rotation.x = 0;
	entity->Rotation.z = 0x101;
	entity->Scale = { 0.10f, 3.50f, 51.0f };
	obj->MainSub = (ObjectFuncPtr)Beetle_Main;
}

void __cdecl Robots(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		auto entity = obj->Data1.Entity;
		float height = (float)GetGroundHeight(entity->Position.x, entity->Position.y + 10.0f, entity->Position.z, &entity->Rotation);

		if (height > -999999.0f)
		{
			entity->Position.y = height;
			entity->Rotation.x = 0x1;
			entity->Rotation.z = 0x100;
			entity->Scale = { 0, 1, 126 };
			obj->MainSub = (ObjectFuncPtr)E_AI;

			if (MainCharObj1[1] && GetDistance(&entity->Position, &MainCharObj1[0]->Position) > GetDistance(&entity->Position, &MainCharObj1[1]->Position))
			{
				entity->Rotation.y = fPositionToRotation(&entity->Position, &MainCharObj1[1]->Position).y + 0x4000;
			}
			else
			{
				entity->Rotation.y = fPositionToRotation(&entity->Position, &MainCharObj1[0]->Position).y + 0x4000;
			}
		}
	}
}

struct breakerData1
{
	Float Xoff;
	Float Yoff;
	Rotation Rotation;
	NJS_VECTOR Position;
	NJS_VECTOR Scale;
	Float Zoff;
};

void Breaker_GetPoint(NJS_VECTOR* orig, Rotation* rot, NJS_VECTOR* dir)
{
	njPushUnitMatrix();
	njRotateZ(_nj_current_matrix_ptr_, rot->z);
	njRotateX(_nj_current_matrix_ptr_, rot->x);
	njRotateY(_nj_current_matrix_ptr_, rot->y);
	njCalcPoint(_nj_current_matrix_ptr_, dir, dir, true);
	njAddVector(dir, orig);
	njPopMatrixEx();
}

static void __cdecl ObjectBreaker_Delete(ObjectMaster* obj)
{
	obj->Data1.Entity->Collision = nullptr;
}

static void __cdecl ObjectBreaker_Display(ObjectMaster* obj)
{
	EntityData1* pdata = obj->Parent->Data1.Entity;
	breakerData1* data = (breakerData1*)obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	njSetTexture(CurrentLandTable->TextureList);

	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	
	njRotateZ(_nj_current_matrix_ptr_, pdata->Rotation.z);
	njRotateX(_nj_current_matrix_ptr_, pdata->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, pdata->Rotation.y);

	njTranslate(_nj_current_matrix_ptr_, data->Xoff, data->Yoff, data->Zoff);
	njTranslateY(-(pdata->Scale.z * 4));
	
	njRotateZ(_nj_current_matrix_ptr_, data->Rotation.z);
	njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);

	njScalef(pdata->Scale.x);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl ObjectBreaker_Main(ObjectMaster* obj)
{
	EntityData1* pdata = obj->Parent->Data1.Entity;
	breakerData1* data = (breakerData1*)obj->Data1.Entity;

	data->Rotation.x += 0x100 + rand() % 0x100;
	data->Rotation.y += 0x100 + rand() % 0x100;
	data->Rotation.z += 0x100 + rand() % 0x100;

	data->Position = GetPathPosition(&pdata->Position, &data->Scale, 1.0f + pdata->Scale.z / 10);
}

void __cdecl ObjBreaker(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	data->Scale.z += 1;
	data->Scale.x = fmax(0.0f, fabs(1 - (data->Scale.z / data->Scale.y)));

	if (data->Scale.z > data->Scale.y) {
		DeleteObject_(obj);
	}
}

void LoadBreaker(NJS_VECTOR* pos, Rotation* rot, NJS_OBJECT* object, Float Xoff, Float Yoff, Float Zoff, Float time)
{
	ObjectMaster* obj = LoadObject(5, "OBJ_BRK", ObjBreaker, LoadObj_Data1);
	EntityData1* data = obj->Data1.Entity;

	data->Position = *pos;
	data->Rotation = *rot;
	data->Scale.y = 1.0f;
	data->Scale.y = time;

	while (object) {
		ObjectMaster* part = LoadChildObject(LoadObj_Data1, ObjectBreaker_Main, obj);
		breakerData1* partdata = (breakerData1*)part->Data1.Entity;

		part->DisplaySub = ObjectBreaker_Display;
		part->DeleteSub = ObjectBreaker_Delete;
		part->field_4C = object;

		NJS_VECTOR dir = { object->pos[0], object->pos[1], object->pos[2] };

		Breaker_GetPoint(&data->Position, &data->Rotation, &dir);

		partdata->Scale = dir;
		partdata->Xoff = Xoff;
		partdata->Yoff = Yoff;
		partdata->Zoff = Zoff;

		object = object->sibling;
	}
}

void __cdecl ObjCannon(ObjectMaster* obj)
{

}

void __cdecl OBJCASE(ObjectMaster* obj)
{

}

void __cdecl e2000_Init(ObjectMaster* obj)
{

}

void __cdecl Flyer_Init(ObjectMaster* obj)
{

}

void __cdecl Flyer_Trigger(ObjectMaster* obj)
{

}

void __cdecl Laserdoor(ObjectMaster* obj)
{

}

void CommonObjects_LoadModels()
{
	LoadTextureList((char*)"heroescmn", &heroescmn_texlist);	
	LoadMDL(&CO_DSHHOOP, "CO_DSHHOOP", ModelFormat_SA2B);
	LoadMDL(&CO_COMNFAN, "CO_COMNFAN", ModelFormat_SA2B);
	LoadMDL(&CO_COMNFANCOL, "CO_COMNFAN", ModelFormat_Basic);
}

void CommonObjects_FreeModels() {
	FreeTexList(&heroescmn_texlist);

	FreeMDL(&CO_DSHHOOP);
	FreeMDL(&CO_COMNFAN);
	FreeMDL(&CO_COMNFANCOL);
}