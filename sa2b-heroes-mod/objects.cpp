#include "stdafx.h"

//Load Object File
ModelInfo* LoadMDL(const char *name) {
	PrintDebug("[SHM] Loading model "); PrintDebug(name); PrintDebug("... ");

	std::string fullPath = "resource\\gd_PC\\MODELS\\";
	fullPath = fullPath + name + ".sa2mdl";
	const char *foo = fullPath.c_str();

	ModelInfo * temp = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == ModelFormat_Chunk) PrintDebug("Done.\n");
	else PrintDebug("Error.\n");

	return temp;
}

ModelInfo* LoadCOLMDL(const char* name) {
	PrintDebug("[SHM] Loading collision model "); PrintDebug(name); PrintDebug("... ");

	std::string fullPath = "resource\\gd_PC\\COLLISIONS\\";
	fullPath = fullPath + name + ".sa1mdl";
	const char* foo = fullPath.c_str();

	ModelInfo* temp = new ModelInfo(HelperFunctionsGlobal.GetReplaceablePath(foo));

	if (temp->getformat() == ModelFormat_Basic) PrintDebug("Done.\n");
	else PrintDebug("Error.\n");

	return temp;
}

//Free Object File
void FreeMDL(ModelInfo * pointer) {
	if (pointer) delete(pointer);
}

//Draw a model
void DrawModel(NJS_MODEL * model) {
	ResetRenderSpace();
	ProcessChunkModel((NJS_CNK_MODEL*)model);
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

void njCalcPoint(NJS_VECTOR *transform, NJS_VECTOR *out, float *matrix, uint8_t somebool) {
	float x = matrix[1] * transform->y + *matrix * transform->x + matrix[2] * transform->z;
	float y = matrix[4] * transform->x + matrix[5] * transform->y + matrix[6] * transform->z;
	float z = matrix[8] * transform->x + matrix[9] * transform->y + matrix[10] * transform->z;

	if (!somebool)
	{
		x = matrix[3] + x;
		y = matrix[7] + y;
		z = matrix[11] + z;
	}

	out->x = x;
	out->y = y;
	out->z = z;
}

void njScalef(Float f) {
	njScale(f, f, f);
}

void njAddVector(NJS_VECTOR* vd, NJS_VECTOR* vs) {
	vd->x += vs->x;
	vd->y += vs->y;
	vd->z += vs->z;
}