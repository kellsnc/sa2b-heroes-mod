#pragma once

enum class HeroesLevelIDs {
	Invalid = -1,
	TestRoom,
	SeasideHill,
	OceanPalace,
	EggFleet = 13
};

extern HeroesLevelIDs CurrentHeroesLevel;

NJS_TEXLIST* GetCurrentHeroesTexList();
void LoadLevelTex(NJS_TEXLIST* texlist, const char* name);
void CommonLevelInit();
void LoadLevelMusic(char* name);
void LoadLevelLayout(ObjectListHead* objlist, const char* s, const char* u);
void SetStartEndPoints(const HelperFunctions& helperFunctions, StartPosition* start, LevelEndPosition* start2pIntro, StartPosition* end, LevelEndPosition* missionend);
void CommonLevelDelete();

void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions);
void OceanPalace_Init(const char *path, const HelperFunctions &helperFunctions);
void EggFleet_Init(const char *path, const HelperFunctions &helperFunctions);