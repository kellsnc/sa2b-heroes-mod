#include "stdafx.h"
#include "ocean-palace-paths.h"
#include "ocean-palace.h"

static ModelInfo * OP_WATERFS;
static ModelInfo * OP_FLOWERS;
static ModelInfo * OP_TURFINS;
static ModelInfo * OP_BOULDER;
static ModelInfo * OP_POLFLAG;
static ModelInfo * OP_SKYMDLS;
static ModelInfo * OP_LNDFALL;
static ModelInfo * OP_SCENARY;
static ModelInfo * OP_BRBLOCK;
static ModelInfo * OP_BRKBARS;
static ModelInfo * OP_PLATFOR;
static ModelInfo * OP_BRKDOOR;
static ModelInfo * OP_LNDFALLCOL;

static NJS_TEXLIST_ oceanpalace_texlist = { arrayptrandlength(oceanpalace_texname) };

static CollisionData Col_OPBreakBlock = { 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 10.0f, 17.5f, 0 }, 30.0f, 30.0f, 20.0f, 0, 0, 0, 0 };
static CollisionData Col_OPBreakDoor = { 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 0, 50.0f, -43.75f }, 40.0f, 100.0f, 10.0f, 0, 0, 0, 0 };

static CollisionData Col_OPBlocks[] = {
	{ 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { -40.0f, 25.0f , 0 }, 30.0f, 30.0f, 20.0f, 0, 0, 0, 0 },
	{ 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 40.0f, 25.0f, 0 }, 30.0f, 30.0f, 20.0f, 0, 0, 0, 0 },
	{ 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 0, 25.0f, 0 }, 80.0f, 30.0f, 20.0f, 0, 0, 0, 0 }
};

static CollisionData Col_OPPillar[] = {
	{ 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { 60.0f, 32.8f, 0 }, 12.5f, 25.0f, 12.5f, 0, 0, 0, 0 },
	{ 0, CollisionShape_Cube1, 0x77, 0xE0, 0, { -60.0f, 32.8f, 0 }, 12.5f, 25.0f, 12.5f, 0, 0, 0, 0 }
};

extern CollisionData Col_Pole;
extern CollisionData Col_Platform;

static void __cdecl OPFlowers_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OPFlowers(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;

	obj->field_4C = reinterpret_cast<void*>(OP_FLOWERS->getmodel()->child);

	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = OPFlowers_Display;
}

static void __cdecl OPFlant_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.y);
	DrawSA2BModel(model->sa2bmodel);

	if (data->Scale.x == 0)
	{
		DrawSA2BModel(model->child->sa2bmodel);
	}
	
	njPopMatrixEx();
}

static void __cdecl OPPlant(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;

	obj->field_4C = reinterpret_cast<void*>(OP_FLOWERS->getmodel()->child->sibling);

	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = OPFlant_Display;
}

static void __cdecl OPWater_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(reinterpret_cast<NJS_TEXLIST*>(&HeroesWater_TexList));
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OPWater(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;

	obj->field_4C = reinterpret_cast<void*>(GetChildModelByIndex(OP_WATERFS->getmodel(), static_cast<int>(data->Scale.x)));
	
	Play3DSound_EntityPosBank(obj->Data1.Entity, 7, &obj->Data1.Entity->Position, 50, 7);

	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub_Delayed1 = OPWater_Display;
}

static void __cdecl OPFallingStructure_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawObject(model, ModelFormat_SA2B);
	njPopMatrixEx();
}

