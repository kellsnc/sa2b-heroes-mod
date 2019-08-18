#include "stdafx.h"
#include "seaside-hill.h"

void __cdecl SeasideHill_SkyBox(ObjectMaster *a1) {

}

void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions) {
	WriteData((ObjectFuncPtr*)0x5DD213, SeasideHill_SkyBox);
	
	for (uint8_t i = 0; i < Characters_Amy; i++)
	{
		helperFunctions.RegisterStartPosition(i, startpos);
	}
}

void SeasideHill_OnFrame() {
	ChunkHandler("SH", SeasideHillChunks, LengthOfArray(SeasideHillChunks));
}