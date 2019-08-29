#include "stdafx.h"

HMODULE hmodule = GetModuleHandle(__TEXT("Data_DLL_orig"));
NJS_TEXLIST * LevelTexList;

uint8_t CurrentChunk = 0;
std::string modpath;

LandTableInfo *info = nullptr;
LandTableInfo *oldinfo = nullptr;

bool restart;

enum HeroesLevelIDs {
	HeroesLevelID_SeasideHill = 13
};

void LandManagerHook(int a1, LandTable *a2)
{
	LandTableSA2BModels = 0;
	LoadLandManager(a2);
}

void FixColFlags(LandTable *land) {
	for (int i = 0; i < land->COLCount; ++i) {		
		switch (land->COLList[i].Flags) {
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

void SwapCurrentLandTable() {
	LandTable *land = info->getlandtable();
	LandTable *cland = nullptr;
	
	switch (CurrentLevel) {
	case HeroesLevelID_SeasideHill:
		cland = (LandTable *)GetProcAddress(hmodule, "objLandTable0013");
		land->TextureName = (char*)"seasidehill";
		break;
	}

	land->TextureList = cland->TextureList;
	
	*cland = *land;
	CurrentLandTable = land;
	FixColFlags(CurrentLandTable);
	LoadLandManager(land);
}

void LoadLevelFile(const char *shortname, int chunknb) {
	std::string numtos = std::to_string(chunknb);

	PrintDebug("[SHM] Loading "); PrintDebug(shortname); if (chunknb < 10) PrintDebug("0");
	PrintDebug(numtos.c_str()); PrintDebug("... ");

	std::string fullPath = modpath + "\\gd_PC\\";
	fullPath += shortname;
	if (chunknb < 10) fullPath += "0";
	fullPath += numtos + ".sa2lvl";
	const char *foo = fullPath.c_str();

	PrintDebug("Freeing chunk... ");
	
	if (info) {
		if (oldinfo) {
			delete oldinfo;
			oldinfo = nullptr;

		}
		oldinfo = info;
		info = nullptr;
	}

	info = new LandTableInfo(foo);

	PrintDebug("Done. Loaded '"); PrintDebug(foo); PrintDebug("'. Swapping landtable... ");

	CurrentChunk = chunknb;
	SwapCurrentLandTable();

	PrintDebug("Done. \n");
}

void ChunkHandler(const char * level, CHUNK_LIST * chunklist, uint8_t size) {
	if (!MainCharObj1[0]) return;
	
	for (Int i = 0; i < size; ++i) {
		if (chunklist[i].Chunk != CurrentChunk) {
			EntityData1 *entity = MainCharObj1[0];
			if (entity != nullptr) {
				NJS_VECTOR pos = MainCharObj1[0]->Position;

				if (((chunklist[i].Position1.x == 0 || pos.x < chunklist[i].Position1.x)) &&
					((chunklist[i].Position1.y == 0 || pos.y < chunklist[i].Position1.y)) &&
					((chunklist[i].Position1.z == 0 || pos.z < chunklist[i].Position1.z)) &&
					((chunklist[i].Position2.x == 0 || pos.x > chunklist[i].Position2.x)) &&
					((chunklist[i].Position2.y == 0 || pos.y > chunklist[i].Position2.y)) &&
					((chunklist[i].Position2.z == 0 || pos.z > chunklist[i].Position2.z))) {

					LoadLevelFile(level, chunklist[i].Chunk);
					break;
				}
			}
		}
	}
}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		if (helperFunctions.Version < 5)
			MessageBoxA(MainWindowHandle, "Your copy of the mod loader does not support API version 5. Some functionality will not be available.\n\nPlease exit the game and update the mod loader for the best experience.", "SA2B Dreamcast Conversion", MB_ICONWARNING);

		modpath = std::string(path);

		WriteCall((void*)0x5DCDF7, LandManagerHook);
		WriteData((char*)0x5DD4F0, (char)0xC3);
		WriteData<2>((void*)0x47C2BC, 0x90u);

		SeasideHill_Init(path, helperFunctions);
	}

	__declspec(dllexport) void OnFrame() {
		switch (CheckModelLoaded()) {
		case 1:
			switch (CurrentLevel) {
			case HeroesLevelID_SeasideHill:
				CommonObjects_LoadModels();
				SeasideHill_LoadModels();
				break;
			}
			break;
		case 2:
			switch (CurrentLevel) {
			case HeroesLevelID_SeasideHill:
				CommonObjects_FreeModels();
				SeasideHill_FreeModels();
				break;
			}
			break;
		default:
			break;
		}

		if (GameState == 9 || GameState == 13 || GameState == GameStates_RestartLevel_1)
			restart = true;

		if (GameState != GameStates_Pause) {
			switch (CurrentLevel) {
			case HeroesLevelID_SeasideHill:
				SeasideHill_OnFrame();
				break;
			}
		}

		if (GameState == 0) {
			CurrentChunk = 0;
			restart = false;
		}
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}