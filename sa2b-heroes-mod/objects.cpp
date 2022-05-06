#include "stdafx.h"

NJS_TEXNAME_ HeroesWater_TexNames[16];
NJS_TEXLIST_ HeroesWater_TexList = { arrayptrandlength(HeroesWater_TexNames) };

const char* ModelFormatStrings[]{
	"collision",
	"chunk",
	"battle"
};

const char* mdlformatfiletypes[] = {
	".sa1mdl",
	".sa2mdl",
	".sa2bmdl"
};

//Load Object File
void LoadMDL(ModelInfo** info, const char *name, ModelFormat format)
{
	std::string fullPath;

	if (format == ModelFormat_Basic)
	{
		fullPath = "resource\\gd_PC\\COLLISIONS\\";
	}
	else
	{
		fullPath = "resource\\gd_PC\\MODELS\\";
	}

	fullPath += static_cast<std::string>(name) + static_cast<std::string>(mdlformatfiletypes[format - 1]);
	
	const char *foo = fullPath.c_str();

	ModelInfo * temp = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == format)
	{
		PrintDebug("[Heroes Mod] Failed loading %s model: %s.", ModelFormatStrings[(int)format - 1], name);
		*info = temp;
	}
	else
	{
		PrintDebug("[Heroes Mod] Loaded %s model: %s.", ModelFormatStrings[(int)format - 1], name);
		delete temp;
		*info = nullptr;
	}
}

void LoadAnim(AnimationFile** info, const char* name)
{
	std::string fullPath = "resource\\gd_PC\\ANIMATIONS\\" + static_cast<std::string>(name) + static_cast<std::string>(".saanim");

	AnimationFile* temp = new AnimationFile(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (temp->getmotion() != nullptr)
	{
		PrintDebug("[Heroes Mod] Failed loading animation: %s.", name);
		*info = temp;
	}
	else {
		PrintDebug("[Heroes Mod] Loaded animation: %s.", name);
		delete temp;
		*info = nullptr;
	}
}

//Free Object File
void FreeMDL(ModelInfo** info)
{
	if (*info)
	{
		delete* info;
		info = nullptr;
	}
}

void FreeAnim(AnimationFile** info)
{
	if (*info)
	{
		delete* info;
		info = nullptr;
	}
}

// Math stuff
float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest)
{
	return sqrtf(powf(dest->x - orig->x, 2) + powf(dest->y - orig->y, 2) + powf(dest->z - orig->z, 2));
}

int IsPlayerInsideSphere(Float x, Float y, Float z, Float radius)
{
	for (int player = 0; player < 2; ++player)
	{
		if (!MainCharObj1[player]) continue;

		auto pos = &MainCharObj1[player]->Position;

		if ((powf(pos->x - x, 2) + pow(pos->y - y, 2) + pow(pos->z - z, 2)) <= pow(radius, 2))
		{
			return player + 1;
		}
	}

	return 0;
}

int IsPlayerInsideSphere(NJS_VECTOR *center, Float radius)
{
	return IsPlayerInsideSphere(center->x, center->y, center->z, radius);
}

bool IsPlayerIDInsideSphere(Float x, Float y, Float z, Float radius, Uint8 PlayerID)
{
	if (!MainCharObj1[PlayerID]) return false;

	auto pos = &MainCharObj1[PlayerID]->Position;

	if ((powf(pos->x - x, 2) + pow(pos->y - y, 2) + pow(pos->z - z, 2)) <= pow(radius, 2))
	{
		return true;
	}

	return false;
}

NJS_VECTOR GetPathPosition(NJS_VECTOR* orig, NJS_VECTOR* dest, float state)
{
	NJS_VECTOR result;

	result.x = (dest->x - orig->x) * state + orig->x;
	result.y = (dest->y - orig->y) * state + orig->y;
	result.z = (dest->z - orig->z) * state + orig->z;

	return result;
}

Rotation fPositionToRotation(NJS_VECTOR* orig, NJS_VECTOR* point)
{
	NJS_VECTOR dist;
	Rotation result;

	dist.x = point->x - orig->x;
	dist.y = point->y - orig->y;
	dist.z = point->z - orig->z;

	result.x = static_cast<Angle>(atan2f(dist.y, dist.z) * -10430.38f);
	result.y = static_cast<Angle>(atan2f(dist.x, sqrtf(dist.z * dist.z + dist.y * dist.y)) * 10430.38f) - 0x8000;
	result.z = 0;

	return result;
}

