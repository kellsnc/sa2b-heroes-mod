#include "stdafx.h"

NJS_TEXNAME_ HeroesWater_TexNames[16];
NJS_TEXLIST_ HeroesWater_TexList = { arrayptrandlength(HeroesWater_TexNames) };

const char* ModelFormatStrings[]{
	"collision",
	"chunk",
	"battle"
};

//Load Object File
ModelInfo* LoadMDL(const char *name, ModelFormat format) {
	std::string fullPath;

	if (format == ModelFormat_Basic) {
		fullPath = "resource\\gd_PC\\COLLISIONS\\";
	}
	else {
		fullPath = "resource\\gd_PC\\MODELS\\";
	}

	fullPath += name;
	
	switch (format) {
	case ModelFormat_Basic:
		fullPath += ".sa1mdl";
		break;
	case ModelFormat_Chunk:
		fullPath += ".sa2mdl";
		break;
	case ModelFormat_SA2B:
		fullPath += ".sa2bmdl";
		break;
	}
	
	const char *foo = fullPath.c_str();

	ModelInfo * temp = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == format) {
		PrintDebug("[Heroes Mod] Loaded %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}
	else {
		PrintDebug("[Heroes Mod] Failed loading %s model: %s.", ModelFormatStrings[(int)format - 1], name);
	}

	return temp;
}

AnimationFile* LoadAnim(const char* name) {
	std::string fullPath = "resource\\gd_PC\\ANIMATIONS\\";

	fullPath = fullPath + name + ".saanim";

	AnimationFile* file = new AnimationFile(HelperFunctionsGlobal.GetReplaceablePath(fullPath.c_str()));

	if (file->getmotion() != nullptr) {
		PrintDebug("[Heroes Mod] Loaded animation: %s.", name);
	}
	else {
		PrintDebug("[Heroes Mod] Failed loading animation: %s.", name);
	}

	return file;
}

//Free Object File
void FreeMDL(ModelInfo * pointer) {
	if (pointer) delete(pointer);
}

void FreeAnim(AnimationFile* pointer) {
	if (pointer) delete pointer;
}

// Math stuff
float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest) {
	return sqrtf(powf(dest->x - orig->x, 2) + powf(dest->y - orig->y, 2) + powf(dest->z - orig->z, 2));
}

int IsPlayerInsideSphere(Float x, Float y, Float z, Float radius) {
	for (uint8_t player = 0; player < 2; ++player) {
		if (!MainCharObj1[player]) continue;

		NJS_VECTOR* pos = &MainCharObj1[player]->Position;
		if ((powf(pos->x - x, 2) + pow(pos->y - y, 2) + pow(pos->z - z, 2)) <= pow(radius, 2)) {
			return player + 1;
		}
	}

	return 0;
}

int IsPlayerInsideSphere(NJS_VECTOR *center, Float radius) {
	return IsPlayerInsideSphere(center->x, center->y, center->z, radius);
}

bool IsPlayerIDInsideSphere(Float x, Float y, Float z, Float radius, Uint8 PlayerID) {
	if (!MainCharObj1[PlayerID]) return false;

	NJS_VECTOR* pos = &MainCharObj1[PlayerID]->Position;

	if ((powf(pos->x - x, 2) + pow(pos->y - y, 2) + pow(pos->z - z, 2)) <= pow(radius, 2)) {
		return true;
	}

	return false;
}

NJS_VECTOR GetPathPosition(NJS_VECTOR* orig, NJS_VECTOR* dest, float state) {
	NJS_VECTOR result;

	result.x = (dest->x - orig->x) * state + orig->x;
	result.y = (dest->y - orig->y) * state + orig->y;
	result.z = (dest->z - orig->z) * state + orig->z;

	return result;
}

bool ClipSetObject(ObjectMaster *obj) {
	if (obj->SETData == nullptr) {
		return 1;
	}

	if (IsPlayerInsideSphere(&obj->Data1.Entity->Position, sqrtf(obj->SETData->field_C))) {
		return 1;
	}
	else {
		DeleteObject_(obj);
		return 0;
	}
}

Rotation fPositionToRotation(NJS_VECTOR* orig, NJS_VECTOR* point) {
	NJS_VECTOR dist;
	Rotation result;

	dist.x = point->x - orig->x;
	dist.y = point->y - orig->y;
	dist.z = point->z - orig->z;

	result.x = atan2(dist.y, dist.z) * 65536.0 * -0.1591549762031479;
	result.y = atan2(dist.x, dist.z) * 65536.0 * 0.1591549762031479;

	result.y = -result.y - 0x4000;
	return result;
}

void TransformSpline(NJS_VECTOR* pos, NJS_VECTOR* orig, NJS_VECTOR* dest, float state) {
	pos->x = (dest->x - orig->x) * state + orig->x;
	pos->y = (dest->y - orig->y) * state + orig->y;
	pos->z = (dest->z - orig->z) * state + orig->z;
}

NJS_OBJECT* GetChildModelByIndex(NJS_OBJECT* object, int index) {
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

NJS_OBJECT* GetSiblingModelByIndex(NJS_OBJECT* object, int index) {
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

void MainSub_Collision(ObjectMaster* obj) {
	if (ClipSetObject(obj)) {
		AddToCollisionList(obj);
	}
}

// Ninja stuff
float* njPushUnitMatrix() {
	float *v8 = _nj_current_matrix_ptr_;
	float *v9 = _nj_current_matrix_ptr_ + 12;
	v8 = _nj_current_matrix_ptr_ + 12;
	memcpy(v9, _nj_current_matrix_ptr_, 0x30u);
	_nj_current_matrix_ptr_ = v9;
	memset(v8, 0, 0x30u);
	*v8 = 1.0;
	v8[5] = 1.0;
	v8[10] = 1.0;
	return v8;
}

void njTranslateV(float* matrix, NJS_VECTOR* pos) {
	njTranslate(matrix, pos->x, pos->y, pos->z);
}

void njScalef(Float f) {
	njScale(f, f, f);
}

void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs) {
	vd->x += vs->x;
	vd->y += vs->y;
	vd->z += vs->z;
}

void njTranslateX(Float f) {
	njTranslate(_nj_current_matrix_ptr_, f, 0, 0);
}

void njTranslateY(Float f) {
	njTranslate(_nj_current_matrix_ptr_, 0, f, 0);
}

void njTranslateZ(Float f) {
	njTranslate(_nj_current_matrix_ptr_, 0, 0, f);
}

void DrawChunkModel(NJS_MODEL* model) {
	ResetRenderSpace();
	ProcessChunkModel((NJS_CNK_MODEL*)model);
}

void njCnkAction(NJS_OBJECT* obj, NJS_MOTION* mot, float frame) {
	*(int*)0x25EFE54 = 0x25EFE60;
	njSetMotion(mot, frame);
	MotionDrawCallback = DrawChunkModel;
	DrawObjMotion(obj);
}

void njSA2BAction(NJS_OBJECT* obj, NJS_MOTION* mot, float frame) {
	*(int*)0x25EFE54 = 0x25EFE60;
	njSetMotion(mot, frame);
	MotionDrawCallback = DrawSA2BModel;
	DrawObjMotion(obj);
}