#include "stdafx.h"
#include "paths.h"

NJS_OBJECT* PropellerModel = nullptr;

CollisionData Prop_col = { 0, CollisionShape_Sphere, 0x77, 0xE0, 0, { 0.0f, 0.0f, 0.0f }, 1.0f, 1.0f, 1.0f, 0.0f, 0, 0, 0 };

enum PropellerActions {
	PropellerAction_CheckForPlayer,
	PropellerAction_Run,
	PropellerAction_FadeAway
};

struct PropellerData {
	Uint8 Player;
	Uint8 Action;
	Uint16 CurrentPoint;
	Float PointProgress;
	NJS_VECTOR Position;
	Rotation Rotation;
	Float PosOffset;
	Angle RotOffset;
};

NJS_VECTOR Propeller_GetHandlePoint(EntityData1* data, CharObj2Base* co2)
{
	NJS_VECTOR point = { 0, -co2->PhysData.Height + data->Scale.y, 0 };

	njPushUnitMatrix();
	njTranslateEx(&data->Position);
	njRotateY(0, -data->Rotation.y + 0x4000);
	njRotateZ(0, data->Rotation.z);
	njRotateX(0, data->Rotation.x);
	njCalcPoint(_nj_current_matrix_ptr_, &point, &point, false);
	njPopMatrixEx();
	return point;
}

void Propeller_SetAnimation(EntityData1* data, CharObj2Base* co2) {
	data->Action = CHAR_MIN;
	co2->field_28 = 75;
	co2->AnimInfo.Current = 75;
	co2->AnimInfo.field_8 = 42;
}

void Propeller_Delete(ObjectMaster* obj) {
	PathControl* ctrl = (PathControl*)obj->Parent->Data2.Undefined;
	EntityData1* data = obj->Data1.Entity;

	if (data->Action != PropellerAction_CheckForPlayer) {
		ctrl->Player &= ~(1 << data->field_2);
	}
}

void Propeller_Display(ObjectMaster* obj) {
	PathControl* ctrl = (PathControl*)obj->Parent->Data2.Undefined;
	EntityData1* pdata = (EntityData1*)ctrl;
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

	if (data->Action || pdata->Timer != 0) {
		njSetTexture(CurrentLevelTexList);
		njPushMatrixEx();
		njTranslateEx(&data->Position);
		njRotateY(0, -data->Rotation.y - 0x4000);
		njRotateZ(0, data->Rotation.z);
		njRotateX(0, data->Rotation.x);
		njTranslateY(data->Scale.y);
		DrawSA2BModel(model->sa2bmodel);
		njRotateY_(data->Status);
		DrawSA2BModel(model->child->sa2bmodel);
		njPopMatrixEx();
	}
}

void Propeller_Run(EntityData1* data, LoopHead* path) {
	EntityData1* PlayerData = MainCharObj1[data->field_2];
	CharObj2Base* co2 = MainCharObj2[data->field_2];

	if (data->Timer < path->Count - 2) {
		if (data->Scale.x > 1) { data->Scale.x = 0; data->Timer++; };
		data->Scale.x = data->Scale.x + (path->TotalDistance / path->Points[data->Timer].Distance) / path->TotalDistance * 8.0f;
		TransformSpline(&data->Position, &path->Points[data->Timer].Position, &path->Points[data->Timer + 1].Position, data->Scale.x);
		data->Rotation.y = fPositionToRotation(&path->Points[data->Timer].Position, &path->Points[data->Timer + 1].Position).y;

		PlayerData->Position = Propeller_GetHandlePoint(data, co2);
		PlayerData->Rotation = data->Rotation;

		data->Status += 0x500;

		Propeller_SetAnimation(PlayerData, co2);

		if (Jump_Pressed[data->field_2]) {
			data->Action = PropellerAction_FadeAway;
			PlayerData->Action = 0;
		}

		if (Controllers[data->field_2].on & Buttons_Up) {
			if (data->Scale.y < 20.0f) {
				data->Scale.y += 2.0f;
			}
		}
		else if (Controllers[data->field_2].on & Buttons_Down) {
			if (data->Scale.y > -20.0f) {
				data->Scale.y -= 2.0f;
			}
		}
		else {
			if (data->Scale.y < 0.0f) {
				data->Scale.y += 2.0f;
			}
			else if (data->Scale.y > 0.0f) {
				data->Scale.y -= 2.0f;
			}
		}
	}
	else {
		data->Action = PropellerAction_FadeAway;
		PlayerData->Action = 0;
	}
}

