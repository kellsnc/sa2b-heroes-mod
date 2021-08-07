#include "stdafx.h"
#include "egg-fleet.h"
#include "egg-fleet-paths.h"
#include "egg-fleet-deathzones.h"

static ModelInfo* EF_SKYMDLS;
static ModelInfo* EF_PROPPLR;
static ModelInfo* EF_EHELICE;
static ModelInfo* EF_EBIGFAN;
static ModelInfo* EF_ANTENNA;
static ModelInfo* EF_BARRIER;
static ModelInfo* EF_ENDRAIL;
static ModelInfo* EF_PIPLINE;
static ModelInfo* EF_PLTFRMS;
static ModelInfo* EF_DIRSGNS;
static ModelInfo* EF_OBJDOOR;
static ModelInfo* EF_EBIGFANCOL;
static ModelInfo* EF_PIPLINECOL;
static ModelInfo* EF_DIRSGNSCOL;

static NJS_TEXLIST_ eggfleet_texlist = { arrayptrandlength(eggfleet_texname) };

static CollisionData AntennaCol = { 0, CollisionShape_Sphere, 0x77, 0, 0, {0, 50.0f, 0}, 25.0f, 0, 0, 0, { 0 } };
static CollisionData EFBarrier_Col = { 0, CollisionShape_Cube2, 0x77, 0, 0x800400, {0, 6, 0}, 15.0f, 15.0f, 2.0f, 0, { 0 } };

static CollisionData EFPlatforms_Col[] = {
	{ 0, CollisionShape_Cube1, 0x77, 0, 0x800400, {0, -10.0f, 0}, 70.0f, 10.0f, 70.0f, 0, { 0 } },
	{ 0, CollisionShape_Cube1, 0x77, 0, 0x800400, {0, -50.0f, 0}, 150.0f, 50.0f, 40.0f, 0, { 0 } },
	{ 0, CollisionShape_Cube2, 0x77, 0, 0x800400, {0, 15.0f, -41.0f}, 150.0f, 15.0f, 1.0f, 0, { 0 } }
};

static CollisionData EFDoor_Col[] = {
	{ 0, CollisionShape_Cube2, 0x77, 0, 0x800400, {-85.0f, 85.0f, -10.0f}, 10.0f, 85.0f, 10.0f, 0, { 0 } },
	{ 0, CollisionShape_Cube2, 0x77, 0, 0x800400, {85.0f, 85.0f, -10.0f}, 10.0f, 85.0f, 10.0f, 0, { 0 } },
	{ 0, CollisionShape_Cube2, 0x77, 0, 0x800400, {0, 80.0f, -10.0F}, 75.0f, 80.0f, 10.0f, 0, { 0 } }
};

enum EFPlatformsActs {
	EFPlatformAct_Move,
	EFPlatformAct_Reach,
	EFPlatformAct_Still
};

enum EFDoorActs {
	EFDoorAction_CloseDoor,
	EFDoorAction_Closed,
	EFDoorAction_OpenDoor,
	EFDoorAction_Opened
};