static void __cdecl OPFallingStructure(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto dynobj = GetFreeDyncolObjectEntry();

	memcpy(dynobj, OP_LNDFALLCOL->getmodel(), sizeof(NJS_OBJECT));

	dynobj->pos[0] = data->Position.x;
	dynobj->pos[1] = data->Position.y;
	dynobj->pos[2] = data->Position.z;
	dynobj->ang[1] = data->Rotation.y;
	dynobj->evalflags = 0xFFFFFFF8;

	DynCol_Add(SurfaceFlag_Solid, obj, dynobj);

	obj->EntityData2 = reinterpret_cast<UnknownData2*>(dynobj);
	obj->field_4C = reinterpret_cast<void*>(OP_LNDFALL->getmodel());

	obj->DeleteSub = ObjectFunc_DynColDelete;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = OPFallingStructure_Display;
}

static void __cdecl OPPOLE_Display(ObjectMaster *obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OPPOLE_DisplayAlpha(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C)->child;

	njSetTexture(reinterpret_cast<NJS_TEXLIST*>(&HeroesWater_TexList));
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OPPOLE(ObjectMaster *obj)
{
	auto data = obj->Data1.Entity;

	InitCollision(obj, &Col_Pole, 1, 4);

	obj->field_4C = reinterpret_cast<void*>(GetSiblingModelByIndex(OP_POLFLAG->getmodel()->child, static_cast<int>(data->Scale.x)));

	obj->MainSub = MainSub_Collision;
	obj->DisplaySub = &OPPOLE_Display;
	obj->DisplaySub_Delayed1 = &OPPOLE_DisplayAlpha;
}

static inline void DrawFin(NJS_OBJECT* object, Uint32 Yrot, Uint32 Xrot)
{
	njPushMatrixEx();
	njTranslate(_nj_current_matrix_ptr_, object->pos[0], object->pos[1], object->pos[2]);

	if (object->ang[1] > 0)
	{
		njRotateY(_nj_current_matrix_ptr_, Yrot + (object->ang[1] - 0x3000));
	}
	else
	{
		njRotateY(_nj_current_matrix_ptr_, Yrot + (object->ang[1] + 0x3000));
	}

	njRotateX(_nj_current_matrix_ptr_, Xrot);
	DrawSA2BModel(object->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OPFins_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.x);

	DrawFin(model, data->Rotation.z, data->Rotation.x);
	DrawFin(model->sibling, -data->Rotation.z, data->Rotation.x);
	DrawFin(model->sibling->sibling, data->Rotation.z, data->Rotation.x);
	DrawFin(model->sibling->sibling->sibling, -data->Rotation.z, data->Rotation.x);

	njPopMatrixEx();
}

static void __cdecl OPFins_Main(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	
	if (!ClipSetObject(obj))
	{
		data->field_6++;

		if (data->Action == 0)
		{
			data->Scale.z += data->Scale.y / 2;

			if (data->Scale.z >= 1.0f)
			{
				data->Action = 1;
			}

			data->Rotation.z = 10000 - static_cast<Angle>(data->Scale.z * 20000.0f);
			data->Rotation.x = 5000 - static_cast<Angle>(data->Scale.z * 10000.0f);
		}
		else
		{
			data->Scale.z -= data->Scale.y / 2;

			data->Rotation.z = 10000 - static_cast<Angle>(data->Scale.z * 20000.0f);
			data->Rotation.x = 5000 - static_cast<Angle>(data->Scale.z * 10000.0f);

			if (data->Scale.z <= 0.0f)
			{
				data->Action = 0;
				data->Scale.z = 0.0f;
			}
		}
	}
}

static void __cdecl OPFins(ObjectMaster* obj)
{
	obj->field_4C = reinterpret_cast<void*>(OP_TURFINS->getmodel()->child);
	obj->MainSub = OPFins_Main;
	obj->DisplaySub = OPFins_Display;
}

static void __cdecl OPLandMove_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto playerid = static_cast<int>(data->Scale.x);

	if (CurrentScreen == playerid)
	{
		auto chunk = CurrentChunk[playerid];

		if (chunk > 6)
		{
			return;
		}

		auto data = obj->Data1.Entity;
		auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

		njSetTexture(CurrentLevelTexList);
		njPushMatrixEx();
		njTranslate(_nj_current_matrix_ptr_, 2100, 0, -44000);
		njTranslateZ(data->Scale.y);

		njPushMatrixEx();
		{
			njScalef(2.0f);
			DrawSA2BModel(model->sa2bmodel);
			njPopMatrixEx();
		}

		njTranslate(_nj_current_matrix_ptr_, -2500, 0, 29000);
		njScalef(2.0f);
		DrawSA2BModel(model->sibling->sa2bmodel);
		DrawSA2BModel(model->sibling->sibling->sa2bmodel);

		njPopMatrixEx();
	}
}

