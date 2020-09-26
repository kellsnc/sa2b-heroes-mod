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

DataPointer(NJS_VECTOR*, CameraPosArray, 0x1DD92B0);
DataPointer(int, CurrentScreen, 0x1DD92A0);

int __cdecl GetLandVisibility(float x, float z);
Trampoline GetLandVisibility_r(0x47C8D0, 0x47C8D6, GetLandVisibility);
int __cdecl GetLandVisibility(float x, float z) {
	NJS_VECTOR* position = &CameraPosArray[CurrentScreen * 2];
	
	for (Uint8 i = 0; i < LengthOfArray(ChunkInfos); ++i) {
		if (position->x > ChunkInfos[i].MinX && position->x < ChunkInfos[i].MaxX &&
			position->y > ChunkInfos[i].MinY && position->y < ChunkInfos[i].MaxY &&
			position->z > ChunkInfos[i].MinZ && position->z < ChunkInfos[i].MaxZ) {
			return ChunkInfos[i].ChunkID;
		}
	}

	return -1;
}

void LoadChunkFile() {
	std::ifstream file;

	file.open(HelperFunctionsGlobal.GetReplaceablePath((GetLevelFilePath() + "_blk.bin").c_str()), std::ios::in | std::ios::binary);
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