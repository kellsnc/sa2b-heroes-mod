#include "stdafx.h"

LandTableInfo* CurrentHeroesLandTable;

// Change the sadx col flags to similar sa2 ones
static void FixColFlags(LandTable* land)
{
	for (int i = 0; i < land->COLCount; ++i)
	{
		switch (land->COLList[i].Flags)
		{
		case 0x80000000:
			break;
		case 0x2:
			land->COLList[i].Flags = 0x40000002;
			break;
		default:
			land->COLList[i].Flags = 0x1;
			break;
		}
	}
}

void UnloadLandTable() {
	if (CurrentHeroesLandTable)
	{
		delete CurrentHeroesLandTable;
		CurrentHeroesLandTable = nullptr;
		CurrentLandTable = nullptr;
	}
}

void LoadLandTable(const char* path, LandTableFormat format)
{
	CurrentHeroesLandTable = new LandTableInfo(HelperFunctionsGlobal.GetReplaceablePath(path));
	LoadLandManager(CurrentHeroesLandTable->getlandtable());
	FixColFlags(CurrentHeroesLandTable->getlandtable());

	LandTableSA2BModels = format == LandTableFormat_SA2B ? 1 : 0;
}