static void __cdecl OPLandMove_Main(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto playerid = static_cast<int>(data->Scale.x);
	auto chunk = CurrentChunk[playerid];

	if (!MainCharObj1[playerid] || MainCharObj1[playerid]->Position.z < -31200.0f)
	{
		DeleteObject_(obj);
		return;
	}

	if (data->Action == 0)
	{
		if (chunk == 5)
		{
			obj->DisplaySub = OPLandMove_Display;
			data->Action = 1;
		}
	}
	else if (data->Action == 1)
	{
		if (IsPlayerIDInsideSphere(2100.0f, 280.0f, -30300.0f, 100.0f, playerid))
		{
			data->Action = 2;
		}

		if (data->Scale.y < 8800.0f)
		{
			data->Scale.y += 2.5f;
		}
	}
	else
	{
		CameraScreensInfoArray[playerid]->pos = { 2360.0f, 112.0f, -31000.0f };
	}
}

static void __cdecl OPLandMove(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;

	if (!MainCharObj1[static_cast<int>(data->Scale.x)])
	{
		DeleteObject_(obj);
		return;
	}

	obj->field_4C = OP_SCENARY->getmodel()->child;
	obj->MainSub = OPLandMove_Main;
}

static void __cdecl BoulderPath(ObjectMaster *obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->Parent->field_4C);
	auto loopdata = &OP_BoulderPaths[data->Index];

	if (data->Action == 0)
	{
		obj->DisplaySub = obj->MainSub;
		obj->MainSub = nullptr;
		data->Action = 1;
	}
	else 
	{
		if (data->field_6 < loopdata->Count)
		{
			if (GameState != GameStates_Pause)
			{
				data->Scale.x = data->Scale.x + (loopdata->TotalDistance / loopdata->Points[data->field_6].Distance) / loopdata->TotalDistance * 7;

				auto pos1 = loopdata->Points[data->field_6].Position;
				auto pos2 = loopdata->Points[data->field_6 + 1].Position;

				NJS_VECTOR fixoffset = { 9000, -1.8f, 2900 };

				njAddVector(&pos1, &fixoffset);
				njAddVector(&pos2, &fixoffset);

				TransformSpline(&data->Position, &pos1, &pos2, data->Scale.x);
				if (loopdata->Points[data->field_6].YRot != 0) data->Rotation.y = loopdata->Points[data->field_6].YRot;
				if (data->Scale.x > 1) { data->Scale.x = 0; data->field_6++; }
				data->Rotation.x += 1500;

				data->Status = IsPlayerInsideSphere(&data->Position, 130.0f);

				if (data->Status)
				{
					int player = data->Status - 1;
					auto ed1 = MainCharObj1[player];
					auto co2 = MainCharObj2[player];

					GameState = GameStates_RestartLevel_1;

					ed1->Rotation.y = data->Rotation.y + 0x4000;
					co2->Speed.x = 22;
					co2->Speed.y = 2;
				}
			}

			njSetTexture(CurrentLevelTexList);
			njPushMatrixEx();

			njTranslateV(_nj_current_matrix_ptr_, &data->Position);
			njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
			njRotateX(_nj_current_matrix_ptr_, data->Rotation.x);

			DrawSA2BModel(model->sa2bmodel);
			njPopMatrixEx();
		}
		else
		{
			DeleteObject(obj);
		}
	}
}