void TransformSpline(NJS_VECTOR* pos, NJS_VECTOR* orig, NJS_VECTOR* dest, float state)
{
	pos->x = (dest->x - orig->x) * state + orig->x;
	pos->y = (dest->y - orig->y) * state + orig->y;
	pos->z = (dest->z - orig->z) * state + orig->z;
}

NJS_OBJECT* GetChildModelByIndex(NJS_OBJECT* object, int index)
{
	int i = 0;
	NJS_OBJECT* child = object;
	
	while (child) {
		if (i == index) {
			return child;
		}

		child = child->child;
		i += 1;
	}

	return nullptr;
}

NJS_OBJECT* GetSiblingModelByIndex(NJS_OBJECT* object, int index)
{
	int i = 0;
	NJS_OBJECT* sibling = object;

	while (sibling) {
		if (i == index) {
			return sibling;
		}

		sibling = sibling->sibling;
		i += 1;
	}

	return nullptr;
}

void MainSub_Collision(ObjectMaster* obj)
{
	if (!ClipSetObject(obj))
	{
		AddToCollisionList(obj);
	}
}

void njScalef(Float f)
{
	njScale_(f, f, f);
}

void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs)
{
	vd->x += vs->x;
	vd->y += vs->y;
	vd->z += vs->z;
}

void njTranslateXYZ(Float x, Float y, Float z)
{
	njTranslate(_nj_current_matrix_ptr_, x, y, z);
}

void njTranslateX(Float f)
{
	njTranslate(_nj_current_matrix_ptr_, f, 0, 0);
}

void njTranslateY(Float f)
{
	njTranslate(_nj_current_matrix_ptr_, 0, f, 0);
}

void njTranslateZ(Float f)
{
	njTranslate(_nj_current_matrix_ptr_, 0, 0, f);
}

void njRotateX_(Angle x)
{
	if (x != 0)
	{
		njRotateX(_nj_current_matrix_ptr_, x);
	}
}

void njRotateY_(Angle y)
{
	if (y != 0)
	{
		njRotateY(_nj_current_matrix_ptr_, y);
	}
}

void njRotateZ_(Angle z)
{
	if (z != 0)
	{
		njRotateZ(_nj_current_matrix_ptr_, z);
	}
}

void njRotateZXY(Angle x, Angle y, Angle z)
{
	njRotateZ_(z);
	njRotateX_(x);
	njRotateY_(y);
}

void njRotateZXY(Rotation* rot)
{
	njRotateZ_(rot->z);
	njRotateX_(rot->x);
	njRotateY_(rot->y);
}

void njRotateXYZ(Rotation* rot)
{
	njRotateX_(rot->x);
	njRotateY_(rot->y);
	njRotateZ_(rot->z);
}

void DrawChunkModel__(NJS_MODEL* model)
{
	ResetRenderSpace();
	ProcessChunkModel((NJS_CNK_MODEL*)model);
}

void njCnkAction(NJS_OBJECT* obj, NJS_MOTION* mot, float frame)
{
	*(int*)0x25EFE54 = 0x25EFE60;
	njSetMotion(mot, frame);
	MotionDrawCallback = reinterpret_cast<ObjectFuncPtr>(DrawChunkModel__);
	DrawObjMotion(obj);
}

void njSA2BAction(NJS_OBJECT* obj, NJS_MOTION* mot, float frame)
{
	*(int*)0x25EFE54 = 0x25EFE60;
	njSetMotion(mot, frame);
	MotionDrawCallback = reinterpret_cast<ObjectFuncPtr>(DrawSA2BModel);
	DrawObjMotion(obj);
}

void DrawObject_(NJS_OBJECT* obj, ModelFormat format)
{
	njPushMatrixEx();

	if (!(obj->evalflags & NJD_EVAL_UNIT_POS))
	{
		njTranslate(_nj_current_matrix_ptr_, obj->pos[0], obj->pos[1], obj->pos[2]);
	}
	
	if (!(obj->evalflags & NJD_EVAL_UNIT_ANG))
	{
		njRotateXYZ(reinterpret_cast<Rotation*>(&obj->ang));
	}

	if (!(obj->evalflags & NJD_EVAL_UNIT_SCL))
	{
		njScale_(obj->scl[0], obj->scl[1], obj->scl[2]);
	}

	if (obj->model)
	{
		switch (format)
		{
		case ModelFormat_Chunk:
			DrawChunkModel__(obj->basicmodel);
			break;
		case ModelFormat_SA2B:
			DrawSA2BModel(obj->sa2bmodel);
			break;
		}
	}
	
	if (obj->child) {
		DrawObject_(obj->child, format);
	}

	njPopMatrixEx();
	
	if (obj->sibling) {
		DrawObject_(obj->sibling, format);
	}
}