#include "stdafx.h"

NJS_MATERIAL matlist_col[] = {
	{ { 0xFFFFFFFF },{ 0xFFFFFFFF }, 0, 0, NJD_DA_INV_SRC | NJD_SA_SRC }
};

//Load Object File
ModelInfo* LoadMDL(const char *name) {
	PrintDebug("[SHM] Loading model "); PrintDebug(name); PrintDebug("... ");

	std::string fullPath = modpath + "\\gd_PC\\";
	fullPath = fullPath + name + ".sa2mdl";
	const char *foo = fullPath.c_str();

	ModelInfo * temp = new ModelInfo(foo);

	if (temp->getformat() == ModelFormat_Chunk) PrintDebug("Done.\n");
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

//Collision Checks
int IsPlayerInsideSphere(NJS_VECTOR *center, float radius) {
	for (uint8_t player = 0; player < 2; ++player) {
		if (!MainCharObj1[player]) continue;
		
		NJS_VECTOR *pos = &MainCharObj1[player]->Position;
		if ((powf(pos->x - center->x, 2) + pow(pos->y - center->y, 2) + pow(pos->z - center->z, 2)) <= pow(radius, 2)) {
			return player + 1;
		}
	}
	return 0;
}

//Check if we can display a SOI_LIST2 model
bool CheckModelDisplay(SOI_LIST item) {
	if (item.Chunk == CurrentChunk || item.Chunk == 0) {
		if (item.DrawDistance == 0.0f) {
			return true;
		}
		else {
			if (IsPlayerInsideSphere(&item.Position, item.DrawDistance) == true)
				return true;
		}
	}
	return false;
}

bool CheckModelDisplay2(SOI_LIST2 item) {
	if (item.Chunk == CurrentChunk || item.Chunk == 0) {
		if (item.DrawDistance == 0.0f) {
			return true;
		}
		else {
			if (IsPlayerInsideSphere(&item.Position, item.DrawDistance) == true)
				return true;
		}
	}
	return false;
}

bool ClipSetObject(ObjectMaster *obj) {
	if (IsPlayerInsideSphere(&obj->Data1.Entity->Position, obj->SETData->field_C / 1000)) return 1;
	else {
		DeleteObject_(obj);
		return 0;
	}
}

//Per-texture animation
void AnimateTextures(SH_ANIMTEXS *list, Int listcount) {
	if (CurrentLandTable) {
		for (uint8_t count = 0; count < listcount; ++count) {
			SH_ANIMTEXS * clist = &list[count];
			int base = clist->texid;
			NJS_TEXNAME * texname = &CurrentLandTable->TextureList->textures[base];

			if (clist->cache < clist->count) {
				if (FrameCount % clist->duration[clist->cache] == 0) {
					if (clist->cache == 0) clist->address = texname->texaddr;
					texname->texaddr = CurrentLandTable->TextureList->textures[base + clist->cache].texaddr;
					clist->cache++;
				}
			}
			else {
				clist->cache = 0;
				texname->texaddr = clist->address;
			}
		}
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

void TransformSpline(NJS_VECTOR * pos, NJS_VECTOR orig, NJS_VECTOR dest, float state) {
	pos->x = (dest.x - orig.x) * state + orig.x;
	pos->y = ((dest.y - orig.y) * state + orig.y);
	pos->z = (dest.z - orig.z) * state + orig.z;
}

float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest) {
	return sqrtf(powf(dest->x - orig->x, 2) + powf(dest->y - orig->y, 2) + powf(dest->z - orig->z, 2));
}

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

void njCalcPoint(NJS_VECTOR *transform, NJS_VECTOR *out, float *matrix, uint8_t somebool)
{
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