static void __cdecl OPBoulders_Display(ObjectMaster *obj)
{
	if (CurrentChunk[0] < 6) return;

	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslate(_nj_current_matrix_ptr_, 9000, -1.8f, 2900);

	switch (data->Action)
	{
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

	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OPBoulders(ObjectMaster *obj)
{
	if (CurrentChunk[0] < 6)
	{
		return;
	}

	auto data = obj->Data1.Entity;

	switch (data->Action)
	{
	case 0:
		obj->DisplaySub = OPBoulders_Display;
		obj->field_4C = reinterpret_cast<void*>(OP_BOULDER->getmodel());
		data->Action = 1;
		break;
	case 1:
		if (IsPlayerInsideSphere(800.0f, 1399.2f, -37145.0f, 45.0f) == 1)
		{
			data->Action = 2;
			LoadChildObject(LoadObj_Data1, BoulderPath, obj);
		}

		break;
	case 2:
		if (obj->Child->Data1.Entity->Position.z < -42054.0f)
		{
			data->Action = 3;

			LoadChildObject(LoadObj_Data1, BoulderPath, obj)->Data1.Entity->Index = 1;
		}

		break;
	case 3:
		if (obj->Child->Data1.Entity->Position.z < -43683.0f)
		{
			data->Action = 0;

			LoadChildObject(LoadObj_Data1, BoulderPath, obj)->Data1.Entity->Index = 2;
		}

		break;
	}
}

NJS_VECTOR pos;

static void __cdecl BoulderCam(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	
	if (IsPlayerInsideSphere(&data->Position, data->Scale.y))
	{
		if (data->Scale.x == 8)
		{
			pos = OP_BoulderPaths[0].Points[10].Position;
			data->field_6 = 10;
			data->Scale.z = 0;
			data->Action = 1;
		}
		else
		{
			data->Action = 0;
			data->field_6 = 0;
		}
	}

	if (data->Action == 1)
	{
		LoopHead* loopdata = &OP_BoulderPaths[0];

		if (data->field_6 == 79) return;

		float dist = GetDistance(&pos, &MainCharObj1[0]->Position);
		float speed = (1 - (dist / 500)) * 24;
		if (speed < 0) speed = 0;

		data->Scale.z = data->Scale.z + (loopdata->TotalDistance / loopdata->Points[data->field_6].Distance) / loopdata->TotalDistance * speed;

		auto pos1 = loopdata->Points[data->field_6].Position;
		auto pos2 = loopdata->Points[data->field_6 + 1].Position;

		NJS_VECTOR fixoffset = { 9000, -1.8f, 2900 };

		njAddVector(&pos1, &fixoffset);
		njAddVector(&pos2, &fixoffset);
		
		TransformSpline(&CameraData.Position, &pos1, &pos2, data->Scale.z);
		CameraData.Position.y -= 50;
		if (loopdata->Points[data->field_6].YRot != 0) data->Rotation.y = loopdata->Points[data->field_6].YRot;
		if (data->Scale.z > 1) { data->Scale.z = 0; data->field_6++; }
		pos = CameraData.Position;
	}
}

static void __cdecl OPPillarBlock_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);
	int id = data->Rotation.x;

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);

	// Shadow
	njPushMatrixEx();
	njTranslateX(model->sibling->sibling->pos[0]);
	DrawSA2BModel(model->sibling->sibling->sa2bmodel);
	njPopMatrixEx();

	// Block
	njTranslateX(model->pos[0]);
	njTranslateY(data->Scale.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OPPillarBlock_Main(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto pdata = obj->Parent->Data1.Entity;

	if (data->Action == 0)
	{
		if (pdata->Action == 1)
		{
			data->Scale.y -= 1.0f;

			if (data->Scale.y <= 7.8f)
			{
				data->Scale.y = 7.8f;
				data->Action = 1;
			}

			data->Collision->CollisionArray[0].center.y = Col_OPPillar[0].center.y + data->Scale.y - 7.8f;
		}
	}
	else
	{
		auto player = GetCollidingPlayer(obj);

		if (player && player->Data1.Entity->Status & Status_Attack && player->Data1.Entity->Position.y < data->Position.y + 30)
		{
			NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;
			model = model->sibling->child;

			LoadBreaker(&data->Position, &data->Rotation, model, 0.0f, 0.0f, 0.0f, 120);
			Play3DSound_Vector(4100, &data->Position, 0, 0, 70);
			DeleteObject_(obj);
			return;
		}
	}

	AddToCollisionList(obj);
}

static void LoadPillarBlock(ObjectMaster* obj, NJS_OBJECT* object, int id)
{
	auto child = LoadChildObject(LoadObj_Data1, OPPillarBlock_Main, obj);

	child->field_4C = object;
	child->Data1.Entity->Scale.y = object->pos[1];
	child->DisplaySub = OPPillarBlock_Display;

	InitCollision(child, &Col_OPBlocks[id], 1, 4);
	child->Data1.Entity->Collision->CollisionArray[0].center.y += child->Data1.Entity->Scale.y - 7.8f;
}

static void __cdecl OPPillar_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);
	int id = data->Rotation.x;

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njTranslateY(7.8f);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);

	if (id == 2 || id == 0)
	{
		DrawSA2BModel(model->sa2bmodel);
	}

	if (id == 2 || id == 1)
	{
		DrawSA2BModel(model->sibling->sa2bmodel);
	}
	
	njPopMatrixEx();
}