static void __cdecl EFBigFan_Display(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY_(data->Rotation.y);
	DrawSA2BModel(model->sa2bmodel);
	njRotateY_(data->Scale.z);
	DrawSA2BModel(model->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl EFBigFan_DisplayAlpha(ObjectMaster* obj)
{
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY_(data->Rotation.y);
	DrawSA2BModel(model->child->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl EFBigFan_Main(ObjectMaster* obj){
	if (!ClipSetObject(obj))	{
		auto data = obj->Data1.Entity;

		if (MainCharObj1[0])		{
			if (Fans_IsSpecificPlayerInCylinder(MainCharObj1[0], &data->Position, 130.0f, data->Scale.x))			{
				data->Index = 20;
			}

			if (data->Index != 0)			{
				MainCharObj2[0]->Speed.y = 0.25f;
				MainCharObj1[0]->Status |= 0x1000;
				MainCharObj1[0]->NextAction = 8;
				MainCharObj1[0]->Position.y += 1.0f;
				data->Index -= 1;
			}
		}

		if (MainCharObj1[1])		{
			if (Fans_IsSpecificPlayerInCylinder(MainCharObj1[1], &data->Position, 130.0f, data->Scale.x))			{
				data->field_2 = 20;
			}
			else			{
				data->field_2 = 0;
			}

			if (data->field_2 != 0)			{
				MainCharObj2[1]->Speed.y = 0.25f;
				MainCharObj1[1]->Status |= 0x1000;
				MainCharObj1[1]->NextAction = 8;
				MainCharObj1[1]->Position.y += 1.0f;
				data->field_2 -= 1;
			}
		}

		data->Scale.z -= data->Scale.x * 80.0f;
	}
}

static void __cdecl EFBigFan(ObjectMaster* obj){
	auto data = obj->Data1.Entity;

	if (data->Scale.y != 1)	{
		obj->MainSub = ObjFan;
		data->Scale.y = data->Scale.x * 80.0f;
		return;
	}

	obj->DeleteSub = ObjectFunc_DynColDelete;
	obj->MainSub = EFBigFan_Main;
	obj->DisplaySub = EFBigFan_Display;
	obj->DisplaySub_Delayed1 = EFBigFan_DisplayAlpha;

	Play3DSound_EntityPosBank(obj->Data1.Entity, 7, &obj->Data1.Entity->Position, 50, 5);

	auto dynobj = GetFreeDyncolObjectEntry();

	memcpy(dynobj, EF_EBIGFANCOL->getmodel(), sizeof(NJS_OBJECT));

	dynobj->pos[0] = data->Position.x;
	dynobj->pos[1] = data->Position.y;
	dynobj->pos[2] = data->Position.z;
	dynobj->ang[1] = data->Rotation.y;
	dynobj->evalflags = 0xFFFFFFF8;

	DynCol_Add(SurfaceFlag_Solid, obj, dynobj);

	obj->EntityData2 = reinterpret_cast<UnknownData2*>(dynobj);
	obj->field_4C = reinterpret_cast<void*>(EF_EBIGFAN->getmodel());
}

static void __cdecl EFCannon(ObjectMaster* obj){

}

static void EFPlatforms_Move(EntityData1* data){
	NJS_VECTOR vec = { 0, 20 - (40 * (1.0 - powf(njSin(data->field_6), 2))), 0 };
	data->field_6 += 50;

	njPushUnitMatrix();
	njTranslateEx(&data->Scale);
	njRotateZXY(&data->Rotation);
	njCalcVector(_nj_current_matrix_ptr_, &data->Position, &vec, false);
	njPopMatrixEx();
}

static void EFPlatforms_Reach(EntityData1* data){
	if (data->NextAction == 0)	{
		float sin = 1.0f - powf(njSin(data->field_6), 2);
		data->field_6 += 1;

		NJS_VECTOR vec = { 0, 100 * sin, 0 };

		if (sin >= 1.0f)		{
			vec.y = 40;
			data->NextAction = 1;
		}

		njPushUnitMatrix();
		njTranslateEx(&data->Scale);
		njRotateZXY(&data->Rotation);
		njCalcVector(_nj_current_matrix_ptr_, &data->Position, &vec, false);
		njPopMatrixEx();
	}
}

static void __cdecl EFPlatforms_Display(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl EFPlatforms_Main(ObjectMaster* obj){
	if (!ClipSetObject(obj))	{
		auto data = obj->Data1.Entity;

		switch (data->Action)		{
		case EFPlatformAct_Move:
			EFPlatforms_Move(data);
			break;
		case EFPlatformAct_Reach:
			EFPlatforms_Move(data);
			break;
		}

		AddToCollisionList(obj);
	}
}

static void __cdecl EFPlatforms(ObjectMaster* obj){
	auto data = obj->Data1.Entity;

	obj->DisplaySub = EFPlatforms_Display;
	obj->MainSub = EFPlatforms_Main;

	if (data->Scale.x == 0)	{
		obj->field_4C = EF_PLTFRMS->getmodel();
		InitCollision(obj, (CollisionData*)&EFPlatforms_Col[0], 1, 4);
		data->Action = EFPlatformAct_Move;
	}
	else	{
		obj->field_4C = EF_PLTFRMS->getmodel()->child;
		InitCollision(obj, (CollisionData*)&EFPlatforms_Col[1], 2, 4);
		data->Action = EFPlatformAct_Reach;
	}

	if (data->Scale.y == 1)	{
		data->Action = EFPlatformAct_Still;
	}

	data->field_6 = rand() % 0xFFFF;
	data->Scale = data->Position;
}

static void __cdecl EFPipeline_Display(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	DrawSA2BModel(model->sa2bmodel);
	DrawSA2BModel(model->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl EFPipeline_Main(ObjectMaster* obj){
	if (!ClipSetObject(obj))	{
		// UV Stuff to figure out
	}
}

static void __cdecl EFPipeline(ObjectMaster* obj){
	auto data = obj->Data1.Entity;

	obj->DeleteSub = ObjectFunc_DynColDelete;
	obj->MainSub = EFPipeline_Main;
	obj->DisplaySub = EFPipeline_Display;

	auto dynobj = GetFreeDyncolObjectEntry();

	memcpy(dynobj, EF_PIPLINECOL->getmodel(), sizeof(NJS_OBJECT));

	dynobj->pos[0] = data->Position.x;
	dynobj->pos[1] = data->Position.y;
	dynobj->pos[2] = data->Position.z;
	dynobj->ang[0] = data->Rotation.x;
	dynobj->ang[1] = data->Rotation.y;
	dynobj->ang[2] = data->Rotation.z;
	dynobj->evalflags = 0xFFFFFFF8;

	DynCol_Add(SurfaceFlag_Solid, obj, dynobj);

	obj->EntityData2 = reinterpret_cast<UnknownData2*>(dynobj);
	obj->field_4C = reinterpret_cast<void*>(EF_PIPLINE->getmodel());
}

static inline bool EFShip_IsDoorOpened(int id){
	return (SwitchPressedStates[id % 9] == true || EnemySwitchStates[id] || Action_Held[0]);
}

static inline void EFShip_UpdateCollision(EntityData1* data){
	auto col = &data->Collision->CollisionArray[2];

	col->center.y = EFDoor_Col[2].center.y - data->Scale.y;
}

static inline void SetCollisionInfoRotations(CollisionInfo* colinfo, Rotation* rotation){
	for (int i = 0; i < colinfo->Count; ++i)	{
		auto col = &colinfo->CollisionArray[i];

		col->rotation.x = rotation->x;
		col->rotation.z = rotation->z;
	}
}

static void __cdecl EFShipDoor_Display(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	DrawSA2BModel(model->sa2bmodel);
	njTranslateY(data->Scale.y);
	DrawSA2BModel(model->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl EFShipDoor_Main(ObjectMaster* obj){
	if (!ClipSetObject(obj))	{
		auto data = obj->Data1.Entity;
		auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);
		auto id = static_cast<int>(data->Scale.x);

		switch (data->Action)		{
		case EFDoorAction_CloseDoor:
			if (data->NextAction == 0)			{
				if (IsPlayerInsideSphere(&data->Position, 800) != 0)				{
					data->NextAction = 1;
					//PlaySound
				}
				else				{
					break;
				}
			}

			if (data->Scale.y < 0)			{
				data->Scale.y += 3;
			}
			else			{
				data->Action = EFDoorAction_Closed;
				data->Scale.y = 0;
			}

			EFShip_UpdateCollision(data);

			break;
		case EFDoorAction_Closed:
			if (EFShip_IsDoorOpened(id))			{
				data->Action = EFDoorAction_OpenDoor;
				//PlaySound

				if (obj->SETData)				{
					obj->SETData->Flags |= 0x100;
				}
			}

			break;
		case EFDoorAction_OpenDoor:
			if (data->Scale.y > model->child->pos[1])			{
				data->Scale.y -= 3;
			}
			else			{
				data->Action = EFDoorAction_Opened;
				data->Scale.y = model->child->pos[1];
			}

			EFShip_UpdateCollision(data);

			break;
		}

		AddToCollisionList(obj);
	}
}

static void __cdecl EFShipDoor(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto id = static_cast<int>(data->Scale.x);

	obj->MainSub = EFShipDoor_Main;
	obj->DisplaySub = EFShipDoor_Display;

	auto model = EF_OBJDOOR->getmodel();

	data->Scale.y = model->child->pos[1];
	obj->field_4C = reinterpret_cast<void*>(model);

	InitCollision(obj, (CollisionData*)EFDoor_Col, 3, 4);
	SetCollisionInfoRotations(data->Collision, &data->Rotation);
	EFShip_UpdateCollision(data);

	if (EFShip_IsDoorOpened(id) || (obj->SETData && obj->SETData->Flags & 0x100))	{
		data->Action = EFDoorAction_Opened;
	}
}

static void __cdecl EFShipConveyor(ObjectMaster* obj){

}

static void __cdecl EFAntenna_Display(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY_(data->Rotation.y);

	if (data->Scale.x == 0)	{
		njRotateY_(data->Scale.y);
		DrawSA2BModel(model->sa2bmodel);
	}
	else	{
		DrawSA2BModel(model->child->sa2bmodel);
		njRotateY_(data->Scale.y);
		DrawSA2BModel(model->child->child->sa2bmodel);
	}

	njPopMatrixEx();
}

static void __cdecl EFAntenna_Main(ObjectMaster* obj){
	if (!ClipSetObject(obj))	{
		auto data = obj->Data1.Entity;

		data->Scale.y += 200;
	}
}

static void __cdecl EFAntenna(ObjectMaster* obj){
	obj->MainSub = EFAntenna_Main;
	obj->DisplaySub = EFAntenna_Display;
	obj->field_4C = reinterpret_cast<void*>(EF_ANTENNA->getmodel());
	InitCollision(obj, (CollisionData*)&AntennaCol, 1, 4);
}

static void __cdecl EFRailSign_Display(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	DrawSA2BModel(model->sa2bmodel);

	int time = GetTimer() % 30;

	if (time < 10)	{
		DrawSA2BModel(model->child->sa2bmodel);
	}
	else if (time < 20)	{
		DrawSA2BModel(model->child->child->sa2bmodel);
	}
	else	{
		DrawSA2BModel(model->child->child->child->sa2bmodel);
	}

	njPopMatrixEx();
}

static void __cdecl EFRailSign(ObjectMaster* obj){
	auto data = obj->Data1.Entity;

	obj->DeleteSub = ObjectFunc_DynColDelete;
	obj->MainSub = ClipObjectObjFunc;
	obj->DisplaySub = EFRailSign_Display;

	auto dynobj = GetFreeDyncolObjectEntry();

	if (data->Scale.x == 1)	{
		memcpy(dynobj, EF_DIRSGNSCOL->getmodel()->child->sibling, sizeof(NJS_OBJECT));
		obj->field_4C = EF_DIRSGNS->getmodel()->child->sibling;
	}
	else	{
		memcpy(dynobj, EF_DIRSGNSCOL->getmodel()->child, sizeof(NJS_OBJECT));
		obj->field_4C = EF_DIRSGNS->getmodel()->child;
	}

	dynobj->pos[0] = data->Position.x;
	dynobj->pos[1] = data->Position.y;
	dynobj->pos[2] = data->Position.z;
	dynobj->ang[0] = data->Rotation.x;
	dynobj->ang[1] = data->Rotation.y;
	dynobj->ang[2] = data->Rotation.z;
	dynobj->evalflags = 0xFFFFFFF8;

	DynCol_Add(SurfaceFlag_Solid, obj, dynobj);

	obj->EntityData2 = (UnknownData2*)dynobj;
}

static void __cdecl EFMissilePods(ObjectMaster* obj){

}

static void __cdecl EFHelice_Display(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateY_(data->Rotation.y);
	njRotateX_(data->Rotation.x);
	DrawSA2BModel(model->sa2bmodel);
	njRotateZ_(data->Scale.z);
	DrawSA2BModel(model->child->sa2bmodel);
	DrawSA2BModel(model->child->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl EFHelice_Main(ObjectMaster* obj){
	if (!ClipSetObject(obj))	{
		obj->Data1.Entity->Scale.z -= 1200.0f;
	}
}

static void __cdecl EFHelice(ObjectMaster* obj){
	obj->MainSub = EFHelice_Main;
	obj->DisplaySub = EFHelice_Display;

	Play3DSound_EntityPosBank(obj->Data1.Entity, 7, &obj->Data1.Entity->Position, 70, 5);

	obj->field_4C = reinterpret_cast<void*>(EF_EHELICE->getmodel());
}

static void __cdecl EFBarrier_Display(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	DrawSA2BModel(model->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl EFBarrier_Main(ObjectMaster* obj){
	if (!ClipSetObject(obj))	{
		auto data = obj->Data1.Entity;
		auto player = GetCollidingPlayer(obj);

		if (player && player->Data1.Entity->Status & Status_Attack)		{
			auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);
			model = model->child;

			LoadBreaker(&data->Position, &data->Rotation, model, 0.0f, 15.0f, 0.0f, 60);
			Play3DSound_Vector(4112, &data->Position, 0, 0, 70);
			UpdateSetDataAndDelete(obj);
		}

		AddToCollisionList(obj);
	}
}

static void __cdecl EFBarrier(ObjectMaster* obj){
	obj->MainSub = EFBarrier_Main;
	obj->DisplaySub = EFBarrier_Display;
	obj->field_4C = reinterpret_cast<void*>(EF_BARRIER->getmodel());
	InitCollision(obj, (CollisionData*)&EFBarrier_Col, 1, 2);
}

static void __cdecl EFEndRail_Display(ObjectMaster* obj){
	auto data = obj->Data1.Entity;
	auto model = reinterpret_cast<NJS_OBJECT*>(obj->field_4C);

	njSetTexture(CurrentLevelTexList);
	njPushMatrixEx();
	njTranslateEx(&data->Position);
	njRotateZXY(&data->Rotation);
	DrawSA2BModel(model->sa2bmodel);
	DrawSA2BModel(model->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl EFEndRail(ObjectMaster* obj){
	obj->DisplaySub = EFEndRail_Display;
	obj->MainSub = ClipObjectObjFunc;
	obj->field_4C = reinterpret_cast<void*>(EF_ENDRAIL->getmodel());
}

static ObjectListEntry EggFleetObjectList_list[]
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
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Switch_Main },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 560000, CONTCHAO },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 1360000, DashHoop },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, ItemBoxBalloon },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 160000, ItemBox_Main },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)ROCKET },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)ROCKETMISSILE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_Default, 0, (ObjectFuncPtr)CHAOPIPE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_Default, 0, (ObjectFuncPtr)MINIMAL },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown5, 360000, (ObjectFuncPtr)E_GOLD},
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Common, DistObj_Default, 0, Checkpoint_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)CWALL },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, RingGroup },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)SPHERE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCYL },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)CCUBE },
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, 0, nullptr }, //ottotto
	{ LoadObj_Data1, ObjIndex_Common, DistObj_UseDist, 360000, (ObjectFuncPtr)HINTBOX },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, //rhino
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, //sweep
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Common, DistObj_UseDist, 2360000, DashRampAdjust },
	{ (LoadObj)(LoadObj_Data2 | LoadObj_Data1 | LoadObj_UnknownA | LoadObj_UnknownB), ObjIndex_Stage, DistObj_UseDist, 160000, ItemBoxAir_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Stationary },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Electric },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Attack },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, ItemBoxBalloon },
	{ (LoadObj)(LoadObj_Data1 | LoadObj_UnknownA), ObjIndex_Stage, DistObj_UseDist, 1360000, (ObjectFuncPtr)LongSpring_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, // uni A
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, // uni B
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, (ObjectFuncPtr)Robots }, // uni C
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_Unknown4, 0, Beetle_Attack },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1000000, WoodenCrate_Main },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1360000, ObjCannon },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 360000, nullptr },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, OBJCASE },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1360000, (ObjectFuncPtr)UDREEL }, //45
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 4060000, EFBigFan },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1060000, EFCannon },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, EFPlatforms },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, EFPipeline },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2060000, EFShipDoor }, //50
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 5060000, EFShipConveyor },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 2060000, EFAntenna },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1360000, EFRailSign },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, EFMissilePods },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, EFHelice }, //55
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 3060000, EFBarrier },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, e2000_Init },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 10000000, Flyer_Init },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1000000, Flyer_Trigger },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, Laserdoor },
	{ LoadObj_Data1, ObjIndex_Stage, DistObj_UseDist, 1560000, EFEndRail }
};