void Propeller_CheckForPlayer(ObjectMaster* obj, PathControl* ctrl, EntityData1* pdata, EntityData1* data, NJS_OBJECT* model) {
	// Adjust position if propeller base is attached to the ground

	if (pdata->field_2 == 1) {
		data->Position.y = pdata->Position.y + model->pos[1];
		pdata->field_2 = 2;
	}

	// Check if a player touches the handle

	Uint8 player = IsPlayerInsideSphere(&data->Position, 10.0f);

	if (player && !((1 << (player - 1)) & ctrl->Player)) {
		data->Action = PropellerAction_Run;
		data->field_2 = player - 1;
		ctrl->Player |= 1 << (player - 1);

		Propeller_SetAnimation(MainCharObj1[player - 1], MainCharObj2[player - 1]);
	}

	AddToCollisionList(obj);
}

void Propeller_Main(ObjectMaster* obj) {
	PathControl* ctrl = (PathControl*)obj->Parent->Data2.Undefined;
	EntityData1* pdata = (EntityData1*)ctrl;
	EntityData1* data = obj->Data1.Entity;

	if (data->Action || pdata->Timer != 0) {
		switch (data->Action) {
		case PropellerAction_CheckForPlayer:
			Propeller_CheckForPlayer(obj, ctrl, pdata, data, (NJS_OBJECT*)obj->field_4C);
			return;
		case PropellerAction_Run:
			Propeller_Run(data, ctrl->loophead);
			return;
		case PropellerAction_FadeAway:
			data->Position.y += 5.0f;

			if (++data->Index > 120) {
				DeleteObject_(obj);
			}
		}
	}
}

void Propeller_Init(ObjectMaster* obj) {
	PathControl* ctrl = (PathControl*)obj->Parent->Data2.Undefined;
	EntityData1* pdata = (EntityData1*)ctrl;
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* model = (NJS_OBJECT*)obj->Parent->field_4C;

	data->Position = pdata->Position;
	data->Rotation = pdata->Rotation;
	data->Position.y += model->child->pos[1];

	obj->field_4C = model->child;
	obj->MainSub = Propeller_Main;
	obj->DisplaySub = Propeller_Display;
	obj->DeleteSub = Propeller_Delete;

	InitCollision(obj, &Prop_col, 1, 3);
}

void PropellerPath_Display(ObjectMaster* obj) {
	PathControl* ctrl = (PathControl*)obj->Data2.Undefined;
	EntityData1* data = (EntityData1*)ctrl;

	if (data->Timer != 0) {
		NJS_OBJECT* model = (NJS_OBJECT*)obj->field_4C;

		njSetTexture(CurrentLevelTexList);
		njPushMatrixEx();
		njTranslateEx(&data->Position);
		njRotateY(0, -data->Rotation.y - 0x4000);
		njRotateZ(0, data->Rotation.z);
		njRotateX(0, data->Rotation.x);
		DrawSA2BModel(model->sa2bmodel);
		njPopMatrixEx();
	}
}

void PropellerPath_Main(ObjectMaster* obj) {
	PathControl* ctrl = (PathControl*)obj->Data2.Undefined;
	EntityData1* data = (EntityData1*)ctrl;

	if (IsPlayerInsideSphere(&data->Position, 3000.0f)) {
		data->Timer = 1; // visible

		if (GameState != GameStates_Ingame && GameState != GameStates_Pause) {
			DeleteChildObjects(obj);
			ctrl->Player = 0;
		}

		// When the ground is found, place the propeller more precisely
		if (data->field_2 == 0 && GetTimer() % 60 == 0) {
			float height = (float)GetGroundHeight(ctrl->loophead->Points[0].Position.x, ctrl->loophead->Points[0].Position.y, ctrl->loophead->Points[0].Position.z, &data->Rotation);

			if (height > -999999) {
				data->Position.y = height;
				data->field_2 = 1;
			}
		}

		// Load a new propeller when needed
		if (!obj->Child || (data->Index != ctrl->Player && MainCharObj1 && ++data->Status > 60)) {
			data->Index = ctrl->Player;
			data->Status = 0;
			LoadChildObject(LoadObj_Data1, Propeller_Init, obj);
		}
	}
	else {
		data->Timer = 0; // not visible
	}
}

void PropellerPath(ObjectMaster* obj) {
	PathControl* ctrl = (PathControl*)obj->Data2.Undefined;
	EntityData1* data = (EntityData1*)ctrl;

	if (IsPlayerInsideSphere(&ctrl->loophead->Points[0].Position, 3000.0f)) {
		EntityData1* data = (EntityData1*)ctrl;

		data->Position = ctrl->loophead->Points[0].Position;
		data->Position.y -= 40;
		data->Rotation.y = fPositionToRotation(&ctrl->loophead->Points[0].Position, &ctrl->loophead->Points[5].Position).y;

		obj->field_4C = PropellerModel;
		obj->DisplaySub = PropellerPath_Display;
		obj->MainSub = PropellerPath_Main;

		LoadChildObject(LoadObj_Data1, Propeller_Init, obj);
	}
}

void SetPropellerModel(NJS_OBJECT* object) {
	PropellerModel = object;
}