static void __cdecl OPPillar_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		auto entity = obj->Data1.Entity;
		
		if (entity->Action == 0)
		{
			auto player = GetCollidingPlayer(obj);

			if (IsPlayerInsideSphere(&entity->Scale, 150.0f) || (player && player->Data1.Entity->Status & Status_Attack))
			{
				auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);
				model = model->sibling->sibling->child;

				NJS_VECTOR pos = entity->Position;

				LoadBreaker(&pos, &entity->Rotation, model, -60.0f, 35.0f, 0.0f, 120);
				LoadBreaker(&pos, &entity->Rotation, model, 60.0f, 35.0f, 0.0f, 120);

				Play3DSound_Vector(4100, &entity->Position, 0, 0, 70);

				obj->DisplaySub = nullptr;
				entity->Action = 1;
			}

			AddToCollisionList(obj);
		}
		else
		{
			if (obj->Child == nullptr)
			{
				UpdateSetDataAndDelete(obj);
			}
		}
	}
}

static void __cdecl OPPillar(ObjectMaster* obj)
{
	auto entity = obj->Data1.Entity;
	int id = entity->Rotation.x;

	if (id == 0)
	{
		InitCollision(obj, &Col_OPPillar[1], 1, 4);
		LoadPillarBlock(obj, OP_BRBLOCK->getmodel()->child->sibling->child, id);
	}
	else if (id == 1)
	{
		InitCollision(obj, &Col_OPPillar[0], 1, 4);
		LoadPillarBlock(obj, OP_BRBLOCK->getmodel()->child->sibling->sibling->child, id);
	}
	else
	{
		InitCollision(obj, Col_OPPillar, 2, 4);
		LoadPillarBlock(obj, OP_BRBLOCK->getmodel()->child->child, id);
	}

	obj->field_4C = reinterpret_cast<void*>(OP_BRKBARS->getmodel()->child);

	obj->MainSub = OPPillar_Main;
	obj->DisplaySub = OPPillar_Display;
}

static void __cdecl OPBreakableBlock_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OPBreakableBlock_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		auto entity = obj->Data1.Entity;
		auto player = GetCollidingPlayer(obj);

		if (player && player->Data1.Entity->Status & Status_Attack && player->Data1.Entity->Position.y < entity->Position.y + 30)
		{
			auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);
			model = model->sibling->child;

			LoadBreaker(&entity->Position, &entity->Rotation, model, 0.0f, 15.0f, 0.0f, 30);
			Play3DSound_Vector(4100, &entity->Position, 0, 0, 70);
			UpdateSetDataAndDelete(obj);
		}

		AddToCollisionList(obj);
	}
}

