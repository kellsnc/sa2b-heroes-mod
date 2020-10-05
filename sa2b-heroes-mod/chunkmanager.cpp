#include "stdafx.h"

#pragma pack(push, 1)

struct BLKEntry {
	Sint32 ChunkID;
	Sint32 MinX;
	Sint32 MinY;
	Sint32 MinZ;
	Sint32 MaxX;
	Sint32 MaxY;
	Sint32 MaxZ;
};

#pragma pack(pop)

BLKEntry ChunkInfos[64];
Sint32 CurrentChunk[2] = { 0, 0 };

bool CheckLandVisibility(Sint32 chunk, NJS_VECTOR* position) {
	if (ChunkInfos[0].ChunkID == 0) {
		return true;
	}

	for (Uint8 i = 0; i < LengthOfArray(ChunkInfos); ++i) {
		if (chunk == ChunkInfos[i].ChunkID &&
			position->x >= ChunkInfos[i].MinX && position->x <= ChunkInfos[i].MaxX &&
			position->y >= ChunkInfos[i].MinY && position->y <= ChunkInfos[i].MaxY &&
			position->z >= ChunkInfos[i].MinZ && position->z <= ChunkInfos[i].MaxZ) {
			return true;
		}
	}

	return false;
}

void __cdecl ListGroundForDrawing_r();
Trampoline ListGroundForDrawing_t(0x47CAE0, 0x47CAE8, ListGroundForDrawing_r);
void __cdecl ListGroundForDrawing_r() {
	if (CurrentHeroesLevel != HeroesLevelIDs::Invalid) {
		NJS_VECTOR* position = &CameraScreenArray[CurrentScreen]->pos;

		Uint16 current = 0;

		for (Uint32 i = 0; i < CurrentLandTable->COLCount; ++i) {
			if (CheckLandVisibility(CurrentLandTable->COLList[i].field_18, position)) {
				LandTable_VisibleEntries[current] = &CurrentLandTable->COLList[i];
				CurrentChunk[CurrentScreen] = CurrentLandTable->COLList[i].field_18;
				current += 1;
			}
		}

		LandTable_VisibleEntriesCount = current;
	}
	else {
		VoidFunc(original, ListGroundForDrawing_t.Target());
		original();
	}
}

void FreeChunkFile() {
	memset(&ChunkInfos, 0, sizeof(ChunkInfos));
}

void LoadChunkFile(const char* path) {
	std::ifstream file;

	file.open(HelperFunctionsGlobal.GetReplaceablePath(path), std::ios::in | std::ios::binary);
	file.read((char*)&ChunkInfos[0], SizeOfArray(ChunkInfos));

	for (Uint8 i = 0; i < LengthOfArray(ChunkInfos); ++i) {
		SWAPITSELF(ChunkInfos[i].ChunkID, bswap_S32);
		SWAPITSELF(ChunkInfos[i].MinX, bswap_S32);
		SWAPITSELF(ChunkInfos[i].MinY, bswap_S32);
		SWAPITSELF(ChunkInfos[i].MinZ, bswap_S32);
		SWAPITSELF(ChunkInfos[i].MaxX, bswap_S32);
		SWAPITSELF(ChunkInfos[i].MaxY, bswap_S32);
		SWAPITSELF(ChunkInfos[i].MaxZ, bswap_S32);
	}

	file.close();
}