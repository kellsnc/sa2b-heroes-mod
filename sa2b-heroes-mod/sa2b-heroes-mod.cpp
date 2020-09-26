#include "stdafx.h"

HelperFunctions HelperFunctionsGlobal;

HeroesLevelIDs CurrentHeroesLevel = HeroesLevelIDs::Invalid;
NJS_TEXLIST* CurrentHeroesTexList = nullptr;

NJS_TEXLIST* GetCurrentHeroesTexList() {
	return CurrentHeroesTexList;
}

// Load the common texpacks, and fill the many common texlists
void CommonLevelInit() {
	DropRingsFunc_ptr = DropRings;
	DisplayItemBoxItemFunc_ptr = DisplayItemBoxItem;

	CommonObjects_LoadModels();

	//Chaos Drive Function Pointers
	dword_1DE4680 = (void*)0x6B6C20;
	dword_1DE4684 = (void*)0x6BBAE0;
	dword_1DE4688 = (void*)0x6BC450;
	dword_1DE468C = (void*)0x6BC4A0;

	LoadTexPacks((TexPackInfo*)0x109E810, (NJS_TEXLIST***)0x109E748);
}

//Delete the heroes landtable at stage exit
void CommonLevelDelete() {
	CommonObjects_FreeModels();
	FreeTexPacks((NJS_TEXLIST***)0x109E748, (TexPackInfo*)0x109E810);
	
	UnloadLandTable();
	FreeChunkFile();

	DropRingsFunc_ptr = nullptr;
	DisplayItemBoxItemFunc_ptr = nullptr;

	*(void**)0x1DE4680 = nullptr;
	*(void**)0x1DE4684 = nullptr;
	*(void**)0x1DE4688 = nullptr;
	*(void**)0x1DE468C = nullptr;

	DeleteObject_(LandManagerPtr);
	DeleteObject_(SetObject_ptr);

	CurrentHeroesLevel = HeroesLevelIDs::Invalid;
	CurrentHeroesTexList = nullptr;
}

//Load the current level music
void LoadLevelMusic(char* name) {
	char character;
	int c = 0;

	do
	{
		character = name[c];
		CurrentSongName[c++] = character;
	} while (character);

	
	PlayMusic(name);
	ResetMusic();
}

void LoadLevelTex(NJS_TEXLIST* texlist, const char* name) {
	LoadTextureList(name, texlist);
	CurrentHeroesTexList = texlist;
	CurrentLevelTexList = texlist;
	CurrentLandTable->TextureList = texlist;
	CurrentLandTable->TextureName = (char*)name;
}

//Set the start and end positions
void SetStartEndPoints(const HelperFunctions &helperFunctions, StartPosition* start, LevelEndPosition* start2pIntro, StartPosition* end, LevelEndPosition* missionend) {
	for (uint8_t i = 0; i < Characters_Amy; i++)
	{
		helperFunctions.RegisterStartPosition(i, *start);
		if (start2pIntro) helperFunctions.Register2PIntroPosition(i, *start2pIntro);

		if (helperFunctions.Version >= 5)
		{
			helperFunctions.RegisterEndPosition(i, *end);
			helperFunctions.RegisterMission23EndPosition(i, *missionend);
		}
	}
}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		if (helperFunctions.Version < 7) {
			MessageBoxA(MainWindowHandle,
				"Your copy of the Mod Loader is outdated, please update it to the latest version.",
				"SA2B Heroes Conversion",
				MB_ICONWARNING);
		}

		HelperFunctionsGlobal = helperFunctions;
		
		SeasideHill_Init(path, helperFunctions);
		OceanPalace_Init(path, helperFunctions);
		EggFleet_Init(path, helperFunctions);
	}

	__declspec(dllexport) void OnFrame() {
		TwoPlayerMode = 1;
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}