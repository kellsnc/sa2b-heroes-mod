#include "stdafx.h"

bool ModelLoaded = false;

//Load Object File
ModelInfo* LoadMDL(const char *name) {
	PrintDebug("[SHM] Loading model "); PrintDebug(name); PrintDebug("... ");

	std::string fullPath = modpath + "\\gd_PC\\";
	fullPath = fullPath + name + ".sa2mdl";
	const char *foo = fullPath.c_str();

	ModelInfo * temp = new ModelInfo(foo);

	if (temp->getformat() == ModelFormat_Basic) PrintDebug("Done.\n");
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

//check if we can display a SOI_LIST2 model
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

int ClipSetObject(ObjectMaster *a1) {
	if (a1->SETData)
	{
		return ClipObject(a1, a1->SETData->field_C);
	}
	else
	{
		return ClipObject(a1, 168100.0);
	}

	return 0;
}