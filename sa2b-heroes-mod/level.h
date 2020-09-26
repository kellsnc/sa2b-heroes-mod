#pragma once

enum class HeroesLevelIDs {
	Invalid = -1,
	TestRoom = 0,
	SeasideHill = 1,
	OceanPalace,
	EggFleet = 13
};

extern HeroesLevelIDs CurrentHeroesLevel;

NJS_TEXLIST* GetCurrentHeroesTexList();
void LoadLevelTex(NJS_TEXLIST* texlist, const char* name);
void CommonLevelInit();
void LoadLevelMusic(char* name);
void SetStartEndPoints(const HelperFunctions& helperFunctions, StartPosition* start, LevelEndPosition* start2pIntro, StartPosition* end, LevelEndPosition* missionend);
void CommonLevelDelete();

ModelInfo* LoadMDL(const char *name);
void FreeMDL(ModelInfo * pointer);

void DrawModel(NJS_MODEL * model);
bool ClipSetObject(ObjectMaster *a1);
float* njPushUnitMatrix();
void njTranslateV(float* matrix, NJS_VECTOR* pos);
void njCalcPoint(NJS_VECTOR *transform, NJS_VECTOR *out, float *matrix, uint8_t somebool);

int IsPlayerInsideSphere(NJS_VECTOR *center, float radius);
void TransformSpline(NJS_VECTOR* pos, NJS_VECTOR orig, NJS_VECTOR dest, float state);
float GetDistance(NJS_VECTOR* orig, NJS_VECTOR* dest);
Rotation fPositionToRotation(NJS_VECTOR* orig, NJS_VECTOR* point);

void CommonObjects_LoadModels();
void CommonObjects_FreeModels();

void SeasideHill_Init(const char *path, const HelperFunctions &helperFunctions);
void OceanPalace_Init(const char *path, const HelperFunctions &helperFunctions);
void EggFleet_Init(const char *path, const HelperFunctions &helperFunctions);

void DashHoop(ObjectMaster* a1);
void ObjFan(ObjectMaster *obj);
void RingGroup(ObjectMaster* obj);
void DashRampAdjust(ObjectMaster* obj);
void Boxes(ObjectMaster* a1);
void Robots(ObjectMaster* a1);
void Beetle_Stationary(ObjectMaster* a1);
void Beetle_Attack(ObjectMaster* a1);
void Beetle_Electric(ObjectMaster* a1);

extern NJS_MATERIAL matlist_col[1];