static ObjectListHead EggFleetObjectList = { arraylengthandptr(EggFleetObjectList_list) };

static void __cdecl EggFleet_SkyBox(ObjectMaster* obj)
{
	auto position = &CameraScreensInfoArray[CurrentScreen]->pos;
	
	njPushMatrixEx();
	njSetTexture(CurrentLevelTexList);
	njTranslate(_nj_current_matrix_ptr_, position->x, position->y, position->z);
	njScalef(0.25f);
	DrawSA2BModel(EF_SKYMDLS->getmodel()->sa2bmodel);
	DrawSA2BModel(EF_SKYMDLS->getmodel()->child->sa2bmodel);
	njPopMatrixEx();
}

static void __cdecl EggFleet_Main(ObjectMaster* obj)
{

}

static void EggFleet_Load()
{
	CurrentHeroesLevel = HeroesLevelIDs::EggFleet;
	CommonLevelInit();

	LoadChunkFile("resource\\gd_pc\\s13_blk.bin");
	LoadLandTable("resource\\gd_pc\\s13.sa2lvl", LandTableFormat_SA2);
	LoadLevelTex((NJS_TEXLIST*)&eggfleet_texlist, "s13");
	LoadTXCFile("resource\\gd_pc\\s13.txc");

	LoadLevelLayout(&EggFleetObjectList, "s13_P1.bin", "s13_DB.bin");

	LoadStageLight("stg13_light.bin");
	LoadStagePaths(EggFleetPathList);
	LoadLevelMusic((char*)"eggfleet.adx");
	LoadDeathZones(EggFleetDeathZones);
	LoadFogData_Fogtask("stg13_fog.bin", (FogData*)0x1A280C8);
	LoadStageSounds("se_ac_gf.mlt", (void*)0x8A0F60);

	LoadObject((LoadObj)0, "SKYBOX", EggFleet_SkyBox, 1)->DisplaySub = EggFleet_SkyBox;

	LoadMDL(&EF_SKYMDLS, "EF_SKYMDLS", ModelFormat_SA2B);
	LoadMDL(&EF_PROPPLR,"EF_PROPPLR", ModelFormat_SA2B);
	LoadMDL(&EF_EHELICE,"EF_EHELICE", ModelFormat_SA2B);
	LoadMDL(&EF_EBIGFAN,"EF_EBIGFAN", ModelFormat_SA2B);
	LoadMDL(&EF_ANTENNA,"EF_ANTENNA", ModelFormat_SA2B);
	LoadMDL(&EF_BARRIER,"EF_BARRIER", ModelFormat_SA2B);
	LoadMDL(&EF_ENDRAIL,"EF_ENDRAIL", ModelFormat_SA2B);
	LoadMDL(&EF_PIPLINE,"EF_PIPLINE", ModelFormat_SA2B);
	LoadMDL(&EF_PLTFRMS,"EF_PLTFRMS", ModelFormat_SA2B);
	LoadMDL(&EF_DIRSGNS,"EF_DIRSGNS", ModelFormat_SA2B);
	LoadMDL(&EF_OBJDOOR,"EF_OBJDOOR", ModelFormat_SA2B);

	LoadMDL(&EF_EBIGFAN,"EF_EBIGFAN", ModelFormat_Basic);
	LoadMDL(&EF_PIPLINE,"EF_PIPLINE", ModelFormat_Basic);
	LoadMDL(&EF_DIRSGNS,"EF_DIRSGNS", ModelFormat_Basic);

	SetPropellerModel(EF_PROPPLR->getmodel());
}

static void EggFleetDelete()
{
	FreeMDL(&EF_SKYMDLS);
	FreeMDL(&EF_PROPPLR);
	FreeMDL(&EF_EHELICE);
	FreeMDL(&EF_EBIGFAN);
	FreeMDL(&EF_ANTENNA);
	FreeMDL(&EF_BARRIER);
	FreeMDL(&EF_ENDRAIL);
	FreeMDL(&EF_PIPLINE);
	FreeMDL(&EF_PLTFRMS);
	FreeMDL(&EF_DIRSGNS);
	FreeMDL(&EF_OBJDOOR);
	FreeMDL(&EF_EBIGFANCOL);
	FreeMDL(&EF_PIPLINECOL);
	FreeMDL(&EF_DIRSGNSCOL);

	CommonLevelDelete();
}

void EggFleet_Init(const char* path, const HelperFunctions& helperFunctions)
{
	FinalRushHeader.Init = EggFleet_Load;
	FinalRushHeader.subprgmanager = EggFleet_Main;
	FinalRushHeader.Free = EggFleetDelete;

	SetStartEndPoints(helperFunctions, &ef_startpos, &ef_2pintro, &ef_endpos, &ef_endpos23);
}