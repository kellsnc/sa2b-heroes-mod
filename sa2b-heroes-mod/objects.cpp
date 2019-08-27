#include "stdafx.h"

bool ModelLoaded = false;

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

//Check if objects can be loaded
int CheckModelLoaded() {
	if (GameState == 0 && ModelLoaded == true) {
		ModelLoaded = false;
		return 2;
	}
	else if (GameState == GameStates_Loading && ModelLoaded == false) {
		ModelLoaded = true;
		return 1;
	}
	else {
		return 0;
	}
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

bool ClipSetObject(ObjectMaster *a1) {
	if (IsPlayerInsideSphere(&a1->Data1.Entity->Position, a1->SETData->field_C / 1000)) return 1;
	else {
		DeleteObject_(a1);
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

Rotation fPositionToRotation(NJS_VECTOR orig, NJS_VECTOR point) {
	NJS_VECTOR dist;
	Rotation result;

	dist.x = orig.x - point.x;
	dist.y = orig.y - point.y;
	dist.z = orig.z - point.z;

	result.x = atan2(dist.y, dist.z) * 65536.0 * -0.1591549762031479;
	float len = dist.z * dist.z + dist.y * dist.y;
	result.y = atan2(dist.x, sqrt(len)) * 65536.0 * 0.1591549762031479;

	if (dist.x < 0 && dist.z < 0) { result.y = result.y; result.x = result.x; }
	if (dist.z < 0 && dist.x > 0) { result.y = result.y; result.x = result.x; }
	if (dist.x < 0 || dist.z < 0) { result.y += 0x8000; result.x += 0x8000; }
	if (dist.x < 0 && dist.z > 0) { result.y += 0x8000; result.x += 0x8000; }

	result.y = -result.y - 0x4000;
	return result;
}

void TransformSpline(EntityData1 * entity, NJS_VECTOR orig, NJS_VECTOR dest, float state) {
	entity->Position.x = (dest.x - orig.x) * state + orig.x;
	entity->Position.y = ((dest.y - orig.y) * state + orig.y);
	entity->Position.z = (dest.z - orig.z) * state + orig.z;
}

int GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest) {
	return sqrtf(powf(dest->x - orig->x, 2) + powf(dest->y - orig->y, 2) + powf(dest->z - orig->z, 2));
}