static void __cdecl OPBreakableBlock(ObjectMaster* obj)
{
	auto entity = obj->Data1.Entity;
	auto id = static_cast<int>(entity->Scale.x);
	
	InitCollision(obj, &Col_OPBreakBlock, 1, 4);

	if (id == 0)
	{
		obj->field_4C = reinterpret_cast<void*>(OP_BRBLOCK->getmodel()->child->sibling->sibling->sibling->child);
	}
	else
	{
		obj->field_4C = reinterpret_cast<void*>(OP_BRBLOCK->getmodel()->child->sibling->sibling->sibling->sibling->child);
		entity->Collision->CollisionArray[0].center.x = -10.0f;
	}
	
	obj->MainSub = OPBreakableBlock_Main;
	obj->DisplaySub = OPBreakableBlock_Display;
}

static void __cdecl OPPlatforms_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njScalef(data->Scale.x);
	DrawSA2BModel(model->sa2bmodel);
	DrawSA2BModel(model->sibling->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OPPlatforms(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	InitCollision(obj, &Col_Platform, 1, 4);

	obj->field_4C = reinterpret_cast<void*>(OP_PLATFOR->getmodel()->child);
	data->Collision->CollisionArray[0].param1 *= data->Scale.x;
	data->Collision->CollisionArray[0].param2 *= data->Scale.x;
	data->Collision->CollisionArray[0].param3 *= data->Scale.x;

	obj->MainSub = MainSub_Collision;
	obj->DisplaySub = OPPlatforms_Display;
}

enum DoorActions {
	DOOR_STAGE1,
	DOOR_MOVE,
	DOOR_STAGE2,
	DOOR_OPEN,
	DOOR_END
};

static void __cdecl OPDoor_Display(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateV(_nj_current_matrix_ptr_, &data->Position);
	njRotateY(_nj_current_matrix_ptr_, data->Rotation.y);
	njTranslateZ(-data->Scale.y);

	if (data->Action == DOOR_STAGE1)
	{
		DrawSA2BModel(model->sa2bmodel);
	}
	else if (data->Action < DOOR_OPEN)
	{
		njTranslate(_nj_current_matrix_ptr_, model->sibling->child->pos[0], 0, model->sibling->child->pos[2]);
		DrawSA2BModel(model->sibling->child->sa2bmodel);

		njTranslateX(model->sibling->child->sibling->pos[0] * 2);
		DrawSA2BModel(model->sibling->child->sibling->sa2bmodel);
	}
	else
	{
		njPushMatrixEx();
		njTranslate(_nj_current_matrix_ptr_, model->sibling->child->pos[0], 0, model->sibling->child->pos[2]);
		njRotateY(_nj_current_matrix_ptr_, data->field_6);
		DrawSA2BModel(model->sibling->child->sa2bmodel);
		njPopMatrixEx();

		njTranslate(_nj_current_matrix_ptr_, model->sibling->child->sibling->pos[0], 0, model->sibling->child->sibling->pos[2]);
		njRotateY(_nj_current_matrix_ptr_, -data->field_6);
		DrawSA2BModel(model->sibling->child->sibling->sa2bmodel);
	}
	
	njPopMatrixEx();
}

static inline bool Door_GetCollision(ObjectMaster* obj)
{
	ObjectMaster* player = GetCollidingPlayer(obj);

	return player && player->Data1.Entity->Status & Status_Attack;
}

static void __cdecl OPDoor_Main(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		auto entity = obj->Data1.Entity;
		auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);
		
		switch (entity->Action)
		{
		case DOOR_STAGE1:
			if (Door_GetCollision(obj))
			{
				model = model->sibling->sibling->child;

				LoadBreaker(&entity->Position, &entity->Rotation, model, 0.0f, 30.0f, -43.0f, 90);
				LoadBreaker(&entity->Position, &entity->Rotation, model->sibling, -6.0f, 25.0f, -41.0f, 90);
				LoadBreaker(&entity->Position, &entity->Rotation, model->sibling, 11.0f, 20.0f, -40.0f, 90);

				Play3DSound_Vector(4100, &entity->Position, 0, 0, 70);

				entity->Action = DOOR_MOVE;
			}

			AddToCollisionList(obj);
			break;
		case DOOR_MOVE:
			if (entity->Scale.y < 60.0f)
			{
				entity->Scale.y += 2.5f;
			}
			else
			{
				entity->Scale.y = 60.0f;
				entity->Action = DOOR_STAGE2;
			}
			
			entity->Collision->CollisionArray[0].center.z = Col_OPBreakDoor.center.z - entity->Scale.y;
			AddToCollisionList(obj);
			break;
		case DOOR_STAGE2:
			if (Door_GetCollision(obj))
			{
				Play3DSound_Vector(4100, &entity->Position, 0, 0, 70);
				entity->Action = DOOR_OPEN;
			}

			AddToCollisionList(obj);
			break;
		case DOOR_OPEN:
			if (entity->field_6 < 0x3500)
			{
				entity->field_6 += 0x300;
			}
			else
			{
				entity->field_6 = 0x3500;
				entity->Action = DOOR_END;
			}

			break;
		}
	}
}

