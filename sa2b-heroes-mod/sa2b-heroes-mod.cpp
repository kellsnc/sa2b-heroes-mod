#include "stdafx.h"

HelperFunctions HelperFunctionsGlobal;

std::string LevelFilePath;
std::string LevelName;
uint8_t CurrentChunk = 0;

NJS_TEXLIST* CurrentHeroesTexList = nullptr;

int CurrentHeroesLevel = 1;

std::string GetLevelFilePath() {
	return LevelFilePath;
}

NJS_TEXLIST* GetCurrentHeroesTexList() {
	return CurrentHeroesTexList;
}

// void __usercall(TexPackInfo* a1@<eax>, NJS_TEXLIST*** a2)
static const void* const LoadTexPacksPtr = (void*)0x44C7B0;
static inline void LoadTexPacks(TexPackInfo* TexPackList, NJS_TEXLIST*** Texlists)
{
	__asm
	{
		push[Texlists]
		mov eax, [TexPackList]
		call LoadTexPacksPtr
		add esp, 4
	}
}

// void __usercall(NJS_TEXLIST*** a1@<eax>, TexPackInfo* a2@<ecx>)
static const void* const FreeTexPacksPtr = (void*)0x44C810;
static inline void FreeTexPacks(NJS_TEXLIST*** Texlists, TexPackInfo* TexPackList)
{
	__asm
	{
		mov ecx, [TexPackList]
		mov eax, [Texlists]
		call FreeTexPacksPtr
	}
}

//Load the common texpacks, and fill the many common texlists
//Set some other common level stuff
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

	std::string LevelName = "s";

	if (CurrentHeroesLevel < 10) {
		LevelName += "0";
	}

	LevelName += std::to_string(CurrentHeroesLevel);

	LevelFilePath = "resource\\gd_PC\\" + LevelName;
	LoadChunkFile();
	LoadLandTable();
}

//Delete the heroes landtable at stage exit
void CommonLevelDelete() {
	CommonObjects_FreeModels();
	FreeTexPacks((NJS_TEXLIST***)0x109E748, (TexPackInfo*)0x109E810);
	
	UnloadLandTable();

	DropRingsFunc_ptr = nullptr;
	DisplayItemBoxItemFunc_ptr = nullptr;

	*(void**)0x1DE4680 = nullptr;
	*(void**)0x1DE4684 = nullptr;
	*(void**)0x1DE4688 = nullptr;
	*(void**)0x1DE468C = nullptr;

	DeleteObject_(LandManagerPtr);
	DeleteObject_(SetObject_ptr);
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

void LoadLevelTex(NJS_TEXLIST* texlist) {
	LoadTextureList(LevelName.c_str(), texlist);
	CurrentHeroesTexList = texlist;
	CurrentLandTable->TextureList = texlist;
	CurrentLandTable->TextureName = (char*)LevelName.c_str();
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