static void __cdecl OPDoor(ObjectMaster* obj)
{
	auto entity = obj->Data1.Entity;
	
	obj->field_4C = reinterpret_cast<void*>(OP_BRKDOOR->getmodel()->child);

	InitCollision(obj, &Col_OPBreakDoor, 1, 4);

	obj->MainSub = OPDoor_Main;
	obj->DisplaySub = OPDoor_Display;
}

static ObjectListEntry OceanPalaceObjectList_list[]
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
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 6460000, OPDoor },
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
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, OPPlatforms },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, OPPillar },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2460000, OPBreakableBlock },
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

static ObjectListHead OceanPalaceObjectList = { arraylengthandptr(OceanPalaceObjectList_list) };

static void __cdecl OceanPalace_SkyBox(ObjectMaster* obj)
{
	auto position = &CameraScreensInfoArray[CurrentScreen]->pos;

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslate(_nj_current_matrix_ptr_, position->x, 0.0f, position->z);
	DrawSA2BModel(OP_SKYMDLS->getmodel()->sa2bmodel);
	DrawSA2BModel(OP_SKYMDLS->getmodel()->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl OceanPalace_Main(ObjectMaster* obj)
{
	AnimateTexlist(&HeroesWater_TexList, 2, (Uint32*)&obj->Data1.Entity->Scale.x, (void**)&obj->field_4C);
}

static void __cdecl OceanPalace_Load()
{
	CurrentHeroesLevel = HeroesLevelIDs::OceanPalace;

	CommonLevelInit();
	
	LoadChunkFile("resource\\gd_pc\\s02_blk.bin");
	LoadLandTable("resource\\gd_pc\\s02.sa2lvl", LandTableFormat_SA2);
	LoadLevelTex((NJS_TEXLIST*)&oceanpalace_texlist, "s02");
	LoadTXCFile("resource\\gd_pc\\s02.txc");
	
	if (TwoPlayerMode == 1)
	{
		LoadLevelLayout(&OceanPalaceObjectList, "s02_2P.bin", "s02_DB.bin");
	}
	else
	{
		LoadLevelLayout(&OceanPalaceObjectList, "s02_P1.bin", "s02_DB.bin");
	}
	
	LoadStageLight("stg13_light.bin");
	LoadStagePaths(OceanPalacePathList);
	LoadLevelMusic((char*)"oceanpalace.adx");
	LoadDeathZones(SeasideHillDeathZones);
	LoadFogData_Fogtask("stg13_fog.bin", (FogData*)0x1A280C8);
	LoadStageSounds("se_ac_gf.mlt", (void*)0x8A0F60);

	LoadObject(0, "SKYBOX", OceanPalace_SkyBox, 0)->DisplaySub = OceanPalace_SkyBox;
	LoadObject(0, "OP BOULDERS", OPBoulders, LoadObj_Data1);

	LoadTextureList("s02w", (NJS_TEXLIST*)&HeroesWater_TexList);

	LoadMDL(&OP_WATERFS,"OP_WATERFS", ModelFormat_SA2B);
	LoadMDL(&OP_FLOWERS,"OP_FLOWERS", ModelFormat_SA2B);
	LoadMDL(&OP_TURFINS,"OP_TURFINS", ModelFormat_SA2B);
	LoadMDL(&OP_BOULDER,"OP_BOULDER", ModelFormat_SA2B);
	LoadMDL(&OP_POLFLAG,"OP_POLFLAG", ModelFormat_SA2B);
	LoadMDL(&OP_SKYMDLS,"OP_SKYMDLS", ModelFormat_SA2B);
	LoadMDL(&OP_LNDFALL,"OP_LNDFALL", ModelFormat_SA2B);
	LoadMDL(&OP_SCENARY,"OP_SCENARY", ModelFormat_SA2B);
	LoadMDL(&OP_BRBLOCK,"OP_BRBLOCK", ModelFormat_SA2B);
	LoadMDL(&OP_BRKBARS,"OP_BRKBARS", ModelFormat_SA2B);
	LoadMDL(&OP_PLATFOR,"OP_PLATFOR", ModelFormat_SA2B);
	LoadMDL(&OP_BRKDOOR,"OP_BRKDOOR", ModelFormat_SA2B);

	LoadMDL(&OP_LNDFALLCOL,"OP_LNDFALL", ModelFormat_Basic);
}

static void __cdecl OceanPalaceDelete()
{
	FreeMDL(&OP_TURFINS);
	FreeMDL(&OP_POLFLAG);
	FreeMDL(&OP_FLOWERS);
	FreeMDL(&OP_BOULDER);
	FreeMDL(&OP_WATERFS);
	FreeMDL(&OP_SKYMDLS);
	FreeMDL(&OP_LNDFALL);
	FreeMDL(&OP_BRBLOCK);
	FreeMDL(&OP_BRKBARS);
	FreeMDL(&OP_PLATFOR);
	FreeMDL(&OP_BRKDOOR);
	FreeMDL(&OP_LNDFALLCOL);

	FreeTexList((NJS_TEXLIST*)&HeroesWater_TexList);
	CommonLevelDelete();
}

void OceanPalace_Init(const char *path, const HelperFunctions &helperFunctions)
{
	MetalHarborHeader.Init = OceanPalace_Load;
	MetalHarborHeader.subprgmanager = OceanPalace_Main;
	MetalHarborHeader.Free = OceanPalaceDelete;

	MetalHarbor2PHeader.Init = OceanPalace_Load;
	MetalHarbor2PHeader.subprgmanager = OceanPalace_Main;
	MetalHarbor2PHeader.Free = OceanPalaceDelete;

	SetStartEndPoints(helperFunctions, &op_startpos, &op_2pintro, &op_endpos, &op_endpos23);

	op_startpos.Level = LevelIDs_MetalHarbor2P;
	op_endpos.Level = LevelIDs_MetalHarbor2P;
	op_endpos23.Level = LevelIDs_MetalHarbor2P;
	op_2pintro.Level = LevelIDs_MetalHarbor2P;
	SetStartEndPoints(helperFunctions, &op_startpos, &op_2pintro, &op_endpos, &op_endpos23);
}